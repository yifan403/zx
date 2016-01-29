# vim: tabstop=4 shiftwidth=4 softtabstop=4
# Copyright (c) 2012 Zte Technologies Co., Ltd.
# Copyright (c) 2012 OpenStack LLC.
# All Rights Reserved.
#
#    Licensed under the Apache License, Version 2.0 (the "License"); you may
#    not use this file except in compliance with the License. You may obtain
#    a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
#    WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
#    License for the specific language governing permissions and limitations
#    under the License.
"""
Volume driver for ZTE storage systems.
"""
##------------------------------------------------------------------------------------------------##
##                                                                                                ##
##  Volume driver for ZTE storage systems                                                         ##
##                                                                                                ##
##  Note      :                                                                                   ##
##  Date:: 2016-01-28 11:17:35                                                                    ##
##  Vision: K                                                                                     ##
##  File Name : zte_ks.py                                                                         ##
##  Copyright (c) 2012 Zte Technologies Co., Ltd                                                  ##
##                                                                                                ##
##------------------------------------------------------------------------------------------------##
import base64
import os
import paramiko
import re
import socket
import threading
import sys
import urllib
import xmlrpclibex
import zte_pub

from oslo.config import cfg
from xml.etree import ElementTree as ET
from cinder import context
from cinder import exception
#from cinder.openstack.common import excutils
from oslo_utils import excutils
#from cinder.openstack.common import log as logging
from oslo_log import log as logging
from cinder import utils
from cinder.volume import driver
from cinder.image import image_utils
from cinder.i18n import _, _LE, _LI, _LW
from cinder.volume import qos_specs
from cinder.volume import volume_types
import time

LOG = logging.getLogger(__name__)

zte_opt = [
    cfg.StrOpt('cinder_zte_conf_file',
               default='/etc/cinder/cinder_zte_conf.xml',
               help='config data for cinder zte plugin')]

CONF = cfg.CONF
CONF.register_opts(zte_opt)

