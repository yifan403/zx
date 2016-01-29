/*********************************************************************
* 版权所有 (C)2010, 深圳市中兴通讯股份有限公司。
*
* 文件名称： usp_capi.h
* 文件标识： 见配置管理计划书
* 内容摘要： USP项目结构体定义 & 接口声明
* 其它说明： 无
* 当前版本： 0.1
* 作    者： tao.linjun@zte.com.cn
* 完成日期： 2010-11-2
**********************************************************************/

#ifndef __USP_CAPI_LIB_H__
#define __USP_CAPI_LIB_H__

#include "usp_common_macro.h"
#include "usp_common_typedef.h"
#include "usp_capi_oam.h"

typedef struct
{
    SWORD32 sdwSvrPort;                 /*存储设备监听的端口号*/
    CHAR    ucSvrIpAddr[MAX_IP_LEN];    /*存储设备IP   地址*/
} _PACKED_1_ T_SvrSocket;

typedef struct
{
    SWORD32 sdwYear;
    SWORD32 sdwMon;
    SWORD32 sdwDay;
    SWORD32 sdwHour;
    SWORD32 sdwMin;
    SWORD32 sdwSec;
} _PACKED_1_ T_ScsTime;

typedef struct
{
    T_ScsTime tTime;           //计划任务第一次运行任务,如果sdwSchedPeriod为“SCHED_IMMEDIATELY”，该时间不需指定
    SWORD32  sdwSchedPeriod; //计划任务的周期，取值SCHED_IMMEDIATELY、SCHED_ONCE、SCHED_DAYLY、SCHED_WEEKLY、SCHED_MONTHLY
} _PACKED_1_ T_Schedule;

/********************************* Time ***********************************/

typedef struct
{
    CHAR   ServerIp[NTP_HOST_NAME_LEN];  /* NTP服务器地址, 查询出参，设置入参 */
    BYTE   ucNtpVersion;                 /* NTP版本号，范围1~3，查询出参，设置入参 */
    WORD32 dwSynInterval;                /* NTP同步间隔(s), 范围 5~600, 查询出参，设置入参 */
} _PACKED_1_ T_NtpInfo;

typedef struct
{
    BYTE sdwNtpStatus;                   /* NTP开关，0为关闭，1为打开，查询出参，设置入参 */
} _PACKED_1_ T_NtpSwitch;

typedef struct
{
    SWORD16  swTimeZone;                 /* 取值范围【-12，13】*/
} _PACKED_1_ T_TimeZoneInfo;

/*
 * 将结构体字段修改为SWORD类型, 在设置时间时, 如果只设置date, 则将hour、minute和second初始化为-1;
 * 如果只设置time, 则将year、month和day初始化为-1
*/
typedef struct
{
    SWORD32 dwTmYear;    /* 年 ,公元纪年,比如2011*/
    SWORD32 dwTmMon;     /* 月 ,实际月份*/
    SWORD32 dwTmDay;     /* 日 */
    SWORD32 dwTmHour;    /* 时 */
    SWORD32 dwTmMin;      /* 分 */
    SWORD32 dwTmSec;      /* 秒 */
} _PACKED_1_ T_SysTime;   /* 系统时间 */

typedef struct
{
    T_SysTime   tSysTime;
} _PACKED_1_ T_TimeInfo;

/******************************** SIC *****************************************/

/* 压缩包信息 */
typedef struct
{
    T_ScsTime tCreatTime;    /* 出参：压缩包创建的时间 */
    CHAR scTarBallName[MAX_SIC_FILE_NAME_LEN];    /* 出参：压缩包名字 */
} _PACKED_1_ T_TarBallInfo;

/* 每个控制器上压缩包信息 */
typedef struct
{
    SWORD32 sdwCtrlId;    /* 压缩包所在的控制器ID */
    T_TarBallInfo tTarBallInfo;
} _PACKED_1_ T_TarBallInfoPerCtrl;

/* 系统中所有控制器上的压缩包信息 */
typedef struct
{
    WORD32 dwCtrlNum;    /* 系统中控制器的数量 */
    T_TarBallInfoPerCtrl tTarBallInfoPerCtrl[MAX_CTL_NUM];    /* 压缩包信息列表 */
} _PACKED_1_ T_TarBallInfoList;

typedef struct
{
    SWORD32 sdwCtlId;  /* 入参：取值参考T_CtrlAction结构体 */
} _PACKED_1_ T_SicCtrlAction;

typedef struct
{
    CHAR    ucFileName[MAX_CONFIG_FILE_NAME_LEN]; /* 仅文件名，不包括路径 */
    SWORD32 sdwCtrlId;
} _PACKED_1_ T_SysInfoTarBall;

/***************************************DM*************************************/
typedef struct
{
    SWORD32  sdwSlotId;      /* 磁盘槽位号，取值0~27(ScanBox);  0~11(SPR10) */
    SWORD32  sdwEnclosureId;  /* 箱体Id，取值 0~实际箱体数*/
} _PACKED_1_ T_PdId;

typedef struct
{
    SWORD32  sdwNum;     /* 磁盘个数，取值MAX_ENC_NUM_IN_SYS(4) * MAX_PD_NUM_IN_ENC(16) */
    T_PdId       tPdId[MAX_PD_NUM_IN_SYS];
} _PACKED_1_ T_AllPdId;

typedef struct
{
    SWORD32  sdwSlotId;     /* 磁盘槽位号，取值0~27(ScanBox);  0~11(SPR10) */
    SWORD32  sdwEnclosureId;/* 硬盘所在的柜子id */
    SWORD32  sdwCache;      /* 硬盘cache状态 1 – 使能, 0 – 禁止, -1 –不支持 */
    SWORD32  sdwPowerSave;  /* 硬盘节能模式状态1 – 使能,0 – 禁止,-1 –不支持 */
    SWORD32  sdwSpeed;      /* 硬盘工作速率设置。-1 不支持 */
} _PACKED_1_ T_PdSetHwInfo;

typedef struct
{
    SWORD32  sdwSlotId;                           /* 磁盘槽位号，取值0~27(ScanBox);  0~11(SPR10) */
    SWORD32  sdwEnclosureId;                      /* 箱体Id，取值 0~实际箱体数*/
    SWORD64  sqwCapacity;                         /* 磁盘容量 */
    SWORD32  sdwCache;                            /* 硬盘cache状态 1 – 使能, 0 – 禁止, -1 –不支持 */
    SWORD32  sdwPowerSave;                        /* 打开，关闭，不支持 *//* 硬盘节能模式SCS_DM_DISK_POWER_ACTIVE  SCS_DM_DISK_POWER_IDLE SCS_DM_DISK_POWER_STANDBY SCS_DM_DISK_POWER_STOP_SLEEP*/
    SWORD32  sdwSpeed;                            /* 硬盘工作速率设置。-1 不支持 */
    CHAR     ucModelName[MAX_PD_MODEL_NAME_LEN];  /* model名称 */
    CHAR     ucPhysicalType[MAX_PD_PHY_TYPE_LEN]; /* 硬盘物理类型 */
    CHAR     ucFwVer[MAX_PD_FW_VER_LEN];          /* Firmware版本.*/
    CHAR     ucSerialNo[MAX_PD_SNO_LEN];          /* 序列号 */
    CHAR     ucStdVerNum[MAX_PD_STD_VER_LEN];     /* 标准版本号. */
    SWORD32  sdwHealthState;                      /* 磁盘的健康状态，包含可访问性和SMART 状态，取值为PD_GOOD(1)、PD_BROKEN(0)*/
    SWORD32  sdwSourceType;                       /* ePdSrc   eSrc;取值PD_LOCAL(0), PD_FOREIGN(2)*/
    SWORD32  sdwLogicType;                        /* ePdType  eType;取值PD_UNKOWN(3),PD_UNUSED(0),PD_HOTSPARE(4), PD_DATA(5)、PD_CONFLICT(6)*/
    SWORD32  ucObjectType;                        /* 磁盘所属类型，TYPE_VD 表示 vd，TYPE_POOL 表示 pool */
    CHAR     cVdName[MAX_BLK_NAME_LEN];           /* 虚拟盘名称 */
    SWORD32  sdwVisibleCtrl;                      /* 对该盘可见的控制器及状态 */
    CHAR     ucInterfaceType[MAX_PD_TYPE_LEN];    /* 磁盘接口类型*/
    WORD32   dwRotationRate;                      /* 磁盘转速 0-固态硬盘 其他-转速,单位:RPM(转每分钟) */
} _PACKED_1_ T_HddInfo;

typedef struct
{
    SWORD32 sdwPdEnclosureId;  /* 箱体Id */
    SWORD32 sdwPdSlotId;       /* 磁盘槽位号，取值0~27(ScanBox);  0~11(SPR10) */
    WORD32 dwFinishRate;       /* 磁盘扫描完成情况-1--100 */
    WORD32 dwBblNum;           /* 磁盘扫描坏块数目 */

} _PACKED_1_ T_PdScanStatus;

typedef struct
{
    SWORD32  sdwSlotId;           /* 磁盘槽位号，取值0~27(ScanBox);  0~11(SPR10) */
    SWORD32  sdwEnclosureId;      /* 箱体Id，取值 0~实际箱体数*/
    SWORD32  sdwCtrlFlg;          /* 扫描控制标志，取值:PD_SCAN_START(0)、PD_SCAN_PAUSE(1)、PD_SCAN_STOP(2)*/
    T_Schedule tSchedule;         /* 该类型值缺省时，表明扫描立即执行*/
} _PACKED_1_ T_PdScanCtrl;

typedef struct
{
    SWORD32 sdwPdSlotId;       /* 磁盘槽位号，取值0~27(ScanBox);  0~11(SPR10) */
    SWORD32 sdwPdEnclosureId;  /* 箱体Id */
    SWORD32 sdwControl;        /* 控制方式，ON-开启可视指示；OFF-关闭可视指示 */
} _PACKED_1_ T_PdLed;

typedef struct
{
    SWORD32 sdwWarnSwitch;       /* 控制方式，ON-开启；OFF-关闭 */
} _PACKED_1_ T_PdWarnSwitch;

typedef struct
{
    WORD32  dwScanStatus;            /* 磁盘扫描所处的状态，出参，取值：HDD_SCAN_STATUE_NOT_STARTED、HDD_SCAN_STATUE_STOPPED、HDD_SCAN_STATUE_RUNNING、HDD_SCAN_STATUE_COMPLETE*/
    T_ScsTime  tStartTime;              /* 磁盘扫描启动时间 ，出参，“未启动”状态没有开始时间、且返回全0*/
    T_ScsTime  tStopTime;               /* 磁盘扫描结束时间 ，出参，“未启动”、“运行中”状态没有结束时间、且返回全0*/
} _PACKED_1_ T_HddScanInfo;

typedef struct
{
    WORD32  dwScanPeriod;           /* 磁盘扫描周期，取值 30 -- 90（天），入参*/
} _PACKED_1_ T_HddScanPeriod;

typedef struct
{
    WORD32 sdwPdBadBlockWarnNum;            /* 系统中磁盘的告警坏块数目，取值:>=0 */
} _PACKED_1_ T_PdBadBlockWarnNum;

/* 此结构体参考了smart工具的设计 */
typedef struct
{
    BYTE ucId;
    WORD16 uwFlags;
    BYTE ucCurrent;
    BYTE ucWorst;
    WORD64 ucRaw;
    BYTE ucThres;
} _PACKED_1_ T_DmSmartDetailInfo;

typedef struct
{
    SWORD32 sdwPdSlotId;            /* 磁盘槽位号，取值0~27(ScanBox);  0~11(SPR10) */
    SWORD32 sdwPdEnclosureId;  /* 箱体Id */
    BYTE ucAucPdName[12];   /* 磁盘设备名 如sda */
    SWORD32 cIsSupportSmart;  /* 磁盘是否支持SMART */
    SWORD32 cIsSmartEnable;   /* 磁盘SMART功能是否开启 */
    SWORD32 cSmartStatus;     /* 磁盘的SMART状态是否OK */
    SWORD32 dwSmartInfoCount;/*SMART属性个数*/
    T_DmSmartDetailInfo tSmartDetailInfo[30];   /* 磁盘SMART属性详细信息 */
    SWORD32 sdwSelfTestTime;  /* 执行自检所需时间 */
} _PACKED_1_  T_PdSmartStateInfo;

typedef struct
{
    SWORD32 sdwPdSlotId;                /* 磁盘槽位号，取值0~27(ScanBox);  0~11(SPR10) */
    SWORD32 sdwPdEnclosureId;           /* 硬盘所在的柜子id */
    WORD32 dwRawReadErrorRate;          /* 01 数据读取错误率 最坏之应该大于阀门值 */
    WORD32 dwSpinUpTime;                /* 03 马达旋转到标准转速所需的时间 毫秒为单位 */
    WORD32 dwStartStopCount;            /* 04 启动、停止计数 仅供参考，无阀门值 */
    WORD32 dwRealloctedSectorsCount;    /* 05 重新分配的扇区数，越小越好 */
    WORD32 dwSeekErrorRate;             /* 07 寻道错误率 */
    WORD32 dwPowerOnHours;              /* 09 累计通电时间  越低越好，无阀门值 */
    WORD32 dwSpinRetryCount;            /* 10 马达重试次数 越低越好，无阀门值 */
    WORD32 dwCalibrationRetryCount;     /* 11 校准重试次数  越低越好，无阀门值 */
    WORD32 dwPowerCycleCount;           /* 12 通电周期计数（硬盘开关电源的次数） 仅供参考，无阀门值 */
    WORD32 dwPowerOffRetractCount;      /* 192 断电磁头缩回计数 越低越好 无门限值 富士通专有 */
    WORD32 dwLoadCycleCount;            /* 193 磁头伸出周期计数 */
    WORD32 dwTemperature;               /* 194 温度 */
    WORD32 dwRealloctedEventCount;      /* 196 重新映射的扇区事件计数 */
    WORD32 dwCurrentPendingSector;      /* 197 当前待映射的扇区数 */
    WORD32 dwUncorrectableSectorCount;  /* 198 脱机无法校验的扇区数 */
    WORD32 dwUDMACrcErrorCount;         /* 199 Ultra DMA CRC错误计数 */
    WORD32 dwWriteErrorRate;            /* 200 写扇区的错误计数 越低越好 */
} _PACKED_1_ T_PdSmartInfo;

typedef struct
{
    SWORD32     sdwPdNum;               /* 磁盘个数，取值MAX_ENC_NUM_IN_SYS(4) * MAX_PD_NUM_IN_ENC(16) */
    T_HddInfo   tHddInfo[MAX_PD_NUM_IN_SYS];
} _PACKED_1_ T_AllHddInfo;

/***************************************Blk*************************************/

/***************************************Vol*************************************/
/* BLK与SCS不能通用该结构体 用户不需要填充Owner*/
typedef struct
{
    CHAR     cVdName[MAX_BLK_NAME_LEN];  /*VD 名称,不能为空*/
    CHAR     cVolName[MAX_BLK_NAME_LEN]; /* Vol名称，不能为空*/
    SWORD32  sdwChunkSize;               /* new chunk size,其为4的倍数，单位:KB， 取值MIN_CHUNK_SIZE(4)~MAX_CHUNK_SIZE(512 )*/
    SWORD64  sqwCapacity;                /* capacity of vol in sectors, KB */
    SWORD32  sdwCtlPrefer;               /* 首选控制器,暂时为0,1 */
    SWORD32  sdwCachePolicy;             /* CACHE 写回写穿策略, 取值CACHE_WRITE_BACK_POLICY(0),CACHE_WRITE_THROUGH_POLICY(1) */
    SWORD32  sdwAheadReadSize;           /* cache预读系数,取值0~2048 ，无单位*/
    WORD32   dwSSDCacheSwitch;           /* SSD Cache开关, 表示是否请SSD Cache, 取值：ON(1)  OFF(0) */
    WORD32   sqwTotalFlowLimit;          /* 总流量上限 ,单位:M */
    WORD32   sqwReadFlowLimit;           /* 读流量上限 ,单位:M*/
    WORD32   sqwWriteFlowLimit;          /* 写流量上限 ,单位:M*/
    WORD32   sqwTotalIoCount;            /* 总IOPS上限:允许访问的总IO个数 */
    WORD32   sqwReadIoCount;             /* 读IOPS上限:允许读操作的总IO个数 */
    WORD32   sqwWriteIoCount;            /* 写IOPS上限:允许写操作的总IO个数 */
} _PACKED_1_ T_CreateVol;
typedef struct
{
    CHAR    cVolName[MAX_BLK_NAME_LEN]; /* Vol/Svol名称,不能为空,入参*/
    WORD32  sqwTotalFlowLimit;          /* 总流量上限 ,单位:M */
    WORD32  sqwReadFlowLimit;           /* 读流量上限 ,单位:M*/
    WORD32  sqwWriteFlowLimit;          /* 写流量上限 ,单位:M*/
    WORD32  sqwTotalIoCount;            /* 总IOPS上限:允许访问的总IO个数 */
    WORD32  sqwReadIoCount;             /* 读IOPS上限:允许读操作的总IO个数 */
    WORD32  sqwWriteIoCount;            /* 写IOPS上限:允许写操作的总IO个数 */
} _PACKED_1_ T_VolFlowLimitInfo;

/* BLK与SCS可以通用该结构体 */
typedef struct
{

    CHAR     cVdName[MAX_BLK_NAME_LEN];  /*VD 名称,不能为空，入参*/
    SWORD32   sdwVolType;                   /* 卷类型，包含普通卷（NORM_VOL）、快照卷（SNAPSHOT_VOL） */
    SWORD32  sdwVolNum;           /* 卷的数目 */
    CHAR     cVolNames[MAX_VISIBLE_VOL_NUM_ON_VD][MAX_BLK_NAME_LEN];   /* 指定VD 上的卷名称列表 */
} T_AllVolNamesOnVd;

typedef struct
{
    CHAR   cVolName[MAX_BLK_NAME_LEN]; /* Vol名称，不能为空，入参*/
    WORD32 sdwReadTotalSectors;        /* 读扇区总数*/
    WORD32 sdwWriteTotalSectors;       /* 写扇区总数*/
    WORD32 sdwReadTotalIos;            /* 读IO总次数*/
    WORD32 sdwWriteTotalIos;           /* 写IO总次数*/
    WORD32 sdwReadErrorSectors;        /* 读出错扇区数目*/
    WORD32 sdwWriteErrorSectors;       /* 写出错扇区数目*/
    WORD32 sdwReadErrorIos;            /* 读出错IO 数目*/
    WORD32 sdwWriteErrorIos;           /* 写出错IO 数目*/
} _PACKED_1_ T_GetVolStat;

/* BLK与SCS可以通用该结构体 */
typedef struct
{
    CHAR    cVolName[MAX_BLK_NAME_LEN];  /* Vol Name ，入参 */
} _PACKED_1_ T_VolName;

typedef struct
{
    CHAR    cVolName[MAX_BLK_NAME_LEN];    /* Vol名称，不能为空 ，入参*/
    CHAR    cVolNewName[MAX_BLK_NAME_LEN]; /* 待修改的Vol名称，不能为空，入参*/
} _PACKED_1_ T_VolRename;

typedef struct
{

    CHAR     cVolName[MAX_BLK_NAME_LEN]; /* Vol名称，不能为空，入参*/
    WORD64   sqwExpandSize;              /* expand size  ，单位MB ，入参*/
} _PACKED_1_ T_ExpVol;

/* BLK与SCS可以通用该结构体 */
typedef struct
{
    CHAR     cVolName[MAX_BLK_NAME_LEN]; /* Vol名称，不能为空，入参*/
    SWORD32  sdwNewChunk; /* new chunk size,其为4的倍数,单位:KB ， 取值MIN_CHUNK_SIZE(4)~MAX_CHUNK_SIZE(512 )，入参*/
} _PACKED_1_ T_ReSegVol;

/* BLK与SCS可以通用该结构体 最后一个成员由SCS填充*/
typedef struct
{
    CHAR      cVolName[MAX_BLK_NAME_LEN]; /* Vol名称,不能为空*/
    CHAR      cVdName[MAX_BLK_NAME_LEN];  /*VD名称或POOL名称,不能为空*/
    BYTE      ucVolUuid[MAX_DEV_UUID_LEN];  /* 卷的UUID  */
    SWORD64   sqwCapacity;     /* vol capacity  ,KB*/
    SWORD32   sdwLevel;        /* 该变量不再使用，EC单号611004003535，熊永刚，2014.6.20 */
    SWORD32   sdwState;        /* eVolState , vol state defined in struct eVolState,取值VOL_S_GOOD(0),
                                               VOL_S_FAULT(1),  VOL_S_ERR(2),VOL_S_CHUNKSIZE_MIGRATION(3),
                                               VOL_S_EXPAND(4),VOL_S_UNREADY(5),VOL_S_READONLY(12), VOL_S_INVALID(0xffff) */
    SWORD32   sdwOwned;        /* 卷的所属，取值:VOL_IN_VD ---表示vol属于VD, VOL_IN_POOL ---表示vol属于pool */
    SWORD32   sdwStripeSize;   /* vol chunk size ,KB*/
    SWORD32   sdwOwnerCtrl;    /* owner control ,暂时为0,1 */
    SWORD32   sdwPreferCtrl;   /*  首选控制器,暂时为0,1 */
    T_ScsTime    tCreateTime;     /* 创建时间  */
    SWORD32   sdwMapState;     /* 卷的映射状态，取值MAPPED_VOL(1),NO_MAPPED_VOL(0) */
    SWORD32   sdwCachePolicy;  /* CACHE 写回写穿策略, 取值CACHE_WRITE_BACK_POLICY(0),CACHE_WRITE_THROUGH_POLICY(1) */
    SWORD32   sdwAheadReadSize;/* cache预读系数,取值0~2048 */
    SWORD32   sdwIsRvol;       /* 源卷是否已经存在快照资源空间 ，出参*/
    SWORD32   sdwSvolNum;      /* 源卷上快照卷的个数 ，出参*/
    SWORD32   sdwCloneNum;     /* 源卷上克隆卷的个数 ，出参*/
    SWORD32   sdwMirrorNum;    /* 源卷上镜像卷的个数 ，出参*/
    SWORD32   sdwVerifyStatus; /* 校验状态，出参，取值：VOL_VERIFY_STATUE_NOT_STARTED、VOL_VERIFY_STATUE_CANCELED、VOL_VERIFY_STATUE_RUNNING、VOL_VERIFY_STATUE_COMPLETE */
    SWORD32   sdwMovePolicy;                   /* 迁移策略,pool上的卷有效，-1表示无效值*/
    SWORD32   sdwAllocPolicy;                  /* 初始容量分配策略,pool上的卷有效,取值：ZTIER_ALLOC_STRATEGY_AUTO（自动分配）、ZTIER_ALLOC_STRATEGY_PREFER_0（优先从高性能层分配）、ZTIER_ALLOC_STRATEGY_PREFER_1（优先从性能层分配）、ZTIER_ALLOC_STRATEGY_PREFER_2 （优先从容量层分配）*/
    SWORD32   sdwTierPercentage[MAX_TIER_NUM]; /* 卷在各Tier上的分布百分比pool上的卷有效,-1表示空值或者无效值*/

    WORD32    udwIsThinVol;                    /* 是否精简卷，0(VALUE_FALSE)否，1(VALUE_TURE)是 ,pool上的卷有效,*/
    SWORD32   sdwAlarmThreshold;               /* 容量告警阈值，百分比, pool上的精简卷有效*/
    SWORD32   sdwAlarmStopAllocFlag;           /* 达到容量告警阈值时，停止空间分配标志，0(VALUE_FALSE)不停止分配空间，1(VALUE_TURE)停止分配空间，pool上的精简卷有效*/
    WORD64    uqwAllocedCapacity;              /* 已经分配的物理空间，单位KB,pool上的精简卷有效*/
    WORD32    dwSSDCacheSwitch;   /* SSD Cache开关, 表示是否请SSD Cache, 取值：ON(1)  OFF(0) */
    WORD32   sqwTotalFlowLimit;   /* 总流量上限 ,单位:M */
    WORD32   sqwReadFlowLimit;    /* 读流量上限 ,单位:M*/
    WORD32   sqwWriteFlowLimit;   /* 写流量上限 ,单位:M*/
    WORD32   sqwTotalIoCount;     /* 总IOPS上限:允许访问的总IO个数 */
    WORD32   sqwReadIoCount;      /* 读IOPS上限:允许读操作的总IO个数 */
    WORD32   sqwWriteIoCount;     /* 写IOPS上限:允许写操作的总IO个数 */
} _PACKED_1_ T_VolInfo;

typedef struct
{
    CHAR    cVolName[MAX_BLK_NAME_LEN]; /* Vol名称,不能为空,入参*/
    SWORD32 sdwPrefeCtl;                /* 首选控制器,暂时为0,1  ，入参*/
} _PACKED_1_ T_VolPreferCtrl;

/* BLK与SCS可以通用该结构体 */
typedef struct
{
    CHAR     cVolName[MAX_BLK_NAME_LEN]; /* Vol名称,不能为空,  入参*/
    SWORD32  sdwTaskType;  /* eVolTaskType, task type, defined in struct eLdTaskType,
                                               取值VOL_TASK_CHUNK(0),VOL_TASK_RESHAPE(1) */
    T_ScsTime   tStartTime;  /* 开始时间  */
    SWORD32  sdwPercent;   /* progress of task */
    T_ScsTime   tFinishTime; /* 结束时间  */
    /* BYTE ucDelay;  */    /* reserved */
} _PACKED_1_ T_VolGetTaskInfo;

typedef struct
{
    CHAR    cVolName[MAX_BLK_NAME_LEN]; /* Vol/Svol名称,不能为空,入参*/
    SWORD32 sdwCachePolicy;  /* CACHE 写回写穿策略, 取值CACHE_WRITE_BACK_POLICY(0),CACHE_WRITE_THROUGH_POLICY(1) ，入参*/
    SWORD32 sdwAheadReadSize;/* cache预读系数 ，入参*/
} _PACKED_1_ T_VolCacheInfo;

typedef struct
{
    CHAR    scVolName[MAX_BLK_NAME_LEN];              /* 卷名，入参*/
    SWORD32 sdwRecoveryMode;                          /* 修复模式，入参，取值：VOL_VERIFY_NON_AUTO_RECOVERY、VOL_VERIFY_AUTO_RECOVERY ，缺省值VOL_VERIFY_NON_AUTO_RECOVERY */
    SWORD32 sdwSpeedLevel;                            /* 校验速率，入参，取值：VOL_VERIFY_SPEED_LOW、VOL_VERIFY_SPEED_MEDIUM、VOL_VERIFY_SPEED_HIGH，缺省值VOL_VERIFY_SPEED_MEDIUM*/
} _PACKED_1_ T_VolVerify;

typedef struct
{
    WORD32 uqwStripeIndex;                                  /* 条带编号,从0开始,取值0 - （MAX_BLK_VERIFY_NUM - 1）*/
    WORD64 udwStripeLocgicAddr;                             /* vol的逻辑地址 */
    WORD32 udwInconsistencyLenth;                           /* 不一致数据的长度, 单位：Byte*/
} _PACKED_1_ T_VolStripeVerify;

typedef struct
{
    CHAR    scVolName[MAX_BLK_NAME_LEN];                     /* 卷名，入参*/
    SWORD32 sdwVerifyStatus;                                 /* 校验状态，出参，取值：VOL_VERIFY_STATUE_NOT_STARTED、VOL_VERIFY_STATUE_CANCELED、VOL_VERIFY_STATUE_RUNNING、VOL_VERIFY_STATUE_COMPLETE */
    SWORD32 sdwVerifyProgress;                               /* 校验进度百分比，出参，取值为0 - 100 */
    T_ScsTime  tStartTime;                                      /* 该次校验启动时间 */
    SWORD32 sdwRecoveryMode;                                 /* 修复模式，出参，取值：VOL_VERIFY_NON_AUTO_RECOVERY、VOL_VERIFY_AUTO_RECOVERY*/
    SWORD32 sdwSpeedLevel;                                   /* 校验速率，出参，取值：VOL_VERIFY_SPEED_LOW、VOL_VERIFY_SPEED_MEDIUM、VOL_VERIFY_SPEED_HIGH */
    SWORD32 sdwTotalNumOfInconsistency;                      /* 校验出来的vol上不一致条带总数，出参，取值：0 - MAX_BLK_VERIFY_NUM */
    T_VolStripeVerify tVolStripeVerify[MAX_BLK_VERIFY_NUM];  /* 校验出来的Vol上不一致条带的信息列表，出参，*/
} _PACKED_1_ T_VolVerifyInfo;

typedef struct
{
    SWORD32 sdwOwnerCtrl;              /*切换的目的控制器Id ,暂时定义为0、1，对应的宏定义CTRL0、CTRL1*/
} _PACKED_1_ T_SwitchAllVolIoPath;

/***************************************SNAP************************************/
typedef struct
{
    CHAR    scVolName[MAX_BLK_NAME_LEN];    /* 卷名字, 入参 */
    WORD32  dwOptObj;                       /* 入参对象，0表示克隆，镜像等对象，1表示一致性组快照，2表示一致性组镜像，3表示一致性组克隆*/
    SWORD32 sdwAgentExistFlag;              /* 出参，0表示无映射，1表示加入映射，有主机代理，2表示加入映射，没有主机代理*/
} _PACKED_1_ T_CheckAgentExist;

typedef struct
{
    CHAR scVolName[MAX_BLK_NAME_LEN];    /* 卷名字, 入参 */
    SWORD16 swRepoSpaceAlarm;            /* 资源卷空间告警阀值 */
    SWORD16 swRepoOverflowPolicy;        /* 资源卷缓存溢出策略 */
    //SWORD16 swRepoPercent;               /* 资源卷占源卷容量的百分比 20~100 */
    SWORD64 sqwRepoCapacity;               /* 资源卷容量,单位KB*/
} _PACKED_1_ T_RepoInfo;

typedef struct
{
    SWORD32 sdwVolNum;                   /* 卷数目 */
    T_RepoInfo tRepoInfo[MAX_SVOL_NUM_IN_SYS];    /* 系统中快照资源卷信息列表 */
} _PACKED_1_ T_AllRepoList;

/* 创建定时快照计划 */
typedef struct
{
    T_ScsTime  tStartTime;                     /* 开始时间，参照系统时间的本地时间，年、月、日、时、分、秒有效，入参 */
    T_ScsTime  tEndTime;                       /* 截止时间，参照系统时间的本地时间，年、月、日、时、分、秒有效，入参 */
    SWORD32    interval_time;                  /* 间隔时间，单位：分钟 */
    T_ScsTime  tInvalidStartTime;              /* 时间区域起点,暂停自动创建,开始清理快照 */
    T_ScsTime  tInvalidEndTime;                /* 时间区域终点,停止清理快照,恢复自动创建 */
    CHAR       scBaseVolName[MAX_BLK_NAME_LEN]; /* 快照源卷名称*/
    SWORD32    sdwSnapMode;                     /* 0只读快照，1可写快照*/
    SWORD16    swRepoSpaceAlarm;                /* 资源卷空间告警阀值 */
    SWORD16    swRepoOverflowPolicy;            /* 资源卷缓存溢出策略 */
    //SWORD16    swRepoPercent;                  /* 资源卷占源卷容量的百分比 20~100 */
    SWORD64    repolun_capacity;                 /* 资源卷占源卷容量KB */
    BYTE       ucIsAgent;                       /* 1表示向快照代理发送快照通知，0表示不发送 */
    BYTE       policy;                          /* 满配策略，0：终止定时快照计划；1：删除最早创建的定时快照 */
    SWORD32    sdwReserveNum;                   /* 自动删除策略中的保留快照数量,0~8个 */
} _PACKED_1_ T_SvolPlanCreate;

/* 删除定时快照计划 */
typedef struct
{
    CHAR scBaseVolName[MAX_BLK_NAME_LEN];    /* 快照源卷名称，入参*/
} _PACKED_1_ T_SvolPlanName;

typedef struct
{
    CHAR       scBaseVolName[MAX_BLK_NAME_LEN];     /* 快照源卷名称，入参*/
    T_ScsTime  tStartTime;                          /* 开始时间，参照系统时间的本地时间，年、月、日、时、分、秒有效， */
    T_ScsTime  tEndTime;                            /* 截止时间，参照系统时间的本地时间，年、月、日、时、分、秒有效， */
    SWORD32    interval_time;                       /* 间隔时间，单位：分钟 ，可选入参， */
    T_ScsTime  tInvalidStartTime;                   /* 计划无效开始时间，不包括日期，仅时、分有效， */
    T_ScsTime  tInvalidEndTime;                     /* 计划无效结束时间，不包括日期，仅时、分有效， */
    BYTE       policy;                              /* 满配策略，0：终止定时快照计划；1：删除最早创建的定时快照， */
    SWORD32    sdwReserveNum;                   /* 自动删除策略中的保留快照数量,0~8个 */
} _PACKED_1_ T_SvolPlanUpdate;

/* 定时快照计划信息 */
typedef struct
{
    CHAR       scBaseVolName[MAX_BLK_NAME_LEN]; /* 快照源卷名称 ，入参*/
    SWORD32    sdwSnapPlanState;                /* 定时快照计划状态。0：正常；1：故障，出参*/
    T_ScsTime  tStartTime;                      /* 开始时间 ，出参*/
    T_ScsTime  tEndTime;                        /* 截止时间，出参 */
    SWORD32    interval_time;                     /* 间隔时间，单位：分钟 ，出参*/
    T_ScsTime  tInvalidStartTime;               /* 计划无效开始时间，不包括日期，仅时、分有效，出参*/
    T_ScsTime  tInvalidEndTime;                 /* 计划无效结束时间，不包括日期，仅时、分有效，出参*/
    BYTE       policy;                            /* 满配策略，0：终止定时快照计划；1：删除该源卷最早创建的定时快照 ，出参*/
    SWORD32    sdwReserveNum;                   /* 自动删除策略中的保留快照数量,0~8个 */
    SWORD64    sqwOriginCapacity;               /* 源卷容量,单位KB*/
    SWORD64    sqwRepoCapacity;                /* 资源卷容量,单位KB*/
} _PACKED_1_ T_SvolPlanInfo;

/* 定时快照计划概要信息列表 */
typedef struct
{
    SWORD32        sdwSnapPlanNum;                      /* 计划数目，出参*/
    T_SvolPlanInfo tSnapPlanInfo[MAX_SNAP_PLAN_NUM];    /* 计划任务信息列表,前sdwSnapPlanNum个元素有效，出参*/
} _PACKED_1_ T_SvolPlanList;

/* 快照创建 */
typedef struct
{

    CHAR scVolName[MAX_BLK_NAME_LEN];    /* 源卷名称*/
    CHAR scSnapName[MAX_BLK_NAME_LEN];   /* 快照卷名称 */
    SWORD32 sdwSnapType;                 /* 快照类型, 取值: COW(1) ROW(2)*/
    SWORD16 swRepoSpaceAlarm;            /* 资源卷空间告警阀值 */
    SWORD16 swRepoOverflowPolicy;        /* 资源卷缓存溢出策略 */
    SWORD64 sqwRepoCapacity;               /* 资源卷容量,单位KB*/
    BYTE ucIsAgent;                      /* 1表示向快照代理发送快照通知，0表示不发送 */
    BYTE ucSnapMode;                     /* 快照模式, 取值: SNAP_READ_ONLY(0)、SNAP_RW(1)*/
    BYTE is_private;                     /* 等于1表示为私有快照。供vas使用 */
    BYTE ucIsAuto;                       /* 表示快照类型。0：普通快照；1：定时快照 */
} _PACKED_1_ T_SvolCreate;

/* 快照删除 */
typedef struct
{
    CHAR scSnapName[MAX_BLK_NAME_LEN];    /* 快照卷名称 */
    BYTE is_private;                     /* 等于1表示为私有快照。供vas使用 */
} _PACKED_1_ T_SvolName;

/* 快照更名 */
typedef struct
{
    CHAR scSnapName[MAX_BLK_NAME_LEN];       /* 快照卷名称 */
    CHAR scSnapNewName[MAX_BLK_NAME_LEN];    /* 快照卷新名称 */
} _PACKED_1_ T_SvolRename;

/* 快照类型变更: 只读/可写 */
typedef struct
{
    CHAR scSnapName[MAX_BLK_NAME_LEN];       /* 快照卷名称 */
    BYTE ucSnapMode;                         /* 快照模式, 取值: SNAP_READ_ONLY(0)、SNAP_RW(1)*/
} _PACKED_1_ T_SnapSetMode;

/* 快照资源卷属性 */
typedef struct
{
    CHAR scSnapName[MAX_BLK_NAME_LEN];         /* 源卷名称(入参), 快照资源卷属性是源卷的一个属性, 因此在修改时, 需以源卷名为索引 */
    SWORD16 swRepoSpaceAlarm;                  /* 资源卷空间告警阀值(入参) */
    SWORD16 swRepoOverflowPolicy;              /* 资源卷缓存溢出策略(入参) */
} _PACKED_1_ T_SnapSetRepoAttr;

/* 快照信息 */
typedef struct
{
    CHAR scSnapName[MAX_BLK_NAME_LEN];        /* 快照卷名称 */
    CHAR scVolName[MAX_BLK_NAME_LEN];         /* Vol名称 */
    SWORD16 swRepoSpaceAlarm;                 /* 资源卷空间告警阀值 */
    SWORD16 swRepoOverflowPolicy;             /* 资源卷缓存溢出策略 */
    SWORD32 sdwSnapType;                      /* 快照类型 */
    SWORD32 sdwSnapState;                     /* The state of the svol, the possible values are %SVOL_S_ACTIVE, %SVOL_S_FAULTY.*/
    SWORD32 sdwLunMapState;                   /* 快照卷的映射状态，取值MAPPED_VOL(1),NO_MAPPED_VOL(0) ，出参*/
    SWORD64 sqwRepoCapacity;                  /* 资源卷容量 */
    SWORD64 sqwRepoRemainCapacity;            /* 资源卷剩余容量 */
    SWORD32 sdwIsAgent;                       /* 是否使用快照代理 */
    SWORD32 sdwSnapMode;                      /* 快照模式, 取值: SNAP_READ_ONLY(0)、SNAP_RW(1)*/
    SWORD32 sdwOwnerCtrl;                     /* 归属控制器ID */
    SWORD32 sdwTaskProcess;                   /* 任务进度 */
    T_ScsTime tCreateTime;                    /* 快照创建时间 */
    T_ScsTime tTaskStartTime;                 /* 回滚任务开始时间 */
    T_ScsTime tTaskEndTime;                   /* 回滚任务结束时间 */
    WORD32   sqwTotalFlowLimit;   /* 总流量上限 ,单位:M/s */
    WORD32   sqwReadFlowLimit;    /* 读流量上限 ,单位:M/s */
    WORD32   sqwWriteFlowLimit;   /* 写流量上限 ,单位:M/s */
    WORD32   sqwTotalIoCount;     /* 总IOPS上限:个数/s */
    WORD32   sqwReadIoCount;      /* 读IOPS上限:个数/s */
    WORD32   sqwWriteIoCount;     /* 写IOPS上限:个数 /s */
} _PACKED_1_ T_SvolInfo;

/* BLK与SCS可以通用该结构体 */
typedef struct
{
    CHAR       scVolName[MAX_BLK_NAME_LEN];  /*卷名称 ，入参*/
    SWORD32    sdwSvolNum;  /*快照卷数目*/
    CHAR       scSnapName[MAX_SVOL_NUM_IN_VOL][MAX_BLK_NAME_LEN];    /*快照卷名列表*/
} _PACKED_1_ T_AllSvolNameListOnVol;

typedef struct
{
    CHAR scSnapName[MAX_BLK_NAME_LEN];        /* 快照卷名称 */
    CHAR scVolName[MAX_BLK_NAME_LEN];         /* Vol名称 */
    SWORD32 sdwSnapType;                      /* 快照类型 */
    SWORD32 sdwSnapState;                     /* The state of the svol, the possible values are %SVOL_S_ACTIVE, %SVOL_S_FAULTY. */
    SWORD32 sdwLunMapState;                   /* 快照卷的映射状态，取值MAPPED_VOL(1),NO_MAPPED_VOL(0) */
    SWORD32 sdwIsAgent;                       /* 1表示使用主机代理; 0表示不使用 */
    SWORD32 sdwSnapMode;                      /* 快照模式, 取值: SNAP_READ_ONLY(0)、SNAP_RW(1)*/
    SWORD32 sdwCloneNumOnVol;                  /* 快照卷上的克隆数量*/
    SWORD64 sqwSnapCapacity;                   /* 快照卷容量KB*/
    T_ScsTime tCreateTime;                   /* 快照create time */
} _PACKED_1_ T_SnapOverViewInfo;

typedef struct
{
    SWORD32 sdwSvolNum;                       /* 快照卷数目*/
    T_SnapOverViewInfo tSnapInfo[MAX_SVOL_NUM_IN_SYS];    /*快照卷概要信息列表*/
} _PACKED_1_ T_AllSvolNameList;

/***************************************Clone Vol************************************/
/*CloneVol创建*/
typedef struct
{
    CHAR    scCvolName[MAX_BLK_NAME_LEN];    /* 克隆名称 */
    CHAR    scBvolName[MAX_BLK_NAME_LEN];    /* 源卷名*/
    CHAR    scTargetName[MAX_BLK_NAME_LEN];  /* 目的卷名 */
    SWORD32 sdwInitSync;                     /* 是否进行初始同步 , 1-YES, 0--NO*/
    SWORD32 sdwProtectRestore;               /* 是否启动保护拷贝, 1-YES, 0--NO */
    SWORD32 sdwPri;                          /* 同步或反同步任务优先级,取值:SYNC_LOW(0),SYNC_MEDIUM(1),SYNC_HIGH(2)*/
    SWORD32 sdwPolicy;                       /* 同步恢复策略, 0：自动；1：手动 */
    SWORD32 sdwBvolType;                     /* 源卷类型, 0：普通卷；1：快照卷 */
} _PACKED_1_ T_CreateCvol;

/* 用于clone删除、同步、恢复、分离等操作 */
typedef struct
{
    CHAR    scCvolName[MAX_BLK_NAME_LEN];    /* 拷贝卷名*/
    BYTE    ucIsAgent;                       /* 默认为0， 1代表不使用主机代理，直接分离ec611004112711 修改*/
} _PACKED_1_ T_CvolName;

/* Clone信息查询 */
typedef struct
{
    CHAR    scCvolName[MAX_BLK_NAME_LEN];    /* 克隆名称, 入参 */
    CHAR    scBVolName[MAX_BLK_NAME_LEN];    /* 源卷名*/
    CHAR    scTargetName[MAX_BLK_NAME_LEN];  /* 目的卷名 */
    SWORD32 sdwInitSync;                     /* 是否进行初始同步, 1-YES, 0--NO */
    SWORD32 sdwProtectRestore;               /* 是否启动保护拷贝, 1-YES, 0--NO */
    SWORD32 sdwPri;                          /* 同步或反同步的速率 */
    SWORD32 sdwPolicy;                       /* 同步恢复策略, 0：自动；1：手动 */
    /* 拷贝卷的状态, 取值:
     * VAS_CLONE_STATUS_INIT       0(初始态)
     * VAS_CLONE_STATUS_FRACTUR    1(分离)
     * VAS_CLONE_STATUS_CONSIS     2(数据一致)
     * VAS_CLONE_STATUS_SYNCING    3(正在同步)
     * VAS_CLONE_STATUS_RECING     4(正在恢复)
     * VAS_CLONE_STATUS_ERROR      5(故障)
     */
    SWORD32 CvolState;
    SWORD32 sdwOwnerCtrl;                    /* 归属控制器 */
    SWORD32 sdwSyncProcess;                  /* 同步任务进度: 百分比% */
    SWORD32 sdwRestoreProcess;               /* 回滚任务进度: 百分比% */
    T_ScsTime tCreateTime;                   /* Clone创建时间 */
    T_ScsTime tSyncStartTime;                /* 同步任务开始时间 */
    T_ScsTime tSyncEndTime;                  /* 同步任务结束时间 */
    T_ScsTime tRestoreStartTime;             /* 回滚任务开始时间 */
    T_ScsTime tRestoreEndTime;               /* 回滚任务结束时间 */
} _PACKED_1_ T_CvolInfo;

typedef struct
{
    CHAR scCloneName[MAX_BLK_NAME_LEN];       /* 克隆名称 */
    CHAR scVolName[MAX_BLK_NAME_LEN];         /* 源卷名称 */
    CHAR scTargetName[MAX_BLK_NAME_LEN];      /* 目的卷名称 */
    /* 拷贝卷的状态, 取值:
     * VAS_CLONE_STATUS_INIT       0(初始态)
     * VAS_CLONE_STATUS_FRACTUR    1(分离)
     * VAS_CLONE_STATUS_CONSIS     2(数据一致)
     * VAS_CLONE_STATUS_SYNCING    3(正在同步)
     * VAS_CLONE_STATUS_RECING     4(正在恢复)
     * VAS_CLONE_STATUS_ERROR      5(故障)
     */
    SWORD32 sdwCloneState;
    T_ScsTime tCreateTime;                    /* 克隆卷创建时间 */
} _PACKED_1_ T_CloneOverViewInfo;

typedef struct
{
    SWORD32 sdwCvolNum;        /* 拷贝卷数目*/
    T_CloneOverViewInfo tCloneInfo[MAX_CLONE_IN_SYS];      /* 拷贝卷概要信息列表*/
} _PACKED_1_ T_AllCvolInfo;

/* 卷上的拷贝卷信息*/
typedef struct
{
    CHAR    scVolName[MAX_BLK_NAME_LEN];        /* 拷贝卷的名字 ,入参*/
    SWORD32 sdwCvolNum;                         /* 卷上的所有拷贝卷数目 */
    CHAR    scCvolNames[MAX_CLONE_IN_VOL][MAX_BLK_NAME_LEN];   /* 卷上的所有拷贝名字列表 */
} _PACKED_1_ T_CvolNamesOnVol;

/*拷贝卷同步或者反同步的优先级(速率)*/
typedef struct
{
    CHAR    scCvolName[MAX_BLK_NAME_LEN];  /* 拷贝卷的名字 ，入参*/
    SWORD32 sdwPri;   /* 同步或反同步的优先级，取值:SYNC_LOW(0),SYNC_MEDIUM(1),SYNC_HIGH(2) */
} _PACKED_1_ T_CvolPriority;

/*拷贝卷同步或者反同步的优先级(速率)*/
typedef struct
{
    CHAR    scCloneName[MAX_BLK_NAME_LEN];  /* 拷贝卷的名字 ，入参*/
    SWORD32 sdwPolicy;                      /* 同步恢复策略, 0：自动；1：手动 */
} _PACKED_1_ T_CvolPolicy;

typedef struct
{
    CHAR    scCvolName[MAX_BLK_NAME_LEN];  /* 拷贝卷的名字，入参 */
    SWORD32 sdwProtectRestore;             /* 是否启动保护拷贝, 1-YES, 0--NO */
} _PACKED_1_ T_CvolProtect;

typedef struct
{
    CHAR    scCvolName[MAX_BLK_NAME_LEN];       /* 拷贝卷名称，入参 */
    CHAR    scCvolNewName[MAX_BLK_NAME_LEN];    /* 拷贝卷新名称 ，入参*/
} _PACKED_1_ T_CvolRename;

typedef struct
{
    SWORD32 sdwVolObjectType;                   /* 卷对象类型 ,取值: NORM_VOL / SNAPSHOT_VOL */
    CHAR    scVolObjectName[MAX_BLK_NAME_LEN];  /* 卷对象的名称*/
} _PACKED_1_ T_VolObjectInfo;

typedef struct
{
    CHAR     scMapGrpName[MAX_MAPGRP_NAME_LEN]; /* 映射组名称，入参*/
    SWORD32 sdwVolObjectNum;                                /* 系统中未映射的卷对象数目*/
    T_VolObjectInfo    tVolObjectList[MAX_VISIBLE_VOL_NUM_IN_SYS];  /* 系统中未映射的卷对象的信息列表*/
} _PACKED_1_ T_VolObjectInfoList;

typedef struct
{
    SWORD32  sdwSlotId;       /* 磁盘槽位号，取值0~27(ScanBox);  0~11(SPR10) */
    SWORD32  sdwEnclosureId;  /* 箱体Id，取值 0~实际箱体数*/
    SWORD64  sqwCapacity;     /* 磁盘容量 */
} _PACKED_1_  T_PdIdInfo;

typedef struct
{
    SWORD32      sdwUnusedPdNum;                    /* 空闲盘数目 */
    SWORD32      sdwSasPdNum;                       /* SAS成员盘数目 */
    T_PdIdInfo   tSasMemberPdId[MAX_PD_NUM_IN_SYS];  /* SAS成员盘列表 */
    SWORD32      sdwSataPdNum;                      /* SATA成员盘数目 */
    T_PdIdInfo   tSataMemberPdId[MAX_PD_NUM_IN_SYS]; /* SATA成员磁盘列表 */
} _PACKED_1_ T_AllUnusedPd;

/***************************************Pool功能相关结构体**************************************/
/* 分级存储池创建*/
typedef struct
{
    SWORD32  sdwTierValidFlag;            /* 该Tier有效标记，取值：1有效，0无效*/
    SWORD32  sdwRaidLevel;                /* RAID级别,取值:取值RAID0(0),RAID1(1), RAID5(5),RAID6(6)，入参*/
    SWORD32  sdwRaidVirtualMode;          /* RAID虚拟模式,当sdwRaidLevel取值为RAID5(5),RAID6(6)有效,取值：POOL_RAID5_2、POOL_RAID5_4、POOL_RAID5_8、POOL_RAID6_4、POOL_RAID6_8，入参*/
    SWORD32  sdwCreateType;               /* 创建方式：1 按磁盘数目(POOL_CREATE_BY_DISK_NUM)；2 按磁盘列表(POOL_CREATE_BY_DISK_LIST)*/
    SWORD32  sdwPdNum;                    /* 磁盘数目，最大256，创建pool时每个tier至少3块盘，入参*/
    T_PdId   tPdId[MAX_DISKS_IN_POOL];    /* 磁盘信息列表 ，当sdwCreateType 为POOL_CREATE_BY_DISK_LIST时有效，可选入参 */
    SWORD32  sdwCapacityPolicy;           /* 空间保留策略 ,取值：POOL_CAPACITY_POLITY_NO_RESERVE，POOL_CAPACITY_POLITY_RESERVE_ONE*/
} _PACKED_1_  T_TierSet;

typedef struct
{
    SWORD32  sdwTierValidFlag;            /* 该Tier有效标记，取值：1有效，0无效*/
    SWORD32  sdwRaidLevel;                /* RAID级别,取值:取值RAID0(0),RAID1(1), RAID5(5),RAID6(6)，入参*/
    SWORD32  sdwRaidVirtualMode;          /* RAID虚拟模式,当sdwRaidLevel取值为RAID5(5),RAID6(6)有效,取值：POOL_RAID5_2、POOL_RAID5_4、POOL_RAID5_8、POOL_RAID6_4、POOL_RAID6_8，入参*/
    SWORD32  sdwPdNum;                    /* 磁盘数目，最大256，入参*/
    T_PdId   tPdId[MAX_DISKS_IN_POOL];    /* 磁盘信息列表 ，当sdwCreateType 为POOL_CREATE_BY_DISK_LIST时有效，可选入参 */
    SWORD32  sdwCapacityPolicy;           /* 空间保留策略 ,取值：POOL_CAPACITY_POLITY_NO_RESERVE，POOL_CAPACITY_POLITY_RESERVE_ONE*/
    WORD64   qwTierTotalCapacity;         /* Tier总容量,容量大小，以MB为单位 */
    WORD64   qwTierUsedCapacity;          /* Tier已使用容量,以MB为单位*/
    WORD64   qwTierFreeCapacity;          /* Tier可用容量，不包括保留空间,以MB为单位*/
    WORD64   qwTierHotCapacity;           /* Tier热备空间大小,以MB为单位*/
} _PACKED_1_  T_TierInfo;

typedef struct
{
    T_ScsTime tStartTime;  /*开始时间*/
    T_ScsTime tEndTime;    /*结束时间*/
} _PACKED_1_ T_TimeWindow;

typedef struct
{
    CHAR     scPoolName[MAX_BLK_NAME_LEN]; /* Pool名称,不能为空,入参*/
    T_TierSet  tTier[MAX_TIER_NUM];        /* Tier的配置信息*/
    SWORD32  sdwAlarmThreshold;            /* 容量告警阈值 ，百分比值，比如值为5，表示剩余容量为5%时告警，取值5-50，缺省值20，入参*/
    SWORD32  sdwChunkSize;                 /* Pool的虚拟块大小,取值:POOL_CK_8(8)-POOL_CK_256(256)，单位MB，入参*/
    SWORD32  sdwZtierOnOff;                /* 是否激活Ztier，取值：1是(ON)、0否(OFF)，缺省值：0否(OFF)，入参*/
    SWORD32  sdwStatsMode;                 /* 统计模式，取值：系统智能选择0（ZTIER_STATS_MODE_AUTO）、用户自定义1（ZTIER_STATS_MODE_CUSTOM），缺省值：系统智能选择，入参*/
    SWORD32  sdwMovingMode;                /* 数据迁移策略，取值：自动：1（ZTIER_MOVING_POLICY_AUTO）、仅手动：2(ZTIER_MOVEING_POLICY_ONLY_MANUAL)、定时：3（ZTIER_MOVEING_POLICY_CLOCK_TRIGGER），缺省值：仅手动，入参*/
    SWORD32  sdwMovingSpeed;               /* 迁移速率，取值：高（ZTIER_DATA_MOVING_SPEED_HIGH）、中（ZTIER_DATA_MOVING_SPEED_MEDIUM）、低（ZTIER_DATA_MOVING_SPEED_LOW）,缺省值：低速，入参*/
    SWORD32  sdwOutWindowLowSpeedMoving;   /* 是否在迁移窗口外启动低速迁移,取值：1是(ON)、0否(OFF)，缺省值1，入参*/
    SWORD32  sdwAnalysisPeriod;            /* 统计分析周期，取值：1-672（1小时至4周），单位:小时，缺省值：168（1周），入参*/
    SWORD32  sdwWarmUpPeriod;              /* 首次统计分析周期，取值：1-672（1小时至4周），单位:小时，缺省值：8，入参*/
    T_TimeWindow tStatsOpen[WEEK_DAY_NUM];        /* 统计打开的时间窗口(按星期，数组下标0-6分别表示周一至周日，时和分有效，无效值为-1)，统计模式为“用户自定义”时有效，可选入参*/
    SWORD32 sdwStatsCloseNum;                     /* 统计关闭的时间窗口有效值数目*/
    T_TimeWindow tStatsClose[CLOSE_WINDOW_ITEMS]; /* 统计关闭的时间窗口(按日期，数组前N个数据有效，有效时间:年、月、日、时、分,无效值为-1)，统计模式为“用户自定义”时前sdwStatsCloseNum个值有效,可选入参*/
    T_TimeWindow tMoveOpen[WEEK_DAY_NUM];         /* 迁移打开的时间窗口(按星期，数组下标0-6分别表示周一至周日，时和分有效，无效值为-1)，迁移模式为“用户自定义”时有效，可选入参*/
    SWORD32 sdwMoveCloseNum;                      /* 统计关闭的时间窗口有效值数目*/
    T_TimeWindow tMoveClose[CLOSE_WINDOW_ITEMS];  /* 迁移关闭的时间窗口(按日期，数组前N个数据有效，有效时间:年、月、日、时、分,无效值为-1)，迁移模式为“用户自定义”时前sdwMoveCloseNum个值有效，可选入参*/
} _PACKED_1_ T_CreatePool;

/* 分级存储池信息查询*/
typedef struct
{
    CHAR     scPoolName[MAX_BLK_NAME_LEN];        /* Pool 名称,不能为空, 入参*/
    SWORD32  sdwState;                            /* Pool的状态，取值：POOL_GOOD(0)、POOL_DAMAGED(1)、POOL_OFFLINE(2)、POOL_FAULT(3) */
    T_TierInfo tTier[MAX_TIER_NUM];               /* Tier的配置信息*/
    SWORD32  sdwAlarmThreshold;                   /* 容量告警阈值 ，百分比值，比如值为5，表示剩余容量为5%时告警*/
    SWORD32  sdwChunkSize;                        /* Pool的虚拟块大小,取值:POOL_CK_8(8)-POOL_CK_256(256)，单位MB，入参*/
    SWORD32 sdwZtierOnOff;                        /* 是否激活Ztier */
    SWORD32 sdwStatsMode;                         /* 统计模式，自动或者用户配置 */
    SWORD32 sdwMovingMode;                        /* 数据迁移策略，取值：自动：1（ZTIER_MOVING_POLICY_AUTO）、仅手动：2(ZTIER_MOVEING_POLICY_ONLY_MANUAL)、定时：3（ZTIER_MOVEING_POLICY_CLOCK_TRIGGER）*/
    SWORD32 sdwMovingSpeed;                       /* 迁移速率，取值：高（ZTIER_DATA_MOVING_SPEED_HIGH）、中（ZTIER_DATA_MOVING_SPEED_MEDIUM）、低（ZTIER_DATA_MOVING_SPEED_LOW），缺省值低，入参*/
    SWORD32 sdwOutWindowLowSpeedMoving;           /* 是否在迁移窗口外启动低速迁移 */
    SWORD32 sdwAnalysisPeriod;                    /* 统计分析周期 */
    SWORD32 sdwWarmUpPeriod;                      /* 首次统计分析周期 */
    T_TimeWindow tStatsOpen[WEEK_DAY_NUM];        /* 统计打开的时间窗口(按星期，数组下标0-6分别表示周一至周日，时和分有效，无效值为-1)*/
    SWORD32 sdwStatsCloseNum;                     /* 统计关闭的时间窗口有效值数目*/
    T_TimeWindow tStatsClose[CLOSE_WINDOW_ITEMS]; /* 统计关闭的时间窗口(按日期，数组前N个数据有效，有效时间:年、月、日、时、分,无效值为-1)，前sdwStatsCloseNum个值有效*/
    T_TimeWindow tMoveOpen[WEEK_DAY_NUM];         /* 迁移打开的时间窗口(按星期，数组下标0-6分别表示周一至周日，时和分有效，无效值为-1)*/
    SWORD32 sdwMoveCloseNum;                      /* 统计关闭的时间窗口有效值数目*/
    T_TimeWindow tMoveClose[CLOSE_WINDOW_ITEMS];  /* 迁移关闭的时间窗口(按日期，数组前N个数据有效，有效时间:年、月、日、时、分,无效值为-1)，前sdwMoveCloseNum个值有效*/    SWORD32  sdwAllPdNum;                         /* 成员盘数目*/
    SWORD32  sdwFaultPdNum;                       /* 成员盘中故障盘数目*/
    T_PdId   tFaultMemberPdId[MAX_DISKS_IN_POOL]; /* 故障成员磁盘列表*/
    WORD64   qwTotalCapacity;                     /* 存储池总容量,容量大小，以MB为单位,下同 */
    WORD64   qwUsedCapacity;                      /* 存储池已使用容量 */
    WORD64   qwFreeCapacity;                      /* 存储池可用容量，不包括保留空间 */
    T_ScsTime   tCreateTime;                      /* Pool 创建时间 */
    SWORD32  sdwEnergyConsrv;                     /* 新增字段:省电模式字段改为节能模式,打开(1)/关闭(0)/不支持(2)  */
    T_ScsTime tMovingStartTime;                   /* 手动迁移的启动时间，"70/01/01 00:00:00"时为无效值 */
    SWORD32   sdwMovingTime;                      /* 手动迁移的持续时间，单位：分钟，手动迁移的启动时间为"70/01/01 00:00:00"时，该值为无效值*/
} _PACKED_1_ T_PoolInfo;

typedef struct
{
    CHAR    scPoolName[MAX_BLK_NAME_LEN];  /* Pool 名称,不能为空，入参*/
} _PACKED_1_ T_PoolName;

typedef struct
{
    CHAR       scName[MAX_BLK_NAME_LEN];       /*  存储池名称 ，入参*/
    SWORD32    sdwIsNewTier[MAX_TIER_NUM];     /*  Tier是否是新创建标记，取值：1是，0否,-1无效，入参*/
    T_TierSet  tTier[MAX_TIER_NUM];            /*  Tier信息，与sdwIsNewTier结合使用，当sdwIsNewTier值为0和1时，对应数据有效，入参*/
} _PACKED_1_ T_ExpandPool;

typedef struct
{
    CHAR      scPoolName[MAX_BLK_NAME_LEN];       /* Pool 名称,不能为空, 入参*/
    SWORD32   sdwState;                           /* Pool的状态,取值:迁移中-7(POOL_MOVE_RUNNING)、不在迁移窗口内-8(POOL_MOVE_ENDED)、准备中-9(POOL_MOVE_PREPARE)、迁移功能未开启-10(POOL_MOVE_INVALID)、被中止-11(POOL_MOVE_STOPPED)*/
    SWORD32   sdwMovingMode;                      /* 迁移触发模式，取值：无：0（ZTIER_MOVING_TRIGGER_MODE_INVALID）、自动:1（ZTIER_MOVING_TRIGGER_MODE_AUTO）、手动:2(ZTIER_MOVEING_TRIGGER_MODE_MANUAL)、定时：3（ZTIER_MOVEING_TRIGGER_MODE_CLOCK_TRIGGER）*/
    WORD64    qwTotalCapacity;                    /* 存储池总容量,容量大小，以MB为单位,下同 */
    WORD64    qwUsedCapacity;                     /* 存储池已使用容量 */
    WORD64    qwFreeCapacity;                     /* 存储池可用容量，不包括保留空间 */
    SWORD32   sdwReadyToMoveUp;                   /* Pool内可以向上层迁移的数据量，单位：MB，出参*/
    SWORD32   sdwReadyToMoveDown;                 /* Pool内可以向下层迁移的数据量，单位：MB，出参*/
    SWORD32   sdwMovedUp;                         /* Pool内已经向上层迁移的数据量，单位：MB，出参*/
    SWORD32   sdwMovedDown;                       /* Pool内已经向下层迁移的数据量，单位：MB，出参*/
    T_ScsTime tMoveStartTime;                     /* 迁移的起始时间，出参*/
    SWORD32   sdwMovedTime;                       /* 迁移的持续时间，单位：分钟，出参 */
    SWORD32   sdwExpactMovingTimeLeft;            /* 迁移过程的剩余时间，单位：分钟，出参*/
} _PACKED_1_ T_PoolMovingStatusInfo;

typedef struct
{
    CHAR     scPoolName[MAX_BLK_NAME_LEN];        /* Pool 名称,不能为空, 入参*/
    CHAR     scNewName[MAX_BLK_NAME_LEN];         /* 存储池新名称，如果不更改名字，传入空串表示该值无效*/
    SWORD32  sdwCapacityPolicy[MAX_TIER_NUM];     /* 热备策略,如不需要修改用-1表示该值无效,*/
    SWORD32  sdwAlarmThreshold;                   /* 容量告警阈值 ，百分比值，比如值为5，表示剩余容量为5%时告警,取值5-50，缺省值20，-1表示该值无效，入参*/
    SWORD32  sdwZtierOnOff;                       /* 是否激活Ztier，取值：1是(ON)、0否(OFF)，-1表示该值无效，可选入参*/
    SWORD32  sdwStatsMode;                        /* 统计模式，自动或者手动，-1表示该值无效，可选入参*/
    SWORD32  sdwMovingMode;                       /* 数据迁移策略，取值：自动：1（ZTIER_MOVING_POLICY_AUTO）、仅手动：2(ZTIER_MOVEING_POLICY_ONLY_MANUAL)、定时：3（ZTIER_MOVEING_POLICY_CLOCK_TRIGGER），-1表示该值无效，可选入参 */
    SWORD32  sdwMovingSpeed;                      /* 迁移速率，取值：高、中、低，-1表示该值无效，可选入参*/
    SWORD32  sdwOutWindowLowSpeedMoving;          /* 是否在迁移窗口外启动低速迁移，取值：1是(ON)、0否(OFF)，-1表示该值无效，可选入参*/
    SWORD32 sdwAnalysisPeriod;                    /* 统计分析周期，取值：1-672（1小时至4周），单位:小时，缺省值：168（1周），-1表示该值无效，可选入参*/
    SWORD32 sdwWarmUpPeriod;                      /* 首次统计分析周期，取值：1-672（1小时至4周），单位:小时，缺省值：8，-1表示该值无效，可选入参*/
    T_TimeWindow tStatsOpen[WEEK_DAY_NUM];        /* 统计打开的时间窗口(按星期，数组下标0-6分别表示周一至周日，时和分有效，无效值为-1)，可选入参*/
    SWORD32 sdwStatsCloseNum;                     /* 统计关闭的时间窗口有效值数目，有效值0-CLOSE_WINDOW_ITEMS；-1表示无效；0表示全部删除*/
    T_TimeWindow tStatsClose[CLOSE_WINDOW_ITEMS]; /* 统计关闭的时间窗口(按日期，数组前N个数据有效，有效时间:年、月、日、时、分,无效值为-1)，前sdwStatsCloseNum个值有效，可选入参*/
    T_TimeWindow tMoveOpen[WEEK_DAY_NUM];         /* 迁移打开的时间窗口(按星期，数组下标0-6分别表示周一至周日，时和分有效，无效值为-1)，可选入参*/
    SWORD32 sdwMoveCloseNum;                      /* 统计关闭的时间窗口有效值数目,有效值0-CLOSE_WINDOW_ITEMS；-1表示无效；0表示全部删除*/
    T_TimeWindow tMoveClose[CLOSE_WINDOW_ITEMS];  /* 迁移关闭的时间窗口(按日期，数组前N个数据有效，有效时间:年、月、日、时、分,无效值为-1)，前sdwMoveCloseNum个值有效，可选入参*/
    SWORD32 sdwEnergyConsrv;                      /* 新增字段：省电模式字段改为节能模式,打开(1)/关闭(0)，入参 */
} _PACKED_1_ T_ModifyPool;
typedef struct
{
    CHAR     scPoolName[MAX_BLK_NAME_LEN];        /* Pool 名称,不能为空, 入参*/
    SWORD32  sdwEnergyConsrv;                      /* 新增字段：省电模式字段改为节能模式,打开(1)/关闭(0)，入参 */
} _PACKED_1_ T_ModifyPoolMaid;

typedef struct
{
    CHAR     scPoolName[MAX_BLK_NAME_LEN];   /* Pool 名称,不能为空, 入参*/
    SWORD32  sdwSetMovingTimeFlag;           /* 设置迁移持续时间标记，取值：1（有效），0（无效），入参*/
    SWORD32  sdwMovingTime;                  /* 本次迁移持续时间，单位：分钟，当sdwSetMovingTimeFlag值为1时有效，可选入参*/
    SWORD32  sdwActiveMovingTask;            /* 激活迁移任务，取值：1是(ON)、0否(OFF)，缺省值：1是(ON)，入参*/
} _PACKED_1_ T_StartPoolMoving;

typedef struct
{
    SWORD32 sdwPoolNum;                                          /* 系统中存储池总数 ，出参*/
    CHAR    sdwPoolNames[MAX_POOL_NUM_IN_SYS][MAX_BLK_NAME_LEN]; /* 存储池名字列表 ，出参*/
} _PACKED_1_ T_AllPoolNames;

/* 分级存储池上创建vol*/
typedef struct
{
    CHAR     scPoolName[MAX_BLK_NAME_LEN];  /* Pool 名称,入参*/
    CHAR     scVolName[MAX_BLK_NAME_LEN];   /* Vol名称,入参*/
    SWORD32  sdwStripeDepth;                /* Vol条带深度,其为2的幂，单位:KB， 取值MIN_CHUNK_SIZE(4)~MAX_CHUNK_SIZE(512 )*/
    WORD64   qwCapacity;                    /* 卷容量, 单位 KB ，入参*/
    SWORD32  sdwCtrlPrefer;                 /* 首选控制器,取值为0,1 ，入参*/
    SWORD32  sdwCachePolicy;                /* Cache写回写穿策略, 取值CACHE_WRITE_BACK_POLICY(0),CACHE_WRITE_THROUGH_POLICY(1)，入参 */
    SWORD32  sdwAheadReadSize;              /* Cache预读系数,取值0~2048 ，无单位，入参*/
    SWORD32  sdwAllocPolicy;                /* 初始容量分配策略,取值：ZTIER_ALLOC_STRATEGY_AUTO（自动分配）、ZTIER_ALLOC_STRATEGY_PREFER_0（优先从高性能层分配）、ZTIER_ALLOC_STRATEGY_PREFER_1（优先从性能层分配）、ZTIER_ALLOC_STRATEGY_PREFER_2 （优先从容量层分配），缺省值：自动分配，入参*/
    SWORD32  sdwMovePolicy;                 /* 迁移策略，取值：取值ZTIER_MOVING_STRATEGY_AUTO（自动迁移）、ZTIER_MOVING_STRATEGY_TO_0(向高性能层迁移) 、ZTIER_MOVING_STRATEGY_TO_2（向容量层迁移） 、ZTIER_MOVINGSTRATEGY_NO（不迁移），缺省值：自动迁移，入参*/

    WORD32   udwIsThinVol;                  /* 是否精简卷,0(VALUE_FALSE)否，1(VALUE_TURE)是，缺省值为0，入参*/
    WORD64   uqwInitAllocedCapacity;        /* 初始分配容量, 单位KB，缺省值为0，是精简卷创建时的必选入参 */
    SWORD32  sdwAlarmThreshold;             /* 容量告警阈值，百分比，比如值为5，表示剩余容量为5%时告警，取值50-100，缺省值75，是精简卷创建时的必选入参*/
    SWORD32  sdwAlarmStopAllocFlag;         /* 达到容量告警阈值时，停止空间分配标志，0(VALUE_FALSE)不停止分配空间，1(VALUE_TURE)停止分配空间，缺省值为0，是精简卷创建时的必选入参*/
    WORD32   dwSSDCacheSwitch; /* SSD Cache开关, 表示是否请SSD Cache, 取值：ON(1)  OFF(0) */
} _PACKED_1_ T_CreateVolOnPool;

typedef struct
{
    CHAR     scVolName[MAX_BLK_NAME_LEN]; /* Vol名称，不能为空，入参*/
    WORD64   qwExpandCapacity;            /* 新扩充的容量值，单位MB ，入参*/
} _PACKED_1_ T_ExpVolCapacity;

typedef struct
{
    CHAR     scPoolName[MAX_BLK_NAME_LEN];  /* Pool名称,不能为空，入参*/
    SWORD32  sdwVolType;                    /* 卷类型，包含普通卷（NORM_VOL）、快照卷（SNAPSHOT_VOL）、拷贝卷（CLONE_VOL）,入参 */
    SWORD32  sdwVolNum;                     /* 卷的数目 */
    CHAR     scVolNames[MAX_VOL_NUM_ON_POOL][MAX_BLK_NAME_LEN];   /* 指定Pool上的卷名称列表 */
} _PACKED_1_ T_VolNamesOnPool;

typedef struct
{
    CHAR    scVolName[MAX_BLK_NAME_LEN]; /* vol name */
    SWORD32 sdwNewMovePolicy;            /* 迁移策略，取值：取值ZTIER_MOVING_STRATEGY_AUTO（自动迁移）、ZTIER_MOVING_STRATEGY_TO_0(向高性能层迁移) 、ZTIER_MOVING_STRATEGY_TO_2（向容量层迁移） 、ZTIER_MOVINGSTRATEGY_NO（不迁移），入参*/
} _PACKED_1_ T_ModifyVolMovePolicy;

typedef struct
{
    SWORD32  sdwPdType;                   /* 磁盘类型，取值：1(USP_HDD_HIGH_PERFORMANCE)、2(USP_HDD_PERFORMANCE)、3(USP_HDD_CAPACITY), 入参 */
    SWORD32  sdwPdNum;                    /* 可用的磁盘数目，最大256，出参*/
    T_PdId   tPdId[MAX_DISKS_IN_POOL];    /* 可用的磁盘信息列表，前sdwPdNum个元素有效，出参 */
} _PACKED_1_ T_HddListForPool;

typedef struct
{
    CHAR     scVolName[MAX_BLK_NAME_LEN];  /* 卷名称，入参 */
    SWORD32  sdwAlarmThreshold;            /* 容量告警阈值，百分比,比如值为5，表示剩余容量为5%时告警，取值50-100， -1表示该值不修改，可选入参*/
    SWORD32  sdwAlarmStopAllocFlag;        /* 达到容量告警阈值时，停止空间分配标志，0(VALUE_FALSE)不停止分配空间，1(VALUE_TURE)停止分配空间，-1表示该值不修改，可选入参*/
} T_ModifyThinVol;

/***************************************卷虚拟化结构体定义结束**************************************/

/***************************************Vd**************************************/
/*该结构体用的是slot id和enc id，另外blk需要的owner由SCS补充，所以blk不能直接使用该结构体*/
typedef struct
{
    CHAR     cVdName[MAX_BLK_NAME_LEN];  /*VD 名称,不能为空*/
    SWORD32  sdwVdRaidLevel;  /* eRaidlevel, RAID level, defined in struct eRaidlevel ,取值RAID0(0),RAID1(1),RAID3(3), RAID5(5),RAID6(6),
                                                   RAIDTP(7),RAID10(10),RAID30(30),RAID50(50),RAID60(60),NRAID(200),RAID_LEVEL_INVALID(0xffff) */
    SWORD32  sdwPdNum;                     /* 最大32 */
    T_PdId   tPdId[MAX_PD_NUM_IN_VD];      /* 磁盘信息列表 */
    SWORD32  sdwAutoRebuild;    /* 自动重建开关 ON自动重建，OFF不自动重建 */
} _PACKED_1_ T_CreateVd;

typedef struct
{
    CHAR     cVdName[MAX_BLK_NAME_LEN];         /* Vd 名称,不能为空 */
    SWORD32  sdwPdNum;                          /* 最大32 */
    SWORD32  sdwVdRaidLevel;                    /* Vd的raid级别 */
    SWORD32  sdwAutoRebuild;                    /* 自动重建开关 ON自动重建，OFF不自动重建 */
} _PACKED_1_ T_AutoCreateVd;

/* blk和SCS可以通用 */
typedef struct
{
    SWORD32  sdwVdNum;   /* 虚拟盘数目 */
    CHAR     cVdNames[MAX_VD_NUM_IN_SYS][MAX_BLK_NAME_LEN];    /*  所有虚拟盘name列表 */
} _PACKED_1_ T_AllVdNames;

/* blk与SCS可以通用 */
typedef struct
{
    CHAR     cVdName[MAX_BLK_NAME_LEN];    /*VD 名称,不能为空, 入参*/
    SWORD32  sdwVdRaidLevel;/* eRaidlevel, RAID level, defined in struct eRaidlevel ,取值RAID0(0),RAID1(1),RAID3(3), RAID5(5),RAID6(6),
                                                   RAIDTP(7),RAID10(10),RAID30(30),RAID50(50),RAID60(60),NRAID(200),RAID_LEVEL_INVALID(0xffff) */
    SWORD32  sdwFullPdNum;                  /*vd创建时,   即vd满配时,磁盘个数*/
    SWORD32  sdwPdNum;                      /*当前情况下VD 成员盘个数*/
    T_PdId   tPdId[MAX_PD_NUM_IN_VD];       /* 磁盘信息列表 */
    SWORD32  sdwAutoRebuild;                /* 自动重建开关ON(1)/OFF(0) */
    WORD64   sqwTotalCapacity;              /*  虚拟盘容量,单位KB */
    WORD64   sqwFreeCapacity;               /*  空闲容量,单位KB */
    WORD64   sqwMaxContiguousFreeSpace;     /*  最大连续空闲空间,单位KB */
    T_ScsTime   tCreateTime;                   /* Vd 创建时间 */
    SWORD32  sdwState;                      /* VD的状态信息,该值是需要按bit位解析，bit位置1表示有效，每bit位的表示的意义，
                                                     取值VD_GOOD(1)/VD_FAULT(2)/VD_DEGRADE(4)/VD_RECING(8)/VD_RECERR(16)/VD_SCSFAULT(32)/VD_SCSINITING(64)/VD_EXPANDING(128)/VD_RELEVELING(256) */
    SWORD32  local;                         /* local为0表示外来VD,local为1表示本地VD */
    SWORD32  sdwEnergyConsrv;               /* 节能模式,打开(1)/关闭(0)/不支持(2)  */
} _PACKED_1_ T_VdInfo;

typedef struct
{
    SWORD32  sdwPdNum;                     /* 磁盘数目，最大值:MAX_PD_NUM_IN_VD，入参*/
    T_PdId   tPdId[MAX_PD_NUM_IN_VD];      /* 磁盘信息列表，入参*/
} _PACKED_1_ T_VdDiskList;

typedef struct
{
    T_VdDiskList tVdDiskList;                  /* 磁盘信息列表，入参*/
    SWORD32      sdwConsistencyResult;          /* 磁盘一致性检查结果，取值：HDD_LIST_CONSISTENCY、HDD_LIST_NO_CONSISTENCY*/
} _PACKED_1_ T_CheckPdConsistency;

/* BLK与SCS可以通用 */
typedef struct
{
    CHAR     cVdName[MAX_BLK_NAME_LEN];    /*VD 名称,不能为空, 入参*/
    /* 待商量确定*/
    SWORD32  sdwTaskType;  /*任务类型*/
    T_ScsTime   tStartTime;  /* 开始时间  */
    SWORD32  sdwPercent;   /* 任务进度 */
    T_ScsTime   tFinishTime; /* 结束时间  */
    /* BYTE ucDelay;  */    /* reserved */
} _PACKED_1_ T_VdGetTaskInfo;

/* BLK与SCS应该不可以通用, blk需要的是设备号*/
typedef struct
{
    CHAR      cVdName[MAX_BLK_NAME_LEN];    /*VD 名称,不能为空, 入参*/
    SWORD32   sdwSpareHdNum;                /* 热备盘数目，入参*/
    T_PdId    tPdId[MAX_PD_NUM_ADD];          /* 磁盘信息列表 ，入参*/
} _PACKED_1_ T_VdRebuild; /* 虚拟盘重建（恢复）*/

/* blk与SCS可以通用 */
typedef struct
{
    CHAR    cVdName[MAX_BLK_NAME_LEN];  /*VD 名称,不能为空，入参*/
} _PACKED_1_ T_VdName;

typedef struct
{
    CHAR     cVdName[MAX_BLK_NAME_LEN];     /*VD 名称,不能为空，入参*/
    CHAR     cVdNewName[MAX_BLK_NAME_LEN];  /*待修改的VD 名称,不能为空，入参*/
} _PACKED_1_ T_VdRename;

/* blk与SCS可以通用 */
typedef struct
{
    CHAR    cVdName[MAX_BLK_NAME_LEN];  /*VD 名称,不能为空，入参*/
    SWORD32 sdwAutoRebuild;  /* 自动重建开关，ON(1)/OFF(0) ，入参*/
} _PACKED_1_ T_VdAutoRebuild;

/* blk与SCS不可以通用 上层是槽位号，blk是设备号*/
typedef struct
{
    CHAR       cVdName[MAX_BLK_NAME_LEN];  /*VD 名称,不能为空，入参*/
    SWORD32    sdwExpandType;              /*  增盘方式：1 按磁盘数目(VD_EXPAND_DISK_BY_NUM)；2 按磁盘列表(VD_EXPAND_DISK_BY_LIST)*/
    SWORD32    sdwAddPdNum;                /*  待增加磁盘数目，入参*/
    T_PdId     tPdId[MAX_PD_NUM_IN_VD];    /*  磁盘信息列表 ，可选入参*/
} _PACKED_1_ T_VdExpand;

/* SCS与blk可以通用 */
typedef struct
{

    CHAR    cVdName[MAX_BLK_NAME_LEN];  /*VD 名称,不能为空，，入参*/
    SWORD32 sdwVdRaidLevelNew;         /* 新的Raid级别 ，，入参*/
    SWORD32 sdwDefragFlg;              /* 变级的过程中是否整理碎片，ON-碎片整理，OFF-不进行碎片整理 ，可选入参*/
} _PACKED_1_ T_VdRelevel;

/***************************************Task**************************************/
/* 后台任务相关*/
typedef struct
{
    SWORD32    sdwTaskId;                              /*任务ID*/
    CHAR       cObjectName[MAX_TASK_OBJECT_NAME_LEN];  /*任务所属对象名*/
    WORD32     sdwTaskType;                            /* 任务类型,取值见宏定义*/
    SWORD32    sdwTaskState;                           /* 任务状态，取值TASK_RUNNING、TASK_PAUSE、TASK_DELAY*/
    T_ScsTime     tStartTime;                             /* 开始时间，年、月、日、时、分、秒*/
    SWORD32    sdwTaskProgress;                        /* 任务进度，整数，不带%*/
    SWORD32    sdwTaskAttr;                            /* 任务属性，按bit位表示，置位(1表示属性有效)有效，其中b0:可删除属性；b1:可暂停属性；b2:暂停后的可继续运行属性*/
} _PACKED_1_ T_TaskInfo;

typedef struct
{
    SWORD32 sdwTaskNum;           /*任务ID*/
    T_TaskInfo tTaskInfo[MAX_TASK_NUM_IN_SYS];    /*系统中所有后台任务列表*/
} _PACKED_1_ T_TaskInfoList;

typedef struct
{
    SWORD32 sdwTaskId;           /*任务ID*/
    SWORD32 sdwTaskCtrl;         /*后台任务操作，取值TASK_CTRL_RUN、TASK_CTRL_PAUSE、TASK_CTRL_DEL*/
} _PACKED_1_ T_TaskCtrl;

typedef struct
{
    CHAR        cObjectName[MAX_TASK_OBJECT_NAME_LEN];      /* 任务所属对象名,input */
    WORD32      sdwTaskType;                           /* 任务类型,取值见宏定义,input */
    SWORD32     sdwPrarmLen;                           /* 任务参数长度,input */
    CHAR        ucTaskPrarm[MAX_TASK_PRARM_LEN];       /* 任务所需参数,input */
} _PACKED_1_ T_TaskAddInfo;

/* 计划任务相关*/

typedef struct
{
    SWORD32 swTaskId;      //计划任务id号
    SWORD32 scTaskType;    //任务类型，参考eSchdTaskType定义
    CHAR    cObjectName[MAX_SCHEDULE_OBJECT_NAME_LEN];   //计划任务所属的对象名称
    T_ScsTime  tStartTime;  //任务启动时间
    T_ScsTime  tNextRunTime;  //任务下次运行时间
    SWORD32 sdwSchedPeriod; //计划任务的周期特性，取值SCHED_ONCE、SCHED_DAYLY、SCHED_WEEKLY、SCHED_MONTHLY
    CHAR    cTaskDescription[128];   // 计划任务简要描述
} _PACKED_1_ T_ScheduleTask;

typedef struct
{
    SWORD32 sdwNum; //计划任务数目
    T_ScheduleTask tScheduleTask[MAX_SCHEDULE_NUM]; //计划任务信息列表
} _PACKED_1_ T_ScheduleList;

typedef struct
{
    SWORD32 swTaskId; //计划任务id号，入参
} _PACKED_1_ T_ScheduleDel;

/***************************************Mirror**************************************/
#define MAX_UUID_LEN MAX_DEV_UUID_LEN+1
/* 创建远程镜像 */
typedef struct
{
    CHAR    scMirrorName[MAX_BLK_NAME_LEN];       /* 镜像名称 ，入参*/
    CHAR    scSrcVolName[MAX_BLK_NAME_LEN];       /* 镜像源卷名称 ，入参*/
    CHAR    ucRmtDiskUuid[MAX_UUID_LEN];          /* 镜像目的卷UUID,即远程磁盘UUID ，入参*/
    SWORD32 sdwMirrorType;                        /* 镜像的类型,取值：MIRROR_SYNCHRONOUS、MIRROR_ASYNCHRONOUS  ，入参*/
    SWORD32 sdwIsInitSync;                        /* 初始同步标记,取值：MIRROR_NOT_INIT_SYNC、MIRROR_IS_INIT_SYNC ，入参*/
    SWORD32 sdwPolicy;                            /* 镜像的同步策略,取值：MIRROR_MANUAL_POLICY、MIRROR_AUTO_POLICY，入参*/
    SWORD32 sdwPriority;                          /* 同步的优先级,取值：SYNC_LOW、SYNC_MEDIUM、SYNC_HIGH，入参*/
} _PACKED_1_ T_CreateMirror;

/* 远程镜像名称: 用于镜像删除、同步、分离等操作 */
typedef struct
{
    CHAR  scMirrorName[MAX_BLK_NAME_LEN];         /* 镜像名称 ,入参*/
    BYTE    ucIsAgent;                       /* 默认为0， 1代表不使用主机代理，直接分离ec611004112711 修改*/
} _PACKED_1_ T_MirrorName;

/* 远程镜像信息 */
typedef struct
{
    CHAR    scMirrorName[MAX_BLK_NAME_LEN];       /* 镜像名称 ，入参*/
    CHAR    scSrcVolName[MAX_BLK_NAME_LEN];       /* 镜像源卷名称 */
    CHAR    scRmtDiskUuid[MAX_DEV_UUID_LEN];      /* 目的卷UUID --- 界面不再显示该项 */
    SWORD64 sdwDestVolCap;                        /* 镜像卷容量 KB */
    CHAR    ucRmtTgtName[RMT_TARGET_NAME_LEN];    /* 远端设备名称,出参，目的卷为远端盘时有效 */
    SWORD32 sdwLunId;                             /* 目的卷的Lun Id 信息*/
    SWORD32 sdwMirrorType;                        /* 镜像的类型,取值：MIRROR_SYNCHRONOUS、MIRROR_ASYNCHRONOUS  */
    SWORD32 sdwInitSync;                          /* 初始同步标记,取值：MIRROR_NOT_INIT_SYNC、MIRROR_IS_INIT_SYNC */
    SWORD32 sdwPolicy;                            /* 镜像的同步策略,取值：MIRROR_MANUAL_POLICY、MIRROR_AUTO_POLICY*/
    SWORD32 sdwPriority;                          /* 同步的优先级: 见SYNC_LOW、SYNC_MEDIUM、SYNC_HIGH*/
    /* 镜像状态, 取值:
     * VAS_MIRROR_STATUS_INIT        初始态(0)
     * VAS_MIRROR_STATUS_FRACTUR     分离(1)
     * VAS_MIRROR_STATUS_CONSIS      数据一致(2)
     * VAS_MIRROR_STATUS_SYNCING     正在同步(3)
     * VAS_MIRROR_STATUS_TASK_DELAY     任务延期，只显示给页面查看使用。4是30版本的延迟同步(5)
     * VAS_MIRROR_STATUS_FAULT           源卷故障未恢复 (6)
     */
    SWORD32 sdwState;
    SWORD32 sdwTaskProcess;                       /* 镜像同步进度 百分比 */
    SWORD32 sdwOwnerCtrlId;                       /* 归属控制器ID */
    T_ScsTime tCreateTime;                        /* 镜像创建时间 */
    T_ScsTime tTaskStartTime;                     /* 镜像同步开始时间 */
    T_ScsTime tTaskEndTime;                       /* 镜像同步结束时间 */
} _PACKED_1_ T_MirrorInfo;

/* 修改远程镜像名称  */
typedef struct
{
    CHAR    scMirrorName[MAX_BLK_NAME_LEN];        /* 镜像名称，入参*/
    CHAR    scMirrorNewName[MAX_BLK_NAME_LEN];     /* 镜像新名称 ，入参*/
} _PACKED_1_ T_MirrorRename;

/* 修改远程镜像同步策略 */
typedef struct
{
    CHAR    scMirrorName[MAX_BLK_NAME_LEN];     /* 镜像名称 ，入参*/
    SWORD32 sdwPolicy;                          /* 镜像的同步策略,取值：MIRROR_MANUAL_POLICY、MIRROR_AUTO_POLICY，，入参*/
} _PACKED_1_ T_MirrorPolicy;

/* 修改远程镜像同步优先级  */
typedef struct
{
    CHAR    scMirrorName[MAX_BLK_NAME_LEN];     /* 镜像名称 ，入参*/
    SWORD32 sdwPriority;                        /* 同步的优先级: 见SYNC_LOW、SYNC_MEDIUM、SYNC_HIGH，入参*/
} _PACKED_1_ T_MirrorPriority;

typedef struct
{
    CHAR    scMirrorName[MAX_BLK_NAME_LEN];       /* 镜像名称 ，入参*/
    CHAR    scSrcVolName[MAX_BLK_NAME_LEN];       /* 镜像源卷名称 */
    SWORD64 sdwMirrorCap;                         /* 镜像卷容量 KB */
    SWORD32 sdwMirrorType;                        /* 镜像的类型,取值：MIRROR_SYNCHRONOUS、MIRROR_ASYNCHRONOUS  */
    SWORD32 sdwState;                             /* 镜像状态, 取值：INIT ~ OUT_OF_INIT*/
    T_ScsTime tCreateTime;                        /* 镜像创建时间 */
} _PACKED_1_ T_MirrOverViewInfo;

/* 所有镜像名称列表 */
typedef struct
{
    SWORD32 sdwMirrorNum;                    /* 镜像数目 */
    T_MirrOverViewInfo tMirrorInfo[MAX_MIRROR_IN_SYS];  /* 镜像概要信息列表 */
} _PACKED_1_ T_AllMirrorList;

/* 远程镜像简要信息*/
typedef struct
{
    CHAR    scMirrorName[MAX_BLK_NAME_LEN];       /* 镜像名称 ，入参*/
    CHAR    scSrcVolName[MAX_BLK_NAME_LEN];       /* 镜像源卷名称 */
    SWORD32 sdwMirrorType;                        /* 镜像的类型,取值：MIRROR_SYNCHRONOUS、MIRROR_ASYNCHRONOUS  */
    /* 镜像状态, 取值:
     * VAS_MIRROR_STATUS_INIT        初始态(0)
     * VAS_MIRROR_STATUS_FRACTUR     分离(1)
     * VAS_MIRROR_STATUS_CONSIS      数据一致(2)
     * VAS_MIRROR_STATUS_SYNCING     正在同步(3)
     * VAS_MIRROR_STATUS_TASK_DELAY     任务延期，只显示给页面查看使用。4是30版本的延迟同步(5)
     * VAS_MIRROR_STATUS_FAULT           源卷故障未恢复 (6)
     */
    SWORD32 sdwState;
} _PACKED_1_ T_MirrorBriefInfo;
/*************************************Consistency Group**********************************/
/*远程镜像一致性组*/
typedef struct
{
    WORD32 dwSucceededNum;/* 添加成功的镜像个数 */
    CHAR   MirrorSucList[MAX_MIRROR_NUM_IN_CG][MAX_BLK_NAME_LEN];/* 添加成功的镜像列表 */
    WORD32 dwFailedNum;/* 添加失败的镜像个数 */
    CHAR   MirrorFailedList[MAX_MIRROR_NUM_IN_CG][MAX_BLK_NAME_LEN];/* 添加失败的镜像列表 */
} _PACKED_1_  T_CreateCGMirrorRes;
typedef struct
{
    CHAR     scCGName[MAX_BLK_NAME_LEN];
    SWORD32  sdwMirrorNum;                           /*一致性组镜像数量*/
    CHAR     MirrorList[MAX_MIRROR_NUM_IN_CG][MAX_BLK_NAME_LEN];
    BYTE      ucPriority;                                  /* 优先级，0：低；1：中；2：高 */
    BYTE      ucPolicy;                                   /* 故障恢复策略；0：自动；1：手动，取值CG_FAULT_RESCUR_POLICY_AUTO、CG_FAULT_RESCUR_POLICY_MANUAL */
    BYTE      ucSyncType;                            /*复制类型；0：同步；1：异步； */
    T_CreateCGMirrorRes tCreateRes;
} _PACKED_1_ T_CreateCGMirror;

typedef struct
{
    CHAR     scMirrorName[MAX_BLK_NAME_LEN];       /* 镜像名称*/
    CHAR     scSrcVolName[MAX_BLK_NAME_LEN];       /* 镜像源卷名称 */
    CHAR     scRmtDiskUuid[MAX_DEV_UUID_LEN];      /*远端磁盘uuid*/
    SWORD64  sqwRmtDiskCap;                        /* 远程磁盘的容量,KB */
    SWORD64  sqwSrcMirrorCap;                      /* 镜像源卷容量 KB */
    SWORD32  sdwMirrorType;                        /* 远程镜像的类型,取值：MIRROR_SYNCHRONOUS、MIRROR_ASYNCHRONOUS  */
} _PACKED_1_ T_MirrViewInfoInCGrp;

typedef struct
{
    CHAR    scCGName[MAX_BLK_NAME_LEN];   /*一致性组名称 入参*/
    SWORD32 sdwMirrorNum;               /*一致性组镜像数量*/
    T_MirrViewInfoInCGrp  tMirrorInfo[MAX_MIRROR_NUM_IN_CG];    /*MAX_MIRROR_NUM_IN_CG 8*/
} _PACKED_1_ T_MirrorInfoInCGrp;

typedef struct
{
    CHAR      scCGName[MAX_BLK_NAME_LEN];           /*一致性组名称*/
    BYTE      ucPriority;                           /* 复制优先级，0：低；1：中；2：高 */
    BYTE      ucPolicy;                             /* 故障恢复策略；0：自动；1：手动； */
    BYTE      ucSyncType;                           /* 复制类型；0：同步；1：异步； */
    WORD32    dwStatus;                             /* 一致性组状态，参考宏 一致性组状态宏值*/
    WORD32    dwPercent;                            /* 任务完成百分比，没有任务填写0*/
    T_ScsTime tCreateTime;                          /* 创建时间 */
} _PACKED_1_ T_CGMirrorOverViewInfo;

typedef struct
{
    CHAR   scCGName[MAX_BLK_NAME_LEN];
} _PACKED_1_ T_CGMirrorName;

typedef struct
{
    SWORD32 sdwCGMirrorNum;
    T_CGMirrorOverViewInfo tCGMirrorInfo[MAX_MIRROR_NUM_IN_CG];
} _PACKED_1_ T_AllCGMirrorList;

typedef struct
{
    CHAR   scCGName[MAX_BLK_NAME_LEN];          /*一致性组名称*/
    CHAR   scMirrorname[MAX_BLK_NAME_LEN];     /* 镜像名 */
} _PACKED_1_ T_MirrorInCGrp;

/*用于添加镜像到一致性组，根据一致性组名获取符合条件的镜像*/
typedef struct
{
    CHAR        scCGName[MAX_BLK_NAME_LEN];        /*入参*/
    SWORD32     sdwMirrorNum;                      /* 镜像数目 */
    T_MirrorBriefInfo tMirrInfo[MAX_MIRROR_NUM];   /*同步镜像数量 + 异步镜像数量*/
} _PACKED_1_ T_CGFilterMirrorList;

/*根据过滤条件获取镜像,用于创建一致性组镜像*/
typedef struct
{
    BYTE      ucPriority;                                  /* 优先级，0：低；1：中；2：??入参 */
    BYTE      ucPolicy;                                   /* 故障恢复策略；0：自动；1：手动, 入参，取值CG_FAULT_RESCUR_POLICY_AUTO、CG_FAULT_RESCUR_POLICY_MANUAL */
    BYTE      ucSyncType;                            /*复制类型；0：同步；1：异步； 入参*/
    SWORD32     sdwMirrorNum;                              /* 镜像数目 */
    T_MirrorBriefInfo tMirrInfo[MAX_MIRROR_NUM];
} _PACKED_1_ T_MirrorFilterList;

/* 修改镜像一致性组名称  */
typedef struct
{
    CHAR    scCGName[MAX_BLK_NAME_LEN];         /* 一致性组名称，入参*/
    CHAR    scCGNewName[MAX_BLK_NAME_LEN];      /* 一致性组新名称 ，入参*/
} _PACKED_1_ T_CGMirrorRename;

/* 修改镜像一致性组优先级*/
typedef struct
{
    CHAR    scCGName[MAX_BLK_NAME_LEN];      /* 一致性组名称，入参*/
    BYTE     ucPriority;                        /* 复制优先级，0：低；1：中；2：高 ，入参*/
} _PACKED_1_ T_CGMirrorPriority;

/* 修改镜像一致性组故障恢复策略*/
typedef struct
{
    CHAR    scCGName[MAX_BLK_NAME_LEN];      /* 一致性组名称，入参*/
    BYTE      ucPolicy;                  /* 故障恢复策略；1：自动；0：手动，取值CG_FAULT_RESCUR_POLICY_AUTO、CG_FAULT_RESCUR_POLICY_MANUAL ，入参*/
} _PACKED_1_ T_CGMirrorPolicy;

/* 修改镜像一致性组中镜像类型*/
typedef struct
{
    CHAR    scCGName[MAX_BLK_NAME_LEN];      /* 一致性组名称，入参*/
    BYTE      ucSyncType;                  /* 复制类型；0：同步；1：异步；入参 */
} _PACKED_1_ T_CGMirrorSyncType;

typedef struct
{
    CHAR   scCGName[MAX_BLK_NAME_LEN];      /* 一致性组对象名*/
    WORD32 udwVasObjType;                   /* 增值对象类型，取值：1（VAS_OBJ_MIRROR_TYPE）、2（VAS_OBJ_SNAP_TYPE ）、3（VAS_OBJ_CLONE_TYPE ）*/
    BYTE   ucIsAgent;                       /* 默认为0， 1代表不使用主机代理，对齐之前611004112711 的修改*/
} _PACKED_1_ T_ConsistencyGrpName;

typedef struct
{
    T_ConsistencyGrpName tConsistencyGrpName; /* 一致性组名称信息*/
    WORD32 udwSyncType;                        /* 同步方式，取值：1（VAS_SYNC_TYPE），2（VAS_SYNC_INC_TYPE）*/
} _PACKED_1_ T_ConsistencyGrpSync;

/************************************* remote copy **************************************/
/* 远程复制目标卷的添加 */
typedef struct
{
    WORD32  dwDstVolNum;                                              /* 用户添加的目标卷数目 */
    CHAR    scRCopyName[MAX_BLK_NAME_LEN];                            /* 远程复制名称,入参*/
    CHAR    scDestVolName[MAX_DST_VOL_IN_RCOPY][MAX_BLK_NAME_LEN];    /* 目标卷名，有名字时填写 */
    CHAR    scDestUuid[MAX_DST_VOL_IN_RCOPY][MAX_UUID_LEN];           /* 目标卷UUID */
    BYTE    ucDstIsRemote[MAX_DST_VOL_IN_RCOPY];                      /* 目标卷是否为远端盘, 1:远端盘 0:本地卷 */
    SWORD32 sdwDestAddResult[MAX_DST_VOL_IN_RCOPY];                   /* 每个目标卷的添加结果,0:成功, 非0:失败 */
} _PACKED_1_ T_AddRCopyDestVol;

/* 远程复制目标卷的删除 */
typedef struct
{
    CHAR    scRCopyName[MAX_BLK_NAME_LEN];      /* 远程复制名称,入参*/
    CHAR    scDestVolName[MAX_BLK_NAME_LEN];    /* 目标卷名，有名字时填写 */
    CHAR    scDestUuid[MAX_UUID_LEN];           /* 目标卷UUID */
    BYTE    ucDstIsRemote;                      /* 目标卷是否为远端盘, 1:远端盘 0:本地卷 */
} _PACKED_1_ T_RCopyDestVol;

/* 创建远程复制 */
typedef struct
{
    CHAR    cReCopyName[MAX_BLK_NAME_LEN];        /* 远程复制名称,入参 */
    CHAR    cSrcVolName[MAX_BLK_NAME_LEN];        /* 复制源卷名称,入参 */
    CHAR    ucSrcRmtDiskUuid[MAX_UUID_LEN];       /* 复制源卷UUID,源卷为远端盘时填写,入参 */
    BYTE    ucSrcIsRemote;                        /* 源卷是否为远端盘, 1:远端盘 0:本地卷 */
    BYTE    ucSyncPolicy;                         /* 同步策略,0：自动；1：手动 ----不对用户暴露该项输入,界面不再显示 */
    BYTE    ucSyncSpeed;                          /* 同步的优先级，0：低；1：中；2：高；3：最快,入参 */
    BYTE    ucRCopyType;                          /* 复制类型；0：全量；1：增量,入参 */
    BYTE    ucRCopyInitSync;                      /* 当增量同步时有效,是否需要初始同步。NOT_INIT_SYNC(0),IS_INIT_SYNC(1) */
    T_AddRCopyDestVol tAddDRCopyDestVol;          /* 添加目标卷 */
} _PACKED_1_ T_CreateReCopy;

/* 远程复制名称: 用于删除、同步、分离等操作 */
typedef struct
{
    CHAR  cReCopyName[MAX_BLK_NAME_LEN];         /* 远程复制名称 ,入参 */
} _PACKED_1_ T_ReCopyName;

/* 远程复制信息 */
typedef struct
{
    CHAR     cReCopyName[MAX_BLK_NAME_LEN];        /* 远程复制名称,入参 */
    CHAR     cSrcVolName[MAX_BLK_NAME_LEN];        /* 复制源卷名称,本地卷有效 */
    CHAR     ucSrcRmtDiskUuid[MAX_DEV_UUID_LEN];   /* 复制源卷UUID ----界面不再显示该项 */
    CHAR     ucSrcRmtTgtName[RMT_TARGET_NAME_LEN]; /* 复制源卷远端设备名称,源卷为远端盘时有效 */
    SWORD32  sdwSrcLunId;                          /* 复制源卷远程磁盘在所在映射组中的Lun Id 信息,源卷为远端盘时有效 */
    SWORD32  sdwSrcVolDev;                         /* 远程复制源卷的设备号*/
    BYTE     ucIsRemoteLun;                        /* 源卷是否为远端盘 */
    BYTE     ucSyncSpeed;                          /* 同步的优先级，0：低；1：中；2：高；3：最快,SYNC_LOW、SYNC_MEDIUM、SYNC_HIGH*/
    BYTE     ucRCopyType;                          /* 复制类型；0：全量, 1：增量 */
    BYTE     ucSyncPolicy;                         /* 同步策略；0：自动；1：手动,取值：MANUAL_POLICY、AUTO_POLICY ----界面上不显示该项 */
    BYTE     ucRCopyInitSync;                      /* 当增量同步时有效,是否初始同步。NOT_INIT_SYNC(0),IS_INIT_SYNC(1) ---如果是全量同步，界面不显示该项 */
    SWORD64  qwOriginCapacity;                     /* 源卷的容量 KB */
    SWORD32  sdwOwnerCtrl;                         /* 主控制器ID */
    WORD32   dwDestVolNum;                         /* 目标卷个数 */
    WORD32   sdwStatus;                            /* 远程复制状态: 0  待拷贝,1  正在拷贝,2  暂停,3  停止,4  拷贝完成,5  故障 */
    WORD32   sdwPercent;                           /* 任务完成百分比，没有任务填写0 */
    SWORD32  sdwTaskProcess;                       /* 同步进度 百分比 */
    T_ScsTime tCreateTime;                         /* 远程复制创建时间 */
    T_ScsTime tSetFlagTime;                        /* 上次设置标记时间 */
    T_ScsTime tTaskStartTime;                      /* 远程复制开始时间 */
    T_ScsTime tTaskEndTime;                        /* 远程复制结束时间 */
} _PACKED_1_ T_ReCopyInfo;

typedef struct
{
    CHAR    scRCopyName[MAX_BLK_NAME_LEN];        /* 远程复制名称,入参*/
    CHAR    scSrcVolName[MAX_BLK_NAME_LEN];       /* 源卷名称 */
    SWORD32 sdwState;                             /* 状态, 取值：0 ~ 5*/
    BYTE    ucSyncSpeed;                          /* 同步的优先级，0：低；1：中；2：高；3：最快,SYNC_LOW、SYNC_MEDIUM、SYNC_HIGH*/
    BYTE    ucRCopyType;                          /* 复制类型；0：全量, 1：增量 */
    BYTE    ucSyncPolicy;                         /* 同步策略；0：自动；1：手动,取值：MANUAL_POLICY、AUTO_POLICY */
    BYTE    ucInitSync;                           /* 初始同步；0：否；1：是 */
    T_ScsTime tCreateTime;                        /* 创建时间 */
} _PACKED_1_ T_RCopyOverViewInfo;

/* 所有远程复制名称列表 */
typedef struct
{
    SWORD32 sdwRCopyNum;                                /* 远程复制数目 */
    T_RCopyOverViewInfo tRCopyInfo[MAX_COPY_IN_SYS];    /* 远程复制概要信息列表 */
} _PACKED_1_ T_AllRCopyList;

/* 修改远程复制名称  */
typedef struct
{
    CHAR    scRCopyName[MAX_BLK_NAME_LEN];         /* 远程复制名称，入参*/
    CHAR    scRCopyNewName[MAX_BLK_NAME_LEN];      /* 远程复制新名称 ，入参*/
} _PACKED_1_ T_RCopyRename;

/* 修改远程复制速率 */
typedef struct
{
    CHAR    scRCopyName[MAX_BLK_NAME_LEN];      /* 远程复制名称,入参*/
    BYTE    ucSyncSpeed;                        /* 同步的优先级，0：低；1：中；2：高；3：最快,SYNC_LOW、SYNC_MEDIUM、SYNC_HIGH,入参*/
} _PACKED_1_ T_RCopySyncSpeed;

/* 修改远程复制同步策略 */
typedef struct
{
    CHAR    scRCopyName[MAX_BLK_NAME_LEN];      /* 远程复制名称,入参*/
    BYTE    ucSyncPolicy;                       /* 同步策略；0：自动；1：手动,取值：MANUAL_POLICY、AUTO_POLICY,入参*/
} _PACKED_1_ T_RCopyPolicy;

/* 修改远程复制类型 */
typedef struct
{
    CHAR    scRCopyName[MAX_BLK_NAME_LEN];      /* 远程复制名称,入参*/
    BYTE    ucType;                             /* 复制类型；0：全量；1：增量,入参*/
} _PACKED_1_ T_RCopyType;

/* 查询一个远程复制下所有目标卷信息 */
typedef struct
{
    CHAR      scDestVolName[MAX_BLK_NAME_LEN];       /* 目标卷名,出参 */
    CHAR      scDestUuid[MAX_UUID_LEN];              /* 目标卷UUID,出参 --- 界面不再显示该项 */
    CHAR      ucDestRmtTgtName[RMT_TARGET_NAME_LEN]; /* 复制源卷远端设备名称,源卷为远端盘时有效 */
    SWORD32   sdwDestLunId;                          /* 复制源卷远程磁盘在所在映射组中的Lun Id 信息,源卷为远端盘时有效 */
    BYTE      ucDstIsRemote;                         /* 目标卷是否为远端盘, 1:远端盘 0:本地卷,出参 */
    SWORD32   sdwDestVolDev;                         /* 远程复制目的卷的设备号,出参 */
    T_ScsTime tCreateTime;                           /* 目标卷创建时间 */
} _PACKED_1_ T_RCopyDestVolInfo;

typedef struct
{
    CHAR    scRCopyName[MAX_BLK_NAME_LEN];      /* 远程复制名称,入参*/
    WORD16  wRCopyDestNum;                      /* 复制中目标卷的个数,出参*/
    T_RCopyDestVolInfo  RCopyDestVolInfo[MAX_RCOPY_NUM_IN_VOL];
} _PACKED_1_ T_DestVolInRCopy;

/************************ 私有卷呈现功能 *********************/

/* 私有卷信息 */
typedef struct
{
    CHAR      scPriVolName[MAX_BLK_NAME_LEN];    /* 私有卷名称 */
    SWORD64   sqwPriVolCap;                      /* 私有卷容量, 单位(KB) */
    SWORD32   sdwState;                          /* 私有卷状态, 取值: 取值VOL_S_GOOD(0),
                                                    VOL_S_FAULT(1),  VOL_S_ERR(2),VOL_S_CHUNKSIZE_MIGRATION(3),
                                                    VOL_S_EXPAND(4),VOL_S_UNREADY(5),VOL_S_READONLY(12), VOL_S_INVALID(0xffff) */
    SWORD32   sdwOwnerCtrlId;                    /* 私有卷归属控制器ID, 取值0或1 */
    WORD32    dwUsedStatus;                      /* 私有卷使用情况, 取值: PRI_VOL_UNUSED(1)和PRI_VOL_USED(2) */
    T_ScsTime tCreateTime;                       /* 私有卷创建时间 */
} _PACKED_1_ T_PriVolInfo;

/* 系统中私有卷列表 */
typedef struct
{
    SWORD32      sdwPriVolNum;
    T_PriVolInfo tPriVolInfo[MAX_PVOL_NUM_IN_SYS];
} _PACKED_1_ T_PriVolList;

/* 删除私有卷 */
typedef struct
{
    CHAR scPriVolName[MAX_BLK_NAME_LEN];
} _PACKED_1_ T_DelPriVol;

/*FC 方式的 镜像逻辑连接 modify by liutt */
typedef struct
{
    SWORD32  sdwCtrlId;                   /* 控制器ID，入参*/
    BYTE     ucWWPN[MAX_FC_WWN_LENGTH];  /* WWPN ，入参*/
    WORD64    qwBandWidth;         /* 主机配置和远端设备配置优化功能需求和方案带宽,单位:MB/s */
    CHAR      aRmtTgtName[RMT_TARGET_NAME_LEN];    //远端设备名称
    SWORD32  sdwSlotId;                  /* new_槽位号 */
} _PACKED_1_ T_FcMirrorConnectInfo;

typedef struct
{
    T_FcMirrorConnectInfo   tFcMirrorConnect;    /* 远程镜像FC方式的 连接信息 */
    SWORD32 sdwFcNexusStatus;                      /* 连接状态，PORT_STATE_UP、PORT_STATE_DOWN*/
} _PACKED_1_ T_FcNexusInfo;

/* 所有镜像链接 */
typedef struct
{
    SWORD32  sdwFcConnectNum;                                                    /* 以FC方式的镜像连接数目 ，出参*/
    T_FcNexusInfo   tFcMirrorConnectInfo[MAX_MIRROR_CONNECT_NUM];        /* 以FC方式的镜像连接信息 ，出参*/
    /*待支持ISCSI方式后再做添加*/
    //SWORD32  sdwIscsiConnectNum;                                               /* 以Iscsi方式的镜像连接数目 ，出参*/
    //T_IscsiMirrorConnectInfo  tIscsiMirrorConnectInfo[MAX_MIRROR_CONNECT_NUM]; /* 以Iscsi方式的镜像连接信息 ，出参*/
} _PACKED_1_ T_MirrorConnectList;

typedef struct
{
    SWORD32  sdwRmtLinkType;                                                          /* 远程连接方式，取值：0（REMOTE_LINK_BY_FC）、1（REMOTE_LINK_BY_ISCSI）*/
    //SWORD32  sdwRmtPathNum;                                                           /* 远程磁盘路径数目*/
    //BYTE     ucRmtDiskPathName[MAX_REMOTE_DISK_PATH_NUM][MAX_REMOTE_DEVICE_NAME_LEN]; /* 远端磁盘路径列表，数组前sdwRmtPathNum元素有效，当sdwRmtLinkType值为1（REMOTE_LINK_BY_FC）时，为WWPN信息*/
    WORD64   qwBandWidth;                                                             /* 主机配置和远端设备配置优化功能需求和方案带宽,单位:MB/s */
    CHAR     aRmtTgtName[RMT_TARGET_NAME_LEN];                                        /* 远端设备名称 */
} _PACKED_1_ T_RemoteLinkInfo;

typedef struct
{
    CHAR     ucRmtDiskUuid[MAX_UUID_LEN];                 /* 远程磁盘UUID */
    SWORD32  sdwUsedFlag;                                 /* 远端磁盘的使用标志 ，取值REMOTE_DISK_UNUSED、REMOTE_DISK_USED*/
    SWORD32  sdwLunId;                                    /* 远端磁盘在所在映射组中的Lun Id 信息 */
    SWORD64  sqwCapacity;                                 /* 远端磁盘的容量,KB */
    T_RemoteLinkInfo tRmtLinkInfo;                        /* 远端磁盘的链路信息 */
    SWORD32  sdwRemoteDiskState;                          /* 远程磁盘的状态信息，取值 0(正常)、1(异常) */
} _PACKED_1_ T_RemoteDiskInfo;

typedef struct
{
    SWORD32          sdwRmtDiskNum;                                             /* 远程磁盘数目 ，出参*/
    T_RemoteDiskInfo tRmtDiskInfo[MAX_MIRROR_REMOTE_DISK_NUM];                  /* 远程磁盘信息列表，前sdwRmtDiskNum元素有效 ，出参*/
} _PACKED_1_ T_RemoteDiskList;

/* FC 端口信息 modify by liutt */
typedef struct
{
    WORD32  udwPortType;                              /* 端口类型，取值: 1(BUSINESS_PORT_TYPE_FC)、2(BUSINESS_PORT_TYPE_FCOE)*/
    WORD32  sdwPortNo;                                /* 端口编号,按FC接口面板顺序进行,从1开始编号 */
    WORD32  udwPortStatus;                            /* 标识该FC端口是否有效,取值:FC_PORT_INVALID 、FC_PORT_VALID ;当取值为FC_PORT_INVALID时，除了sdwPortNo值有效外，其他属性值均无效  */
    BYTE    ucPortID[MAX_FC_PORT_ID_LENGTH];          /* 端口ID,FC协议生成,显示方式三个字节按照16进制依次显示，形如为0x123456      */
    WORD32  udwPortRate;                              /* 端口速率，取值：FC_PORT_SPEED_INVALID、FC_PORT_SPEED_2G、FC_PORT_SPEED_4G、FC_PORT_SPEED_8G.*/
    WORD32  udwLinkStatus;                            /* 链路状态，取值：PORT_STATE_INVALID、PORT_STATE_UP、PORT_STATE_DOWN*/
    WORD32  udwTopoType;                              /* 端口拓扑类型：FC_TOPO_INVALID、FC_TOPO_PRIVATE_LOOP、FC_TOPO_PUBLIC_LOOP、FC_TOPO_FABRIC、FC_TOPO_P2P*/
    BYTE    ucWwpn[MAX_FC_WWN_LENGTH];                /* 端口WWPN，输出格式 A1：A2：A3：A4：A5：A6：A7：A8, 全0值无效*/
    WORD32  sdwSlotNo;                                /* new_槽位号:1--4 */
} _PACKED_1_ T_FcPortInfo;

/* 每个控制器上FC 端口的信息 */
typedef struct
{
    WORD32  sdwCtrlId;                          /* 端口所在的控制器ID */
    BYTE ucWwnn[MAX_FC_WWN_LENGTH];            /* 端口所在单板的WWNN */
    WORD32  PortNum;                           /* 端口数目，fcoe有2个口，fc有4个口 *////num
    T_FcPortInfo tFcPortInfo[MAX_FC_PORT_NUM]; /* FC接口信息结构,每个端口占用一个数组条目 */
} _PACKED_1_ T_FcPortInfoPerCtrl;

/* 系统中所有FC 端口的信息 */
typedef struct
{
    WORD32             udwCtrlNum;                             /*环境中Ctrl控制器数量*/
    T_FcPortInfoPerCtrl tFcPortInfoPerCtrl[MAX_CTL_NUM];       /*FC端口信息列表*/
} _PACKED_1_ T_FcPortInfoList;

/* 获取控制器上，FC子卡所在槽位 2014/12/11 */
/* 端口信息 */
typedef struct
{
    WORD32 dwPortType;      /* 端口类型 出参 */
    WORD32 dwPortNo;        /* 端口号 */
} T_FcPort;
/* 有效槽位号 */
typedef struct
{
    WORD32  dwSlotNo;       /* 有效槽位号 出参 */
    SWORD32 sdwPortNum;   /* 端口数 */
    T_FcPort tFcPort[8];
} T_CardFcPortList;
/* 控制器 */
typedef struct
{
    WORD32  dwCtrlId;          /* 控制器号 出参 */
    SWORD32 sdwFcCardNum;
    T_CardFcPortList tCardFcPortList[MAX_CARD_SLOT_NUM];
} T_CtrlFcPortList;
typedef struct
{
    SWORD32 sdwCtrlNum;
    T_CtrlFcPortList tCtrlFcPortList[2];
} T_FcPortList;

typedef struct
{
    BYTE ucHostPortWwpn[FC_WWN_LENGTH];
} T_FcHostPortName;

typedef struct
{
    SWORD32 sdwHostPortNum;
    T_FcHostPortName tFcHostPortName[MAX_FC_HOST_PORT_NUM];
} T_FcHostPortList;

/***************************************STS*************************************/

typedef struct
{
    SWORD32 sdwLunId;  /* Lun的本地Id, int型值，组内唯一 */
    CHAR    cVolName[MAX_BLK_NAME_LEN]; /* Vol/Svol名称,不能为空*/
    SWORD32 sdwBlockSize;   /* 数据块大小，取值范围512,512*2,512*4,512*8 */
    SWORD32 sdwAccessAttr;  /* 只读 or 读写 */
    SWORD32 sdwLunState; /* lun 的状态 */
} _PACKED_1_ T_LunInfo;

typedef struct
{
    CHAR      cMapGrpName[MAX_MAPGRP_NAME_LEN]; /* 映射组名称,不能为空,入参*/
    T_LunInfo tLunInfo;                              /*Lun相关的信息，入参*/
} _PACKED_1_ T_AddVolToGrp;

typedef struct
{
    CHAR     cMapGrpName[MAX_MAPGRP_NAME_LEN]; /* Vol的所属MapGrp名称,入参*/
    SWORD32  sdwLunId;       /* Lun的本地Id，映射组内唯一 ,入参*/
} _PACKED_1_ T_DelVolFrmGrp;

/* 2010-12-02    xygang  */
typedef struct
{
    CHAR  ucHostName[MAX_INI_NAME_LEN];
    /* CHAP鉴权时Host用户名和密码 */
} _PACKED_1_ T_HostInfo;

/* 2010-12-02    xygang  */
typedef struct
{

    CHAR        cMapGrpName[MAX_MAPGRP_NAME_LEN]; /* 映射组名称,不能为空,入参*/
    SWORD32     sdwLunNum;     /* 逻辑单元个数*/
    T_LunInfo   tLunInfo[MAX_LUN_NUM_IN_MAP_GROUP];     /*Lun相关的信息*/
    SWORD32     sdwHostNum;    /* 主机的个数 */
    T_HostInfo  tHostInfo[MAX_HOST_NUM_IN_MAP_GRP];
} _PACKED_1_ T_MapGrpInfo;

typedef struct
{
    CHAR    ucInitName[MAX_INI_NAME_LEN];     /* 主机名 */
    CHAR    cMapGrpName[MAX_MAPGRP_NAME_LEN]; /* 映射组名称*/
} _PACKED_1_ T_HostInGrp;

typedef struct
{
    SWORD32  sdwMapGrpNum;    /* 系统中映射组数目 */
    CHAR     cMapGrpNames[MAX_MAP_GROUP_NUM_IN_SYS][MAX_MAPGRP_NAME_LEN]; /* 所有映射组名称列表*/
} _PACKED_1_ T_AllGrpNames;

typedef struct
{
    CHAR        cMapGrpName[MAX_MAPGRP_NAME_LEN]; /* 映射组名称,不能为空,入参*/
    SWORD32     sdwLunNum;                        /* 映射组中逻辑单元数目*/
    SWORD32     sdwHostNum;                       /* 映射组中主机数目 */
} _PACKED_1_ T_MapGrpSimpleInfo;

typedef struct
{
    SWORD32                sdwMapGrpNum;                                /* 系统中映射组数目 */
    T_MapGrpSimpleInfo     tMapGrpSimpleInfo[MAX_MAP_GROUP_NUM_IN_SYS]; /* 所有映射组简要信息列表*/
} _PACKED_1_ T_AllGrpSimpleInfo;

typedef struct
{
    CHAR      cMapGrpName[MAX_MAPGRP_NAME_LEN]; /* 映射组名称，入参*/
} _PACKED_1_ T_MapGrpName;

typedef struct
{
    CHAR     cMapGrpName[MAX_MAPGRP_NAME_LEN]; /* 映射组名称，入参*/
    CHAR     cMapGrpNewName[MAX_MAPGRP_NAME_LEN]; /* 映射组新名称，入参*/
} _PACKED_1_ T_MapGrpRename;

typedef struct
{
    CHAR      cVolName[MAX_BLK_NAME_LEN]; /* Vol/Svol名称,不能为空,入参*/
    SWORD32   sdwMapGrpNum;
    CHAR      cMapGrpNames[MAX_MAP_GROUP_NUM_IN_SYS][MAX_MAPGRP_NAME_LEN]; /* 映射组名称列表*/
    SWORD32   sdwLunLocalId[MAX_MAP_GROUP_NUM_IN_SYS];                     /* Lun所在映射组中的Lun局部Id*/
} _PACKED_1_ T_GrpNameByVol;

typedef struct
{
    //SWORD32 sdwCtrlId;        /* 控制器Id ,暂时定义为0、1，对应的宏定义CTRL0、CTRL1*/
    CHAR     cMapGrpName[MAX_MAPGRP_NAME_LEN]; /* 映射组名称，入参*/
    SWORD32  sdwLunId;       /* Lun的本地Id，映射组内唯一 ,入参*/
    CHAR     cInitName[MAX_INI_NAME_LEN];    /* 主机名 ，入参*/
    SWORD32  sdwAction;      /*操作标志: 0/1/2，对应的宏定义为"OFF"、 "ON"、"RES"，分别表示关闭、打开、重置。 入参*/
} _PACKED_1_ T_LunIOStaticSwitch;

typedef struct
{
    //SWORD32 sdwCtrlId;        /* 控制器Id ,暂时定义为0、1，对应的宏定义CTRL0、CTRL1*/
    CHAR        cMapGrpName[MAX_MAPGRP_NAME_LEN]; /* 映射组名称，入参*/
    SWORD32     sdwLunId;       /* Lun的本地Id，映射组内唯一 ,入参*/
    CHAR        cInitName[MAX_INI_NAME_LEN];    /* 主机名 ，入参*/
    WORD64      sqwStatReadCount;           /* 统计读的个数 */
    WORD64      sqwStatReadTransimitData;   /* 统计读数据量 ,单位:Byte*/
    WORD64      sqwStatWriteCount;          /* 统计写的个数 */
    WORD64      sqwStatWriteTransimitData;  /* 统计写数据量 ,单位:Byte*/
    WORD64      sqwStatTransimitDataAverage;    /* 平均数据速率 */
    WORD64      sqwStatTransimitDataAll;        /* 数据总量 */
    WORD64      sdwStatCmdTimeAverage;          /* 命令平均执行时间,单位:微秒 */
    WORD64      sdwStatCmdTimeMax;              /* 命令最大执行时间 ,单位:微秒*/
    WORD64      sdwCmdSuccessNum ;              /* 命令执行成功的个数 */
    WORD64      sdwCmdTimeAll;                  /* 命令执行的总时间,单位:微秒 */
} _PACKED_1_ T_LunIOStaticData;
/***************************************CBS*************************************/
typedef struct
{
    SWORD32 sdwRwRatio;      /* 读写所占空间比例中，写占的比例 */
    SWORD32 sdwUnitSize;     /* 缓存单元大小 ，单位:KB*/
    SWORD32 sdwWrPeriod;     /* 定时回写周期 */
    SWORD32 sdwRefreshRatio; /* 回写比例上线 */
    SWORD32 sdwWrEnable;     /* 镜像开关ON/OFF */
} _PACKED_1_ T_SetCacheGlbPolicy;

typedef struct
{
    SWORD32  sdwRwRatio;       /* 读写Cache比例 */
    SWORD32  sdwUnitSizeSet;   /* 最新设置的Cache单元大小，单位KB，值为4、8、16、32、64、128。(重启后生效) */
    SWORD32  sdwCurUnitSize;   /* 当前生效Cache单元大小（值同上） */
    SWORD32  sdwWrPeriod;      /* 刷新周期 */
    SWORD32  sdwRefreshRatio;  /* 刷新比例 */
    SWORD32  sdwWrEnable;      /* Cache镜像开关 值为ON（1）/OFF（1） */
} _PACKED_1_ T_GetCacheGlbPolicy;

typedef struct
{
    SWORD32 sdwTotalBuffs;/*  总的缓存个数 */
    SWORD32 sdwFreeBuffs;      /*  空闲的缓存个数 */
} _PACKED_1_ T_CacheBuffInfo;

typedef struct
{
    //SWORD32 sdwCtrlId;        /* 控制器Id ,暂时定义为0、1，对应的宏定义CTRL0、CTRL1*/
    SWORD32 sdwAction;      /*操作标志: 0/1/2，对应的宏定义为"OFF"、 "ON"、"RES"，分别表示关闭、打开、重置。 */
} _PACKED_1_ T_CacheIOStatSwitch;

typedef struct
{

    WORD64 uqwBcReadCmds;      /* 处理读命令总个数 */
    WORD64 uqwBcReadSize;      /* 读命令处理的总数据量(单位：sector，块)  */
    WORD64 uqwBcWriteCmds;     /* 处理写命令总个数 (单位：sector，块) */
    WORD64 uqwBcWriteSize;     /* 写命令处理的数据总量 */
    WORD64 uqwBcReadHits;      /* 读命令命中个数 */
    WORD64 uqwBcWriteMerge;    /* 合并写个数(目前这个变量未使用) */
    WORD64 uqwBcDirtyBuffers;  /* 脏缓存个数 */
    WORD64 uqwBcCleanBuffers;  /* 干净缓存个数 */
} _PACKED_1_ T_CacheIOStatData;

/***************************************ISCSI***********************************/

typedef struct
{
    CHAR     scIp[MAX_IP_LEN];   /*IP地址*/
    CHAR     scName[MAX_INI_NAME_LEN];
} _PACKED_1_ T_IscsiIniInfo;
typedef struct
{
    WORD32          wTid;/* target Id，目标端口Id */
    WORD32          wFlag;/* flag为1时，表示为了加入主机，需剔除已在主机中的端口 */
    WORD32          wCount;
    T_IscsiIniInfo  tIscsiIInfo[MAX_INITIATOR_NUM];
} _PACKED_1_ T_IscsiIniInfoList;

typedef struct
{
    BYTE       ucISID[6];             /*  标识主机端信息ID  */
    WORD16     udwTSIH;               /* 标识Tgt端信息Id  */
    WORD16     udwPortalGroupTag;
    WORD16     udwSvrPort;            /* iSCSI专用端口 3260*/
    CHAR       scTgtPortIp[MAX_IP_LEN];   /* 业务端口的IP */
    CHAR       cInitIp[MAX_IP_LEN];   /* Initiator IP */
    CHAR       cInitName[MAX_INI_NAME_LEN];  /* Initiator Name */
    WORD16     udwIniPort; /* 启动器发起会话的端口号 */
    WORD16     udwConnId; /* 链接号 */
} _PACKED_1_ T_IscsiSessInfo;

/*Target会话信息列表*/
typedef struct
{
    SWORD32     sdwCtrlId;
    WORD32      udwTgtId;                            /*Target Id*/
    WORD32      udwSessCount;                      /*Session 数量*/
    T_IscsiSessInfo tIscsiSessInfo[MAX_ISCSI_SESSION_COUNT];        /*Session 信息列表*/
} _PACKED_1_ T_IscsiSessInfoList;

typedef struct
{
    WORD32      udwCtrlId;                      /*控制器Id */
    WORD32      udwTgtId;                      /* Tgt Id */
    WORD32      udwSessCount;                      /*Session 数量*/
} _PACKED_1_ T_GetIscsiSessNum;

typedef struct
{
    SWORD32     sdwCtrlId;
    SWORD32      udwTgtId;                            /*Target Id*/
    BYTE       ucISID[6];             /*  标识主机端信息ID  */
    WORD16     udwTSIH;               /* 标识Tgt端信息Id  */
    WORD16     udwPortalGroupTag;
    WORD16     udwSvrPort;            /* iSCSI专用端口 3260*/
    CHAR       scTgtPortIp[MAX_IP_LEN];   /* 业务端口的IP */
    CHAR       cInitIp[MAX_IP_LEN];   /* Initiator IP */
    CHAR       cInitName[MAX_INI_NAME_LEN];  /* Initiator Name */
    WORD16     udwIniPort; /* 启动器发起会话的端口号 */
    WORD16     udwConnId; /* 链接号 */
} _PACKED_1_ T_IscsiSessionInfo;

typedef struct
{
    WORD32      udwCtrlId;
    WORD32      udwTid;
    WORD32      udwSessCount;                      /*每次要获取的Session 数量*/
    WORD32      udwSessBgnIndex;                      /*要获取信息的起始位置*/
    T_IscsiSessionInfo tIscsiSessListInfo[MAX_ISCSI_SESSION_NUM_ONCE];        /*Session 信息列表*/
} _PACKED_1_ T_IscsiSessGetOnceInfo;

typedef struct
{
    BYTE       ucWWPN[FC_WWN_LENGTH];  /* FC World Wide长度 */
} _PACKED_1_ T_FcGpnInfo;

typedef struct
{
    WORD32      udwCtrlId;                         /*控制器Id ，入参*/
    WORD32      udwSlotId;                         /*槽位Id ，入参*/
    WORD32      udwPortId;                         /* 端口 Id ，入参*/
    WORD16      udwGpnBgnIndex;                    /*要获取信息的起始位置，入参，从1开始*/
    WORD16      udwNextGetIndex;                   /*返回的下一次获取的起始位置，出参*/
    WORD32      udwGpnCount;                       /*返回的Gpn 数量，出参*/
    BYTE        udwEndFlag;                        /* 是否继续获取的标识，出参 */

    T_FcGpnInfo tFcGpnListInfo[MAX_FC_GPN_NUM_ONCE]; /*gpn 信息列表，出参*/
} _PACKED_1_ T_GetOnceFcGpnInfo;

typedef struct
{
    WORD32      udwCtrlCount;                      /*Session 数量*/
    T_IscsiSessInfoList tIscsiSessListInfo[2];        /*Session 信息列表*/
} _PACKED_1_ T_IscsiSessInfoDualList;
typedef struct
{
    WORD64                 LogInReq;
    WORD64                 TextReq;
    WORD64                 NopOut;
    WORD64                 LogOutReq;
    WORD64                 ScsiCmdReq;
    WORD64                 ScsiMgmtCmdReq;
    WORD64                 DataOut;

    WORD64                 NopOut_Reject;
    WORD64                 ScsiCmdReq_Reject;
    WORD64                 ScsiMgmtCmdReq_Reject;
    WORD64                 DataOut_Reject;

    WORD64                 LogInRsp;
    WORD64                 TextRsp;
    WORD64                 LogOutRsp;
    WORD64                 NopIn;
    WORD64                 ScsiCmdRsp;
    WORD64                 ScsiMgmtCmdRsp;
    WORD64                 R2t;
    WORD64                 DataIn;
    WORD64                 Snack;
    WORD64                 Async;
    WORD64                 Reject;
} _PACKED_1_ T_IscsiPduInfo;

typedef struct
{
    SWORD32     sdwCtrlId;
    T_IscsiPduInfo   tiscsiPduInfo; /*PDU 信息列表*/
} _PACKED_1_ T_IscsiPduInfoList;

typedef struct
{
    WORD32      udwCtrlCount;            /* 控制器个数*/
    T_IscsiPduInfoList  tIscsiPduInfo[2];    /* PDU信息列表*/
} _PACKED_1_ T_IscsiAllPduStatisticInfo;

/*获取session 属性*/
typedef struct
{
    //WORD64      uqwSessId;                /* Session Id, 入参*/
    SWORD32     sdwCtrlId;
    BYTE        ucISID[6];                 /*  标识主机端信息ID  */
    WORD16      udwTSIH;                 /* 标识Tgt端信息Id  */
    WORD32      udwTgtId;               /*Target Id */

    WORD32      udwSessionParam[session_key_last];    /*session 属性*/
} _PACKED_1_ T_GetIscsiSessAttrInfo;

/*端口流量信息*/
typedef struct
{
    SWORD32      sdwCtrlId;               /* 控制器Id ,暂时定义为0、1，对应的宏定义CTRL0、CTRL1*/
    WORD32       udwTgtId;                /* Target ID*/
    WORD32       udwPortId;              /*Target  port ID , 值为0表示所有端口，其他值为端口ID */
//    WORD32       udwBandWidth;      /*数据流带宽*/
    WORD64       uqwTxPDUCount;    /*发送完整(成功)PDU个数*/
    WORD64       uqwRxPDUCount;    /*接收完整(成功)PDU个数*/
    WORD64       uqwTxPktCount;     /*发送不完整(失败)PDU个数*/
    WORD64       uqwRxPktCount;     /*接收不完整(失败)PDU个数*/
    WORD64       uqwTxByteCount;   /*发送总字节数*/
    WORD64       uqwRxByteCount;   /*接收总字节数*/
    WORD64       uqwBandWidth;      /*数据流带宽,单位:Byte/s */
} _PACKED_1_ T_IscsiFlowStatInfo;

/*Target Name*/
typedef struct
{
    SWORD32       udwCtrlId;  /* CTRL ID*/
    CHAR         cTgtName[MAX_TGT_NAME_LEN];   /*Target Name*/
} _PACKED_1_ T_IscsiTargetInfo;

typedef struct
{
    WORD32             udwCtrlCount;  /* 控制器个数*/
    T_IscsiTargetInfo  tIscsiTargetInfo[2];   /*Target Name*/
} _PACKED_1_ T_IscsiTargetList;

/*Iscsi 流量统计开关*/
typedef struct
{
    SWORD32     sdwCtrlId;    /* 控制器Id ,暂时定义为0、1，对应的宏定义CTRL0、CTRL1*/
    WORD32      udwTid;       /* Target ID*/
    WORD32      udwAction;    /* 操作标志: 0/1/2，对应的宏定义为"OFF"、 "ON"、"RES"，分别表示关闭、打开、重置。 */
} _PACKED_1_ T_IscsiFlowStatFlag;

/* Target 对应的端口信息列表 */
typedef struct
{

    CHAR         cPortIp[MAX_IP_LEN];  /* 端口的物理IP */
    WORD16       sPGT;    /* PortalGroupTag */
    WORD16       sServPort;                     /* 服务端口 */
} _PACKED_1_ T_IscsiPortalInfo;
typedef struct
{
    SWORD32           sdwCtrlId;
    WORD32            udwTgtId;                                                                               /*Target Id*/
    WORD32            udwPortCount;                                                                        /* 端口数量 */
    T_IscsiPortalInfo tISCSIPortalInfo[MAX_ISCSI_PORT_NUM_PER_CTL];             /* 端口信息列表*/
} _PACKED_1_ T_IscsiPortalList;

typedef struct
{
    WORD32             udwCtrlCount;                        /*Ctrl控制器 数量*/
    T_IscsiPortalList  tIscsiPortListInfo[2];        /*Port信息列表*/
} _PACKED_1_ T_IscsiNetPortalList;

/* 管理口浮动IP */
typedef struct
{
    CHAR scDriftIp[MAX_IP_LEN];
    CHAR scDriftIpMask[MAX_IP_LEN];
} _PACKED_1_ T_MportDriftIp;

/***************************************统计项补充功能***********************************/
typedef struct
{
    SWORD32  sdwCtrlId;      /* 控制器Id：0、1，对应宏定义CTRL0、CTRL1 */
    SWORD32  sdwOccupy;      /* CPU占用率 */
} _PACKED_1_ T_CpuOccupyPerCtl;

typedef struct
{
    SWORD32             sdwCtrlNum;             /* 控制器数目,  出参 */
    T_CpuOccupyPerCtl   tCpuOccu[ENC_ALL_CTL];  /* ENC_ALL_CTL值为2 ，表示两个控制器 */
} _PACKED_1_ T_CpuOccupy;

typedef struct
{
    SWORD32  sdwSlotId;          /* 磁盘槽位号，取值0~27(ScanBox);  0~11(SPR10) */
    SWORD32  sdwEnclosureId;    /* 箱体Id，取值 0~实际箱体数 */
    SWORD32  sdwCtrlId;         /* 控制器Id：0、1，对应宏定义CTRL0、CTRL1*/
    WORD64   dwCmdCount;        /* IO命令个数 */
    WORD64   dwCmdDataSize;    /* IO数据携带的总数据量大小，以字节为单位 */
} _PACKED_1_ T_SasStatPerCtrl;

typedef struct
{
    SWORD32           sdwSlotId;                   /* 磁盘槽位号，取值0~27(ScanBox);  0~11(SPR10) */
    SWORD32           sdwEnclosureId;             /* 箱体Id，取值 0~实际箱体数 */
    SWORD32           sdwCtrlNum;                 /* 控制器数目,  出参*/
    T_SasStatPerCtrl  tSasStatInfo[ENC_ALL_CTL];  /* 分别表示两个控制器信息 */
} _PACKED_1_ T_SasStatInfo;

typedef struct
{
    SWORD32  sdwCtrlId;        /* 控制器Id：0、1，对应宏定义CTRL0、CTRL1*/
    WORD64   HscAverageSpeed; /* 从通道建立以来平均速度，单位Byte/s */
    WORD64   HscCurrentSpeed; /* 最近1s内流出通道的数据，对用户相当于瞬时速率单位Byte/s */
    WORD64   HscTotalData;    /* 从通道建立以来流出通道的总数据量，单位Byte/s */
} _PACKED_1_ T_PcieFlowStatusPerCtl;

typedef struct
{
    SWORD32                 sdwCtrlNum;             /* 控制器数目,  出参*/
    T_PcieFlowStatusPerCtl  tPcieFlow[ENC_ALL_CTL]; /*  ENC_ALL_CTL定义为2 */
} _PACKED_1_ T_PcieFlowStatus;

typedef struct
{
    WORD32 dwPortNo;           /* 端口号 */
    WORD64 qwRcvPkts;          /* 接收报文数 */
    WORD64 qwRcvBytes;         /* 接收字节数 */
    WORD64 qwSndPkts;          /* 发送报文数 */
    WORD64 qwSndBytes;         /* 发送字节数 */
} _PACKED_1_ T_TcsStat;
typedef struct
{
    SWORD32       sdwCtrlId;         /* 控制器Id：0、1，对应宏定义CTRL0、CTRL1*/
    SWORD32       sdwPortNum;        /* 端口数目，值是宏定义TCS_PORT_NUM */
    T_TcsStat    tTcsStat[GE_PORT_NUM];
} _PACKED_1_ T_TcsStatInfoPerCtl;

typedef struct
{
    SWORD32             sdwCtrlNum;                /* 控制器数目,  出参*/
    T_TcsStatInfoPerCtl tTcsStatInfo[ENC_ALL_CTL]; /*  ENC_ALL_CTL定义为2 */
} _PACKED_1_ T_TcsStatInfo;

/** 统计功能完善 - 2013.05 **/

/* 基于存储控制器的界面上呈现的性能统计项 */
typedef struct
{
    SWORD32  sdwCtrlId;               /* 控制器Id：0、1，对应宏定义CTRL0、CTRL1 */
    SWORD32  sdwOccupy;               /* CPU占用率 */
    WORD64   qwReadMBps;              /* 读MBps,统计间隔内的平均读带宽,单位:MB/s */
    WORD64   qwReadIOps;              /* 读IOps,统计间隔内的平均读命令IO数,单位:个/s */
    WORD64   qwReadDataSize;          /* 读命令数据块大小,统计间隔内读命令的平均数据块大小,单位:字节 */
    WORD64   qwReadRespTime;          /* 读命令响应时间,统计间隔内读命令的平均响应时间,单位:ms */
    WORD64   qwReadQueueLen;          /* 读命令队列长度,统计间隔内读命令的平均队列长度,单位:未知 */
    WORD64   qwWriteMBps;             /* 写MBps,统计间隔内的平均写带宽,单位:MB/s */
    WORD64   qwWriteIOps;             /* 写IOps,统计间隔内的平均写命令IO数,单位:个/s  */
    WORD64   qwWriteDataSize;         /* 写命令数据块大小,统计间隔内写命令的平均数据块大小,单位:字节 */
    WORD64   qwWriteRespTime;         /* 写命令响应时间,统计间隔内写命令的平均响应时间,单位:ms */
    WORD64   qwWriteQueueLen;         /* 写命令队列长度,统计间隔内写命令的平均队列长度,单位:无 */
    WORD64   qwDirtyCacheRatio;       /* 脏Cache数据比例,脏数据空间和全部cache空间的比值 */
} T_CtrlStatInfoPerCtl;

typedef struct
{
    SWORD32              sdwCtrlNum;              /* 控制器数目,  出参*/
    T_ScsTime            tCurTime;                /* 实时时间 */
    T_CtrlStatInfoPerCtl tCtrlStatInfoPerCtl[ENC_ALL_CTL];
} T_CtrlStatInfo;

/* 基于端口的界面上呈现的性能统计项 */
typedef struct
{
    WORD32   dwPortType;           /* 端口类型，出参。取值如下:
                                     #define USP_MEDIA_PORT_TYPE_GE           1
                                     #define USP_MEDIA_PORT_TYPE_10G          2
                                     #define USP_MEDIA_PORT_TYPE_FC           3
                                     #define USP_MEDIA_PORT_TYPE_FCOE         4
                                     #define USP_MEDIA_PORT_TYPE_BOND         5 */
    WORD32   dwPortNo;             /* 端口号,SPR20单板:取值1-8,其他单板取值1-4 */
    WORD64   qwRcvMesCnt;          /* 接收报文数,单位:个 */
    WORD64   qwRcvBandWidth;       /* 接收报文带宽,单位:MB/s */
    WORD64   qwSendMesCnt;         /* 发送报文数,单位:个 */
    WORD64   qwSendBandWidth;      /* 发送报文带宽,单位:MB/s */
    WORD32   dwCardNo;             /* 板卡号,即卡的槽位号,SPR20单板:取值1-4,其他单板取值1,显示仅针对SPR20有效,端口类型为5时,此字段无效,界面显示- */
} T_PortStat;

typedef struct
{
    SWORD32  sdwCtrlId;            /* 控制器Id：0、1，对应宏定义CTRL0、CTRL1 */
    SWORD32  sdwGePortNum;           /* GE端口数目 */
    SWORD32  sdwFcPortNum;           /* FC端口数目 */
    SWORD32  sdw10GPortNum;          /* 10G端口数目 */
    T_PortStat tGePortStat[MAX_GE_FC_PORT_NUM];
    T_PortStat tFcPortStat[MAX_GE_FC_PORT_NUM];
    T_PortStat t10GPortStat[MAX_10G_FCOE_PORT_NUM];
    SWORD32  sdwBondPortNum;         /* Bond端口数目 */
    T_PortStat tBondPortStat[MAX_BOND_NUM_PRE_CTRL];
} T_PortStatInfoPerCtl;

typedef struct
{
    SWORD32              sdwCtrlNum;              /* 控制器数目,  出参*/
    T_ScsTime            tCurTime;                /* 实时时间 */
    T_PortStatInfoPerCtl tPortStatInfoPerCtl[ENC_ALL_CTL];
} T_PortStatInfo;

/* 基于LUN的界面上呈现的性能统计项*/
typedef struct
{
    SWORD32   sdwCtrlId;                                      /* 控制器Id：0、1，对应宏定义CTRL0、CTRL1,入参 */
    SWORD32   sdwVolCount;                                    /* vol 数量,出参 */
    SWORD32   sdwVolType[MAX_VISIBLE_VOL_NUM_IN_SYS];                 /* 卷类型，包含普通卷(NORM_VOL,值为0)、快照卷(SNAPSHOT_VOL,值为2)、拷贝卷(CLONE_VOL,值为4) */
    CHAR      cVolName[MAX_VISIBLE_VOL_NUM_IN_SYS][MAX_BLK_NAME_LEN]; /* Vol名称 */
    CHAR      cVdName[MAX_VISIBLE_VOL_NUM_IN_SYS][MAX_BLK_NAME_LEN];  /* vol所在的vd名称 */
} T_VolNum;

typedef struct
{
    CHAR     cVolName[MAX_BLK_NAME_LEN]; /* Vol名称，出入参，当sdwLunNum为1时，是入参。其他情况是出参 */
    CHAR     cVdName[MAX_BLK_NAME_LEN];  /* vol所在的vd名称 */
    WORD64   qwReadMBps;                 /* 读MBps,统计间隔内的平均读带宽,单位:MB/s */
    WORD64   qwReadIOps;                 /* 读IOps,统计间隔内的平均读命令IO数,单位:个/s */
    WORD64   qwReadDataSize;             /* 读命令数据块大小,统计间隔内读命令的平均数据块大小,单位:字节 */
    WORD64   qwReadRespTime;             /* 读命令响应时间,统计间隔内读命令的平均响应时间,单位:ms */
    WORD64   qwReadQueueLen;             /* 读命令队列长度,统计间隔内读命令的平均队列长度 */
    WORD64   qwWriteMBps;                /* 写MBps,统计间隔内的平均写带宽,单位:MB/s */
    WORD64   qwWriteIOps;                /* 写IOps,统计间隔内的平均写命令IO数,单位:个/s */
    WORD64   qwWriteDataSize;            /* 写命令数据块大小,统计间隔内写命令的平均数据块大小,单位:字节 */
    WORD64   qwWriteRespTime;            /* 写命令响应时间,统计间隔内写命令的平均响应时间,单位:ms */
    WORD64   qwWriteQueueLen;            /* 写命令队列长度,统计间隔内写命令的平均队列长度 */
    WORD64   qwPrereadHitRatio;          /* 预读命中率,统计间隔内，读命令命中预读数据的百分比 */
    WORD64   qwReadCacheHitRatio;        /* 读cache命中率,统计间隔内，读命令命中cache数据的百分比 */
    WORD64   qwWriteCacheHitRatio;       /* 写cache命中率,统计间隔内，写命令命中cache数据的百分比 */
    SWORD32  sdwVolType;                 /* 卷类型，包含普通卷（NORM_VOL）、快照卷（SNAPSHOT_VOL）、拷贝（CLONE_VOL） */
} T_LunStat;

typedef struct
{
    SWORD32             sdwCtrlId;                  /* 控制器Id：0、1，对应宏定义CTRL0、CTRL1,出参 */
    SWORD32             sdwLunNum;                  /* LUN数目,出参 */
    T_LunStat tLunStat[MAX_VISIBLE_VOL_NUM_IN_SYS];
} T_LunStatInfoPerCtl;

/* 用于WEB一次查询所有卷统计信息 */
typedef struct
{
    SWORD32             sdwCtrlNum;              /* 控制器数目,  出参*/
    T_ScsTime           tCurTime;                /* 实时时间 */
    T_LunStatInfoPerCtl tLunStatInfoPerCtl[ENC_ALL_CTL];
} T_LunStatOnceInfo;

/* 用于CLI命令查询单个卷统计信息 */
typedef struct
{
    SWORD32             sdwCtrlNum;                 /* 控制器数目,  出参*/
    SWORD32             sdwLunNum;                  /* LUN数目，入参 */
    T_ScsTime           tCurTime;                   /* 实时时间 */
    CHAR                cVolName[MAX_BLK_NAME_LEN]; /* Vol名称，入参。 */
    T_LunStatInfoPerCtl tLunStatInfoPerCtl[ENC_ALL_CTL];
} T_LunStatInfo;

/* 基于磁盘的界面上呈现的性能统计项 */
typedef struct
{
    SWORD32  sdwSlotId;                /* 磁盘槽位号，取值0~27(ScanBox);  0~11(SPR) */
    SWORD32  sdwEnclosureId;           /* 箱体Id，取值 0~实际箱体数 */
    WORD64   qwReadMBps;               /* 读MBps,统计间隔内的平均读带宽,单位:MB/s */
    WORD64   qwReadIOps;               /* 读IOps,统计间隔内的平均读命令IO数,单位:个/s */
    WORD64   qwReadDataSize;           /* 读命令数据块大小,统计间隔内读命令的平均数据块大小,单位:字节 */
    WORD64   qwReadRespTime;           /* 读命令响应时间,统计间隔内读命令的平均响应时间,单位:ms */
    WORD64   qwWriteMBps;              /* 写MBps,统计间隔内的平均写带宽,单位:MB/s */
    WORD64   qwWriteIOps;              /* 写IOps,统计间隔内的平均写命令IO数,单位:个/s */
    WORD64   qwWriteDataSize;          /* 写命令数据块大小,统计间隔内写命令的平均数据块大小,单位:字节 */
    WORD64   qwWriteRespTime;          /* 写命令响应时间,统计间隔内写命令的平均响应时间,单位:ms */
    WORD64   qwQueueLen;               /* 命令队列长度,统计间隔内命令的平均队列长度,单位:个 */
    SWORD32  sdwDiskIOAccessRatio;     /* 磁盘IO访问率,统计间隔内，磁盘请求队列不为空的时间百分比 */
} T_DiskStat;
typedef struct
{
    SWORD32    sdwCtrlId;                /* 控制器Id：0、1，对应宏定义CTRL0、CTRL1 */
    SWORD32    sdwDiskNum;               /* 磁盘数目 */
    T_DiskStat tDiskStat[MAX_PD_NUM_IN_SYS];
} T_DiskStatInfoPerCtl;

typedef struct
{
    SWORD32              sdwSlotId;                   /* 磁盘槽位号，取值0~27(ScanBox);  0~11(SPR) */
    SWORD32              sdwEnclosureId;              /* 箱体Id，取值 0~实际箱体数 */
    SWORD32              sdwCtrlNum;                  /* 控制器数目,  出参*/
    T_ScsTime            tCurTime;                    /* 实时时间 */
    T_DiskStatInfoPerCtl tDiskStatInfoPerCtl[ENC_ALL_CTL];
} T_DiskStatInfo;

typedef struct
{
    SWORD32              sdwCtrlNum;              /* 控制器数目,  出参*/
    T_ScsTime            tCurTime;                /* 实时时间 */
    T_DiskStatInfoPerCtl tDiskStatInfoPerCtl[ENC_ALL_CTL];
} T_AllDiskStatInfo;

typedef struct
{
    WORD32      dwTime;           /* 统计周期，入参 */
} T_StatTime;

/*** 性能统计模块2014年12月  ***/

typedef struct
{
    WORD32 dwCtrlId;
} _PACKED_1_ T_DEVStat;

typedef struct
{
    CHAR cPoolName[MAX_BLK_NAME_LEN];
} _PACKED_1_ T_POOLStat;

typedef struct
{
    CHAR cVdName[MAX_BLK_NAME_LEN];
} _PACKED_1_ T_VDStat;

typedef struct
{
    WORD32 dwCtrlId;          /* 控制器ID */
    WORD32 dwPortType;        /* 端口类型--
                                 #define USP_MEDIA_PORT_TYPE_GE           1
                                 #define USP_MEDIA_PORT_TYPE_10G          2
                                 #define USP_MEDIA_PORT_TYPE_FC           3
                                 #define USP_MEDIA_PORT_TYPE_FCOE         4
                                 #define USP_MEDIA_PORT_TYPE_BOND         5 */
    WORD32 dwPortNo;          /* 端口号 */
    WORD32 dwCardNo;          /* 板卡号,即卡的槽位号,SPR20单板:取值1-4,其他单板取值1,显示仅针对SPR20有效,端口类型为5时,此字段无效,界面显示- */
} _PACKED_1_ T_FRONTPORTStat;

typedef struct
{
    SWORD32  sdwSlotId;                /* 磁盘槽位号 */
    SWORD32  sdwEnclosureId;           /* 箱体Id */
} _PACKED_1_ T_DISKStat;

typedef struct
{
    CHAR cVolName[MAX_BLK_NAME_LEN];
} _PACKED_1_ T_LUNStat;

/* 界面显示内容结构体 */
typedef struct
{
    WORD64 ldwIops;         /* 个/秒 */
    WORD64 ldwThroughput;   /* Mb/秒 */
    WORD64 ldwIoRespTime;   /* ms */
    WORD64 ldwReadIoNum;    /* 个 */
    WORD64 ldwWriteIoNum;   /* 个 */
    T_ScsTime tScsTime;     /* 该记录对应的时间 */
} _PACKED_1_ T_BaseStatInfo;

/* 界面显示统计需要的头信息 */
typedef struct
{
    WORD32 dwSumPeriod;        /* @ref sum_period,取值天(1),周(2),月(3),年(4),入参. */
    WORD32 dwPageSize;         /* 获取的数量，分页查询用,入参 */
    WORD32 dwCurrentPage;      /* 当前页号,从1开始编号,入参 */
    WORD32 dwQueryObjNum;      /* 查询对象数,入参 */
    WORD32 dwTotalRecordNum;   /* 总记录数,出参 */
    WORD32 dwRealNum;          /* 实际记录数,出参 */
    T_ScsTime tStartDate;      /* 用户输入的统计开始时间,入参 */
    T_ScsTime tEndDate;        /* 用户输入的统计截止时间,入参 */
} _PACKED_1_ T_StatHheadInfo;

/* dev 统计结构体 */
typedef struct
{
    T_BaseStatInfo  tBaseStatInfo;
    T_DEVStat       tDevStat;
} _PACKED_1_ T_DevStatDetailInfo;

typedef struct
{
    T_StatHheadInfo     tStatHeadInfo;
    T_DEVStat           tDevStat[MAX_OBJ_NUM]; //暂不使用
    T_DevStatDetailInfo tDevStatDetailInfo[MAX_RECORD_NUM];
} _PACKED_1_ T_DevPmInfo;

/* vd 统计结构体 */
typedef struct
{
    T_BaseStatInfo  tBaseStatInfo;
    T_VDStat        tVdStat;
} _PACKED_1_ T_VdStatDetailInfo;

typedef struct
{
    T_StatHheadInfo    tStatHeadInfo;
    T_VDStat           tVdStat[MAX_OBJ_NUM];
    T_VdStatDetailInfo tVdStatDetailInfo[MAX_RECORD_NUM];
} _PACKED_1_ T_VdPmInfo;

/* pool 统计结构体 */
typedef struct
{
    T_BaseStatInfo  tBaseStatInfo;
    T_POOLStat      tPoolStat;
} _PACKED_1_ T_PoolStatDetailInfo;

typedef struct
{
    T_StatHheadInfo      tStatHeadInfo;
    T_POOLStat           tPoolStat[MAX_OBJ_NUM];
    T_PoolStatDetailInfo tPoolStatDetailInfo[MAX_RECORD_NUM];
} _PACKED_1_ T_PoolPmInfo;

/*lun统计结构体 */
typedef struct
{
    T_BaseStatInfo  tBaseStatInfo;
    T_LUNStat        tLunStat;
} _PACKED_1_ T_LunStatDetailInfo;

typedef struct
{
    T_StatHheadInfo     tStatHeadInfo;
    T_LUNStat           tLunStat[MAX_OBJ_NUM];
    T_LunStatDetailInfo tLunStatDetailInfo[MAX_RECORD_NUM];
} _PACKED_1_ T_LunPmInfo;

/*磁盘统计结构体 */
typedef struct
{
    T_BaseStatInfo  tBaseStatInfo;
    T_DISKStat      tDiskStat;
} _PACKED_1_ T_DiskStatDetailInfo;

typedef struct
{
    T_StatHheadInfo      tStatHeadInfo;
    T_DISKStat           tDiskStat[MAX_OBJ_NUM];
    T_DiskStatDetailInfo tDiskStatDetailInfo[MAX_RECORD_NUM];
} _PACKED_1_ T_DiskPmInfo;

/*前端端口统计结构体 */
typedef struct
{
    T_BaseStatInfo  tBaseStatInfo;
    T_FRONTPORTStat tFrontPortStat;
} _PACKED_1_ T_PortStatDetailInfo;

typedef struct
{
    T_StatHheadInfo       tStatHeadInfo;
    T_FRONTPORTStat       tFrontPortStat[MAX_OBJ_NUM];
    T_PortStatDetailInfo  tPortStatDetailInfo[MAX_RECORD_NUM];
} _PACKED_1_ T_PortPmInfo;

/***********************************Iscsi Chap***********************************/
/* Chap鉴权相关结构体 */
typedef struct
{
    CHAR             acname[CHAP_ACCOUNT_NAME_MAX];/* 223+1*/
    CHAR             acpass[CHAP_ACCOUNT_PASS_MAX];
} _PACKED_1_ T_IscsiChapAuthInf;
typedef struct
{
    WORD32      udwMulChapCount;      /* 双向chap配置数量 */
} _PACKED_1_ T_GetIscsiMulChapNum;
typedef struct
{
    WORD32      udwMulChapCount;      /*每次要获取的Chap 数量*/
    WORD32      udwMulChapBgnIndex;   /*要获取信息的起始位置*/
    T_IscsiChapAuthInf  tIscsiChapListInfo[MAX_ISCSI_CHAP_NUM_ONCE];        /*Chap 信息列表*/
} _PACKED_1_ T_IscsiMulChapGetOnceInfo;

/***************************************other***********************************/
typedef struct
{

    //SWORD32  sdwType;            /* USP_VER_TYPE/EXP_VER_TYPE/VPD_VER_TYPE/POW_VER_TYPE/BOOT_VER_TYPE 该字段目前只针对主柜即EncId=0有效 */
    SWORD32  sdwRebootMode;      /* 2--OFFLINE REBOOT, 1--ONLINE REBOOT, 3-CTL_NO_REBOOT 出参 */
    CHAR     ucFileName[MAX_FW_FILE_NAME_LEN];
} _PACKED_1_ T_UpdateFirmware;

typedef struct
{
    SWORD32  sdwEnclosureId; /* enclosure identification,入参 */
    SWORD32  sdwCtlId;       /* ctl id or expander id，  入参 */
    SWORD32  sdwType;        /* USP_VER_TYPE/EXP_VER_TYPE/VPD_VER_TYPE/POW_VER_TYPE/BOOT_VER_TYPE 该字段目前只针对主柜即EncId=0有效 */
    CHAR     ucCurrentFileName[MAX_FW_FILE_NAME_LEN]; /* 当前版本名称 */
    CHAR     ucCurrentVersion[MAX_VERSION_LEN];       /* 当前版本号 */
    CHAR     ucStandbyFileName[MAX_FW_FILE_NAME_LEN]; /* 备用版本名称 */
    CHAR     ucStandbyVersion[MAX_VERSION_LEN];       /* 备用版本号 */
    CHAR     ucUpdateFileName[MAX_FW_FILE_NAME_LEN];  /* 升级版本名称 */
    CHAR     ucUpdateVersion[MAX_VERSION_LEN];        /* 升级版本号 */
} _PACKED_1_ T_FirmwareVersion;

typedef struct
{
    SWORD32  sdwEnclosureId; /* enclosure identification  */
    SWORD32  sdwCtlId;       /* ctl id or expander id  SMC -1*/
    WORD16   wVerType;        /* USP_VER_TYPE/SMC_VER_TYPE */
    //CHAR     ucCurrentFileName[MAX_FW_FILE_NAME_LEN]; /* 当前版本名称 */
    CHAR     ucCurrentVersion[MAX_VERSION_LEN];       /* 当前版本号 */
    //CHAR     ucUpdateFileName[MAX_FW_FILE_NAME_LEN];  /* 升级版本名称 */
    CHAR     ucUpdateVersion[MAX_VERSION_LEN];        /* 升级版本号 */
} _PACKED_1_ T_SoftWareVer;

typedef struct
{
    SWORD32  sdwEnclosureId;
    SWORD32  sdwCtlId;
    WORD16   wVerType;
    /*
    支持的版本类型
    CPU                 1
    FPGA                2
    DSP                 3
    MICROCODE           4
    FW                  5
    SCM                 6
    EPLD                7
    BOOTROM             8
    SCRIPT              9
    VERCFG              10
    LIB                 11
    SVRSET              12
    PATCH               13
    IPMC                14
    FRU                 15
    DDMPRI              16
    DDMSNMP             17
    CDM                 18
    IPMCBOOT            20
    DEPTCFG             21
    DSPTEST             23
    DSPTFTP             24
    DSP_MTS             25
    BIOS                26
    THIRDPARTY_PROC     27
    DESCRIBE_FILE       28
    PMBUS               29
    PDUEPLD             30
    SVRSETNEW           31
    BBUM                2730
    PM8005              8500
    VPD                 8501
    POWER               8502
    */
    CHAR     ucCurrentVersion[MAX_VERSION_LEN];
    CHAR     ucUpdateVersion[MAX_VERSION_LEN];
    WORD16   brdType;
    /*
    支持的单板类型
    PC          (0xFFFF)
    SBCW        (0x0214)
    SBCJ        (0x0219)
    IBMC        (0x2011)
    SPR10       (0x6701)
    SPJ10       (0x6710)
    SPR11       (0x6718)
    SPJ11       (0x6730)
    SPR12       (0x6738)
    SPR20       (0x6748)
    SMC10       (0x6750)
    SIOFC10     (0x6758)
    SIOFC11     (0x6760)
    SIOE10      (0x6768)
    SIOE20      (0x6770)
    SIOE21      (0x6778)
    SIOS10      (0x6780)
    SIOS11      (0x6788)
    BBUM10      (0x6790)
    FANM10      (0x6798)
    SIOE11      (0x67A8)
    SIOS20      (0x67B0)
    */
    WORD16   cpuType;
    WORD16   funcType;
    WORD32   pcbID;
} _PACKED_1_ T_HardWareVer;

typedef struct
{
    SWORD32 sdwSoftVerNum;
    T_SoftWareVer softVer[MAX_SOFTWARE_VER_NUM];
    SWORD32 sdwHardVerNum;
    T_HardWareVer hardVer[MAX_HARDWARE_VER_NUM];
} _PACKED_1_ T_VerList;

typedef struct
{
    SWORD32  sdwEnclosureId;      /* 扩展柜箱体ID,  现默认为0 */
    SWORD32  sdwCtlId;            /* ctl id or expander id or ENC_ALL_CTL */
    SWORD32  sdwAction;           /* 在线(CTL_ONLINE_REBOOT)/非在(CTL_SINGLE_REBOOT)线重启标记CTL_SINGLE_REBOOT/CTL_ONLINE_REBOOT */
} _PACKED_1_ T_CtrlAction;

typedef struct
{
    SWORD32  sdwNum;                             /* 箱体个数*/
    SWORD32  sdwEnclosureId[MAX_ENC_NUM_IN_SYS]; /* 箱体Id，取值 0~实际箱体数*/
} _PACKED_1_ T_AllEncId;

typedef struct
{
    SWORD32 sdwFileType;                          /* eConfigFileType, 保存文件类型 */
    CHAR    ucFileName[MAX_CONFIG_FILE_NAME_LEN]; /* 仅文件名，不包括路径 */
} _PACKED_1_ T_ConfigFile;

/* *************************System config**************************** */

/* 网络信息 modif by liutt */
typedef struct
{
    WORD32 udwCtrlId;          /* 控制器ID */
    WORD32 udwRoleType;     /* 网络设备角色(作用类型)类型，即业务网口(NET_ROLE_BUSINESS)、管理网口 (NET_ROLE_MANAGEMENT)*/
    WORD32 udwPortType;           /* 端口类型，仅对业务口有效，取值: 1(BUSINESS_PORT_TYPE_GE)、2(BUSINESS_PORT_TYPE_10GE),缺省值1，入参*/
    WORD32 udwDeviceId;         /* 设备编号 */
    CHAR   cIpAddr[MAX_IP_LEN]; /* IP地址 */
    CHAR   cNetmask[MAX_IP_LEN]; /* 子网掩码 */
    CHAR   cGateway[MAX_IP_LEN]; /* 网关 */
    WORD32 udwPortMtu;            /* 端口MTU ，仅在端口信息获取中使用 */
    WORD32 udwBondFlag;           /* 端口是否被聚合，仅业务网口 0(NET_ROLE_BUSINESS)有效，取值 0(PORT_NO_BOND_FLAG)、1(PORT_BOND_FLAG)*/
    CHAR   scBondName[MAX_BOND_NAME_LEN];        /* 端口归属的Bond名称，当udwBondFlag值为1(PORT_BOND_FLAG)是有效*/
    WORD32 udwSlotId;         /* 槽位号id */
} _PACKED_1_ T_SystemNetCfg;

typedef struct
{
    SWORD32  sdwDeviceNum;                                                     /* 网络设备数量 */
    T_SystemNetCfg tSystemNetCfg[DUAL_MAX_NET_DEVICE_NUM];         /* 网络设备信息列表(双控)*/
} _PACKED_1_ T_SystemNetCfgList;

/* 端口MAC modify by liutt */
typedef struct
{
    WORD32 udwCtrlId;                         /* 控制器ID */
    WORD32 udwPortType;                       /* 端口类型，仅对业务口有效，取值: 1(BUSINESS_PORT_TYPE_GE)、2(BUSINESS_PORT_TYPE_10GE),缺省值1，入参*/
    WORD32 dwPortNo;                          /*端口号，在SPR10中，这个编号为1~4*/
    BYTE   ucMacData[6];                       /*MAC 地址*/
    WORD32 dwSlotNo;                          /*new_槽位号*/
} _PACKED_1_  T_IscsiPortMac;

typedef struct
{
    SWORD32  sdwIscsiPortNum;                               /* Iscsi  端口数量 */
    T_IscsiPortMac tIscsiPortMac[DUAL_ISCSI_PORT_NUM];      /* Iscsi  端口Mac 信息列表*/
} _PACKED_1_ T_IscsiPortMacList;

/*ISCSI 端口信息 modify by liutt */
typedef struct
{
    WORD32 udwCtrlId;                        /* 控制器ID ，入参*/
    WORD32 udwPortType;                      /* 端口类型，仅对业务口有效，取值: 1(BUSINESS_PORT_TYPE_GE)、2(BUSINESS_PORT_TYPE_10GE),缺省值1，入参*/
    WORD32 dwPortNo;                         /* 端口号，GE口编号为1~4,10GE口编号为1~2,入参*/
    SWORD32 sdwSetFlg;                       /* 设置标志，暂取值0、1、2，分别表示设置MAC、设置MTU、设置MAC和MTU ,(该入参AMS 赋值)*/
    WORD32 udwPortMtu;                       /* 端口MTU ，可选入参*/
    BYTE   ucMacData[6];                     /* MAC 地址，可选入参*/
    WORD32 dwSlotNo;                         /* new_槽位号 */
} _PACKED_1_  T_IscsiPortSet;

/* 端口的基本物理信息 */
typedef struct
{
    BYTE    ucMacData[PORT_MAC_DATA_SIZE];                      /* MAC 地址*/
    WORD32  udwPortMtu;                                         /* 端口MTU */
    WORD32  udwPortState;                                       /* 端口状态，取值PORT_STATE_UP、PORT_STATE_DOWN*/
    WORD32  udwNegMode;                                         /* 协商模式,取值PORT_NEG_FORCE、PORT_NEG_AUTO*/
    WORD32  udwSpeed;                                           /* 端口速率值,取值PORT_SPEED_10M ~ PORT_SPEED_16G*/
    WORD32  udwDuplexMode;                                      /* 双工模式,取值PORT_DUPLEX_FULL、PORT_DUPLEX_HALF*/
} _PACKED_1_  T_PortInfo;

/*一个ISCSI 端口的物理信息 modify by liutt */
typedef struct
{
    WORD32 udwPortType;                        /* 端口类型，仅对业务口有效，取值: 1(BUSINESS_PORT_TYPE_GE)、2(BUSINESS_PORT_TYPE_10GE)*/
    WORD32 dwPortNo;                           /* 端口号，GE口编号为1~4,10GE口编号为1~2*/
    T_PortInfo tIscsiPortInfo;                 /* Iscsi  端口信息*/
    WORD32 dwSlotNo;                            /* new_槽位号id 编号:1-4 */
    WORD32     udwBondFlag;                    /* 端口是否被聚合，取值 0(PORT_NO_BOND_FLAG)、1(PORT_BOND_FLAG)*/
    CHAR       scBondName[MAX_BOND_NAME_LEN];  /* 端口归属的Bond名称，当udwBondFlag值为1(PORT_BOND_FLAG)时有效*/
} _PACKED_1_ T_IscsiPortInfo;

/*一个控制器上的所有ISCSI端口的信息*/
typedef struct
{
    WORD32   udwCtrlId;                                           /* 控制器ID */
    SWORD32  sdwIscsiPortNum;                                     /* Iscsi  端口数量 */
    T_IscsiPortInfo tIscsiPortInfo[ISCSI_PORT_NUM];               /* Iscsi  端口信息列表 */
} _PACKED_1_ T_SingleIscsiPortInfo;

/*系统中的所有控制器上ISCSI端口的信息*/
typedef struct
{
    WORD32 udwCtrlNum;                                            /* 系统中控制器数目,出参 */
    T_SingleIscsiPortInfo tSingleIscsiPortInfo[2];                /* 系统中Iscsi端口物理信息,出参 */
} _PACKED_1_ T_IscsiPortInfoList;

/*一个控制器上的管理网口的物理信息*/
typedef struct
{
    WORD32 udwCtrlId;                        /* 控制器ID */
    WORD32 udwPortType;                      /* 端口类型，1(BUSINESS_PORT_TYPE_GE)、2(BUSINESS_PORT_TYPE_10GE),目前单板物理口均为GE口，出参*/
    T_PortInfo tManePortInfo;                /* 管理口信息*/
} _PACKED_1_ T_SingleManaPortInfo;

/*系统中的所有控制器上管理网口的物理信息*/
typedef struct
{
    WORD32 udwCtrlNum;                                   /* 系统中控制器数目,出参*/
    T_SingleManaPortInfo tSingleManaPortInfo[2];         /* 系统中管理网口物理信息列表，出参*/
} _PACKED_1_ T_ManaPortInfoList;

/* 静态路由信息*/
typedef struct
{
    CHAR   scDstIp[MAX_IP_LEN];               /* 目标IP地址 ,入参*/
    CHAR   scMask[MAX_IP_LEN];                /* 掩码 ，入参*/
    CHAR   scNextHop[MAX_IP_LEN];             /* 下一跳地址 ，入参*/
} _PACKED_1_  T_IscsiRouteInfo;

/* 删除静态端口路由*/
typedef struct
{
    WORD32 udwCtrlId;                         /* 控制器ID ，可选入参，无效路由删除，该值填写缺省值0XFFFF（DEFAULT_VALUE）*/
    WORD32 udwPortType;                       /* 端口类型，仅对业务口有效，取值: 1(BUSINESS_PORT_TYPE_GE)、2(BUSINESS_PORT_TYPE_10GE),缺省值1，可选入参*/
    WORD32 dwPortId;                          /* 端口号，GE口编号为1~4,10GE口编号为1~2,可选入参*/
    CHAR   scDstIp[MAX_IP_LEN];               /* IP地址 ，入参*/
    CHAR   scMask[MAX_IP_LEN];                /* 掩码 ，入参*/
    CHAR   scNextHop[MAX_IP_LEN];             /* 下一跳地址 ，无效路由删除时需要，可选入参，缺省值为空串*/
    WORD32 dwSlotId;                            /* new_槽位号 */
} _PACKED_1_  T_IscsiPortRouteDel;

/* 端口的静态路由信息 modify by liutt */
typedef struct
{
    WORD32 udwCtrlId;                         /* 控制器ID */
    WORD32 udwPortType;                       /* 端口类型，仅对业务口有效，取值: 1(BUSINESS_PORT_TYPE_GE)、2(BUSINESS_PORT_TYPE_10GE),缺省值1，入参*/
    WORD32 dwPortId;                          /* 端口号，GE口编号为1~4,10GE口编号为1~2 */
    T_IscsiRouteInfo tIscsiRouteInfo;         /* 路由信息*/
    WORD32 dwRouteStatus;                     /* 路由状态信息，取值:1 有效，0 无效*/
    WORD32 dwSlotId;     /* new_槽位号 */
} _PACKED_1_  T_IscsiPortRouteInfo;

/* 静态路由信息列表*/
typedef struct
{
    SWORD32 sdwRouteNum;                      /* 静态路由数目 ，出参*/
    T_IscsiPortRouteInfo tIscsiPortRouteInfo[SCSI_MAX_STATICROUTE_NUM];    /* 静态路由列表，出参*/
} _PACKED_1_  T_IscsiPortRouteList;

typedef struct
{
    WORD32 udwCtrlId;                       /* 控制器ID */
    WORD32 dwFCoEPortId;                    /* FCoE端口编号，取值1~2，入参*/
} _PACKED_1_  T_FCoEPortInfo;

typedef struct
{
    T_FCoEPortInfo  tFCoEPortInfo;                    /* FCoE端口信息 */
    WORD32          dwVlan;                           /* VLAN，取值:0~4095(FCOE_MAX_VLAN_VALUE),入参*/
} _PACKED_1_  T_FCoEPortVlanInfo;

typedef struct
{
    WORD32 udwCtrlId;                                        /* 控制器ID */
    SWORD32 sdwFCoEPortNum;                                  /* FCoE端口数目*/
    T_FCoEPortVlanInfo tFCoEPortVlanInfo[FCOE_PORT_NUM];     /* FCoE端口信息列表*/
} _PACKED_1_  T_FCoEPortVlanInfoPerCtrl;

typedef struct
{
    WORD32                    udwCtrlNum;                             /*环境中Ctrl控制器数量*/
    T_FCoEPortVlanInfoPerCtrl tVlanPerCtrl[MAX_CTL_NUM];       /*FC端口信息列表*/
} _PACKED_1_ T_FCoEPortVlanInfoList;

typedef struct
{
    CHAR   scDstIp[MAX_IP_LEN];               /* 目标IP地址 ,入参*/
    WORD32 udwBytes;                          /* 数据长度 单位：字节,出参*/
    WORD32 udwTotTime;                        /* 往返时间 单位：us,出参*/
    WORD32 udwTtl;                            /* ttl ,出参*/
} _PACKED_1_  T_IscsiPingInfo;

/* IQN */
typedef struct
{
    SWORD32 sdwCtrlId;
    CHAR    acNewIqnname[MAX_TGT_NAME_LEN]; //iqn名称
} T_SetIscsiName;

/* remote target net */
typedef struct
{
    CHAR     ucRmtDiskUuid[MAX_UUID_LEN];                  /* 远程磁盘唯一标识符 */
    SWORD32  sdwRmtDiskState;                                  /* 远程磁盘的状态信息，取值 NORMAL_HDD、ABNORMAL_HDD*/
    SWORD32  sdwUsedFlag;                                      /* 远程磁盘的使用标志 ，取值REMOTE_DISK_UNUSED、REMOTE_DISK_USED*/
    SWORD32  sdwLunId;                                         /* 远程磁盘在所在映射组中的Lun Id 信息*/
    SWORD64  sqwCapacity;                                      /* 远程磁盘的容量,KB */
} T_RmtDiskBasicInfo;/* 37Byte */

typedef struct
{
    SWORD32       sdwCtrlId;                           /* 控制器ID，入参*/
    CHAR          aRmtTgtName[RMT_TARGET_NAME_LEN];    //远端设备名称
    WORD32        udwLinkType;                         /*链路类型，取值: 1(REMOTE_TARGET_FC)、2(REMOTE_TARGET_ISCSI),入参*/
    WORD32        udwTcpPort;                          /* 链路端口号，iSCSI方式时必填入参，默认值3260，取值范围1~65535 */
    WORD32        udwLinkState;                        /* 链路状态，取值1:REMOTE_LINK_STATUS_DISCONNECT,2:REMOTE_LINK_STATUS_CONNECTING,3:REMOTE_LINK_STATUS_STATUS_CONNECTED,4:REMOTE_LINK_STATUS_STATUS_DISCONNECTING*/
    SWORD32       sdwModyFlag;                         /* 此参数只在修改时有效，创建时无效，修改iscsi方式时，1: 只修改带宽，2:只修改chap,3:修改带宽和chap*/
    WORD64        qwBandWidth;                         /* 带宽,单位:MB/s ,约定修改iscsi链路时候，当带宽值为-1时候，认为是无效值，不修改*/
    CHAR          acIpAddr[MAX_IP_LEN];                /* iSCSI方式时有效，入参*/
    BYTE          ucWWPN[FC_WWN_LENGTH];               /* FC 方式时有效，入参*/
    WORD32        udwFcCardNo;                         /* FC 方式时有效，入参*/
    CHAR          acStatryChap[CHAP_ACCOUNT_PASS_MAX]; /* 单向chap，可选入参 */
    CHAR          acIqn[CHAP_ACCOUNT_NAME_MAX];
    //SWORD32       sdwRmtDiskNum;                                    /* 远端磁盘的数目，出参*/
    //T_RmtDiskBasicInfo tScsRmtDiskBasicInfo[MAX_MIRROR_REMOTE_DISK_NUM];  /* 远端磁盘列表，出参*/
} _PACKED_1_ T_RmtTgtLinkInfo; /*373Byte */
typedef struct
{
    SWORD32       sdwCtrlId;                           /* 控制器ID，入参*/
    //CHAR          aRmtTgtName[RMT_TARGET_NAME_LEN];    //远端设备名称
    WORD32        udwLinkType;                         /*链路类型，取值: 1(REMOTE_TARGET_FC)、2(REMOTE_TARGET_ISCSI),入参*/
    WORD32        udwTcpPort;                          /* 链路端口号，iSCSI方式时必填入参，默认值3260，取值范围1~65535 */
    WORD32        udwLinkState;                        /* 链路状态，取值1:REMOTE_LINK_STATUS_DISCONNECT,2:REMOTE_LINK_STATUS_CONNECTING,3:REMOTE_LINK_STATUS_STATUS_CONNECTED,4:REMOTE_LINK_STATUS_STATUS_DISCONNECTING*/
    CHAR          acIpAddr[MAX_IP_LEN];                /* iSCSI方式时有效，入参*/
    BYTE          ucWWPN[FC_WWN_LENGTH];               /* FC 方式时有效，入参*/
    SWORD32       sdwRmtDiskNum;                                    /* 远端磁盘的数目，出参*/
    T_RmtDiskBasicInfo tScsRmtDiskBasicInfo[MAX_MIRROR_REMOTE_DISK_NUM];  /* 远端磁盘列表，出参*/
} _PACKED_1_ T_RmtDiskListOnLink; /*373Byte */

typedef struct
{
    CHAR                   aRmtTgtName[RMT_TARGET_NAME_LEN];    //远端设备名称
    WORD32                 wRmtLinkNum;
    T_RmtTgtLinkInfo       tRmtTgtLinkInfo[MAX_LINK_IN_RMT_DEV];
    CHAR                   acTargetIQN[CHAP_ACCOUNT_NAME_MAX];
} _PACKED_1_ T_RmtLinkInDevInfo;

typedef struct
{
    SWORD32       sdwCtrlId;                           /* 控制器ID，入参*/
    WORD32        udwLinkType;                         /*链路类型，取值: 1(REMOTE_TARGET_FC)、2(REMOTE_TARGET_ISCSI),入参*/
    WORD32        udwTcpPort;                          /* 端口号，暂时保留 */
    WORD64        qwBandWidth;                         /* 带宽,单位:MB/s */
    CHAR          acIpAddr[MAX_IP_LEN];                /* iSCSI方式时有效，入参*/
    BYTE          ucWWPN[FC_WWN_LENGTH];               /* FC 方式时有效，入参*/
    WORD32        udwFcCardNo;                         /* FC 方式时有效，入参*/
    CHAR          acStatryChap[CHAP_ACCOUNT_PASS_MAX]; /* 单向chap，可选入参 */
} _PACKED_1_ T_LinkInfWhenAddRmtTgt;

typedef struct
{
    SWORD32                sdwCtrlId;                           /* 控制器ID，入参*/
    WORD32                 udwFirmType;                         /* 厂商类型，取值: 1(FIRM_SELF)本厂商、2(FIRM_EXTRA)外厂商入参*/
    WORD32                 udwLinkType;                         /*链路类型，取值: 1(REMOTE_TARGET_FC)、2(REMOTE_TARGET_ISCSI),入参*/
    WORD32                 udwTcpPort;                          /* 端口号，暂时保留 */
    CHAR                   aRmtTgtName[RMT_TARGET_NAME_LEN];    //远端设备名称
    CHAR                   cIpAddr[MAX_IP_LEN];                 /* IP地址，入参 */
    WORD32                 udwLinkFlag;                         /* 链路信息，入参1:LINK_HAVE_WHEN_ADD_TGT 2:LINK_NO_WHEN_ADD_TGT*/
    T_LinkInfWhenAddRmtTgt tLinkInfo;                           /* 链路信息，可选入参*/
} _PACKED_1_ T_RmtTgtInfo;

typedef struct
{
    WORD32                udwCtrlId;                           /* 控制器ID，*/
    WORD32                udwFirmType;                         /* 厂商类型，取值: 1(FIRM_SELF)本厂商、2(FIRM_EXTRA)外厂商入参*/
    WORD32                udwTcpPort;                          /* 端口号，暂时保留 */
    CHAR                  aRmtTgtName[RMT_TARGET_NAME_LEN];    //远端设备名称
    CHAR                  cIpAddr[MAX_IP_LEN];                 /* IP地址 */
    T_RmtLinkInDevInfo    tLinkInfo;                          /* 链路信息*/
} _PACKED_1_ T_GetRmtTgtInfo;

typedef struct
{
    WORD32                  wTargetNum;
    T_GetRmtTgtInfo         tTargetInfo[MAX_RMT_TARGET_NUM];
} _PACKED_1_ T_RmtTgtList;

typedef struct
{
    CHAR     cFileName[FILE_NAME_LEN];      /* 待上传文件的文件名, 入参*/
    WORD32  dwLocalFreeSize;                /* 本端剩余空间大小 */
    WORD32  dwPeerFreeSize;                 /* 对端剩余空间大小 */
} _PACKED_1_ T_VerFreeSpace;

typedef struct
{
    CHAR     cFileName[FILE_NAME_LEN];        /* 待上传文件的文件名, 入参*/
    SWORD32  sdwIsValid;                      /* 校验结果，0---校验通过，其他--校验不通过，返回错误码, 出参 */
} _PACKED_1_ T_VerFileCheck;

typedef struct
{
    CHAR   cFileName[FILE_NAME_LEN];        /* 待上传文件的文件名, 入参*/
    BYTE   ucUploadType;                    /* VERSION_FILE_TPYE--版本文件 CONFIG_FILE_TPYE--配置文件 OTHER_FILE_TYPE--其他 */

} _PACKED_1_ T_UploadPreInfo;

typedef struct
{
    CHAR   cUserName[USR_NAME_LEN];         /* ftp服务器登录用户名 ，入参*/
    CHAR   cPassWord[PASSWD_LEN];           /* ftp服务器登录密码 ，入参*/
    CHAR   cFtpServerIPAddr[MAX_IP_LEN];    /* ftp服务器IP 地址，入参*/
    CHAR   cFilePath[FILE_PATH_LEN];        /* 待上传文件的文件名 (带相对于FTP服务器目录的绝对路径)，入参*/
    BYTE   ucUploadType;                    /* VERSION_FILE_TPYE--版本文件 CONFIG_FILE_TPYE--配置文件 LOG_FILE_TPYE--日志文件 OTHER_FILE_TYPE--其他 */
} _PACKED_1_ T_UploadFileInfo;

typedef struct
{
    BYTE    ucFileType;                     /* VERSION_FILE_TPYE--版本文件 CONFIG_FILE_TPYE--配置文件 LOG_FILE_TPYE--日志文件 OTHER_FILE_TYPE 其他文件*/
    CHAR    cFileName[FILE_NAME_LEN];
} _PACKED_1_ T_FileToPeer;

/* ftp下载文件涉及的结构体 */
typedef struct
{
    CHAR  cUserName[USR_NAME_LEN];         /* ftp服务器登录用户名 ，入参*/
    CHAR  cPassWord[PASSWD_LEN];           /* ftp服务器登录密码 ，入参*/
    CHAR  cFtpServerIPAddr[MAX_IP_LEN];    /* ftp服务器IP 地址，入参*/
    CHAR  cDstFilePath[FILE_PATH_LEN];     /* 文件存放的目的路径（不带文件名），将自动以srcFileName文件名保存，入参 */
    CHAR  cSrcFilePath[FILE_PATH_LEN];
    CHAR  cSrcFileName[FILE_NAME_LEN];     /* 要下载的文件文件名（不带路径），入参 */
    BYTE  ucDownloadType;                  /* VERSION_FILE_TPYE--版本文件 CONFIG_FILE_TPYE--配置文件 LOG_FILE_TPYE--日志文件 OTHER_FILE_TYPE--其他 */
} _PACKED_1_ T_DownloadFileInfo;

typedef struct
{
    WORD32  udwPeerProcess;                 /* 对端进度，出参 */
    WORD32  udwLocalProcess;                /* 本端进度，出参 */
    WORD32  udwFileSize;                    /* 文件大小，出参 */
    BYTE    ucPeerSyncState;                /* 对端文件同步状态 */
    CHAR    cFileName[FILE_PATH_LEN];       /* 文件名(带路径) ，入参*/
} _PACKED_1_ T_UploadFileProgress;

typedef struct
{
    WORD32  udwDownloadProcess;             /* 下载进度 */
    CHAR    cSrcDir[FILE_PATH_LEN];
    CHAR    cFileName[FILE_NAME_LEN];       /* 文件名(不带路径) */
} _PACKED_1_ T_DownloadFileProgress;

typedef struct
{
    CHAR       cFileName[FILE_NAME_LEN];       /* 文件名(不带路径) ，入参*/
} _PACKED_1_ T_UploadFileName;

typedef struct
{
    CHAR       cFileName[FILE_NAME_LEN];       /* 文件名(不带路径) ，入参*/
    BYTE       ucExistType;                    /* 1:两端都存在,2:双控下仅本端存在,3:双控下仅对端存在,
                                                * 4:双控下两端都不存在,5:单控下存在,6:单控下不存在,
                                                * 7:单双控情况下文件名与当前主用或备用版本重名---出参 */
} _PACKED_1_ T_IsFileExist;

typedef struct
{
    SWORD32 sdwCtrlId;                                  /* 控制器ID,暂时定义为0、1，对应的宏定义CTRL0、CTRL1*/
    CHAR    cManufactureName[MAX_DIAG_DEVICE_NAME_LEN]; /* BBU厂家信息 */
    CHAR    cDeviceName[MAX_DIAG_DEVICE_NAME_LEN];      /* BBU型号 */
    SWORD32 sdwBbuPresentInfo;                          /* BBU是否在位 ，在位为DIAG_BBU_PRESENT(0)，不在位为DIAG_BBU_NOPRESENT(1) */
    //SWORD32 sdwBbuWorkFlag;                            /* BBU充放电标志，正在充放电为DIAG_BBU_CHARGING(0)，不在充放电为DIAG_BBU_NOT_CHARGING(1) */
    SWORD32 sdwBbuDeviceStatus;                         /* BBU状态，取值:正常(BBU_NORMAL,0)、异常(BBU_ABNORMAL,1)、电量不足(BBU_LOW_CAPACITY,2) */
} _PACKED_1_ T_SingleBbuInfo;

typedef struct
{
    SWORD32 sdwCtrlFlg;                /* 控制器标志 ,暂时定义为0、1、2，对应的宏定义CTRL_LOCAL、CTRL_PEER、CTRL_DUAL, 入参 */
    SWORD32 sdwBbuNum;                 /* BBU电源的数目，出参 */
    T_SingleBbuInfo tSingleBbuInfo[2]; /* 信息列表，当 sdwCtrlFlg = 0/1 时,仅tSingleBbuInfo[0]有值,当 sdwCtrlFlg = 2 时 , tSingleBbuInfo都有值 */
} _PACKED_1_ T_BbuInfo;

/* *************************DIAG**************************** */
/*单板诊断信息*/

typedef struct
{
    SWORD32  sdwDiagDeviceId;                                /* 诊断芯片ID */
    CHAR     cDiagDeviceName[MAX_DIAG_DEVICE_NAME_LEN];      /* 诊断对象名称 */
    SWORD32  sdwDiagPreStatus;                               /* 诊断上一次结果，正常为DEVICE_STATUS_OK，异常为DEVICE_STATUS_FALSE */
    SWORD32  sdwDiagCurStatus;                               /* 诊断本次结果， 正常为DEVICE_STATUS_OK，异常为DEVICE_STATUS_FALSE */
} _PACKED_1_ T_DiagOneDeviceInfo;

typedef struct
{
    SWORD32         sdwCtrlId;                                       /* 控制器ID,暂时定义为0、1，对应的宏定义CTRL0、CTRL1，出参*/
    SWORD32         sdwDeviceNum;                                    /* 传入参数后实际返回的设备数目 ,取值范围为0~MAX_DIAG_DEVICE_NUM，出参*/
    T_DiagOneDeviceInfo tDiagDeviceInfo[MAX_DIAG_DEVICE_NUM];        /* 诊断芯片的数组 ，数组中前sdwDeviceNum个值有效,   出参*/
} _PACKED_1_ T_DiagSingleDeviceInfo;

typedef struct
{
    SWORD32 sdwCtrlFlg;                              /* 控制器标志 ,暂时定义为0、1、2，对应的宏定义CTRL_LOCAL、CTRL_PEER、CTRL_DUAL， 入参*/
    SWORD32 sdwBoardNum;                             /* 诊断单板的数目，出参 */
    T_DiagSingleDeviceInfo tDiagSingleDeviceInfo[2]; /* 诊断信息列表，当 sdwCtrlFlg = 0/1 时,仅tDiagSingleDeviceInfoList[0]有值；当 sdwCtrlFlg = 2 时 ,tDiagSingleDeviceInfoList都有值，出参*/
} _PACKED_1_ T_DiagDeviceInfo;

/*BBU诊断信息*/

typedef struct
{
    SWORD32 sdwCtrlId;                              /* 控制器ID,暂时定义为0、1，对应的宏定义CTRL0、CTRL1 */
    SWORD32 sdwBbuwMv;                              /* BBU当前电压，单位：mV */
    SWORD32 sdwBbuwCapacity;                        /* BBU剩余电量百分比 */
    //SWORD32 sdwBbuWorkFlag;                        /* BBU充放电标志，正在充放电为DIAG_BBU_CHARGING(0)，不在充放电为DIAG_BBU_NOT_CHARGING(1) */
    SWORD32 sdwBbuPresentInfo;                      /* BBU是否在位，在位为DIAG_BBU_PRESENT(0)，不在位为DIAG_BBU_NOPRESENT(1) */
    SWORD32 sdwBbuCommunicate;                      /* BBU能否通信，能通信为BBU_COMMUNICATE_OK(0)，不能通信为BBU_COMMUNICATE_FAIL(2) */
    SWORD32 sdwBbuCharge;                           /* BBU能否充电，能充电为BBU_CHARGE_OK(0)，不能充电为BBU_CHARGE_FAIL(3) */
    SWORD32 sdwBbuDischarge;                        /* BBU能否放电，能放电为BBU_DISCHARGE_OK(0)，不能放电为BBU_DISCHARGE_FAIL(4) */
    //SWORD32 sdwBbuOverTemperature;                /* BBU是否过温，正常温度为BBU_NORMAL_TEMPERATURE(0)，过温为BBU_OVER_TEMPERATURE(5) */
    SWORD32 sdwBbuInvalid;                          /* BBU是否失效,未失效为BBU_VALID(0),失效为BBU_INVALID(6) */
    SWORD32 sdwBbuCapacity;                         /* BBU当前电量值，单位: mah */
    SWORD32 sdwBbuDeviceStatus;                     /* BBU状态，取值:正常(BBU_NORMAL,0)、异常(BBU_ABNORMAL,1)、电量不足(BBU_LOW_CAPACITY,2) */
    SWORD32 sdwBbuFaultFlag;                        /* 仅当BBU状态为BBU_ABNORMAL时有效，用于标识BBU是何种异常，
                                                                              取值: DIAG_BBU_NOPRESENT   表示BBU不在位
                                                                                    BBU_COMMUNICATE_FAIL 表示BBU不能通信
                                                                                    BBU_CHARGE_FAIL      表示BBU不能充电
                                                                                    BBU_DISCHARGE_FAIL   表示BBU不能放电
                                                                                    BBU_OVER_TEMPERATURE 表示BBU温度过高
                                                                                    BBU_INVALID          表示BBU失效 */
} _PACKED_1_ T_DiagSingleBatteryInfo;

typedef struct
{
    SWORD32 sdwCtrlFlg;                                    /* 控制器标志 ,暂时定义为0、1、2，对应的宏定义CTRL_LOCAL、CTRL_PEER、CTRL_DUAL,   入参*/
    SWORD32 sdwBbuNum;                                     /* 诊断BBU电源的数目，出参 */
    T_DiagSingleBatteryInfo tDiagSingleBatteryInfo[2];     /* 诊断信息列表，当 sdwCtrlFlg = 0/1 时,仅tDiagSingleBatteryInfo[0]有值,
                                                              当 sdwCtrlFlg = 2时,tDiagSingleBatteryInfo都有值*/
} _PACKED_1_ T_DiagBatteryInfo;

/* EPLD诊断项*/
typedef struct
{
    SWORD32 sdwCtrlId;                                     /* 控制器ID,暂时定义为0、1，对应的宏定义CTRL0、CTRL1*/
    SWORD32 sdwEpldFirmVer;                                /* EPLD固件版本号*/
    CHAR    cEpldLocation[MAX_DIAG_DEVICE_NAME_LEN];       /* EPLD的位置       */
    SWORD32 sdwEpldDeviceStatus;                           /* EPLD设备状态,正常为DEVICE_STATUS_OK，异常为DEVICE_STATUS_FALSE*/
} _PACKED_1_ T_DiagSingleEpldInfo;

typedef struct
{
    SWORD32 sdwCtrlFlg;                                    /* 控制器标志 ,暂时定义为0、1、2，对应的宏定义CTRL_LOCAL、CTRL_PEER、CTRL_DUAL,   入参*/
    SWORD32 sdwEpldNum;                                    /* 诊断Epld的数目，出参 */
    T_DiagSingleEpldInfo tDiagSingleEpldInfo[2];           /* 诊断信息列表，当 sdwCtrlFlg = 0/1 时,仅tDiagSingleEpldInfo[0]有值,当 sdwCtrlFlg = 2 时 ,tDiagSingleEpldInfo都有值*/
} _PACKED_1_ T_DiagEpldInfo;

/* CRYSTAL诊断项 */
typedef struct
{
    SWORD32  sdwCtrlId;                                   /* 控制器ID,暂时定义为0、1，对应的宏定义CTRL0、CTRL1 */
    SWORD32  sdwCrystalTotalNum;                          /* 晶振总个数 */
    SWORD32  sdwCrystalDeviceStatus;                      /* Crystal设备状态,正常为DEVICE_STATUS_OK，异常为DEVICE_STATUS_FALSE */
} _PACKED_1_  T_DiagSingleCrystalInfo;

typedef struct
{
    SWORD32 sdwCtrlFlg;                                   /* 控制器标志 ,暂时定义为0、1、2，对应的宏定义CTRL_LOCAL、CTRL_PEER、CTRL_DUAL,   入参*/
    SWORD32 sdwCrystalNum;                                /* 诊断晶振的数目，出参 */
    T_DiagSingleCrystalInfo tDiagSingleCrystalInfo[2];    /* 诊断信息列表，当 sdwCtrlFlg = 0/1 时,仅tDiagSingleCrystalInfo[0]有值,
                                                             当 sdwCtrlFlg = 2时,tDiagSingleCrystalInfo都有值*/
} _PACKED_1_ T_DiagCrystalInfo;

/* RTC诊断项 */
typedef struct
{
    SWORD32     sdwCtrlId;                               /* 控制器ID,暂时定义为0、1，对应的宏定义CTRL0、CTRL1*/
    SWORD32     sdwRtcDeviceStatus;                      /* Rtc设备状态,正常为DEVICE_STATUS_OK，异常为DEVICE_STATUS_FALSE */
} _PACKED_1_  T_DiagSingleRtcInfo;

typedef struct
{
    SWORD32 sdwCtrlFlg;                                  /* 控制器标志 ,暂时定义为0、1、2，对应的宏定义CTRL_LOCAL、CTRL_PEER、CTRL_DUAL,   入参*/
    SWORD32 sdwRtcNum;                                   /* 诊断Rtc的数目，出参 */
    T_DiagSingleRtcInfo tDiagSingleRtcInfo[2];           /* 诊断信息列表，当 sdwCtrlFlg = 0/1 时,仅tDiagSingleRtcInfo[0]有值,当 sdwCtrlFlg = 2 时 ,tDiagSingleRtcInfo都有值*/
} _PACKED_1_ T_DiagRtcInfo;

/* PM8001 诊断项 */
typedef struct
{
    SWORD32     sdwCtrlId;                              /* 控制器ID,暂时定义为0、1，对应的宏定义CTRL0、CTRL1*/
    SWORD32     sdwPmDeviceStatus;                      /* PM8001 设备状态,正常为DEVICE_STATUS_OK，异常为DEVICE_STATUS_FALSE*/
} _PACKED_1_  T_DiagSinglePmInfo;

typedef struct
{
    SWORD32 sdwCtrlFlg;                                 /* 控制器标志 ,暂时定义为0、1、2，对应的宏定义CTRL_LOCAL、CTRL_PEER、CTRL_DUAL,   入参*/
    SWORD32 sdwPmNum;                                   /* 诊断 PM8001 的数目，出参 */
    T_DiagSinglePmInfo tDiagSinglePmInfo[2];            /* 诊断信息列表，当 sdwCtrlFlg = 0/1 时,仅tDiagSinglePmInfo[0]有值,当 sdwCtrlFlg = 2 时 ,tDiagSinglePmInfo都有值*/
} _PACKED_1_ T_DiagPmInfo;

/* GE 诊断项 */
typedef struct
{
    SWORD32      sdwCtrlId;                             /* 控制器ID,暂时定义为0、1，对应的宏定义CTRL0、CTRL1*/
    BYTE         geStatus;                              /* GE端口总体状态 */
    SWORD32      sdwGeLInkStatus[4];                    /* GE端口使用,供ams单独使用 */
} _PACKED_1_  T_DiagSingleGeInfo;

typedef struct
{
    SWORD32 sdwCtrlFlg;                                /* 控制器标志 ,暂时定义为0、1、2，对应的宏定义CTRL_LOCAL、CTRL_PEER、CTRL_DUAL,   入参*/
    SWORD32 sdwGeNum;                                  /* 诊断GE 的数目，出参 */
    T_DiagSingleGeInfo tDiagSingleGeInfo[2];           /* 诊断信息列表，当 sdwCtrlFlg = 0/1 时,仅tDiagSingleGeInfo[0]有值,当 sdwCtrlFlg = 2 时 ,tDiagSingleGeInfo都有值*/
} _PACKED_1_ T_DiagGeInfo;

/* PCIE诊断 */
typedef struct
{
    SWORD32     sdwCtrlId;                             /* 控制器ID,暂时定义为0、1，对应的宏定义CTRL0、CTRL1*/
    SWORD32     sdwLinkSpeed;                          /* PCIE 连接速率*/
    SWORD32     sdwLinkWidth;                          /* PCIE 连接带宽x1~x4 x0表示无link */
    SWORD32     sdwBadTlpCount;                        /* TLP层坏包个数 */
    SWORD32     sdwBadDllpCount;                       /* DLLP层坏包个数 */
    SWORD32     sdwEepromStatus;                       /* PCIE 设备E2prom在位与否 有效与否 */
    SWORD32     sdwDllpStatus;                         /* DLLP 状态 */
    SWORD32     sdwPcieDeviceStatus;                   /* PCIE 设备状态,正常为DEVICE_STATUS_OK，异常为DEVICE_STATUS_FALSE*/
} _PACKED_1_  T_DiagSinglePcieInfo;

typedef struct
{
    SWORD32 sdwCtrlFlg;                                /* 控制器标志 ,暂时定义为0、1、2，对应的宏定义CTRL_LOCAL、CTRL_PEER、CTRL_DUAL,   入参*/
    SWORD32 sdwPcieNum;                                /* 诊断PCIE 的数目，出参 */
    T_DiagSinglePcieInfo tDiagSinglePcieInfo[2];       /* 诊断信息列表，当 sdwCtrlFlg = 0/1 时,仅tDiagSinglePcieInfo[0]有值,当 sdwCtrlFlg = 2 时 ,tDiagSinglePcieInfo都有值*/
} _PACKED_1_ T_DiagPcieInfo;

/* EEPROM诊断项  */
typedef struct
{
    SWORD32    sdwCtrlId;                             /* 控制器ID,暂时定义为0、1，对应的宏定义CTRL0、CTRL1*/
    SWORD32    sdwEepromDeviceStatus;                 /* Eeprom设备状态,正常为DEVICE_STATUS_OK，异常为DEVICE_STATUS_FALSE*/
} _PACKED_1_ T_DiagSingleEepromInfo;

typedef struct
{
    SWORD32 sdwCtrlFlg;                               /* 控制器标志 ,暂时定义为0、1、2，对应的宏定义CTRL_LOCAL、CTRL_PEER、CTRL_DUAL,   入参*/
    SWORD32 sdwEepromNum;                             /* 诊断Eeprom的数目，出参 */
    T_DiagSingleEepromInfo tDiagSingleEepromInfo[2];  /* 诊断信息列表，当 sdwCtrlFlg = 0/1 时,仅tDiagSingleEepromInfo[0]有值,当 sdwCtrlFlg = 2 时 ,tDiagSingleEepromInfo都有值*/
} _PACKED_1_ T_DiagEepromInfo;

/* 锁相环诊断项 */
typedef struct
{
    SWORD32  sdwCtrlId;                               /* 控制器ID,暂时定义为0、1，对应的宏定义CTRL0、CTRL1*/
    SWORD32  sdwClockDeviceStatus;                    /* 锁相环设备状态,正常为DEVICE_STATUS_OK，异常为DEVICE_STATUS_FALSE*/
} _PACKED_1_  T_DiagSingleClockInfo;

typedef struct
{
    SWORD32 sdwCtrlFlg;                                 /* 控制器标志 ,暂时定义为0、1、2，对应的宏定义CTRL_LOCAL、CTRL_PEER、CTRL_DUAL,   入参*/
    SWORD32 sdwClockNum;                                /* 诊断锁相环的数目，出参 */
    T_DiagSingleClockInfo tDiagSingleClockInfo[2];      /* 诊断信息列表，当 sdwCtrlFlg = 0/1 时,仅tDiagSingleClockInfo[0]有值,当 sdwCtrlFlg = 2 时 ,tDiagSingleClockInfo都有值*/
} _PACKED_1_ T_DiagClockInfo;

/* FC诊断项 */

/* IBMC诊断项 */
typedef struct
{
    SWORD32  sdwCtrlId;
    BYTE     sdwIbmcStatus;                             /* IBMC设备状态,正常为DEVICE_STATUS_OK，异常为DEVICE_STATUS_FALSE*/
} T_DiagSingleIbmcInfo;

typedef struct
{
    SWORD32 sdwCtrlFlg;                                 /* 控制器标志 ,暂时定义为0、1、2，对应的宏定义CTRL_LOCAL、CTRL_PEER、CTRL_DUAL,   入参*/
    SWORD32 sdwIbmcNum;                                 /* 诊断IBMC的数目，出参 */
    T_DiagSingleIbmcInfo    tDiagSingleIbmcInfo[2];     /* 诊断信息列表，当 sdwCtrlFlg = 0/1 时,仅tDiagSingleIbmcInfo[0]有值,当 sdwCtrlFlg = 2 时 ,tDiagSingleIbmcInfo都有值*/
} _PACKED_1_ T_DiagIbmcInfo;

typedef struct
{
    CHAR    cDiagDeviceName[MAX_DIAG_DEVICE_NAME_LEN];    /* 诊断对象名称，   出参  */
    CHAR    cDiagProperty[MAX_PROP_NAME_LEN];             /* 诊断对象属性，   出参  */
    CHAR    cDiagPropertyValue[MAX_PROP_VALUE_LEN];       /* 诊断对象属性值， 出参  */
} _PACKED_1_ T_DiagDeviceProperty;

/* ECC开关设置 */
typedef struct
{
    SWORD32     sdwEccSwitch;                           /* 入参: ECC检测打开开关: DIAG_ECC_SWITCH_OPEN 打开开关; DIAG_ECC_SWITCH_CLOSE关闭开关 */
} _PACKED_1_  T_DiagSingleEccSwitch;

typedef struct
{
    SWORD32 sdwCtrlFlg;                                 /* 入参: 控制器标志 ,暂时定义为0、1、2，对应的宏定义CTRL_LOCAL、CTRL_PEER、CTRL_DUAL,   入参*/
    SWORD32 sdwEccSwitchNum;                            /* 出参: 需要设置ECC开关的个数，出参 */
    T_DiagSingleEccSwitch  tDiagSingleEccSwitch[2];     /* 入参: 诊断信息列表，当 sdwCtrlFlg = 0/1 时,仅tDiagSingleEccSwitch[0]有值,当 sdwCtrlFlg = 2 时 ,tDiagSingleEccSwitch都有值*/
} _PACKED_1_ T_DiagEccSwitch;

/* 通用诊断对象结构体 */
typedef struct
{
    SWORD32                 sdwDiagRetNum;                                /* 诊断对象返回的记录数量， 出参 */
    T_DiagDeviceProperty    tDiagDeviceProperty[MAX_PROP_REC_NUM];        /* 所有的查询记录 */
} _PACKED_1_ T_DiagSingleDeviceRecord;

typedef struct
{
    SWORD32 sdwCtrlFlg;                                   /* 控制器标志 ,暂时定义为0、1、2，对应的宏定义CTRL_LOCAL、CTRL_PEER、CTRL_DUAL,  入参  */
    SWORD32 sdwDiagDeviceId;                              /* 诊断对象ID,  入参  */
    SWORD32 sdwDeviceNum;                                 /* 诊断对象的数目,  出参  */
    T_DiagSingleDeviceRecord tDiagSingleDeviceRecord[2];  /* 诊断信息列表,当 sdwCtrlFlg = 0/1 时,仅tDiagSingleDeviceInfo[0]有值,当 sdwCtrlFlg = 2 时 ,tDiagSingleDeviceInfo都有值*/
} _PACKED_1_ T_DiagDeviceRecord;

/* *************************Expander WUI Diag**************************** */
/*风扇信息*/
typedef struct
{
    SWORD32 sdwLevel;       /* 转速级别, 1-13级, 转速越快级别越高 */
    WORD16  sdwSpeed;       /* 转速, RPM, Round Per Minute */
    BYTE    bFanStatus;     /* 风扇状态,取值:DEVICE_STATUS_OK(值为0,风扇正常),DEVICE_STATUS_FALSE(值为1,风扇异常) */
} _PACKED_1_ T_FanInfo;

/*电源信息*/
typedef struct
{
    SWORD32 sdwVoltInCurrentValue;     /* 输入电压当前值 */
    SWORD32 sdwVoltInMaxValue;         /* 输入电压上限值 */
    SWORD32 sdwVoltInMinValue;         /* 输入电压下限值 */
    SWORD32 sdwVoltInStatus;           /* 电源输入电压状态, 正常为DEVICE_STATUS_OK, 异常为DEVICE_STATUS_FALSE */
    SWORD32 sdwVoltOutHighCurrentValue;/* 输出高电压当前值 */
    SWORD32 sdwVoltOutHighMaxValue;    /* 输出高电压上限值 */
    SWORD32 sdwVoltOutHighMinValue;    /* 输出高电压下限值 */
    SWORD32 sdwVoltOutHighStatus;      /* 电源输出高电压状态, 正常为DEVICE_STATUS_OK, 异常为DEVICE_STATUS_FALSE */
    SWORD32 sdwVoltOutLowCurrentValue; /* 输出低电压当前值 */
    SWORD32 sdwVoltOutLowMaxValue;     /* 输出低电压上限值 */
    SWORD32 sdwVoltOutLowMinValue;     /* 输出低电压下限值 */
    SWORD32 sdwVoltOutLowStatus;       /* 电源输出低电压状态, 正常为DEVICE_STATUS_OK, 异常为DEVICE_STATUS_FALSE */
    SWORD32 sdwPowerTempValue;         /* 电源温度实际值, Centigrade*/
    SWORD32 sdwPowerTempMaxValue;      /* 电源温度上限值 */
    SWORD32 sdwPowerTempMinValue;      /* 电源温度下限值 */
    SWORD32 sdwPowerTempStatus;        /* 电源温度状态, 正常为DEVICE_STATUS_OK, 异常为DEVICE_STATUS_FALSE */
    SWORD32 sdwPresentStatus;          /* 电源在位状态，正常为DEVICE_STATUS_OK, 异常为DEVICE_STATUS_FALSE */
} _PACKED_1_ T_PowerInfo;

/*单板温度信息*/
typedef struct
{
    SWORD32 sdwBoardTempValue;         /* 单板温度实际值, Centigrade */
    SWORD32 sdwBoardMaxTempValue;      /* 单板温度上限,即超过该温度应该告警 */
    SWORD32 sdwBoardMinTempValue;      /* 单板温度下限,即低于该温度应该告警 */
    SWORD32 sdwBoardTempStatus;        /* 单板温度状态, 正常为DEVICE_STATUS_OK, 异常为DEVICE_STATUS_FALSE */
    SWORD32 sdwCtrId;                  /* 单板槽位号,值为0 或者1 */
} _PACKED_1_ T_BoardInfo;

/*CPU温度信息*/
typedef struct
{
    SWORD32 sdwCpuTempValue;           /* CPU温度实际值, Centigrade   */
    SWORD32 sdwCpuMaxTempValue;        /* CPU温度上限,即超过该温度应该告警 */
    SWORD32 sdwCpuMinTempValue;        /* CPU温度下限,即低于该温度应该告警 */
    SWORD32 sdwCpuTempStatus;          /* CPU温度状态, 正常为DEVICE_STATUS_OK, 异常为DEVICE_STATUS_FALSE */
    SWORD32 sdwCtrId;                  /* 单板槽位号,值为0 或者1 */
} _PACKED_1_ T_CpuInfo;

/*箱体设备信息*/
typedef struct
{
    BYTE sdwChassisId;                 /*箱体ID*/
    BYTE sdwBoardNum;                  /*控制器单板数目*/
    BYTE ucFanNum;                     /*风扇个数*/
    BYTE ucPsNum;                      /*电源个数*/
    T_FanInfo    tFanInfo[8];          /*风扇信息, 槽位0对应tFanInfo[0]和tFanInfo[1], 槽位1对应tFanInfo[2]和tFanInfo[3]*/
    T_PowerInfo  tPowerInfo[4];        /*电源信息, 槽位0对应tPowerInfo[0], 槽位1对应tPowerInfo[1]*/
    T_BoardInfo  tBoardInfo[2];        /*单板信息, 槽位0对应tBoardInfo[0], 单控环境下只有tBoardInfo[0]有值*/
    T_CpuInfo    tCpuInfo[2];          /*CPU信息, 槽位0对应tCpuInfo[0], 单控环境下只有tCpuInfo[0]有值*/
} _PACKED_1_ T_DiagExpanderInfo;

/*所有箱体设备信息列表*/
typedef struct
{
    BYTE                sdwExpanderNum;                     /*箱体个数, 出参*/
    BYTE                sdwQueryFlag;                       /*查询箱体标志, DIAG_ALL_EXPANDER查询所有箱体, DIAG_SINGLE_EXPANDER表示查询单个箱体, 入参*/
    BYTE                sdwSingleChassisId;                 /*需查询的单个箱体信息的ID号, 入参*/
    T_DiagExpanderInfo  tExpanderInfo[MAX_UP_SUB_ENCL];     /*所有箱体信息列表, 入参*/
} _PACKED_1_ T_ExpanderInfoList;

/* *************************Board WUI Diag**************************** */
/*整板状态信息*/
typedef struct
{
    SWORD32 sdwCtrlId;                                     /* 控制器ID, 暂时定义为0、1, 对应的宏定义CTRL0、CTRL1*/
    SWORD32 sdwBoardStatus;                                /* 整板状态, 正常为DEVICE_STATUS_OK, 异常为DEVICE_STATUS_FALSE*/
} _PACKED_1_ T_DiagSingleBoardStatus;

typedef struct
{
    SWORD32 sdwCtrlFlg;                                    /* 控制器标志 ,暂时定义为0、1、2, 对应的宏定义CTRL_LOCAL、CTRL_PEER、CTRL_DUAL, 入参*/
    SWORD32 sdwBoardNum;                                   /* 诊断整板的数目, 出参 */
    T_DiagSingleBoardStatus tDiagSingleBoardStatus[2];     /* 诊断信息列表, 当 sdwCtrlFlg = 0/1 时, tDiagSingleBoardStatus[0]有值,当 sdwCtrlFlg = 2 时, tDiagSingleBoardStatus都有值*/
} _PACKED_1_ T_DiagBoardStatus;

/* *************************Hdd WUI Diag**************************** */
/*磁盘状态信息*/
typedef struct
{
    SWORD32 sdwSlotId;                                     /* 磁盘槽位号，取值0~27(ScanBox);  0~11(SPR10) */
    SWORD32 sdwEnclosureId;                                /* 箱体Id, 取值 0~实际箱体数*/
    SWORD32 sdwHddStatus;                                  /* 磁盘状态, 正常为DEVICE_STATUS_OK, 异常为DEVICE_STATUS_FALSE*/
} _PACKED_1_ T_DiagSingleHddStatus;

typedef struct
{
    SWORD32 sdwHddNum;                                               /* 磁盘个数，取值MAX_ENC_NUM_IN_SYS(4) * MAX_PD_NUM_IN_ENC(16) */
    T_DiagSingleHddStatus tDiagSingleHddStatus[MAX_PD_NUM_IN_SYS];   /* 磁盘诊断信息列表 */
} _PACKED_1_ T_DiagHddStatus;

/* *************************EM**************************** */
typedef struct
{
    WORD32   udwEncType;                    /* 扩展柜类型， */
} _PACKED_1_ T_EnclosureType;

/*风扇信息*/
typedef struct
{
    SWORD32 sdwLevel;       /* 转速级别 */
    WORD16  swSpeed;        /* 转速 */
    BYTE    bFanStatus;     /* 风扇状态,取值:DEVICE_STATUS_OK(值为0,风扇正常),DEVICE_STATUS_FALSE(值为1,风扇异常) */
} _PACKED_1_ T_EncFanInfo;

/*电源信息*/
typedef struct
{
    SWORD32 sdwBrokenFlag;   /*电源故障,0、1*/
    SWORD32 sdwPresentFlag;  /*电源在位标志,0、1*/
} _PACKED_1_ T_EncPsInfo;

/*电压信息*/
typedef struct
{
    SWORD32 sdwHighCritical;  /*最高门限*/
    SWORD32 sdwHighWarning;   /*最高告警*/
    SWORD32 sdwLowWarning;    /*最低告警*/
    SWORD32 sdwLowCritical;   /*最低门限*/
    SWORD32 sdwValue;         /*实际值*/
    SWORD32 sdwWarnFlag;      /*告警标记，取值OUT_FAILURE、OUT_WARNING、UNDER_FAILURE、UNDER_WARNING*/
} _PACKED_1_ T_EncVoltInfo;

/*温度信息*/
typedef struct
{
    SWORD32 sdwHighCritical;  /*最高门限*/
    SWORD32 sdwHighWarning;   /*最高告警*/
    SWORD32 sdwLowWarning;    /*最低告警*/
    SWORD32 sdwLowCritical;   /*最低门限*/
    SWORD32 sdwValue;         /*实际值*/
    SWORD32 sdwWarnFlag;      /*告警标记，取值OUT_FAILURE、OUT_WARNING、UNDER_FAILURE、UNDER_WARNING*/
} _PACKED_1_ T_EncTempratureInfo;

/*磁盘信息*/
typedef struct
{
    WORD64  uqwSasAddr;  /*磁盘SAS地址*/
    SWORD32 sdwSlotId;   /*槽位号*/
} _PACKED_1_ T_EncDiskInfo;

/*箱体拓扑结构*/
typedef struct
{
    BYTE ucVisted;                             /*访问标志*/
    BYTE ucChassisId;                          /*箱体ID*/
    BYTE ucSlotId;                             /*槽位ID*/
    BYTE ucDiskNum;                            /*硬盘个数*/
    BYTE ucSubexpnum;                          /*级联个数*/
    BYTE ucHeadflag;                           /*头标志*/
    BYTE ucSubId[SUBID_LEN];                  /*扩展柜ID*/
    BYTE ucSgName[MAX_DISKNAMELEN];           /*SG设备名*/
    WORD64   uqwSasAddr;                      /*EXPSAS地址*/
    T_EncDiskInfo tDiskinfo[MAX_DISK_NUM];    /*磁盘信息*/
    BYTE ucSub[MAX_UP_SUB_ENCL];              /*级联箱体ID列表*/
} _PACKED_1_ T_EncTopoInfo;

/*所有箱体拓扑结构*/
typedef struct
{
    BYTE ucExpcount;                            /*箱体个数*/
    T_EncTopoInfo tExpanders[MAX_UP_SUB_ENCL];  /*箱体链表头*/
} _PACKED_1_  T_EncTopoInfoList;

/* 单个磁盘的SMART信息 */
typedef struct
{
    SWORD32 sdwPdSlotId;                        /* 磁盘槽位号，取值0~27(ScanBox);  0~11(SPR10) */
    SWORD32 sdwPdEnclosureId;                   /* 箱体Id */
    BYTE ucAucPdName[12];                       /* 磁盘设备名 如sda */
    BYTE ucIsSupportSmart;                      /* 磁盘是否支持SMART */
    BYTE ucIsSmartEnable;                       /* 磁盘SMART功能是否开启 */
    BYTE ucSmartStatus;                         /* 磁盘的SMART状态是否OK */
    WORD32 dwSmartInfoCount;                    /*SMART属性个数*/
    T_DmSmartDetailInfo tSmartDetailInfo[30];   /* 磁盘SMART属性详细信息 */
    SWORD32 sdwSelfTestTime;                    /* 执行自检所需时间 */
} _PACKED_1_ T_DmSmartInfo;

typedef struct
{
    //SWORD32 sdwCtrlId;        /* 控制器Id ,暂时定义为0、1，对应的宏定义CTRL0、CTRL1*/
    SWORD32 sdwAction;          /*操作标志: 0/1/2，对应的宏定义为"OFF"、 "ON"、 */
} _PACKED_1_ T_DmPowerStatSwitch;

typedef struct
{
    WORD32 dwAction;
} _PACKED_1_ T_DmPdSlowSwitch;

typedef struct
{
    SWORD32 sdwPdSlotId;            /* 磁盘槽位号，取值0~27(ScanBox);  0~11(SPR10) */
    SWORD32 sdwPdEnclosureId;       /* 箱体Id */
    SWORD32 sdwTestType;            /*磁盘自检类型DM_SMART_SHORT_SELFTEST  DM_SMART_LONG_SELFTEST*/
    SWORD32 sdwTime;                /*返回自检事件 */
} _PACKED_1_ T_DmSmartTestCtl;

/*箱体设备信息*/
typedef struct
{
    BYTE ucChassisId;  /*箱体ID*/
    BYTE ucSlotId;  /*槽位ID*/
    BYTE ucFanNum;  /*风扇个数*/
    BYTE ucPsNum;  /*电源个数*/
    BYTE ucTemperatureNum;  /*温度传感器个数*/
    BYTE ucVoltNum;  /*电压传感器个数*/
    //BYTE ucDiskNum;  /*硬盘个数*/
    BYTE ucPeerStatus;/*对板在位标志*/
    BYTE ucSubId[SUBID_LEN]; /*扩展柜ID*/
    BYTE ucSgName[MAX_DISKNAMELEN];  /*SG设备名*/
    WORD64   uqwSasAddr;  /*EXPsaS地址*/

    T_EncFanInfo tFaninfo[MAX_FAN_NUM];  /*风扇信息*/
    T_EncPsInfo tPsinfo[MAX_PS_NUM];  /*电源信息*/
    T_EncVoltInfo tVoltinfo[MAX_VOLT_NUM];  /*电压信息*/
    T_EncTempratureInfo tTempratureinfo[MAX_TEMP_NUM];  /*温度信息*/

} _PACKED_1_ T_EncDeviceInfo;
/*箱体设备信息列表*/
typedef struct
{
    BYTE            ucExpcount;                   /*箱体个数*/
    SWORD32         sdwCtrlId;                    /* 控制器ID,暂时定义为0、1，对应的宏定义CTRL0、CTRL1*/
    T_EncDeviceInfo tExpanders[MAX_UP_SUB_ENCL];  /*箱体链表头*/
} _PACKED_1_  T_EncDeviceInfoList;
/*所有箱体设备信息列表*/
typedef struct
{
    SWORD32 sdwCtrlFlg;                                 /* 控制器标志 ,暂时定义为0、1、2，对应的宏定义CTRL_LOCAL、CTRL_PEER、CTRL_DUAL,   入参*/
    SWORD32 sdwCtrlNum;                                 /* 控制器的数目，出参 */
    T_EncDeviceInfoList tEncInfoList[2];                /* 诊断信息列表，当 sdwCtrlFlg = 0/1 时,仅tEncInfoList[0]有值,当 sdwCtrlFlg = 2 时 ,tEncInfoList[2]都有值*/
} _PACKED_1_ T_AllEncInfoList;

/***************************************Get System Information***********************************/
typedef  struct
{
    SWORD32 sdwCtrlId;
    WORD16  wBoardId;
    WORD16  wBoardSubId;
    BYTE    ucBoardBomId;          /**<母板bom id,取值:0-SPR11C,1-SPR11I,2-SPR11F(SPR11FS),3-SPR11C1,SPR11时有效 */
    BYTE    ucBoardSubBomId;       /**<子卡bom id,取值:0,1,无。母板bom id为2时，子卡bom id:0-SPR11F;1-SPR11FS, SPR11时有效 */
    WORD32  dwResered[9];         /** 保留字节 */
} _PACKED_1_ T_CtrlBoardInfo;
typedef  struct
{
    WORD32 sdwBroadType;          /** 单板类型，取值BROAD_UNKNOWN / BROAD_SBCJ / BROAD_SPR10 / BROAD_SPR11 / BROAD_PC */
    WORD32 dwCtrlNum;
    BYTE   dwValue;               /* BOARD_NAME_SAME 0表示画机架图，BOARD_NAME_NOTSAME  1则不画.提供给界面使用 */
    T_CtrlBoardInfo tCtrlBoardInfo[MAX_CTL_NUM];
} _PACKED_1_ T_SysBroadType;

typedef  struct
{
    CHAR   cSysName[USP_SYSTEM_NAME_MAX_LEN];          /* 系统名称 , 默认值为 ZXATCA_USP*/
} _PACKED_1_ T_SysNameInfo;

typedef  struct
{
    SWORD32   sdwSysReadyFlag;          /* 系统是否准备就绪标记，取值：USP_SYSTEM_NO_READY、USP_SYSTEM_READY*/
} _PACKED_1_ T_SysReadyFlag;

typedef  struct
{
    T_SysNameInfo tSysNameInfo;                           /* 系统名称, 出参*/

    CHAR   cVendor[USP_SYSTEM_VENDOR_MAX_LEN];            /* 供应商,    默认值为 ZTE, 出参*/

    CHAR   cModel[USP_SYSTEM_MODEL_MAX_LEN];              /* 型号,      默认值为 USP, 出参*/

    CHAR   cVersionName[USP_SYSTEM_VERSION_MAX_LEN];      /* 产品版本,  默认值为 V1.0, 出参*/

    CHAR   cSerialNum[USP_SYSTEM_SERIAL_NUM_MAX_LEN];     /* 产品序列号, 默认值为1111-1111, 出参*/

    CHAR   cSysState[USP_SYSTEM_STATE_MAX_LEN];           /* 系统状态, 单控运行或双控运行两种情况: Single Running或Dual Running, 出参 */
} _PACKED_1_ T_SysInfo;

/************************************Get Detail Controller Information*******************************/
typedef  struct
{
    SWORD32   sdwCtrlId;                                       /*  控制器ID  */
    SWORD32   sdwRamCapacity;                                  /*  RAM大小, 单位是M  */
    SWORD32   sdwCtrlRole;                                     /*  控制器角色  */
    SWORD32   sdwCtrlState;                                    /*  控制器状态  */
    CHAR      cCtrlSerial[USP_CONTROLLER_SERIAL_MAX_LEN];      /*  控制器序列号, 默认为控制器UUID  */
    CHAR      cCtrlName[USP_CONTROLLER_NAME_MAX_LEN];          /*  控制器名称 默认刀片名称, 比如SPR10或SBCJ */

} _PACKED_1_ T_CtrlSingleInfo;

typedef  struct
{
    SWORD32   sdwCtrlNumb;                   /* 控制器数目,  出参*/
    SWORD32   sdwCtrlAction;                 /* CTRL_LOCAL--本端, CTRL_PEER--对端, CTRL_DUAL--两端，设置控制器名称时使用, 入参 */
    T_CtrlSingleInfo   tCtrlSingleInfo[2];   /*  控制器详细信息列表,  出参 */
} _PACKED_1_ T_CtrlInfo;

typedef  struct
{
    SWORD32   sdwCtrlId;                     /* 控制器ID,双控的环境改变量取值0或者1, 入参 */
} _PACKED_1_ T_CtrlId;

/************************************Get System Boot Done Time**************************************/
typedef  struct
{
    SWORD32   sdwCtrlId;                                    /*  控制器ID  */
    T_ScsTime    tSysBootTime;                                 /*  系统启动完成时间  */
} _PACKED_1_ T_SysSingleBootTime;

typedef  struct
{
    SWORD32               sdwCtrlNumb;                      /* 控制器数目,  出参*/
    T_SysSingleBootTime   tSysSingleBootTime[2];            /* 系统启动完成时间列表,  出参 */
} _PACKED_1_ T_SysBootTime;

/******************************* 获取和设置预设事件的cache自动回写策略 ************************************/
typedef struct
{
    /* Cache自动直写策略开关，ON表示预定，OFF表示关，RST表示保留原值 */
    BYTE bFanFaultEvt;         /* 风扇Cache自动直写策略开关 */
    BYTE bPowerFaultEvt;       /* 电源Cache自动直写策略开关 */
    BYTE bBbuFaultEvt;         /* BBU的Cache自动直写策略开关 */
    BYTE bUpsConnLossEvt;      /* UPS连接丢失Cache自动直写策略开关 */
    BYTE bUpsBattFaultEvt;     /* UPS电池失效Cache自动直写策略开关 */
    BYTE bUpsOverloadEvt;      /* UPS过载Cache自动直写策略开关 */
    BYTE bOher;                /* 其他Cache自动直写策略开关 */
} _PACKED_1_ T_AutoWrThrPreSet;

/************************************Bond相关功能****************************************/
typedef struct
{
    WORD32 udwCardNo;           /* 子卡编号，即子卡槽位编号，取值1-4*/
    WORD32 udwPortType;           /* 端口类型，仅对业务口有效，取值: 1(BUSINESS_PORT_TYPE_GE)、2(BUSINESS_PORT_TYPE_10GE),缺省值1，入参*/
    WORD32 udwPortNo;             /* 设备编号 */
} _PACKED_1_ T_NetPort;

typedef struct
{
    WORD32 udwPortNum;                           /* Bond成员端口数目，入参*/
    T_NetPort tPort[MAX_BOND_PORT_NUM];          /* Bond成员端口信息列表， 入参*/
} _PACKED_1_ T_BondPortInfo;

typedef struct
{
    WORD32 udwCtrlId;                            /* 控制器ID， 入参*/
    CHAR   scBondName[MAX_BOND_NAME_LEN];        /* Bond名称， 入参*/
    T_BondPortInfo tBondPortInfo;                /* Bond中的成员端口信息*/
    WORD32 udwBondMode;                          /* Bond模式，取值1（BOND_MODE_802_3AD）、2（BOND_MODE_BALANCE_RR ），缺省值是2（BOND_MODE_BALANCE_RR ）入参*/
    WORD32 udwBondPolicy;                        /* Bond报文分发策略，取值1（BOND_POLICY_LAYER2）、2（BOND_POLICY_LAYER2_3）、3（BOND_POLICY_LAYER3_4），缺省值是3（BOND_POLICY_LAYER3_4）,入参*/
} _PACKED_1_ T_BondCreate;

typedef struct
{
    WORD32 udwCtrlId;                            /* 控制器ID， 入参*/
    CHAR  scBondName[MAX_BOND_NAME_LEN];         /* Bond名称， 入参*/
} _PACKED_1_ T_BondName;

typedef struct
{
    WORD32 udwCtrlId;                            /* 控制器ID， 出参*/
    CHAR   scBondName[MAX_BOND_NAME_LEN];        /* Bond名称， 出参*/
    T_BondPortInfo tBondPortInfo;                /* Bond中的成员端口信息， 出参*/
    WORD32 udwBondMode;                          /* Bond模式， 出参*/
    WORD32 udwBondPolicy;                        /* Bond报文分发策略， 出参*/
    CHAR   cIpAddr[MAX_IP_LEN];                  /* IP地址 ， 出参*/
    CHAR   cNetmask[MAX_IP_LEN];                 /* 子网掩码 ， 出参*/
    WORD32 udwPortMtu;                           /* Bond MTU， 出参*/
    BYTE   ucMacData[PORT_MAC_DATA_SIZE];        /* MAC 地址， 出参*/
} _PACKED_1_ T_BondInfo;

typedef struct
{
    WORD32 udwBondNum;                            /* 系统中Bond数目， 出参*/
    T_BondInfo  tBondInfo[MAX_BOND_NUM];          /* 系统中Bond信息列表,前udwBondNum个元素有效， 出参*/
} _PACKED_1_ T_BondInfoList;

typedef struct
{
    WORD32 udwCtrlId;                            /* 控制器ID， 入参*/
    CHAR  scBondName[MAX_BOND_NAME_LEN];         /* Bond名称，入参*/
    T_BondPortInfo tBondPortInfo;                /* 所操作的Bond中的成员端口信息*/
} _PACKED_1_ T_BondPortSet;

typedef struct
{
    WORD32 udwCtrlId;                            /* 控制器ID，入参*/
    CHAR   scBondName[MAX_BOND_NAME_LEN];        /* Bond名称，入参*/
    WORD32 udwBondMode;                          /* Bond模式，取值1（BOND_MODE_802_3AD）、2（BOND_MODE_BALANCE_RR ）,入参*/
} _PACKED_1_ T_BondMode;

typedef struct
{
    WORD32 udwCtrlId;                            /* 控制器ID，入参*/
    CHAR   scBondName[MAX_BOND_NAME_LEN];        /* Bond名称，入参*/
    WORD32 udwBondPolicy;                        /* Bond报文分发策略，取值1（BOND_POLICY_LAYER2）、2（BOND_POLICY_LAYER2_3）、3（BOND_POLICY_LAYER3_4），入参*/
} _PACKED_1_ T_BondPolicy;

typedef struct
{
    WORD32 udwCtrlId;                            /* 控制器ID， 入参*/
    WORD32 udwPortNum;                           /* Bond成员端口数目，入参*/
    T_NetPort tPort[MAX_NET_PORT_NUM];              /* Bond成员端口信息列表， 入参*/
} _PACKED_1_ T_PortList;

typedef struct
{
    WORD32 udwCtrlId;                            /* 控制器ID，入参*/
    CHAR   scBondName[MAX_BOND_NAME_LEN];        /* Bond名称，入参*/
    CHAR   cIpAddr[MAX_IP_LEN];                  /* IP地址 */
    CHAR   cNetmask[MAX_IP_LEN];                 /* 子网掩码 */
} _PACKED_1_ T_BondNetInfo;

typedef struct
{
    WORD32 udwCtrlId;                            /* 控制器ID，入参*/
    CHAR   scBondName[MAX_BOND_NAME_LEN];        /* Bond名称，入参*/
    WORD32 udwPortMtu;                           /* Bond MTU, 入参 */
} _PACKED_1_ T_BondMtu;

typedef struct
{
    WORD32 udwCtrlId;                            /* 控制器ID，入参*/
    CHAR   scBondName[MAX_BOND_NAME_LEN];        /* Bond名称，入参*/
    BYTE   ucMacData[PORT_MAC_DATA_SIZE];        /* MAC 地址，入参*/
} _PACKED_1_ T_BondMac;

typedef struct
{
    WORD32 udwCtrlId;                   /* 控制器ID， 入参*/
    WORD32 udwBondNameNum;              /* 可用的bond名数目， 出参*/
    CHAR   scBondName[MAX_BOND_NUM][MAX_BOND_NAME_LEN];   /*可用的bond名称列表，默认给用户使用下标为scBondName[0], 出参*/
} _PACKED_1_ T_UsableBondNameList;

typedef struct
{
    WORD32 udwLunUsableNum;                         /* 可用的LunId数目， 出参*/
    WORD32 udwLunIndex[MAX_LUN_NUM_IN_MAP_GROUP];   /*可用的LunId列表，出参*/
    CHAR   cMapGrpName[MAX_MAPGRP_NAME_LEN];        /* 映射组名称,不能为空,入参*/
} _PACKED_1_ T_UsableLunIdList;

/************************************系统简要信息结构体说明****************************************/

/* 获取普通卷简要信息*/
typedef struct
{
    CHAR      cVolName[MAX_BLK_NAME_LEN]; /* Vol名称*/
    SWORD32   sdwOwned;                   /* 卷的所属虚拟对象(vd/pool)类型，取值:VOL_IN_VD(0) ---表示vol属于VD, VOL_IN_POOL(1) ---表示vol属于pool */
    CHAR      cVoName[MAX_BLK_NAME_LEN];  /* 卷的所属虚拟对象(vd/pool)名称*/
    WORD64    uqwFreeCapacity;         /*卷的所属虚拟对象空闲容量,单位KB*/
    WORD64    uqwCapacity;                /* 卷容量信息  ,单位：KB*/
    SWORD32   sdwSnapNum;                 /* 以该卷为源卷的快照卷个数 */
    SWORD32   sdwCloneNum;                /* 以该卷为源卷的克隆卷个数 */
    SWORD32   sdwMirrorNum;               /* 以该卷为源卷的镜像卷个数 */
    SWORD32   sdwSnapPlanNum;             /* 以该卷为源卷的定时快照个数*/
} _PACKED_1_ T_VolSimpleInfo;

typedef  struct
{
    SWORD32         sdwVolNum;                                       /* 系统中虚拟盘数目 */
    T_VolSimpleInfo tVolSimpleInfo[MAX_NORM_VOL_NUM_IN_SYS];         /* 系统中普通卷简要列表*/
} _PACKED_1_ T_VolSimpleInfoList;

/* pool上的卷简要信息列表*/
typedef struct
{
    CHAR      cVolName[MAX_BLK_NAME_LEN]; /* Vol名称*/
    SWORD32   sdwState;                   /* eVolState , vol state defined in struct eVolState,取值VOL_S_GOOD(0),
                                             VOL_S_FAULT(1),  VOL_S_ERR(2),VOL_S_CHUNKSIZE_MIGRATION(3),
                                             VOL_S_EXPAND(4),VOL_S_UNREADY(5),VOL_S_READONLY(12), VOL_S_INVALID(0xffff)
                                          */
    T_ScsTime tCreateTime;                /* 创建时间  */
    WORD64    uqwCapacity;                /* 卷容量信息  ,单位：KB*/
    SWORD32   sdwSnapNum;                 /* 以该卷为源卷的快照卷个数 */
    SWORD32   sdwCloneNum;                /* 以该卷为源卷的克隆卷个数 */
    SWORD32   sdwMirrorNum;               /* 以该卷为源卷的镜像卷个数 */
    SWORD32   sdwSnapPlanNum;             /* 以该卷为源卷的定时快照个数*/
} _PACKED_1_ T_VolSimpleInfoOnPool;

typedef  struct
{
    CHAR     scPoolName[MAX_BLK_NAME_LEN];                             /* Pool名称,不能为空，入参*/
    SWORD32  sdwVolNum;                                                /* 卷的数目 */
    T_VolSimpleInfoOnPool tVolSimpleInfo[MAX_VOL_NUM_ON_POOL];         /* pool中普通卷简要列表，前sdwVolNum个元素有效*/
} _PACKED_1_ T_VolSimpleInfoListOnPool;

/* 系统简要信息*/
typedef  struct
{
    SWORD32   sdwCtrlNum;                   /* 控制器数目,出参*/
    SWORD32   sdwCtrlId[MAX_CTL_NUM];       /* 控制器Id列表,数值表示,出参 */
} _PACKED_1_ T_CtrlIdList;

typedef  struct
{
    /* 系统信息*/
    CHAR          cSysName[USP_SYSTEM_NAME_MAX_LEN];         /* 系统名称 , 字符串表示，出参*/
    CHAR          cSysState[USP_SYSTEM_STATE_MAX_LEN];       /* 系统状态, 单控运行或双控运行两种情况: Single Running或Dual Running, 出参 */
    T_CtrlIdList  tCtrlIdList;                               /* 控制器ID列表，出参*/
    T_SysTime     tSysTime;                                  /* 系统本地时间，包括年、月、日、时、分、秒*/

    /* 存储对象信息*/
    SWORD32  sdwVdNum;                                       /* 系统中虚拟盘总数目 */
    SWORD32  sdwPoolNum;                                     /* 系统中存储池总数目*/
    WORD64   uqwTotalCapacity;                               /* 虚拟对象(vd/pool)总容量,即所有pool、vd总容量之和,单位KB */
    WORD64   uqwUsedCapacity;                                /* 虚拟对象(vd/pool)已使用容量,即所有pool、vd已使用容量之和,单位KB*/
    WORD64   uqwFreeCapacity;                                /* 虚拟对象(vd/pool)空闲容量,即所有pool、vd空闲容量之和,单位KB */
    SWORD32  sdwMapGrpNum;                                   /* 系统中映射组数目 */

    /* 任务相关信息*/
    SWORD32 sdwTaskNum;                                     /* 后台任务数目*/
    SWORD32 sdwRunningTaskNum;                              /* 运行状态的后台任务数目*/
    SWORD32 sdwScheduleNum;                                 /* 计划任务数目*/

    /* 磁盘信息*/
    SWORD32     sdwDiskNum;                                 /* 系统中总磁盘数目 */
    SWORD32     sdwUnusedDiskNum;                           /* 系统中空闲磁盘数目 */
    WORD64      uqwDiskTotalCapacity;                       /* 磁盘总容量,单位KB*/
    WORD64      uqwUnusedDiskTotalCapacity;                 /* 磁盘总容量,单位KB*/

} _PACKED_1_ T_SystemSimpleInfo;

/* 虚拟对象(vd/pool)简要信息*/
typedef struct
{
    CHAR        cVoName[MAX_BLK_NAME_LEN];     /* 虚拟对象名称*/

    WORD64      uqwTotalCapacity;              /* 虚拟对象容量,单位KB */
    WORD64      uqwUsedCapacity;               /* 虚拟对象(vd/pool)已使用容量,单位KB*/
    WORD64      uqwFreeCapacity;               /* 虚拟对象(vd/pool)空闲容量,单位KB */
    T_ScsTime   tCreateTime;                   /* 虚拟对象创建时间，年、月、日、时、分、秒 */
    SWORD32     sdwState;                      /* 虚拟对象状态：
                                                         VD取值：VD_GOOD(1)/VD_FAULT(2)/VD_DEGRADE(4)/VD_RECING(8)/VD_RECERR(16)/VD_SCSFAULT(32)/VD_SCSINITING(64)/VD_EXPANDING(128)/VD_RELEVELING(256)
                                                         Pool取值：POOL_GOOD(0)/POOL_DAMAGED(1)/POOL_OFFLINE(2)/POOL_OFFLINE(3)/POOL_FAULT(4)/POOL_LOADING(5)/POOL_RECING(6)
                                                      */
} _PACKED_1_ T_VoSimpleInfo;

typedef  struct
{
    SWORD32         sdwVdNum;                                       /* 系统中虚拟盘数目 */
    T_VoSimpleInfo  tVdSimpleInfo[MAX_VD_NUM_IN_SYS];               /* 系统中所有VD简要信息列表*/
    SWORD32         sdwPoolNum;                                     /* 系统中存储池数目 */
    T_VoSimpleInfo  tPoolSimpleInfo[MAX_POOL_NUM_IN_SYS];           /* 系统中所有VD简要信息列表*/
} _PACKED_1_ T_VoSimpleInfoList;

/********************************MTS测试仪相关的结构体说明******************************************/
/********************************除特殊说明外, 结构体成员都为出参***********************************/

/****************************************单板公共项测试*********************************************/
/* 工作EPLD自检 */
typedef struct
{
    WORD32 dwStandardValue;   /* 标准值  */
    WORD32 dwReadValue;       /* 读出值  */
    WORD32 dwCheckResult;     /* 判断值  */
    WORD32 dwTimeoutMax;      /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Work_Epld_Self;

/* 工作EPLD信息读取 */
typedef struct
{
    WORD32 dwBoardId;         /* 单板ID        */
    WORD32 dwPcbVer;          /* 单板pcb版本号 */
    WORD32 dwBomVer;          /* 单板bom料单   */
    WORD32 dwTimeoutMax;      /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Work_Epld_Info;

/* 启动EPLD信息读取 */
typedef struct
{
    WORD32 dwBoardId;         /* 单板ID        */
    WORD32 dwPcbVer;          /* 单板pcb版本号 */
    WORD32 dwBomVer;          /* 单板bom料单   */
    WORD32 dwTimeoutMax;      /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Boot_Epld_Info;

/* 电子条形码扫描 */
typedef struct
{
    BYTE   cLableInfo[MAX_INFO_LABLE_LENGTH]; /* 条形码 */
    WORD32 dwTimeoutMax;                      /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Lable_Info;

/* 单板硬件地址读取 */
typedef struct
{
    WORD32   dwBackBoardId;    /* 6位测试背板ID */
    BYTE     cSlotId;          /* 槽位号 */
    WORD32   dwTimeoutMax;      /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Phy_Addr_Info;

/* 在位信号测试 */
typedef struct
{
    BYTE     cOnlieFlag;        /* 在位标志 */
    WORD32   dwTimeoutMax;      /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Online_Flag;

/* CPU外挂DDR3测试 */
typedef struct
{
    WORD16  wMtsType;      /* 入参，测试类型:MTS_FT,  功能测试:  MTS_HT,       高温       */
    BYTE    cCheckResult;  /* 出参，测试结果:MTS_DDR_GOOD 测试通过;  MTS_DDR_NOT_GOOD  测试不通过 */
    WORD32  dwTimeoutMax;  /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Ddr;

/* NVRAM芯片测试 */
typedef struct
{
    WORD16  wMtsType;       /* 入参，测试类型:MTS_FT,  功能测试: MTS_HT,      高温*/
    BYTE    cCheckResult;   /* 出参：测试结果:MTS_NVRAM_GOOD 测试通过; MTS_NVRAM_NOT_GOOD 测试不通过 */
    WORD32  dwTimeoutMax;   /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Nvram;

/* 版本FLASH测试 */
typedef struct
{
    WORD16  wMtsType;     /* 入参，测试类型:MTS_FT,  功能测试:
                                            MTS_HT,  高温测试
                                            MTS_MO_COMPA   版本比较
                          */
    BYTE    cCheckResult; /* 出参：测试结果 */
    WORD32  dwTimeoutMax; /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Verflash;

/* 板内时钟电路测试 */
typedef struct
{
    WORD16  wMtsClockType;  /* 入参：MTS_25M_CLOCK, MTS_33_CLOCK...*/
    BYTE    cCheckResult;   /* 出参：MTS_CLOCK_GOOD      测试通过
                                   MTS_CLOCK_NOT_GOOD   测试不通过*/
    WORD32  dwTimeoutMax;   /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Clock;

/* 面板指示灯测试 */
typedef struct
{
    WORD32  dwLedId;      /* < 入参:灯id，统一编号            */
    WORD32  dwLedColor;   /* < 入参:LED颜色，对单色灯取默认值 */
    WORD32  dwFlashType;  /* < 入参:设置当前闪灯方式          */
    WORD32  dwTimeoutMax; /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Led;

/* 看门狗复位测试 */
typedef struct
{
    WORD32  dwMtsType;    /* 入参，使能看门狗:MTS_ENABLE_WTG,  禁用看门狗: MTS_DISABLE_WTG, */
    WORD32  dwTimeoutMax; /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Wtg;

/* 温度传感器测试 */
typedef struct
{
    /* 数组下标0代表LM_93  1代表75_1, 2代表75_2, 3代表75_2 4代表75_3 */
    BYTE    cSenorStatus[5];  /* 出参; MTS_SENOR_GOOD正常  MTS_SENOR_NOT_GOOD 不正常 */
    SWORD32 sdwSenorValue[5]; /* 出参; 传感器的实际温度 */
    BYTE    cEncDevId;          /* 扩展柜号 */
    WORD32  dwTimeoutMax;     /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Senor;

/* RTC实时时钟电路测试 */
typedef struct
{
    BYTE    cCheckResult;   /* 出参：MTS_RTC_GOOD        测试通过
                                    MTS_RTC_NOT_GOOD    测试不通过 */
    WORD32  dwTimeoutMax;   /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Rtc;

/* 面板GE口环回测试 */
typedef struct
{
    WORD16  wMtsType;       /* 入参，测试类型:MTS_FT,  功能测试: MTS_HT,      高温*/
    BYTE    cCheckResult[4];   /* 出参：测试结果:MTS_GE_GOOD 测试通过; MTS_GE_NOT_GOOD 测试不通过 */
    WORD32  dwTimeoutMax;   /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Ge;

/* 面板调试网口作为通信链路测试 */
typedef struct
{
    BYTE    cCheckResult;   /* 出参：MTS_LINK_GOOD       测试通过
                                    MTS_LINK_NOT_GOOD   测试不通过 */
    WORD32  dwTimeoutMax;   /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Conn_Link;

/********************************* 以下为SPR12单板公共功能测试 ********************************/

/* 多核CPU核数测试 */
typedef  struct
{
    WORD32   dwEquInfo; //表示测试设备情况
    WORD32   dwResult; //为0测试成功，为1测试失败
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_CpuCore;

/* 获取Cpu外存容量 */
typedef  struct
{
    WORD32   dwEquInfo; //bit位表示测试设备情况
    WORD32   dwSize; //返回外存容量
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_CpuMemorySize;

/* Cpu外存测试 */
typedef  struct
{
    WORD32   wMtsType;  //测试类型
    WORD32   dwEquInfo; //表示测试设备情况
    WORD32   dwResult; //0测试成功，为1测试失败
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_CpuMemoryTest;

/* CPU外存SPD信息获取 */
typedef struct
{
    BYTE    cSpdInfoVer;          /**< 出参: SPD信息版本号,为未来扩展使用 */
    BYTE    cCont_code;             /**< 出参: 计算厂家ID时用的,SPD寄存器中0x7f的个数 */
    BYTE    cHex_byte;              /**< 出参: 计算厂家ID时用的,SPD寄存器中除0x7f外的数值 */
    BYTE    cRsv;                 /**< 出参: 填充字段 */
    BYTE    cMemSlotId;           /**< 出参: 内存条插槽位置,取值范围1~8 */
    BYTE    cMemType;             /**< 出参: 内存类型,取值范围 BSP_MEM_TYPE_SDRAM,BSP_MEM_TYPE_DDR,BSP_MEM_TYPE_DDR2,BSP_MEM_TYPE_DDR3 */
    BYTE    cModuleManufactureLocation; /**< 出参: 产地编码,SDRAM、DDR、DDR3为必选项,DDR2为可选 */
    BYTE    cSpdRev;              /**< 出参: 内存条SPD修正码(SPD Revision),1.0(0x10)以上为量产版本 */
    BYTE    cManufactureId[8];         /**< 出参: 生产厂家ID,SDRAM、DDR、DDR2为8个字节,DDR3为两个字节,一般只用第一个字节,后续填0 */
    BYTE    cManufacturerSpecData[32]; /**< 出参: 内存条模块附加信息,SDRAM、DDR、DDR2 29个字节,为必选项;DDR3为26个节,为可选项 */
    BYTE    cModulePartNum[18];  /**< 出参: 内存条元件代码(Module Part Number),以ASCII码表示,18个字节长度,不用的字段以空格(0x20)表示。SDRAM为必选项,DDR、DDR2、DDR3为可选项 */
    WORD16  wMemSize;               /**< 出参: 内存条大小, 以MByte为单位 */
    WORD16  wModuleManufacturDate;  /**< 出参: 内存条模块制造日期(Module Manufacturing Date),BCD码 */
    WORD16  wModuleRevisionCode;    /**< 出参: 内存条模块修定码(Module Revision Code), 2个字节, 用于内存厂商跟踪生产的批次, DDR3为可选项 */
    WORD32  dwModuleSerialNumber;   /**< 出参: 为内存条模块维护的唯一序列码,4个字节,为必选项 */
} _PACKED_1_ T_MTS_SPD_INFO;

typedef struct
{
    BYTE     cRackId;           /**< 出参:机架号,1~32   */
    BYTE     cShelfId;          /**< 出参:机框号,1~4    */
    BYTE     cSlotId;           /**< 出参:槽位号,1~28   */
    BYTE     cCpuDspId;         /**< 出参:CPU(DSP)ID号,1~32    */
    BYTE     cMemSlotNum;       /**< 出参:总的内存条槽数,暂时只支持8个内存条*/
    BYTE     cOnboardType;      /**< 出参:RAM在位类型, 板载颗粒 或 DIMM内存条 */
    BYTE     cRsv[2];           /**< 出参:保留字节*/
    T_MTS_SPD_INFO  tMemSpdInfo[MTS_MAX_SPD_NUM];

    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_CpuSpdInfo;

/* Cpu SPD信息校验 */
typedef  struct
{
    WORD32   wMtsType;  //测试类型
    WORD32   dwEquInfo; //表示测试设备情况
    WORD32   dwResult; //为0测试成功，为1测试失败
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_CpuSpdInfoCheck;

/* Flash测试 */
typedef  struct
{
    WORD32   wMtsType;  //测试类型
    WORD32   dwEquInfo; //表示测试设备情况
    WORD32   dwResult; //为0测试成功，为1测试失败
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_FlashTest;

/* WATCHDOG使能 */
typedef  struct
{
    WORD32   dwEquInfo; //表示测试设备情况
    WORD32   dwResult; //为0测试成功，为1测试失败
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_WDogEnable;

/* WATCHDOG喂狗 */
typedef  struct
{
    WORD32   dwEquInfo; //表示测试设备情况
    WORD32   dwResult; //为0测试成功，为1测试失败
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_WDogFeeding;

/* RTC时钟芯片测试 */
typedef  struct
{
    WORD32   dwEquInfo; //表示测试设备情况
    WORD32   dwResult; //为0测试成功，为1测试失败
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_ClockRtcTest;

/* 点灯测试 */
typedef  struct
{
    WORD32   wMtsType;  //测试类型
    WORD32   dwEquInfo; //表示测试设备情况
    WORD32   dwResult; //为0测试成功，为1测试失败
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_LedTest;

/* 固件信息查询 */
typedef  struct
{
    WORD32   dwFirmNum;
    WORD32   dwFirmTestType;
    WORD32   dwFirmType;
    WORD32   dwFirmLocation;
    WORD32   dwFirmDevFuncId;

    WORD32   dwEquInfo[4]; //表示测试设备情况
    WORD32   dwResult[4]; //为0测试成功，为1测试失败
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_FirmInfoTest;

/* 单板物理信息 */
typedef struct
{
    WORD32  wMtsType;      /* 入参  位置信息 */

    WORD32  dwBitMap[4];        //dwBitMap的值

    WORD32  dwBordId;           //单板id
    WORD32  dwBordBomVer;       //单板Bom版本号
    WORD32  dwBordPcbVer;       //单板pcb版本号
    WORD32  dwBordPcbBatch;     //单板pcb批次号

    WORD32  dwSubCardSiteInfo;  //子卡在位信息
    WORD32  dwSubCardId;        //子卡ID
    WORD32  dwSubCardPcbNum;    //子卡PCB号
    WORD32  dwSubCardPcbId;     //子卡bomID

    WORD32  dwCpuSubCardId;     //CPU子卡的ID
    WORD32  dwCpuSubCardPcbId;  //CPU子卡的PCBID
    WORD32  dwCpuSubCardBomId;  //CPU子卡的BOMID
    WORD32  dwCpuSubCardEpldVer;//CPU子卡的EPLD版本号

    WORD32  dwBordTpye;         //背板类型
    WORD32  dwBordVer;          //背板版本号
    WORD32  dwBordFrameSlotInfo;//单板所在架框槽的信息

    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_Brd_PhyInfoTest;
/*
typedef  struct
{
    WORD32   wMtsType;  //测试类型
    WORD32   dwEquInfo; //表示测试设备情况
    WORD32   dwResult; //0测试成功，为1测试失败
    WORD32   dwTimeoutMax;
}_PACKED_1_ T_Mts_Check_BrdPhyInfoTest;
*/

/* 单板上PLL和晶振测试 */
typedef  struct
{
    WORD32   dwEquInfo; //表示测试设备情况
    WORD32   dwResult; //为0测试成功，为1测试失败
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_OnBoardClkTest;

/* 获取电子条码测试 */
typedef  struct
{

    WORD32     dwEquInfo; /* 条形码 */
    WORD32   dwResult; //为0测试成功，为1测试失败
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_BrdSerialNumTest;

/*MAC+PHY芯片自检*/
typedef  struct
{
    WORD32   dwBMValue; //表示bitmap
    WORD32   dwPhyResult[MTS_MAX_PORT_NUM]; //端口测试结果，为0测试成功，为1测试失败
    WORD32   dwMacResult[MTS_MAX_PORT_NUM]; //Phy自测结果
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_MacSelfTest;

/* 端口流量测试设置 */
typedef  struct
{
    WORD32   wMtsType;
    WORD32   dwEquInfo; //表示测试设备情况
    WORD32   dwResult;     //为0测试成功，为1测试失败
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_DbgCircleTest;

/* 硬盘测试 */
typedef  struct
{
    WORD32   dwTestType;   //测试类型，入参, 取值范围:1,3,6,11,14
    WORD32   dwEquInfo; //表示测试设备情况
    WORD32   dwResult;     //为0测试成功，为1测试失败
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_Hdd;

/* PCI桥自检测试 */
typedef  struct
{
    WORD32   dwMtsType;
    WORD32   dwEquInfo; //表示测试设备情况
    WORD32   dwResult; //为0测试成功，为1测试失败
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_PciBridgeTest;

/********************************* 以上SPR12单板公共功能测试 ********************************/

typedef struct
{
    /* 数组下标0代表LM_93  1代表75_1, 2代表75_2, 3代表75_2 4代表75_3 */
    BYTE    cSenorStatus[5];  /* 出参; MTS_SENOR_GOOD正常  MTS_SENOR_NOT_GOOD 不正常 */
    SWORD32 sdwSenorValue[5]; /* 出参; 传感器的实际温度 */
    SWORD32 sdwSenorVolt;     /* 出参; LM_93的实际电压 */
    BYTE    cEncDevId;        /* 扩展柜号 */
    WORD32  dwTimeoutMax;     /* 超时最大值 */
} _PACKED_1_ T_Mts_Senor;

typedef struct
{
    WORD32 dwCheckType;       /* 可选入参,查询类型 */
    WORD32 dwCheckResult;     /* 判断值  */
    WORD32 dwTimeoutMax;      /* 超时最大值 */
} _PACKED_1_ T_Mts_Board;

typedef struct
{
    WORD16 wFuncCardID;         /* 出参:功能子卡ID */
    WORD16 wBomID;              /* 出参:功能子卡BOM ID */
    WORD16 wPcb;                /* 出参:PCB号 */
    WORD16 wOnBoard;            /* 出参:功能子卡在位信息 */
    WORD32 dwCheckResult;       /* 出参:判断值  */
    WORD32 dwTimeoutMax;        /* 超时最大值 */
} _PACKED_1_ T_Mts_10G;

typedef struct
{
    T_Mts_10G tMts10G[2];
    WORD32    dwTimeoutMax;
} _PACKED_1_ T_Cmt_10G;

/* 江国才确认光模块最大数目为32个 */
typedef struct
{
    WORD32 dwTotalSffNum;            /* 光模块数目 */
    WORD32 dwExistInfo[32];          /* 在位信息 */
    WORD32 dwRate[32];               /* 光模块速率，单位：MBd(Mbit/s) */
    WORD32 dwType[32];               /* 光模块类型， BSP_LSSP_SFF_OM_TYPE(2) 多模光模块；BSP_LSSP_SFF_SMF_TYPE(1) 单模光模块
                                          BSP_LSSP_SFF_COPPER_TYPE(3) 电口模块 */
    WORD32 dwCheckResult;            /* 出参:判断值  */
    WORD32 dwTimeoutMax;             /* 超时最大值 */
} _PACKED_1_ T_Mts_Sff;

typedef struct
{
    T_Mts_Sff tMtsSff[2];
    WORD32    dwTimeoutMax;
} _PACKED_1_ T_Cmt_Sff;

typedef struct
{
    WORD32 dw10GNum;                          /* 出参，支持 10G能力的10G口数目 */
    WORD32 dwTestResult[TCS_10G_PORT_NUM];    /* 出参，自测试结果 */
    WORD32 dwCheckResult;                     /* 出参: 判断值  */
    WORD32 dwTimeoutMax;                      /* 入参，超时最大值 */
} _PACKED_1_ T_Mts_10GSelfTest;

typedef struct
{
    T_Mts_10GSelfTest tMts10GSelfTest[2];
    WORD32    dwTimeoutMax;
} _PACKED_1_ T_Cmt_10GSelfTest;

typedef struct
{
    WORD32 dw10GNum;                          /* 出参，支持 10G能力的10G口数目 */
    WORD32 dwTestResult[TCS_10G_PORT_NUM];    /* 出参，自测试结果 */
    WORD32 dwCheckResult;                     /* 出参: 判断值  */
    WORD32 dwTimeoutMax;                      /* 入参，超时最大值 */
    CHAR   ucMacAddr[TCS_10G_PORT_NUM][6];    /* 出参，MAC地址 */
} _PACKED_1_ T_Mts_MacAddr;

typedef struct
{
    T_Mts_MacAddr tMtsMacAddr[2];
    WORD32    dwTimeoutMax;
} _PACKED_1_ T_Cmt_MacAddr;

/************************************单板特定项测试************************************/
/* Cache同步信号测试 */
typedef struct
{
    WORD32     dwPciePexId;          /* PEX8624厂家ID */
    BYTE       cCheckResult;         /* PEX8624自检结果 */
    WORD32     dwPcieLinkSpeed;      /* PCIE 连接速率 G1/G2*/
    WORD32     dwPcieLinkWidth;      /* PCIE 连接带宽x1~x4 x0表示无link */
    WORD32     dwPcieBadTlpCount;    /* TLP层坏包个数 */
    WORD32     dwPcieBadDllpCount;   /* DLLP层坏包个数 */
    WORD32     dwPcieEepromStatus;   /* PCIE 设备E2prom在位与否、有效与否 */
    WORD32     dwPcieDllpStatus;     /* DLLP 状态 */
    BYTE       cPcieDeviceStatus;    /* PCIE设备状态 */
    WORD32     dwTimeoutMax;         /* 超时最大值 */
} _PACKED_1_  T_Mts_Check_Pcie_Info;

/* PHY芯片自检 */
typedef struct
{
    WORD16  wPhyDevId;          /*  入参：宏定义MTS_PHY_88E1111和MTS_PHY_88E1119 */
    WORD32  dwPhyId;            /* 出参：厂家ID */
    BYTE    cCheckResult;       /* 出参：测试结果:MTS_PHYSELF_GOOD 测试通过; MTS_PHYSELF_NOTGOOD 测试不通过 */
    WORD32  dwTimeoutMax;       /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Phyself;

/* PCIE芯片桥自检 */
//说明:同cache同步信号测试

/* SAS控制器PM8001自检 */
typedef struct
{
    WORD32  dwPmId;         /* 出参: PM8001厂家ID */
    BYTE    cCheckResult;   /* 出参: 检测结果 */
    WORD32  dwTimeoutMax;   /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Pm;

/************************************IO信号类************************************/
/* 硬盘指示灯测试 */
//暂无数据结构

/* 输入IO信号指示灯测试 */
typedef struct
{
    WORD32  dwInputIoSigType;   /* 输入IO信号类型测试  */
    BYTE    cCheckResult;       /* 状态返回值      */
    WORD32  dwResult;        /* bsp提供的result[0] */
    WORD32  dwTimeoutMax;       /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_InputIo;

/* 输出IO信号指示灯测试 */
typedef struct
{
    WORD32  dwOutputIoSigType;  /* 输出IO信号类型测试  */
    BYTE    cInputValue;        /* 期望输出的信号0或1,入参 */
    BYTE    cCheckResult;       /* 状态返回值       */
    WORD32  dwResult;            /* bsp提供的result[0] */
    WORD32  dwTimeoutMax;       /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_OutputIo;

/* SSD容量读取测试 by liutt 2014/12/15*/
typedef struct
{
    WORD32  dwTimeoutMax;       /* 超时最大值 */
    WORD32  dwSsdSize;         /* ssd容量 */
} _PACKED_1_ T_Mts_Ssd_SizeTest;

/* SSD子卡读写测试 */
typedef struct
{
    BYTE    cCheckResult;       /* 状态返回值 */
    WORD32  dwTimeoutMax;       /* 超时最大值 */
} _PACKED_1_ T_Mts_Ssd_WDTest;
/* 电源信号指示灯测试 */
typedef struct
{
    BYTE    cCheckResult;       /* 状态返回值 */
    WORD32  dwTimeoutMax;       /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Power_Light;

/* BBU信息读取 */
typedef struct
{
    WORD32  dwBbuId;        /* BBU电池序列号     */
    WORD16  wBbuMv;         /* BBU当前电压       */
    WORD16  wBbuCapacity;   /* BBU剩余电量百分比 */
    BYTE    ucPresent;      /* BBU在位信息  MTS_BBU_PRESENT;  在位          MTS_BBU_NOTPRESENT:  不在位 */
    BYTE    ucWorkFlag;     /* 是否正常工作 MTS_BBU_CHARGING: BBU正在充放电 MTS_BBU_NOT_CHARGING:BBU此时没有充放电 */
    BYTE    cCheckResult;   /* BBU状态 MTS_BBU_GOOD 正常 MTS_BBU_GOOD不正常 */
    WORD32  dwTimeoutMax;   /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Bbu;

/* 8005看门狗复位测试 */
typedef struct
{
    BYTE    cCheckResult;       /* 测试返回值 */
    BYTE    cEncDevId;            /* 扩展柜号 */
    WORD32  dwTimeoutMax;       /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Ezzf_Reset;

/* minisas接口自环测试 */
typedef struct
{
    BYTE    cCheckResult[4];    /* 测试速率返回值 */
    BYTE    cEncDevId;            /* 扩展柜号 */
    WORD32  dwTimeoutMax;       /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Ezzf_GetSpeed;

/* 背板SAS接口自环测试 */
typedef struct
{
    BYTE    cCheckResult[12];   /* 测试速率返回值 */
    BYTE    cEncDevId;            /* 扩展柜号 */
    WORD32  dwTimeoutMax;       /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Ezzf_BdGetSpeed;

/* TW0\TW1\TW2信号测试 */
typedef struct
{
    BYTE    cTwSigValue[6];
    BYTE    cEncDevId;            /* 扩展柜号 */
    WORD32  dwTimeoutMax;       /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Ezzf_Ttsig;

/* SAS扩展芯片PM8005自检 */
typedef struct
{
    BYTE    cSasAddr[8];        /* SAS地址 */
    BYTE    cEncDevId;            /* 扩展柜号 */
    WORD32  dwTimeoutMax;       /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Ezzf_Self;

/* 硬盘指示灯测试 */
typedef struct
{
    BYTE    cMtsType;           /* 点灯or灭灯 */
    WORD32  dwHddLightType;     /* 点灯类型 */
    WORD32  dwHddIndexId;       /* 索引号 1~12*/
    WORD32  dwTimeoutMax;       /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Hdd_Light;

/* 内存大小测试 */
typedef struct
{
    WORD32  dwDdrSize;          /* 内存大小,单位:M */
    BYTE    cCoherenceResult;   /* 数据一致性测试 */
    BYTE    cCorrectResult;     /* 数据正确性测试 */
    WORD32  dwTimeoutMax;       /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_Ddr_Size;

/* 版本查询 */
typedef  struct
{
    BYTE    cEncDevId;
    SWORD32 sdwVerType;
    WORD32  dwWorkEpldVer;
    WORD32  dwBootEpldVer;
    CHAR    dwZbootVer[128];
    CHAR    dwUspVer[128];
    CHAR    dwExpVer[128];
    WORD32  dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_Ver;

/* MAC地址 */
typedef  struct
{
    BYTE    cMacAddr[128];
    WORD32  dwTimeoutMax;
} _PACKED_1_ T_Mts_Check_MacAddr;
/************************************测试仪End******************************************/

/***********************************整机测试Begin***************************************/
/* 工作EPLD自检 */
typedef  struct
{
    BYTE    ucChassisId;                    /*箱体ID*/
    WORD32  dwStandardValue;                /* Output parameter: standard value */
    WORD32  dwReadValue;                    /* Output parameter: Read-Out value */
    WORD32  dwCheckResult;                  /* Output parameter: CheckReust */
} _PACKED_1_ T_Cmt_Check_WorkEpldSelf;

typedef  struct
{
    //BYTE  ucSlotId;               /*槽位ID*/
    //BYTE  ucPeerStatus;           /*对版在位标志*/
    T_Cmt_Check_WorkEpldSelf    tCmtCheckWorkEpldSelf[2];
} _PACKED_1_ T_CmtWorkEpldSelf;

typedef  struct
{
    WORD32  dwTimeoutMax;       /* Input  parameter: Max-Timeout value */
    WORD32  dwEncNum;           /* 级联层次,最小为1,最大为5 */
    T_CmtWorkEpldSelf       tCheckWorkEpldSelf[CMT_CLASS_LEVEL];
} _PACKED_1_ T_WorkEpldSelfList;

/* 工作EPLD信息读取 */
typedef  struct
{
    BYTE   ucChassisId;       /* 箱体ID */
    WORD32 dwBoardId;         /* 单板ID        */
    WORD32 dwPcbVer;          /* 单板pcb版本号 */
    WORD32 dwBomVer;          /* 单板bom料单   */
} _PACKED_1_ T_Cmt_Check_WorkEpldInfo;

typedef  struct
{
    //BYTE  ucSlotId;           /*槽位ID*/
    //BYTE  ucPeerStatus;       /*对版在位标志*/
    T_Cmt_Check_WorkEpldInfo    tCmtCheckWorkEpldInfo[2];
} _PACKED_1_ T_CmtWorkEpldInfo;

typedef  struct
{
    WORD32  dwTimeoutMax;      /* Input  parameter: Max-Timeout value */
    WORD32  dwEncNum;          /* 级联层次,最小为1,最大为5 */
    T_CmtWorkEpldInfo          tCheckWorkEpldInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_WorkEpldInfoList;

/* 工作EPLD信息读取 */
typedef  struct
{
    BYTE   ucChassisId;       /* 箱体ID */
    WORD32  dwStandardValue;                /* Output parameter: standard value */
    WORD32  dwReadValue;                    /* Output parameter: Read-Out value */
    WORD32  dwCheckResult;                  /* Output parameter: CheckReust */
    BYTE p33M;
    BYTE p75M;
    WORD32 dwBoardId;         /* 单板ID        */
    WORD32 dwPcbVer;          /* 单板pcb版本号 */
    WORD32 dwBomVer;          /* 单板bom料单   */
    WORD32   dwBackBoardId;    /* 6位测试背板ID */

} _PACKED_1_ T_SPR11_Cmt_Check_WorkEpldInfo;

typedef  struct
{
    T_SPR11_Cmt_Check_WorkEpldInfo    tCmtCheckWorkEpldInfo[2];
} _PACKED_1_ T_SPR11CmtWorkEpldInfo;

typedef  struct
{
    WORD32  dwTimeoutMax;      /* Input  parameter: Max-Timeout value */
    WORD32  dwEncNum;          /* 级联层次,最小为1,最大为5 */
    T_SPR11CmtWorkEpldInfo          tCheckWorkEpldInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_SPR11WorkEpldInfoList;
/* 启动EPLD信息读取 */
typedef  struct
{
    BYTE   ucChassisId;       /* 箱体ID */
    WORD32 dwBoardId;         /* 单板ID        */
    WORD32 dwPcbVer;          /* 单板pcb版本号 */
    WORD32 dwBomVer;          /* 单板bom料单   */
} _PACKED_1_ T_Cmt_Check_BootEpldInfo;

typedef  struct
{
    //BYTE  ucSlotId;           /*槽位ID*/
    //BYTE  ucPeerStatus;       /*对版在位标志*/
    T_Cmt_Check_BootEpldInfo    tCmtCheckBootEpldInfo[2];
} _PACKED_1_ T_CmtBootEpldInfo;

typedef  struct
{
    WORD32  dwTimeoutMax;       /* Input  parameter: Max-Timeout value */
    WORD32  dwEncNum;           /* 级联层次,最小为1,最大为5，扩展柜中没有启动EPLD，该字段保留 */
    T_CmtBootEpldInfo     tCheckBootEpldInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_BootEpldInfoList;

/* 电子标签信息 */
typedef  struct
{
    BYTE   ucChassisId;                       /* 箱体号 */
    BYTE   cLableInfo[MAX_INFO_LABLE_LENGTH]; /* 条形码 */
} _PACKED_1_ T_Cmt_Check_Lable_Info;

typedef struct
{
    T_Cmt_Check_Lable_Info      tCmtCheckLableInfo[2];
} _PACKED_1_ T_CmtLableInfo;

typedef  struct
{
    WORD32  dwTimeoutMax;       /* Input  parameter: Max-Timeout value */
    WORD32  dwEncNum;           /* 级联层次,最小为1,最大为5，扩展柜中没有启动EPLD，该字段保留 */
    T_CmtLableInfo      tCheckLableInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_LableInfoList;

/* 单板硬件地址读取  */
typedef  struct
{
    BYTE     ucChassisId;          /* 箱体号 */
    WORD32   dwBackBoardId;        /* 6位测试背板ID */
    BYTE     cSlotId;              /* 槽位号 */
} _PACKED_1_ T_Cmt_Check_PhyAddr_Info;

typedef struct
{
    T_Cmt_Check_PhyAddr_Info        tCmtCheckPhyAddrInfo[2];
} _PACKED_1_ T_CmtPhyAddrInfo;

typedef  struct
{
    WORD32  dwTimeoutMax;       /* Input  parameter: Max-Timeout value */
    WORD32  dwEncNum;           /* 级联层次,最小为1,最大为5，扩展柜中没有启动EPLD，该字段保留 */
    T_CmtPhyAddrInfo     tCheckPhyAddrInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_PhyAddrInfoList;

/* 在位信号测试 */
typedef  struct
{
    BYTE     ucChassisId;       /* 箱体号 */
    BYTE     cOnlieFlag;        /* 在位标志 */
} _PACKED_1_ T_Cmt_Check_OnlineFlag_Info;

typedef struct
{
    T_Cmt_Check_OnlineFlag_Info     tCmtCheckOnlieFlagInfo[2];
} _PACKED_1_ T_CmtOnlineFlagInfo;

typedef  struct
{
    WORD32  dwTimeoutMax;       /* Input  parameter: Max-Timeout value */
    WORD32  dwEncNum;           /* 级联层次,最小为1,最大为5，扩展柜中没有启动EPLD，该字段保留 */
    T_CmtOnlineFlagInfo    tCheckOnlieFlagInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_OnlineFlagInfoList;

/* 读取SSD型号、容量 */
typedef  struct
{
    BYTE   acDeviceName[20];                 /* 表示C2F分区名。如:sda2 */
    WORD32 dwStartSector;                    /* 表示C2F分区开始扇区  */
    WORD32 dwSectorsCount;                   /* 表示C2F分区的扇区数  */
    WORD32 dwResult;                         /* 检测结果  */
} _PACKED_1_ T_Cmt_C2f_Ssd;

typedef struct
{
    WORD32 dwTimeoutMax;      /* 超时最大值 */
    T_Cmt_C2f_Ssd tC2fSsd[2];
} _PACKED_1_ T_CmtC2fSsdList;

/* 板内时钟电路测试 */
typedef  struct
{
    BYTE    ucChassisId;    /* 箱体号 */
    WORD16  wMtsClockType;  /* 入参：MTS_25M_CLOCK, MTS_33_CLOCK...*/
    BYTE    cCheckResult[5];    /* 出参：MTS_CLOCK_GOOD      测试通过
                                     MTS_CLOCK_NOT_GOOD  测试不通过*/
} _PACKED_1_ T_Cmt_Check_Clock_Info;

typedef struct
{
    T_Cmt_Check_Clock_Info      tCmtCheckClockInfo[2];
} _PACKED_1_ T_CmtClockInfo;

typedef  struct
{
    WORD32          dwTimeoutMax;       /* Input  parameter: Max-Timeout value */
    WORD32          dwEncNum;           /* 级联层次,最小为1,最大为5，扩展柜中没有启动EPLD，该字段保留 */
    T_CmtClockInfo  tCheckClockInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_ClockInfoList;

/* 温度传感器测试 */
typedef  struct
{
    BYTE    ucChassisId;            /* 箱体号 */
    /* 数组下标0代表LM_93  1代表75_1, 2代表75_2, 3代表75_2 4代表75_3 */
    BYTE    cSenorStatus[5];  /* 出参; MTS_SENOR_GOOD正常  MTS_SENOR_NOT_GOOD 不正常 */

} _PACKED_1_ T_Cmt_Check_Senor_Info;

typedef struct
{
    T_Cmt_Check_Senor_Info      tCmtCheckSenorInfo[2];
} _PACKED_1_ T_CmtSenorInfo;

typedef  struct
{
    WORD32          dwTimeoutMax;       /* Input  parameter: Max-Timeout value */
    WORD32          dwEncNum;           /* 级联层次,最小为1,最大为5，扩展柜中没有启动EPLD，该字段保留 */
    T_CmtSenorInfo  tCheckSenorInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_SenorInfoList;
/*箱体设备信息*/
typedef struct
{
    BYTE ucChassisId;  /*箱体ID*/
    BYTE ucSlotId;  /*槽位ID*/
    BYTE ucFanNum;  /*风扇个数*/
    BYTE ucPsNum;  /*电源个数*/
    BYTE ucTemperatureNum;  /*温度传感器个数*/
    BYTE ucVoltNum;  /*电压传感器个数*/
    BYTE ucDiskNum;  /*硬盘个数*/
    WORD64   uqwSasAddr;  /*EXPsaS地址*/
    T_EncFanInfo tFaninfo[MAX_FAN_NUM];  /*风扇信息*/
    T_EncPsInfo tPsinfo[MAX_PS_NUM];  /*电源信息*/
    T_EncVoltInfo tVoltinfo[MAX_VOLT_NUM];  /*电压信息*/
    T_EncTempratureInfo tTempratureinfo[MAX_TEMP_NUM];  /*温度信息*/

} _PACKED_1_ T_MtsEncDeviceInfo;
/*箱体设备信息列表*/
typedef struct
{
    WORD32    dwTimeoutMax;     /* Input  parameter: Max-Timeout value */
    BYTE            ucExpcount;                   /*箱体个数*/
    T_MtsEncDeviceInfo tExpanders[CMT_CLASS_LEVEL];  /*箱体链表头*/
} _PACKED_1_  T_MtsEncDeviceInfoList;

typedef struct
{
    BYTE id;     /* 属性id */
    WORD16 flags;  /* 属性标识，可分析得到pre-fail和update方式 */
    BYTE currentvalue; /* 属性当前值 */
    BYTE worst;   /* 属性曾经出现的最坏值 */
    WORD64 raw;  /* 属性真实值 */
    BYTE thres;  /* 属性门限值 */
} _PACKED_1_ T_MtsDmPdSmartDetailInfo;

/*磁盘检测信息*/
typedef struct
{
    WORD32    dwTimeoutMax;     /* Input  parameter: Max-Timeout value */
    WORD64   uqwSasAddr;
    WORD32 type;
    /*硬盘条码, 磁盘序列号*/
    CHAR cSerialNum[MAX_PD_SNO_LEN];

    /*RAID盘一致性检查*/

    /*硬盘SMART信息*/

    BYTE ucIsSupportSmart;  /* 磁盘是否支持SMART */
    BYTE ucIsSmartEnable;   /* 磁盘SMART功能是否开启 */
    BYTE ucSmartStatus;     /* 磁盘的SMART状态是否OK */
    WORD32 PdSmartAttrNum;  /* 磁盘SMART属性个数 */
    T_MtsDmPdSmartDetailInfo tSmartDetailInfo[30];
    /*硬盘读速率*/
    WORD32 fReadSpeed;

    /*硬盘写速率*/
    WORD32 fWriteSpeed;

    /*硬盘固件版本*/
    CHAR cFwVer[MAX_PD_FW_VER_LEN];

    /*硬盘标准版本*/

    /*硬盘Model版本*/
    CHAR cModel[MAX_PD_MODEL_NAME_LEN];

    /*硬盘厂家信息*/
    CHAR cManufacture[64];
    CHAR  ucStdVerNum[MAX_PD_STD_VER_LEN];
    /*硬盘型号*/
    BYTE     ucPhyType[MAX_PD_TYPE_LEN];

    /*硬盘容量, 单位：块(512字节)*/
    WORD64 uCapacity;

    /*硬盘坏道数目*/
    SWORD32 sBadBlocks;
    SWORD32 scanPercentage;

    /*逻辑坏道修复测试*/
    BYTE ucBadBlockflag;
    /*硬盘在位信息, HDD_PRESENT表示在位, HDD_ABSENT表示不在位*/
    WORD32 wPresentFlag;
    WORD16 wGlist;   /* grown defect list */
    WORD16 wPlist;   /* primary defect list */
    WORD32 dwManufactureYear;    /* manufacture year 0-is unknown */
    WORD16 wManufactureWeek;     /* manufacture weed 0-is unknown */
    WORD32 dwStartStopCnt;       /* ACCUMULATED START-STOP CYCLES 0-is unknown */
    WORD32 dwMaxStartStop;       /* Specified cycle count over device lifetime  0-is unknown */
} _PACKED_1_  T_MtsDiskInfo;

/* RTC实时时钟电路测试 */
typedef  struct
{
    BYTE    ucChassisId;            /* 箱体号 */
    BYTE    cCheckResult;           /* 出参：MTS_RTC_GOOD        测试通过
                                     MTS_RTC_NOT_GOOD    测试不通过 */
} _PACKED_1_ T_Cmt_Check_Rtc_Info;

typedef struct
{
    WORD32                      dwTimeoutMax;
    T_Cmt_Check_Rtc_Info        tCmtCheckRtcInfo[2];
} _PACKED_1_ T_CmtRtcInfo;

typedef  struct
{
    WORD32          dwTimeoutMax;       /* Input  parameter: Max-Timeout value */
    WORD32          dwEncNum;           /* 级联层次,最小为1,最大为5，扩展柜中没有启动EPLD，该字段保留 */
    T_CmtRtcInfo    tCheckRtcInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_RtcInfoList;

/* GE口链路速率，是否双控测试 */
typedef  struct
{
    BYTE    ucChassisId;            /* 箱体号 */
    BYTE    cCheckResult[4];        /* 出参：测试结果:MTS_GE_GOOD 测试通过; MTS_GE_NOT_GOOD 测试不通过 */
} _PACKED_1_ T_Cmt_Check_Ge_Info;

typedef struct
{
    T_Cmt_Check_Ge_Info     tCmtCheckGeInfo[2];
} _PACKED_1_ T_CmtGeInfo;

typedef  struct
{
    WORD32          dwTimeoutMax;       /* Input  parameter: Max-Timeout value */
    WORD32          dwEncNum;           /* 级联层次,最小为1,最大为5，扩展柜中没有启动EPLD，该字段保留 */
    T_CmtGeInfo     tCheckGeInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_GeInfoList;

/* PCIE测试 */
typedef  struct
{
    BYTE    ucChassisId;        /* 箱体号 */
    WORD32  dwPciePexId;        /* PEX8624厂家ID */
    BYTE    cCheckResult;       /* PEX8624自检结果 */
    WORD32  dwPcieLinkSpeed;    /* PCIE 连接速率 G1/G2*/
    WORD32  dwPcieLinkWidth;    /* PCIE 连接带宽x1~x4 x0表示无link */
    WORD32  dwPcieBadTlpCount;  /* TLP层坏包个数 */
    WORD32  dwPcieBadDllpCount; /* DLLP层坏包个数 */
    WORD32  dwPcieEepromStatus; /* PCIE 设备E2prom在位与否、有效与否 */
    WORD32  dwPcieDllpStatus;   /* DLLP 状态 */
    BYTE    cPcieDeviceStatus;  /* PCIE设备状态 */
} _PACKED_1_ T_Cmt_Check_Pcie_Info;

typedef struct
{
    T_Cmt_Check_Pcie_Info       tCmtCheckPcieInfo[2];
} _PACKED_1_ T_CmtPcieInfo;

typedef  struct
{
    WORD32          dwTimeoutMax;       /* Input  parameter: Max-Timeout value */
    WORD32          dwEncNum;           /* 级联层次,最小为1,最大为5，扩展柜中没有启动EPLD，该字段保留 */
    T_CmtPcieInfo   tCheckPcieInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_PcieInfoList;

/* PHY自检 */
typedef  struct
{
    BYTE    ucChassisId;        /* 箱体号 */
    //WORD16    wPhyDevId;      /*  入参：宏定义 MTS_PHY_88E1111 和 MTS_PHY_88E1119 */
    WORD32  dwPhyId;            /* 出参：厂家ID */
    BYTE    cCheckResult[2];    /* 出参：测试结果:MTS_PHYSELF_GOOD 测试通过; MTS_PHYSELF_NOTGOOD 测试不通过 */
} _PACKED_1_ T_Cmt_Check_Phy_Info;

typedef struct
{
    T_Cmt_Check_Phy_Info        tCmtCheckPhyInfo[2];
} _PACKED_1_ T_CmtPhyInfo;

typedef  struct
{
    WORD32          dwTimeoutMax;       /* Input  parameter: Max-Timeout value */
    WORD32          dwEncNum;           /* 级联层次,最小为1,最大为5，扩展柜中没有启动EPLD，该字段保留 */
    T_CmtPhyInfo    tCheckPhyInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_PhyInfoList;

/* SAS控制器PM8001自检 */
typedef  struct
{
    BYTE    ucChassisId;    /* 箱体号 */
    WORD32  dwPmId;         /* 出参: PM8001厂家ID */
    BYTE    cCheckResult;   /* 出参: 检测结果 */
} _PACKED_1_ T_Cmt_Check_Pm_Info;

typedef struct
{
    T_Cmt_Check_Pm_Info     tCmtCheckPmInfo[2];
} _PACKED_1_ T_CmtPmInfo;

typedef  struct
{
    WORD32          dwTimeoutMax;       /* Input  parameter: Max-Timeout value */
    WORD32          dwEncNum;           /* 级联层次,最小为1,最大为5，扩展柜中没有启动EPLD，该字段保留 */
    T_CmtPmInfo     tCheckPmInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_PmInfoList;

/* BBU检测 */
typedef  struct
{
    BYTE    ucChassisId;            /* 箱体号 */
    WORD32  dwBbuId;                /* BBU电池序列号     */
    WORD16  wBbuMv;                 /* BBU当前电压       */
    WORD16  wBbuCapacity;           /* BBU剩余电量百分比 */
    BYTE    ucPresent;              /* BBU在位信息  MTS_BBU_PRESENT;  在位          MTS_BBU_NOTPRESENT:  不在位 */
    BYTE    ucWorkFlag;             /* 是否正常工作 MTS_BBU_CHARGING: BBU正在充放电 MTS_BBU_NOT_CHARGING:BBU此时没有充放电 */
    BYTE    cCheckResult;           /* BBU状态 MTS_BBU_GOOD 正常 MTS_BBU_GOOD不正常 */
} _PACKED_1_ T_Cmt_Check_Bbu_Info;

typedef struct
{
    T_Cmt_Check_Bbu_Info        tCmtCheckBbuInfo[2];
} _PACKED_1_ T_CmtBbuInfo;

typedef  struct
{
    WORD32          dwTimeoutMax;       /* Input  parameter: Max-Timeout value */
    WORD32          dwEncNum;           /* 级联层次,最小为1,最大为5，扩展柜中没有启动EPLD，该字段保留 */
    T_CmtBbuInfo    tCheckBbuInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_BbuInfoList;

/* MINISAS和背部SAS接口测试0~3代表MINIsas速率,11~19代表背板SAS速率 */
typedef  struct
{
    BYTE    ucChassisId;            /* 箱体号 */
    CHAR    ucDiskType[12][MAX_PD_TYPE_LEN];
    BYTE    cCheckResult[36];       /* 硬盘SAS链路速度 */
} _PACKED_1_ T_Cmt_Check_Sas_Info;

typedef struct
{
    T_Cmt_Check_Sas_Info        tCmtCheckSasInfo[2];
} _PACKED_1_ T_CmtSasInfo;

typedef  struct
{
    WORD32          dwTimeoutMax;       /* Input  parameter: Max-Timeout value */
    WORD32          dwEncNum;           /* 级联层次,最小为1,最大为5，扩展柜中没有启动EPLD，该字段保留 */
    T_CmtSasInfo    tCheckSasInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_SasInfoList;

typedef  struct
{
    BYTE    ucChassisId;         /* 箱体号 */
    BYTE    ucPhyRate[36];       /* 硬盘SAS链路速度 */
    BYTE    ucCheckResult;       /* 测试结果 */
    WORD32  dwTimeoutMax;        /* Input  parameter: Max-Timeout value */
} _PACKED_1_ T_MtsTestSas;

/* HardDisk 自检 */
typedef  struct
{
    BYTE     ucChassisId;                               /* 箱体号       */
    SWORD32  sdwHddSoltId;                              /* 硬盘槽位号   */
    CHAR     ucSerialNo[MAX_PD_SNO_LEN];                /* 硬盘序列号   */
    SWORD64  sdwHddCapcity;                             /* 硬盘容量     */
    CHAR     ucStdVerNum[MAX_PD_STD_VER_LEN];           /* 标准版本号   */
    CHAR     ucFwVer[MAX_PD_FW_VER_LEN];                /* FirmWare版本 */
    CHAR     ucModelName[MAX_PD_MODEL_NAME_LEN];        /* Model名称    */
    SWORD32  sdwHealthState;                            /* 磁盘的健康状态，包含可访问性和SMART 状态，取值为PD_GOOD(1)、PD_BROKEN(0)     */
} _PACKED_1_ T_Cmt_Check_Hdd_Info;

typedef struct
{
    T_Cmt_Check_Hdd_Info        tCmtCheckHddInfo[16];
} _PACKED_1_ T_CmtHddInfo;

typedef  struct
{
    WORD32          dwTimeoutMax;       /* Input  parameter: Max-Timeout value */
    WORD32          dwEncNum;           /* 级联层次,最小为1,最大为5，扩展柜中没有启动EPLD，该字段保留 */
    T_CmtHddInfo    tCheckHddInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_HddInfoList;

/* 版本检测 */
typedef  struct
{
    BYTE    ucChassisId;        /*  箱体号             */
    SWORD32 sdwVerType;         /*  version   type     */
    WORD32  dwWorkEpldVer;      /*  work epld version  */
    WORD32  dwBootEpldVer;      /*  boot epld version  */
    WORD32  dwBootVer;
    CHAR    dwZbootVer[128];    /*  Zboot     version  */
    CHAR    dwUspVer[128];      /*  USP       version  */
    CHAR    dwExpVer[128];      /*  8005      version  */
} _PACKED_1_ T_Cmt_Check_Ver_Info;

typedef struct
{
    T_Cmt_Check_Ver_Info        tCmtCheckVerInfo[2];
} _PACKED_1_ T_CmtVerInfo;

typedef  struct
{
    WORD32          dwTimeoutMax;       /* Input  parameter: Max-Timeout value */
    WORD32          dwEncNum;           /* 级联层次,最小为1,最大为5，扩展柜中没有启动EPLD，该字段保留 */
    T_CmtVerInfo    tCheckVerInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_VerInfoList;

/* 内存检测 */
typedef  struct
{
    BYTE    ucChassisId;        /*  箱体号         */
    WORD32  dwDdrSize;          /* 内存大小,单位:M */
    BYTE    cCoherenceResult;   /* 数据一致性测试  */
    BYTE    cCorrectResult;     /* 数据正确性测试  */
} _PACKED_1_ T_Cmt_Check_Ddr_Info;

typedef struct
{
    T_Cmt_Check_Ddr_Info        tCmtCheckDdrInfo[2];
} _PACKED_1_ T_CmtDdrInfo;

typedef  struct
{
    WORD32          dwTimeoutMax;       /* Input  parameter: Max-Timeout value */
    WORD32          dwEncNum;           /* 级联层次,最小为1,最大为5，扩展柜中没有启动EPLD，该字段保留 */
    T_CmtDdrInfo    tCheckDdrInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_DdrInfoList;

/* MAC地址 */
typedef  struct
{
    BYTE    ucChassisId;    /*  箱体号  */
    BYTE    cMacAddr[128];
} _PACKED_1_ T_Cmt_Check_MacAddr_Info;

typedef struct
{
    T_Cmt_Check_MacAddr_Info        tCmtCheckMacAddrInfo[2];
} _PACKED_1_ T_CmtMacAddrInfo;

typedef  struct
{
    WORD32          dwTimeoutMax;       /* Input  parameter: Max-Timeout value */
    WORD32          dwEncNum;           /* 级联层次,最小为1,最大为5，扩展柜中没有启动EPLD，该字段保留 */
    T_CmtMacAddrInfo   tCheckMacAddrInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_MacAddrInfoList;

/* 测试环境检测 */
typedef  struct
{
    BYTE    ucChassisId;    /*  箱体号  */
    SWORD32 sdwPeerState;   /*  对端单板的状态 */
} _PACKED_1_ T_Cmt_Check_PeerState_Info;

typedef struct
{
    T_Cmt_Check_PeerState_Info      tCmtCheckPeerStateInfo[2];
} _PACKED_1_ T_CmtPeerStateInfo;

typedef  struct
{
    WORD32            dwTimeoutMax;      /* Input  parameter: Max-Timeout value */
    WORD32            dwEncNum;          /* 级联层次,最小为1,最大为5，扩展柜中没有启动EPLD，该字段保留 */
    T_CmtPeerStateInfo   tCheckPeerStateInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_PeerStateInfoList;

/* SAS地址测试, 8005自检 */
typedef  struct
{
    BYTE    ucChassisId;    /*  箱体号  */
    BYTE    ucSasAddr[8];   /*  SAS地址 */
} _PACKED_1_ T_Cmt_Check_SasAddr_Info;

typedef struct
{
    T_Cmt_Check_SasAddr_Info        tCmtCheckSasAddrInfo[2];
} _PACKED_1_ T_CmtSasAddrInfo;

typedef  struct
{
    WORD32            dwTimeoutMax;      /* Input  parameter: Max-Timeout value */
    WORD32            dwEncNum;          /* 级联层次,最小为1,最大为5，扩展柜中没有启动EPLD，该字段保留 */
    T_CmtSasAddrInfo   tCheckSasAddrInfo[CMT_CLASS_LEVEL];
} _PACKED_1_ T_SasAddrInfoList;

/* added by huangan 20131227 */
typedef  struct
{
    WORD32            dwTimeoutMax;      /* Input  parameter: Max-Timeout value */
    WORD32            dwSpr10WorkMode;   /* output parameter: spr10 work mode */
} _PACKED_1_ T_Spr10WorkMode;
/***********************************整机测试End****************************************/
/***********************************spr11 测试仪****************************************/
/* CPU外挂DDR3测试 */
typedef struct
{
    WORD16  wMtsType;      /* 入参，测试类型:MTS_FT,  功能测试:  MTS_HT,       高温       */
    WORD32     CheckResult;  /* 出参，测试结果:MTS_DDR_GOOD 测试通过;  MTS_DDR_NOT_GOOD  测试不通过 */

    WORD32  dwTimeoutMax;  /* 超时最大值 */
} _PACKED_1_ T_Mts_SPR11_Check_Ddr;
/* 内存大小测试 */
typedef struct
{
    WORD32  dwDdrSize;          /* 内存大小,单位:M */
    BYTE    cCoherenceResult;   /* 数据一致性测试 */
    BYTE    cCorrectResult;     /* 数据正确性测试 */
    WORD32     cMemResult;     /* 内存容量校验*/
    WORD32     cCpuResult;     /* CPU多核功能检测*/
    WORD32  dwTimeoutMax;       /* 超时最大值 */
} _PACKED_1_ T_Mts_SPR11_Check_Ddr_Size;

typedef struct
{
    WORD32  dwDdrSize[2];          /* 内存大小,单位:M */
    WORD32  dwTimeoutMax;       /* 超时最大值 */
} _PACKED_1_ T_Cmt_SPR11_Check_Ddr_Size;

typedef struct
{
    WORD32  dwTimeoutMax;       /* 超时最大值 */
    WORD32     CheckResult;
} _PACKED_1_ T_Cmt_SPR11_Check_Hb;

/* 工作EPLD自检 */
typedef struct
{
    WORD32 dwStandardValue;   /* 标准值  */
    WORD32 dwReadValue;       /* 读出值  */
    WORD32 dwCheckResult;     /* 判断值  */
    WORD32 dwTimeoutMax;      /* 超时最大值 */
} _PACKED_1_ T_Mts_SPR11_Check_Work_Epld_Self;

/* MAC地址 */
typedef  struct
{
    BYTE    cMacAddr[6];
} _PACKED_1_ T_Mts_SPR11_MacAddr;

/* MAC地址 */
typedef  struct
{
    BYTE ucPortNum;
    BYTE ucPortType;
    T_Mts_SPR11_MacAddr    MacAddr[8];
    WORD32  dwTimeoutMax;
} _PACKED_1_ T_Mts_SPR11_Check_MacAddr;

typedef  struct
{
    WORD32  dwTimeoutMax;
    T_Mts_SPR11_Check_MacAddr    MacAddrs[2];

} _PACKED_1_ T_Cmt_SPR11_Check_MacAddr;
/* MAC地址 */
typedef  struct
{
    WORD32     type;
    WORD32     dwipaddr;
    WORD32     dwResult;
    WORD32  dwTimeoutMax;
} _PACKED_1_ T_Mts_SPR11_Check_Macband;

/* 温度传感器测试 */
typedef struct
{
    /* 数组下标0代表LM_93  1代表75_1, 2代表75_2, 3代表75_2 4代表75_3 */
    BYTE    cSenorStatus[4];  /* 出参; MTS_SENOR_GOOD正常  MTS_SENOR_NOT_GOOD 不正常 */
    SWORD32 sdwSenorValue[4]; /* 出参; 传感器的实际温度 */
    BYTE    cEncDevId;          /* 扩展柜号 */
    WORD32  dwTimeoutMax;     /* 超时最大值 */
} _PACKED_1_ T_Mts_SPR11_Check_Senor;

/* BBU信息读取 */
typedef struct
{
    WORD32  dwBbuId;        /* BBU电池序列号     */
    WORD16  wBbuMv;         /* BBU当前电压       */
    WORD16  wBbuCapacity;   /* BBU剩余电量百分比 */
    BYTE    ucPresent;      /* BBU在位信息  MTS_BBU_PRESENT;  在位          MTS_BBU_NOTPRESENT:  不在位 */
    BYTE    ucWorkFlag;     /* 是否正常工作 MTS_BBU_CHARGING: BBU正在充放电 MTS_BBU_NOT_CHARGING:BBU此时没有充放电 */
    BYTE    cCheckResult;   /* BBU状态 MTS_BBU_GOOD 正常 MTS_BBU_GOOD不正常 */
    WORD32  dwTimeoutMax;   /* 超时最大值 */
} _PACKED_1_ T_Mt_SPR11_Check_Bbu;

/* 温度传感器测试 */
typedef struct
{
    BYTE    cType;
    BYTE    cSenorStatus[40];  /* 出参; PHY速率*/
    BYTE    cEncDevId;          /* 扩展柜号 */
    WORD32  dwTimeoutMax;     /* 超时最大值 */
} _PACKED_1_ T_Mts_SPR11_SASLINK;

/* RTC实时时钟电路测试 */
typedef struct
{
    BYTE    cCheckResult;   /* 出参：MTS_RTC_GOOD        测试通过
                                    MTS_RTC_NOT_GOOD    测试不通过 */
    WORD32  dwTimeoutMax;   /* 超时最大值 */
} _PACKED_1_ T_Mts_SPR11_Check_Rtc;

/* 板内时钟电路测试 */
typedef struct
{
    WORD16  wMtsClockType;  /* 入参：MTS_25M_CLOCK, MTS_33_CLOCK...*/
    BYTE    cCheckResult;   /* 出参：MTS_CLOCK_GOOD      测试通过
                                   MTS_CLOCK_NOT_GOOD   测试不通过*/
    WORD32  dwTimeoutMax;   /* 超时最大值 */
} _PACKED_1_ T_Mts_SPR11_Check_Clock;

/* 硬盘指示灯测试 */
typedef struct
{
    BYTE    cMtsType;           /* type */
    WORD32  dwLightMode;     /* 点灯模式电源OR DISK OR 面板*/
    WORD32  dwLightType;     /* color*/
    WORD32  dwIndexId;       /* 索引号 1~12*/
    WORD32  dwTimeoutMax;       /* 超时最大值 */
} _PACKED_1_ T_Mts_SPR11_Check_LED_Light;

/* 工作EPLD信息读取 */
typedef struct
{
    WORD32 dwBoardId;         /* 单板ID        */
    WORD32 dwPcbVer;          /* 单板pcb版本号 */
    WORD32 dwBomVer;          /* 单板bom料单   */
    BYTE    ucSlotId;               /*slotid*/
    WORD32  dwBackBoardTypeId;/*背板ID*/
    WORD32 dwTimeoutMax;      /* 超时最大值 */
} _PACKED_1_ T_Mts_SPR11_Check_Work_Epld_Info;

/* 工作EPLD信息读取 */
typedef struct
{

    WORD32 dwcpuid;         /* CPUid*/
    WORD32 dwsbrigeid;          /* 南桥芯片ID */
    WORD32 mac350id;          /* 350网口ID*/
    WORD32 mac82580id;          /* 82580网口ID*/
    BYTE    cCheckResult[4];   /* 出参：MTS_CLOCK_GOOD        测试通过
                                   MTS_CLOCK_NOT_GOOD   测试不通过*/
    WORD32 dwTimeoutMax;      /* 超时最大值 */
} _PACKED_1_ T_Mts_SPR11_Check_Chips;

/* 工作EPLD信息读取 */
typedef struct
{
    WORD32 dwTimeoutMax;      /* 超时最大值 */
    T_Mts_SPR11_Check_Chips chips[2];
} _PACKED_1_ T_Cmt_SPR11_Check_Chips;
/* 电子条形码扫描 */
typedef struct
{
    BYTE   cLableInfo[MAX_INFO_LABLE_LENGTH]; /* 条形码 */
    WORD32 dwTimeoutMax;                      /* 超时最大值 */
} _PACKED_1_ T_Mts_SPR11_Check_Lable_Info;

/* 版本查询 */
typedef  struct
{
    BYTE    cEncDevId;
    SWORD32 sdwVerType;
    WORD32  dwWorkEpldVer;
    WORD32  dwBootEpldVer;
    WORD32 dwBootVer;
    CHAR    dwZbootVer[128];
    CHAR    dwUspVer[128];
    CHAR    dwExpVer[128];
    WORD32  dwTimeoutMax;
} _PACKED_1_ T_Mts_SPR11_Check_Ver;

typedef struct
{
    BYTE  ifPortValid;                /* 标识该端口是否存在.    0 : 端口不存在; 1 : 端口存在.           */
    BYTE  PortID[FC_PORT_ID_LENGTH];  /* 端口ID,FC协议生成,显示方式为0x123456      */
    BYTE  PortNo;                     /* 端口编号,按FC接口面板顺序进行,从1开始编号 */

    BYTE  DataRate;                   /* 端口速率                                  */
    /* #define FC_SPEED_INVALID 255              */
    /* #define FC_SPEED_2G       2               */
    /* #define FC_SPEED_4G       4               */
    /* #define FC_SPEED_8G       8               */

    BYTE  LinkStatus;                 /* 链路状态                                  */
    /* 0 : UP; 1 : DOWN.                         */

    BYTE  Topology;                   /* 端口拓扑                                  */
    /* FC端口拓扑为私有环     0x01               */
    /* FC端口拓扑为公有环     0x02               */
    /* FC端口拓扑为点对点     0x04               */
    /* FC端口拓扑为Fabric     0x08               */
    BYTE   LinkLength;                /* 光模块连接链路长度 */
    BYTE   SpeedCapacity;             /* 光模块速率能力     */
    BYTE   TransType;                 /* 光模块传输类型     */
    BYTE   TxStatus;                  /* 光模块发送端状态   */
    BYTE   LOSStatus;                 /* 光模块LOS状态      */
    BYTE   FaultStatus;               /* 光模块FAULT状态    */
    BYTE   ifSFPONLine;               /* 判断光模块是否在线 */
    BYTE  WWPN[FC_WWN_LENGTH];        /* 端口WWPN                                  */
    WORD16 deviceid;                  /* 设备id */
} _PACKED_1_ T_Mts_SPR11_FCPortInfo;

/* SCS获取FC端口信息索引结构 */
typedef  struct
{
    WORD32 CtrlNo;
    BYTE      WWNN[FC_WWN_LENGTH];         /* 端口所在单板的WWNN               */
    T_Mts_SPR11_FCPortInfo FCPortInfo[FC_MAX_PORT_NUM]; /* FC接口信息结构                   */
    WORD32  dwTimeoutMax;
} _PACKED_1_ T_Mts_SPR11_FCinfo;

/* SCS获取FC端口信息索引结构 */
typedef  struct
{
    WORD32  dwTimeoutMax;
    T_Mts_SPR11_FCinfo fcinfo[2];
} _PACKED_1_ T_Cmt_SPR11_FCinfo;

typedef  struct
{
    WORD32  dwTimeoutMax;
    BYTE   encid;
    WORD16 voltinfo[32];
} _PACKED_1_ T_Cmt_SPR11_Voltinfo;

typedef struct
{
    WORD32  dwTimeoutMax;
    WORD32 CtrlNo;                                  /* 控制器号,值为0或1    */
    WORD32 PortNo;                                  /* 端口号，值为1-4      */

    BYTE   TxStatus;                                /* 设置的光模块发送状态 */
    BYTE   ifSFPONLine;
    BYTE   ReservedOne;                             /* 保留字段             */
    WORD16 ReservedTwo;                             /* 保留字段             */
} _PACKED_1_ T_Cmt_FCSetMSTSFPTXStatus;

/* 面板FC口环回测试 */
typedef struct
{
    WORD32 dwPortid;             /* 入参，FC端口号1-4 */
    WORD32 wMtsType;             /* 入参，测试类型:MTS_FT,  外环测试: MTS_HT,内环测试 */
    WORD32 dwSndFrameSet;        /* 入参，测试发出帧个数*/
    WORD32 dwSndFrameCount;      /* 出参，发出帧个数 */
    WORD32 dwRcvFrameCount;      /* 出参，收到帧个数 */
    WORD32 dwFrameCheckErrCount; /* 出参，收到的帧中校验有错的个数 */
    WORD32 dwTimeoutMax;         /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_FC;

/* FC速率灯测试 */
typedef struct
{
    WORD32  cPortid;       /* 端口id*/
    WORD32  cLedid;        /* LEDid*/
    WORD32  cLedStatus;    /* LED status*/
    WORD32  dwPreFlag[2];  /* 出参，设置前的两个灯状态，值同上 */
    WORD32  dwCurFlag[2];  /* 出参，设置后的两个灯的状态，值同上 */
    WORD32  dwTimeoutMax;  /* 超时最大值 */
} _PACKED_1_ T_Mts_Check_FC_LED;

/* 工作EPLD自检 */
typedef struct
{
    WORD64 dwCapacity[2];        /*磁盘容量*/
    BYTE   aucPhyDevName[2][64]; /* 硬盘物理设备符名称 */
    BYTE   aucModel[2][64];      /* 硬盘厂商名称 */
    BYTE   aucSerialNum[2][64];  /* 硬盘设备序列号 */
    WORD32 dwformatResult;       /* 格式化测试  */
    WORD32 dwRWResult;           /* 读写测试  */
    WORD32 dwSmartResult;        /* SMART检测结果  */
    WORD32 dwTimeoutMax;         /* 超时最大值 */
    WORD32 dwtype;               /* 测试类型 */
} _PACKED_1_ T_Mts_SPR11_SSD;

/* 工作EPLD自检 */
typedef struct
{
    WORD32 dwTimeoutMax;      /* 超时最大值 */
    T_Mts_SPR11_SSD ssdinfo[2];
} _PACKED_1_ T_Cmt_SPR11_SSD;
/* 工作EPLD自检 */
typedef struct
{
    WORD32  dwPhyNum[2];       /* SAS控制器端口号 */
    WORD64 dwCapacity[2];      /* 硬盘容量 */
    BYTE aucPhyDevName[2][64]; /* 硬盘物理设备符名称 */
    BYTE aucModel[2][64];      /* 硬盘厂商名称 */
    BYTE aucSerialNum[2][64];  /* 硬盘设备序列号 */
    BYTE aucFirmVer[2][64];    /* 硬盘固件版本号 */
    WORD32 dwTimeoutMax;       /* 超时最大值 */
} _PACKED_1_ T_Mts_SPR11_USB;

/* 在位信号测试 */
typedef struct
{
    WORD32   dwOnlieFlag;        /* 在位标志 */
    WORD32   dwTimeoutMax;      /* 超时最大值 */
} _PACKED_1_ T_Mts_SPR11_Online_Flag;

/* 在位信号测试 */
typedef struct
{
    WORD32   dwResult;        /* 是否正常*/
    WORD32  wMtsType;       /* 入参*/
    WORD32   dwTimeoutMax;      /* 超时最大值 */
} _PACKED_1_ T_Mts_SPR11_ChipCLOCK;

/* 在位信号测试 */
typedef struct
{
    WORD32   dwTimeoutMax;      /* 超时最大值 */
    T_Mts_SPR11_ChipCLOCK chiplock[2];
} _PACKED_1_ T_Cmt_SPR11_ChipCLOCK;

/* 在位信号测试 */
typedef struct
{
    WORD32   dwResult;        /* 是否正常*/
    WORD32   dwTimeoutMax;      /* 超时最大值 */
} _PACKED_1_ T_Mts_SPR11_CHECKCOMMON;

/* 在位信号测试 */
typedef struct
{
    WORD32   dwResult;        /* 是否正常*/
    WORD32  wMtsType;       /* 入参，0 背板IO输出，1 背板IO输入，2对板上下点3磁盘在位信息*/
    WORD32   dwPsID;        /* 电源ID*/
    WORD32   dwSwitch;        /* 开关*/
    WORD32  dwSvrOp;
    WORD16  wPowerCtrl;
    BYTE ucDiskSlot[12];
    BYTE ucOnlineFlag[12];
    WORD32   dwTimeoutMax;      /* 超时最大值 */
} _PACKED_1_ T_Mts_SPR11_CHECKBACKPLANEIO;

typedef struct
{
    WORD32 sasAddressHi[2];       /* Expander SAS地址，高32位 */
    WORD32 sasAddressLow[2];      /* Expander SAS地址，低32位 */
    WORD32 chassisId;             /* Expander 箱体ID */
} _PACKED_1_ T_Mts_DspamExpanderInfo;

typedef struct
{
    WORD32 sasBaseAddressHi;      /* SAS基地址，高32位，入参 */
    WORD32 sasBaseAddressLow;     /* SAS基地址，低32位，入参 */
    WORD32 sasEnclosureNum;       /* 箱体个数，入参 */
    WORD32 sasDspamCardNum;       /* 待烧结子卡数目，入参 */
    WORD32 sasDspamOptCode;       /* 操作类型, 入参 */
    WORD32 sasDspamResult;        /* 烧结结果, 出参 */
    T_Mts_DspamExpanderInfo tDspamExpanderInfo[6]; /* 系统中Expander信息，入参 */
} _PACKED_1_ T_Mts_DspamUpdateSasAddrInfo;

/* 在位信号测试 */
typedef struct
{
    WORD32   dwTimeoutMax;        /* 是否正常*/
    T_Mts_DspamUpdateSasAddrInfo DspamInfo;
} _PACKED_1_ T_Mts_SPR11_DSPAM;

/* 设置IBMC的网络信息 */
typedef struct
{
    WORD32   dwTimeoutMax;         /* 超时时限,该功能可填充默认值30m即可，入参 */
    WORD32   udwCtrlFlag;          /* 控制器标记，取值 CTRL_LOCAL、CTRL_PEER，入参*/
    CHAR     cIpAddr[MAX_IP_LEN];  /* IP地址,支持单独设置，与掩码至少配置一项，该参数为空时，不设置IP,入参*/
    CHAR     cNetmask[MAX_IP_LEN]; /* 子网掩码 ，支持单独设置，与IP至少配置一项，该参数为空串时，不设置掩码,入参*/
} _PACKED_1_ T_Mts_SPR11_IBMC_NET;

/* add by tao 2014-6-12 10:41:59 */
typedef struct
{
    WORD32   dwOp;  /* 1 上电，0 下电 */
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_Ctrl;

typedef struct
{
    WORD32  dwModuleSerialNumber[2]; /* spr12下两个RAM */
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_RamId;

typedef struct
{
    WORD32 dwCpuType;
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_CpuType;

typedef struct
{
    WORD32   dwPresent;      /* 子卡在位信息 */
    //BYTE   cLableInfo[MAX_INFO_LABLE_LENGTH]; /* FC电子条码，冯圣琴跟江国才确认没有 */
    WORD16   wBoardId;
    BYTE     ucBoardPcbId;
    BYTE     ucBoardBomId;
    WORD32   dwTimeoutMax;
} _PACKED_1_ T_Mts_FC_Card_Info;

/***********************************spr11 测试仪end****************************************/

/*VPD FRU信息*/
typedef struct
{
    SWORD32  sdwEnclosureId;//箱体ID
    WORD16 uwBackplaneID;//背板ID
    WORD16 uwChassisType;
    CHAR    ucChassisPartNumber[36];
    CHAR    ucChassisSerialNumber[36];
    BYTE    ucLanguageCode;
    BYTE    ucManufacturingDate[3];
    CHAR    ucBoardManufacturer[36];
    CHAR    ucBoardProductName[36];
    CHAR    ucBoardSerialNumber[36];
    CHAR    ucBoardPartNumber[36];
    CHAR    ucVersion[36];
    BYTE    ucBomid;
    BYTE    ucPcbversion;
    CHAR    ucIncumbentCanisterID[24];
    WORD16 uwQualifiedDriveInterfaces;
    WORD16 uwQualifiedIntercanister;
    BYTE    ucNumberSBBCanisterSlots;
    BYTE    ucVentConfiguration1[4];
    BYTE    ucVentConfiguration2[4];
    BYTE    ucVentConfiguration3[4];
    BYTE    ucVentConfiguration4[4];
    BYTE    ucSBBSlotAMax12VCurrent;
    BYTE    ucSBBSlotBMax12VCurrent;
    BYTE    ucNumberPSSupplySlots;
    BYTE    ucMaxDrivespinup;
    BYTE    ucReducedPSMaxspinup;
    WORD16 uwPSVPDAddrpssupply1;
    WORD16 uwPSVPDAddrpssupply2;
    BYTE    ucPSSupply1CtlTWIAddress;
    BYTE    ucPSSupply1CtlTWIBusProtocol;
    BYTE    ucPSSupply2CtlTWIAddress;
    BYTE    ucPSSupply2CtlTWIBusProtocol;
    BYTE    ucSBBSlotAPortMapTable[12];
    BYTE    ucSBBSlotBPortMapTable[12];
    CHAR    ucSBBSignalUsage[36];
    CHAR    ucSBBSGPIOUsage[82];
    CHAR    ucSBBVendorData[36];
} _PACKED_1_ T_VPD;
/**********************************************************************
* 函数名称：GetSvrSocket
* 输入参数：
* 输出参数：ptSvrSoc
* 返 回 值：    0       -   执行成功             非0 -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetSvrSocket(T_SvrSocket *ptSvrSoc);
/**********************************************************************
* 函数名称：SetSvrSocket
* 输入参数：ptSvrSoc
* 输出参数：
* 返 回 值：    0       -   执行成功             非0 -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 SetSvrSocket(T_SvrSocket *ptSvrSoc);

/* FC会话相关 */
/* 目的端口的信息结构 */
typedef struct T_FCObjProtocolInfo
{
    BYTE   ucPortName[FC_WWN_LENGTH];/* 对端的端口名                               */
    BYTE   ucNodeName[FC_WWN_LENGTH]; /* 对端的节点名                             */
    BYTE   ucifTgtFun;                    /* 对端是否具有TARGET功能.    0:不具备;1:具备 */
    BYTE   ucifIniFun;                     /* 对端是否具有INITIATOR功能. 0:不具备;1:具备 */
    WORD16 Reserved;                 /* 保留字段                                   */
} T_FCObjProtocolInfo;

/*单个端口的FC协议信息结构 */
typedef struct T_GetFCProtocolIInfo
{
    SWORD32                   sdwCtrlId;                       /* 控制器号,值为0或1        */
    SWORD32                   sdwPortNo;   /* 端口号，fc信息时端口号范围1-4，fcoe时端口号范围1到2    */
    SWORD32                   sdwSlotNo;    /* new_槽位号 */
    WORD32                    udwPortType;                /* 端口类型，取值: 1(BUSINESS_PORT_TYPE_FC)、2(BUSINESS_PORT_TYPE_FCOE)*/
    SWORD32                   sdwFlag; /* flag为1时，表示为了加入主机，需剔除已在主机中的端口 */
    SWORD32                   sdwValidNum;                  /* 有效的端口登录信息数     */
    /* 端口号，值为1-4          */
    T_FCObjProtocolInfo    tProtItem[FC_ALLOW_PLOGI_CNT];  /* 单条端口登录信息结构数组 */
} T_GetFCProtocolIInfo;

/*单个控制器的端口类型 */
typedef struct T_GetCtrlPortTypeInfo
{
    SWORD32                   sdwCtrlId;                       /* 控制器号,值为0或1        */
    WORD32                    udwPortType;                /* 端口类型，取值: 1(BUSINESS_PORT_TYPE_FC)、2(BUSINESS_PORT_TYPE_FCOE)*/
    SWORD32                   sdwValidNum;                  /* 有效的端口数     */
} T_GetCtrlPortTypeInfo;

/* 单个端口的链路统计信息结构 */
typedef struct T_FCLinkStatisInfo
{

    WORD32  LinkUp; /* 链路UP计数统计                              */
    WORD32  LinkDown;/* 链路DOWN计数统计                           */
    WORD32  ORFECC; /* Outbound Reroute FIFO ECC Correction Count  */
    WORD32  LCFECC; /* Link Control FIFO ECC Correction Count      */
    WORD32  IECC;   /* IFM ECC Correction Count                    */
    WORD32  OECC;   /* OFM ECC Error Count                         */
    WORD32  OCRECC; /* OKey Cache RAM ECC Correction Count         */
    WORD32  MORECC; /* Multi Outbound Request ECC Correction Count */
    WORD32  SCECC;  /* SEST Cache ECC Correction Count             */

    WORD32  RFOC;   /* Reroute FIFO Overflow Count                 */
    WORD32  RPEC;   /* Reroute Parity Error Count                  */
    WORD32  RCEC;   /* Reroute CRC Error Count                     */
    WORD32  SLC;    /* SEST LRU Count                              */
    WORD32  DFC;    /* Discarded Frame Counter                     */
    WORD32  LOS;    /* Loss of Signal Count                        */
    WORD32  BRCC;   /* Bad Received Character Count                */
    WORD32  LOSC;   /* Loss of Synchronization Count               */
    WORD32  LFC;    /* Link Fail Count                             */

    WORD32  REOFa;  /* Received EOFa                               */
    WORD32  DF;     /* Discarded Frames                            */
    WORD32  BCC;    /* Bad CRC Count                               */
    WORD32  PEC;    /* Protocol Error Count                        */
    WORD32  EF;     /* Expired Frames                              */

} T_FCLinkStatisInfo;

/* 单个端口的基本连接业务统计信息结构 */
typedef struct T_FCPortBLSStatisInfo
{
    WORD32  ABTSSendCnt;     /* 发送ABTS计数统计                  */
    WORD32  ABTSACCRcvCnt;   /* 接收ABTS BA_ACCEPT计数统计        */
    WORD32  ABTSRJTRcvCnt;   /* 接收ABTS BA_REJECT计数统计        */

    WORD32  ABTSRcvCnt;      /* 接收ABTS计数统计                  */
    WORD32  ABTSACCSendCnt;  /* 发送ABTS BA_ACCEPT计数统计        */
    WORD32  ABTSRJTSendCnt;  /* 发送ABTS BA_REJECT计数统计        */

    WORD32  NOPSendCnt;      /* 发送NOP计数统计                   */
    WORD32  NOPACCRcvCnt;    /* 接收NOP BA_ACCEPT计数统计         */
    WORD32  NOPRJTRcvCnt;    /* 接收NOP BA_REJECT计数统计         */

    WORD32  NOPRcvCnt;       /* 接收NOP计数统计                   */
    WORD32  NOPACCSendCnt;   /* 发送NOP BA_ACCEPT计数统计         */
    WORD32  NOPRJTSendCnt;   /* 发送NOP BA_REJECT计数统计         */

    WORD32  OtherACCRcvCnt;  /* 接收非ABST与NOP BA_ACCEPT计数统计 */
    WORD32  OtherACCSendCnt; /* 发送非ABST与NOP BA_ACCEPT计数统计 */
    WORD32  OtherRJTRcvCnt;  /* 接收非ABST与NOP BA_REJECT计数统计 */
    WORD32  OtherRJTSendCnt; /* 发送非ABST与NOP BA_REJECT计数统计 */
} T_FCPortBLSStatisInfo;

/* 单个端口的扩展连接业务统计信息结构 */
typedef struct T_FCPortELSStatisInfo
{
    WORD32  FLOGISendCnt;      /* 发送FLOGI计数统计           */
    WORD32  FLOGIACCRcvCnt;    /* 接收FLOGI LS_ACCEPT计数统计 */
    WORD32  FLOGIRJTRcvCnt;    /* 接收FLOGI LS_REJECT计数统计 */

    WORD32  FLOGIRcvCnt;       /* 接收FLOGI计数统计           */
    WORD32  FLOGIACCSendCnt;   /* 发送FLOGI LS_ACCEPT计数统计 */
    WORD32  FLOGIRJTSendCnt;   /* 发送FLOGI LS_REJECT计数统计 */

    WORD32  PLOGISendCnt;      /* 发送PLOGI计数统计           */
    WORD32  PLOGIACCRcvCnt;    /* 接收PLOGI LS_ACCEPT计数统计 */
    WORD32  PLOGIRJTRcvCnt;    /* 接收PLOGI LS_REJECT计数统计 */

    WORD32  PLOGIRcvCnt;       /* 接收PLOGI计数统计           */
    WORD32  PLOGIACCSendCnt;   /* 发送PLOGI LS_ACCEPT计数统计 */
    WORD32  PLOGIRJTSendCnt;   /* 发送PLOGI LS_REJECT计数统计 */

    WORD32  PRLISendCnt;       /* 发送PRLI计数统计            */
    WORD32  PRLIACCRcvCnt;     /* 接收PRLI LS_ACCEPT计数统计  */
    WORD32  PRLIRJTRcvCnt;     /* 接收PRLI LS_REJECT计数统计  */

    WORD32  PRLIRcvCnt;        /* 接收PRLI计数统计            */
    WORD32  PRLIACCSendCnt;    /* 发送PRLI LS_ACCEPT计数统计  */
    WORD32  PRLIRJTSendCnt;    /* 发送PRLI LS_REJECT计数统计  */

    WORD32  LOGOSendCnt;       /* 发送LOGO计数统计            */
    WORD32  LOGOACCRcvCnt;     /* 接收LOGO LS_ACCEPT计数统计  */
    WORD32  LOGORJTRcvCnt;     /* 接收LOGO LS_REJECT计数统计  */

    WORD32  LOGORcvCnt;        /* 接收LOGO计数统计            */
    WORD32  LOGOACCSendCnt;    /* 发送LOGO LS_ACCEPT计数统计  */
    WORD32  LOGORJTSendCnt;    /* 发送LOGO LS_REJECT计数统计  */

    WORD32  PRLOSendCnt;       /* 发送PRLO计数统计            */
    WORD32  PRLOACCRcvCnt;     /* 接收PRLO LS_ACCEPT计数统计  */
    WORD32  PRLORJTRcvCnt;     /* 接收PRLO LS_REJECT计数统计  */

    WORD32  PRLORcvCnt;        /* 接收PRLO计数统计            */
    WORD32  PRLOACCSendCnt;    /* 发送PRLO LS_ACCEPT计数统计  */
    WORD32  PRLORJTSendCnt;    /* 发送PRLO LS_REJECT计数统计  */

    WORD32  SCRSendCnt;        /* 发送SCR计数统计             */
    WORD32  SCRACCRcvCnt;      /* 接收SCR LS_ACCEPT计数统计   */
    WORD32  SCRRJTRcvCnt;      /* 接收SCR LS_REJECT计数统计   */

    WORD32  SCRRcvCnt;         /* 接收SCR计数统计             */
    WORD32  SCRACCSendCnt;     /* 发送SCR LS_ACCEPT计数统计   */
    WORD32  SCRRJTSendCnt;     /* 发送SCR LS_REJECT计数统计   */

    WORD32  RSCNSendCnt;       /* 发送RSCN计数统计            */
    WORD32  RSCNACCRcvCnt;     /* 接收RSCN LS_ACCEPT计数统计  */
    WORD32  RSCNRJTRcvCnt;     /* 接收RSCN LS_REJECT计数统计  */

    WORD32  RSCNRcvCnt;        /* 接收RSCN计数统计            */
    WORD32  RSCNACCSendCnt;    /* 发送RSCN LS_ACCEPT计数统计  */
    WORD32  RSCNRJTSendCnt;    /* 发送RSCN LS_REJECT计数统计  */

    WORD32  ECHOSendCnt;       /* 发送ECHO计数统计            */
    WORD32  ECHOACCRcvCnt;     /* 接收ECHO LS_ACCEPT计数统计  */
    WORD32  ECHORJTRcvCnt;     /* 接收ECHO LS_REJECT计数统计  */

    WORD32  ECHORcvCnt;        /* 接收ECHO计数统计            */
    WORD32  ECHOACCSendCnt;    /* 发送ECHO LS_ACCEPT计数统计  */
    WORD32  ECHORJTSendCnt;    /* 发送ECHO LS_REJECT计数统计  */

    WORD32  ADISCSendCnt;      /* 发送ADISC计数统计           */
    WORD32  ADISCACCRcvCnt;    /* 接收ADISC LS_ACCEPT计数统计 */
    WORD32  ADISCRJTRcvCnt;    /* 接收ADISC LS_REJECT计数统计 */

    WORD32  ADISCRcvCnt;       /* 接收ADISC计数统计           */
    WORD32  ADISCACCSendCnt;   /* 发送ADISC LS_ACCEPT计数统计 */
    WORD32  ADISCRJTSendCnt;   /* 发送ADISC LS_REJECT计数统计 */

    WORD32  PDISCSendCnt;      /* 发送PDISC计数统计           */
    WORD32  PDISCACCRcvCnt;    /* 接收PDISC LS_ACCEPT计数统计 */
    WORD32  PDISCRJTRcvCnt;    /* 接收PDISC LS_REJECT计数统计 */

    WORD32  PDISCRcvCnt;       /* 接收PDISC计数统计           */
    WORD32  PDISCACCSendCnt;   /* 发送PDISC LS_ACCEPT计数统计 */
    WORD32  PDISCRJTSendCnt;   /* 发送PDISC LS_REJECT计数统计 */

    WORD32  OtherELSRcvCnt;    /* 其它ELS接收计数统计         */
    WORD32  OtherELSSendCnt;   /* 其它ELS发送计数统计         */
    WORD32  OtherLSACCRcvCnt;  /* 其它LS_ACCEPT接收计数统计   */
    WORD32  OtherLSACCSendCnt; /* 其它LS_ACCEPT发送计数统计   */
    WORD32  OtherLSRJTRcvCnt;  /* 其它LS_REJECT接收计数统计   */
    WORD32  OtherLSRJTSendCnt; /* 其它LS_REJECT发送计数统计   */
} T_FCPortELSStatisInfo;

/*单个端口的通用业务统计信息结构 */
typedef struct T_FCPortGSStatisInfo
{
    WORD32  GIDPNSendCnt;      /* 发送GIDPN计数统计           */
    WORD32  GIDPNACCRcvCnt;    /* 接收GIDPN CT_ACCEPT计数统计 */
    WORD32  GIDPNRJTRcvCnt;    /* 接收GIDPN CT_REJECT计数统计 */

    WORD32  GPNIDSendCnt;      /* 发送GPNID计数统计           */
    WORD32  GPNIDACCRcvCnt;    /* 接收GPNID CT_ACCEPT计数统计 */
    WORD32  GPNIDRJTRcvCnt;    /* 接收GPNID CT_REJECT计数统计 */

    WORD32  RNNIDSendCnt;      /* 发送RNNID计数统计           */
    WORD32  RNNIDACCRcvCnt;    /* 接收RNNID CT_ACCEPT计数统计 */
    WORD32  RNNIDRJTRcvCnt;    /* 接收RNNID CT_REJECT计数统计 */

    WORD32  RFTIDSendCnt;      /* 发送RFTID计数统计           */
    WORD32  RFTIDACCRcvCnt;    /* 接收RFTID CT_ACCEPT计数统计 */
    WORD32  RFTIDRJTRcvCnt;    /* 接收RFTID CT_REJECT计数统计 */

    WORD32  OtherGSRcvCnt;     /* 其它GS接收计数统计          */
    WORD32  OtherGSSendCnt;    /* 其它GS发送计数统计          */
    WORD32  OtherCTACCRcvCnt;  /* 其它CT_ACCEPT接收计数统计   */
    WORD32  OtherCTACCSendCnt; /* 其它CT_ACCEPT发送计数统计   */
    WORD32  OtherCTRJTRcvCnt;  /* 其它CT_REJECT接收计数统计   */
    WORD32  OtherCTRJTSendCnt; /* 其它CT_REJECT发送计数统计   */
} T_FCPortGSStatisInfo;

/* 单个端口的FCP业务统计信息结构 */
typedef struct T_FCPortFCPStatisInfo
{
    WORD64  CMDSendCnt;     /* FCP命令发送计数统计             */
    WORD64  XFERSendCnt;    /* FCP XFER发送计数统计            */
    WORD64  RESPSendCnt;    /* FCP RESP发送计数统计            */

    WORD64  CMDRcvCnt;      /* FCP命令接收计数统计             */
    WORD64  DATARcvCnt;     /* FCP数据接收计数统计            */
    WORD64  RESPRcvCnt;     /* FCP RESP接收计数统计            */

    WORD64  CMDExeSuccCnt;  /* 命令执行成功计数统计            */
    WORD64  CMDExeFailCnt;  /* 命令执行失败计数统计            */

} T_FCPortFCPStatisInfo;

/*单个端口的统计信息结构 */
typedef struct T_FCGetPortStatisInfo
{
    SWORD32                  CtrlId;     /* 控制器号,值为0或1 */
    SWORD32                  PortNo;     /* 端口号，值为1-4   */
    WORD32                 udwPortType;  /* 端口类型，取值: 1(BUSINESS_PORT_TYPE_FC)、2(BUSINESS_PORT_TYPE_FCOE)*/
    T_FCLinkStatisInfo     tLinkStat;   /* 链路统计信息      */
    T_FCPortBLSStatisInfo  tBLSStat;    /* BLS统计信息       */
    T_FCPortELSStatisInfo  tELSStat;    /* ELS统计信息       */
    T_FCPortGSStatisInfo   tGSStat;     /* GS统计信息  */
    T_FCPortFCPStatisInfo  tFCPStat;    /* FCP统计信息  */
} T_FCGetPortStatisInfo;

/* 单个端口的统计信息结构 */
typedef struct T_ClearFCPortStatisInfo
{
    SWORD32    CtrlId;         /* 控制器号,值为0或1               */
    SWORD32    PortNo;         /* 端口号，值为1-4                 */
} T_ClearFCPortStatisInfo;
/*fc会话信息的呈现cli和web不同， 以下结构体提供给web使用 */

/* SCS获取单个端口的链路统计信息结构 */
typedef struct T_WebGetFCLinkStatisInf
{
    WORD32  LinkUp; /* 链路UP计数统计                              */
    WORD32  LinkDown;/* 链路DOWN计数统计                           */
} T_WebGetFCLinkStatisInf;

/* SCS获取单个端口的基本连接业务统计信息结构 */
typedef struct T_WebGetFCPortBLSStatisInf
{
    WORD32  BLSFrameSendCnt;   /* 发送BLS帧计数        */
    WORD32  BLSACCRcvCnt;      /* 接收BLS ACCEPT帧计数 */
    WORD32  BLSPRJRcvCnt;      /* 接收BLS REJECT帧计数 */

    WORD32  BLSFrameRcvCnt;    /* 接收BLS帧计数 */
    WORD32  BLSACCSendCnt;     /* 发送BLS ACCEPT帧计数 */
    WORD32  BLSPRJSendCnt;     /* 发送BLS REJECT帧计数 */
} T_WebGetFCPortBLSStatisInf;

/* SCS获取Web界面显示的单个端口的扩展连接业务统计信息结构 */
typedef struct T_WebGetFCPortELSStatisInf
{
    WORD32  ELSFrameSendCnt;   /* 发送ELS帧计数        */
    WORD32  ELSACCRcvCnt;      /* 接收ELS ACCEPT帧计数 */
    WORD32  ELSPRJRcvCnt;      /* 接收ELS REJECT帧计数 */

    WORD32  ELSFrameRcvCnt;    /* 接收ELS帧计数 */
    WORD32  ELSACCSendCnt;     /* 发送ELS ACCEPT帧计数 */
    WORD32  ELSPRJSendCnt;     /* 发送ELS REJECT帧计数 */
} T_WebGetFCPortELSStatisInf;

/* SCS获取Web界面显示的单个端口的通用业务统计信息结构 */
typedef struct T_WebGetFCPortGSStatisInf
{
    WORD32  GSFrameSendCnt;   /* 发送GS帧计数        */
    WORD32  GSACCRcvCnt;      /* 接收GS ACCEPT帧计数 */
    WORD32  GSPRJRcvCnt;      /* 接收GS REJECT帧计数 */

    WORD32  GSFrameRcvCnt;    /* 接收GS帧计数 */
    WORD32  GSACCSendCnt;     /* 发送GS ACCEPT帧计数 */
    WORD32  GSPRJSendCnt;     /* 发送GS REJECT帧计数 */
} T_WebGetFCPortGSStatisInf;

typedef struct T_WebGetFCPortStatisInf
{
    SWORD32                sdwCtrlId;           /* 控制器号,值为0或1 */
    SWORD32                sdwPortId;           /* 端口号，值为1-4   */
    WORD32                 udwPortType;      /* 端口类型，取值: 1(BUSINESS_PORT_TYPE_FC)、2(BUSINESS_PORT_TYPE_FCOE)*/
    T_FCPortFCPStatisInfo       tFCPStat;    /* FCP统计信息       */
    T_WebGetFCLinkStatisInf     tLinkStat;   /* 链路统计信息      */
    T_WebGetFCPortBLSStatisInf  tBLSStat;    /* BLS统计信息       */
    T_WebGetFCPortELSStatisInf  tELSStat;    /* ELS统计信息       */
    T_WebGetFCPortGSStatisInf   tGSStat;     /* GS统计信息        */
} T_WebGetFCPortStatisInf;

/*  iSNS*/
typedef struct
{
    CHAR    cIpAddr[MAX_IP_LEN];   /* iSNS Server的IP地址 */
    WORD32  dwPortNo;             /*iSNS Server的监听TCP端口号*/
    WORD32  dwIsnsStatus;     /*操作标志: ISNS_SWITCH_OFF/ ISNS_SWITCH_ON,分别表示关闭、打开。 */
    WORD32  dwIsnsRegStatus;  /* 注册状态 */
    WORD32  dwExistFlag;     /*ISNS_CFG_EXIST_NO:配置不存在\ ISNS_CFG_EXIST_YES:配置存在*/
} _PACKED_1_  T_IsnsInfo;

/* ssd cache */
typedef struct
{
    SWORD32 sdwEnclosureId;  /* 箱体Id，取值 0~实际箱体数*/
    SWORD32 sdwSlotId;       /* 磁盘槽位号，取值0~12 */
    SWORD64 sqwCapacity;     /* 磁盘容量 */
} _PACKED_1_ T_SSDPdInfo;

typedef struct
{
    SWORD32     sdwDiskNum;
    T_SSDPdInfo tSSDPdInfo[MAX_PD_NUM_IN_SYS];
} _PACKED_1_ T_SSDPdList;

/* 该结构体修改需要通知CBS */
typedef struct
{
    T_PdId   tPdId[MAX_PD_NUM_IN_VD];  /* 磁盘信息列表 */
    SWORD32  sdwPdNum;                 /* 磁盘个数 */
} _PACKED_1_ T_CreateSSDCache;

typedef struct
{
    WORD32  dwSwitch;                 /* ssd cache开关, 取值：ON(1)  OFF(0)*/
    SWORD32 sdwPdNum;                 /* 最大32 */
    WORD64  qwCapacity;               /* 容量, 单位KB */
    T_PdId  tPdId[MAX_PD_NUM_IN_VD];  /* 磁盘信息列表 */
} _PACKED_1_ T_SSDCacheInfo;

typedef struct
{
    WORD32  dwSwitch;                 /* ssd cache开关, 取值：ON(1)  OFF(0)*/
} _PACKED_1_ T_SSDCacheSwitch;

typedef struct
{
    WORD32 dwSwitch;        /* ssd cache开关, 取值：ON(1)  OFF(0)*/
    CHAR scVolName[MAX_BLK_NAME_LEN];    /* 卷名 */
} _PACKED_1_ T_SetVolSsdCacheSwitch;
typedef struct
{
    CHAR    sensorName[IPMI_MAX_XMLSTR_LEN]; //传感器名字，取值范围【1-32】
    WORD32  sensorType;                       //传感器类型，参见M_SENSORTYP枚举类型
    WORD32  sensorUnit;                       //传感器单位，参见M_SENSORUNIT枚举类型
    WORD32  sensorHealth;   //传感器健康状态，参见M_HEALTH枚举类型
    CHAR    sensorCurrentVal[IPMI_MAX_XMLSTR_LEN]; //传感器当前值，取值范围【1-32】
    //BYTE    aucSensorThresholdSupported[6];           //传感器的门限是否支持，0表示不支持，1表示支持
    CHAR    sensorThresholds[6][IPMI_MAX_XMLSTR_LEN];   //传感器门限，取值范围【1-32】
} T_SensorInfo;

typedef struct
{
    WORD32  ctrlId; /* 控制器ID,0、1，对应的宏定义CTRL0、CTRL1 */
    WORD32 result;
    WORD32 sensorCount;                               //传感器个数，取值范围【1-255】
    WORD32 deviceHealthState;   //整个单板的健康状态，参见M_HEALTH枚举类型
    T_SensorInfo sensorInfo[IPMI_XMLRPC_MAX_SENSOR]; //所有传感器信息
} T_AllSensorInfo;

typedef struct
{
    WORD32 ctrlId; /* 控制器ID,0、1，对应的宏定义CTRL0、CTRL1 */
    WORD32 ctrlStatus; /* 控制器状态 */

    WORD32 ssdStatus; /* SSD状态 */
    WORD32 crystalDeviceStatus; /* Crystal设备状态,正常为DEVICE_STATUS_OK，异常为DEVICE_STATUS_FALSE */
    WORD32 rtcDeviceStatus;                      /* Rtc设备状态,正常为DEVICE_STATUS_OK，异常为DEVICE_STATUS_FALSE */
    WORD32 ibmcStatus;                             /* IBMC设备状态,正常为DEVICE_STATUS_OK，异常为DEVICE_STATUS_FALSE*/
    WORD32 bbumDeviceStatus;                     /* BBU状态，取值:正常(BBU_NORMAL,0)、异常(BBU_ABNORMAL,1)、电量不足(BBU_LOW_CAPACITY,2) */
} _PACKED_1_ T_SPR20CtrlInfo;

typedef struct
{
    WORD32 result;             //响应返回错误码
    WORD32 slotID;             /**功能子卡槽位号 */
    WORD32 subSlotID;          /**功能子卡叠楼编号，从0开始按照从左到右，从下到上顺序编号*/
    WORD32 funcCardID;         /**功能子卡ID */
    WORD32 bomID;              /**功能子卡BOM ID */
    WORD32 pcb;                /**PCB号 */
    WORD32 onBoard;            /**功能子卡在位信息
                                                     BSP_SUBCARD_ONBOARD   在位
                                                     BSP_SUBCARD_OFFBOARD  不在位
                                                     BSP_SUBCARD_NOT_EXIST 该槽位不存在功能子卡
                                                     BSP_UNKNOWN           不清楚该槽位子卡信息                        */
    WORD32 cardStatus;        /* 子卡状态 */
} _PACKED_1_ T_FuncCardInfo;

typedef struct
{
    SWORD32 ctrlId; /* 控制器ID,0、1，对应的宏定义CTRL0、CTRL1 */
    T_FuncCardInfo funcCardInfo[FUNCARD_MAX_NUM];
} _PACKED_1_ T_AllFuncCardInfo;

//风扇信息
typedef struct
{
    WORD32 result;            //响应返回错误码
    WORD32 slotNo;            //风扇槽位号
    WORD32 fanLevel;          //风扇等级
    WORD32 OnBoard;
} _PACKED_1_ T_Spr20FanInfo;

typedef struct
{
    //WORD32 slotNo;            //风扇槽位号
    T_Spr20FanInfo fanInfo[FAN_MAX_NUM];
} _PACKED_1_ T_AllFanInfo;

//获取PMBUS电源信息(电源输出功率信息)
typedef struct
{
    WORD32  result;
    WORD32  slotnum;          //电源槽位号
    WORD32  OnBoard;          //在位状态
    WORD32  maxOutPutPower;  //电源的最大输出功率
    WORD32  maxEnvTmp;       //电源的环境温度最大值
    WORD32  minEnvTmp;       //电源的环境温度最小值
    WORD32  outPutState;     //电源当前输出状态
} _PACKED_1_ T_PemBasicInfo;

typedef struct
{
    T_PemBasicInfo pemBasicInfo[POWER_MAX_NUM];
} _PACKED_1_ T_PWDInfo;

typedef struct
{
    WORD16 bbuMinSize;
    WORD16 bbumMinSize;
} _PACKED_1_ T_BbumSizeAlarmValue;

typedef  struct
{
    SWORD32 sdwCtrlId;

    WORD16  bbumPresentInfo;      /* BBUM是否在位 */
    WORD16  bbumCommunicate;      /* BBUM能否通信 */
    WORD16  bbumInvalid;          /* BBUM失效状态 */
    WORD16  bbumBoostCircuit;     /* BBUM升压电路故障状态 */
    WORD16  bbumTotalCapacity;    /* BBUM总电池容量是否低于告警阈值 */
    WORD16  bbumInvalidNumStatus; /* BBU失效或升压电路故障数量是否>=N,N默认1 */
    WORD16  bbumAlarmNumMin;      /* BBU失效或升压电路故障数量最小值*/
    WORD16  bbumMaintenance;      /* BBUM维护模式*/

    WORD16  bbuCapabilityMin;     /* BBU电池容量告警阈值 */
    WORD16  bbumCapabilityMin;    /* BBUM总电池容量告警阈值 */

    WORD16  bbuPresent[BBU_NUMBER_MAX];       /* BBU是否在位 */
    WORD16  bbuMaintain[BBU_NUMBER_MAX];      /* BBU维护状态 */
    WORD16  bbuVoltage[BBU_NUMBER_MAX];       /* BBU当前电压 */
    WORD16  bbuCurrent[BBU_NUMBER_MAX];       /* BBU当前电流 */
    WORD16  bbuTemperature[BBU_NUMBER_MAX];   /* BBU当前温度 */
    WORD16  bbubatteryStatus[BBU_NUMBER_MAX]; /* 电池状态(0x16) */
    WORD16  bbuFETControl[BBU_NUMBER_MAX];    /* 电池FETControl(0x46)状态 */
    WORD16  bbuSafetyStatus[BBU_NUMBER_MAX];  /* 电池SafetyStatus(0x51)状态 */
    WORD16  bbuPFStatus[BBU_NUMBER_MAX];      /* 电池PFStatus(0x53)状态 */
    WORD16  bbuChargingStatus[BBU_NUMBER_MAX];/* 电池ChargingStatus(0x55)状态 */
    WORD16  bbuCellVoltage4[BBU_NUMBER_MAX];  /* 电池wCellVoltage4(0x3c)状态 */
    WORD16  bbuCellVoltage3[BBU_NUMBER_MAX];  /* 电池wCellVoltage3(0x3d)状态 */
    WORD16  bbuCellVoltage2[BBU_NUMBER_MAX];  /* 电池wCellVoltage2(0x3e)状态 */
    WORD16  bbuCellVoltage1[BBU_NUMBER_MAX];  /* 电池wCellVoltage1(0x3f)状态 */
    WORD16  bbuVoltageTest[BBU_NUMBER_MAX];       /* BBU当前电压TEST数据 */
    WORD16  bbuCurrentTest[BBU_NUMBER_MAX];       /* BBU当前电流TEST数据  */
    WORD16  bbuTemperatureTest[BBU_NUMBER_MAX];   /* BBU当前温度TEST数据  */

    WORD16  bbuCapacity[BBU_NUMBER_MAX]; /* BBU当前电量值 */
    BYTE    bbuCommFault[BBU_NUMBER_MAX];        /* BBU通讯故障 */
    BYTE    bbuCapacityFault[BBU_NUMBER_MAX];    /* BBU容量告警 */
    BYTE    bbuSecondaryProtect[BBU_NUMBER_MAX]; /* BBU二级保护 */
    BYTE    bbuChargerFault[BBU_NUMBER_MAX];     /* BBU充电器故障 */
    BYTE    bbuChargeoff[BBU_NUMBER_MAX];        /* BBU Chargeoff 状态*/

    BYTE    bbuPowerAlarm[BBU_NUMBER_MAX];      /* 升压电路PWR_ALM */
    BYTE    bbuOverTempProtect[BBU_NUMBER_MAX]; /* 升压电路过温保护 */
    BYTE    bbuCurrentProtect[BBU_NUMBER_MAX];  /* 升压电路输出电流保护 */
    BYTE    bbuVoltageProtect[BBU_NUMBER_MAX];  /* 升压电路输出电压保护 */

    CHAR    bbuDeviceMaker[BBU_NUMBER_MAX][BBU_DEVICE_MAKER_LENTH]; /* bbu设备制造商 */
    CHAR    bbuDeviceName[BBU_NUMBER_MAX][BBU_DEVICE_NAME_LENTH]; /* bbu设备名称 */
} _PACKED_1_ T_Mts_Check_Bbu_Info;

/* 箱体图形界面主界面 */
typedef struct
{
    SWORD32   sdwCtrlId;        /*控制器ID  */
    SWORD32   sdwCtrlState;     /*控制器状态*/
} T_CtrlBriState;

typedef struct
{
    WORD32 dwSlotId;           /*风扇槽位号*/
    WORD32 dwOnBoard;          /*在位标志  */
} T_EncFanBriState;

typedef struct
{
    WORD32  dwSlotId;         /*电源槽位号        */
    WORD32  dwOnBoard;        /*电源在位标志,0、1 */
} T_EncPowBriState;

typedef struct
{
    SWORD32 sdwCtrlId;         /*控制器ID,暂时定义为0、1，对应的宏定义CTRL0、CTRL1*/
    WORD16  uwPresentInfo;     /*Bbu(m)是否在位：0，在位；1，不在位               */
    WORD16  uwDeviceStatus;    /*Bbu(m)设备状态：0，正常；1，异常；2电量不足      */
} T_MainBbuBriInfo;

typedef struct
{
    WORD32   dwChassisId;      /*箱体ID    */
    SWORD32  sdwMaxFanNum;     /*支持风扇最大个数 */
    SWORD32  sdwMaxPowNum;     /*支持电源最大个数 */
    SWORD32  sdwFanNum;        /*风扇个数  */
    SWORD32  sdwPowNum;        /*电源个数  */

    T_EncFanBriState   tFanState[MAX_FAN_NUM];
    T_EncPowBriState   tPowState[POWER_MAX_NUM];
} T_AllEncBriInfo;

typedef struct
{
    WORD32   dwChassisId;      /*箱体ID,只保存主柜信息，id为0  */
    SWORD32  sdwMaxBbuNum;     /*支持bbu(m)最大个数 */
    SWORD32  sdwMaxFanNum;     /*支持风扇最大个数 */
    SWORD32  sdwMaxPowNum;     /*支持电源最大个数 */
    SWORD32  sdwFanNum;        /*风扇个数  */
    SWORD32  sdwPowNum;        /*电源个数  */
    SWORD32  sdwCtrlNum;       /*控制器个数*/
    SWORD32  sdwBbuNum;        /*bbu(m)个数*/

    T_CtrlBriState     tCtrlState[MAX_CTL_NUM];
    T_MainBbuBriInfo   tMainBbu[MAX_BBU_NUM];

    T_EncFanBriState   tFanState[MAX_FAN_NUM];
    T_EncPowBriState   tPowState[POWER_MAX_NUM];
} T_MainEquBriInfo;

typedef struct
{
    BYTE     ucExpcount;          /*扩展柜个数*/
    T_MainEquBriInfo   tMainEqu;  /*主柜控制器和bbu(m)信息*/
    T_AllEncBriInfo    tEncInfo[MAX_UP_SUB_ENCL];     /* 箱体风扇和电源信息，不包括主柜 */
} T_GetAllEquBriInfo;

/* 所有主柜和扩展柜的箱体信息 */
typedef struct
{
    SWORD32   sdwCtrlId;        /*控制器ID  */
    SWORD32   sdwCtrlState;    /*控制器状态*/
    SWORD32   sdwRamCapacity;  /*RAM大小, 单位是M*/
    SWORD32   sdwCtrlRole;     /*控制器角色      */
    CHAR      cCtrlSerial[USP_CONTROLLER_SERIAL_MAX_LEN];  /*控制器序列号*/
    CHAR      cCtrlName[USP_CONTROLLER_NAME_MAX_LEN];      /*控制器名称  */
} T_CtrlState;

typedef struct
{
    WORD32 dwSlotId;           /*风扇槽位号*/
    WORD32 dwOnBoard;          /*在位标志  */
    WORD32 dwFanLevel;         /*风扇等级或转速级别     */
    WORD16 uwFanspeed;         /*实际转速 SPR11和12有效 */
    BYTE   ucFanStatus;        /*风扇状态,取值:DEVICE_STATUS_OK(值为0,风扇正常),DEVICE_STATUS_FALSE(值为1,风扇异常) SPR11和12有效*/
} T_EncFanState;

typedef struct
{
    WORD32  dwSlotId;           /*电源槽位号        */
    WORD32  dwOnBoard;          /*电源在位标志,0、1 */
    WORD32  dwMaxOutPutPower;  /*电源的最大输出功率  仅SPR20有效*/
    WORD32  dwMaxEnvTmp;       /*电源的环境温度最大值 仅SPR20有效*/
    WORD32  dwMinEnvTmp;       /*电源的环境温度最小值 仅SPR20有效*/
    WORD32  dwOutPutState;     /*电源是否有输出       仅SPR20有效*/
    WORD32  dwBrokenFlag;      /*电源故障,0、1      SPR11和12有效*/
} T_EncPowState;

typedef struct
{
    SWORD32 sdwCtrlId;         /*控制器ID,暂时定义为0、1，对应的宏定义CTRL0、CTRL1*/
    WORD16  uwPresentInfo;     /*Bbu(m)是否在位：0，在位；1，不在位               */
    WORD16  uwDeviceStatus;    /*Bbu(m)设备状态：0，正常；1，异常；2电量不足      */
    CHAR    cManufactureName[MAX_DIAG_DEVICE_NAME_LEN]; /*Bbu(m)厂家信息*/
    CHAR    cDeviceName[MAX_DIAG_DEVICE_NAME_LEN];      /*Bbu(m)型号    */
} T_MainBbuInfo;

typedef struct
{
    WORD32   dwChassisId;      /*箱体ID 入参 */
    SWORD32  sdwMaxBbuNum;     /*支持bbu(m)最大个数 最大值共界面用*/
    SWORD32  sdwMaxFanNum;     /*支持风扇最大个数 */
    SWORD32  sdwMaxPowNum;     /*支持电源最大个数 */
    /* 电源和风扇信息 */
    SWORD32  sdwFanNum;        /*风扇个数  */
    SWORD32  sdwPowNum;        /*电源个数  */

    /* 主柜控制器和bbum信息 */
    SWORD32  sdwCtrlNum;       /*控制器个数*/
    SWORD32  sdwBbuNum;        /*bbu(m)个数*/

    T_EncFanState   tFanState[MAX_FAN_NUM];
    T_EncPowState   tPowState[POWER_MAX_NUM];
    T_CtrlState     tCtrlState[MAX_CTL_NUM];
    T_MainBbuInfo   tMainBbu[MAX_BBU_NUM];
} T_GetEncInfo;

typedef struct
{
    BYTE     ucExpcount;                     /* 箱体数目 */
    WORD32   dwChassisId[MAX_UP_SUB_ENCL];   /*  所有箱体id列表 */
} T_GetAllEncList;

/* 单个控制器上的cpu信息列表 */
typedef struct
{
    WORD32 dwCpuFamily;        /* CPU产品系列代号 */
    WORD32 dwModel;            /* CPU属于其系列中的哪一代的代号 */
    WORD32 dwStepping;         /* CPU属于制作更新版本 */
    WORD32 dwCpuMHz;            /* CPU实际使用主频 */
    WORD32 dwCacheSize;        /* CPU二级缓存大小 单位KB*/
    WORD32 dwPhysicalId;       /* 单个CPU的标号 */
    WORD32 dwSiblings;         /* 单个CPU逻辑物理核数 */
    WORD32 dwCpuCores;         /* CPU核数 */
    CHAR   cVendorId[MAX_CTRL_CPU_LEN];  /* CPU设备制造商 */
    CHAR   cModelName[MAX_CTRL_CPU_LEN]; /* CPU属于的名字及其编号、标称主频 */
} T_CtrlCpuInfo;
/* 单个控制器上所有cpu信息 */
typedef struct
{
    SWORD32  sdwCtrlId;                              /* 控制器id     */
    WORD32   dwCpuNum;                               /* 实际CPU个数  */
    T_CtrlCpuInfo tCtrlCpuInfo[MAX_CTRL_CPU_NUM];
} T_GetCtrlCpuInfo;
/* 所有控制器上cpu信息 */
typedef struct
{
    WORD32   dwCtrlNum;                               /* 实际控制器个数  */
    T_GetCtrlCpuInfo tGetCtrlCpuInfo[MAX_CTL_NUM];
} T_GetCtrlAllCpuInfo;

/* 内存信息 */
typedef struct
{
    WORD32  dwSlotId;
    WORD16  uwMemSize;    /* 内存大小,单位M */
    WORD16  uwMemType;    /* 内存型号，取值:BSP_MEM_TYPE_SDRAM,BSP_MEM_TYPE_DDR,BSP_MEM_TYPE_DDR2,BSP_MEM_TYPE_DDR3 */
} T_MemInfo;
typedef struct
{
    SWORD32   sdwCtrlId;                              /* 控制器id     */
    WORD32    dwMemTotal;
    WORD32    dwMemFree;
    WORD32    dwMemNum;                               /* 实际内存条个数  */
    T_MemInfo tMemInfo[MAX_CTRL_MEM_NUM];
} T_GetCtrlMemInfo;
typedef struct
{
    WORD32    dwCtrlNum;                               /* 实际控制器个数  */
    T_GetCtrlMemInfo tCtrlMemInfo[MAX_CTL_NUM];
} T_GetMemInfoList;
/**********************************************************************
* 函数名称：SetIsnsServerCfg
* 输入参数：
* 输出参数：ptIsnsServerCfg
* 返 回 值：    0       -   执行成功             非0 -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 SetIsnsServerCfg(T_IsnsInfo *ptIsnsServerCfg);
/**********************************************************************
* 函数名称：SetIsnsServerCfg
* 输入参数：
* 输出参数：ptIsnsServerCfg
* 返 回 值：    0       -   执行成功             非0 -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32  SetIsnsSwitchStatus(T_IsnsInfo *ptIsnsServerCfg);
/**********************************************************************
* 函数名称：SetIsnsServerCfg
* 输入参数：
* 输出参数：ptIsnsServerCfg
* 返 回 值：    0       -   执行成功             非0 -   执行失败
* 其它说明：无
***********************************************************************/

/**********************************************************************
* 函数名称：SetIsnsServerCfg
* 输入参数：
* 输出参数：ptIsnsServerCfg
* 返 回 值：    0       -   执行成功             非0 -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetIsnsServerCfgInfo(T_IsnsInfo *ptIsnsServerCfg);
/**********************************************************************
* 函数名称：GetIsnsServerRegStatusInfo
* 输入参数：
* 输出参数：*udwIsnsRegStatus
* 返 回 值：    0       -   执行成功             非0 -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32  GetIsnsServerRegStatusInfo(WORD32 *udwIsnsRegStatus);

typedef struct
{
    BYTE  ucChkUpdateUsp;   /* 大版本更新检查 */
} _PACKED_1_ T_UpdateUspChk;

/* 单个层次上的SAS扩展器列表结构 */
typedef struct S_SASExpanderDeviceList
{
    WORD64 ExpanderSASAddr[4];    /* Expander的SAS地址,每层次最多2个Expander */
    BYTE       ExpanderSASAddrDisplay0[8];
    BYTE       ExpanderSASAddrDisplay1[8];
    BYTE       ExpanderSASAddrDisplay2[8];
    BYTE       ExpanderSASAddrDisplay3[8];
} T_SASExpanderDeviceList;

/* SAS扩展器列表结构 */
typedef struct S_SASExpanderList
{
    BYTE                   ExpanderLevelNum;                    /* Expander最大级联数,目前最大为6 */
    BYTE                   ReservedOne;                         /* 保留字段                       */
    WORD16                  ReservedTwo;                         /* 保留字段                       */
    T_SASExpanderDeviceList LevelDevice[6]; /* 每个层次上的设备列表           */
} T_SASExpanderList;

typedef struct
{
    BYTE  PhyNo;                /* PHY编号,从0开始   */
    BYTE  ReservedOne;          /* 保留字段          */
    WORD16 ReservedTwo;          /* 保留字段          */

    WORD32 InvalidDword;         /* 无效字统计        */
    WORD32 Disparityerror;       /* 不一致错误统计    */
    WORD32 LOSNum;               /* 失步统计          */
    WORD32 PhyResetFailedNum;    /* Phy重置失败统计   */
    WORD32 CodeViolationErr;     /* 编码冲突错误统计  */
    WORD32 CRCErrHigh;           /* CRC错误统计高32位 */
    WORD32 CRCErrLower;          /* CRC错误统计低32位 */
} T_SASExpanderPhyStat;

typedef struct
{
    BYTE                PageCode;                                  /* 页面码0xA6          */
    BYTE                ReservedOne;                               /* 保留字段            */
    WORD16               PageLength;                                /* 页面长度            */
    BYTE                OperType;                                  /* 操作类型            */
    BYTE                ReservedTwo;                               /* 保留字段            */
    WORD16               ReservedThree;                             /* 保留字段            */
    T_SASExpanderPhyStat ExpanderPhyStat[36]; /* PHY统计信息结构数组 */
} T_SASExpanderStat;
typedef struct
{
    BYTE  PhyNo;                /* PHY编号,从0开始   */
    BYTE  ReservedOne;          /* 保留字段          */
    WORD16 ReservedTwo;          /* 保留字段          */

    BYTE  SASG1PREEMPHASIS;     /* SAS 1.5G预加重参数  */
    BYTE  SASG1SWING;           /* SAS 1.5G振幅参数    */
    BYTE  SASG2PREEMPHASIS;     /* SAS 3G预加重参数    */
    BYTE  SASG2SWING;           /* SAS 3G振幅参数      */
    BYTE  SASG3PREEMPHASIS;     /* SAS 6G预加重参数    */
    BYTE  SASG3SWING;           /* SAS 6G振幅参数      */
    BYTE  SATAG1PREEMPHASIS;    /* SATA 1.5G预加重参数 */
    BYTE  SATAG1SWING;          /* SATA 1.5G振幅参数   */
    BYTE  SATAG2PREEMPHASIS;    /* SATA 3G预加重参数   */
    BYTE  SATAG2SWING;          /* SATA 3G振幅参数     */
    BYTE  SATAG3PREEMPHASIS;    /* SATA 6G预加重参数   */
    BYTE  SATAG3SWING;          /* SATA 6G振幅参数     */
} T_SASExpanderPhyPara;

/* 8005参数信息页面结构 */
typedef struct
{
    BYTE                PageCode;                                  /* 页面码0xA7          */
    BYTE                ReservedOne;                               /* 保留字段            */
    WORD16               PageLength;                                /* 页面长度            */
    BYTE                OperType;                                  /* 操作类型            */
    BYTE                ReservedTwo;                               /* 保留字段            */
    WORD16               ReservedThree;                             /* 保留字段            */
    T_SASExpanderPhyPara ExpanderPhyStat[36]; /* PHY参数信息结构数组 */
} T_SASExpanderPara;

typedef struct
{
    BYTE                     OperType;    /* 操作类型           */
    BYTE                     CmpStatus;   /* 定时比较状态       */
    BYTE                     CmpHours;    /* 定时比较时长小时值 */
    BYTE                     CmpMinutes;  /* 定时比较时长分钟值 */
} T_SASExpanderCmpTimer;

typedef struct
{
    BYTE  ifItemValid;          /* 条目是否有效       */
    BYTE  DiskNo;               /* 磁盘号,从1开始编号 */
    WORD16  Reserved;             /* 保留字段           */
    WORD64  DiskAddr;
    WORD64 RawReadErrRate;       /* 未格式化读错误     */
    WORD64 SoftReadErrRate;      /* 软件读错误         */
    WORD64 UDMACRCErrRate;       /* UDMA CRC错误       */
    WORD64 WriteErrRate;         /* 写错误             */
    WORD64 ReadErrRetryRate;     /* 读错误重试         */
} T_SASExpanderSMARTStatInfo;

/* 磁盘S.M.A.R.T信息显示结构 */
typedef struct
{
    WORD64                     ExpanderSASAddr;                      /* Expander的SAS地址     */
    T_SASExpanderSMARTStatInfo SmartInfo[12]; /* 磁盘S.M.A.R.T信息结构 */
} T_SASExpanderSMARTInfo;

typedef struct
{
    WORD64  ExpanderSASAddr;
    BYTE       opcode;
    BYTE       phyid;
    T_SASExpanderPara exppara;
    T_SASExpanderStat expstat;
    T_SASExpanderCmpTimer cmptimer;
    T_SASExpanderSMARTInfo smartinfo;
} T_SASExpanderPhyOp;
typedef struct
{
    CHAR      cVdName[MAX_BLK_NAME_LEN];  /*VD 名称,不能为空，入参*/
    SWORD32   sdwEnergyConsrv;            /* 省电模式字段,打开(1)/关闭(0)，入参 */
} _PACKED_1_ T_VdEnergyConsrvMod;

/* add by tao 2014-8-18 */
typedef struct
{
    CHAR    cHostAlias[MAX_ALIAS_NAME_LEN];
    BYTE    ucOs; /* Linux、Windows、Solaris、HP-UX、AIX、XenSever、Mac OS */
} _PACKED_1_ T_HostBrief;

typedef struct
{
    CHAR    cHostAlias[MAX_ALIAS_NAME_LEN];
    CHAR    cNewHostAlias[MAX_ALIAS_NAME_LEN];  /* 不设置此项时填空字符串 */
    BYTE    ucOs; /* 不设置此项时填-1 */
} _PACKED_1_ T_ModifyHostAttr;

typedef struct
{
    BYTE    ucType;/* fc or iscsi */
    CHAR    cPortName[MAX_INI_NAME_LEN]; /* 224 iqn or wwn */
    SWORD32 sdwMultiPathMode;
    CHAR    cMulChapPass[CHAP_ACCOUNT_PASS_MAX];/* 空时就是不使能 */
} _PACKED_1_ T_Port;

typedef struct
{
    CHAR    cPortName[MAX_INI_NAME_LEN]; /* 224 iqn or wwn */
    CHAR    cMulChapPass[CHAP_ACCOUNT_PASS_MAX];/* 空时就是不使能 */
} _PACKED_1_ T_MutualChap;

typedef struct
{
    T_HostBrief tHost;
    T_Port      tPort;
} _PACKED_1_ T_CreateHost;

typedef struct
{
    CHAR        cHostAlias[MAX_ALIAS_NAME_LEN];
    BYTE        ucOs; /* Linux、Windows、Solaris、HP-UX、AIX、XenSever、Mac OS */
    SWORD32     sdwPortNum;
    T_Port      tPort[MAX_PORT_IN_HOST];
    CHAR        cMapGrpName[MAX_MAPGRP_NAME_LEN];/* 所属映射组名 */
} _PACKED_1_ T_Host;

typedef struct
{
    WORD16  udwBgnIdx;/*要获取信息的起始位置，入参，从0开始*/
    WORD32  udwCount;/*返回主机数量，出参*/
    BYTE    udwFinFlag;/* 是否继续获取的标识，出参 1表示完结 0表示需要继续获取*/
    T_Host  tHost[MAX_HOST_GET_ONCE];
} _PACKED_1_ T_AllHostOnce;

typedef struct
{
    CHAR    cHostAlias[MAX_ALIAS_NAME_LEN];
    CHAR      cMapGrpName[MAX_MAPGRP_NAME_LEN];
    BYTE      ucOs;
} _PACKED_1_ T_HostSimpleInfo ;
typedef  struct
{
    SWORD32         sdwHostNum;
    T_HostSimpleInfo tHostSimpleInfo[MAX_HOST_NUM_IN_SYS];
} _PACKED_1_ T_AllHostSimpleInfoList;

typedef struct
{
    CHAR    cHostAlias[MAX_ALIAS_NAME_LEN];
} _PACKED_1_ T_HostAlias;

typedef struct
{
    T_Port  tPort;
    CHAR    cHostAlias[MAX_ALIAS_NAME_LEN];
} _PACKED_1_ T_AddPortToHost;

typedef struct
{
    CHAR    cPortName[MAX_INI_NAME_LEN]; /* 224 iqn or wwn */
    CHAR    cHostAlias[MAX_ALIAS_NAME_LEN];
} _PACKED_1_ T_DelPortFrmHost;

typedef struct
{
    CHAR    cPortName[MAX_INI_NAME_LEN]; /* 224 iqn or wwn */
    SWORD32 sdwMultiPathMode;
} _PACKED_1_ T_MultiPathMode;

/**********************************************************************
* 函数名称：    CreateHost
* 功能描述：    创建主机
* 输入参数：    主机别名、操作系统；
                端口类型（FC/ISCSI）、端口WWPN/IQN、多路径模式
                CHAP密码（ISCSI类型）
* 输出参数：    无
* 返 回 值：    0 -  执行成功，非0 - 执行失败
* 其它说明：
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014-8-5        V1.0       taolj        初次创建
***********************************************************************/
SWORD32 CreateHost(T_CreateHost *pHost);

/**********************************************************************
* 函数名称：    SetMultiPathMode
* 功能描述：    设置多路径模式
* 输入参数：    端口WWPN/IQN、多路径模式
* 输出参数：    无
* 返 回 值：    0 -  执行成功，非0 - 执行失败
* 其它说明：
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014-8-5        V1.0       taolj        初次创建
***********************************************************************/
SWORD32 SetMultiPathMode(T_MultiPathMode *p);

/**********************************************************************
* 函数名称：    AddPortToHost
* 功能描述：    将端口加入主机
* 输入参数：    端口类型（FC/ISCSI）、端口WWPN/IQN、多路径模式、
                CHAP密码（ISCSI类型）、主机别名
* 输出参数：    无
* 返 回 值：    0 -  执行成功，非0 - 执行失败
* 其它说明：
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014-8-5        V1.0       taolj        初次创建
***********************************************************************/
SWORD32 AddPortToHost(T_AddPortToHost *p);

/**********************************************************************
* 函数名称：    DelPortFromHost
* 功能描述：    从主机中删除端口
* 输入参数：    主机WWPN/IQN，主机名
* 输出参数：    无
* 返 回 值：    0 -  执行成功，非0 - 执行失败
* 其它说明：
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014-8-5        V1.0       taolj        初次创建
***********************************************************************/
SWORD32 DelPortFromHost(T_DelPortFrmHost *p);

/**********************************************************************
* 函数名称：    DelHost
* 功能描述：    删除主机
* 输入参数：    主机名
* 输出参数：
* 返 回 值：    0 -  执行成功，非0 - 执行失败
* 其它说明：
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014-8-5        V1.0       taolj        初次创建
***********************************************************************/
SWORD32 DelHost(T_HostAlias *p);

/**********************************************************************
* 函数名称：    ModifyHostAttr
* 功能描述：    修改主机属性
* 输入参数：    主机别名、主机OS
* 输出参数：    无
* 返 回 值：    0 -  执行成功，非0 - 执行失败
* 其它说明：
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014-8-5        V1.0       taolj        初次创建
***********************************************************************/
SWORD32 ModifyHostAttr(T_ModifyHostAttr *p);

/**********************************************************************
* 函数名称：    ModifyMutualChap
* 功能描述：    修改CHAP属性
* 输入参数：    IQN、CHAP密码，CHAP密码为空时即禁用CHAP
* 输出参数：
* 返 回 值：    0 -  执行成功，非0 - 执行失败
* 其它说明：
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014-8-5        V1.0       taolj        初次创建
***********************************************************************/
SWORD32 ModifyMutualChap(T_MutualChap *p);

/**********************************************************************
* 函数名称：    GetAllHostOnce
* 功能描述：    获取所有主机信息
* 输入参数：    无
* 输出参数：    所有主机信息
* 返 回 值：    0 -  执行成功，非0 - 执行失败
* 其它说明：    一次性获取数据太大，所以分次获取，下标从0开始
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014-8-5        V1.0       taolj        初次创建
***********************************************************************/
SWORD32 GetAllHostOnce(T_AllHostOnce *p);

SWORD32 GetAllHostSimpleInfo(T_AllHostSimpleInfoList *ptHostSimpleInfoList);

/**********************************************************************
* 函数名称：    GetHost
* 功能描述：    获取指定主机信息
* 输入参数：    无
* 输出参数：    主机信息
* 返 回 值：    0 -  执行成功，非0 - 执行失败
* 其它说明：
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014-8-5        V1.0       taolj        初次创建
***********************************************************************/
SWORD32 GetHost(T_Host *p);

/***************************************Pd***************************************/
/**********************************************************************
* 功能描述： 获取所有磁盘列表
* 输入参数： 无
* 输出参数：全部为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetAllPdId(T_AllPdId *ptAllPdId);
/**********************************************************************
* 功能描述： 获取硬盘硬属性
* 输入参数： ptPdHwInfo->sdwSLotId,pPdHwInfo->sdwEnclour
* 输出参数： 其他为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/

/**********************************************************************
* 功能描述： 获取磁盘信息
* 输入参数： ptPdHwInfo->sdwSLotId,pPdHwInfo->sdwEnclour
* 输出参数： 其他为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetHddInfo(T_HddInfo *ptHddInfo);
/**********************************************************************
* 功能描述： 获取磁盘详细信息
* 输入参数： ptPdHwInfo->sdwSLotId,pPdHwInfo->sdwEnclour
* 输出参数： 其他为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetHddDetailInfo(T_HddInfo *ptHddInfo);

/**********************************************************************
* 功能描述： 获取所有磁盘信息
* 输入参数： 无
* 输出参数： 均为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetAllHddInfo(T_AllHddInfo *ptAllHddInfo);
/**********************************************************************
* 功能描述： 按照磁盘类型获取所有空闲盘信息
* 输入参数： 无
* 输出参数： 均为出参(sas和sata盘的数目，slotid和容量)
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetAllUnusedDisk(T_AllUnusedPd *ptAllUnusedPd);
/**********************************************************************
* 功能描述： 设置硬盘硬属性（传输速率、节能模式、cache开关）
* 输入参数： pPdHwInfo->sdwSlotId,pPdHwInfosdwEnclouserId
* 输出参数：其他为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetPdHwInfo(T_PdSetHwInfo *pPdHwInfo);

/**********************************************************************
* 功能描述： 空闲盘变成热备盘
* 输入参数：全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/

SWORD32 SetPdUnusedToHotSpare(T_PdId *ptPdId);
/**********************************************************************
* 功能描述： 热备盘变成空闲盘
* 输入参数： 全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetPdHotSpareToUnsed(T_PdId *ptPdId);

/**********************************************************************
* 功能描述： 未知盘和冲突盘转换为空闲盘
* 输入参数： 全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetPdToUnsed(T_PdId *ptPdId);

/**********************************************************************
* 功能描述： 设置磁盘坏块告警数目
* 输入参数： 无
* 输出参数： BadBlockWarnNum
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetBadBlockWarnNum(T_PdBadBlockWarnNum *ptPdBadBlockWarnNum);

/**********************************************************************
* 功能描述： 查询磁盘坏块告警
* 输入参数： BadBlockWarnNum
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetBadBlockWarnNum(T_PdBadBlockWarnNum *ptPdBadBlockWarnNum);

/**********************************************************************
* 功能描述：获取磁盘的SMART状态信息（针对单个硬盘）
* 输入参数：EnclosureId  ,  SlotId
* 输出参数：其他为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetPdSmartStateInfo(T_PdSmartStateInfo *ptPdSmartStateInfo);

/**********************************************************************
* 功能描述： 查询Smart信息
* 输入参数：EnclosureId  ,  SlotId
* 输出参数：其他为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetSmartInfo(T_PdSmartInfo *ptSmartInfo);

/**********************************************************************
* 功能描述： 使能/ 禁止硬盘Smart告警开关
* 输入参数： ptPdWarnSwitch
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetPdWarnSwitchStatus(T_PdWarnSwitch *ptPdWarnSwitch);

/**********************************************************************
* 功能描述： 获取磁盘告警开关
* 输入参数： EnclosureId  ,  SlotId
* 输出参数： sdwSwitch
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetPdWarnSwitchStatus(T_PdWarnSwitch *ptPdWarnSwitch);

/**********************************************************************
* 功能描述： 获取磁盘扫描信息
* 输入参数：  无
* 输出参数：  ptHddScanInfo
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetHddScanInfo(T_HddScanInfo *ptHddScanInfo);

/**********************************************************************
* 功能描述： 发起磁盘扫描
* 输入参数： ptHddScanPeriod
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 StartHddScan(T_HddScanPeriod *ptHddScanPeriod);

/**********************************************************************
* 功能描述： 中止磁盘扫描
* 输入参数： 无
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 StopHddScan(void);

/**********************************************************************
* 功能描述： 设置磁盘扫描周期
* 输入参数： ptHddScanInfo
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetHddScanPeriod(T_HddScanPeriod *ptHddScanPeriod);

/**********************************************************************
* 功能描述： 查询扫描任务进度
* 输入参数： EnclosureId  ,  SlotId
* 输出参数：  其他为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetPdScanProgress(T_PdScanStatus *ptPdScanStatus);

/**********************************************************************
* 功能描述： 磁盘扫描
* 输入参数： sdwPdSlotId、sdwPdEnclosureId、sdwCtrlFlg
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 ScanPd(T_PdScanCtrl *ptPdScanCtrl);

/**********************************************************************
* 功能描述： 控制硬盘灯闪烁
* 输入参数： ptPdLed->sdwSlotId,sdwSlotId->sdwEnclouserId
* 输出参数： 其他为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 CtrlPdLed(T_PdLed *ptPdLed);

/**********************************************************************
* 功能描述： 磁盘热插入(自动化测试使用)
* 输入参数： sdwPdSlotId、sdwPdEnclosureId
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32  PluginHdd(T_PdId *ptPdId);

/**********************************************************************
* 功能描述： 磁盘热拔出(自动化测试使用)
* 输入参数： sdwPdSlotId、sdwPdEnclosureId
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32  PulloutHdd(T_PdId *ptPdId);

/***************************************Blk***************************************/
/**********************************************************************
* 功能描述： 创建池
* 输入参数： *ptCreatePool
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 CreatePool(T_CreatePool *ptCreatePool);

/**********************************************************************
* 功能描述： 删除存储池
* 输入参数： *ptPoolName
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 DelPool(T_PoolName *ptPoolName);

/**********************************************************************
* 功能描述： 查询存储池
* 输入参数： *scPoolName
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetPoolInfo(T_PoolInfo *ptPoolInfo);

/**********************************************************************
* 功能描述： 存储池上创建卷
* 输入参数： *ptCreateVolOnPool
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 CreateVolOnPool(T_CreateVolOnPool *ptCreateVolOnPool);

/**********************************************************************
* 功能描述：  查询系统中所有存储池名称列表
* 输入参数：  无
* 输出参数：  全部
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：  无
***********************************************************************/
SWORD32 GetAllPoolNames(T_AllPoolNames *ptAllPoolNames);

/**********************************************************************
* 功能描述：  获取存储池上的虚拟卷名称列表
* 输入参数：  cPoolName:存储池名称
* 输出参数：  cVolNames
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：  无
***********************************************************************/
SWORD32 GetVolNamesOnPool(T_VolNamesOnPool *ptAllVolNamesOnPool);

/**********************************************************************
* 功能描述：  修改存储池属性（名称、容量告警阈值、空间保留策略）
* 输入参数：  全部
* 输出参数：  无
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：  无
***********************************************************************/
SWORD32 ModifyPool(T_ModifyPool *ptModifyPool);

/**********************************************************************
* 功能描述：  存储池扩容
* 输入参数：  全部
* 输出参数：  无
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：  当按照磁盘列表修改时，结构体中的tPdId才有效
***********************************************************************/
SWORD32 ExpandPool(T_ExpandPool *ptExpandPool);

/**********************************************************************
* 功能描述：  存储池上的虚拟卷扩容
* 输入参数：  全部
* 输出参数：  无
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：  无
***********************************************************************/
SWORD32 ExpandVolOnPool(T_ExpVolCapacity *ptExpVolCapacity);

/**********************************************************************
* 功能描述：  修改pool上卷的迁移策略
* 输入参数：  全部
* 输出参数：  无
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：  无
***********************************************************************/
SWORD32 ModifyVolMovePolicy(T_ModifyVolMovePolicy *ptModifyVolMovePolicy);

/**********************************************************************
* 功能描述：  启动pool上的数据迁移
* 输入参数：  全部
* 输出参数：  无
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：  无
***********************************************************************/
SWORD32 StartZtierMovingOnPool(T_StartPoolMoving *ptStartPoolMoving);

/**********************************************************************
* 功能描述：  停止pool上的数据迁移
* 输入参数：  全部
* 输出参数：  无
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：  无
***********************************************************************/
SWORD32 StopZtierMovingOnPool(T_PoolName *ptPoolName);

/**********************************************************************
* 功能描述：  pool迁移状态信息查询
* 输入参数：  全部
* 输出参数：  无
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：  无
***********************************************************************/
SWORD32 GetZtierMovingStatus(T_PoolMovingStatusInfo *ptPoolMovingInfo);

/**********************************************************************
* 功能描述：  转换Thin卷为普通卷
* 输入参数：  卷名称
* 输出参数：  无
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：  无
***********************************************************************/
SWORD32 ChangeThinVol(T_VolName *ptVolName);

/**********************************************************************
* 功能描述：  修改Thin卷属性
* 输入参数：  卷名称
* 输出参数：  无
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：  无
***********************************************************************/
SWORD32 ModifyThinVol(T_ModifyThinVol *ptModifyThinVol);

/**********************************************************************
* 功能描述：  获取可供pool使用的指定类型的磁盘列表
* 输入参数：  全部
* 输出参数：  无
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：  无
***********************************************************************/
SWORD32 GetUsableHddListForPool(T_HddListForPool *ptHddListForPool);

/**********************************************************************
* 功能描述：  修改存储池节能属性
* 输入参数：  全部
* 输出参数：  无
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：  无
***********************************************************************/

SWORD32 ModifyPoolEnergyConv(T_ModifyPoolMaid *ptModifyPool);

/**********************************************************************
* 功能描述：检查磁盘是否一致
* 输入参数：ptCheckPdConsistency
* 输出参数：
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 CheckPdConsistency(T_CheckPdConsistency *ptCheckPdConsistency);

/**********************************************************************
* 功能描述：系统自动选择磁盘创建虚拟盘
* 输入参数：ptAutoCreateVd
* 输出参数：
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 AutoCreateVd(T_AutoCreateVd *ptAutoCreateVd);
/**********************************************************************
* 功能描述： 创建虚拟盘
* 输入参数： *ptCreateVd
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 CreateVd(T_CreateVd *ptCreateVd);
/**********************************************************************
* 功能描述： 删除虚拟盘
* 输入参数： sdwVdId
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 DelVd(T_VdName *ptVdName);
/**********************************************************************
* 功能描述： 获取虚拟盘个数及Id
* 输入参数： 无
* 输出参数： *ptAllVdId
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/

SWORD32 GetAllVdNames(T_AllVdNames *ptAllVdNames);
/**********************************************************************
* 功能描述： 根据名称查询虚拟盘信息
* 输入参数： ptVdInfo->udwVdNum
* 输出参数： 其他为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetVdInfo(T_VdInfo *ptVdInfo);

/**********************************************************************
* 功能描述： 获取虚拟盘上的所有VOL名称
* 输入参数： ptAllVolIdonVd->sdwVdID
* 输出参数：其他为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/

SWORD32 GetVolNamesOnVd(T_AllVolNamesOnVd *ptAllVolNamesOnVd);
/**********************************************************************
* 功能描述： 获取虚拟盘上的卷ID
* 输入参数： ptAllVolIdonVd->sdwVdID
* 输出参数：其他为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/

/**********************************************************************
* 功能描述： 设置虚拟盘名称
* 输入参数： *ptVdName
* 输出参数：  无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 RenameVd(T_VdRename *ptVdRename);
/**********************************************************************
* 功能描述： 设置虚拟盘首选控制器
* 输入参数： *ptVdPreferVtl
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/

/**********************************************************************
* 功能描述： 设置虚拟盘自动重建开关
* 输入参数： *ptVdAuReb
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetVdAutoRebuild(T_VdAutoRebuild *ptVdAutoRebuild);
/**********************************************************************
* 功能描述： 虚拟盘数据一致性检查
* 输入参数： sdwVdId
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/

SWORD32 CheckVdConsistency(T_VdName *ptVdName);
/**********************************************************************
* 功能描述： 虚拟盘重新校验
* 输入参数： sdwVdId
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/

SWORD32 RegenerateParityVd(T_VdName *ptVdName);
/**********************************************************************
* 功能描述： 获取虚拟盘任务信息
* 输入参数： ptVdTaskInf->sdwVdId
* 输出参数：其他都为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetVdTaskInfo(T_VdGetTaskInfo *ptVdTaskInfo);
/**********************************************************************
* 功能描述： 虚拟盘碎片整理
* 输入参数： sdwVdId
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/

SWORD32 DefragmentVd(T_VdName *ptVdName);
/**********************************************************************
* 功能描述：虚拟盘手动重建
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/

SWORD32 RebuildVd(T_VdRebuild *ptVdRebuild);
/**********************************************************************
* 功能描述： 虚拟盘扩展
* 输入参数：  *ptVdExpand
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/

SWORD32 ExpandVd(T_VdExpand *ptVdExpand);
/**********************************************************************
* 功能描述： 虚拟盘变级
* 输入参数： *ptVdRelevel
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/

SWORD32 RelevelVd(T_VdRelevel *ptVdRelevel);
/**********************************************************************
* 功能描述： 虚拟盘冻结
* 输入参数： *ptVdName
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 FreezeVd(T_VdName *ptVdName);
/**********************************************************************
* 功能描述： 虚拟盘解冻
* 输入参数： *ptVdName
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 UnFreezeVd(T_VdName *ptVdName);
/**********************************************************************
* 功能描述： 虚拟盘迁入
* 输入参数： *ptVdName
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/

/**********************************************************************
* 功能描述： 创建卷
* 输入参数： *ptCreateVol
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 CreateVol(T_CreateVol *ptCreateVol);

/**********************************************************************
* 函数名称：SetVolFlowLimitAttr
* 功能描述：设置流量上限
* 访问的表：
* 修改的表：T_SCS_LUN
* 输入参数：
* 输出参数：
* 返 回 值：  0      -   执行成功
*                              非0 - 执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2015/01/16                 V1.0                 zhangchao               初次创建
***********************************************************************/
SWORD32 SetVolFlowLimitAttr(T_VolFlowLimitInfo *ptVolFlowLimitInfo);

/**********************************************************************
* 功能描述： 删除卷
* 输入参数： *ptDelVol
* 输出参数：无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/

SWORD32 DelVol(T_VolName *ptVolName);

/**********************************************************************
* 函数名称：  ForceDelVol
* 功能描述：  强制删除卷
* 访问的表：
* 修改的表：
* 输入参数：  卷名
* 输出参数：  无
* 返 回 值：  0      -   执行成功
*             非0    - 执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------

***********************************************************************/
SWORD32 ForceDelVol(T_VolName *ptVolName);

/**********************************************************************
* 功能描述： 卷统计信息
* 输入参数： T_VolStat
* 输出参数：无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetVolStatData(T_GetVolStat *ptStatVolInfo);

/**********************************************************************
* 功能描述： 卷重命名
* 输入参数： 全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 RenameVol(T_VolRename *ptVolRename);
/**********************************************************************
* 功能描述： 卷扩容
* 输入参数： 全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 ExpandVol(T_ExpVol *ptExpVol);
/**********************************************************************
* 功能描述： 卷变条带
* 输入参数： 全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 ReSegmentVol(T_ReSegVol *ptReSegVol);
/**********************************************************************
* 功能描述： 获取指定卷信息
* 输入参数： ptVolInf->sdwVolId
* 输出参数：其他为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetVolInfo(T_VolInfo *ptVolInfo);
/**********************************************************************
* 功能描述： 卷写0初始化
* 输入参数： ptVolInit->sdwVdId,   ptVolInit->sdwVolId
* 输出参数：其他为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 ZeroInitVol(T_VolName *VolName);
/**********************************************************************
* 功能描述： 设置卷prefer控制器
* 输入参数： 全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetVolPreferCtrl(T_VolPreferCtrl *ptVolPreferCtrl);
/**********************************************************************
* 功能描述： 获取卷的任务信息
* 输入参数： ptVolTaskInf->sdwVdId, ptVolTaskInf->sdwVolId
* 输出参数：其他为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetVolTaskInfo(T_VolGetTaskInfo *ptVolTaskInfo);

/**********************************************************************
* 功能描述： 创建快照
* 输入参数： 全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 CreateSvol(T_SvolCreate *ptSvolCreate);
/**********************************************************************
* 函数名称：GetRepoInfo
* 功能描述：根据卷名字获取卷上的资源卷信息
* 输入参数：
* 输出参数：
* 返 回 值：  0    -   执行成功   非0 - 执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetRepoInfo(T_RepoInfo *ptRepoInfo);

/**********************************************************************
* 函数名称：  GetRepoList
* 功能描述：获取系统中所有快照资源卷信息以及所在卷名字
* 输入参数：
* 输出参数：
* 返 回 值：  0      -   执行成功
*                              非0 - 执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetRepoList(T_AllRepoList *ptRepoList);

/**********************************************************************
* 功能描述： 删除快照
* 输入参数： 全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 DelSvol(T_SvolName *ptSvolName);
SWORD32 SyncForceDelSvol(T_SvolName *ptSvolName);
/**********************************************************************
* 功能描述： 强制删除快照
* 输入参数： 全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 ForceDelSvol(T_SvolName *ptSvolName);
/**********************************************************************
* 功能描述： 恢复快照
* 输入参数： sdwSvolId
* 输出参数：无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：底层SNAP暂时最小功能集中不做
***********************************************************************/
SWORD32 RestoreSvol(T_SvolName *ptSvolName);
/**********************************************************************
* 功能描述： 重命名快照
* 输入参数： 全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 RenameSvol(T_SvolRename *ptSvolRename);

/**********************************************************************
* 函数名称：  SetSnapMode
* 功能描述：
* 访问的表：
* 修改的表：
* 输入参数：
* 输出参数：
* 返 回 值：  0      -   执行成功
*                              非0 - 执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/07/22      V1.0       姚冬         初次创建
***********************************************************************/
SWORD32 SetSnapMode(T_SnapSetMode *ptSetSnapMode);

/**********************************************************************
* 功能描述： 查看指定快照卷属性
* 输入参数： ptSvolInfo-> udwSvolId;
* 输出参数： 其他为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetSvolInfo(T_SvolInfo *ptSvolInfo);

/**********************************************************************
* 功能描述： 查看卷上的所有快照卷信息
* 输入参数：
* 输出参数： 全部
* 返 回 值：  0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetAllSvolInfoOnVol(T_AllSvolNameListOnVol *ptAllSvolListOnVol);
/**********************************************************************
* 功能描述： 查看系统中所有快照卷属性
* 输入参数：
* 输出参数： 全部
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetAllSvolInfo(T_AllSvolNameList *ptAllSvolList);

/**********************************************************************
* 功能描述： 查看快照卷相关信息
* 输入参数：
* 输出参数： 全部
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：创建克隆时快照源卷所需要的信息
***********************************************************************/
SWORD32 GetSvolInfoList(T_AllSvolNameList *ptAllSvolList);

/**********************************************************************
* 功能描述： 设置快照卷告警阀值
* 输入参数： 全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetSvolThr(T_SnapSetRepoAttr *ptSvolThr);

/**********************************************************************
* 功能描述：创建拷贝卷
* 输入参数：
* 输出参数： 无
* 返回值：    0   - SUCCESS    <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 CreateSnapPlan(T_SvolPlanCreate *ptSnapPlanCreate);

/**********************************************************************
* 功能描述：创建拷贝卷
* 输入参数：
* 输出参数： 无
* 返回值：    0   - SUCCESS    <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 DelSnapPlan(T_SvolPlanName *ptSnapPlanName);

/**********************************************************************
* 功能描述：创建拷贝卷
* 输入参数：
* 输出参数： 无
* 返回值：    0   - SUCCESS    <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 UpdateSnapPlan(T_SvolPlanUpdate *ptSnapPlanUpdate);

/**********************************************************************
* 功能描述：创建拷贝卷
* 输入参数：
* 输出参数： 无
* 返回值：    0   - SUCCESS    <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetSnapPlanList(T_SvolPlanList *ptSnapPlanInfo);

/**********************************************************************
* 功能描述：创建拷贝卷
* 输入参数：
* 输出参数： 无
* 返回值：    0   - SUCCESS    <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetSnapPlanInfo(T_SvolPlanInfo *ptSnapPlanInfo);

/**********************************************************************
* 功能描述：创建拷贝卷
* 输入参数：
* 输出参数： 无
* 返回值：    0   - SUCCESS    <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 CreateCvol(T_CreateCvol  *ptCreateCvol);

/**********************************************************************
* 功能描述： 获取拷贝卷信息
* 输入参数：
* 输出参数： 无
* 返回值：    0   - SUCCESS    <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetCvolInfo(T_CvolInfo *ptCvolInfo);
/**********************************************************************
* 功能描述： 获取拷贝卷信息
* 输入参数：
* 输出参数： 无
* 返回值：    0   - SUCCESS    <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetAllCvolInfo(T_AllCvolInfo *ptAllCvolInfo);

/**********************************************************************
* 功能描述： 获取源卷上的拷贝卷信息
* 输入参数：
* 输出参数： 无
* 返回值：    0   - SUCCESS    <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetCvolNamesOnVol(T_CvolNamesOnVol *ptCvolNamesOnVol) ;

/**********************************************************************
* 功能描述： 设置拷贝卷同步或者反同步的优先级
* 输入参数：
* 输出参数： 无
* 返回值：    0   - SUCCESS    <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetCvolPriority(T_CvolPriority *ptCvolPriority);

/**********************************************************************
* 功能描述：  设置克隆卷策略
* 输入参数：
* 输出参数：
* 返 回 值：  0      -   执行成功     非0 - 执行失败
* 其它说明：无
***********************************************************************/
SWORD32 SetCvolPolicy(T_CvolPolicy *ptCvolPolicy);

/**********************************************************************
* 功能描述： 设置是否启动保护拷贝
* 输入参数：
* 输出参数： 无
* 返回值：    0   - SUCCESS    <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetCvolProtect(T_CvolProtect *ptCvolProtect);

/**********************************************************************
* 功能描述：删除拷贝卷
* 输入参数：
* 输出参数： 无
* 返回值：    0   - SUCCESS    <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 DelCvol(T_CvolName *ptCvolName);
SWORD32 SyncForceDelCvol(T_CvolName *ptCvolName);
/**********************************************************************
* 功能描述： 分离拷贝卷
* 输入参数：
* 输出参数： 无
* 返回值：    0   - SUCCESS    <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 FractureCvol(T_CvolName  *ptCvolName);

/**********************************************************************
* 功能描述： 同步拷贝卷
* 输入参数：
* 输出参数： 无
* 返回值：    0   - SUCCESS    <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SyncCvol(T_CvolName *ptCvolName);

/**********************************************************************
* 功能描述：反同步拷贝卷
* 输入参数：
* 输出参数： 无
* 返回值：    0   - SUCCESS    <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 ReverseSyncCvol(T_CvolName *ptCvolName);

/**********************************************************************
* 功能描述： 重命名拷贝卷
* 输入参数： 全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 RenameCvol(T_CvolRename *ptCvolRename);

/**********************************************************************
* 功能描述：获取系统中未被映射的卷对象(包括普通卷/快照/拷贝卷)信息
* 输入参数：
* 输出参数： 无
* 返回值：    0   - SUCCESS    <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetVolUnmappedInfo(T_VolObjectInfoList *ptVolObjectInfoList);

/**********************************************************************
* 功能描述：开始vol校验
* 输入参数：所有参数
* 输出参数：无
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 VerifyVol(T_VolVerify *ptVerifyVol);
/**********************************************************************
* 功能描述：取消vol校验
* 输入参数：cVolName
* 输出参数：无
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 CancelVolVerify(T_VolName *ptVolName);
/**********************************************************************
* 功能描述：卷校验信息查询
* 输入参数：cVolName
* 输出参数：其他参数均为出参
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 ShowVolVerifyInfo(T_VolVerifyInfo *ptVolVerifyInfo);
/**********************************************************************
* 功能描述：对当前控制器上的所有的卷进行IO 路径切换
* 输入参数：无
* 输出参数：无
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 SwitchAllVolOwnerCtrl(T_SwitchAllVolIoPath *tSwitchInfo);
/**********************************************************************
* 功能描述：回滚控制器上所有卷路径至优选控制器
* 输入参数：无
* 输出参数：无
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 RestoreAllVolPreferOwner(void);

/**********************************************************************
* 功能描述： 修改VOL的Cache属性
* 输入参数： ptLunCacheInfo->sdwLunGlbId
* 输出参数： 其他为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetVolCacheAttr(T_VolCacheInfo *ptVolCacheInfo);

/**********************************************************************
* 功能描述： 创建远程镜像
* 输入参数： ptCreateMirror
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 CreateMirror(T_CreateMirror *ptCreateMirror);

/**********************************************************************
* 功能描述： 删除远程镜像
* 输入参数： ptMirrorName
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 DeleteMirror(T_MirrorName *ptMirrorName);

/**********************************************************************
* 功能描述： 显示远程镜像信息
* 输入参数： 无
* 输出参数： ptMirrorInfo
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetMirrorInfo(T_MirrorInfo *ptMirrorInfo);

/**********************************************************************
* 功能描述： 获取所有镜像名称列表
* 输入参数： 无
* 输出参数： ptAllMirrorNames
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetAllMirrorNames(T_AllMirrorList *ptAllMirrorList);

/**********************************************************************
* 功能描述： 修改远程镜像名称
* 输入参数： ptMirrorRename
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetMirrorName(T_MirrorRename *ptMirrorRename);

/**********************************************************************
* 功能描述： 修改远程镜像恢复策略
* 输入参数： ptMirrorPolicy
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetMirrorPolicy(T_MirrorPolicy *ptMirrorPolicy);

/**********************************************************************
* 功能描述： 修改远程镜像同步优先级
* 输入参数： ptMirrorPriority
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetMirrorPriority(T_MirrorPriority *ptMirrorPriority);

/**********************************************************************
* 功能描述： 启动同步远程镜像
* 输入参数： ptMirrorName
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 StartMirrorSync(T_MirrorName *ptMirrorName);

/**********************************************************************
* 功能描述： 启动增量同步远程镜像
* 输入参数： ptMirrorName
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 StartMirrorIncSync(T_MirrorName *ptMirrorName);

/**********************************************************************
* 功能描述：分离远程镜像
* 输入参数：
* 输出参数：
* 返 回 值：  0      -   执行成功    非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 FractureMirror(T_MirrorName *ptMirrorName);

/**********************************************************************
* 函数名称：GetAllPriVolList
* 输入参数：
* 输出参数：
* 返 回 值：  0      -   执行成功    非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetAllPriVolList(T_PriVolList *ptPriVolList);

/**********************************************************************
* 函数名称：GetPriVolInfo
* 输入参数：
* 输出参数：
* 返 回 值：  0      -   执行成功    非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetPriVolInfo(T_PriVolInfo *ptPriVolInfo);

/**********************************************************************
* 函数名称：DelPriVol
* 输入参数：
* 输出参数：
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 DelPriVol(T_DelPriVol *ptDelPriVol);

/**********************************************************************
* 功能描述： 设置镜像逻辑连接
* 输入参数： ptMirrorConnectInfo
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetFcMirrorConnect(T_FcMirrorConnectInfo *ptFcMirrorConnectInfo);

/**********************************************************************
* 功能描述： 删除镜像逻辑连接
* 输入参数： ptFcMirrorConnectInfo
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 DeleteFcMirrorConnect(T_FcMirrorConnectInfo *ptFcMirrorConnectInfo);

/**********************************************************************
* 功能描述： 查询所有镜像链接
* 输入参数： 无
* 输出参数： ptMirrorConnectList
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetAllMirrorConnect(T_MirrorConnectList *ptMirrorConnectList);

/**********************************************************************
* 功能描述： 查询所有目的卷信息
* 输入参数： 无
* 输出参数： ptRemoteDiskList
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetAllRemoteDiskInfo(T_RemoteDiskList *ptRemoteDiskList);

/**********************************************************************
* 功能描述： 刷新远端磁盘
* 输入参数： 无
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 RefreshRemoteDisk(void);
/**********************************************************************
* 功能描述： 创建远程复制
* 输入参数： T_CreateReCopy
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 CreateReCopy(T_CreateReCopy *ptCreateReCopy);
/**********************************************************************
* 功能描述： 删除远程复制
* 输入参数： T_ReCopyName
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 DelReCopy(T_ReCopyName *ptReCopyName);
/**********************************************************************
* 功能描述：显示远程复制信息
* 输入参数：cReCopyName
* 输出参数：其他参数
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetReCopyInfo(T_ReCopyInfo *ptRCopyInfo);
/**********************************************************************
* 功能描述：获取所有远程复制名称列表
* 输入参数：
* 输出参数：T_AllRCopyList
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetAllRCopyNames(T_AllRCopyList *ptAllRCopyList);
/**********************************************************************
* 功能描述：修改远程复制名称
* 输入参数：T_RCopyRename
* 输出参数：
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 SetRCopyName(T_RCopyRename *ptRCopyRename);
/**********************************************************************
* 功能描述：修改远程复制速率
* 输入参数：T_RCopySyncSpeed
* 输出参数：
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 SetRCopySpeed(T_RCopySyncSpeed *ptRCopySpeed);
/**********************************************************************
* 功能描述：修改远程复制同步策略
* 输入参数：T_RCopyPolicy
* 输出参数：
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 SetRCopyPolicy(T_RCopyPolicy *ptRCopyPolicy);
/**********************************************************************
* 功能描述：修改远程复制类型
* 输入参数：T_RCopyType
* 输出参数：
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 SetRCopyType(T_RCopyType *ptRCopyType);
/**********************************************************************
* 功能描述：发起远程复制同步任务
* 输入参数：cReCopyName
* 输出参数：无
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 StartReCopySync(T_ReCopyName *ptReCopyName);
/**********************************************************************
* 功能描述：远程复制添加目标卷
* 输入参数：T_RCopyDestVol
* 输出参数：
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 AddReCopyDestVol(T_RCopyDestVol *ptAddRCopyDestVol);
/**********************************************************************
* 功能描述：远程复制删除目标卷
* 输入参数：T_RCopyDestVol
* 输出参数：
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 DelReCopyDestVol(T_RCopyDestVol *ptDelRCopyDestVol);
/**********************************************************************
* 功能描述：远程复制设置标记
* 输入参数：T_ReCopyName
* 输出参数：无
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：用户发起这个操作之后，前台会创建一个私有快照。等发起同步的时候，用这个快照中的内容发起同步
***********************************************************************/
SWORD32 SetReCopyFlag(T_ReCopyName *ptReCopyName);
/**********************************************************************
* 功能描述：查询一个远程复制下有多少个目标卷及信息
* 输入参数：scRCopyName
* 输出参数：其他参数
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetDestLunByRCopy(T_DestVolInRCopy *ptDestVolInRCopy);
/**********************************************************************
* 功能描述：添加远端设备
* 输入参数：udwCtrlId  udwFirmType aRmtTgtName  cIpAddr
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 AddRemoteTarget(T_RmtTgtInfo *ptRmtTgtNetInfo);

/**********************************************************************
* 功能描述：删除远端设备
* 输入参数： udwCtrlId  , aRmtTgtName
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 DelRemoteTarget(T_RmtTgtInfo *ptRmtTgtNetInfo);

/**********************************************************************
* 功能描述： 获取远端设备列表
* 输入参数： 无
* 输出参数： ptRmtTgtInfo
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetRemoteTargetList(T_RmtTgtList *ptRmtTgtInfo);

/**********************************************************************
* 功能描述：  添加远端设备的链接
* 输入参数：sdwCtrlId  aRmtTgtName udwLinkType
*                            udwLinkType = 1(REMOTE_TARGET_FC)时的其他入参:ucWWPN
*                            udwLinkType = 2(REMOTE_TARGET_FC)时的其他入参:acIpAddr,acStatryChap
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 AddRmtTgtLink(T_RmtTgtLinkInfo *ptRmtTgtLink);

/**********************************************************************
* 功能描述：删除连接
* 输入参数：sdwCtrlId  aRmtTgtName udwLinkType
*                            udwLinkType = 1(REMOTE_TARGET_FC)时的其他入参:ucWWPN
*                            udwLinkType = 2(REMOTE_TARGET_FC)时的其他入参:acIpAddr
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 DelRmtTgtLink(T_RmtTgtLinkInfo *ptRmtTgtNetInfo);

/**********************************************************************
* 功能描述：获取指定设备上的链路列表
* 输入参数： ptRmtTgtLinkInfo->aRmtTgtName
* 输出参数：结构体 其他字段为出参(acTargetIQN这个字段目前不用)
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetRmtTgtLinkList(T_RmtLinkInDevInfo *ptRmtTgtLinkInfo);

/**********************************************************************
* 功能描述：获取指定设备上的链路列表
* 输入参数： ptRmtDiskListOnLink->sdwCtrlId,udwLinkType,acIpAddr,ucWWPN
* 输出参数：结构体 其他字段为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetRmtDiskListOnLink(T_RmtDiskListOnLink *ptRmtDiskListOnLink);

/**********************************************************************
* 功能描述：修改指定设备上的一条链路
* 输入参数：iscsi方式时入参: ptRmtTgtLink->sdwCtrlId,aRmtTgtName, udwLinkType, sdwModyFlag, qwBandWidth,acIpAddr,acStatryChap,
*                            FC方式时入参: ptRmtTgtLink->sdwCtrlId,aRmtTgtName, udwLinkType,ucWWPN,
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 ModyRmtTgtLink(T_RmtTgtLinkInfo *ptRmtTgtLink);

/**********************************************************************
* 功能描述： 查询FC 端口信息
* 输入参数： 无
* 输出参数： ptFcPortInfoList
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetFcPortInfo(T_FcPortInfoList *ptFcPortInfoList);

/**********************************************************************
* 功能描述：获取控制器上，FC子卡所在槽位信息列表
* 访问的表：
* 修改的表：
* 输入参数：
* 输出参数：
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetFcPortList(T_FcPortList *ptFcPortList);

/**********************************************************************
* 功能描述： 查询FC 主机端口信息
* 输入参数： 无
* 输出参数： ptFcPortInfoList
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetFcHostPortList(T_FcHostPortList *ptFcHostPortList);

/**********************************************************************
* 功能描述： 创建映射组
* 输入参数： sdwMapGrpId
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 CreateMapGrp(T_MapGrpName *ptMapGrpName);

/**********************************************************************
* 功能描述： 删除映射组
* 输入参数： sdwMapGrpId
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 DelMapGrp(T_MapGrpName *ptMapGrpName);

/**********************************************************************
* 功能描述： 重命令映射组
* 输入参数： sdwMapGrpId
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 RenameMapGrp(T_MapGrpRename *ptMapGrpRename);

/**********************************************************************
* 功能描述： 获取映射组信息
* 输入参数： ptMapGrpInfo
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetMapGrpInfo(T_MapGrpInfo *ptMapGrpInfo);

/**********************************************************************
* 功能描述： VOL加入映射组
* 输入参数： 全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 AddVolToGrp(T_AddVolToGrp *ptAddVolToGrp);
/**********************************************************************
* 功能描述： VOL从映射组中删除
* 输入参数： 全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 DelVolFromGrp(T_DelVolFrmGrp *ptDelVolFromGrp);
/**********************************************************************
* 功能描述： Host加入映射组
* 输入参数： 全部为入参
* 输出参数：  无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 AddHostToGrp(T_HostInGrp *ptHostInGrp);
/**********************************************************************
* 功能描述： Host从映射组中删除
* 输入参数：  全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 DelHostFromGrp(T_HostInGrp *ptHostInGrp);
/**********************************************************************
* 功能描述： 查询所有映射组ID列表
* 输入参数： 无
* 输出参数： 全部为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetGrpNamesList(T_AllGrpNames *ptAllGrpNames);

/**********************************************************************
* 功能描述： 查询所有映射组简要信息
* 输入参数： 无
* 输出参数： 全部为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetGrpSimpleInfoList(T_AllGrpSimpleInfo *ptAllGrpSimpleInfo);

/**********************************************************************
* 功能描述： 查询指定host所在映射组名称
* 输入参数： ptHostGrpId->ucInitName
* 输出参数： 其他为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetGrpNameOfHost(T_HostInGrp *ptHostInGrp);
/**********************************************************************
* 功能描述： 查询VOL所在的映射组列表
* 输入参数： ptLunGrpId->sdwLunGlbId
* 输出参数： 其他为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetGrpNamesOfVol(T_GrpNameByVol *ptGrpNameByVol);
/**********************************************************************
* 功能描述： 打开/关闭映射组内Lun的IO统计开关
* 输入参数： 全部为入参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 输出参数： 无
* 其它说明：
***********************************************************************/
SWORD32 SetLunIOStaticSwitchStatus(T_LunIOStaticSwitch *ptVolIOStaticSwitch);
/**********************************************************************
* 功能描述： 查询映射组内Lun的IO统计开关状态
* 输入参数： 全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetLunIOStaticSwitchStatus(T_LunIOStaticSwitch *ptVolIOStaticSwitch);
/**********************************************************************
* 功能描述： 获取映射组内Lun的IO统计数据
* 输入参数：ptLunIoStaticData->sdwLunLocalId,ptLunIoStaticData->ucInitName
* 输出参数：其他为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetLunIOStaticData(T_LunIOStaticData *ptVolIoStaticData);

/***************************************Cache***********************************/
/**********************************************************************
* 功能描述： 设置cache全局配置
* 输入参数： 全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetCacheGlobalPolicy(T_SetCacheGlbPolicy *ptSetCacheGlbPolicy);
/**********************************************************************
* 功能描述： 获取cache全局配置
* 输入参数： 无
* 输出参数： 全部为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetCacheGlobalPolicy(T_GetCacheGlbPolicy *ptGetCacheGlbPolicy);
/**********************************************************************
* 功能描述： 获取buffer的使用信息，
* 输入参数： 无
* 输出参数： 全部为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetCacheBuffInfo(T_CacheBuffInfo *ptCacheBuffInfo);
/**********************************************************************
* 功能描述： 获得统计开关的状态
* 输入参数： 无
* 输出参数：sdwSwitch
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetCacheStatSwitchStaus(T_CacheIOStatSwitch *ptCacheIOStatSwitch);
/**********************************************************************
* 功能描述： 设置统计开关
* 输入参数： sdwSwitch
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetCacheStatSwitchStaus(T_CacheIOStatSwitch *ptCacheIOStatSwitch);
/**********************************************************************
* 功能描述： 获取IO统计信息，包括读写命令个数，大小，命中率
* 输入参数： 无
* 输出参数： 全部为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetCacheStatData(T_CacheIOStatData *ptCacheIOStatData);

/***************************************Other***********************************/
/**********************************************************************
* 功能描述： 获取所有封装ID
* 输入参数： 无
* 输出参数： 全部为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetAllEncId(T_AllEncId *ptAllEncId);

/* SWORD32 GetCtlHwInfo();*/
/**********************************************************************
* 功能描述： 扩展柜版本更新
* 输入参数： *ptUpdateFirmware
* 输出参数： 无
* 其它说明：
***********************************************************************/
SWORD32 UpdateFirmware(T_UpdateFirmware *ptUpdateFirmware);
/**********************************************************************
* 功能描述： 扩展柜版本查询
* 输入参数： 无
* 输出参数： *ptFirmwareVer
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetFirmwareVer(T_FirmwareVersion *ptFirmwareVer);

/**********************************************************************
* 功能描述：  查询版本信息
* 输入参数：
* 输出参数：  ptVer 版本信息
* 返 回 值：  0      -   执行成功
*             非0 - 执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetVerList(T_VerList *ptVer);

/**********************************************************************
* 功能描述： VPD信息查询
* 输入参数： 无
* 输出参数： *ptVpd
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetVpd(T_VPD *ptVpd);
/**********************************************************************
* 功能描述： 重启控制器
* 输入参数： 全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 RestartCtrl(T_CtrlAction *ptCtrlAction);
/**********************************************************************
* 功能描述： 关闭控制器
* 输入参数： 全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 ShutdownCtrl(T_CtrlAction *ptCtrlAction);
/**********************************************************************
* 功能描述： 软关机
* 输入参数： 全部为入参
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GraceShutdown(void);

/**********************************************************************
* 功能描述： 获取当前控制器ID
* 输入参数： 无
* 输出参数：*sdwCtlId
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetLocalCtlId(SWORD32 *sdwCtlId);
/**********************************************************************
* 功能描述： 获取当前控制器状态
* 输入参数： 无
* 输出参数： *LocalCtrlState
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetLocalCtrlState(SWORD32 *LocalCtrlState);
/**********************************************************************
* 功能描述： 获取对端控制器状态
* 输入参数： 无
* 输出参数： *PeerCtlState
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetPeerCtlState(SWORD32 *PeerCtlState);
/**********************************************************************
* 功能描述： 获取当前控制器角色
* 输入参数： 无
* 输出参数： *LocalCtlRole
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetLocalCtlRole(SWORD32 *LocalCtlRole);

/**********************************************************************
* 功能描述： 将配置保存为指定类型文件
* 输入参数： *ptConfigFile
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SaveConfigFile(T_ConfigFile *ptConfigFile);

/**********************************************************************
* 功能描述： 将系统信息包保存在指定路径
* 输入参数： *ptConfigFile
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SaveSysInfoTarBall(T_SysInfoTarBall *ptSysInfoTarBall);

/**********************************************************************
* 功能描述： 恢复指定文件配置
* 输入参数： *ptConfigFile
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 RestoreConfigFile(T_ConfigFile *ptConfigFile);

/**********************************************************************
* 功能描述： 恢复出厂配置
* 输入参数： 无
* 输出参数： 无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 RestoreOriginalConfig(void);

/**********************************************************************
* 功能描述：获取所有箱体信息
* 输入参数：控制器标志--sdwCtrlFlg
* 输出参数：控制器数目--sdwCtrlNum, 诊断信息记录--tEncInfoList[2]
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetDiagAllEncInfoList(T_AllEncInfoList *ptAllEncInfoList);

/**********************************************************************
* 函数名称：GetBbuInfo
* 功能描述：获取BBU信息
* 输入参数：sdwCtrlFlg
* 输出参数：其他
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/8/16       V1.0       王京         初次创建
***********************************************************************/
SWORD32 GetBbuInfo(T_BbuInfo *ptBbuInfo);
/**********************************************************************
* 功能描述： 获得整板的诊断信息
* 输入参数： 诊断对象类型diagDeviceType，诊断发起者DiagSourceType
* 输出参数： 其它为出参
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetDiagDeviceInfo(T_DiagDeviceInfo *ptDiagDeviceInfo);

/**********************************************************************
* 函数名称：scsSetDiagEccSwitch
* 功能描述：
* 访问的表：
* 修改的表：
* 输入参数：
* 输出参数：
* 返 回 值：  0      -   执行成功
*                              非0 - 执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/11/28              V1.0              wangwei             初次创建
***********************************************************************/
SWORD32 scsSetDiagEccSwitch(T_DiagEccSwitch *ptDiagEccSwitch);

/**********************************************************************
* 功能描述： 获得BBU电源诊断信息
* 输入参数：无
* 输出参数： 全部
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetDiagBbuInfo(T_DiagBatteryInfo *ptDiagbatteryInfo);

/**********************************************************************
* 功能描述： 获得EPLD诊断信息
* 输入参数：无
* 输出参数： 全部
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetDiagEpldInfo(T_DiagEpldInfo *ptDiagEpldInfo);

/**********************************************************************
* 功能描述： 获得Rtc设备诊断信息
* 输入参数：无
* 输出参数： 全部
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetDiagRtcInfo(T_DiagRtcInfo *ptDiagRtcInfo);

/**********************************************************************
* 功能描述： 获得Crystal设备诊断信息
* 输入参数：无
* 输出参数： 全部
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetDiagCrystalInfo(T_DiagCrystalInfo *ptDiagCrystalInfo);

/**********************************************************************
* 功能描述：获取诊断设备记录
* 输入参数：控制器标志--sdwCtrlFlg, 诊断器件ID--sdwDiagDeviceId
* 输出参数：诊断对象数目--sdwDeviceNum, 诊断对象记录--tDiagSingleDeviceRecord[2]
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetDiagDeviceRecord(T_DiagDeviceRecord *ptDiagDeviceRecord);

/**********************************************************************
* 功能描述：获取PM8001诊断信息
* 输入参数：控制器标志--sdwCtrlFlg
* 输出参数：诊断PM8001数目--sdwPmNum, 诊断信息列表--tDiagSinglePmInfo[2]
* 返 回 值：  0 - 执行成功
*           非0 - 执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetDiagPmInfo(T_DiagPmInfo *ptDiagPmInfo);

/**********************************************************************
* 功能描述：获取PCIE诊断信息
* 输入参数：控制器标志--sdwCtrlFlg
* 输出参数：诊断PCIE数目--sdwPcieNum, 诊断信息列表--tDiagSinglePcieInfo[2]
* 返 回 值：  0 - 执行成功
*           非0 - 执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetDiagPcieInfo(T_DiagPcieInfo *ptDiagPcieInfo);

/**********************************************************************
* 功能描述：获取扩展柜诊断信息
* 输入参数：无
* 输出参数：诊断信息列表-- tExpanderInfo[MAX_UP_SUB_ENCL]
* 返 回 值：  0 - 执行成功
*           非0 - 执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetDiagExpanderInfoList(T_ExpanderInfoList *ptExpanderInfoList);

/**********************************************************************
* 功能描述：获取整板状态信息
* 输入参数：控制器标志--sdwCtrlFlg
* 输出参数：整板数目--sdwBoardNum, 诊断信息列表--tDiagSingleBoardStatus[2]
* 返 回 值：  0 - 执行成功
*           非0 - 执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetDiagBoardStatus(T_DiagBoardStatus *ptDiagBoardStatus);

/**********************************************************************
* 功能描述：获取磁盘状态信息
* 输入参数：无
* 输出参数：诊断磁盘数目--sdwHddNum
*           诊断信息列表--tDiagSingleHddStatus[MAX_PD_NUM_IN_SYS]
* 返 回 值：  0 - 执行成功
*           非0 - 执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetDiagHddStatus(T_DiagHddStatus *ptDiagHddStatus);

/**********************************************************************
* 功能描述：获取GE端口状态信息
* 输入参数：无
* 返 回 值：  0 - 执行成功
*           非0 - 执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetDiagGeInfo(T_DiagGeInfo *tDiagGeInfo);

/**********************************************************************
* 功能描述： 获得锁相环(时钟相关)诊断信息
* 输入参数：无
* 输出参数： 全部
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetDiagClockInfo(T_DiagClockInfo *ptDiagClockInfo);

/**********************************************************************
* 功能描述： 获得EEPROM诊断信息
* 输入参数：无
* 输出参数： 全部
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetDiagEepromInfo(T_DiagEepromInfo *ptDiagEepromInfo);

/**********************************************************************
* 功能描述： 获得IMBC诊断信息
* 输入参数：无
* 输出参数： 全部
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetDiagIbmcInfo(T_DiagIbmcInfo *ptDiagIbmcInfo);

/**********************************************************************
* 功能描述：根据targetId ,获取Initiator信息列表
* 输入参数：targetId
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetIscsiInitList(T_IscsiIniInfoList *ptIscsiIniInfoList);

/**********************************************************************
* 功能描述：根据targetId ,获取所有Session 信息列表
* 输入参数：targetId
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetIscsiAllSessInfoList(T_IscsiSessInfoDualList *ptIscsiSessList);
SWORD32 GetIscsiAllSessNum(T_GetIscsiSessNum *ptIscsiAllSessNum);
SWORD32 GetIscsiSessOnceInfo(T_IscsiSessGetOnceInfo *ptIscsiSssGetOnceInfo);
SWORD32 GetIscsiAllHistorySessNum(T_GetIscsiSessNum *ptIscsiAllHisySessNum);
SWORD32 GetIscsiHisSessOnceInfo(T_IscsiSessGetOnceInfo *ptIscsiSssGetOnceInfo);

SWORD32 GetIscsiPduStatisticsInfo(T_IscsiAllPduStatisticInfo  *ptIscsiPduList);
SWORD32 GetFcGpnOnceInfo(T_GetOnceFcGpnInfo *ptFcGpnGetOnceInfo);
/**********************************************************************
* 功能描述： 修改双向chap配置
* 输入参数：无
* 输出参数：udwMulChapCount
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32  GetIscsiMulChapNum(T_GetIscsiMulChapNum *ptChapInfoNum);

/**********************************************************************
* 功能描述： 一次获取iscsi的双向chap配置的信息
* 输入参数：udwMulChapCount和udwMulChapBgnIndex
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetIscsiMulChapInfoOnce(T_IscsiMulChapGetOnceInfo *ptGetChapInfOnce);

/**********************************************************************
* 功能描述： 添加单向chap配置
* 输入参数：acname和acpass
* 输出参数：无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32  AddIscsiStationaryChap(T_IscsiChapAuthInf   *ChapInfo);

/**********************************************************************
* 功能描述： 删除chap单向配置
* 输入参数：无
* 输出参数：无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 DelIscsiStationatyChap(void);

/**********************************************************************
* 功能描述： 获取单向chap配置
* 输入参数：无
* 输出参数：acname和acpass
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetIscsiStationaryChap(T_IscsiChapAuthInf   *ChapInfo);

/**********************************************************************
* 功能描述： 添加chap双向配置
* 输入参数：acname和acpass
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32  AddIscsiMulChap(T_IscsiChapAuthInf   *ChapInfo);
/**********************************************************************
* 功能描述： 设置单向chap配置
* 输入参数：acpass
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32  SetIscsiStationaryChap(T_IscsiChapAuthInf  *ChapInfo);
/**********************************************************************
* 功能描述： 设置单向chap的开关状态
* 输入参数：udwStationaryChapSwitch
* 输出参数：无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32  SetIscsiStationaryChapSwitch(WORD32 *udwStationaryChapSwitch);
/**********************************************************************
* 功能描述： 获取单向chap的开关状态
* 输入参数：无
* 输出参数：udwStationaryChapSwitch
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32  GetIscsiStationaryChapSwitch(WORD32 *udwStationaryChapSwitch);

/**********************************************************************
* 功能描述： 删除chap双向配置
* 输入参数：acname
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32  DelIscsiMulChap(T_IscsiChapAuthInf *ptMultualChapInfo);

/**********************************************************************
* 功能描述： 修改双向chap配置
* 输入参数: T_iSCSIChapInfo 包含配置需要输入的scName和scPass
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32  SetIscsiMulChap(T_IscsiChapAuthInf   *ChapInfo);

/**********************************************************************
* 功能描述： 一次删除所有双向chap配置
* 输入参数：无
* 输出参数：无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32  DelAllIscsiMulChap(void);

/**********************************************************************
* 功能描述：根据targetId ,获取所有Session 信息列表
* 输入参数：targetId
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetIscsiHistorySessInfoList(T_IscsiSessInfoDualList *ptIscsiHistorySessList);

/**********************************************************************
* 功能描述：根据Session Id ,获取所有Session属性信息
* 输入参数：Session Id
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetIscsiSessionAttr(T_GetIscsiSessAttrInfo *ptIscsiSessAttr);

/**********************************************************************
* 功能描述：根据targetId,统计指定端口/所有端口的流量信息
* 输入参数：targetId、Port Id
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetIscsiFlowInfoStat(T_IscsiFlowStatInfo *ptIscsiPortStatInfo);

/**********************************************************************
* 功能描述：根据targetId,获取Target Name
* 输入参数：targetId
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetIscsiTargetName(T_IscsiTargetList *ptIscsiTgtInfo);

/**********************************************************************
* 功能描述：根据targetId,获取流量统计开关状态
* 输入参数：targetId
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetIscsiFlowStatSwitchStatus(T_IscsiFlowStatFlag *ptIscsiTgtInfo);

/**********************************************************************
* 功能描述：根据targetId,设置流量统计开关状态
* 输入参数：targetId
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetIscsiFlowStatSwitchStatus(T_IscsiFlowStatFlag *ptIscsiTgtInfo);

/**********************************************************************
* 功能描述：根据targetId, 获取端口信息列表
* 输入参数：targetId
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetIscsiPortInfoList(T_IscsiNetPortalList *ptIscsiPortInfo);

/**********************************************************************
* 功能描述：获取扩展柜类型
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetEnclosureType(T_EnclosureType *ptEnclosureTyp);

/**********************************************************************
* 功能描述：获取Expander拓扑结构信息列表
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetExpanderTopoList(T_EncTopoInfoList *ptEncTopoInfoList);

/**********************************************************************
* 功能描述：诊断Expander设备列表
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 DiagExpanderList(T_EncDeviceInfoList *ptEncDevInfoList);

/**********************************************************************
* 功能描述：配置系统网络相关的信息
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetSystemNetCfg(T_SystemNetCfg *ptSystemNetCfg);

/**********************************************************************
* 功能描述：查询系统网络相关的信息
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetSystemNetCfg(T_SystemNetCfgList *ptSystemNetCfgList);

/**********************************************************************
* 功能描述：删除管理口的默认网关
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 DeleteDefaultGateway(T_CtrlId *ptCtrlId);

/**********************************************************************
* 功能描述：设置Iscsi 端口Mac 地址
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetIscsiPortMac(T_IscsiPortMac *ptIscsiPortMac);

/**********************************************************************
* 功能描述：查询Iscsi 端口Mac 地址列表
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetIscsiPortMac(T_IscsiPortMacList *ptIscsiPortMacList);

/**********************************************************************
* 功能描述：设置Iscsi 端口信息
* 输入参数：控制器ID、端口号、MAC、MTU
* 输出参数：无
* 返回值：    0   - SUCCESS   < 0     -  FAILURE
* 其它说明：该设置包括端口MAC、MTU,可以二者同时设置，也可设置其一
***********************************************************************/
SWORD32 SetIscsiPortInfo(T_IscsiPortSet *ptIscsiPortSet);

/**********************************************************************
* 功能描述：查询Iscsi 端口信息列表
* 输入参数：无
* 输出参数：全部为出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：该信息包括端口MAC、MTU、端口状态信息
***********************************************************************/
SWORD32 GetIscsiPortInfo(T_IscsiPortInfoList *ptIscsiPortInfoList);

/**********************************************************************
* 功能描述： 查询管理口端口信息列表
* 输入参数：无
* 输出参数：全部
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 GetManaPortInfo(T_ManaPortInfoList *ptManaPortInfoList);

/**********************************************************************
* 功能描述：添加Iscsi 端口路由信息
* 输入参数：目标IP、掩码、下一跳IP
* 输出参数：无
* 返回值：    0   - SUCCESS   <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 AddIscsiPortRoute(T_IscsiRouteInfo *ptIscsiRouteInfo);

/**********************************************************************
* 功能描述：删除Iscsi 端口路由信息
* 输入参数：控制器ID、目标IP、掩码
* 输出参数：无
* 返回值：    0   - SUCCESS   <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 DelIscsiPortRoute(T_IscsiPortRouteDel *ptIscsiPortRouteDel);

/**********************************************************************
* 功能描述：查询Iscsi 端口路由信息
* 输入参数：无
* 输出参数：路由数据、路由信息列表
* 返回值：    0   - SUCCESS   <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetIscsiPortRoute(T_IscsiPortRouteList *ptIscsiPortRouteList);

/**********************************************************************
* 功能描述：删除FCoE端口的VLAN信息
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 DelFCoEPortVlan(T_FCoEPortInfo *ptFCoEPortInfo);

/**********************************************************************
* 功能描述：设置FCoE端口的VLAN信息
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetFCoEPortVlan(T_FCoEPortVlanInfo *ptFCoEPortVlanInfo);

/**********************************************************************
* 功能描述：查询系统中所有FCoE端口的VLAN信息
* 输入参数：无
* 输出参数：
* 返回值：    0   - SUCCESS   <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetFCoEPortInfoList(T_FCoEPortVlanInfoList *ptFCoEPortVlanInfoList);

/**********************************************************************
* 功能描述：Iscsi 端口ping 功能
* 输入参数：目标IP
* 输出参数：
* 返回值：    0   - SUCCESS   <0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 GetPingInfo(T_IscsiPingInfo *ptIscsiPingInfo);

/**********************************************************************
* 功能描述：修改Iscsi Name
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 SetIscsiName(T_SetIscsiName *ptSetIscsiName);

/**********************************************************************
* 功能描述：重启Iscsi服务
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：
***********************************************************************/
SWORD32 RestartIscsiService(SWORD32 *psdwCtrlId);

/**********************************************************************
* 函数名称： CreateBond
* 功能描述： 创建bond
* 输入参数： 控制器ID、Bond名称、端口信息列表
* 输出参数： 无
* 返 回 值： 0  -   成功  非0  -  失败
* 其它说明：
***********************************************************************/
SWORD32 CreateBond(T_BondCreate *ptBondCreate);

/**********************************************************************
* 函数名称：DeleteBond
* 功能描述：删除bond
* 输入参数：控制器ID、Bond名称
* 输出参数： 无
* 返 回 值： 0  -   成功  非0  -  失败
* 其它说明：
***********************************************************************/
SWORD32 DeleteBond(T_BondName *ptBondName);

/**********************************************************************
* 函数名称： GetBondInfoList
* 功能描述： 查询bond信息
* 输入参数： bond信息列表
* 输出参数： 无
* 返 回 值： 0  -   成功  非0  -  失败
* 其它说明：
***********************************************************************/
SWORD32 GetBondInfoList(T_BondInfoList *ptBondInfoList);

/**********************************************************************
* 函数名称： AddPortToBond
* 功能描述： 增加端口到bond中
* 输入参数： 控制器ID、bond名称、端口信息
* 输出参数： 无
* 返 回 值： 0  -   成功  非0  -  失败
* 其它说明：
***********************************************************************/
SWORD32 AddPortToBond(T_BondPortSet *ptBondPortSet);

/**********************************************************************
* 函数名称： RemovePortFromBond
* 功能描述： 从bond中移除端口
* 输入参数： 控制器ID、bond名称、端口信息
* 输出参数： 无
* 返 回 值： 0  -   成功  非0  -  失败
* 其它说明：
***********************************************************************/
SWORD32 RemovePortFromBond(T_BondPortSet *ptBondPortSet);

/**********************************************************************
* 函数名称： ModifyBondMode
* 功能描述： 修改bond模式
* 输入参数： 控制器ID、bond名称、策略信息
* 输出参数： 无
* 返 回 值： 0  -   成功  非0  -  失败
* 其它说明：
***********************************************************************/
SWORD32 ModifyBondMode(T_BondMode *ptBondMode);

/**********************************************************************
* 函数名称: ModifyBondPolicy
* 功能描述：修改bond报文分发策略
* 输入参数：控制器ID、bond名称、策略信息
* 输出参数： 无
* 返 回 值： 0  -   成功  非0  -  失败
* 其它说明：
***********************************************************************/
SWORD32 ModifyBondPolicy(T_BondPolicy *ptBondPolicy);

/**********************************************************************
* 函数名称： GetUsablePortForBond
* 功能描述： 查询单个控制器上可加入bond的端口列表
* 输入参数： 控制器ID
* 输出参数： 无
* 返 回 值： 0  -   成功  非0  -  失败
* 其它说明：
***********************************************************************/
SWORD32 GetUsablePortForBond(T_PortList *ptPortList);

/**********************************************************************
* 函数名称： GetUsableBondNameList
* 功能描述： 查询单个控制器上可用的bond名称列表
* 输入参数： 控制器ID
* 输出参数： 无
* 返 回 值： 0  -   成功  非0  -  失败
* 其它说明：
***********************************************************************/
SWORD32 GetUsableBondNameList(T_UsableBondNameList *ptUsableBondNameList);

/**********************************************************************
* 函数名称： GetUsableLunIdList
* 功能描述： 查询空闲的LunId名列表
* 输入参数： 映射组名字
* 输出参数： 可用的LunId列表
* 返 回 值： 0  -   成功  非0  -  失败
* 其它说明：
***********************************************************************/
SWORD32 GetUsableLunIdList(T_UsableLunIdList *ptUsableLunIdList);

/**********************************************************************
* 函数名称： SetBondIpAddr
* 功能描述： 设置Bond口IP、Mask
* 输入参数： 控制器ID、bond名称、IP信息
* 输出参数： 无
* 返 回 值： 0  -   成功  非0  -  失败
* 其它说明：
***********************************************************************/
SWORD32 SetBondIpAddr(T_BondNetInfo *ptBondNetInfo);

/**********************************************************************
* 函数名称： SetBondMtu
* 功能描述： 设置Bond口MTU
* 输入参数： 控制器ID、bond名称、MTU信息
* 输出参数： 无
* 返 回 值： 0  -   成功  非0  -  失败
* 其它说明：
***********************************************************************/
SWORD32 SetBondMtu(T_BondMtu *ptBondMtu);

/**********************************************************************
* 函数名称： SetBondMac
* 功能描述： 设置Bond口MAC
* 输入参数： 控制器ID、bond名称、MAC信息
* 输出参数： 无
* 返 回 值： 0  -   成功  非0  -  失败
* 其它说明：
***********************************************************************/
SWORD32 SetBondMac(T_BondMac *ptBondMac);

/**********************************************************************
* 功能描述： 获取版本目录剩余空间大小
* 输入参数： cFileName
* 输出参数： dwLocalFreeSize、dwPeerFreeSize
* 返 回 值： 0         -   空间够用
*            错误码    -   空间不够
* 其它说明：
***********************************************************************/
SWORD32 GetFreeSpace(T_VerFreeSpace *ptVerFreeSpace);
/**********************************************************************
* 函数名称： UpdatePreProcess
* 功能描述： 更新主柜版本前的预处理
* 输入参数： ucFileType
* 输出参数： 无
* 返 回 值： 0  -   成功  非0  -  失败
* 其它说明：
***********************************************************************/
SWORD32 UpdatePreProcess(WORD16 ucFileType);

/**********************************************************************
* 功能描述： 版本文件校验
* 输入参数： ptVerFileCheck
* 输出参数： 校验结果
* 返 回 值： 0      -   执行成功
*            非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 VerFileCheck(T_VerFileCheck *ptVerFileCheck);

/**********************************************************************
* 功能描述：上传文件预处理
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 UploadPreProcess(T_UploadPreInfo *ptUploadPreInfo);

/**********************************************************************
* 功能描述：上传文件后处理
* 输入参数：文件名、文件类型
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 UploadPostProcess(T_UploadPreInfo *ptUploadPreInfo);

/**********************************************************************
* 功能描述：通过Ftp 方式上传文件
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 UploadFileByFtp(T_UploadFileInfo *ptUploadFileInfo);

/**********************************************************************
* 函数名称： DownloadFileByFtp
* 功能描述： 将配置文件从FTP客户端传递到FTP服务器端
* 访问的表：
* 修改的表：
* 输入参数：
* 输出参数：
* 返 回 值：  0   - 执行成功
*             非0 - 执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2011/8/16       V1.0       陶林君             初次创建
***********************************************************************/
SWORD32 DownloadFileByFtp(T_DownloadFileInfo *ptUploadFileInfo);

/**********************************************************************
* 功能描述：获取文件上传进度
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/

SWORD32 GetFileUploadProgress(T_UploadFileProgress *ptUploadFileProgress);
/**********************************************************************
* 功能描述：获取文件下载进度
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 GetFileDownloadProgress(T_DownloadFileProgress *ptDownloadFileProgress);

/***************************************************************
* 功能描述：删除版本目录下同类型文件
* 输入参数：T_UploadFileName
* 输出参数：无
* 返 回 值: 0--成功；非0--失败
* 其他说明：
***************************************************************/
SWORD32 DelDuplicate(T_UploadFileName *ptFileName);

/**********************************************************************
* 功能描述：取消文件上传
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 CancelUploadFile(T_UploadFileName *ptFileName);
/**********************************************************************
* 功能描述：判断文件的存在性
* 输入参数：cFileName--文件名
* 输出参数：ucExistType---存在类型
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 IsFileDualExist(T_IsFileExist *ptIsFileExist);

/**********************************************************************
* 功能描述：  查询时区
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 GetTimeZone(T_TimeZoneInfo *ptTimeZoneInfo);

/**********************************************************************
* 功能描述：  设置时区
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 SetTimeZone(T_TimeZoneInfo *ptTimeZoneInfo);

/**********************************************************************
* 功能描述：  查询系统时间
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 GetSysTime(T_TimeInfo *ptTimeInfo);

/**********************************************************************
* 功能描述：  设置系统时间
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 SetSysTime(T_TimeInfo *ptTimeInfo);

/**********************************************************************
* 功能描述：  查询NTP配置
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 GetNtpCfg(T_NtpInfo *ptNtpInfo);

/**********************************************************************
* 功能描述：  设置NTP配置
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 SetNtpCfg(T_NtpInfo *ptNtpInfo);

/**********************************************************************
* 功能描述：  手动NTP同步时间
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 SyncNtpTime(T_NtpInfo *ptNtpInfo);

/**********************************************************************
* 功能描述：  查询NTP开关
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 GetNtpSwitch(T_NtpSwitch *ptNtpSwitch);

/**********************************************************************
* 功能描述：  设置NTP开关
* 输入参数：
* 输出参数：
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 SetNtpSwitch(T_NtpSwitch *ptNtpSwitch);

/**********************************************************************
* 功能描述：获取所有后台任务信息
* 输入参数：无
* 输出参数：全是出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 GetTaskInfo(T_TaskInfoList *ptTaskInfoList);

/**********************************************************************
* 功能描述：暂停/ 运行/ 删除后台任务
* 输入参数：sdwTaskId 、sdwTaskCtrl
* 输出参数：无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 SetTask(T_TaskCtrl *PtTaskCtrl);

/**********************************************************************
* 功能描述：添加后台任务
* 输入参数：
* 输出参数：无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 AddTask(T_TaskAddInfo *ptTaskAddInfo);

/**********************************************************************
* 功能描述：获取所有计划任务信息
* 输入参数：无
* 输出参数：全是出参
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 GetScheduleInfo(T_ScheduleList *ptScheduleList);

/**********************************************************************
* 功能描述： 删除计划任务
* 输入参数：sdwTaskId
* 输出参数：无
* 返回值：    0   - SUCCESS   !0     -  FAILURE
* 其它说明：无
***********************************************************************/
SWORD32 DelSchedule(T_ScheduleDel *ptScheduleDel);

/**********************************************************************
* 功能描述：获取系统信息
* 输入参数：T_SysInfo
* 输出参数：
* 返 回 值：  0      -   执行成功
*                                非0 - 执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetSysInfo(T_SysInfo *ptSysInfo);

/**********************************************************************
* 功能描述：检查系统是否准备就绪
* 输入参数：无
* 输出参数：ptSysReadyFlag
* 返 回 值： 0      -   执行成功
*            非0 - 执行失败
* 其它说明：
***********************************************************************/
SWORD32 CheckSystemReady(T_SysReadyFlag *ptSysReadyFlag);

/**********************************************************************
* 功能描述：修改系统名称
* 输入参数：T_SysNameInfo
* 输出参数：
* 返 回 值： 0      -   执行成功
*                                非0 - 执行失败
* 其它说明：
***********************************************************************/
SWORD32 SetSysName(T_SysNameInfo *ptSysName);

/**********************************************************************
* 功能描述：查看控制器详细信息
* 输入参数：T_CtrlInfo
* 输出参数：
* 返 回 值： 0      -   执行成功
*                                非0 - 执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetCtrlInfo(T_CtrlInfo *ptCtrlInfo);

/**********************************************************************

* 功能描述：修改本端控制器名称
* 输入参数：T_SysNameInfo
* 输出参数：
* 返 回 值： 0      -   执行成功
*                                非0 - 执行失败
* 其它说明：
***********************************************************************/
SWORD32 SetCtrlName(T_CtrlInfo *ptCtrlInfo);

/**********************************************************************

* 功能描述：获取单板类型
* 输入参数：GetBroadType
* 输出参数：
* 返 回 值： 0      -   执行成功
*            非0    - 执行失败
* 其它说明：
***********************************************************************/
SWORD32  GetBroadType(T_SysBroadType *ptSysBroadType);

/**********************************************************************
* 功能描述：查看磁盘SMART信息
* 输入参数：T_DmSmartInfo
* 输出参数：
* 返 回 值： 0      -   执行成功
*                                非0 - 执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetHddSmartInfo(T_DmSmartInfo *ptSmartInfo);
/**********************************************************************
* 功能描述：启动SMART扫描
* 输入参数：T_DmSmartTestCtl
* 输出参数：
* 返 回 值： 0      -   执行成功
*                                非0 - 执行失败
* 其它说明：
***********************************************************************/
SWORD32 ExecHddSmartTest(T_DmSmartTestCtl *ptSmartTest);
/**********************************************************************
* 功能描述：设置磁盘节能减排开关
* 输入参数：T_DmPowerStatSwitch
* 输出参数：
* 返 回 值： 0      -   执行成功
*                                非0 - 执行失败
* 其它说明：
***********************************************************************/
SWORD32 SetHddPowerSwitchStatus(T_DmPowerStatSwitch *ptPowSwitch);
/**********************************************************************
* 功能描述：获取磁盘节能减排开关
* 输入参数：T_DmPowerStatSwitch
* 输出参数：
* 返 回 值： 0      -   执行成功
*                                非0 - 执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetHddPowerSwitchStatus(T_DmPowerStatSwitch *ptPowSwitch);
/**********************************************************************
* 功能描述：同步文件到对端
* 输入参数：文件名称(不带路径)
* 输出参数：
* 返 回 值： 0      -   执行成功
*                                非0 - 执行失败
* 其它说明：
***********************************************************************/
SWORD32 SyncFileToPeer(T_FileToPeer *ptFileToPeer);
/**********************************************************************
* 功能描述：同步文件(两端都可以同步)
* 输入参数：文件名称(不带路径)
* 输出参数：
* 返 回 值： 0      -   执行成功
*                                非0 - 执行失败
* 其它说明：
***********************************************************************/
SWORD32 SyncFileToDual(T_FileToPeer *ptFileToPeer);
/**********************************************************************
* 功能描述：获取系统启动完成时间
* 输入参数：无
* 输出参数：ptSysBootTime->tSysSingleBootTime[2]
* 返 回 值： 0 - 执行成功
*          非0 - 执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetSysBootTime(T_SysBootTime *ptSysBootTime);
/**********************************************************************
* 功能描述：设置统计开关状态
* 输入参数：sdwStatFlag -- 统计开关
* 输出参数：无
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 SetStatAndWriteToCfg(SWORD32 sdwStatFlag);
/**********************************************************************
* 功能描述：查询统计开关状态
* 输入参数：无
* 输出参数：pStatFlag -- 统计开关
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetStatisticStatus(SWORD32 *pStatFlag);
/**********************************************************************
* 函数名称：GetCpuOccuRate
* 功能描述：查询CPU占用率
* 输入参数：无
* 输出参数：ptCpuOccupy
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetCpuOccupy(T_CpuOccupy  *ptCpuOccupy);
/**********************************************************************
* 函数名称：GetDiskStaticData
* 功能描述：查询磁盘SAS统计信息
* 输入参数：无
* 输出参数：ptSasStaticData
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetDiskStaticData(T_SasStatInfo *ptSasStatInfo);
/**********************************************************************
* 函数名称：GetPcieStaticData
* 功能描述：查询控制器内部PCIe吞吐情况
* 输入参数：无
* 输出参数：ptPcieSta
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetPcieStaticData(T_PcieFlowStatus *ptPcieSta);
/**********************************************************************
* 函数名称：GetTcsStaticData
* 功能描述：查询前端物理端口TCP/IP流量统计
* 输入参数：wSwitchFlag--统计开关
* 输出参数：ptPcieSta
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32  GetTcsStaticData(T_TcsStatInfo *ptTcsStatInfo);
/**********************************************************************
* 函数名称：GetCtrlStatInfo
* 功能描述：查询基于控制器的性能统计信息
* 输入参数：无
* 输出参数：ptCtrlStatInfo
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetCtrlStatInfo(T_CtrlStatInfo *ptCtrlStatInfo);
/**********************************************************************
* 函数名称：GetPortStatInfo
* 功能描述：查询基于端口的性能统计信息
* 输入参数：无
* 输出参数：ptPortStatInfo
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetPortStatInfo(T_PortStatInfo *ptPortStatInfo);
/**********************************************************************
* 函数名称：GetVolNum
* 功能描述：查询系统中所有的vol数目和类型
* 输入参数：sdwCtrlId       -- 控制器ID
* 输出参数：其他参数
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：目前只查询vd中的卷数目
***********************************************************************/
SWORD32 GetVolNum(T_VolNum *ptVolNum);
/**********************************************************************
* 函数名称：GetLunStatOnce
* 功能描述：分次查询基于LUN的性能统计信息
* 输入参数：sdwCtrlId       -- 控制器ID
            udwVolOnceNum   -- 每次要获取的vol 数量
            udwVolBgnIndex  -- 要获取信息的起始位置
* 输出参数：T_LunStat
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetLunStatOnce(T_LunStatOnceInfo *ptLunStatOnceInfo);
/**********************************************************************
* 函数名称：GetLunStatInfo
* 功能描述：查询单个LUN的性能统计信息
* 输入参数：cVolName   -- vol的名称
* 输出参数：T_LunStat
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetLunStatInfo(T_LunStatInfo *ptLunStatInfo);
/**********************************************************************
* 函数名称：GetDiskStatInfo
* 功能描述：查询基于磁盘的性能统计信息
* 输入参数：sdwSlotId       -- 磁盘槽位号
            sdwEnclosureId  -- 磁盘箱体号
* 输出参数：其他
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetDiskStatInfo(T_DiskStatInfo *ptDiskStatInfo);
/**********************************************************************
* 功能描述：查询基于磁盘的性能统计信息
* 输入参数：无
* 输出参数：T_AllDiskStatInfo
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetAllDiskStatInfo(T_AllDiskStatInfo *ptAllDiskStatInfo);
/**********************************************************************
* 函数名称：ExportCtrlStatInfo
* 功能描述：导出内存中保存的控制器历史性能统计信息
* 输入参数：ptSysInfoTarBall
* 输出参数：无
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 ExportCtrlStatInfo(T_SysInfoTarBall *ptSysInfoTarBall);
/**********************************************************************
* 函数名称：ExportPortStatInfo
* 功能描述：导出内存中保存的端口性能统计信息
* 输入参数：ptSysInfoTarBall
* 输出参数：无
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 ExportPortStatInfo(T_SysInfoTarBall *ptSysInfoTarBall);
/**********************************************************************
* 函数名称：ExportLunStatInfo
* 功能描述：导出内存中保存的LUN性能统计信息
* 输入参数：ptSysInfoTarBall
* 输出参数：无
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 ExportLunStatInfo(T_SysInfoTarBall *ptSysInfoTarBall);
/**********************************************************************
* 函数名称：ExportDiskStatInfo
* 功能描述：导出内存中保存的磁盘性能统计信息
* 输入参数：ptSysInfoTarBall
* 输出参数：无
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 ExportDiskStatInfo(T_SysInfoTarBall *ptSysInfoTarBall);
/**********************************************************************
* 函数名称：SetStatPeriod
* 功能描述：设置统计周期间隔
* 输入参数：dwTime
* 输出参数：无
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 SetStatPeriod(T_StatTime *ptStatTime);
/**********************************************************************
* 函数名称：GetStatPeriod
* 功能描述：设置统计周期间隔
* 输入参数：无
* 输出参数：dwTime
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetStatPeriod(T_StatTime *ptStatTime);
/**********************************************************************
* 函数名称：GetDevPmInfo
* 功能描述：读取设备统计数据
* 输入参数：T_StatHheadInfo
* 输出参数：T_BaseStatInfo
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/12/13      V1.0       王京         初次创建
***********************************************************************/
SWORD32 GetDevPmInfo(T_DevPmInfo *ptDevPmInfo);
/**********************************************************************
* 函数名称：GetVdPmInfo
* 功能描述：读取VD统计数据
* 输入参数：T_StatHheadInfo
            T_VDStat
* 输出参数：T_BaseStatInfo
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/12/13      V1.0       王京         初次创建
***********************************************************************/
SWORD32 GetVdPmInfo(T_VdPmInfo *ptVdPmInfo);
/**********************************************************************
* 函数名称：GetPoolPmInfo
* 功能描述：读取Pool统计数据
* 输入参数：T_StatHheadInfo
            T_POOLStat
* 输出参数：T_BaseStatInfo
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/12/13      V1.0       王京         初次创建
***********************************************************************/
SWORD32 GetPoolPmInfo(T_PoolPmInfo *ptPoolPmInfo);
/**********************************************************************
* 函数名称：GetPortPmInfo
* 功能描述：读取前端端口统计数据
* 输入参数：T_StatHheadInfo
            T_FRONTPORTStat
* 输出参数：T_PortStatDetailInfo
            T_StatHheadInfo
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/12/13      V1.0       王京         初次创建
***********************************************************************/
SWORD32 GetPortPmInfo(T_PortPmInfo *ptPortPmInfo);
/**********************************************************************
* 函数名称：GetDiskPmInfo
* 功能描述：读取磁盘统计数据
* 输入参数：T_StatHheadInfo
            T_DISKStat
* 输出参数：T_BaseStatInfo
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/12/13      V1.0       王京         初次创建
***********************************************************************/
SWORD32 GetDiskPmInfo(T_DiskPmInfo *ptDiskPmInfo);
/**********************************************************************
* 函数名称：GetLunPmInfo
* 功能描述：读取LUN统计数据
* 输入参数：T_StatHheadInfo
            T_LUNStat
* 输出参数：T_BaseStatInfo
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/12/13      V1.0       王京         初次创建
***********************************************************************/
SWORD32 GetLunPmInfo(T_LunPmInfo *ptLunPmInfo);
/**********************************************************************
* 功能描述：查询预设事件的cache自动直写策略
* 输入参数：无
* 输出参数：ptAutoWrThrPreSet
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetAutoWrThrEvt(T_AutoWrThrPreSet *ptAutoWrThrPreSet);
/**********************************************************************
* 功能描述：设置预设事件的cache自动直写策略
* 输入参数：ptAutoWrThrPreSet
* 输出参数：无
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 SetAutoWrThrEvt(T_AutoWrThrPreSet *ptAutoWrThrPreSet);

/**********************************************************************
* 函数名称：GetAllVolSimpleInfo
* 功能描述：获取所有普通卷简要信息
* 输入参数：无
* 输出参数：卷数目及卷信息列表
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetAllVolSimpleInfo(T_VolSimpleInfoList *ptVolSimpleInfoList);

/**********************************************************************
* 函数名称：GetAllVolSimpleInfoOnPool
* 功能描述：获取pool上所有普通卷简要信息
* 输入参数：无
* 输出参数：卷数目及卷简要信息列表
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetAllVolSimpleInfoOnPool(T_VolSimpleInfoListOnPool *ptVolSimpleInfoListOnPool);

/**********************************************************************
* 函数名称：GetSystemSimpleInfo
* 功能描述：获取系统简要信息
* 输入参数：无
* 输出参数：卷数目及卷信息列表
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetSystemSimpleInfo(T_SystemSimpleInfo *ptSystemSimpleInfo);

/**********************************************************************
* 函数名称：GetVirtualObjectSimpleInfo
* 功能描述：获取虚拟对象(vd/pool)简要信息
* 输入参数：无
* 输出参数：卷数目及卷信息列表
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 GetVirtualObjectSimpleInfo(T_VoSimpleInfoList *ptVoSimpleInfoList);

/**********************************************************************/
/*********************MTS使用的CAPI接口*******************************/
/**********************************************************************
* 功能描述：工作EPLD自检
* 输入参数：无
* 输出参数：ptCheckWorkEpldSelf
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiCheckWorkEpldSelf(T_Mts_Check_Work_Epld_Self *ptCheckWorkEpldSelf);

/**********************************************************************
* 功能描述：工作EPLD信息读取
* 输入参数：无
* 输出参数：ptCheckWorkEpldInfo
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiCheckWorkEpldInfo(T_Mts_Check_Work_Epld_Info *ptCheckWorkEpldInfo);

/**********************************************************************
* 功能描述：启动EPLD信息读取
* 输入参数：无
* 输出参数：ptCheckBootEpldInfo
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiCheckBootEpldInfo(T_Mts_Check_Boot_Epld_Info *ptCheckBootEpldInfo);

/**********************************************************************
* 功能描述：电子条形码扫描
* 输入参数：无
* 输出参数：ptCheckLableInfo
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiCheckLableInfo(T_Mts_Check_Lable_Info *ptCheckLableInfo);

/**********************************************************************
* 功能描述：单板硬件地址读取
* 输入参数：无
* 输出参数：ptCheckPhyAddrInfo
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiCheckPhyAddrInfo(T_Mts_Check_Phy_Addr_Info *ptCheckPhyAddrInfo);

/**********************************************************************
* 功能描述：在位信号测试
* 输入参数：无
* 输出参数：ptCheckLocPreState
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiCheckLocalPreState(T_Mts_Check_Online_Flag *ptCheckLocPreState);

/**********************************************************************
* 功能描述：CPU外挂DDR3测试
* 输入参数：无
* 输出参数：ptCheckDdr
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiCheckDdr(T_Mts_Check_Ddr *ptCheckDdr);

/**********************************************************************
* 功能描述：NVRAM芯片测试
* 输入参数：无
* 输出参数：ptCheckNvram
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiCheckNvram(T_Mts_Check_Nvram *ptCheckNvram);

/**********************************************************************
* 功能描述：版本flash测试
* 输入参数：无
* 输出参数：ptCheckVerFlash
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiCheckVerFlash(T_Mts_Check_Verflash *ptCheckVerFlash);

/**********************************************************************
* 功能描述：板内时钟电路测试
* 输入参数：无
* 输出参数：ptCheckClock
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiCheckClock(T_Mts_Check_Clock *ptCheckClock);

/**********************************************************************
* 功能描述：面板指示灯测试
* 输入参数：无
* 输出参数：ptCheckLed
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiCheckLed(T_Mts_Check_Led *ptCheckLed);

/**********************************************************************
* 功能描述：看门狗复位测试
* 输入参数：无
* 输出参数：ptCheckWtg
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiCheckWtg(T_Mts_Check_Wtg *ptCheckWtg);

/**********************************************************************
* 功能描述：温度传感器
* 输入参数：无
* 输出参数：ptCheckTemp
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiCheckSenor(T_Mts_Check_Senor *ptCheckSenor);

/**********************************************************************
* 功能描述：RTC实时时钟电路测试
* 输入参数：无
* 输出参数：ptCheckRtc
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiCheckRtc(T_Mts_Check_Rtc *ptCheckRtc);

/**********************************************************************
* 功能描述：面板GE口环回测试
* 输入参数：无
* 输出参数：ptCheckGe
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiCheckGe(T_Mts_Check_Ge *ptCheckGe);

/**********************************************************************
* 功能描述：面板调试网口作为通信链路测试
* 输入参数：无
* 输出参数：ptCheckConnectLink
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiCheckConnectLink(T_Mts_Check_Conn_Link *ptCheckConnLink);

/**********************************************************************
* 功能描述：Cache同步信号测试/PCIE芯片桥自检
* 输入参数：无
* 输出参数：ptCheckPcieInfo
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiCheckPcie(T_Mts_Check_Pcie_Info *ptCheckPcieInfo);

/**********************************************************************
* 功能描述：phy芯片自检
* 输入参数：无
* 输出参数：ptPhySelf
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiCheckPhySelf(T_Mts_Check_Phyself *ptPhySelf);

/**********************************************************************
* 功能描述：PM8001自检
* 输入参数：无
* 输出参数：ptPmSelf
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiCheckPmSelf(T_Mts_Check_Pm *ptPmSelf);

/**********************************************************************
* 功能描述：输入IO信号指示灯测试
* 输入参数：无
* 输出参数：ptInputIo
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32  mtsCapiCheckInputIo(T_Mts_Check_InputIo *ptInputIo);

/**********************************************************************
* 功能描述：输出IO信号指示灯测试
* 输入参数：无
* 输出参数：ptOutputIo
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32  mtsCapiCheckOutputIo(T_Mts_Check_OutputIo *ptOutputIo);

/**********************************************************************
* 功能描述：SSD容量读取测试
* 输入参数：无
* 输出参数：ptInputIo
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
***********************************************************************/
SWORD32 mtsCapiGetSsdSize(T_Mts_Ssd_SizeTest *ptGetSsdSize);

/**********************************************************************
* 功能描述：SSD读写测试
* 输入参数：无
* 输出参数：ptInputIo
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
***********************************************************************/
SWORD32 mtsCapiSsdWDtest(T_Mts_Ssd_WDTest *ptSsdWD);

/**********************************************************************
* 函数名称：mtsCapiGetCpuCoreNum
* 功能描述：Cpu core number test
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：ptInputIo
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/12/26      V1.0       liutt      初次创建
***********************************************************************/

/**********************************************************************
* 功能描述：电源信号指示灯测试
* 输入参数：无
* 输出参数：ptPowerLight
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32  mtsCapiCheckPowerLight(T_Mts_Check_Power_Light *ptPowerLight);

/**********************************************************************
* 功能描述：获取BBU信息
* 输入参数：无
* 输出参数：ptMtsCheckBbu
* 返 回 值：0      -   执行成功
*           非0    -   执行失败
* 其它说明：
***********************************************************************/
SWORD32 mtsCapiGetWorkBbuInfo(T_Mts_Check_Bbu *ptCheckBbu);

/**********************************************************************
* 函数名称：mtsCapiEzzfReset
* 功能描述：8005看门狗复位测试
* 输入参数：无
* 输出参数：ptMtsCheckBbu
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
***********************************************************************/
SWORD32 mtsCapiEzzfReset(T_Mts_Check_Ezzf_Reset *ptMtsEzzfReset);

/**********************************************************************
* 函数名称：mtsCapiEzzfGetSpeed
* 功能描述：minisas接口自环测试
* 输入参数：无
* 输出参数：ptMtsCheckBbu
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
***********************************************************************/
SWORD32 mtsCapiEzzfGetSpeed(T_Mts_Check_Ezzf_GetSpeed *ptMtsEzzfGetSpeed);

/**********************************************************************
* 函数名称：mtsCapiEzzfBbGetSpeed
* 功能描述：背板SAS接口自环测试
* 输入参数：无
* 输出参数：ptMtsCheckBbu
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
***********************************************************************/
SWORD32 mtsCapiEzzfBbGetSpeed(T_Mts_Check_Ezzf_BdGetSpeed *ptMtsEzzfBdGetSpeed);

/**********************************************************************
* 函数名称：mtsCapiEzzfTtSigTest
* 功能描述：TW0\TW1\TW2信号测试
* 输入参数：无
* 输出参数：ptMtsCheckBbu
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
***********************************************************************/
SWORD32 mtsCapiEzzfTtSigTest(T_Mts_Check_Ezzf_Ttsig *ptMtsEzzfTtsig);

/**********************************************************************
* 函数名称：mtsCapiEzzfSasSelf
* 功能描述：SAS扩展芯片PM8005自检
* 输入参数：无
* 输出参数：ptMtsCheckBbu
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
***********************************************************************/
SWORD32 mtsCapiEzzfSasSelf(T_Mts_Check_Ezzf_Self *ptMtsEzzfSelf);

/**********************************************************************
* 函数名称：mtsCapiHddLight
* 功能描述：硬盘指示灯测试
* 输入参数：无
* 输出参数：ptMtsCheckBbu
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
***********************************************************************/
SWORD32 mtsCapiHddLight(T_Mts_Check_Hdd_Light *ptMtsHddLight);

/**********************************************************************
* 函数名称：mtsCapiDdrSize
* 功能描述：内存大小检测
* 输入参数：无
* 输出参数：ptMtsDdrSize
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
***********************************************************************/
SWORD32 mtsCapiDdrSize(T_Mts_Check_Ddr_Size *ptMtsDdrSize);

/**********************************************************************
* 函数名称：mtsCapiCheckVer
* 功能描述：检测版本
* 输入参数：无
* 输出参数：ptMtsDdrSize
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
***********************************************************************/
SWORD32 mtsCapiCheckVer(T_Mts_Check_Ver *ptMtsVer);

/**********************************************************************
* 函数名称：mtsCapiCheckMacAddr
* 功能描述：MAC地址获取
* 输入参数：无
* 输出参数：ptMtsMacAddr
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
***********************************************************************/
SWORD32 mtsCapiCheckMacAddr(T_Mts_Check_MacAddr *ptMtsMacAddr);

/*****************************整机测试*********************************/
/**********************************************************************
* 函数名称：cmtCapiWorkEpldSelf
* 功能描述：工作EPLD整机测试
* 输入参数：无
* 输出参数：ptMtsWorkEpldSelf
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
***********************************************************************/
SWORD32 cmtCapiWorkEpldSelf(T_WorkEpldSelfList *ptCmtWorkEpldSelf);

/**********************************************************************
* 函数名称：cmtCapiWorkEpldInfo
* 功能描述：工作EPLD信息读取
* 输入参数：无
* 输出参数：ptCmtWorkEpldInfo
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
***********************************************************************/
SWORD32 cmtCapiWorkEpldInfo(T_WorkEpldInfoList *ptCmtWorkEpldInfo);

/**********************************************************************
* 函数名称：cmtCapiBootEpldInfo
* 功能描述：启动EPLD整机测试信息获取
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：ptMtsWorkEpldSelf
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/05/12      V1.0       wangwei      初次创建
***********************************************************************/
SWORD32 cmtCapiBootEpldInfo(T_BootEpldInfoList *ptCmtBootEpldInfo);

/**********************************************************************
* 函数名称：cmtCapiLableInfo
* 功能描述：电子标签信息
* 输入参数：无
* 输出参数：ptMtsWorkEpldSelf
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/05/12      V1.0       wangwei      初次创建
***********************************************************************/
SWORD32 cmtCapiLableInfo(T_LableInfoList *ptCmtLableInfo);

/**********************************************************************
* 函数名称：cmtCapiPhyAddrInfo
* 功能描述：单板硬件地址读取
* 输入参数：无
* 输出参数：ptMtsWorkEpldSelf
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/05/12      V1.0       wangwei      初次创建
***********************************************************************/
SWORD32 cmtCapiPhyAddrInfo(T_PhyAddrInfoList *ptCmtPhyAddrInfo);

/**********************************************************************
* 函数名称：cmtCapiOnlineFlagInfo
* 功能描述：在位信号测试
* 输入参数：无
* 输出参数：ptMtsWorkEpldSelf
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/05/12      V1.0       wangwei      初次创建
***********************************************************************/
SWORD32 cmtCapiOnlineFlagInfo(T_OnlineFlagInfoList *ptCmtOnlieFlagInfo);

/**********************************************************************
* 函数名称：cmtCapiClockInfo
* 功能描述：板内时钟电路测试
* 输入参数：无
* 输出参数：ptMtsWorkEpldSelf
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/05/12      V1.0       wangwei      初次创建
***********************************************************************/
SWORD32 cmtCapiClockInfo(T_ClockInfoList *ptCmtClockInfo);

/**********************************************************************
* 函数名称：cmtCapiSenorInfo
* 功能描述：传感器信息获取
* 输入参数：无
* 输出参数：ptMtsWorkEpldSelf
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/05/12      V1.0       wangwei      初次创建
***********************************************************************/
SWORD32 cmtCapiSenorInfo(T_SenorInfoList *ptCmtSenorInfo);
SWORD32 cmtCapiExpInfo(T_MtsEncDeviceInfoList *ptCmtExpInfo);
SWORD32 cmtCapiDiskInfo(T_MtsDiskInfo *ptCmtDiskInfo);

/**********************************************************************
* 函数名称：cmtCapiRtcInfo
* 功能描述：RTC实时时钟电路测试
* 输入参数：无
* 输出参数：ptMtsWorkEpldSelf
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/05/12      V1.0       wangwei      初次创建
***********************************************************************/
SWORD32 cmtCapiRtcInfo(T_RtcInfoList *ptCmtRtcInfo);

/**********************************************************************
* 函数名称：cmtCapiGeInfo
* 功能描述：GE口链路速率，是否双控测试
* 输入参数：无
* 输出参数：ptMtsWorkEpldSelf
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/05/12      V1.0       wangwei      初次创建
***********************************************************************/
SWORD32 cmtCapiGeInfo(T_GeInfoList *ptCmtGeInfo);

/**********************************************************************
* 函数名称：cmtCapiPcieInfo
* 功能描述：PCIE测试
* 输入参数：无
* 输出参数：ptMtsWorkEpldSelf
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/05/12      V1.0       wangwei      初次创建
***********************************************************************/
SWORD32 cmtCapiPcieInfo(T_PcieInfoList *ptCmtPcieInfo);

/**********************************************************************
* 函数名称：cmtCapiPhyInfo
* 功能描述：PHY自检
* 输入参数：无
* 输出参数：ptMtsWorkEpldSelf
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/05/12      V1.0       wangwei      初次创建
***********************************************************************/
SWORD32 cmtCapiPhyInfo(T_PhyInfoList *ptCmtPhyInfo);

/**********************************************************************
* 函数名称：cmtCapiPmInfo
* 功能描述：SAS控制器PM8001自检
* 输入参数：无
* 输出参数：ptCmtPmInfo
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/05/12      V1.0       wangwei      初次创建
***********************************************************************/
SWORD32 cmtCapiPmInfo(T_PmInfoList *ptCmtPmInfo);

/**********************************************************************
* 函数名称：cmtCapiBbuInfo
* 功能描述：BBU检测
* 输入参数：无
* 输出参数：ptCmtBbuInfo
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/05/12      V1.0       wangwei      初次创建
***********************************************************************/
SWORD32 cmtCapiBbuInfo(T_BbuInfoList *ptCmtBbuInfo);

/**********************************************************************
* 函数名称：cmtCapiSasInfo
* 功能描述：MINISAS和背部SAS接口测试
* 输入参数：无
* 输出参数：ptCmtSasInfo
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/05/12      V1.0       wangwei      初次创建
***********************************************************************/
SWORD32 cmtCapiSasInfo(T_SasInfoList *ptCmtSasInfo);
SWORD32 mtsCapiTestSasInterface(T_MtsTestSas *ptMtsTestSas);
/**********************************************************************
* 函数名称：cmtCapiHddInfo
* 功能描述：HardDisk 自检
* 输入参数：无
* 输出参数：ptCmtHddInfo
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/05/12      V1.0       wangwei      初次创建
***********************************************************************/
SWORD32 cmtCapiHddInfo(T_HddInfoList *ptCmtHddInfo);

/**********************************************************************
* 函数名称：cmtCapiVerInfo
* 功能描述：版本检测
* 输入参数：无
* 输出参数：cmtCapiVerInfo
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/05/12      V1.0       wangwei      初次创建
***********************************************************************/
SWORD32 cmtCapiVerInfo(T_VerInfoList *ptCmtVerInfo);

/**********************************************************************
* 函数名称：cmtCapiDdrInfo
* 功能描述：内存检测
* 输入参数：无
* 输出参数：ptMtsWorkEpldSelf
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/05/12      V1.0       wangwei      初次创建
***********************************************************************/
SWORD32 cmtCapiDdrInfo(T_DdrInfoList *ptCmtDdrInfo);

/**********************************************************************
* 函数名称：cmtCapiMacAddrInfo
* 功能描述：MAC地址
* 输入参数：无
* 输出参数：ptMtsWorkEpldSelf
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/05/12      V1.0       wangwei      初次创建
***********************************************************************/
SWORD32 cmtCapiMacAddrInfo(T_MacAddrInfoList *ptCmtMacAddrInfo);

/**********************************************************************
* 函数名称：cmtCapiPeerStateInfo
* 功能描述：测试环境检测
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：ptMtsWorkEpldSelf
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/05/12      V1.0       wangwei      初次创建
***********************************************************************/
SWORD32 cmtCapiPeerStateInfo(T_PeerStateInfoList *ptCmtPeerStateInfo);

/**********************************************************************
* 函数名称：cmtCapiSasAddrInfo
* 功能描述：SAS地址检测,即8005自检
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：ptMtsWorkEpldSelf
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/05/12      V1.0       wangwei      初次创建
***********************************************************************/
SWORD32 cmtCapiSasAddrInfo(T_SasAddrInfoList *ptCmtSasAddrInfo);

/* added by huangan 20131227 */
SWORD32 cmtCapiSpr10GetMode(T_Spr10WorkMode *ptSpr10WorkMode);
SWORD32 cmtCapiSpr10SingleMode(T_Spr10WorkMode *ptSpr10WorkMode);
SWORD32 cmtCapiSpr10DoubleMode(T_Spr10WorkMode *ptSpr10WorkMode);
SWORD32 cmtCapispr11DdrSize(T_Cmt_SPR11_Check_Ddr_Size *ptMtsDdrSize);
SWORD32 cmtCapiSPR11WorkEpldInfo(T_SPR11WorkEpldInfoList *ptCmtWorkEpldInfo);
SWORD32 cmtCapispr11SSDInfo(T_Cmt_SPR11_SSD *ptSsdInfo);
SWORD32 cmtCapispr11CheckMacAddr(T_Cmt_SPR11_Check_MacAddr *ptMtsMacAddr);
SWORD32 cmtCapispr11CheckChipClock(T_Cmt_SPR11_ChipCLOCK *ptMtsChipClock);
SWORD32 cmtCapispr11CheckHb(T_Cmt_SPR11_Check_Hb *ptMtsHb);
SWORD32 cmtCapispr11CheckChips(T_Cmt_SPR11_Check_Chips *ptCheckChips);
SWORD32 cmtCapispr11FCInfo(T_Cmt_SPR11_FCinfo *ptFcInfo);
SWORD32 cmtCapispr11VoltInfo(T_Cmt_SPR11_Voltinfo *ptVoltInfo);
SWORD32 cmtCapispr11FCCtl(T_Cmt_FCSetMSTSFPTXStatus *ptFCtl);
/**********************************************************************
* 函数名称：CollectSysInfo
* 功能描述：系统信息采集
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：ptMtsWorkEpldSelf
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/06/12      V1.0       姚冬      初次创建
***********************************************************************/
SWORD32 CollectSysInfo(T_SicCtrlAction *ptCtrlAction);

/**********************************************************************
* 函数名称：GetTarBallInfo
* 功能描述：系统信息采集压缩包信息获取
* 访问的表：无
* 修改的表：无
* 输入参数：无
* 输出参数：ptMtsWorkEpldSelf
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/06/12      V1.0       姚冬      初次创建
***********************************************************************/
SWORD32 GetTarBallInfo(T_TarBallInfoList *ptTarBallInfoList);

SWORD32 mtsCapispr11CheckDdr(T_Mts_SPR11_Check_Ddr *ptCheckDdr);
SWORD32 mtsCapispr11DdrSize(T_Mts_SPR11_Check_Ddr_Size *ptMtsDdrSize);
SWORD32 mtsCapispr11CheckWorkEpldSelf(T_Mts_SPR11_Check_Work_Epld_Self *ptCheckWorkEpldSelf);
SWORD32 mtsCapispr11CheckMacAddr(T_Mts_SPR11_Check_MacAddr *ptMtsMacAddr);
SWORD32 mtsCapispr11CheckSenor(T_Mts_SPR11_Check_Senor *ptCheckSenor);
SWORD32 mtsCapispr11GetWorkBbuInfo(T_Mt_SPR11_Check_Bbu *ptMtsCheckBbu);
SWORD32 mtsCapispr11GetSasLinkSpeed(T_Mts_SPR11_SASLINK *ptMtsSasLinkSpeed);
SWORD32 mtsCapispr11CheckRtc(T_Mts_SPR11_Check_Rtc *ptCheckRtc);
SWORD32 mtsCapispr11CheckClock(T_Mts_SPR11_Check_Clock *ptCheckClock);
SWORD32 mtsCapispr11Light(T_Mts_SPR11_Check_LED_Light *ptMtsHddLight);
SWORD32 mtsCapispr11CheckWorkEpldInfo(T_Mts_SPR11_Check_Work_Epld_Info *ptCheckWorkEpldInfo);
SWORD32 mtsCapispr11CheckChips(T_Mts_SPR11_Check_Chips *ptCheckChips);
SWORD32 mtsCapispr11CheckLableInfo(T_Mts_SPR11_Check_Lable_Info *ptCheckLableInfo);
SWORD32 mtsCapispr11CheckWtg(T_Mts_Check_Wtg *ptCheckWtg);
SWORD32 mtsCapispr11CheckVer(T_Mts_SPR11_Check_Ver *ptMtsVer);
SWORD32 mtsCapispr11FCInfo(T_Mts_SPR11_FCinfo *ptFcInfo);
SWORD32 mtsCapispr11CheckFC(T_Mts_Check_FC *ptCheckFC);
SWORD32 mtsCapispr11CheckFCLight(T_Mts_Check_FC_LED *ptFCLight);
SWORD32 mtsCapispr11SSDInfo(T_Mts_SPR11_SSD *ptSsdInfo);
SWORD32 mtsCapispr11CheckMacBand(T_Mts_SPR11_Check_Macband *ptMtsMacBand);
SWORD32 mtsCapispr11GetUSB(T_Mts_SPR11_USB *ptMtsUSB);
SWORD32 mtsCapispr11CheckPresent(T_Mts_SPR11_Online_Flag *ptMtsPresent);
SWORD32 mtsCapispr11CheckChipClock(T_Mts_SPR11_ChipCLOCK *ptMtsChipClock);
SWORD32 mtsCapispr11Checkcpld(T_Mts_SPR11_CHECKCOMMON *ptMtsCPLD);
SWORD32 mtsCapispr11Dspam(T_Mts_SPR11_DSPAM *ptMtsDspam);
SWORD32 mtsCapispr11BackPlaneIO(T_Mts_SPR11_CHECKBACKPLANEIO *ptBackplaneio);
SWORD32 mtsCapiSpr11SetIbmcNetwork(T_Mts_SPR11_IBMC_NET *ptMtsIbmcNet);

/* mts for spr12 */
SWORD32 mtsCapiCtrlPeerPower(T_Mts_Ctrl *pCtrl);
SWORD32 mtsCapiGetRamId(T_Mts_RamId *ptRamId);
SWORD32 mtsCapiGetCpuType(T_Mts_CpuType *ptInfo);
SWORD32 mtsCapiGetFcCardInfo(T_Mts_FC_Card_Info *ptInfo);
SWORD32 mtsCapiBoardSsd(T_Mts_Board *diagSsd);
SWORD32 mtsCapiSenor(T_Mts_Senor *ptCheckSenor);
SWORD32 mtsCapiBoardOnline(T_Mts_Board *ptBoardOnline);
SWORD32 mtsCapiSubCard(T_Mts_Board *ptCheckSubCard);
SWORD32 mtsCapiPeerBoardOnline(T_Mts_Board *ptPeerBoard);
SWORD32 mtsCapiResetPeerBoard(T_Mts_Board *ptResetPeerBoard);
SWORD32 mtsCapiWatchDog(T_Mts_Board *ptWatchDog);
SWORD32 mtsCapiBootVer(T_Mts_Board *ptCpu);
SWORD32 mtsCapiFlashVer(T_Mts_Board *ptFlash);
SWORD32 mtsCapiVerRewrite(T_Mts_Board *ptVerRewrite);
SWORD32 mtsCapiCpuCoreTest(T_Mts_Board *ptCpuCore);
SWORD32 mtsCapiBoardClock(T_Mts_Board *ptBoardClock);
SWORD32 mtsCapiNandFlash(T_Mts_Board *ptNandFlash);
SWORD32 mtsCapi10G(T_Mts_10G *pt10G);
SWORD32 cmtCapi10G(T_Cmt_10G *pt10GList);
SWORD32 mtsCapiSffInfo(T_Mts_Sff *ptSffInfo);
SWORD32 cmtCapiSffInfo(T_Cmt_Sff *ptSffList);
SWORD32 mtsCapiOpticalOuterTest(T_Mts_10GSelfTest *ptOpticalOuter);
SWORD32 cmtCapiOpticalOuter(T_Cmt_10GSelfTest *ptOpticalOuterList);
SWORD32 mtsCapiChipSelfTest(T_Mts_10GSelfTest *ptChipSelfTest);
SWORD32 cmtCapiChipSelfTest(T_Cmt_10GSelfTest *ptChipSelfTestList);
SWORD32 mtsCapiMacAddr(T_Mts_MacAddr *ptMacAddr);
SWORD32 cmtCapiMacAddr(T_Cmt_MacAddr *ptMacAddrList);
SWORD32 mtsCapiTempSenor(T_Mts_Board *ptTempSenor);
SWORD32 cmtCapiBoardOnline(T_OnlineFlagInfoList *ptCmtBoardOnline);
SWORD32 cmtCapiC2FSsd(T_CmtC2fSsdList *ptSsd);
SWORD32 cmtCapiSerdesPingTest(T_CmtRtcInfo *ptPing);

/* 以下为fc会话呈现提供的接口函数 */
/**********************************************************************
* 函数名称：GetFCProtocalInfo
* 功能描述：获取FC会话协议信息
* 访问的表：无
* 修改的表：无
* 输入参数：CtrlId,PortId
* 输出参数：协议信息
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/08/30      V1.1      qinping      初次创建
***********************************************************************/
SWORD32 GetFCProtocalInfo(T_GetFCProtocolIInfo *ptFcProtocalInfo);
/**********************************************************************
* 函数名称：GetCtrlPortTypeInfo
* 功能描述：获取控制器上的端口类型
* 访问的表：无
* 修改的表：无
* 输入参数：CtrlId,
* 输出参数：端口类型udwPortType和端口个数
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/08/30      V1.1      qinping      初次创建
***********************************************************************/
SWORD32 GetCtrlPortTypeInfo(T_GetCtrlPortTypeInfo *ptPortTypeInfo);
/**********************************************************************
* 函数名称：GetFCProtocalInfo
* 功能描述：获取FC会话统计信息
* 访问的表：无
* 修改的表：无
* 输入参数：CtrlId,PortId
* 输出参数：协议信息
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/08/30      V1.1      qinping      初次创建
***********************************************************************/
SWORD32 GetFCPortStatisticInfo(T_FCGetPortStatisInfo *ptFcPortStatisInfo);
/**********************************************************************
* 函数名称：GetFCProtocalInfo
* 功能描述：清除FC会话统计信息
* 访问的表：无
* 修改的表：无
* 输入参数：CtrlId,PortId
* 输出参数：协议信息
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/08/30      V1.1      qinping      初次创建
***********************************************************************/
SWORD32 ClearFCPortStatisticInfo(T_ClearFCPortStatisInfo *ptClearFcPortStatisInfo);
/**********************************************************************
* 函数名称：GetFCProtocalInfo
* 功能描述：获取FC会话统计信息，提供给web调用
* 访问的表：无
* 修改的表：无
* 输入参数：CtrlId,PortId
* 输出参数：协议信息
* 返 回 值： 0  -  执行成功
*          非0  -  执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2012/08/30      V1.1      qinping      初次创建
***********************************************************************/
SWORD32 GetFCPortStatisticInfoForWeb(T_WebGetFCPortStatisInf *ptFcPortStatisInfo);
/**********************************************************************
* 函数名称：  GetUspUpdateChkStatus
* 功能描述：获取USP更新前是否具备更新条件
* 输入参数：T_UpdateUspChk *ptUpdateUspChk
* 输出参数：T_UpdateUspChk *ptUpdateUspChk
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2013/03/12     V1.1      huangan      初次创建
***********************************************************************/
SWORD32 GetUspUpdateChkStatus(T_UpdateUspChk *ptUpdateUspChk);

SWORD32 GetExpList(T_SASExpanderList *ptExpList);
SWORD32 ExpPhyOp(T_SASExpanderPhyOp *ptExpOp);
/**********************************************************************
* 函数名称：  SetVdEnergyConsrv
* 功能描述：设置Vd节能模式
* 输入参数： ptVdConsrvMode->cVdName   ptVdConsrvMode->sdwEnergyConsrv
* 输出参数：无
* 返 回 值：    0      -   执行成功
*                           非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/04/1     V1.1      qinping      初次创建
***********************************************************************/
SWORD32 SetVdEnergyConsrv(T_VdEnergyConsrvMod *ptVdConsrvMode);
/**********************************************************************
* 函数名称：mtsCapiCpuCore
* 功能描述：多核CPU核数测试
* 输入参数：T_Mts_Check_CpuCore *ptCpuCore
* 输出参数：T_Mts_Check_CpuCore *ptCpuCore
* 返 回 值： 0    -  执行成功
*            非0  -  执行失败
* 其它说明: 无

* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/06/04      V1.0       刘涛涛        初次创建
***********************************************************************/
SWORD32 mtsCapiCpuCore(T_Mts_Check_CpuCore *ptCpuCore);
/**********************************************************************
* 函数名称：mtsCapiCpuMemorySize
* 功能描述：CPU外存容量获取
* 输入参数：T_Mts_Check_CpuMemorySize *ptCpuMemorySize
* 输出参数：T_Mts_Check_CpuMemorySize *ptCpuMemorySize
* 返 回 值： 0    -  执行成功
*            非0  -  执行失败
* 其它说明: 无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/06/05      V1.0       刘涛涛        初次创建
***********************************************************************/
SWORD32 mtsCapiCpuMemorySize(T_Mts_Check_CpuMemorySize *ptCpuMemorySize);
/**********************************************************************
* 函数名称：mtsCapiCpuMemoryTest
* 功能描述：CPU外存MEMORY测试
* 输入参数：T_Mts_Check_CpuMemoryTest *ptCpuMemoryTest
* 输出参数: T_Mts_Check_CpuMemoryTest *ptCpuMemoryTest
* 返 回 值： 0    -  执行成功
*            非0  -  执行失败
* 其它说明: 无

* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/06/05      V1.0       刘涛涛        初次创建
***********************************************************************/
SWORD32 mtsCapiCpuMemoryTest(T_Mts_Check_CpuMemoryTest *ptCpuMemoryTest);
/**********************************************************************
* 函数名称：mtsCapiCpuSpdInfo
* 功能描述：CPU外存SPD信息获取
* 输入参数：T_Mts_Check_CpuSpdInfo *ptCpuSpdInfo
* 输出参数：T_Mts_Check_CpuSpdInfo *ptCpuSpdInfo
* 返 回 值： 0    -  执行成功
*            非0  -  执行失败
* 其它说明: 无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/06/05      V1.0       刘涛涛        初次创建
***********************************************************************/
SWORD32 mtsCapiCpuSpdInfo(T_Mts_Check_CpuSpdInfo *ptCpuSpdInfo);
/**********************************************************************
* 函数名称：mtsCapiCpuSpdInfoCheck
* 功能描述：CPU SPD信息校验（只针对X86单板有效）
* 输入参数：T_Mts_Check_CpuSpdInfoCheck *ptCpuSpdInfoCheck
* 输出参数：T_Mts_Check_CpuSpdInfoCheck *ptCpuSpdInfoCheck
* 返 回 值： 0    -  执行成功
*            非0  -  执行失败
* 其它说明: 无

* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/06/05      V1.0       刘涛涛        初次创建
***********************************************************************/
SWORD32 mtsCapiCpuSpdInfoCheck(T_Mts_Check_CpuSpdInfoCheck *ptCpuSpdInfoCheck);
/**********************************************************************
* 函数名称：mtsCapiFlashTest
* 功能描述：FLASH测试
* 输入参数：T_Mts_Check_FlashTest *ptFlashTest
* 输出参数：T_Mts_Check_FlashTest *ptFlashTest
* 返 回 值： 0    -  执行成功
*            非0  -  执行失败
* 其它说明: 无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/06/05      V1.0       刘涛涛        初次创建
***********************************************************************/
SWORD32 mtsCapiFlashTest(T_Mts_Check_FlashTest *ptFlashTest);
/**********************************************************************
* 函数名称：mtsCapiWDogEnableTest
* 功能描述：WATCHDOG使能
* 输入参数：T_Mts_Check_WDogEnableTest *ptWDogEnable
* 输出参数：T_Mts_Check_WDogEnableTest *ptWDogEnable
* 返 回 值： 0    -  执行成功
*            非0  -  执行失败
* 其它说明: 无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/06/06      V1.0       刘涛涛        初次创建
***********************************************************************/
SWORD32 mtsCapiWDogEnableTest(T_Mts_Check_WDogEnable *ptWDogEnable);
/**********************************************************************
* 函数名称：mtsCapiWDogFeedingTest
* 功能描述：WATCHDOG喂狗
* 输入参数：T_Mts_Check_WDogFeedingTest *ptWDogFeeding
* 输出参数：T_Mts_Check_WDogFeedingTest *ptWDogFeeding
* 返 回 值： 0    -  执行成功
*            非0  -  执行失败
* 其它说明: 无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/06/06      V1.0       刘涛涛        初次创建
***********************************************************************/
SWORD32 mtsCapiWDogFeedingTest(T_Mts_Check_WDogFeeding *ptWDogFeeding);
/**********************************************************************
* 函数名称：mtsCapiClockRtcTest
* 功能描述：RTC时钟芯片测试
* 输入参数：T_Mts_Check_ClockRtcTest *ptClockRtc
* 输出参数：T_Mts_Check_ClockRtcTest *ptClockRtc
* 返 回 值： 0    -  执行成功
*            非0  -  执行失败
* 其它说明: 无

* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/06/06      V1.0       刘涛涛        初次创建
***********************************************************************/
SWORD32 mtsCapiClockRtcTest(T_Mts_Check_ClockRtcTest *ptClockRtc);
/**********************************************************************
* 函数名称：mtsCapiLedTest
* 功能描述：点灯测试
* 输入参数：T_Mts_Check_LedTest *ptLed
* 输出参数：T_Mts_Check_LedTest *ptLed
* 返 回 值： 0    -  执行成功
*            非0  -  执行失败
* 其它说明: 无

* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/06/06      V1.0       刘涛涛        初次创建
***********************************************************************/
SWORD32 mtsCapiLedTest(T_Mts_Check_LedTest *ptLed);
/**********************************************************************
* 函数名称：mtsCapiFirmInfoTest
* 功能描述：固件信息查询
* 输入参数：T_Mts_Check_FirmInfoTest *ptFirmInfo
* 输出参数：T_Mts_Check_FirmInfoTest *ptFirmInfo
* 返 回 值： 0    -  执行成功
*            非0  -  执行失败
* 其它说明: 无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/06/06      V1.0       刘涛涛        初次创建
***********************************************************************/
SWORD32 mtsCapiFirmInfoTest(T_Mts_Check_FirmInfoTest *ptFirmInfo);
/**********************************************************************
* 函数名称：mtsCapiBrdPhyInfoTest
* 功能描述：单板物理信息
* 输入参数：T_Mts_Check_BrdPhyInfoTest *ptBrdPhyInfo
* 输出参数：T_Mts_Check_BrdPhyInfoTest *ptBrdPhyInfo
* 返 回 值： 0    -  执行成功
*            非0  -  执行失败
* 其它说明: 无

* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/06/06      V1.0       刘涛涛        初次创建
***********************************************************************/
SWORD32 mtsCapiBrdPhyInfoTest(T_Mts_Check_Brd_PhyInfoTest *ptBrdPhyInfo);
/**********************************************************************
* 函数名称：mtsCapiOnBoardClkTest
* 功能描述：单板上PLL和晶振测试
* 输入参数：T_Mts_Check_OnBoardClkTest *ptOnBoardClk
* 输出参数：T_Mts_Check_OnBoardClkTest *ptOnBoardClk
* 返 回 值：0    -  执行成功
*           非0  -  执行失败
* 其它说明: 无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/06/07      V1.0       刘涛涛        初次创建
***********************************************************************/
SWORD32 mtsCapiOnBoardClkTest(T_Mts_Check_OnBoardClkTest *ptOnBoardClk);
/**********************************************************************
* 函数名称：mtsCapiBrdSerialNumTest
* 功能描述：获取电子条码测试
* 输入参数：T_Mts_Check_BrdSerialNumTest *ptBrdSerialNum
* 输出参数：T_Mts_Check_BrdSerialNumTest *ptBrdSerialNum
* 返 回 值：0    -  执行成功
*           非0  -  执行失败
* 其它说明: 无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/06/07      V1.0       刘涛涛        初次创建
***********************************************************************/
SWORD32 mtsCapiBrdSerialNumTest(T_Mts_Check_BrdSerialNumTest *ptBrdSerialNum);
/**********************************************************************
* 函数名称：mtsCapiMacSelfTest
* 功能描述：MAC+PHY芯片自检
* 输入参数：T_Mts_Check_MacSelfTest *ptMacSelf
* 输出参数：T_Mts_Check_MacSelfTest *ptMacSelf
*           非0  -  执行失败
* 其它说明: 无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/06/08      V1.0       刘涛涛        初次创建
***********************************************************************/
SWORD32 mtsCapiMacSelfTest(T_Mts_Check_MacSelfTest *ptMacSelf);
/**********************************************************************
* 函数名称：mtsCapiDbgCircleTest
* 功能描述：端口流量测试设置
* 输入参数：T_Mts_Check_DbgCircleTest *ptDbgCircle
* 输出参数：T_Mts_Check_DbgCircleTest *ptDbgCircle
* 返 回 值：0    -  执行成功
*           非0  -  执行失败
* 其它说明: 无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/06/08      V1.0       刘涛涛        初次创建
***********************************************************************/
SWORD32 mtsCapiDbgCircleTest(T_Mts_Check_DbgCircleTest *ptDbgCircle);
/**********************************************************************
* 函数名称：mtsCapiHddTest
* 功能描述：硬盘测试
* 输入参数：T_Mts_Check_Hdd *ptHddTest
* 输出参数：T_Mts_Check_Hdd *ptHddTest
            aucResultExt：输出scanbox上硬盘PHYID
* 返 回 值：0    -  执行成功
*           非0  -  执行失败
* 其它说明: 无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/06/08      V1.0       刘涛涛        初次创建
***********************************************************************/
SWORD32 mtsCapiHddTest(T_Mts_Check_Hdd *ptHddTest);
/**********************************************************************
* 函数名称：mtsCapiPciBridgeTest
* 功能描述：PCI桥自检测试
* 输入参数：T_Mts_Check_PciBridgeTest *ptPciBridge
* 输出参数：T_Mts_Check_PciBridgeTest *ptPciBridge
* 返 回 值：0    -  执行成功
*           非0  -  执行失败
* 其它说明: 无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/06/08      V1.0       刘涛涛        初次创建
***********************************************************************/
SWORD32 mtsCapiPciBridgeTest(T_Mts_Check_PciBridgeTest *ptPciBridge);

/**********************************************************************
* 函数名称：GetSSDPdList
* 功能描述：获取SSD磁盘列表
* 输入参数：
* 输出参数：
* 其它说明：无
***********************************************************************/
SWORD32 GetSSDPdList(T_SSDPdList *ptSsdPdList);
/**********************************************************************
* 函数名称：CreateSSDCache
* 功能描述：创建SSD Cache
* 输入参数：
* 输出参数：
* 其它说明：无
***********************************************************************/
SWORD32 CreateSSDCache(T_CreateSSDCache *ptCreateSSDCache);
/**********************************************************************
* 函数名称：ExpandSSDCache
* 功能描述：SSD Cache
* 输入参数：
* 输出参数：
* 其它说明：无
***********************************************************************/
SWORD32 ExpandSSDCache(T_CreateSSDCache *ptCreateSSDCache);
/**********************************************************************
* 函数名称：DeleteSSDCache
* 功能描述：删除SSD Cache
* 输入参数：
* 输出参数：
* 返 回 值：  0      -   执行成功
*                              非0 - 执行失败
* 其它说明：无
***********************************************************************/
SWORD32 DeleteSSDCache(VOID);
/**********************************************************************
* 函数名称：GetSSDCacheInfo
* 功能描述：获取SSD Cache信息
* 输入参数：
* 输出参数：
* 返 回 值：  0      -   执行成功
*                              非0 - 执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetSSDCacheInfo(T_SSDCacheInfo *ptSSDCacheInfo);
/**********************************************************************
* 函数名称：SetSSDCacheSwitch
* 功能描述：设置SSD Cache开关
* 输入参数：
* 输出参数：
* 返 回 值：  0      -   执行成功
*                              非0 - 执行失败
* 其它说明：无
***********************************************************************/
SWORD32 SetSSDCacheSwitch(T_SSDCacheSwitch *ptSSDCacheSwitch);
/**********************************************************************
* SetVolSSDCacheSwitch
* 功能描述：设置卷的SSD Cache开关
* 输入参数：
* 输出参数：
* 返 回 值：  0      -   执行成功
*                              非0 - 执行失败
* 其它说明：无
***********************************************************************/
SWORD32 SetVolSSDCacheSwitch(T_SetVolSsdCacheSwitch *ptVolSSDCacheSwitch);
/**********************************************************************
* 函数名称：SetMportDriftIp
* 功能描述：配置(包括添加和修改)浮动IP
* 输入参数：
* 输出参数：无
* 返 回 值：    0      -   执行成功
*                           非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/08/18      V1.1       姚冬         初次创建
***********************************************************************/
SWORD32 SetMportDriftIp(T_MportDriftIp *ptDriftIp);
/**********************************************************************
* 函数名称：GetMportDriftIp
* 功能描述：获取浮动IP
* 输入参数：
* 输出参数：无
* 返 回 值：    0      -   执行成功
*                           非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/08/18      V1.1       姚冬         初次创建
***********************************************************************/
SWORD32 GetMportDriftIp(T_MportDriftIp *ptDriftIp);
/**********************************************************************
* 函数名称：DeleteMportDriftIp
* 功能描述：删除浮动IP
* 输入参数：
* 输出参数：无
* 返 回 值：    0      -   执行成功
*                           非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2014/08/18      V1.1       姚冬         初次创建
***********************************************************************/
SWORD32 DeleteMportDriftIp(void);
/**********************************************************************
* 函数名称：CheckHostAgentCondition
* 功能描述：根据卷名检查对应的映射组主机代理状态
* 输入参数：
* 输出参数：无
* 返 回 值：    0      -   执行成功
*                           非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2015/03/30      V1.1       尤永先         初次创建
***********************************************************************/
SWORD32 CheckHostAgentCondition(T_CheckAgentExist *ptCheckAgentCondition);
/**********************************************************************
* 函数名称：CreatCGMirror
* 功能描述：创建镜像一致性组
* 输入参数：
* 输出参数：无
* 返 回 值：    0      -   执行成功
*                           非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2015/01/13      V1.1       尤永先         初次创建
***********************************************************************/
SWORD32 CreateCGMirror(T_CreateCGMirror *ptCreateCGMirror);
/**********************************************************************
* 函数名称：DeleteCGMirror
* 功能描述：删除镜像一致性组
* 输入参数：
* 输出参数：无
* 返 回 值：    0      -   执行成功
*                           非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2015/01/13      V1.1       尤永先         初次创建
***********************************************************************/
SWORD32 DeleteCGMirror(T_CGMirrorName *ptCGMirrorName);
/**********************************************************************
* 函数名称：GetAllCGMirrorInfo
* 功能描述：查看镜像一致性组
* 输入参数：
* 输出参数：无
* 返 回 值：    0      -   执行成功
*                           非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2015/01/13      V1.1       尤永先         初次创建
***********************************************************************/
SWORD32 GetAllCGMirrorInfo(T_AllCGMirrorList *ptCGMirrorList);
/**********************************************************************
* 函数名称：GetMirrorInfoInCGrp
* 功能描述：查看一致性组里的镜像
* 输入参数：
* 输出参数：无
* 返 回 值：    0      -   执行成功
*                           非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2015/01/13      V1.1       尤永先         初次创建
***********************************************************************/
SWORD32 GetMirrorInfoInCGrp(T_MirrorInfoInCGrp *ptMirrorInfo);
/**********************************************************************
* 函数名称：AddMirrorToCGrp
* 功能描述：增加一致性组里的镜像
* 输入参数：
* 输出参数：无
* 返 回 值：    0      -   执行成功
*                           非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2015/01/13      V1.1       尤永先         初次创建
***********************************************************************/
SWORD32 AddMirrorToCGrp(T_MirrorInCGrp *ptMirrorInCGrp);
/**********************************************************************
* 函数名称：DelMirrorFromCGrp
* 功能描述：删除一致性组里的镜像
* 输入参数：
* 输出参数：无
* 返 回 值：    0      -   执行成功
*                           非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2015/01/13      V1.1       尤永先         初次创建
***********************************************************************/
SWORD32 DelMirrorFromCGrp(T_MirrorInCGrp *ptMirrorInCGrp);
/**********************************************************************
* 函数名称：GetCGFilterMirrorList
* 功能描述：获取所有满足条件的镜像列表
* 输入参数：
* 输出参数：无
* 返 回 值：    0      -   执行成功
*                           非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2015/01/13      V1.1       尤永先         初次创建
***********************************************************************/
SWORD32 GetCGFilterMirrorList(T_CGFilterMirrorList *ptMirrorList);
/**********************************************************************
* 函数名称：GetMirrorFilterList
* 功能描述：获取所有满足条件的镜像列表
                               用于创建一致性组镜像
* 输入参数：
* 输出参数：无
* 返 回 值：    0      -   执行成功
*                           非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2015/01/13      V1.1       尤永先         初次创建
***********************************************************************/
SWORD32 GetMirrorFilterList(T_MirrorFilterList *ptMirrorFilterList);
/**********************************************************************
* 函数名称：GetMirrorInfoInCGrp
* 功能描述：查看一致性组信息
* 输入参数：
* 输出参数：无
* 返 回 值：    0      -   执行成功
*                           非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2015/01/13      V1.1       尤永先         初次创建
***********************************************************************/
SWORD32 GetCGMirrorInfo(T_CGMirrorOverViewInfo *ptCGMirrorInfo);
/**********************************************************************
* 函数名称：setCGMirrorName()
* 功能描述：设置镜像一致性组名称
* 输入参数：
* 输出参数：无
* 返 回 值：    0      -   执行成功
*                           非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2015/01/26      V1.1       尤永先         初次创建
***********************************************************************/
SWORD32 setCGMirrorName(T_CGMirrorRename *ptCGMirrorRename);
/**********************************************************************
* 函数名称：SetCGMirrorPolicy
* 功能描述：修改镜像一致性组恢复策略
* 访问的表：
* 修改的表：
* 输入参数：
* 输出参数：
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2015/01/26      V1.1       尤永先         初次创建
***********************************************************************/
SWORD32 SetCGMirrorPolicy(T_CGMirrorPolicy *ptCGMirrorPolicy);
/**********************************************************************
* 函数名称：SetCGMirrorPriority
* 功能描述：修改镜像一致性组同步优先级
* 访问的表：
* 修改的表：
* 输入参数：
* 输出参数：
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2015/01/26     V1.1       尤永先         初次创建
***********************************************************************/
SWORD32 SetCGMirrorPriority(T_CGMirrorPriority *ptCGMirrorPriority);
/**********************************************************************
* 函数名称：SetCGMirrorSyncType
* 功能描述：修改镜像一致性组中镜像类型
* 访问的表：
* 修改的表：
* 输入参数：
* 输出参数：
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2015/01/26     V1.1       尤永先         初次创建
***********************************************************************/
SWORD32 SetCGMirrorSyncType(T_CGMirrorSyncType *ptCGMirrorSyncType);
/**********************************************************************
* 函数名称：FractureConsistencyGrp
* 功能描述：分离一致性组中的镜像
* 访问的表：
* 修改的表：
* 输入参数：
* 输出参数：
* 返 回 值：  0      -   执行成功
*             非0    -   执行失败
* 其它说明：无
* 修改日期        版本号     修改人       修改内容
* -----------------------------------------------
* 2015/01/26     V1.1       尤永先         初次创建
***********************************************************************/
SWORD32 FractureConsistencyGrp(T_ConsistencyGrpName *ptConsistencyGrpName);
/**********************************************************************
* 函数名称：SyncConsistencyGrp
* 功能描述：同步一致性组(支持全量/增量同步)
* 输入参数：
* 输出参数：
* 返 回 值： 0      -   执行成功
*            非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 SyncConsistencyGrp(T_ConsistencyGrpSync *ptConsistencyGrpSync);
/**********************************************************************
* 函数名称：ReverseSyncConsistencyGrp
* 功能描述：反同步一致性组(镜像/克隆)
* 输入参数：
* 输出参数：
* 返 回 值： 0      -   执行成功
*            非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 ReverseSyncConsistencyGrp(T_ConsistencyGrpName *ptConsistencyGrpName);
/**********************************************************************
* 函数名称：RestoreConsistencyGrp
* 功能描述：恢复一致性组(快照)
* 输入参数：
* 输出参数：
* 返 回 值： 0      -   执行成功
*            非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 RestoreConsistencyGrp(T_ConsistencyGrpName *ptConsistencyGrpName);
/**********************************************************************
* 函数名称：GetPwdinfo
* 功能描述：获取pdw信息
* 输入参数：
* 输出参数：
* 返 回 值： 0      -   执行成功
*            非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetPwdInfo(T_PWDInfo *ptPwdInfo);
/**********************************************************************
* 函数名称：GetFanInfo
* 功能描述：获取风扇信息
* 输入参数：
* 输出参数：
* 返 回 值： 0      -   执行成功
*            非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetFanInfo(T_AllFanInfo *ptFanInfo);
/**********************************************************************
* 函数名称：GetSubCardInfo
* 功能描述：获取子卡信息
* 输入参数：
* 输出参数：
* 返 回 值： 0      -   执行成功
*            非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetSubCardInfo(T_AllFuncCardInfo *ptFuncCardInfo);
/**********************************************************************
* 函数名称：GetSpr20CtrlInfo
* 功能描述：获取控制器信息
* 输入参数：
* 输出参数：
* 返 回 值： 0      -   执行成功
*            非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetSpr20CtrlInfo(T_SPR20CtrlInfo *ptCtrlInfo);
/**********************************************************************
* 函数名称：GetAllSensorInfo
* 功能描述：获取传感器信息
* 输入参数：
* 输出参数：
* 返 回 值： 0      -   执行成功
*            非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetAllSensorInfo(T_AllSensorInfo *ptSensorInfo);
/**********************************************************************
* 函数名称：SetBbumMainTenMode
* 功能描述：设置bbum
* 输入参数：
* 输出参数：
* 返 回 值： 0      -   执行成功
*            非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 SetBbumMainTenMode(WORD16 ptMainMode);
/**********************************************************************
* 函数名称：SetBbumAlarmMinValue
* 功能描述：设置bbum告警数最小值
* 输入参数：
* 输出参数：
* 返 回 值： 0      -   执行成功
*            非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 SetBbumAlarmMinValue(WORD16 ptAlarmValue);
/**********************************************************************
* 函数名称：SetBbumAlarmMinValue
* 功能描述：设置bbum的容量告警阈值
* 输入参数：
* 输出参数：
* 返 回 值： 0      -   执行成功
*            非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 SetBbumSizeAlarmValue(T_BbumSizeAlarmValue *ptSizeValue);
/**********************************************************************
* 函数名称：GetBbumInfo
* 功能描述：查询bbum信息
* 输入参数：
* 输出参数：
* 返 回 值： 0      -   执行成功
*            非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetBbumInfo(T_Mts_Check_Bbu_Info *ptBbumInfo);
/**********************************************************************
* 函数名称：GetAllEquBriInfo
* 功能描述：查询所有主柜和扩展柜的简要信息
* 输入参数：
* 输出参数：
* 返 回 值： 0      -   执行成功
*            非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetAllEquBriInfo(T_GetAllEquBriInfo *ptEquBri);
/**********************************************************************
* 函数名称：GetEncInfoList
* 功能描述：查询主柜或者扩展柜的详细信息
* 输入参数：
* 输出参数：
* 返 回 值： 0      -   执行成功
*            非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetEncInfoList(T_GetEncInfo *ptEncInfo);
/**********************************************************************
* 函数名称：GetAllEncList
* 功能描述：查询主柜或者扩展柜的箱体数和箱体id信息
* 输入参数：
* 输出参数：
* 返 回 值： 0      -   执行成功
*            非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetAllEncList(T_GetAllEncList *ptEncList);
/**********************************************************************
* 函数名称：GetCtrlCpuInfo
* 功能描述：查询cpu信息
* 输入参数：
* 输出参数：
* 返 回 值： 0      -   执行成功
*            非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetCtrlCpuInfo(T_GetCtrlAllCpuInfo *ptCpuInfo);
/**********************************************************************
* 函数名称：GetCtrlMemInfo
* 功能描述：查询内存信息
* 输入参数：
* 输出参数：
* 返 回 值： 0      -   执行成功
*            非0    -   执行失败
* 其它说明：无
***********************************************************************/
SWORD32 GetCtrlMemInfo(T_GetMemInfoList *ptMemInfo);

/**********************************************************************************/

typedef struct
{
    CHAR    acLogContent[MAX_LOG_CONTENT_LENGTH];
} _PACKED_1_ T_LogInfo;

/* 删除虚拟盘_Log */
SWORD32 DelVd_Log(T_VdName *ptVdName, T_LogInfo *ptLogInfo);
/* 创建虚拟盘_Log */
SWORD32 CreateVd_Log(T_CreateVd *ptCreateVd, T_LogInfo *ptLogInfo);
/* 扩容虚拟盘_Log */
SWORD32 ExpandVd_Log(T_VdExpand *ptVdExpand, T_LogInfo *ptLogInfo);
/* 变级虚拟盘_Log */
SWORD32 RelevelVd_Log(T_VdRelevel *ptVdRelevel, T_LogInfo *ptLogInfo);
/* 自动创建VD_Log */
SWORD32 AutoCreateVd_Log(T_AutoCreateVd *ptAutoCreateVd, T_LogInfo *ptLogInfo);
/* 自动重建VD_log */
SWORD32 SetVdAutoRebuild_Log(T_VdAutoRebuild *ptVdAutoRebuild, T_LogInfo *ptLogInfo);
/* 重建VD_log */
SWORD32 RebuildVd_Log(T_VdRebuild *ptVdRebuild, T_LogInfo *ptLogInfo);
/* 冻结VD_log */
SWORD32 FreezeVd_Log(T_VdName *ptVdName, T_LogInfo *ptLogInfo);
/* 解冻VD_log */
SWORD32 UnFreezeVd_Log(T_VdName *ptVdName, T_LogInfo *ptLogInfo);
/* regenerate parity vd_log */
SWORD32 RegenerateParityVd_Log(T_VdName *ptVdName, T_LogInfo *ptLogInfo);
/* 设置Vd节能模式_log */
SWORD32 SetVdEnergyConsrv_Log(T_VdEnergyConsrvMod *ptVdConsrvMode, T_LogInfo *ptLogInfo);
/* 重命名vd_log */
SWORD32 RenameVd_Log(T_VdRename *ptVdRename, T_LogInfo *ptLogInfo);
/* 创建拷贝_log */
SWORD32 CreateCvol_Log(T_CreateCvol *ptCreateCvol, T_LogInfo *ptLogInfo);
/* 分离拷贝_Log */
SWORD32 FractureCvol_Log(T_CvolName *ptCvolName, T_LogInfo *ptLogInfo);
/* 克隆同步_log */
SWORD32 SyncCvol_Log(T_CvolName *ptCvolName, T_LogInfo *ptLogInfo);
/* 反克隆同步_log */
SWORD32 ReverseSyncCvol_Log(T_CvolName *ptCvolName, T_LogInfo *ptLogInfo);
/* 拷贝重命名_log */
SWORD32 RenameCvol_Log(T_CvolRename *ptCvolRename, T_LogInfo *ptLogInfo);
/* 设置拷贝同步或者反同步的优先级_log */
SWORD32 SetCvolPriority_Log(T_CvolPriority *ptCvolPriority, T_LogInfo *ptLogInfo);
/* 设置克隆策略_log */
SWORD32 SetCvolPolicy_Log(T_CvolPolicy *ptCvolPolicy, T_LogInfo *ptLogInfo);
/* 设置是否启动保护拷贝_log */
SWORD32 SetCvolProtect_Log(T_CvolProtect *ptCvolProtect, T_LogInfo *ptLogInfo);
/* 删除拷贝_log */
SWORD32 DelCvol_Log(T_CvolName *ptCvolName, T_LogInfo *ptLogInfo);
/* 删除管理口的默认网关_log */
SWORD32 DeleteDefaultGateway_Log(T_CtrlId *ptCtrlId, T_LogInfo *ptLogInfo);
/* 创建远程镜像_Log */
SWORD32 CreateMirror_Log(T_CreateMirror *ptCreateMirror, T_LogInfo *ptLogInfo);
/* 修改远程镜像名称_Log */
SWORD32 SetMirrorName_Log(T_MirrorRename *ptMirrorRename, T_LogInfo *ptLogInfo);
/* 启动远程镜像增量同步_Log */
SWORD32 StartMirrorIncSync_Log(T_MirrorName *ptMirrorName, T_LogInfo *ptLogInfo);
/* 启动同步远程镜像_Log */
SWORD32 StartMirrorSync_Log(T_MirrorName *ptMirrorName, T_LogInfo *ptLogInfo);
/* 分离远程镜像_log */
SWORD32 FractureMirror_Log(T_MirrorName *ptMirrorName, T_LogInfo *ptLogInfo);
/* 修改远程镜像恢复策略_Log */
SWORD32 SetMirrorPolicy_Log(T_MirrorPolicy *ptMirrorPolicy, T_LogInfo *ptLogInfo);
/* 修改远程镜像优先级_Log */
SWORD32 SetMirrorPriority_Log(T_MirrorPriority *ptMirrorPriority, T_LogInfo *ptLogInfo);
/* 设置镜像逻辑连接_log */
SWORD32 SetFcMirrorConnect_Log(T_FcMirrorConnectInfo *ptFcMirrorConnectInfo, T_LogInfo *ptLogInfo);
/* 删除镜像逻辑连接_log */
SWORD32 DeleteFcMirrorConnect_Log(T_FcMirrorConnectInfo *ptFcMirrorConnectInfo, T_LogInfo *ptLogInfo);
/* 删除远程镜像_log */
SWORD32 DeleteMirror_Log(T_MirrorName *ptMirrorName, T_LogInfo *ptLogInfo);
/* 添加FCoE端口的VLAN信息_log */
SWORD32 SetFCoEPortVlan_Log(T_FCoEPortVlanInfo *ptFCoEPortVlanInfo, T_LogInfo *ptLogInfo);
/* 删除FCoE端口的VLAN信息_log */
SWORD32 DelFCoEPortVlan_Log(T_FCoEPortInfo *ptFCoEPortInfo, T_LogInfo *ptLogInfo);
/* 设置Iscsi 端口Mac 地址_log */
SWORD32 SetIscsiPortMac_Log(T_IscsiPortMac *ptIscsiPortMac, T_LogInfo *ptLogInfo);
/* 设置Iscsi 端口信息_log */
SWORD32 SetIscsiPortInfo_Log(T_IscsiPortSet *ptIscsiPortSet, T_LogInfo *ptLogInfo);
/* 添加Iscsi 端口路由信息_log */
SWORD32 AddIscsiPortRoute_Log(T_IscsiRouteInfo *ptIscsiRouteInfo, T_LogInfo *ptLogInfo);
/* 修改Iscsi Name_log */
SWORD32 SetIscsiName_Log(T_SetIscsiName *ptSetIscsiName, T_LogInfo *ptLogInfo);
/* 删除Iscsi 端口路由信息_log */
SWORD32 DelIscsiPortRoute_Log(T_IscsiPortRouteDel *ptIscsiPortRouteDel, T_LogInfo *ptLogInfo);
/* 添加chap双向配置_log */
SWORD32 AddIscsiMulChap_Log(T_IscsiChapAuthInf *ChapInfo, T_LogInfo *ptLogInfo);
/* 修改chap双向配置_log */
SWORD32 SetIscsiMulChap_Log(T_IscsiChapAuthInf *ChapInfo, T_LogInfo *ptLogInfo);
/* 删除chap双向配置_log */
SWORD32 DelIscsiMulChap_Log(T_IscsiChapAuthInf *ptMultualChapInfo, T_LogInfo *ptLogInfo);
/* 添加单向chap配置_log */
SWORD32 AddIscsiStationaryChap_Log(T_IscsiChapAuthInf *ChapInfo, T_LogInfo *ptLogInfo);
/* 设置单向chap配置_log */
SWORD32 SetIscsiStationaryChap_Log(T_IscsiChapAuthInf  *ChapInfo, T_LogInfo *ptLogInfo);
/* 设置单向chap开关_log */
SWORD32 SetIscsiStationaryChapSwitch_Log(WORD32 *udwStationaryChapSwitch, T_LogInfo *ptLogInfo);
/* 删除chap单向配置_log */
SWORD32 DelIscsiStationatyChap_Log(T_LogInfo *ptLogInfo);
/* 删除所有配置 */
SWORD32 DelAllIscsiMulChap_Log(T_LogInfo *ptLogInfo);
/* 创建映射组_Log */
SWORD32 CreateMapGrp_Log(T_MapGrpName *ptMapGrpName, T_LogInfo *ptLogInfo);
/* 重命名映射组 */
SWORD32 RenameMapGrp_Log(T_MapGrpRename *ptMapGrpRename, T_LogInfo *ptLogInfo);
/* 创建主机_log */
SWORD32 CreateHost_Log(T_CreateHost *pHost, T_LogInfo *ptLogInfo);
/* 增加主机到映射组_log */
SWORD32 AddHostToGrp_Log(T_HostInGrp *ptHostInGrp, T_LogInfo *ptLogInfo);
/* 增加主机到映射组_log */
SWORD32 SetMultiPathMode_Log(T_MultiPathMode *ptPathMode, T_LogInfo *ptLogInfo);
/* 将端口加入主机_log */
SWORD32 AddPortToHost_Log(T_AddPortToHost *ptAddPort, T_LogInfo *ptLogInfo);
/* 从主机中删除端口_log */
SWORD32 DelPortFromHost_Log(T_DelPortFrmHost *ptDelPort, T_LogInfo *ptLogInfo);
/* 删除主机_log */
SWORD32 DelHost_Log(T_HostAlias *ptDelHost, T_LogInfo *ptLogInfo);
/* 修改主机属性_log */
SWORD32 ModifyHostAttr_Log(T_ModifyHostAttr *ptModifyHostAttr, T_LogInfo *ptLogInfo);
/* 修改CHAP属性_log */
SWORD32 ModifyMutualChap_Log(T_MutualChap *ptMutualChap, T_LogInfo *ptLogInfo);
/* 从映射组中删除主机_log */
SWORD32 DelHostFromGrp_Log(T_HostInGrp *ptHostInGrp, T_LogInfo *ptLogInfo);
/* 删除映射组_Log */
SWORD32 DelMapGrp_Log(T_MapGrpName *ptMapGrpName, T_LogInfo *ptLogInfo);
/* 创建存储池_Log */
SWORD32 CreatePool_Log(T_CreatePool *ptCreatePool, T_LogInfo *ptLogInfo);
/* 池扩容_Log */
SWORD32 ExpandPool_Log(T_ExpandPool *ptExpandPool, T_LogInfo *ptLogInfo);
/* 修改存储池属性_Log */
SWORD32 ModifyPool_Log(T_ModifyPool *ptModifyPool, T_LogInfo *ptLogInfo);
/* 修改存储池节能属性_Log */
SWORD32 ModifyPoolEnergyConv_Log(T_ModifyPool *ptModifyPool, T_LogInfo *ptLogInfo);
/* 修改pool上卷的迁移策略_Log */
SWORD32 ModifyVolMovePolicy_Log(T_ModifyVolMovePolicy *ptModifyVolMovePolicy, T_LogInfo *ptLogInfo);
/* 停止pool上的数据迁移_log */
SWORD32 StopZtierMovingOnPool_Log(T_PoolName *ptPoolName, T_LogInfo *ptLogInfo);
/* 删除存储池_Log */
SWORD32 DelPool_Log(T_PoolName *ptPoolName, T_LogInfo *ptLogInfo);
/* 删除私有卷_log */
SWORD32 DelPriVol_Log(T_DelPriVol *ptDelPriVol, T_LogInfo *ptLogInfo);
/* 删除计划任务_log */
SWORD32 DelSchedule_Log(T_ScheduleDel *ptScheduleDel, T_LogInfo *ptLogInfo);
/* 创建快照_log */
SWORD32 CreateSvol_Log(T_SvolCreate *ptSvolCreate, T_LogInfo *ptLogInfo);
/* 重命名快照_log */
SWORD32 RenameSvol_Log(T_SvolRename *ptSvolRename, T_LogInfo *ptLogInfo);
/* 设置快照资源卷空间阈值和溢出策略_Log */
SWORD32 SetSvolThr_Log(T_SnapSetRepoAttr *ptSvolThr, T_LogInfo *ptLogInfo);
/* 快照删除_log */
SWORD32 DelSvol_Log(T_SvolName *ptSvolName, T_LogInfo *ptLogInfo);
/* 强制快照删除_log */
SWORD32 ForceDelSvol_Log(T_SvolName *ptSvolName, T_LogInfo *ptLogInfo);
/* 恢复源卷数据_log */
SWORD32 RestoreSvol_Log(T_SvolName *ptSvolName, T_LogInfo *ptLogInfo);
/* 创建卷_log */
SWORD32 CreateVol_Log(T_CreateVol *ptCreateVol, T_LogInfo *ptLogInfo);
/* 卷扩容_log */
SWORD32 ExpandVol_Log(T_ExpVol *ptExpVol, T_LogInfo *ptLogInfo);
/* vol校验_log */
SWORD32 VerifyVol_Log(T_VolVerify *ptVerifyVol, T_LogInfo *ptLogInfo);
/* 取消vol校验_log */
SWORD32 CancelVolVerify_Log(T_VolName *ptVolName, T_LogInfo *ptLogInfo);
/* 增加卷到映射组_log */
SWORD32 AddVolToGrp_Log(T_AddVolToGrp *ptAddVolToGrp, T_LogInfo *ptLogInfo);
/* 重命名卷_log */
SWORD32 RenameVol_Log(T_VolRename *ptVolRename, T_LogInfo *ptLogInfo);
/* 转换Thin卷为普通卷_log */
SWORD32 ChangeThinVol_Log(T_VolName *ptVolName, T_LogInfo *ptLogInfo);
/* 修改Thin卷属性_log */
SWORD32 ModifyThinVol_Log(T_ModifyThinVol *ptModifyThinVol, T_LogInfo *ptLogInfo);
/* 修改系统名称_log */
SWORD32 SetCtrlName_Log(T_CtrlInfo *ptCtrlInfo, T_LogInfo *ptLogInfo);
/* 重启控制器_log */
SWORD32 RestartCtrl_Log(T_CtrlAction *ptCtlAction, T_LogInfo *ptLogInfo);
/* 关闭控制器_log */
SWORD32 ShutdownCtrl_Log(T_CtrlAction *ptCtlAction, T_LogInfo *ptLogInfo);
/* 清除FC端口性能统计信息_log */
SWORD32 ClearFCPortStatisticInfo_Log(T_ClearFCPortStatisInfo *ptClearFcPortStatisInfo, T_LogInfo *ptLogInfo);
/* 关闭Grace_log */
SWORD32 GraceShutdown_Log(T_LogInfo *ptLogInfo);
/* 设置首选控制器_log */
SWORD32 SetVolPreferCtrl_Log(T_VolPreferCtrl *ptVolPreferCtrl, T_LogInfo *ptLogInfo);
/* 删除卷_log */
SWORD32 DelVol_Log(T_VolName *ptVolName, T_LogInfo *ptLogInfo);
/* 强制删除卷_log */
SWORD32 ForceDelVol_Log(T_VolName *ptVolName, T_LogInfo *ptLogInfo);
/* 删除映射组中的卷_log */
SWORD32 DelVolFromGrp_Log(T_DelVolFrmGrp *ptDelVolFromGrp, T_LogInfo *ptLogInfo);
/* 在存储池上创建卷_log */
SWORD32 CreateVolOnPool_Log(T_CreateVolOnPool *ptCreateVolOnPool, T_LogInfo *ptLogInfo);
/* 存储池上的虚拟卷扩容_log */
SWORD32 ExpandVolOnPool_Log(T_ExpVolCapacity *ptExpVolCapacity, T_LogInfo *ptLogInfo);
/* 设置卷cache属性_log */
SWORD32 SetVolCacheAttr_Log(T_VolCacheInfo *ptVolCacheInfo, T_LogInfo *ptLogInfo);
/* 设置cache全局配置_log */
SWORD32 SetCacheGlobalPolicy_Log(T_SetCacheGlbPolicy *ptSetCacheGlbPolicy, T_LogInfo *ptLogInfo);
/* 设置预设事件的Cache自动直写策略_log */
SWORD32 SetAutoWrThrEvt_Log(T_AutoWrThrPreSet *ptAutoWrThrPreSet, T_LogInfo *ptLogInfo);
/* 设置cache统计开关状态_log */
SWORD32 SetCacheStatSwitchStaus_Log(T_CacheIOStatSwitch *ptCacheIOStatSwitch, T_LogInfo *ptLogInfo);
/* 设置磁盘的硬件特性_log */
SWORD32 SetPdHwInfo_Log(T_PdSetHwInfo *ptPdSetHwInfo, T_LogInfo *ptLogInfo);
/* 设置磁盘坏块告警值（多少个坏块时告警）_log */
SWORD32 SetBadBlockWarnNum_Log(T_PdBadBlockWarnNum *ptPdBadBlockWarnNum, T_LogInfo *ptLogInfo);
/* 使能/禁止硬盘告警开关_log */
SWORD32 SetPdWarnSwitchStatus_Log(T_PdWarnSwitch *ptPdWarnSwitch, T_LogInfo *ptLogInfo);
/* 对当前控制器上的所有的卷进行IO 路径切换_Log */
SWORD32 SwitchAllVolOwnerCtrl_Log(T_SwitchAllVolIoPath *tSwitchInfo, T_LogInfo *ptLogInfo);
/* 回滚控制器上所有卷路径至优选控制器 */
SWORD32 RestoreAllVolPreferOwner_Log(T_LogInfo *ptLogInfo);
/* 把空闲盘转为热备盘_log */
SWORD32 SetPdUnusedToHotSpare_Log(T_PdId *ptPdId, T_LogInfo *ptLogInfo);
/* 把热备盘转为空闲盘_log */
SWORD32 SetPdHotSpareToUnsed_Log(T_PdId *ptPdId, T_LogInfo *ptLogInfo);
/* 设置为空闲盘_log */
SWORD32 SetPdToUnsed_Log(T_PdId *ptPdId, T_LogInfo *ptLogInfo);
/* 设置LUNIO统计开关状态_log */
SWORD32 SetLunIOStaticSwitchStatus_Log(T_LunIOStaticSwitch *ptLunIOStaticSwitch, T_LogInfo *ptLogInfo);
/* 设置isns的配置信息_log */
SWORD32 SetIsnsServerCfg_Log(T_IsnsInfo *ptIsnsServerCfg, T_LogInfo *ptLogInfo);
/* 设置isns的开关状态_log */
SWORD32  SetIsnsSwitchStatus_Log(T_IsnsInfo *ptIsnsServerCfg, T_LogInfo *ptLogInfo);
/* 设置磁盘扫描周期_log */
SWORD32 SetHddScanPeriod_Log(T_HddScanPeriod *ptHddScanPeriod, T_LogInfo *ptLogInfo);
/* 设置磁盘节能减排开关_log */
SWORD32 SetHddPowerSwitchStatus_Log(T_DmPowerStatSwitch *ptPowSwitch, T_LogInfo *ptLogInfo);
/* 设置系统网络相关的信息_log */
SWORD32 SetSystemNetCfg_Log(T_SystemNetCfg *ptSystemNetCfg, T_LogInfo *ptLogInfo);
/* 设置系统时间_log */
SWORD32 SetSysTime_Log(T_TimeInfo *ptTimeInfo, T_LogInfo *ptLogInfo);
/* 修改系统名称_log */
SWORD32 SetSysName_Log(T_SysNameInfo *ptSysName, T_LogInfo *ptLogInfo);
/* 系统信息采集_log */
SWORD32 CollectSysInfo_Log(T_SicCtrlAction *ptCtrlAction, T_LogInfo *ptLogInfo);
/* 设置时区_log */
SWORD32 SetTimeZone_Log(T_TimeZoneInfo *ptTimeZoneInfo, T_LogInfo *ptLogInfo);
/* 设置NTP服务器配置_log */
SWORD32 SetNtpCfg_Log(T_NtpInfo *ptNtpInfo, T_LogInfo *ptLogInfo);
/* 设置NTP服务开关_log */
SWORD32 SetNtpSwitch_Log(T_NtpSwitch *ptNtpSwitch, T_LogInfo *ptLogInfo);
/* 暂停/ 运行/ 删除后台任务_log */
SWORD32 SetTask_Log(T_TaskCtrl *PtTaskCtrl, T_LogInfo *ptLogInfo);
/* 设置ECC开关_log */
SWORD32 scsSetDiagEccSwitch_Log(T_DiagEccSwitch *ptDiagEccSwitch, T_LogInfo *ptLogInfo);
/* 设置统计开关状态_log */
SWORD32 SetStatAndWriteToCfg_Log(SWORD32 sdwStatFlag, T_LogInfo *ptLogInfo);
/* 设置统计周期间隔_log */
SWORD32 SetStatPeriod_Log(T_StatTime *ptStatTime, T_LogInfo *ptLogInfo);
/* 版本更新_log */
SWORD32 UpdateFirmware_Log(T_UpdateFirmware *ptUpdateFirmware, T_LogInfo *ptLogInfo);
/* 上传版本文件_log */
SWORD32 UploadPostProcess_Log(T_UploadPreInfo *ptUploadPreInfo, T_LogInfo *ptLogInfo);
/* 取消文件上传_log */
SWORD32 CancelUploadFile_Log(T_UploadFileName *ptFileName, T_LogInfo *ptLogInfo);
/* 导出配置文件 */
SWORD32 SaveConfigFile_Log(T_ConfigFile *ptConfigFile, T_LogInfo *ptLogInfo);
/* 导入数据库文件_log */
SWORD32 RestoreConfigFile_Log(T_ConfigFile *ptConfigFile, T_LogInfo *ptLogInfo);
/* 恢复出厂配置_log */
SWORD32 RestoreOriginalConfig_Log(T_LogInfo *ptLogInfo);
/* 控制磁盘灯闪烁(属于机框管理)_Log */
SWORD32 CtrlPdLed_Log(T_PdLed *ptPdLed, T_LogInfo *ptLogInfo);
/* 创建ssd cache_log */
SWORD32 CreateSSDCache_Log(T_CreateSSDCache *ptCreateSSDCache, T_LogInfo *ptLogInfo);
/* 删除ssd cache */
SWORD32 DeleteSSDCache_Log(T_LogInfo *ptLogInfo);
/* 设置ssd cache 开关_log */
SWORD32 SetSSDCacheSwitch_Log(T_SSDCacheSwitch *ptSSDCacheSwitch, T_LogInfo *ptLogInfo);
/* 设置卷ssd cache 开关_log */
SWORD32 SetVolSSDCacheSwitch_Log(T_SetVolSsdCacheSwitch *ptVolSSDCacheSwitch, T_LogInfo *ptLogInfo);
/* 扩展ssd cache_log */
SWORD32 ExpandSSDCache_Log(T_CreateSSDCache *ptCreateSSDCache, T_LogInfo *ptLogInfo);
/* 配置(包括添加和修改)浮动IP_log */
SWORD32 SetMportDriftIp_Log(T_MportDriftIp *ptDriftIp, T_LogInfo *ptLogInfo);
/* 删除浮动IP_log */
SWORD32 DeleteMportDriftIp_Log(T_LogInfo *ptLogInfo);
/* 开始硬盘扫描_Log */
SWORD32 StartHddScan_Log(T_HddScanPeriod *ptHddScanPeriod, T_LogInfo *ptLogInfo);
/* 停止硬盘扫描_Log */
SWORD32 StopHddScan_Log(T_LogInfo *ptLogInfo);
/* 启动磁盘SMART自检_Log */
SWORD32 ExecHddSmartTest_Log(T_DmSmartTestCtl *ptSmartTest, T_LogInfo *ptLogInfo);
/* 扫描磁盘 */
SWORD32 ScanPd_Log(T_PdScanCtrl *ptPdScanCtrl, T_LogInfo *ptLogInfo);
/* 导出内存中保存的控制器历史性能统计信息_Log */
SWORD32 ExportCtrlStatInfo_Log(T_SysInfoTarBall *ptSysInfoTarBall, T_LogInfo *ptLogInfo);
/* 导出内存中保存的端口性能统计信息_log */
SWORD32 ExportPortStatInfo_Log(T_SysInfoTarBall *ptSysInfoTarBall, T_LogInfo *ptLogInfo);
/* 导出内存中保存的LUN性能统计信息_log */
SWORD32 ExportLunStatInfo_Log(T_SysInfoTarBall *ptSysInfoTarBall, T_LogInfo *ptLogInfo);
/* 导出内存中保存的磁盘性能统计信息_log */
SWORD32 ExportDiskStatInfo_Log(T_SysInfoTarBall *ptSysInfoTarBall, T_LogInfo *ptLogInfo);
/* 添加远端Target网络信息_log */
SWORD32 AddRemoteTarget_Log(T_RmtTgtInfo *ptRmtTgtNetInfo, T_LogInfo *ptLogInfo);
/* 删除远端Target网络信息_log */
SWORD32 DelRemoteTarget_Log(T_RmtTgtInfo *ptRmtTgtNetInfo, T_LogInfo *ptLogInfo);
/* 添加远端Target网络链路信息_log */
SWORD32 AddRmtTgtLink_Log(T_RmtTgtLinkInfo *ptRmtTgtLink, T_LogInfo *ptLogInfo);
/* 刷新远端磁盘_log */
SWORD32 RefreshRemoteDisk_Log(T_LogInfo *ptLogInfo);
/* 删除远端Target网络链路信息_log */
SWORD32 DelRmtTgtLink_Log(T_RmtTgtLinkInfo *ptRmtTgtNetInfo, T_LogInfo *ptLogInfo);
/* 修改远端Target网络链路信息_log */
SWORD32 ModyRmtTgtLink_Log(T_RmtTgtLinkInfo *ptRmtTgtLink, T_LogInfo *ptLogInfo);
/* 创建远程复制_log */
SWORD32 CreateReCopy_Log(T_CreateReCopy *ptCreateReCopy, T_LogInfo *ptLogInfo);
/* 删除远程复制_log */
SWORD32 DelReCopy_Log(T_ReCopyName *ptReCopyName, T_LogInfo *ptLogInfo);
/* 修改远程复制名称_log */
SWORD32 SetRCopyName_Log(T_RCopyRename *ptRCopyRename, T_LogInfo *ptLogInfo);
/* 修改远程复制速率_log */
SWORD32 SetRCopySpeed_Log(T_RCopySyncSpeed *ptRCopySpeed, T_LogInfo *ptLogInfo);
/* 修改远程复制同步策略_log */
SWORD32 SetRCopyPolicy_Log(T_RCopyPolicy *ptRCopyPolicy, T_LogInfo *ptLogInfo);
/* 修改远程复制类型_log */
SWORD32 SetRCopyType_Log(T_RCopyType *ptRCopyType, T_LogInfo *ptLogInfo);
/* 发起远程复制同步任务_log */
SWORD32 StartReCopySync_Log(T_ReCopyName *ptReCopyName, T_LogInfo *ptLogInfo);
/* 远程复制添加目标卷_log */
SWORD32 AddReCopyDestVol_Log(T_RCopyDestVol *ptAddRCopyDestVol, T_LogInfo *ptLogInfo);
/* 远程复制删除目标卷_log */
SWORD32 DelReCopyDestVol_Log(T_RCopyDestVol *ptDelRCopyDestVol, T_LogInfo *ptLogInfo);
/* 远程复制设置标记_log */
SWORD32 SetReCopyFlag_Log(T_ReCopyName *ptReCopyName, T_LogInfo *ptLogInfo);
/* 创建bond_log */
SWORD32 CreateBond_Log(T_BondCreate *ptBondCreate, T_LogInfo *ptLogInfo);
/* 删除bond_log */
SWORD32 DeleteBond_Log(T_BondName *ptBondName, T_LogInfo *ptLogInfo);
/* 增加端口到bond中_log */
SWORD32 AddPortToBond_Log(T_BondPortSet *ptBondPortSet, T_LogInfo *ptLogInfo);
/* 从bond中移除端口_log */
SWORD32 RemovePortFromBond_Log(T_BondPortSet *ptBondPortSet, T_LogInfo *ptLogInfo);
/* 修改bond模式_log */
SWORD32 ModifyBondMode_Log(T_BondMode *ptBondMode, T_LogInfo *ptLogInfo);
/* 修改bond模式_log */
SWORD32 ModifyBondPolicy_Log(T_BondPolicy *ptBondPolicy, T_LogInfo *ptLogInfo);
/* 设置Bond口IP、Mask_log */
SWORD32 SetBondIpAddr_Log(T_BondNetInfo *ptBondNetInfo, T_LogInfo *ptLogInfo);
/* 设置Bond口MTU_log */
SWORD32 SetBondMtu_Log(T_BondMtu *ptBondMtu, T_LogInfo *ptLogInfo);
/* 设置Bond口MAC_log */
SWORD32 SetBondMac_Log(T_BondMac *ptBondMac, T_LogInfo *ptLogInfo);
/* 创建计划快照_log */
SWORD32 CreateSnapPlan_Log(T_SvolPlanCreate *ptSnapPlanCreate, T_LogInfo *ptLogInfo);
/* 创建计划快照_log */
SWORD32 DelSnapPlan_Log(T_SvolPlanName *ptSnapPlanName, T_LogInfo *ptLogInfo);
/* 更新计划快照_log */
SWORD32 UpdateSnapPlan_Log(T_SvolPlanUpdate *ptSnapPlanUpdate, T_LogInfo *ptLogInfo);
/*创建镜像一致性组*/
SWORD32 CreateCGMirror_Log(T_CreateCGMirror *ptCreateCGMirror,  T_LogInfo *ptLogInfo);
/*删除镜像一致性组*/
SWORD32 DeleteCGMirror_Log(T_CGMirrorName *ptCGMirrorName,  T_LogInfo *ptLogInfo);
/*添加镜像至一致性组*/
SWORD32 AddMirrorToCGrp_Log(T_MirrorInCGrp *ptMirrorInCGrp,  T_LogInfo *ptLogInfo);
/*移除镜像从一致性组*/
SWORD32 DelMirrorFromCGrp_Log(T_MirrorInCGrp *ptMirrorInCGrp,  T_LogInfo *ptLogInfo);
/*设置一致性组镜像名称*/
SWORD32 setCGMirrorName_Log(T_CGMirrorRename *ptCGMirrorRename,  T_LogInfo *ptLogInfo);
/*修改镜像一致性组恢复策略*/
SWORD32 SetCGMirrorPolicy_Log(T_CGMirrorPolicy *ptCGMirrorPolicy,  T_LogInfo *ptLogInfo);
/*修改镜像一致性组同步优先级*/
SWORD32 SetCGMirrorPriority_Log(T_CGMirrorPriority *ptCGMirrorPriority,  T_LogInfo *ptLogInfo);
/*修改镜像一致性组中镜像同步类型*/
SWORD32 SetCGMirrorSyncType_Log(T_CGMirrorSyncType *ptCGMirrorSyncType,  T_LogInfo *ptLogInfo);
/*分离远程镜像一致性组中的镜像*/
SWORD32 FractureConsistencyGrp_Log(T_ConsistencyGrpName *ptConsistencyGrpName,  T_LogInfo *ptLogInfo);
/*同步一致性组(支持全量/增量同步)*/
SWORD32 SyncConsistencyGrp_Log(T_ConsistencyGrpSync *ptConsistencyGrpSync,  T_LogInfo *ptLogInfo);
SWORD32 SetPdSlowSwitchStatus(T_DmPdSlowSwitch*ptPowSwitch);
SWORD32 SetPdSmartStatus(T_DmPdSlowSwitch*ptPowSwitch);
#endif
