<?php 
	function makeInputParams($method,$sessionID,$json_params){
		$xmlrpc_params = array(new xmlrpcval(array("session"=>new xmlrpcval($sessionID,"string")),"struct"));
		switch ($method) {
			case 'plat.session.signin':
				$xmlrpc_params[] = new xmlrpcval($json_params["UserName"]);
				$xmlrpc_params[] = new xmlrpcval($json_params["UserPassword"]);
				$xmlrpc_params[] = new xmlrpcval($json_params["LocalIP"]);
				$xmlrpc_params[] = new xmlrpcval($json_params["LoginType"],"int");
				break;
			case 'plat.session.heartbeat':
			case 'GetSystemNetCfg':
			case 'GetSysInfo':
			case 'GetIscsiTargetName':
			
				break;
			case 'GetVdInfo':
				$xmlrpc_params[] = new xmlrpcval(array(
					"cVdName"=>new xmlrpcval($json_params["cVdName"])
					),"struct");
				break;
			case 'GetPoolInfo':
				$xmlrpc_params[] = new xmlrpcval(array(
					"scPoolName"=>new xmlrpcval($json_params["scPoolName"])
					),"struct");
				break;
				
			case 'GetVolNamesOnVd':
				$xmlrpc_params[] = new xmlrpcval(array(
					"cVdName"=>new xmlrpcval($json_params["cVdName"])
					),"struct");
				break;
			case 'GetCvolNamesOnVol':
				$xmlrpc_params[] = new xmlrpcval(array(
					"scVolName"=>new xmlrpcval($json_params["scVolName"])
					),"struct");
				break;
			case 'GetMapGrpInfo':
				$xmlrpc_params[] = new xmlrpcval(array(
					"cMapGrpName"=>new xmlrpcval($json_params["cMapGrpName"])
					),"struct");
				break;
			case 'GetGrpSimpleInfoList':
				$xmlrpc_params[] = new xmlrpcval(array(
					"cMapGrpName"=>new xmlrpcval($json_params["cMapGrpName"])
					),"struct");
				break;
			case 'CreateVol':
				$xmlrpc_params[] = new xmlrpcval(array(
					"cVdName"=>new xmlrpcval($json_params["cVdName"]),
					"cVolName"=>new xmlrpcval($json_params["cVolName"]),
					"sdwChunkSize"=>new xmlrpcval($json_params["sdwChunkSize"],"int"),
					"sqwCapacity"=>new xmlrpcval($json_params["sqwCapacity"],"i8"),
					"sdwCtlPrefer"=>new xmlrpcval($json_params["sdwCtlPrefer"],"int"),
					"sdwCachePolicy"=>new xmlrpcval($json_params["sdwCachePolicy"],"int"),
					"sdwAheadReadSize"=>new xmlrpcval($json_params["sdwAheadReadSize"],"int"),
					"dwSSDCacheSwitch"=>new xmlrpcval($json_params["dwSSDCacheSwitch"],"int")
					),"struct");
				break;	
			case 'ExpandVol':
				$xmlrpc_params[] = new xmlrpcval(array(
					"cVolName"=>new xmlrpcval($json_params["cVolName"]),
					"sqwExpandSize"=>new xmlrpcval($json_params["sqwExpandSize"],"i8")
					),"struct");
				break;	
			case 'ExpandVolOnPool':
				$xmlrpc_params[] = new xmlrpcval(array(
					"scVolName"=>new xmlrpcval($json_params["scVolName"]),
					"qwExpandCapacity"=>new xmlrpcval($json_params["qwExpandCapacity"],"i8")
					),"struct");
				break;	
			case 'DelVol':
				$xmlrpc_params[] = new xmlrpcval(array(
					"cVolName"=>new xmlrpcval($json_params["cVolName"])
					),"struct");
				break;	
			case 'DelCvol':
				$xmlrpc_params[] = new xmlrpcval(array(
					"scCvolName"=>new xmlrpcval($json_params["scCvolName"])
					),"struct");
				break;	
			case 'DelSvol':
				$xmlrpc_params[] = new xmlrpcval(array(
					"scSnapName"=>new xmlrpcval($json_params["scSnapName"])
					),"struct");
				break;
			case 'DelMapGrp':
				$xmlrpc_params[] = new xmlrpcval(array(
					"cMapGrpName"=>new xmlrpcval($json_params["cMapGrpName"])
					),"struct");
				break;
			case 'GetHost':
				$xmlrpc_params[] = new xmlrpcval(array(
					"cHostAlias"=>new xmlrpcval($json_params["cHostAlias"])
					),"struct");
				break;
			case 'CreateMapGrp':
				$xmlrpc_params[] = new xmlrpcval(array(
					"cMapGrpName"=>new xmlrpcval($json_params["cMapGrpName"])
					),"struct");
				break;
			case 'CreateCvol':
				$xmlrpc_params[] = new xmlrpcval(array(
					"scCvolName"=>new xmlrpcval($json_params["scCvolName"],"string"),
					"scBvolName"=>new xmlrpcval($json_params["scBvolName"]),
					"scTargetName"=>new xmlrpcval($json_params["scTargetName"]),
					"sdwInitSync"=>new xmlrpcval($json_params["sdwInitSync"],"int"),
					"sdwProtectRestore"=>new xmlrpcval($json_params["sdwProtectRestore"],"int"),
					"sdwPri"=>new xmlrpcval($json_params["sdwPri"],"int"),
					"sdwPolicy"=>new xmlrpcval($json_params["sdwPolicy"],"int"),
					"sdwBvolType"=>new xmlrpcval($json_params["sdwBvolType"],"int")
					),"struct");
				break;		
			case 'CreateSvol':
				$xmlrpc_params[] = new xmlrpcval(array(
					"scVolName"=>new xmlrpcval($json_params["scVolName"],"string"),
					"scSnapName"=>new xmlrpcval($json_params["scSnapName"]),
					"sdwSnapType"=>new xmlrpcval($json_params["sdwSnapType"],"int"),
					"swRepoSpaceAlarm"=>new xmlrpcval($json_params["swRepoSpaceAlarm"],"int"),
					"swRepoOverflowPolicy"=>new xmlrpcval($json_params["swRepoOverflowPolicy"],"int"),
					"sqwRepoCapacity"=>new xmlrpcval($json_params["sqwRepoCapacity"],"i8"),
					"ucIsAgent"=>new xmlrpcval($json_params["ucIsAgent"],"int"),
					"ucSnapMode"=>new xmlrpcval($json_params["ucSnapMode"],"int"),
					"is_private"=>new xmlrpcval($json_params["is_private"],"int"),
					"ucIsAuto"=>new xmlrpcval($json_params["ucIsAuto"],"int")
					),"struct");
				break;		
				
			case 'CreateVolOnPool':
				$xmlrpc_params[] = new xmlrpcval(array(
					"scPoolName"=>new xmlrpcval($json_params["scPoolName"],"string"),
					"scVolName"=>new xmlrpcval($json_params["scVolName"],"string"),
					"sdwStripeDepth"=>new xmlrpcval($json_params["sdwStripeDepth"],"int"),
					"qwCapacity"=>new xmlrpcval($json_params["qwCapacity"],"i8"),
					"sdwCtrlPrefer"=>new xmlrpcval($json_params["sdwCtrlPrefer"],"int"),
					"sdwCachePolicy"=>new xmlrpcval($json_params["sdwCachePolicy"],"int"),
					"sdwAheadReadSize"=>new xmlrpcval($json_params["sdwAheadReadSize"],"int"),
					"sdwAllocPolicy"=>new xmlrpcval($json_params["sdwAllocPolicy"],"int"),
					"sdwMovePolicy"=>new xmlrpcval($json_params["sdwMovePolicy"],"int"),
					"udwIsThinVol"=>new xmlrpcval($json_params["udwIsThinVol"],"int"),
					"uqwInitAllocedCapacity"=>new xmlrpcval($json_params["uqwInitAllocedCapacity"],"i8"),
					"sdwAlarmThreshold"=>new xmlrpcval($json_params["sdwAlarmThreshold"],"int"),
					"sdwAlarmStopAllocFlag"=>new xmlrpcval($json_params["sdwAlarmStopAllocFlag"],"int"),
					"dwSSDCacheSwitch"=>new xmlrpcval($json_params["dwSSDCacheSwitch"],"int")
					),"struct");
				break;
			case 'AddVolToGrp':
				$xmlrpc_params[] = new xmlrpcval(array(
					"cMapGrpName"=>new xmlrpcval($json_params["cMapGrpName"],"string"),
					"tLunInfo"=>new xmlrpcval(array("sdwLunId"=>new xmlrpcval($json_params["sdwLunId"],"int"),
						"cVolName"=>new xmlrpcval($json_params["cVolName"])),"struct")
					),"struct");
				break;	
			case 'CreateHost':
				$xmlrpc_params[] = new xmlrpcval(array(
					"tHost"=>new xmlrpcval(array(
						"cHostAlias"=>new xmlrpcval($json_params["cHostAlias"],"string"),
						"ucOs"=>new xmlrpcval($json_params["ucOs"],"int")),"struct"),
					"tPort"=>new xmlrpcval(array(
						"ucType"=>new xmlrpcval($json_params["ucType"],"int"),
						"cPortName"=>new xmlrpcval($json_params["cPortName"]),
						"sdwMultiPathMode"=>new xmlrpcval($json_params["sdwMultiPathMode"],"int"),
						"cMulChapPass"=>new xmlrpcval($json_params["cMulChapPass"])),"struct")
					),"struct");
				break;		
			case 'AddPortToHost':
				$xmlrpc_params[] = new xmlrpcval(array(
					"cHostAlias"=>new xmlrpcval($json_params["cHostAlias"],"string"),
					"tPort"=>new xmlrpcval(array(
						"ucType"=>new xmlrpcval($json_params["ucType"],"int"),
						"cPortName"=>new xmlrpcval($json_params["cPortName"]),
						"sdwMultiPathMode"=>new xmlrpcval($json_params["sdwMultiPathMode"],"int"),
						"cMulChapPass"=>new xmlrpcval($json_params["cMulChapPass"])),"struct")
					),"struct");
				break;	
			case 'AddHostToGrp':
				$xmlrpc_params[] = new xmlrpcval(array(
					"ucInitName"=>new xmlrpcval($json_params["ucInitName"]),
					"cMapGrpName"=>new xmlrpcval($json_params["cMapGrpName"])
					),"struct");
				break;
			case 'DelVolFromGrp':
				$xmlrpc_params[] = new xmlrpcval(array(
					"cMapGrpName"=>new xmlrpcval($json_params["cMapGrpName"]),
					"sdwLunId"=>new xmlrpcval($json_params["sdwLunId"],"int")
					),"struct");
				break;
			case 'DelHostFromGrp':
				$xmlrpc_params[] = new xmlrpcval(array(
					"ucInitName"=>new xmlrpcval($json_params["ucInitName"]),
					"cMapGrpName"=>new xmlrpcval($json_params["cMapGrpName"])
					),"struct");
				break;
			case 'DelPortFromHost':
				$xmlrpc_params[] = new xmlrpcval(array(
					"cPortName"=>new xmlrpcval($json_params["cPortName"]),
					"cHostAlias"=>new xmlrpcval($json_params["cHostAlias"])
					),"struct");
				break;
			case 'DelHost':
				$xmlrpc_params[] = new xmlrpcval(array(
					"cHostAlias"=>new xmlrpcval($json_params["cHostAlias"])
					),"struct");
				break;
			default:
				# code...
				break;
		}
		return $xmlrpc_params;
	}
	function makeOutputParams($method,$return_arr_value){
		$data = array();
		//var_dump($return_arr_value);
		switch ($method) {
			case 'plat.session.signin':
				$data["sessionID"] = $return_arr_value[0]["session"];
				break;
			case 'GetSysInfo':
				$data["cVendor"] = $return_arr_value[1]["cVendor"];
				$data["cVersionName"] = $return_arr_value[1]["cVersionName"];
				break;
			case 'GetVdInfo':
				$data["sdwState"] = $return_arr_value[1]["sdwState"];
				$data["sqwTotalCapacity"] = $return_arr_value[1]["sqwTotalCapacity"];
				$data["sqwFreeCapacity"] = $return_arr_value[1]["sqwFreeCapacity"];
				break;
			case 'GetPoolInfo':
				$data["sdwState"] = $return_arr_value[1]["sdwState"];
				$data["qwTotalCapacity"] = $return_arr_value[1]["qwTotalCapacity"];
				$data["qwFreeCapacity"] = $return_arr_value[1]["qwFreeCapacity"];
				break;
			case 'GetVolNamesOnVd':
				$data["sdwVolNum"] = $return_arr_value[1]["sdwVolNum"];
				break;
			case 'GetCvolNamesOnVol':
				$data["sdwCvolNum"] = $return_arr_value[1]["sdwCvolNum"];
				$data["scCvolNames"] = array();
				for($i=0;$i<$return_arr_value[1]["sdwCvolNum"];$i++){
					$data["scCvolNames"][$i] = array("scCvolName"=>$return_arr_value[1]['scCvolNames'][$i]);
				}
				break;
			case 'GetMapGrpInfo':
				$data["sdwHostNum"] = $return_arr_value[1]["sdwHostNum"];
				$data["tHostInfo"] = array();
				for($i=0;$i<$return_arr_value[1]["sdwHostNum"];$i++){
					$data["tHostInfo"][$i] = array(
						"ucHostName"=>$return_arr_value[1]['tHostInfo'][$i]['ucHostName']
						);
				}
				$data["sdwLunNum"] = $return_arr_value[1]["sdwLunNum"];
				$data["tLunInfo"] = array();
				for($i=0;$i<$return_arr_value[1]["sdwLunNum"];$i++){
					$data["tLunInfo"][$i] = array(
						"cVolName"=>$return_arr_value[1]['tLunInfo'][$i]['cVolName'],
						"sdwLunId"=>$return_arr_value[1]['tLunInfo'][$i]['sdwLunId']
						);
				}
				break;
			case 'GetGrpSimpleInfoList':
				$data["sdwMapGrpNum"] = $return_arr_value[1]["sdwMapGrpNum"];
				$data["tMapGrpSimpleInfo"] = array();
				for($i=0;$i<$return_arr_value[1]["sdwMapGrpNum"];$i++){
					$data["tMapGrpSimpleInfo"][$i] = array("cMapGrpName"=>$return_arr_value[1]['tMapGrpSimpleInfo'][$i]['cMapGrpName']);
				}
				break;
			case 'GetSystemNetCfg':
				$data["sdwDeviceNum"] = $return_arr_value[1]["sdwDeviceNum"];
				$data["tSystemNetCfg"] = array();
				for($i=0;$i<$return_arr_value[1]["sdwDeviceNum"];$i++){
					$data["tSystemNetCfg"][$i] = array(
						"udwRoleType"=>$return_arr_value[1]['tSystemNetCfg'][$i]['udwRoleType'],
						"cIpAddr"=>$return_arr_value[1]['tSystemNetCfg'][$i]['cIpAddr'],
						"udwCtrlId"=>$return_arr_value[1]['tSystemNetCfg'][$i]['udwCtrlId']
						);
				}
				break;
			case 'GetIscsiTargetName':
				$data["udwCtrlCount"] = $return_arr_value[1]["udwCtrlCount"];
				$data["tIscsiTargetInfo"] = array();
				for($i=0;$i<$return_arr_value[1]["udwCtrlCount"];$i++){
					$data["tIscsiTargetInfo"][$i] = array(
						"udwCtrlId"=>$return_arr_value[1]['tIscsiTargetInfo'][$i]['udwCtrlId'],
						"cTgtName"=>$return_arr_value[1]['tIscsiTargetInfo'][$i]['cTgtName']
						);
				}
				break;
			case 'GetHost':
				$data["sdwPortNum"] = $return_arr_value[1]["sdwPortNum"];
				$data["tPort"] = array();
				for($i=0;$i<$return_arr_value[1]["sdwPortNum"];$i++){
					$data["tPort"][$i] = array(
						"cPortName"=>$return_arr_value[1]['tPort'][$i]['cPortName']
						);
				}
				break;
			case 'AddVolToGrp':
				$data["sdwLunId"] = $return_arr_value[1]["tLunInfo"]["sdwLunId"];
				break;
			/*
			case 'plat.session.heartbeat':
			case 'CreateVol':
			case 'CreateSvol':
			case 'CreateCvol':
			case 'ExpandVol':
			case 'ExpandVolOnPool':
			case 'DelVol':
			case 'DelCvol':
			case 'DelSvol':
			case 'CreateVolOnPool':
			case 'DelMapGrp':
			case 'AddVolToGrp':
			case 'CreateMapGrp':
			case 'CreateHost':
			case 'AddPortToHost':
			case 'AddHostToGrp':
			case 'DelVolFromGrp':
			case 'DelHostFromGrp':
			case 'DelPortFromHost':
			case 'DelHost':
				$data = (object)array();
				break;
			*/
			default:
				$data = (object)array();
				break;
		}
		$output = array("returncode"=>$return_arr_value[0]["returncode"],"data"=>$data);
		$output_params = json_encode($output);
		return $output_params;
	}
?>