g_getLunID = 0
ZTE_QOS_KEY_list        = ['maxBWS']
class ZteApi(driver.VolumeDriver):
    def __init__(self, *args, **kwargs):
        super(ZteApi, self).__init__(*args, **kwargs)
        self.configuration.append_config_values(zte_opt)
        self.login_info = {}
        self.session_id = ''

    def _get_xmlrpc_server(self):
        """get xml server"""
        if ((self.login_info['ControllerIP0']) and
                (self.login_info['ControllerIP1'])):

            try:
                xml_url = \
                    'http://'+self.login_info['ControllerIP0']+':8080/RPC2'
                self.server = xmlrpclibex.ServerProxy(xml_url)

            except Exception:
                xml_url = \
                    'http://'+self.login_info['ControllerIP1']+':8080/RPC2'
                self.server = xmlrpclibex.ServerProxy(xml_url)
        else:
            if self.login_info['ControllerIP0']:
                xml_url = \
                    'http://'+self.login_info['ControllerIP0']+':8080/RPC2'
                self.server = xmlrpclibex.ServerProxy(xml_url)
            else:
                xml_url = \
                    'http://'+self.login_info['ControllerIP1']+':8080/RPC2'
                self.server = xmlrpclibex.ServerProxy(xml_url)
        self.driverurl  = xml_url
        log_msg = ('Set zte server is %s.') % xml_url
        LOG.debug(log_msg)

    def _change_xmlrpc_server(self):
        """set xml server"""
        if ((self.login_info['ControllerIP0']) and
                (self.login_info['ControllerIP1'])):
            controllerip=self.login_info['ControllerIP0']
            if (controllerip == self.driverurl.split('//')[1].split(':')[0]):
                controllerip = self.login_info['ControllerIP1']
            xml_url = 'http://'+controllerip+':8080/RPC2'
            self.server = xmlrpclibex.ServerProxy(xml_url)
            self.driverurl  = xml_url
            log_msg = ('Change zte server is %s.') % xml_url
            LOG.debug(log_msg)

    def _user_login(self):
        """user login"""
        try:
            session = \
                self.server.plat.session.signin({'session': ''},
                                                self.login_info['UserName'],
                                                self.login_info['UserPassword'],
                                                self.login_info['LocalIP'],
                                                zte_pub.ZTE_WEB_LOGIN_TYPE)

            if session[0]['returncode'] in [zte_pub.ZTE_SUCCESS,1495]:
                self.session_id = session[0]['session']
                return self.session_id
            else:
                err_msg = (_LE('zte iscsi init:Failed to signin.'
                           'with ret code: %(ret)s'
                             )
                           % {'ret': session[0]['returncode']})
                LOG.error(err_msg)
        except Exception as err:
            LOG.error(_LE('_user_login: %s') % str(err))
        return "-1"

    def do_setup(self, context):
        """Any initialization the volume driver does while starting."""
        LOG.debug(_('do_setup.'))
        self.context = context
        self._check_conf_file()
        self.login_info = self._get_login_info()
        self._get_xmlrpc_server()
        sessionid = self._user_login()
        if sessionid != "-1":
            return
        self._change_xmlrpc_server()
        sessionid = self._user_login()
        if sessionid == "-1":
            err_msg = (_LE('_user_login failed.'))
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)
        return

    def check_for_setup_error(self):
        """Return error if prerequisites aren't met."""
        pass

    def _get_sessionid(self):
        try:
            sid = self.session_id
            ret = self.server.plat.session.heartbeat({"session": sid})
            if ret[0]['returncode'] == zte_pub.ZTE_SUCCESS:
                return sid
            else:
                err_msg = (_LE('heartbeat failed.San %(server)s,ret code: %(ret)s'
                             ) % {'server': self.server,'ret': ret[0]['returncode']})
                LOG.info(err_msg)
        except Exception as err:
            LOG.error(_LE('_get_sessionid: %s') % str(err))

        # an xmlrpc error happen,we have to connect by another ctrlip
        self._change_xmlrpc_server()
        return self._user_login()

    def _get_vd_pool(self):

        sid = self._get_sessionid()
        lun_conf = self._get_lun_conf()
        vd_or_pool_info_list = []

        if lun_conf['StorageVd']:
            for item in lun_conf['StorageVd']:
                if item.text:
                    vd_name = item.text
                    vd_info = {'cVdName': vd_name}
                    ret = self.server.GetVdInfo({"session": sid}, vd_info)
                    vd_info = {'name': vd_name, 'total': 0, 'free': 0}
                    if (ret[0]['returncode'] == zte_pub.ZTE_SUCCESS and
                            1 == ret[1]['sdwState']):
                        vd_info['total'] = (ret[1]['sqwTotalCapacity'] / (1024*1024))
                        vd_info['free'] = (ret[1]['sqwFreeCapacity'] / (1024*1024))
                    #get vd volume num
                    va_param  = {'cVdName': vd_name}
                    ret = self.server.GetVolNamesOnVd({"session": sid}, va_param)
                    if  (ret[0]['returncode'] == zte_pub.ZTE_SUCCESS):
                        vd_info['volnum'] = ret[1]['sdwVolNum']
                        if  (int(vd_info['volnum']) <  int(lun_conf['MaxVolInVd'])):
                            vd_or_pool_info_list.append(vd_info)

        if lun_conf['StoragePool']:
            for item in lun_conf['StoragePool']:
                if item.text:
                    pool_name = item.text
                    pool_info = {'scPoolName': pool_name}
                    ret = self.server.GetPoolInfo({"session": sid}, pool_info)
                    pool_info = {'name': pool_name, 'total': 0, 'free': 0}
                    if (ret[0]['returncode'] == zte_pub.ZTE_SUCCESS and
                            1 == ret[1]['sdwState']):
                        pool_info['total'] = (ret[1]['qwTotalCapacity'] / (1024))
                        pool_info['free'] = (ret[1]['qwFreeCapacity'] / (1024))
                        vd_or_pool_info_list.append(pool_info)

        return vd_or_pool_info_list

    def _find_vd_to_create_volume(self):

        vd_list = self._get_vd_pool()

        vd_name = ''
        max_size = 0

        for vd in vd_list:
            if max_size < vd['free']:
                max_size = vd['free']
                vd_name = vd['name']

        return vd_name

    def _find_pool_to_create_volume(self):

        pool_list = self._get_vd_pool()

        pool_name = ''
        max_size = 0

        for pool in pool_list:
            if max_size < pool['free']:
                max_size = pool['free']
                pool_name = pool['name']

        return pool_name

    def _create_volume_from_vd(self,volume_name,volume_size, vd_name,volume):
        sid = self._get_sessionid()
        lun_conf = self._get_lun_conf()
        vol = {}
        vol['cVdName'] = vd_name
        vol['cVolName'] = volume_name
        vol['sdwChunkSize'] = int(lun_conf['ChunkSize'])
        vol['sqwCapacity'] = long(volume_size)
        vol['sdwCtlPrefer'] = 0xFFFF
        vol['sdwCachePolicy'] = int(lun_conf['CachePolicy'])
        vol['sdwAheadReadSize'] = int(lun_conf['AheadReadSize'])
        vol['dwSSDCacheSwitch'] = int(lun_conf['SSDCacheSwitch'])

        ret = self.server.CreateVol({"session": sid}, vol)
        if (ret[0]['returncode'] != zte_pub.ZTE_ERR_OBJECT_EXIT and
                ret[0]['returncode'] != zte_pub.ZTE_SUCCESS):
            err_msg = (_LE('_create_volume:Failed to Create volume. '
                         'volume name:%(name)s. ret code: %(ret)s'
                         )
                       % {'name': volume_name,
                          'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)

        #set qos
        self._set_volume_qos(volume,volume_name)

        metadata = {"volname":volume_name,"vdname":vd_name}
        return {"metadata":metadata}

    def _create_volume_from_Pool(self, volume_name, volume_size, pool_name,volume):
        sid = self._get_sessionid()
        lun_conf = self._get_lun_conf()
        vol = {}
        vol['scPoolName'] = pool_name
        vol['scVolName'] = volume_name
        vol['sdwStripeDepth'] = int(lun_conf['ChunkSize'])
        vol['qwCapacity'] = long(volume_size)
        vol['sdwCtrlPrefer'] = 0xFFFF
        vol['sdwCachePolicy'] = int(lun_conf['CachePolicy'])
        vol['sdwAheadReadSize'] = int(lun_conf['AheadReadSize'])
        vol['sdwAllocPolicy'] = int(lun_conf['PoolVolAllocPolicy'])
        vol['sdwMovePolicy'] = int(lun_conf['PoolVolMovePolicy'])
        vol['udwIsThinVol'] = int(lun_conf['PoolVolIsThin'])
        vol['uqwInitAllocedCapacity'] = long(lun_conf['PoolVolInitAllocedCapacity'])
        vol['sdwAlarmThreshold'] = int(lun_conf['PoolVolAlarmThreshold'])
        vol['sdwAlarmStopAllocFlag'] = int(lun_conf['PoolVolAlarmStopAllocFlag'])
        vol['dwSSDCacheSwitch'] = int(lun_conf['SSDCacheSwitch'])

        ret = self.server.CreateVolOnPool({"session": sid}, vol)
        if (ret[0]['returncode'] != zte_pub.ZTE_ERR_OBJECT_EXIT and
                ret[0]['returncode'] != zte_pub.ZTE_SUCCESS):
            err_msg = (_LE('_create_volume:Failed to Create volume. '
                         'volume name:%(name)s. ret code: %(ret)s'
                         )
                       % {'name': volume_name,
                          'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)

        #set qos
        self._set_volume_qos(volume,volume_name)

        metadata = {"volname":volume_name, "poolname":pool_name}
        return {"metadata":metadata}

    def _create_volume(self, volume_name, volume_size,volume):
        """create a volume"""
        lun_conf = self._get_lun_conf()
        if lun_conf['StorageVd']:
            vd_name = self._find_vd_to_create_volume()
            if not vd_name:
                err_msg = (_LE('No vd available.' ))
                LOG.error(err_msg)
                raise exception.CinderException(err_msg)
            return self._create_volume_from_vd(volume_name, volume_size, vd_name,volume)
        if lun_conf['StoragePool']:
            pool_name = self._find_pool_to_create_volume()
            if not pool_name:
                err_msg = (_LE('No pool available.'))
                LOG.error(err_msg)
                raise exception.CinderException(err_msg)
            return self._create_volume_from_Pool(volume_name, volume_size, pool_name,volume)

    def create_volume(self, volume):
        """Create a new volume."""
        metadata         = None
        v_metadata       = None

        volume_name = self._translate_volume_name(volume['name'])
        if not volume_name:
            err_msg = (_LE('_create_volume:Failed,volume_name is None'))
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)
        LOG.debug('create_volume:volume name: %s.' % volume_name)
        volume_size = long(volume['size']*1024*1024)
        metadata = self._create_volume(volume_name, volume_size,volume)
        v_metadata = volume.get('volume_metadata')
        for data in v_metadata:
            metadata['metadata'][data['key']] = data['value']
        return metadata
    def _delete_clone_volume(self, cloned_name):

        sid = self._get_sessionid()

        #cloned_name can't be the same as the new volume_name, so just plus 'c' to make this relationship.
        cloned_name = cloned_name + 'c'
        cvol_name = {'scCvolName': cloned_name}

        ret = self.server.SyncForceDelCvol({"session": sid}, cvol_name)
        if (ret[0]['returncode'] != zte_pub.ZTE_ERR_CLONE_OR_SNAP_NOT_EXIT and
                ret[0]['returncode'] != zte_pub.ZTE_ERR_VAS_OBJECT_NOT_EXIT and
                ret[0]['returncode'] != zte_pub.ZTE_SUCCESS):
            err_msg = (_LE('_delete_clone_volume:Failed to clone vol.'
                         'fracture name:%(name)s with ret code: %(ret)s'
                         )
                       % {'name': cloned_name,
                          'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)

    def _delete_volume(self, volume_name):
        """test"""

        sid = self._get_sessionid()

        vol_name = {'cVolName': volume_name}
        ret = self.server.DelVol({"session": sid}, vol_name)
        if (ret[0]['returncode'] != zte_pub.ZTE_ERR_VOLUME_NOT_EXIT and 
                ret[0]['returncode'] != zte_pub.ZTE_ERR_LUNDEV_NOT_EXIT and
                ret[0]['returncode'] != zte_pub.ZTE_SUCCESS):
            err_msg = (_LE('_delete_volume:Failed to delete volume.'
                       'volume name:%(name)s. ret code: %(ret)s'
                         )
                       % {'name': volume_name,
                       'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)
            
    def _remove_volume_from_group(self,volume):
        sid = self._get_sessionid()
        group_names = []
        ret = self.server.GetGrpNamesOfVol({"session": sid},{'cVolName': volume})
        if ret[0]['returncode'] == zte_pub.ZTE_SUCCESS:
            group_num = int(ret[1]['sdwMapGrpNum'])
            for index in range(0,group_num):
                group_name = ret[1]['cMapGrpNames'][index]
                lun_ID = ret[1]['sdwLunLocalId'][index]
                self._map_delete_lun(lun_ID, group_name)
                
    def delete_volume(self, volume):
        """Delete a volume."""
        volume_name = self._translate_volume_name(volume['name'])
        LOG.debug('delete_volume: volume name: %s.' % volume_name)

        # should find the volume by the name from the storage
        #if volume['source_volid'] is not None or volume['snapshot_id'] is not None:
        #    self._delete_clone_volume(volume_name)
        self._delete_clone_ralation_by_volname(volume_name,False)
        self._remove_volume_from_group(volume_name)
        self._delete_volume(volume_name)
    def _delete_clone_ralation_by_volname(self,volname,isSnapShot):
        sid = self._get_sessionid()
        svol_name = {'scVolName': volname}
        LOG.debug(_LE('GetCvolNamesOnVol: volume name: %s.') % svol_name)
        ret = self.server.GetCvolNamesOnVol({"session": sid}, svol_name)
        if (ret[0]['returncode'] == zte_pub.ZTE_SUCCESS):
            scCvolNames = ret[1]['scCvolNames']
            for i in range(0,ret[1]['sdwCvolNum']):
                cloned_name = scCvolNames[i]
                cvol_name = {'scCvolName': cloned_name}
                ret = self.server.SyncForceDelCvol({"session": sid}, cvol_name)
                if (ret[0]['returncode'] != zte_pub.ZTE_ERR_CLONE_OR_SNAP_NOT_EXIT and
                        ret[0]['returncode'] != zte_pub.ZTE_ERR_VAS_OBJECT_NOT_EXIT and
                        ret[0]['returncode'] != zte_pub.ZTE_SUCCESS):
                    err_msg = (_LE('_delete_clone_volume:Failed to clone vol.'
                             'cloned  name:%(name)s with ret code: %(ret)s'
                             )
                           % {'name': cloned_name,
                              'ret': ret[0]['returncode']})
                    LOG.error(err_msg)
                    if(ret[0]['returncode'] == 17436959):
                        if isSnapShot:
                            raise exception.SnapshotIsBusy(err_msg)
                        else:
                            raise exception.VolumeIsBusy(err_msg)
                    else:
                        raise exception.CinderException(err_msg)
        #delete clone ralation where volume is target volume
        cloned_name = volname+'c'
        cvol_name = {'scCvolName': cloned_name}
        ret = self.server.SyncForceDelCvol({"session": sid}, cvol_name)
        if(ret[0]['returncode'] != zte_pub.ZTE_SUCCESS):
            LOG.debug(_LE('SyncForceDelCvol: volume name(name): %s.with ret code: %(ret)s') %
                      {'name': cvol_name,
                       'ret': ret[0]['returncode']})
        if(ret[0]['returncode'] == 17436959):
            raise exception.VolumeIsBusy(cloned_name)

    def _create_snapshot(self, snapshot_name, src_vol, src_vol_size, snapshot_mode):

        sid = self._get_sessionid()
        lun_conf = self._get_lun_conf()
        svol_paras = {}
        svol_paras['scVolName'] = src_vol
        svol_paras['scSnapName'] = snapshot_name
        svol_paras['sdwSnapType'] = 1
        svol_paras['swRepoSpaceAlarm'] = 60
        svol_paras['swRepoOverflowPolicy'] = 0
        if lun_conf['RepoCapacity']:
            svol_paras['sqwRepoCapacity'] = long(int(lun_conf['RepoCapacity'])*1024*1024)
        else:
            svol_paras['sqwRepoCapacity'] = long(src_vol_size*1024*1024)
        svol_paras['ucIsAgent'] = 0
        svol_paras['ucSnapMode'] = snapshot_mode
        svol_paras['is_private'] = 0
        svol_paras['ucIsAuto'] = 0

        ret = self.server.CreateSvol({"session": sid}, svol_paras)
        if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
            err_msg = (_LE('_create_snapshot:Failed to create snap.'
                         'snap name:%(snapname)s,srvol name :%(srv)s '
                         'with ret code: %(ret)s'
                         )
                       % {'snapname': snapshot_name,
                           'srv': src_vol,
                          'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)

        metadata = {"snapshot_name":snapshot_name,"source_vol":src_vol}
        return {"metadata":metadata}


    def create_snapshot(self, snapshot):
        """create a snapshot from volume"""
        snapshot_name = self._translate_volume_name(snapshot['name'])
        volume_name = self._translate_volume_name(snapshot['volume_name'])
        volume_size = snapshot['volume_size']
        self._create_snapshot(snapshot_name, volume_name,volume_size, 0)

    def _delete_snapshot(self, snapshot_name):
        sid = self._get_sessionid()

        svol_name = {'scSnapName': snapshot_name}

        ret = self.server.SyncForceDelSvol({"session": sid}, svol_name)
        if (ret[0]['returncode'] != zte_pub.ZTE_ERR_CLONE_OR_SNAP_NOT_EXIT and
                ret[0]['returncode'] != zte_pub.ZTE_ERR_VAS_OBJECT_NOT_EXIT and
                ret[0]['returncode'] != zte_pub.ZTE_SUCCESS):
            err_msg = (_LE('_delete_snapshot:Failed to delete snap.'
                         'snap name:%(snapname)s with ret code: %(ret)s'
                         )
                       % {'snapname': snapshot_name,
                          'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            if(ret[0]['returncode'] == 16917163):
                raise exception.SnapshotIsBusy(err_msg)
            else:
                raise exception.CinderException(err_msg)

    def delete_snapshot(self, snapshot):
        """delete a snapshot volume"""
        snapshot_name = self._translate_volume_name(snapshot['name'])
        self._delete_clone_ralation_by_volname(snapshot_name,True)
        self._delete_snapshot(snapshot_name)

    def copy_image_to_volume(self, context, volume, image_service, image_id):
        """Fetch the image from image_service and write it to the volume."""
        LOG.debug('copy_image_to_volume %s.' % volume['name'])
        vol_allocation =self._get_allocation_conf()
        properties = utils.brick_get_connector_properties()
        attach_info = self._attach_volume(context, volume, properties)

        try:
            image_utils.fetch_to_raw(context,
                                     image_service,
                                     image_id,
                                     attach_info[0]['device']['path'],
                                     vol_allocation,
                                     size=volume['size'])
        finally:
            self._detach_volume(context, attach_info[0], volume, properties)

    def _extend_volume(self, volume_name, inc_size):
        sid = self._get_sessionid()
        ext_vol_paras = {}
        lun_conf = self._get_lun_conf()
        if lun_conf['StorageVd']:
            ext_vol_paras['cVolName'] = volume_name
            ext_vol_paras['sqwExpandSize'] = long(inc_size*1024)
            ret = self.server.ExpandVol({"session": sid}, ext_vol_paras)
            if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
                err_msg = (_LE('_extend_volume:Failed to extend vol.'
                         'vol name:%(name)s with ret code: %(ret)s'
                         )
                       % {'name': volume_name,
                          'ret': ret[0]['returncode']})
                LOG.error(err_msg)
                raise exception.CinderException(err_msg)
        if lun_conf['StoragePool']:
            ext_vol_paras['scVolName'] = volume_name
            ext_vol_paras['qwExpandCapacity'] = long(inc_size*1024)
            ret = self.server.ExpandVolOnPool({"session": sid}, ext_vol_paras)
            if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
                err_msg = (_LE('_extend_volume:Failed to extend vol.'
                         'vol name:%(name)s with ret code: %(ret)s'
                         )
                       % {'name': volume_name,
                          'ret': ret[0]['returncode']})
                LOG.error(err_msg)
                raise exception.CinderException(err_msg)

    def extend_volume(self, volume, new_size):
        """extend volume size"""
        size_increase = (int(new_size)) - volume['size']
        volume_name = self._translate_volume_name(volume['name'])
        self._extend_volume(volume_name, size_increase)

    def _get_vol_info(self, volume_name):
        """extend volume size"""
        sid = self._get_sessionid()
        vol_info = {'cVolName': volume_name}
        ret = self.server.GetVolInfo({"session": sid}, vol_info)
        if ret[0]['returncode'] == zte_pub.ZTE_ERR_VOLUME_NOT_EXIT:
            return
        if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
            err_msg = (_LE('_get_vol_info:Failed to get vol info.'
                         'vol name:%(name)s with ret code: %(ret)s'
                         )
                       % {'name': volume_name,
                          'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)

        return ret[1]

    def _cloned_volume(self, cloned_name, src_name,src_vol_name, vol_size,vol_type,volume):

        sid = self._get_sessionid()
        #delete src vol's clone
        self._delete_clone_ralation_by_volname(src_name,False)
        #create new volume

        volmetadata = self._create_volume(cloned_name,vol_size,volume)

        cvol_paras = {}
        #cloned_name can't be the same as the new volume_name, so just plus 'c' to make this relationship.
        cvol_paras['scCvolName'] = cloned_name + 'c'
        cvol_paras['scBvolName'] = src_name
        cvol_paras['scTargetName'] = cloned_name
        cvol_paras['sdwInitSync'] = 1
        cvol_paras['sdwProtectRestore'] = 0
        cvol_paras['sdwPri'] = 0
        cvol_paras['sdwPolicy'] = 0
        cvol_paras['sdwBvolType'] = vol_type

        ret = self.server.CreateCvol({"session": sid}, cvol_paras)
        if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
            # CreateCvol fail. Need to rollback: delete the volume that we had created before.
            self._delete_volume(cloned_name)

            err_msg = (_LE('_cloned_volume:Failed to clone vol.'
                         'vol name:%(name)s with ret code: %(ret)s'
                         )
                       % {'name': src_name,
                          'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)
        return volmetadata

    def create_cloned_volume(self, volume, src_vref):
        """clone a volume"""
        metadata         = None
        v_metadata       = None

        bvol_name = self._translate_volume_name(src_vref['name'])
        cvol_name = self._translate_volume_name(volume['name'])
        if int(volume['size']) < src_vref['size']:
            err_msg = (_LE('create_cloned_volume:cloned volume size invalid.'
                         'clone siez:%(cloned_size)s '
                         'src volume size: %(volume_size)s'
                         )
                       % {'cloned_size': int(volume['size']),
                          'volume_size': int(src_vref['size'])})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)
        else:
            volume_size = long(volume['size']*1024*1024)

        metadata = self._cloned_volume(cvol_name, bvol_name, bvol_name,volume_size,0,volume)
        v_metadata = volume.get('volume_metadata')
        for data in v_metadata:
            metadata['metadata'][data['key']] = data['value']
        return metadata
        # after clone volume,we need to fracture it,so it will be independence
        #self._fracture_clone_volume(cvol_name)

    def create_volume_from_snapshot(self,volume, snapshot):
        """ create  volume from  snapshot """
        metadata         = None

        bvol_name = self._translate_volume_name(snapshot['name'])
        bsvol_name = self._translate_volume_name(snapshot['volume_name'])
        cvol_name = self._translate_volume_name(volume['name'])
        if int(volume['size']) < snapshot['volume_size']:
            err_msg = (_LE('create_volume_from_snapshot:cloned volume size invalid.'
                         'clone siez:%(cloned_size)s '
                         'src volume size: %(volume_size)s'
                         )
                       % {'cloned_size': int(volume['size']),
                          'volume_size': int(snapshot['volume_size'])})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)
        else:
            volume_size = long(volume['size']*1024*1024)

        metadata = self._cloned_volume(cvol_name, bvol_name,bsvol_name, volume_size,1,volume)
        v_metadata = volume.get('volume_metadata')
        for data in v_metadata:
            metadata['metadata'][data['key']] = data['value']
        return metadata

    def create_export(self, context, volume):
        """ Exports the volume """
        pass

    def ensure_export(self, context, volume):
        """Driver entry point to get the export info for a existing volume."""
        pass

    def remove_export(self, context, volume_id):
        """Driver entry point to remove an export for a volume."""
        pass

    def get_volume_stats(self, refresh=False):
        """Get volume status.

        If 'refresh' is True, run update the stats first.
        """
        if refresh:
            self._update_volume_status()

        return self._stats

    def _check_conf_file(self):
        """Check the config file, make sure the key elements are set."""
        root = self._read_xml()
        try:
            IP0 = root.findtext('Storage/ControllerIP0')
            IP1 = root.findtext('Storage/ControllerIP1')
            local_ip = root.findtext('Storage/LocalIP')
            usr = root.findtext('Storage/UserName')
            pwd = root.findtext('Storage/UserPassword')
            vd_list = root.findall('LUN/StorageVd')
            pool_list = root.findall('LUN/StoragePool')

            # check the login conf
            if ((not IP0 and not IP1) or
                    (not local_ip) or
                    (not usr) or
                    (not pwd)):
                err_msg = (_LE('Config file is wrong. Controler IP, '
                             'UserName and UserPassword must be set.'))
                LOG.error(err_msg)
                raise exception.InvalidInput(reason=err_msg)

            # check the lun conf
            is_lun_conf_wrg = True
            if (vd_list and pool_list):
                err_msg = (_LE('Config file is wrong. you can not configure both vd and pool'))
                LOG.error(err_msg)
                raise exception.InvalidInput(reason=err_msg)

            for item in vd_list:
                if item.text is not None:
                    is_lun_conf_wrg = False
                    break

            for item in pool_list:
                if item.text is not None:
                    is_lun_conf_wrg = False
                    break

            if is_lun_conf_wrg:
                err_msg = (_LE('Config file is wrong. '
                             'lun storage pool must be set.'))
                LOG.error(err_msg)
                raise exception.InvalidInput(reason=err_msg)

        except Exception as err:
            LOG.error(_LE('_check_conf_file: %s') % str(err))
            raise exception.CinderException(data=err)

    def _read_xml(self):
        """Open xml file."""
        file_name = self.configuration.cinder_zte_conf_file
        try:
            tree = ET.parse(file_name)
            root = tree.getroot()

        except Exception as err:
            LOG.error(_LE('_read_xml:%s') % err)
            raise exception.CinderException(data=err)
        return root

    def _get_login_info(self):
        """Get login IP, username and password from config file."""
        self.login_info = {}
        try:
            file_name = self.configuration.cinder_zte_conf_file
            tree = ET.parse(file_name)
            root = tree.getroot()
            self.login_info['ControllerIP0'] = \
                root.findtext('Storage/ControllerIP0')
            self.login_info['ControllerIP1'] = \
                root.findtext('Storage/ControllerIP1')
            self.login_info['LocalIP'] = root.findtext('Storage/LocalIP')

            need_encode = False
            for key in ['UserName', 'UserPassword']:
                node = root.find('Storage/%s' % key)
                node_text = node.text
                if node_text.find('!$$$') == 0:
                    self.login_info[key] = base64.b64decode(node_text[4:])
                else:
                    self.login_info[key] = node_text
                    node.text = '!$$$' + base64.b64encode(node_text)
                    need_encode = True
            if need_encode:
                try:
                    tree.write(file_name, 'UTF-8')
                except Exception as err:
                    LOG.error(_LE('Write login information to xml error. %s')
                              % err)

        except Exception as err:
            LOG.error(_LE('_get_login_info error. %s') % err)
            raise exception.CinderException(data=err)

        return self.login_info

    def _get_lun_conf(self):
        """get lun conf"""

        lun_info = {}
        root = self._read_xml()
        lun_info['ChunkSize'] = root.findtext('LUN/ChunkSize')
        lun_info['AheadReadSize'] = root.findtext('LUN/AheadReadSize')
        lun_info['CachePolicy'] = root.findtext('LUN/CachePolicy')
        lun_info['SSDCacheSwitch'] = root.findtext('LUN/SSDCacheSwitch')
        lun_info['MaxVolInVd'] = root.findtext('LUN/MaxVolInVd')
        if not lun_info['MaxVolInVd']:
            lun_info['MaxVolInVd'] = 32
        lun_info['StorageVd'] = root.findall('LUN/StorageVd')
        lun_info['StoragePool'] = root.findall('LUN/StoragePool')
        lun_info['RepoCapacity'] = root.findtext('LUN/RepoCapacity')
        lun_info['PoolVolAllocPolicy'] = root.findtext('LUN/PoolVolAllocPolicy')
        lun_info['PoolVolMovePolicy'] = root.findtext('LUN/PoolVolMovePolicy')
        lun_info['PoolVolIsThin'] = root.findtext('LUN/PoolVolIsThin')
        lun_info['PoolVolInitAllocedCapacity'] = root.findtext('LUN/PoolVolInitAllocedCapacity')
        lun_info['PoolVolAlarmThreshold'] = root.findtext('LUN/PoolVolAlarmThreshold')
        lun_info['PoolVolAlarmStopAllocFlag'] = root.findtext('LUN/PoolVolAlarmStopAllocFlag')

        return lun_info

    def _translate_host_name(self, host_name):
        new_name = 'host_' + str(hash(host_name))
        new_name = new_name.replace('-', 'R')
        LOG.debug('_translate_host_name:Name in cinder: %(old)s, '
                    'new name in storage system: %(new)s'
                  % {'old': host_name,
                     'new': new_name})

        return new_name

    def _translate_volume_name(self, vol_name):
        """Form new names because of the 32-character limit on names."""
        new_name = zte_pub.ZTE_VOL_AND_SNAP_NAME_PREFIX + str(hash(vol_name))
        new_name = new_name.replace('-', 'R')

        LOG.debug('_translate_volume_name:Name in cinder: %(old)s, '
                    'new name in storage system: %(new)s'
                  % {'old': vol_name,
                     'new': new_name})

        return new_name

    def _find_lun(self, name):
        """Get the ID of a LUN with the given LUN name."""
        return 0

    def _genALunid(self, map_group_name):
        """  """

        sid = self._get_sessionid()

        map_grp_info = {'cMapGrpName': map_group_name}
        ret = self.server.GetMapGrpInfo({"session": sid}, map_grp_info)
        if ret[0]['returncode'] == zte_pub.ZTE_SUCCESS:
            lun_num = ret[1]['sdwLunNum']
            lun_info = ret[1]['tLunInfo']
            if int(lun_num) == 0:
                return 0
            lun_list = []
            for count in range(0, int(lun_num)):
                lun_list.append(lun_info[count]['sdwLunId'])

            for id in range(0, 254):
                if id not in lun_list:
                    return id

        else:
            err_msg = (_LE('_genALunid:get lunid for vol fail.'
                         'group name:%(name)s with ret code: %(ret)s'
                         )
                       % {'name': map_group_name,
                          'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)

    def _getLunidFromVol(self, volume_name, map_group_name):
        """if no lunid,generate one lunid"""

        sid = self._get_sessionid()

        lunid = -1
        map_grp_info = {'cMapGrpName': map_group_name}
        ret = self.server.GetMapGrpInfo({"session": sid}, map_grp_info)
        if ret[0]['returncode'] == zte_pub.ZTE_SUCCESS:
            lun_num = ret[1]['sdwLunNum']
            lun_info = ret[1]['tLunInfo']
            if int(lun_num) > 0:
                for count in range(0, int(lun_num)):
                    if volume_name == lun_info[count]['cVolName']:
                        lunid = lun_info[count]['sdwLunId']
                        return lunid
            return -1
        elif ret[0]['returncode'] == zte_pub.ZTE_ERR_GROUP_NOT_EXIT:
            return -1
        else:
            err_msg = (_LE('_getLunidFromVol:get lunid from vol fail.'
                         'group name:%(name)s vol:%(vol)s '
                         'with ret code: %(ret)s'
                         )
                       % {'name': map_group_name,
                          'vol': volume_name,
                          'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)

    def _getLunid(self, volume_name, map_group_name):
        """if no lunid,generate one lunid"""

        sid = self._get_sessionid()

        lunid = -1

        map_grp_info = {'cMapGrpName': map_group_name}
        ret = self.server.GetMapGrpInfo({"session": sid}, map_grp_info)

        if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
            return -1

        lun_num = ret[1]['sdwLunNum']
        lun_info = ret[1]['tLunInfo']
        if int(lun_num) == 0:
            return 1

        lun_list = []
        for count in range(0, int(lun_num)):
            if volume_name == lun_info[count]['cVolName']:
                lunid = lun_info[count]['sdwLunId']
                return lunid
            lun_list.append(lun_info[count]['sdwLunId'])

        for i in range(1, zte_pub.ZTE_GROUP_MAX_LUN-1):
            if i not in lun_list:
                lunid = int(i)
                return lunid

        # don't find a valid lunid
        return -1

    def _get_group_lunnum(self, map_group_name):

        sid = self._get_sessionid()

        map_grp_info = {'cMapGrpName': map_group_name}
        ret = self.server.GetMapGrpInfo({"session": sid}, map_grp_info)

        if ret[0]['returncode'] == zte_pub.ZTE_SUCCESS:
            lun_num = ret[1]['sdwLunNum']
            return int(lun_num)
        elif ret[0]['returncode'] == zte_pub.ZTE_ERR_GROUP_NOT_EXIT:
            return -1
        else:
            err_msg = (_LE('_map_lun:get group info fail.'
                         'group name:%(name)s with ret code: %(ret)s'
                         )
                       % {'name': map_group_name,
                          'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)

    def _delete_group(self, map_group_name):
        """ """
        sid = self._get_sessionid()

        # before delete the group, we must delete the hosts in group
        self._map_delete_host(map_group_name)

        map_grp_info = {'cMapGrpName': map_group_name}
        ret = self.server.DelMapGrp({"session": sid}, map_grp_info)
        if (ret[0]['returncode'] != zte_pub.ZTE_SUCCESS and
                ret[0]['returncode'] != zte_pub.ZTE_ERR_GROUP_NOT_EXIT):
            err_msg = (_LE('_delete_group:del group fail.'
                         'group name:%(name)s with ret code: %(ret)s'
                         )
                       % {'name': map_group_name,
                          'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)

    def _find_group(self, map_group_name):
        """  """

        sid = self._get_sessionid()

        ret = self.server.GetGrpSimpleInfoList({"session": sid})

        if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
            return 0
        map_grp_num = ret[1]['sdwMapGrpNum']
        map_grp_simple_info = ret[1]['tMapGrpSimpleInfo']

        if int(map_grp_num) > 0:
            for count in range(0, int(map_grp_num)):
                if map_group_name == map_grp_simple_info[count]['cMapGrpName']:
                    return 1
                else:
                    continue
        return 0


    def _map_lun(self, initiator_name, volume_name, map_group_name):
        """Map a lun to a host.

        Here we give the hostlun ID which starts from 1.
        """
        #grp_exist = self._find_group(map_group_name)
        #if grp_exist == 0:
        self._create_group(initiator_name, map_group_name)

        # add lun to grp
        time.sleep(0.5)
        lunid = self._getLunid(volume_name, map_group_name)
        if lunid == -1:
            err_msg = (_LE('_map_lun:fail to get lunid.'
                         'group name:%(name)s volume name:%(vol)s'
                         )
                       % {'name': map_group_name,
                          'vol': volume_name})
            LOG.error('fail to get lunid')
            raise exception.CinderException(err_msg)
        self._map_add_lun(lunid, volume_name, map_group_name)

        return lunid

    def _map_add_lun(self, lunid, volume_name, map_group_name):
        """ """

        sid = self._get_sessionid()

        lun_info = {'sdwLunId': lunid, 'cVolName': volume_name}
        add_vol_to_grp = {'cMapGrpName': map_group_name, 'tLunInfo': lun_info}
        ret = self.server.AddVolToGrp({"session": sid}, add_vol_to_grp)
        if ret[0]['returncode'] not in [zte_pub.ZTE_SUCCESS, zte_pub.ZTE_VOLUME_IN_GROUP,16917000]:
            err_msg = (_LE('_map_lun:fail to add vol to grp.'
                         'group name:%(name)s lunid:%(lun)s '
                         'vol:%(vol)s with ret code: %(ret)s'
                         )
                       % {'name': map_group_name,
                          'lun': lunid,
                          'vol': volume_name,
                          'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)


    def _get_group_lunnum(self, map_group_name):

        sid = self._get_sessionid()

        map_grp_info = {'cMapGrpName': map_group_name}
        ret = self.server.GetMapGrpInfo({"session": sid}, map_grp_info)

        if ret[0]['returncode'] == zte_pub.ZTE_SUCCESS:
            lun_num = ret[1]['sdwLunNum']
            return int(lun_num)
        elif ret[0]['returncode'] == zte_pub.ZTE_ERR_GROUP_NOT_EXIT:
            return -1
        else:
            err_msg = (_LE('_map_lun:get group info fail.'
                         'group name:%(name)s with ret code: %(ret)s'
                         )
                       % {'name': map_group_name,
                          'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)

    def _update_volume_group_info(self):

        lun_conf = self._get_lun_conf()
        vd_list = self._get_vd_pool()
        sid = self._get_sessionid()
        vd_info = {}
        vd_info['total'] = 0
        vd_info['free'] = 0

        for item in vd_list:
            vd_info['total'] += item['total']
            vd_info['free'] += item['free']
        return vd_info

    def _get_sysinfo(self):

        sid = self._get_sessionid()
        ret = self.server.GetSysInfo({"session": sid})
        if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
            err_msg = (_LE('_map_lun:get sys info fail.'
                         'with ret code: %(ret)s'
                         )
                       % {'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)

        return ret[1]
    def _get_qos_specs(self, volume):
        '''
        get qos specs information from volume information
        '''
        # ctxt           : context
        # volume_type_id : volume type id
        # volume_type    : volume type
        # qos_specs_dict : qos specs
        # qos_specs_id   : qos specs id

        LOG.debug(_('*****_get_qos_specs,Enter method'))

        # initialize
        ctxt           = None
        volume_type_id = None
        volume_type    = {}
        qos_specs_dict = {}
        qos_specs_id   = None
        qos = {'maxBWS':0}
        # main processing
        volume_type_id = volume.get('volume_type_id', None)

        if volume_type_id is not None:
            ctxt = context.get_admin_context()
            volume_type = volume_types.get_volume_type(ctxt, volume_type_id)
            qos_specs_id = volume_type.get('qos_specs_id')

        if qos_specs_id is not None:
            qos_specs_dict = qos_specs.get_qos_specs(ctxt, qos_specs_id)['specs']
        for key, value in qos_specs_dict.iteritems():
            if key in ZTE_QOS_KEY_list:
                qos[key] = value
                break
            # end of if
        # end of for
        if qos.get('maxBWS')==0:
            qos = None
        LOG.debug(_LE('*****_get_qos_specs,Exit method'))
        return qos

    def _set_volume_qos(self, volume,volume_name):
        sid = self._get_sessionid()
        qos = self._get_qos_specs(volume)
        if qos is not None:
            maxBWS = int(float(qos.get('maxBWS')))
            VolFlowLimitAttr={}
            VolFlowLimitAttr['cVolName'] = volume_name
            VolFlowLimitAttr['sqwTotalFlowLimit'] = maxBWS
            ret = self.server.SetVolFlowLimitAttr({"session": sid}, VolFlowLimitAttr)
            if (ret[0]['returncode'] != zte_pub.ZTE_ERR_OBJECT_EXIT and
                ret[0]['returncode'] != zte_pub.ZTE_SUCCESS):
                err_msg = (_LE('SetVolFlowLimitAttr :Failed to Set Vol Flow Limit Attr. '
                         'volume name:%(name)s. ret code: %(ret)s'
                         )
                       % {'name': volume_name,
                          'ret': ret[0]['returncode']})
                LOG.error(err_msg)
                raise exception.CinderException(err_msg)
    def _update_volume_status(self):
        """Retrieve status info from volume group."""

        LOG.debug("Updating volume status")

        sys_info = self._get_sysinfo()
        data = {}
        backend_name = self.configuration.safe_get('volume_backend_name')
        data["volume_backend_name"] = backend_name or 'ZteISCSIDriver'
        data['vendor_name'] = sys_info['cVendor']
        data['driver_version'] = sys_info['cVersionName']
        data['storage_protocol'] = 'iSCSI'
        data['multiattach']         = True

        vd_info = self._update_volume_group_info()

        data['total_capacity_gb'] = vd_info['total']
        data['free_capacity_gb'] = vd_info['free']
        data['reserved_percentage'] = 0
        data['QoS_support'] = True

        self._stats = data

class ZteISCSIDriver(ZteApi,driver.ISCSIDriver):
    """Zte iSCSI volume driver."""

    def __init__(self, *args, **kwargs):
        super(ZteISCSIDriver, self).__init__(*args, **kwargs)

    def _get_Net_Cfg_ips(self):
        sid = self._get_sessionid()
        ret = self.server.GetSystemNetCfg({"session": sid})
        if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
            err_msg = (_LE('get_Net_Cfg fail.'
                         'with ret code: %(ret)s'
                         )
                       % {'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)

        targetips = []
        net_cfg_info = ret[1]['tSystemNetCfg']
        for item in range(ret[1]['sdwDeviceNum']):
            if net_cfg_info[item]['udwRoleType']==0 and net_cfg_info[item]['cIpAddr']:
                targetips.append(net_cfg_info[item]['cIpAddr'])
        return targetips

    @utils.synchronized('locked_initialize_connection')
    def initialize_connection(self, volume, connector):
        """Map a volume to a host and return target iSCSI information."""
        initiator_name = connector['initiator']
        volume_name = self._translate_volume_name(volume['name'])

        LOG.debug('initialize_connection: volume name: %(volume)s. '
                    'initiator name: %(ini)s.'
                  % {'volume': volume_name,
                     'ini': initiator_name})

        iscsi_conf = self._get_iscsi_info()
        target_ips = iscsi_conf['DefaultTargetIPs']
        map_group_name = self._translate_grp_name(initiator_name)
        lunid = self._map_lun(initiator_name, volume_name, map_group_name)

        target_portals=[]
        target_iqns=[]
        target_luns=[]
        ipnumber=0
        for ip in target_ips:
            iqn = self._get_tgt_iqn(ip)
            if iqn:
                target_iqns.append(iqn)
                target_portals.append('%s:%s' % (ip, '3260'))
                target_luns.append(lunid)
        if not target_iqns:
            msg = (_LE('initialize_connection: Failed to get target ip or iqn '
                     'for initiator %(ini)s, please check config file.')
                   % {'ini': initiator_name})
            LOG.error(msg)
            raise exception.CinderException(reason=msg)

        # Return iSCSI properties.
        properties = {}
        properties['target_discovered'] = False
        properties['target_portal'] = target_portals[0]
        properties['target_iqn'] = target_iqns[0]
        properties['target_lun'] = lunid
        properties['volume_id'] = volume['id']
        properties['target_portals'] = target_portals
        properties['target_iqns'] = target_iqns
        properties['target_luns'] = target_luns
        return {'driver_volume_type': 'iscsi', 'data': properties}

    @utils.synchronized('locked_initialize_connection')
    def terminate_connection(self, volume, connector, **kwargs):
        """Delete map between a volume and a host."""
        initiator_name = connector['initiator']
        volume_name = self._translate_volume_name(volume['name'])

        LOG.debug('terminate_connection:volume name: %(volume)s, '
                    'initiator name: %(ini)s.'
                  % {'volume': volume_name,
                     'ini': initiator_name})

        map_group_name = self._translate_grp_name(initiator_name)
        lunid = self._getLunidFromVol(volume_name, map_group_name)
        self._map_delete_lun(lunid, map_group_name)

    def _get_iscsi_conf(self):
        """get lun conf"""

        lun_info = {}
        root = self._read_xml()
        lun_info['ChunkSize'] = root.findtext('LUN/ChunkSize')
        lun_info['StorageVd'] = root.findall('LUN/StorageVd')

        return lun_info

    def _get_allocation_conf(self):
        """get vol_allocation conf"""

        root = self._read_xml()
        vol_allocation = root.findtext('VOLUME/Volume_Allocation_Ratio')
        if not vol_allocation:
            vol_allocation = zte_pub.ZTE_VOLUME_ALLOCATION_RATIO

        return vol_allocation

    def _get_iscsi_info(self):
        """Get iSCSI info from config file."""
        iscsi_info = {}
        root = self._read_xml()
        try:
            iscsi_info['DefaultTargetIPs'] = self._get_Net_Cfg_ips()
            if not iscsi_info['DefaultTargetIPs']:
                err_msg = _LE('_get_iscsi_info:can not get target ip address')
                LOG.error(err_msg)
                raise exception.InvalidInput(reason=err_msg)
            initiator_list = []
            for dic in root.findall('iSCSI/Initiator'):
                initiator_list.append(dic.attrib)
            iscsi_info['Initiator'] = initiator_list

        except Exception as err:
            LOG.error(_LE('_get_iscsi_info:%s') % str(err))

        return iscsi_info

    def _translate_grp_name(self, grp_name):
        """Form new names because of the 32-character limit on names."""
        new_name = zte_pub.ZTE_HOST_GROUP_NAME_PREFIX + str(hash(grp_name))
        new_name = new_name.replace('-', 'R')

        LOG.debug('_translate_grp_name:Name in cinder: %(old)s, '
                    'new name in storage system: %(new)s'
                  % {'old': grp_name,
                     'new': new_name})

        return new_name

    def _translate_volume_name(self, vol_name, isAdd=False):
        """Form new names because of the 32-character limit on names."""
        new_name = zte_pub.ZTE_VOL_AND_SNAP_NAME_PREFIX_NEW + str(hash(vol_name))
        new_name = new_name.replace('-', 'R')
        if isAdd:
            return new_name
        new_name1 = new_name.replace('OpenCos_', 'OpenStack_')
        LOG.debug('_translate_volume_name:Name in cinder: %(old)s, '
                    'new name in storage system: OpenStack_ or %(new)s'
                  % {'old': vol_name,
                     'new': new_name})
        if self._get_vol_info(new_name1):
            return new_name1
        else:
            return new_name

    def _get_target_ip_ctrl(self, target_ip):
        """Get ctrl which target_ip belong to."""
        LOG.debug('_get_target_ip_ctrl:target IP is %s.' % target_ip)
        sid = self._get_sessionid()
        ret = self.server.GetSystemNetCfg({"session": sid})
        if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
            err_msg = (_LE('_get_target_ip_ctrl:get iscsi port list fail.'
                         'with ret code: %(ret)s'
                         )
                       % {'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)
        count = ret[1]['sdwDeviceNum']
        for index in range(0, count):
            SystemNetCfg = ret[1]['tSystemNetCfg'][index]
            if target_ip == SystemNetCfg['cIpAddr']:
                return SystemNetCfg['udwCtrlId']
        return -1

    def _get_tgt_iqn(self, iscsiip):
        """Get target iSCSI iqn."""
        sid = self._get_sessionid()
        # as the given iscsiip,we need to find it's ctrl number
        ip_ctrl = self._get_target_ip_ctrl(iscsiip)

        if -1 == ip_ctrl:
            err_msg = (_LE('_get_tgt_iqn:get iscsi ip ctrl fail,IP is %s.') % iscsiip)
            LOG.error(err_msg)
            return None

        # get the ctrl iqn
        ret = self.server.GetIscsiTargetName({"session": sid})

        if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
            return None

        target_info = ret[1]['tIscsiTargetInfo']
        ctrl_count = ret[1]['udwCtrlCount']
        for index in range(0, ctrl_count):
            if ip_ctrl == target_info[index]['udwCtrlId']:
                return target_info[index]['cTgtName']
        return None

    def _getLunid(self, volume_name, map_group_name):
        """if no lunid,generate one lunid"""

        sid = self._get_sessionid()

        lunid = -1

        map_grp_info = {'cMapGrpName': map_group_name}
        ret = self.server.GetMapGrpInfo({"session": sid}, map_grp_info)

        if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
            return -1

        lun_num = ret[1]['sdwLunNum']
        lun_info = ret[1]['tLunInfo']
        if int(lun_num) == 0:
            return 1

        lun_list = []
        for count in range(0, int(lun_num)):
            if volume_name == lun_info[count]['cVolName']:
                lunid = lun_info[count]['sdwLunId']
                return lunid
            lun_list.append(lun_info[count]['sdwLunId'])

        for i in range(1, zte_pub.ZTE_GROUP_MAX_LUN-1):
            if i not in lun_list:
                lunid = int(i)
                return lunid

        # don't find a valid lunid
        return -1

    def _create_group(self, initiator_name, map_group_name):
        """ """
        sid = self._get_sessionid()

        map_grp_info = {'cMapGrpName': map_group_name}
        ret = self.server.CreateMapGrp({"session": sid}, map_grp_info)
        if (ret[0]['returncode'] == zte_pub.ZTE_SUCCESS or
                ret[0]['returncode'] == zte_pub.ZTE_ERR_GROUP_EXIT):
            host_info = {}
            host_info['tHost'] = {}
            host_name = self._translate_host_name(initiator_name)
            host_info['tHost']['cHostAlias'] = host_name
            host_info['tHost']['ucOs'] = 1
            host_info['tPort'] = {}
            host_info['tPort']['ucType'] = 1
            host_info['tPort']['cPortName'] = initiator_name
            host_info['tPort']['sdwMultiPathMode'] = 1
            host_info['tPort']['cMulChapPass'] = ''
            
            ''' create host '''
            ret = self.server.CreateHost({"session": sid}, host_info)
            if (ret[0]['returncode'] != zte_pub.ZTE_SUCCESS and
                    ret[0]['returncode'] != zte_pub.ZTE_ERR_HOSTNAME_EXIT and
                    ret[0]['returncode'] != zte_pub.ZTE_ERR_PORT_EXIT and
                     ret[0]['returncode'] != zte_pub.ZTE_ERR_PORT_EXIT_OLD):
                err_msg = (_LE('_create_group:create host fail.'
                             'host name:%(name)s '
                             'with ret code: %(ret)s'
                             )
                           % {'name': host_name,
                               'ret': ret[0]['returncode']})
                LOG.error(err_msg)
                raise exception.CinderException(err_msg)

            #if port deleted by user ,add it
            port_info ={}
            port_info['cHostAlias'] = host_name
            port_info['tPort'] = {}
            port_info['tPort']['ucType'] = 1
            port_info['tPort']['cPortName'] = initiator_name
            port_info['tPort']['sdwMultiPathMode'] = 1
            port_info['tPort']['cMulChapPass'] = ''
            ret = self.server.AddPortToHost({"session": sid}, port_info)
            if (ret[0]['returncode'] != zte_pub.ZTE_SUCCESS and
                    ret[0]['returncode'] != zte_pub.ZTE_ERR_PORT_EXIT  and
                     ret[0]['returncode'] != zte_pub.ZTE_ERR_PORT_EXIT_OLD):
                err_msg = (_LE('_create_group:add port fail.'
                             'port name:%(name)s '
                             'with ret code: %(ret)s'
                             )
                           % {'name': initiator_name,
                               'ret': ret[0]['returncode']})
                LOG.error(err_msg)
                raise exception.CinderException(err_msg)

            host_in_grp = {}
            host_in_grp['ucInitName'] = host_name
            host_in_grp['cMapGrpName'] = map_group_name
            ret = self.server.AddHostToGrp({"session": sid}, host_in_grp)
            if (ret[0]['returncode'] != zte_pub.ZTE_SUCCESS and
                    ret[0]['returncode'] != zte_pub.ZTE_ERR_HOST_EXIT and
                    ret[0]['returncode'] != zte_pub.ZTE_ERR_HOST_EXIT_OLD):
                self._delete_group(map_group_name)
                err_msg = (_LE('_create_group:add host to group fail.'
                             'group name:%(name)s init name :%(init)s '
                             'with ret code: %(ret)s'
                             )
                           % {'name': map_group_name,
                               'init': host_name,
                               'ret': ret[0]['returncode']})
                LOG.error(err_msg)
                raise exception.CinderException(err_msg)
        else:
            err_msg = (_LE('create group fail.'
                         'group name:%(name)s with ret code: %(ret)s'
                         )
                       % {'name': map_group_name,
                          'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)


    def _map_delete_lun(self, lunid, map_group_name):

        # lunid is -1,means lun not exit,no need to delete
        if lunid != -1:
            sid = self._get_sessionid()

            del_vol_from_grp = {}
            del_vol_from_grp['cMapGrpName'] = map_group_name
            del_vol_from_grp['sdwLunId'] = lunid
            ret = self.server.DelVolFromGrp({"session": sid}, del_vol_from_grp)
            if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
                err_msg = (_LE('_map_lun:delete lunid from group fail.'
                           'group name:%(name)s lunid : %(lun)s '
                             'with ret code: %(ret)s'
                             )
                           % {'name': map_group_name,
                              'lun': lunid,
                              'ret': ret[0]['returncode']})
                LOG.error(err_msg)
                raise exception.CinderException(err_msg)

        # if no lun in group,then we will delete this group
        lun_num = self._get_group_lunnum(map_group_name)
        if lun_num == 0:
            self._delete_group(map_group_name)

    def _map_delete_host(self, map_group_name):
        """Delete host from a map.

        Here we give the hostlun ID which starts from 1.
        """

        sid = self._get_sessionid()

        map_grp_info = {'cMapGrpName': map_group_name}
        ret = self.server.GetMapGrpInfo({"session": sid}, map_grp_info)
        if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
            err_msg = (_LE('_map_delete_host:get map group info fail.'
                         'group name:%(name)s with ret code: %(ret)s'
                         )
                       % {'name': map_group_name,
                          'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)

        sdwHostNum = ret[1]['sdwHostNum']

        if sdwHostNum > 0:
            tHostInfo = ret[1]['tHostInfo']
            for index in range(0, int(sdwHostNum)):
                initiator_name = tHostInfo[index]['ucHostName']
                host_in_grp = {}
                host_in_grp['ucInitName'] = initiator_name
                host_in_grp['cMapGrpName'] = map_group_name
                ret = self.server.DelHostFromGrp({"session": sid}, host_in_grp)
                if(ret[0]['returncode'] == zte_pub.ZTE_ERR_GROUP_NOT_EXIT):
                    continue
                if (ret[0]['returncode'] != zte_pub.ZTE_SUCCESS and
                        ret[0]['returncode'] != zte_pub.ZTE_ERR_HOST_NOT_EXIT):
                    err_msg = (_LE('DelHostFromGrp fail:host name:%(name)s with ret code: %(ret)s '
                        )
                        % {'name': initiator_name,
                           'ret': ret[0]['returncode']})
                    LOG.error(err_msg)
                    raise exception.CinderException(err_msg)
                ret = self.server.GetHost({"session": sid}, {"cHostAlias":initiator_name})
                if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
                    err_msg = (_LE('_map_delete_host:get host info fail.'
                                 'host name:%(name)s with ret code: %(ret)s'
                                 )
                               % {'name': initiator_name,
                                  'ret': ret[0]['returncode']})
                    LOG.error(err_msg)
                    raise exception.CinderException(err_msg)
                portnum = ret[1]['sdwPortNum']
                for index in range(0, int(portnum)):
                    port_host_info = {}
                    port_name = ret[1]['tPort'][index]['cPortName']
                    port_host_info['cPortName'] = port_name
                    port_host_info['cHostAlias'] = initiator_name
                    ret = self.server.DelPortFromHost({"session": sid}, port_host_info)
                    if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
                        err_msg = (_LE('_map_delete_host:delete port from host fail.'
                                     'host name:%(name)s ,port name:%(port)s with ret code: %(ret)s'
                                     )
                                   % {'name': initiator_name,
                                      'port': port_name,
                                      'ret': ret[0]['returncode']})
                        LOG.error(err_msg)
                        raise exception.CinderException(err_msg)
                ret = self.server.DelHost({"session": sid}, {"cHostAlias" : initiator_name})
                if (ret[0]['returncode'] != zte_pub.ZTE_SUCCESS and
                        ret[0]['returncode'] != zte_pub.ZTE_ERR_HOSTNAME_NOT_EXIT):
                    err_msg = (_LE('_map_delete_host:delete hostfail.'
                                 'host name:%(name)s with ret code: %(ret)s'
                                 )
                               % {'name': initiator_name,
                                  'ret': ret[0]['returncode']})
                    LOG.error(err_msg)
                    raise exception.CinderException(err_msg)

class ZteFCDriver(ZteApi,driver.FibreChannelDriver):
    """FC driver for ZTE KS series storage arrays."""

    def __init__(self, *args, **kwargs):
        super(ZteFCDriver, self).__init__(*args, **kwargs)

    def execute(*args, **kwargs):
        return utils.execute(*args, **kwargs)


    def _refresh_host_for_connection(self, lunid=-1, wwnn1='', wwnn2=''):
        """Refresh host for connection."""
        LOG.debug('_refresh_host_for_connection. lunid: %(lunid)s.' % {'lunid': lunid})
        if lunid == -1:
            utils.execute('sh', '/etc/cinder/rescanHost.sh', lunid, run_as_root=True)
        else:
            LOG.debug('_refresh_host_for_connection: wwnn1: %(wwnn1)s. '
                    'wwnn2: %(wwnn2)s.'
                  % {'wwnn1': wwnn1,
                     'wwnn2': wwnn2})
            utils.execute('sh', '/etc/cinder/rescanHost.sh', lunid, wwnn1, wwnn2, run_as_root=True)

    def _get_tgt_fc_port_wwpns(self):
        """Get tgt fc port wwpns that is connected."""
        sid = self._get_sessionid()
        tgt_wwpns = []

        ret = self.server.GetFcPortInfo({"session": sid})
        if ret[0]['returncode'] == zte_pub.ZTE_SUCCESS:
            ctrl_num = ret[1]['udwCtrlNum']
            port_info_per_ctrl = ret[1]['tFcPortInfoPerCtrl']

            for ctrl in range(0, int(ctrl_num)):
                port_info = port_info_per_ctrl[ctrl]['tFcPortInfo']
                for portid in range(0, 4):
                    if port_info[portid]['udwLinkStatus'] == 1:
                        wwpn = port_info[portid]['ucWwpn']
                        for num in range(0, 8):  
                            wwpn[num] = '%x' %wwpn[num]
                            if len(wwpn[num]) == 1:
                                wwpn[num] = '0' + wwpn[num]
                        wwpn = ''.join(wwpn)
                        tgt_wwpns.append(wwpn)     
        else:
            err_msg = (_LE('_get_tgt_fc_port_wwpns.'
                         'GetFcPortInfo with ret code: %(ret)s'
                         )
                       % {'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)

        return tgt_wwpns

    @utils.synchronized('locked_initialize_connection')
    def initialize_connection(self, volume, connector):
        """Create FC connection between a volume and a host."""
        fc_wwpns = connector['wwpns']
        volume_name = self._translate_volume_name(volume['name'])

        LOG.debug('initialize_connection: volume name: %(volume)s. '
                    'initiator: %(fc_wwpns)s.'
                  % {'volume': volume_name,
                     'fc_wwpns': fc_wwpns})

        tgt_wwpns = self._get_tgt_fc_port_wwpns()
        if not tgt_wwpns:
            LOG.debug('initialize_connection: _get_tgt_fc_port_wwpns: not tgt_wwpns. ')
            return {'driver_volume_type': 'fibre_channel', 'data': ''}

        map_group_name = self._translate_grp_name(fc_wwpns)

        lunid = self._map_lun(fc_wwpns, volume_name, map_group_name)

        # Refresh host for connection
        # self._refresh_host_for_connection()
        # LOG.info(_("initialize_connection, refreshed"))

        # Return FC properties.
        properties = {}
        properties['target_discovered'] = False
        properties['target_wwn'] = tgt_wwpns
        properties['target_lun'] = lunid
        properties['volume_id'] = volume['id']

        return {'driver_volume_type': 'fibre_channel', 'data': properties}

    def _get_tgt_fc_port_wwnns(self):
        """Get tgt fc port wwpns that is connected."""
        sid = self._get_sessionid()
        tgt_wwnns = []

        ret = self.server.GetFcPortInfo({"session": sid})
        if ret[0]['returncode'] == zte_pub.ZTE_SUCCESS:
            ctrl_num = ret[1]['udwCtrlNum']
            port_info_per_ctrl = ret[1]['tFcPortInfoPerCtrl']

            for ctrl in range(0, int(ctrl_num)):
                wwnn = port_info_per_ctrl[ctrl]['ucWwnn']
                for num in range(0, 8):  
                    wwnn[num] = '%x' %wwnn[num]
                    if len(wwnn[num]) == 1:
                        wwnn[num] = '0' + wwnn[num]
                wwnn = ''.join(wwnn)
                wwnn = '0x' + wwnn
                tgt_wwnns.append(wwnn)     
        else:
            err_msg = (_LE('_get_tgt_fc_port_wwnns.'
                         'GetFcPortInfo with ret code: %(ret)s'
                         )
                       % {'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)

        return tgt_wwnns

    @utils.synchronized('locked_initialize_connection')
    def terminate_connection(self, volume, connector, **kwargs):
        """Delete map between a volume and a host."""
        fc_wwpns = connector['wwpns']
        volume_name = self._translate_volume_name(volume['name'])

        LOG.debug('terminate_connection:volume name: %(volume)s, '
                    'initiator: %(fc_wwpns)s.'
                  % {'volume': volume_name,
                     'fc_wwpns': fc_wwpns})

        map_group_name = self._translate_grp_name(fc_wwpns)
        lunid = self._getLunidFromVol(volume_name, map_group_name)
        self._map_delete_lun(lunid, map_group_name)
        
        tgt_wwnns = []
        tgt_wwnns = self._get_tgt_fc_port_wwnns()       
        
        #if len(tgt_wwnns) == 2:
        #    self._refresh_host_for_connection(lunid, tgt_wwnns[0], tgt_wwnns[1])
        #    LOG.info(_LI("terminate_connection, refreshed"))
        #elif len(tgt_wwnns) == 1:
        #    self._refresh_host_for_connection(lunid, tgt_wwnns[0], tgt_wwnns[0])
        #    LOG.info(_LI("terminate_connection, refreshed only one wwnn"))
        #else:
        #    LOG.debug('terminate_connection: _get_tgt_fc_port_wwnns: not tgt_wwnns. ')

    def _get_allocation_conf(self):
        """get vol_allocation conf"""

        root = self._read_xml()
        vol_allocation = root.findtext('VOLUME/Volume_Allocation_Ratio')
        if not vol_allocation:
            vol_allocation = zte_pub.ZTE_VOLUME_ALLOCATION_RATIO

        return vol_allocation

    def _translate_grp_name(self, grp_name):
        """Form new names because of the 32-character limit on names."""
        grp_name.sort()
        new_name = zte_pub.ZTE_HOST_GROUP_NAME_PREFIX + str(hash(grp_name[0]))
        new_name = new_name.replace('-', 'R')

        LOG.debug('_translate_grp_name:Name in cinder: %(old)s, '
                    'new name in storage system: %(new)s'
                  % {'old': grp_name[0],
                     'new': new_name})

        return new_name

    def _translate_volume_name(self, vol_name):
        """Form new names because of the 32-character limit on names."""
        new_name = zte_pub.ZTE_VOL_AND_SNAP_NAME_PREFIX + str(hash(vol_name))
        new_name = new_name.replace('-', 'R')

        LOG.debug('_translate_volume_name:Name in cinder: %(old)s, '
                    'new name in storage system: %(new)s'
                  % {'old': vol_name,
                     'new': new_name})

        return new_name

    def _getLunid(self, volume_name, map_group_name):
        global g_getLunID

        while (g_getLunID >0):
            time.sleep(0.5)
            
        g_getLunID += 1
        """if no lunid,generate one lunid"""

        sid = self._get_sessionid()

        lunid = -1

        map_grp_info = {'cMapGrpName': map_group_name}
        ret = self.server.GetMapGrpInfo({"session": sid}, map_grp_info)

        if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
            g_getLunID -= 1
            return -1

        lun_num = ret[1]['sdwLunNum']
        lun_info = ret[1]['tLunInfo']
        if int(lun_num) == 0:
            g_getLunID -= 1
            return 1

        lun_list = []
        for count in range(0, int(lun_num)):
            if volume_name == lun_info[count]['cVolName']:
                lunid = lun_info[count]['sdwLunId']
                g_getLunID -= 1
                return lunid
            lun_list.append(lun_info[count]['sdwLunId'])

        for i in range(1, zte_pub.ZTE_GROUP_MAX_LUN-1):
            if i not in lun_list:
                lunid = int(i)
                g_getLunID -= 1
                return lunid

        # don't find a valid lunid
        g_getLunID -= 1
        return -1

    def _create_group(self, initiator_name, map_group_name):
        """ """
        sid = self._get_sessionid()

        map_grp_info = {'cMapGrpName': map_group_name}
        ret = self.server.CreateMapGrp({"session": sid}, map_grp_info)
        if (ret[0]['returncode'] == zte_pub.ZTE_SUCCESS or
                ret[0]['returncode'] == zte_pub.ZTE_ERR_GROUP_EXIT):
            host_in_grp = {}
            host_in_grp['cMapGrpName'] = map_group_name

            for wwpn in initiator_name:
                wwpn = str(wwpn)
                wwpn = wwpn[0:2] + ':' + wwpn[2:4] + ':' + wwpn[4:6] + ':' + wwpn[6:8] + ':' + wwpn[8:10] + ':' + wwpn[10:12] + ':' + wwpn[12:14] + ':' + wwpn[14:16]
                host_info = {}
                host_info['tHost'] = {}
                host_name = self._translate_host_name(wwpn)
                host_info['tHost']['cHostAlias'] = host_name
                host_info['tHost']['ucOs'] = 1
                host_info['tPort'] = {}
                host_info['tPort']['ucType'] = 2
                host_info['tPort']['cPortName'] = wwpn
                host_info['tPort']['sdwMultiPathMode'] = 1
                host_info['tPort']['cMulChapPass'] = ''
                
                ''' create host '''
                ret = self.server.CreateHost({"session": sid}, host_info)
                if (ret[0]['returncode'] != zte_pub.ZTE_SUCCESS and 
                        ret[0]['returncode'] != zte_pub.ZTE_ERR_HOSTNAME_EXIT and
                     ret[0]['returncode'] != zte_pub.ZTE_ERR_PORT_EXIT and
                     ret[0]['returncode'] != zte_pub.ZTE_ERR_PORT_EXIT_OLD):
                    err_msg = (_LE('_create_group:create host fail.'
                                 'host name:%(name)s '
                                 'with ret code: %(ret)s'
                                 )
                               % {'name': host_name,
                                   'ret': ret[0]['returncode']})
                    LOG.error(err_msg)
                    raise exception.CinderException(err_msg)
                #if port deleted by user ,add it
                port_info ={}
                port_info['cHostAlias'] = host_name
                port_info['tPort'] = {}
                port_info['tPort']['ucType'] = 2
                port_info['tPort']['cPortName'] = wwpn
                port_info['tPort']['sdwMultiPathMode'] = 1
                port_info['tPort']['cMulChapPass'] = ''
                ret = self.server.AddPortToHost({"session": sid}, port_info)
                if (ret[0]['returncode'] != zte_pub.ZTE_SUCCESS and
                        ret[0]['returncode'] != zte_pub.ZTE_ERR_PORT_EXIT  and
                     ret[0]['returncode'] != zte_pub.ZTE_ERR_PORT_EXIT_OLD):
                    err_msg = (_LE('_create_group:add host fail.'
                                 'port name:%(name)s '
                                 'with ret code: %(ret)s'
                                 )
                               % {'name': initiator_name,
                                   'ret': ret[0]['returncode']})
                    LOG.error(err_msg)
                    raise exception.CinderException(err_msg)

                host_in_grp['ucInitName'] = host_name
                ret = self.server.AddHostToGrp({"session": sid}, host_in_grp)

                if (ret[0]['returncode'] != zte_pub.ZTE_SUCCESS and
                     ret[0]['returncode'] != zte_pub.ZTE_ERR_HOST_EXIT and
                    ret[0]['returncode'] != zte_pub.ZTE_ERR_HOST_EXIT_OLD):
                    self._delete_group(map_group_name)
                    err_msg = (_LE('_create_group:add host to group fail.'
                                 'group name:%(name)s init name :%(init)s '
                                 'with ret code: %(ret)s'
                                 )
                               % {'name': map_group_name,
                                   'init': host_name,
                                   'ret': ret[0]['returncode']})
                    LOG.error(err_msg)
                    raise exception.CinderException(err_msg)
        else:
            err_msg = (_LE('create group fail.'
                         'group name:%(name)s with ret code: %(ret)s'
                         )
                       % {'name': map_group_name,
                          'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)

    def _map_delete_lun(self, lunid, map_group_name):

        # lunid is -1,means lun not exit,no need to delete
        if lunid != -1:
            sid = self._get_sessionid()

            del_vol_from_grp = {}
            del_vol_from_grp['cMapGrpName'] = map_group_name
            del_vol_from_grp['sdwLunId'] = lunid
            ret = self.server.DelVolFromGrp({"session": sid}, del_vol_from_grp)
            if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
                err_msg = (_LE('_map_lun:delete lunid from group fail.'
                           'group name:%(name)s lunid : %(lun)s '
                             'with ret code: %(ret)s'
                             )
                           % {'name': map_group_name,
                              'lun': lunid,
                              'ret': ret[0]['returncode']})
                LOG.error(err_msg)
                raise exception.CinderException(err_msg)

        # if no lun in group,then we will delete this group
        lun_num = self._get_group_lunnum(map_group_name)
        if lun_num == 0:
            self._delete_group(map_group_name)

    def _map_delete_host(self, map_group_name):
        """Delete host from a map.

        Here we give the hostlun ID which starts from 1.
        """

        sid = self._get_sessionid()

        map_grp_info = {'cMapGrpName': map_group_name}
        ret = self.server.GetMapGrpInfo({"session": sid}, map_grp_info)
        if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
            err_msg = (_LE('_map_lun:get map group info fail.'
                         'group name:%(name)s with ret code: %(ret)s'
                         )
                       % {'name': map_group_name,
                          'ret': ret[0]['returncode']})
            LOG.error(err_msg)
            raise exception.CinderException(err_msg)

        sdwHostNum = ret[1]['sdwHostNum']

        if sdwHostNum > 0:
            tHostInfo = ret[1]['tHostInfo']
            for index in range(0, int(sdwHostNum)):
                initiator_name = tHostInfo[index]['ucHostName']
                host_in_grp = {}
                host_in_grp['ucInitName'] = initiator_name
                host_in_grp['cMapGrpName'] = map_group_name
                ret = self.server.DelHostFromGrp({"session": sid}, host_in_grp)
                if(ret[0]['returncode'] == zte_pub.ZTE_ERR_GROUP_NOT_EXIT):
                    continue
                if (ret[0]['returncode'] != zte_pub.ZTE_SUCCESS and
                        ret[0]['returncode'] != zte_pub.ZTE_ERR_HOST_NOT_EXIT):
                    err_msg = (_LE('DelHostFromGrp fail:host name:%(name)s with ret code: %(ret)s '
                        )
                        % {'name': initiator_name,
                           'ret': ret[0]['returncode']})
                    LOG.error(err_msg)
                    raise exception.CinderException(err_msg)
                ret = self.server.GetHost({"session": sid}, {"cHostAlias":initiator_name})
                if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
                    err_msg = (_LE('_map_delete_host:get host info fail.'
                                 'host name:%(name)s with ret code: %(ret)s'
                                 )
                               % {'name': initiator_name,
                                  'ret': ret[0]['returncode']})
                    LOG.error(err_msg)
                    raise exception.CinderException(err_msg)
                port_host_info = {}
                port_host_info['cHostAlias'] = initiator_name
                tPortInfo = ret[1]['tPort']
                sdwPortNum = ret[1]['sdwPortNum']
                for item in range(0, int(sdwPortNum)):
                    port_name = tPortInfo[item]['cPortName']
                    port_host_info['cPortName'] = port_name
                    ret = self.server.DelPortFromHost({"session": sid}, port_host_info)
                    if ret[0]['returncode'] != zte_pub.ZTE_SUCCESS:
                        err_msg = (_LE('_map_delete_host:delete port from host fail.'
                                 'host name:%(name)s ,port name:%(port)s with ret code: %(ret)s'
                                 )
                               % {'name': initiator_name,
                                  'port': port_name,
                                  'ret': ret[0]['returncode']})
                        LOG.error(err_msg)
                        raise exception.CinderException(err_msg)
                ret = self.server.DelHost({"session": sid}, {"cHostAlias" : initiator_name})
                if (ret[0]['returncode'] != zte_pub.ZTE_SUCCESS and
                        ret[0]['returncode'] != zte_pub.ZTE_ERR_HOSTNAME_NOT_EXIT):
                    err_msg = (_LE('_map_delete_host:delete hostfail.'
                                 'host name:%(name)s with ret code: %(ret)s'
                                 )
                               % {'name': initiator_name,
                                  'ret': ret[0]['returncode']})
                    LOG.error(err_msg)
                    raise exception.CinderException(err_msg)
        
