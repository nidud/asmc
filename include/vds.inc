ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err<this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __vds_h__
__vds_h__ equ <>

ifndef __IEnumVdsObject_FWD_DEFINED__
__IEnumVdsObject_FWD_DEFINED__ equ <>
endif
ifndef __IVdsAsync_FWD_DEFINED__
__IVdsAsync_FWD_DEFINED__ equ <>
endif
ifndef __IVdsAdviseSink_FWD_DEFINED__
__IVdsAdviseSink_FWD_DEFINED__ equ <>
endif
ifndef __IVdsProvider_FWD_DEFINED__
__IVdsProvider_FWD_DEFINED__ equ <>
endif
ifndef __IVdsProviderSupport_FWD_DEFINED__
__IVdsProviderSupport_FWD_DEFINED__ equ <>
endif
ifndef __IVdsSwProvider_FWD_DEFINED__
__IVdsSwProvider_FWD_DEFINED__ equ <>
endif
ifndef __IVdsPack_FWD_DEFINED__
__IVdsPack_FWD_DEFINED__ equ <>
endif
ifndef __IVdsPack2_FWD_DEFINED__
__IVdsPack2_FWD_DEFINED__ equ <>
endif
ifndef __IVdsDisk_FWD_DEFINED__
__IVdsDisk_FWD_DEFINED__ equ <>
endif
ifndef __IVdsDisk2_FWD_DEFINED__
__IVdsDisk2_FWD_DEFINED__ equ <>
endif
ifndef __IVdsDiskOnline_FWD_DEFINED__
__IVdsDiskOnline_FWD_DEFINED__ equ <>
endif
ifndef __IVdsAdvancedDisk_FWD_DEFINED__
__IVdsAdvancedDisk_FWD_DEFINED__ equ <>
endif
ifndef __IVdsAdvancedDisk2_FWD_DEFINED__
__IVdsAdvancedDisk2_FWD_DEFINED__ equ <>
endif
ifndef __IVdsAdvancedDisk3_FWD_DEFINED__
__IVdsAdvancedDisk3_FWD_DEFINED__ equ <>
endif
ifndef __IVdsCreatePartitionEx_FWD_DEFINED__
__IVdsCreatePartitionEx_FWD_DEFINED__ equ <>
endif
ifndef __IVdsRemovable_FWD_DEFINED__
__IVdsRemovable_FWD_DEFINED__ equ <>
endif
ifndef __IVdsVolume_FWD_DEFINED__
__IVdsVolume_FWD_DEFINED__ equ <>
endif
ifndef __IVdsVolume2_FWD_DEFINED__
__IVdsVolume2_FWD_DEFINED__ equ <>
endif
ifndef __IVdsVolumeOnline_FWD_DEFINED__
__IVdsVolumeOnline_FWD_DEFINED__ equ <>
endif
ifndef __IVdsVolumePlex_FWD_DEFINED__
__IVdsVolumePlex_FWD_DEFINED__ equ <>
endif
ifndef __IVdsDisk3_FWD_DEFINED__
__IVdsDisk3_FWD_DEFINED__ equ <>
endif
ifndef __IVdsHwProvider_FWD_DEFINED__
__IVdsHwProvider_FWD_DEFINED__ equ <>
endif
ifndef __IVdsHwProviderType_FWD_DEFINED__
__IVdsHwProviderType_FWD_DEFINED__ equ <>
endif
ifndef __IVdsHwProviderType2_FWD_DEFINED__
__IVdsHwProviderType2_FWD_DEFINED__ equ <>
endif
ifndef __IVdsHwProviderStoragePools_FWD_DEFINED__
__IVdsHwProviderStoragePools_FWD_DEFINED__ equ <>
endif
ifndef __IVdsSubSystem_FWD_DEFINED__
__IVdsSubSystem_FWD_DEFINED__ equ <>
endif
ifndef __IVdsSubSystem2_FWD_DEFINED__
__IVdsSubSystem2_FWD_DEFINED__ equ <>
endif
ifndef __IVdsSubSystemNaming_FWD_DEFINED__
__IVdsSubSystemNaming_FWD_DEFINED__ equ <>
endif
ifndef __IVdsSubSystemIscsi_FWD_DEFINED__
__IVdsSubSystemIscsi_FWD_DEFINED__ equ <>
endif
ifndef __IVdsSubSystemInterconnect_FWD_DEFINED__
__IVdsSubSystemInterconnect_FWD_DEFINED__ equ <>
endif
ifndef __IVdsControllerPort_FWD_DEFINED__
__IVdsControllerPort_FWD_DEFINED__ equ <>
endif
ifndef __IVdsController_FWD_DEFINED__
__IVdsController_FWD_DEFINED__ equ <>
endif
ifndef __IVdsControllerControllerPort_FWD_DEFINED__
__IVdsControllerControllerPort_FWD_DEFINED__ equ <>
endif
ifndef __IVdsDrive_FWD_DEFINED__
__IVdsDrive_FWD_DEFINED__ equ <>
endif
ifndef __IVdsDrive2_FWD_DEFINED__
__IVdsDrive2_FWD_DEFINED__ equ <>
endif
ifndef __IVdsLun_FWD_DEFINED__
__IVdsLun_FWD_DEFINED__ equ <>
endif
ifndef __IVdsLun2_FWD_DEFINED__
__IVdsLun2_FWD_DEFINED__ equ <>
endif
ifndef __IVdsLunNaming_FWD_DEFINED__
__IVdsLunNaming_FWD_DEFINED__ equ <>
endif
ifndef __IVdsLunNumber_FWD_DEFINED__
__IVdsLunNumber_FWD_DEFINED__ equ <>
endif
ifndef __IVdsLunControllerPorts_FWD_DEFINED__
__IVdsLunControllerPorts_FWD_DEFINED__ equ <>
endif
ifndef __IVdsLunMpio_FWD_DEFINED__
__IVdsLunMpio_FWD_DEFINED__ equ <>
endif
ifndef __IVdsLunIscsi_FWD_DEFINED__
__IVdsLunIscsi_FWD_DEFINED__ equ <>
endif
ifndef __IVdsLunPlex_FWD_DEFINED__
__IVdsLunPlex_FWD_DEFINED__ equ <>
endif
ifndef __IVdsIscsiPortal_FWD_DEFINED__
__IVdsIscsiPortal_FWD_DEFINED__ equ <>
endif
ifndef __IVdsIscsiTarget_FWD_DEFINED__
__IVdsIscsiTarget_FWD_DEFINED__ equ <>
endif
ifndef __IVdsIscsiPortalGroup_FWD_DEFINED__
__IVdsIscsiPortalGroup_FWD_DEFINED__ equ <>
endif
ifndef __IVdsStoragePool_FWD_DEFINED__
__IVdsStoragePool_FWD_DEFINED__ equ <>
endif
ifndef __IVdsMaintenance_FWD_DEFINED__
__IVdsMaintenance_FWD_DEFINED__ equ <>
endif
ifndef __IVdsVdProvider_FWD_DEFINED__
__IVdsVdProvider_FWD_DEFINED__ equ <>
endif
ifndef __IVdsVDisk_FWD_DEFINED__
__IVdsVDisk_FWD_DEFINED__ equ <>
endif
ifndef __IVdsOpenVDisk_FWD_DEFINED__
__IVdsOpenVDisk_FWD_DEFINED__ equ <>
endif
ifndef __IVdsServiceLoader_FWD_DEFINED__
__IVdsServiceLoader_FWD_DEFINED__ equ <>
endif
ifndef __IVdsService_FWD_DEFINED__
__IVdsService_FWD_DEFINED__ equ <>
endif
ifndef __IVdsServiceUninstallDisk_FWD_DEFINED__
__IVdsServiceUninstallDisk_FWD_DEFINED__ equ <>
endif
ifndef __IVdsServiceHba_FWD_DEFINED__
__IVdsServiceHba_FWD_DEFINED__ equ <>
endif
ifndef __IVdsServiceIscsi_FWD_DEFINED__
__IVdsServiceIscsi_FWD_DEFINED__ equ <>
endif
ifndef __IVdsServiceInitialization_FWD_DEFINED__
__IVdsServiceInitialization_FWD_DEFINED__ equ <>
endif
ifndef __IVdsHbaPort_FWD_DEFINED__
__IVdsHbaPort_FWD_DEFINED__ equ <>
endif
ifndef __IVdsIscsiInitiatorAdapter_FWD_DEFINED__
__IVdsIscsiInitiatorAdapter_FWD_DEFINED__ equ <>
endif
ifndef __IVdsIscsiInitiatorPortal_FWD_DEFINED__
__IVdsIscsiInitiatorPortal_FWD_DEFINED__ equ <>
endif
ifndef __IVdsDiskPartitionMF_FWD_DEFINED__
__IVdsDiskPartitionMF_FWD_DEFINED__ equ <>
endif
ifndef __IVdsVolumeMF_FWD_DEFINED__
__IVdsVolumeMF_FWD_DEFINED__ equ <>
endif
ifndef __IVdsVolumeMF2_FWD_DEFINED__
__IVdsVolumeMF2_FWD_DEFINED__ equ <>
endif
ifndef __IVdsVolumeShrink_FWD_DEFINED__
__IVdsVolumeShrink_FWD_DEFINED__ equ <>
endif
ifndef __IVdsSubSystemImportTarget_FWD_DEFINED__
__IVdsSubSystemImportTarget_FWD_DEFINED__ equ <>
endif
ifndef __IVdsIscsiPortalLocal_FWD_DEFINED__
__IVdsIscsiPortalLocal_FWD_DEFINED__ equ <>
endif
ifndef __IVdsServiceSAN_FWD_DEFINED__
__IVdsServiceSAN_FWD_DEFINED__ equ <>
endif
ifndef __IVdsVolumeMF3_FWD_DEFINED__
__IVdsVolumeMF3_FWD_DEFINED__ equ <>
endif
ifndef __IVdsDiskPartitionMF2_FWD_DEFINED__
__IVdsDiskPartitionMF2_FWD_DEFINED__ equ <>
endif
ifndef __IVdsServiceSw_FWD_DEFINED__
__IVdsServiceSw_FWD_DEFINED__ equ <>
endif

include oaidl.inc
include vdssys.inc
include vdserr.inc
include vdslun.inc

include winapifamily.inc
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
include winapifamily.inc
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

VDS_OBJECT_ID		typedef GUID

VDS_OBJECT_TYPE		typedef SDWORD
VDS_OT_UNKNOWN		equ 0
VDS_OT_PROVIDER		equ 1
VDS_OT_PACK		equ 10
VDS_OT_VOLUME		equ 11
VDS_OT_VOLUME_PLEX	equ 12
VDS_OT_DISK		equ 13
VDS_OT_SUB_SYSTEM	equ 30
VDS_OT_CONTROLLER	equ 31
VDS_OT_DRIVE		equ 32
VDS_OT_LUN		equ 33
VDS_OT_LUN_PLEX		equ 34
VDS_OT_PORT		equ 35
VDS_OT_PORTAL		equ 36
VDS_OT_TARGET		equ 37
VDS_OT_PORTAL_GROUP	equ 38
VDS_OT_STORAGE_POOL	equ 39
VDS_OT_HBAPORT		equ 90
VDS_OT_INIT_ADAPTER	equ 91
VDS_OT_INIT_PORTAL	equ 92
VDS_OT_ASYNC		equ 100
VDS_OT_ENUM		equ 101
VDS_OT_VDISK		equ 200
VDS_OT_OPEN_VDISK	equ 201

VDS_PROVIDER_TYPE	typedef SDWORD
VDS_PT_UNKNOWN		equ 0
VDS_PT_SOFTWARE		equ 1
VDS_PT_HARDWARE		equ 2
VDS_PT_VIRTUALDISK	equ 3
VDS_PT_MAX		equ 4

VDS_PROVIDER_FLAG	typedef SDWORD
VDS_PF_DYNAMIC		equ 0x1
VDS_PF_INTERNAL_HARDWARE_PROVIDER equ 0x2
VDS_PF_ONE_DISK_ONLY_PER_PACK equ 0x4
VDS_PF_ONE_PACK_ONLINE_ONLY equ 0x8
VDS_PF_VOLUME_SPACE_MUST_BE_CONTIGUOUS equ 0x10
VDS_PF_SUPPORT_DYNAMIC	equ 0x80000000
VDS_PF_SUPPORT_FAULT_TOLERANT equ 0x40000000
VDS_PF_SUPPORT_DYNAMIC_1394 equ 0x20000000
VDS_PF_SUPPORT_MIRROR	equ 0x20
VDS_PF_SUPPORT_RAID5	equ 0x40

VDS_RECOVER_ACTION	typedef SDWORD
VDS_RA_UNKNOWN		equ 0
VDS_RA_REFRESH		equ 1
VDS_RA_RESTART		equ 2

VDS_NOTIFICATION_TARGET_TYPE typedef SDWORD
VDS_NTT_UNKNOWN		equ 0
VDS_NTT_PACK		equ VDS_OT_PACK
VDS_NTT_VOLUME		equ VDS_OT_VOLUME
VDS_NTT_DISK		equ VDS_OT_DISK
VDS_NTT_PARTITION	equ 60
VDS_NTT_DRIVE_LETTER	equ 61
VDS_NTT_FILE_SYSTEM	equ 62
VDS_NTT_MOUNT_POINT	equ 63
VDS_NTT_SUB_SYSTEM	equ VDS_OT_SUB_SYSTEM
VDS_NTT_CONTROLLER	equ VDS_OT_CONTROLLER
VDS_NTT_DRIVE		equ VDS_OT_DRIVE
VDS_NTT_LUN		equ VDS_OT_LUN
VDS_NTT_PORT		equ VDS_OT_PORT
VDS_NTT_PORTAL		equ VDS_OT_PORTAL
VDS_NTT_TARGET		equ VDS_OT_TARGET
VDS_NTT_PORTAL_GROUP	equ VDS_OT_PORTAL_GROUP
VDS_NTT_SERVICE		equ 200

VDS_NF_PACK_ARRIVE	equ ( 1 )
VDS_NF_PACK_DEPART	equ ( 2 )
VDS_NF_PACK_MODIFY	equ ( 3 )
VDS_NF_VOLUME_ARRIVE	equ ( 4 )
VDS_NF_VOLUME_DEPART	equ ( 5 )
VDS_NF_VOLUME_MODIFY	equ ( 6 )
VDS_NF_VOLUME_REBUILDING_PROGRESS equ ( 7 )
VDS_NF_DISK_ARRIVE	equ ( 8 )
VDS_NF_DISK_DEPART	equ ( 9 )
VDS_NF_DISK_MODIFY	equ ( 10 )
VDS_NF_PARTITION_ARRIVE equ ( 11 )
VDS_NF_PARTITION_DEPART equ ( 12 )
VDS_NF_PARTITION_MODIFY equ ( 13 )
VDS_NF_SUB_SYSTEM_ARRIVE equ ( 101 )
VDS_NF_SUB_SYSTEM_DEPART equ ( 102 )
VDS_NF_CONTROLLER_ARRIVE equ ( 103 )
VDS_NF_CONTROLLER_DEPART equ ( 104 )
VDS_NF_DRIVE_ARRIVE	equ ( 105 )
VDS_NF_DRIVE_DEPART	equ ( 106 )
VDS_NF_DRIVE_MODIFY	equ ( 107 )
VDS_NF_LUN_ARRIVE	equ ( 108 )
VDS_NF_LUN_DEPART	equ ( 109 )
VDS_NF_LUN_MODIFY	equ ( 110 )
VDS_NF_PORT_ARRIVE	equ ( 121 )
VDS_NF_PORT_DEPART	equ ( 122 )
VDS_NF_PORTAL_ARRIVE	equ ( 123 )
VDS_NF_PORTAL_DEPART	equ ( 124 )
VDS_NF_PORTAL_MODIFY	equ ( 125 )
VDS_NF_TARGET_ARRIVE	equ ( 126 )
VDS_NF_TARGET_DEPART	equ ( 127 )
VDS_NF_TARGET_MODIFY	equ ( 128 )
VDS_NF_PORTAL_GROUP_ARRIVE equ ( 129 )
VDS_NF_PORTAL_GROUP_DEPART equ ( 130 )
VDS_NF_PORTAL_GROUP_MODIFY equ ( 131 )
VDS_NF_SUB_SYSTEM_MODIFY equ ( 151 )
VDS_NF_DRIVE_LETTER_FREE equ ( 201 )
VDS_NF_DRIVE_LETTER_ASSIGN equ ( 202 )
VDS_NF_FILE_SYSTEM_MODIFY equ ( 203 )
VDS_NF_FILE_SYSTEM_FORMAT_PROGRESS equ ( 204 )
VDS_NF_MOUNT_POINTS_CHANGE equ ( 205 )
VDS_NF_FILE_SYSTEM_SHRINKING_PROGRESS equ ( 206 )
VDS_NF_SERVICE_OUT_OF_SYNC equ ( 301 )
VDS_NF_CONTROLLER_MODIFY equ ( 350 )
VDS_NF_CONTROLLER_REMOVED equ ( 351 )
VDS_NF_PORT_MODIFY	equ ( 352 )
VDS_NF_PORT_REMOVED	equ ( 353 )
VDS_NF_DRIVE_REMOVED	equ ( 354 )

VDS_PACK_NOTIFICATION	STRUC
ulEvent			ULONG ?
packId			VDS_OBJECT_ID <>
VDS_PACK_NOTIFICATION	ENDS

VDS_DISK_NOTIFICATION	STRUC
ulEvent			ULONG ?
diskId			VDS_OBJECT_ID <>
VDS_DISK_NOTIFICATION	ENDS

VDS_VOLUME_NOTIFICATION STRUC
ulEvent			ULONG ?
volumeId		VDS_OBJECT_ID <>
plexId			VDS_OBJECT_ID <>
ulPercentCompleted	ULONG ?
VDS_VOLUME_NOTIFICATION ENDS

VDS_PARTITION_NOTIFICATION STRUC
ulEvent			ULONG ?
diskId			VDS_OBJECT_ID <>
ullOffset		ULONGLONG ?
VDS_PARTITION_NOTIFICATION ENDS

VDS_SERVICE_NOTIFICATION STRUC
ulEvent			ULONG ?
action			VDS_RECOVER_ACTION ?
VDS_SERVICE_NOTIFICATION ENDS

VDS_DRIVE_LETTER_NOTIFICATION STRUC
ulEvent			ULONG ?
wcLetter		WCHAR ?
volumeId		VDS_OBJECT_ID <>
VDS_DRIVE_LETTER_NOTIFICATION ENDS

VDS_FILE_SYSTEM_NOTIFICATION STRUC
ulEvent			ULONG ?
volumeId		VDS_OBJECT_ID <>
dwPercentCompleted	dd ?
VDS_FILE_SYSTEM_NOTIFICATION ENDS

VDS_MOUNT_POINT_NOTIFICATION STRUC
ulEvent			ULONG ?
volumeId		VDS_OBJECT_ID <>
VDS_MOUNT_POINT_NOTIFICATION ENDS

VDS_SUB_SYSTEM_NOTIFICATION STRUC
ulEvent			ULONG ?
subSystemId		VDS_OBJECT_ID <>
VDS_SUB_SYSTEM_NOTIFICATION ENDS

VDS_CONTROLLER_NOTIFICATION STRUC
ulEvent			ULONG ?
controllerId		VDS_OBJECT_ID <>
VDS_CONTROLLER_NOTIFICATION ENDS

VDS_DRIVE_NOTIFICATION	STRUC
ulEvent			ULONG ?
driveId			VDS_OBJECT_ID <>
VDS_DRIVE_NOTIFICATION	ENDS

VDS_LUN_NOTIFICATION	STRUC
ulEvent			ULONG ?
LunId			VDS_OBJECT_ID <>
VDS_LUN_NOTIFICATION	ENDS

VDS_PORT_NOTIFICATION	STRUC
ulEvent			ULONG ?
portId			VDS_OBJECT_ID <>
VDS_PORT_NOTIFICATION	ENDS

VDS_PORTAL_NOTIFICATION STRUC
ulEvent			ULONG ?
portalId		VDS_OBJECT_ID <>
VDS_PORTAL_NOTIFICATION ENDS

VDS_TARGET_NOTIFICATION STRUC
ulEvent			ULONG ?
targetId		VDS_OBJECT_ID <>
VDS_TARGET_NOTIFICATION ENDS

VDS_PORTAL_GROUP_NOTIFICATION STRUC
ulEvent			ULONG ?
portalGroupId		VDS_OBJECT_ID <>
VDS_PORTAL_GROUP_NOTIFICATION ENDS

VDS_NOTIFICATION	STRUC
objectType		VDS_NOTIFICATION_TARGET_TYPE ?
UNION
 Pack			VDS_PACK_NOTIFICATION <>
 Disk			VDS_DISK_NOTIFICATION <>
 Volume			VDS_VOLUME_NOTIFICATION <>
 Partition		VDS_PARTITION_NOTIFICATION <>
 Letter			VDS_DRIVE_LETTER_NOTIFICATION <>
 FileSystem		VDS_FILE_SYSTEM_NOTIFICATION <>
 MountPoint		VDS_MOUNT_POINT_NOTIFICATION <>
 SubSystem		VDS_SUB_SYSTEM_NOTIFICATION <>
 Controller		VDS_CONTROLLER_NOTIFICATION <>
 Drive			VDS_DRIVE_NOTIFICATION <>
 Lun			VDS_LUN_NOTIFICATION <>
 Port			VDS_PORT_NOTIFICATION <>
 Portal			VDS_PORTAL_NOTIFICATION <>
 Target			VDS_TARGET_NOTIFICATION <>
 PortalGroup		VDS_PORTAL_GROUP_NOTIFICATION <>
 Service		VDS_SERVICE_NOTIFICATION <>
ENDS
VDS_NOTIFICATION	ENDS

VDS_ASYNC_OUTPUT_TYPE	typedef SDWORD
VDS_ASYNCOUT_UNKNOWN	equ 0
VDS_ASYNCOUT_CREATEVOLUME equ 1
VDS_ASYNCOUT_EXTENDVOLUME equ 2
VDS_ASYNCOUT_SHRINKVOLUME equ 3
VDS_ASYNCOUT_ADDVOLUMEPLEX equ 4
VDS_ASYNCOUT_BREAKVOLUMEPLEX equ 5
VDS_ASYNCOUT_REMOVEVOLUMEPLEX equ 6
VDS_ASYNCOUT_REPAIRVOLUMEPLEX equ 7
VDS_ASYNCOUT_RECOVERPACK equ 8
VDS_ASYNCOUT_REPLACEDISK equ 9
VDS_ASYNCOUT_CREATEPARTITION equ 10
VDS_ASYNCOUT_CLEAN	equ 11
VDS_ASYNCOUT_CREATELUN	equ 50
VDS_ASYNCOUT_ADDLUNPLEX equ 52
VDS_ASYNCOUT_REMOVELUNPLEX equ 53
VDS_ASYNCOUT_EXTENDLUN	equ 54
VDS_ASYNCOUT_SHRINKLUN	equ 55
VDS_ASYNCOUT_RECOVERLUN equ 56
VDS_ASYNCOUT_LOGINTOTARGET equ 60
VDS_ASYNCOUT_LOGOUTFROMTARGET equ 61
VDS_ASYNCOUT_CREATETARGET equ 62
VDS_ASYNCOUT_CREATEPORTALGROUP equ 63
VDS_ASYNCOUT_DELETETARGET equ 64
VDS_ASYNCOUT_ADDPORTAL	equ 65
VDS_ASYNCOUT_REMOVEPORTAL equ 66
VDS_ASYNCOUT_DELETEPORTALGROUP equ 67
VDS_ASYNCOUT_FORMAT	equ 101
VDS_ASYNCOUT_CREATE_VDISK equ 200
VDS_ASYNCOUT_ATTACH_VDISK equ 201
VDS_ASYNCOUT_COMPACT_VDISK equ 202
VDS_ASYNCOUT_MERGE_VDISK equ 203
VDS_ASYNCOUT_EXPAND_VDISK equ 204

VDS_ASYNC_OUTPUT	STRUC
_type			VDS_ASYNC_OUTPUT_TYPE ?
UNION
 STRUCT _cp
  ullOffset		ULONGLONG ?
  volumeId		VDS_OBJECT_ID <>
 ENDS
 STRUCT _cv
  pVolumeUnk		LPIUnknown ?
 ENDS
 STRUCT _bvp
  pVolumeUnk		LPIUnknown ?
 ENDS
 STRUCT _sv
  ullReclaimedBytes	ULONGLONG ?
 ENDS
 STRUCT _cl
  pLunUnk		LPIUnknown ?
 ENDS
 STRUCT _ct
  pTargetUnk		LPIUnknown ?
 ENDS
 STRUCT _cpg
  pPortalGroupUnk	LPIUnknown ?
 ENDS
 STRUCT _cvd
  pVDiskUnk		LPIUnknown ?
 ENDS
ENDS
VDS_ASYNC_OUTPUT	ENDS

VDS_ISCSI_PORTALGROUP_TAG typedef USHORT

VDS_IPADDRESS_TYPE	typedef SDWORD
VDS_IPT_TEXT		equ 0
VDS_IPT_IPV4		equ 1
VDS_IPT_IPV6		equ 2
VDS_IPT_EMPTY		equ 3

VDS_HEALTH		typedef SDWORD
VDS_H_UNKNOWN		equ 0
VDS_H_HEALTHY		equ 1
VDS_H_REBUILDING	equ 2
VDS_H_STALE		equ 3
VDS_H_FAILING		equ 4
VDS_H_FAILING_REDUNDANCY equ 5
VDS_H_FAILED_REDUNDANCY equ 6
VDS_H_FAILED_REDUNDANCY_FAILING equ 7
VDS_H_FAILED		equ 8
VDS_H_REPLACED		equ 9
VDS_H_PENDING_FAILURE	equ 10
VDS_H_DEGRADED		equ 11

VDS_TRANSITION_STATE	typedef SDWORD
VDS_TS_UNKNOWN		equ 0
VDS_TS_STABLE		equ 1
VDS_TS_EXTENDING	equ 2
VDS_TS_SHRINKING	equ 3
VDS_TS_RECONFIGING	equ 4
VDS_TS_RESTRIPING	equ 5

VDS_FILE_SYSTEM_TYPE	typedef SDWORD
VDS_FST_UNKNOWN		equ 0
VDS_FST_RAW		equ ( VDS_FST_UNKNOWN + 1 )
VDS_FST_FAT		equ ( VDS_FST_RAW + 1 )
VDS_FST_FAT32		equ ( VDS_FST_FAT + 1 )
VDS_FST_NTFS		equ ( VDS_FST_FAT32 + 1 )
VDS_FST_CDFS		equ ( VDS_FST_NTFS + 1 )
VDS_FST_UDF		equ ( VDS_FST_CDFS + 1 )
VDS_FST_EXFAT		equ ( VDS_FST_UDF + 1 )
VDS_FST_CSVFS		equ ( VDS_FST_EXFAT + 1 )
VDS_FST_REFS		equ ( VDS_FST_CSVFS + 1 )

VDS_HBAPORT_TYPE	typedef SDWORD
VDS_HPT_UNKNOWN		equ 1
VDS_HPT_OTHER		equ 2
VDS_HPT_NOTPRESENT	equ 3
VDS_HPT_NPORT		equ 5
VDS_HPT_NLPORT		equ 6
VDS_HPT_FLPORT		equ 7
VDS_HPT_FPORT		equ 8
VDS_HPT_EPORT		equ 9
VDS_HPT_GPORT		equ 10
VDS_HPT_LPORT		equ 20
VDS_HPT_PTP		equ 21

VDS_HBAPORT_STATUS	typedef SDWORD
VDS_HPS_UNKNOWN		equ 1
VDS_HPS_ONLINE		equ 2
VDS_HPS_OFFLINE		equ 3
VDS_HPS_BYPASSED	equ 4
VDS_HPS_DIAGNOSTICS	equ 5
VDS_HPS_LINKDOWN	equ 6
VDS_HPS_ERROR		equ 7
VDS_HPS_LOOPBACK	equ 8

VDS_HBAPORT_SPEED_FLAG	typedef SDWORD
VDS_HSF_UNKNOWN		equ 0
VDS_HSF_1GBIT		equ 0x1
VDS_HSF_2GBIT		equ 0x2
VDS_HSF_10GBIT		equ 0x4
VDS_HSF_4GBIT		equ 0x8
VDS_HSF_NOT_NEGOTIATED	equ ( 1 shl 15 )

VDS_PATH_STATUS		typedef SDWORD
VDS_MPS_UNKNOWN		equ 0
VDS_MPS_ONLINE		equ 1
VDS_MPS_FAILED		equ 5
VDS_MPS_STANDBY		equ 7

VDS_LOADBALANCE_POLICY_ENUM typedef SDWORD
VDS_LBP_UNKNOWN		equ 0
VDS_LBP_FAILOVER	equ 1
VDS_LBP_ROUND_ROBIN	equ 2
VDS_LBP_ROUND_ROBIN_WITH_SUBSET equ 3
VDS_LBP_DYN_LEAST_QUEUE_DEPTH equ 4
VDS_LBP_WEIGHTED_PATHS	equ 5
VDS_LBP_LEAST_BLOCKS	equ 6
VDS_LBP_VENDOR_SPECIFIC equ 7

VDS_PROVIDER_LBSUPPORT_FLAG typedef SDWORD
VDS_LBF_FAILOVER	equ 0x1
VDS_LBF_ROUND_ROBIN	equ 0x2
VDS_LBF_ROUND_ROBIN_WITH_SUBSET equ 0x4
VDS_LBF_DYN_LEAST_QUEUE_DEPTH equ 0x8
VDS_LBF_WEIGHTED_PATHS	equ 0x10
VDS_LBF_LEAST_BLOCKS	equ 0x20
VDS_LBF_VENDOR_SPECIFIC equ 0x40

VDS_VERSION_SUPPORT_FLAG typedef SDWORD
VDS_VSF_1_0		equ 0x1
VDS_VSF_1_1		equ 0x2
VDS_VSF_2_0		equ 0x4
VDS_VSF_2_1		equ 0x8
VDS_VSF_3_0		equ 0x10

VDS_HWPROVIDER_TYPE	typedef SDWORD
VDS_HWT_UNKNOWN		equ 0
VDS_HWT_PCI_RAID	equ 1
VDS_HWT_FIBRE_CHANNEL	equ 2
VDS_HWT_ISCSI		equ 3
VDS_HWT_SAS		equ 4
VDS_HWT_HYBRID		equ 5

VDS_ISCSI_LOGIN_TYPE	typedef SDWORD
VDS_ILT_MANUAL		equ 0
VDS_ILT_PERSISTENT	equ 1
VDS_ILT_BOOT		equ 2

VDS_ISCSI_AUTH_TYPE	typedef SDWORD
VDS_IAT_NONE		equ 0
VDS_IAT_CHAP		equ 1
VDS_IAT_MUTUAL_CHAP	equ 2

VDS_ISCSI_IPSEC_FLAG	typedef SDWORD
VDS_IIF_VALID		equ 0x1
VDS_IIF_IKE		equ 0x2
VDS_IIF_MAIN_MODE	equ 0x4
VDS_IIF_AGGRESSIVE_MODE equ 0x8
VDS_IIF_PFS_ENABLE	equ 0x10
VDS_IIF_TRANSPORT_MODE_PREFERRED equ 0x20
VDS_IIF_TUNNEL_MODE_PREFERRED equ 0x40

VDS_ISCSI_LOGIN_FLAG	typedef SDWORD
VDS_ILF_REQUIRE_IPSEC	equ 0x1
VDS_ILF_MULTIPATH_ENABLED equ 0x2

VDS_PATH_ID		STRUC
ullSourceId		ULONGLONG ?
ullPathId		ULONGLONG ?
VDS_PATH_ID		ENDS

VDS_WWN			STRUC
rguchWwn		UCHAR  8  dup(?)
VDS_WWN			ENDS

VDS_IPADDRESS		STRUC
_type			VDS_IPADDRESS_TYPE ?
ipv4Address		ULONG ?
ipv6Address		UCHAR  16  dup(?)
ulIpv6FlowInfo		ULONG ?
ulIpv6ScopeId		ULONG ?
wszTextAddress		WCHAR  257  dup(?)
ulPort			ULONG ?
VDS_IPADDRESS		ENDS
PVDS_IPADDRESS		typedef ptr VDS_IPADDRESS

VDS_ISCSI_IPSEC_KEY	STRUC
pKey			LPBYTE ?
ulKeySize		ULONG ?
VDS_ISCSI_IPSEC_KEY	ENDS

VDS_ISCSI_SHARED_SECRET STRUC
pSharedSecret		LPBYTE ?
ulSharedSecretSize	ULONG ?
VDS_ISCSI_SHARED_SECRET ENDS

VDS_HBAPORT_PROP	STRUC
id			VDS_OBJECT_ID <>
wwnNode			VDS_WWN <>
wwnPort			VDS_WWN <>
_type			VDS_HBAPORT_TYPE ?
status			VDS_HBAPORT_STATUS ?
ulPortSpeed		ULONG ?
ulSupportedPortSpeed	ULONG ?
VDS_HBAPORT_PROP	ENDS
PVDS_HBAPORT_PROP	typedef ptr VDS_HBAPORT_PROP

VDS_ISCSI_INITIATOR_ADAPTER_PROP STRUC
id			VDS_OBJECT_ID <>
pwszName		LPWSTR ?
VDS_ISCSI_INITIATOR_ADAPTER_PROP ENDS

VDS_ISCSI_INITIATOR_PORTAL_PROP STRUC
id			VDS_OBJECT_ID <>
address			VDS_IPADDRESS <>
ulPortIndex		ULONG ?
VDS_ISCSI_INITIATOR_PORTAL_PROP ENDS

VDS_PROVIDER_PROP	STRUC
id			VDS_OBJECT_ID <>
pwszName		LPWSTR ?
guidVersionId		GUID <>
pwszVersion		LPWSTR ?
_type			VDS_PROVIDER_TYPE ?
ulFlags			ULONG ?
ulStripeSizeFlags	ULONG ?
sRebuildPriority	dw ?
VDS_PROVIDER_PROP	ENDS

VDS_PATH_INFO		STRUC
pathId			VDS_PATH_ID <>
_type			VDS_HWPROVIDER_TYPE ?
status			VDS_PATH_STATUS ?
union
 controllerPortId	VDS_OBJECT_ID <>
 targetPortalId		VDS_OBJECT_ID <>
ends
union
 hbaPortId		VDS_OBJECT_ID <>
 initiatorAdapterId	VDS_OBJECT_ID <>
ends
union
 pHbaPortProp		PVDS_HBAPORT_PROP ?
 pInitiatorPortalIpAddr PVDS_IPADDRESS ?
ends
VDS_PATH_INFO		ENDS

VDS_PATH_POLICY		STRUC
pathId			VDS_PATH_ID <>
bPrimaryPath		BOOL ?
ulWeight		ULONG ?
VDS_PATH_POLICY		ENDS

externdef		__MIDL_itf_vds_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_vds_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEnumVdsObject_INTERFACE_DEFINED__
__IEnumVdsObject_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumVdsObject:IID

.comdef IEnumVdsObject

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif

ifndef __IVdsAsync_INTERFACE_DEFINED__
__IVdsAsync_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsAsync:IID

.comdef IVdsAsync

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Cancel		proc
    _Wait		proc :ptr, :ptr
    QueryStatus		proc :ptr, :ptr
    .ends

endif

ifndef __IVdsAdviseSink_INTERFACE_DEFINED__
__IVdsAdviseSink_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsAdviseSink:IID

.comdef IVdsAdviseSink

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    OnNotify		proc :LONG, :ptr
    .ends

endif

ifndef __IVdsProvider_INTERFACE_DEFINED__
__IVdsProvider_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsProvider:IID

.comdef IVdsProvider

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties	proc :ptr
    .ends

endif

ifndef __IVdsProviderSupport_INTERFACE_DEFINED__
__IVdsProviderSupport_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsProviderSupport:IID

.comdef IVdsProviderSupport

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetVersionSupport	proc :ptr
    .ends

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)


VDS_PACK_STATUS		typedef SDWORD
VDS_PS_UNKNOWN		equ 0
VDS_PS_ONLINE		equ 1
VDS_PS_OFFLINE		equ 4

VDS_PACK_FLAG		typedef SDWORD
VDS_PKF_FOREIGN		equ 0x1
VDS_PKF_NOQUORUM	equ 0x2
VDS_PKF_POLICY		equ 0x4
VDS_PKF_CORRUPTED	equ 0x8
VDS_PKF_ONLINE_ERROR	equ 0x10

VDS_DISK_STATUS		typedef SDWORD
VDS_DS_UNKNOWN		equ 0
VDS_DS_ONLINE		equ 1
VDS_DS_NOT_READY	equ 2
VDS_DS_NO_MEDIA		equ 3
VDS_DS_FAILED		equ 5
VDS_DS_MISSING		equ 6
VDS_DS_OFFLINE		equ 4

VDS_PARTITION_STYLE	typedef SDWORD
VDS_PST_UNKNOWN		equ 0
VDS_PST_MBR		equ 1
VDS_PST_GPT		equ 2

VDS_DISK_FLAG		typedef SDWORD
VDS_DF_AUDIO_CD		equ 0x1
VDS_DF_HOTSPARE		equ 0x2
VDS_DF_RESERVE_CAPABLE	equ 0x4
VDS_DF_MASKED		equ 0x8
VDS_DF_STYLE_CONVERTIBLE equ 0x10
VDS_DF_CLUSTERED	equ 0x20
VDS_DF_READ_ONLY	equ 0x40
VDS_DF_SYSTEM_DISK	equ 0x80
VDS_DF_BOOT_DISK	equ 0x100
VDS_DF_PAGEFILE_DISK	equ 0x200
VDS_DF_HIBERNATIONFILE_DISK equ 0x400
VDS_DF_CRASHDUMP_DISK	equ 0x800
VDS_DF_HAS_ARC_PATH	equ 0x1000
VDS_DF_DYNAMIC		equ 0x2000
VDS_DF_BOOT_FROM_DISK	equ 0x4000
VDS_DF_CURRENT_READ_ONLY equ 0x8000
VDS_DF_REFS_NOT_SUPPORTED equ 0x10000

VDS_PARTITION_FLAG	typedef SDWORD
VDS_PTF_SYSTEM		equ 0x1

VDS_LUN_RESERVE_MODE	typedef SDWORD
VDS_LRM_NONE		equ 0
VDS_LRM_EXCLUSIVE_RW	equ 1
VDS_LRM_EXCLUSIVE_RO	equ 2
VDS_LRM_SHARED_RO	equ 3
VDS_LRM_SHARED_RW	equ 4

VDS_VOLUME_STATUS	typedef SDWORD
VDS_VS_UNKNOWN		equ 0
VDS_VS_ONLINE		equ 1
VDS_VS_NO_MEDIA		equ 3
VDS_VS_FAILED		equ 5
VDS_VS_OFFLINE		equ 4

VDS_VOLUME_TYPE		typedef SDWORD
VDS_VT_UNKNOWN		equ 0
VDS_VT_SIMPLE		equ 10
VDS_VT_SPAN		equ 11
VDS_VT_STRIPE		equ 12
VDS_VT_MIRROR		equ 13
VDS_VT_PARITY		equ 14

VDS_VOLUME_FLAG		typedef SDWORD
VDS_VF_SYSTEM_VOLUME	equ 0x1
VDS_VF_BOOT_VOLUME	equ 0x2
VDS_VF_ACTIVE		equ 0x4
VDS_VF_READONLY		equ 0x8
VDS_VF_HIDDEN		equ 0x10
VDS_VF_CAN_EXTEND	equ 0x20
VDS_VF_CAN_SHRINK	equ 0x40
VDS_VF_PAGEFILE		equ 0x80
VDS_VF_HIBERNATION	equ 0x100
VDS_VF_CRASHDUMP	equ 0x200
VDS_VF_INSTALLABLE	equ 0x400
VDS_VF_LBN_REMAP_ENABLED equ 0x800
VDS_VF_FORMATTING	equ 0x1000
VDS_VF_NOT_FORMATTABLE	equ 0x2000
VDS_VF_NTFS_NOT_SUPPORTED equ 0x4000
VDS_VF_FAT32_NOT_SUPPORTED equ 0x8000
VDS_VF_FAT_NOT_SUPPORTED equ 0x10000
VDS_VF_NO_DEFAULT_DRIVE_LETTER equ 0x20000
VDS_VF_PERMANENTLY_DISMOUNTED equ 0x40000
VDS_VF_PERMANENT_DISMOUNT_SUPPORTED equ 0x80000
VDS_VF_SHADOW_COPY	equ 0x100000
VDS_VF_FVE_ENABLED	equ 0x200000
VDS_VF_DIRTY		equ 0x400000
VDS_VF_REFS_NOT_SUPPORTED equ 0x800000
VDS_VF_BACKS_BOOT_VOLUME equ 0x1000000
VDS_VF_BACKED_BY_WIM_IMAGE equ 0x2000000

VDS_VOLUME_PLEX_TYPE	typedef SDWORD
VDS_VPT_UNKNOWN		equ 0
VDS_VPT_SIMPLE		equ VDS_VT_SIMPLE
VDS_VPT_SPAN		equ VDS_VT_SPAN
VDS_VPT_STRIPE		equ VDS_VT_STRIPE
VDS_VPT_PARITY		equ VDS_VT_PARITY

VDS_VOLUME_PLEX_STATUS	typedef SDWORD
VDS_VPS_UNKNOWN		equ 0
VDS_VPS_ONLINE		equ 1
VDS_VPS_NO_MEDIA	equ 3
VDS_VPS_FAILED		equ 5

VDS_DISK_EXTENT_TYPE	typedef SDWORD
VDS_DET_UNKNOWN		equ 0
VDS_DET_FREE		equ 1
VDS_DET_DATA		equ 2
VDS_DET_OEM		equ 3
VDS_DET_ESP		equ 4
VDS_DET_MSR		equ 5
VDS_DET_LDM		equ 6
VDS_DET_CLUSTER		equ 7
VDS_DET_UNUSABLE	equ 0x7fff

VDS_PACK_PROP		STRUC
id			VDS_OBJECT_ID <>
pwszName		LPWSTR ?
status			VDS_PACK_STATUS ?
ulFlags			ULONG ?
VDS_PACK_PROP		ENDS

PVDS_PACK_PROP		typedef ptr VDS_PACK_PROP

VDS_DISK_PROP		STRUC
id			VDS_OBJECT_ID <>
status			VDS_DISK_STATUS ?
ReserveMode		VDS_LUN_RESERVE_MODE ?
health			VDS_HEALTH ?
dwDeviceType		dd ?
dwMediaType		dd ?
ullSize			ULONGLONG ?
ulBytesPerSector	ULONG ?
ulSectorsPerTrack	ULONG ?
ulTracksPerCylinder	ULONG ?
ulFlags			ULONG ?
BusType			VDS_STORAGE_BUS_TYPE ?
PartitionStyle		VDS_PARTITION_STYLE ?
union
 dwSignature		DWORD ?
 DiskGuid		GUID <>
ends
pwszDiskAddress		LPWSTR ?
pwszName		LPWSTR ?
pwszFriendlyName	LPWSTR ?
pwszAdaptorName		LPWSTR ?
pwszDevicePath		LPWSTR ?
VDS_DISK_PROP		ENDS

PVDS_DISK_PROP		typedef ptr VDS_DISK_PROP

VDS_DISK_OFFLINE_REASON typedef SDWORD
VDSDiskOfflineReasonNone equ 0
VDSDiskOfflineReasonPolicy equ 1
VDSDiskOfflineReasonRedundantPath equ 2
VDSDiskOfflineReasonSnapshot equ 3
VDSDiskOfflineReasonCollision equ 4
VDSDiskOfflineReasonResourceExhaustion equ 5
VDSDiskOfflineReasonWriteFailure equ 6
VDSDiskOfflineReasonDIScan equ 7

VDS_DISK_PROP2		STRUC
id			VDS_OBJECT_ID <>
status			VDS_DISK_STATUS ?
OfflineReason		VDS_DISK_OFFLINE_REASON ?
ReserveMode		VDS_LUN_RESERVE_MODE ?
health			VDS_HEALTH ?
dwDeviceType		dd ?
dwMediaType		dd ?
ullSize			ULONGLONG ?
ulBytesPerSector	ULONG ?
ulSectorsPerTrack	ULONG ?
ulTracksPerCylinder	ULONG ?
ulFlags			ULONG ?
BusType			VDS_STORAGE_BUS_TYPE ?
PartitionStyle		VDS_PARTITION_STYLE ?
union
 dwSignature		DWORD ?
 DiskGuid		GUID <>
ends
pwszDiskAddress		LPWSTR ?
pwszName		LPWSTR ?
pwszFriendlyName	LPWSTR ?
pwszAdaptorName		LPWSTR ?
pwszDevicePath		LPWSTR ?
pwszLocationPath	LPWSTR ?
VDS_DISK_PROP2		ENDS
PVDS_DISK_PROP2		typedef ptr VDS_DISK_PROP2

VDS_ADVANCEDDISK_PROP	STRUC
pwszId			LPWSTR ?
pwszPathname		LPWSTR ?
pwszLocation		LPWSTR ?
pwszFriendlyName	LPWSTR ?
pswzIdentifier		LPWSTR ?
usIdentifierFormat	dw ?
ulNumber		ULONG ?
pwszSerialNumber	LPWSTR ?
pwszFirmwareVersion	LPWSTR ?
pwszManufacturer	LPWSTR ?
pwszModel		LPWSTR ?
ullTotalSize		ULONGLONG ?
ullAllocatedSize	ULONGLONG ?
ulLogicalSectorSize	ULONG ?
ulPhysicalSectorSize	ULONG ?
ulPartitionCount	ULONG ?
status			VDS_DISK_STATUS ?
health			VDS_HEALTH ?
BusType			VDS_STORAGE_BUS_TYPE ?
PartitionStyle		VDS_PARTITION_STYLE ?
union
 dwSignature		DWORD ?
 DiskGuid		GUID <>
ends
ulFlags			ULONG ?
dwDeviceType		dd ?
VDS_ADVANCEDDISK_PROP	ENDS
PVDS_ADVANCEDDISK_PROP	typedef ptr VDS_ADVANCEDDISK_PROP

VDS_VOLUME_PROP		STRUC
id			VDS_OBJECT_ID <>
_type			VDS_VOLUME_TYPE ?
status			VDS_VOLUME_STATUS ?
health			VDS_HEALTH ?
TransitionState		VDS_TRANSITION_STATE ?
ullSize			ULONGLONG ?
ulFlags			ULONG ?
RecommendedFileSystemType VDS_FILE_SYSTEM_TYPE ?
pwszName		LPWSTR ?
VDS_VOLUME_PROP		ENDS
PVDS_VOLUME_PROP	typedef ptr VDS_VOLUME_PROP

VDS_VOLUME_PROP2	STRUC
id			VDS_OBJECT_ID <>
_type			VDS_VOLUME_TYPE ?
status			VDS_VOLUME_STATUS ?
health			VDS_HEALTH ?
TransitionState		VDS_TRANSITION_STATE ?
ullSize			ULONGLONG ?
ulFlags			ULONG ?
RecommendedFileSystemType VDS_FILE_SYSTEM_TYPE ?
cbUniqueId		ULONG ?
pwszName		LPWSTR ?
pUniqueId		LPBYTE ?
VDS_VOLUME_PROP2	ENDS
PVDS_VOLUME_PROP2	typedef ptr VDS_VOLUME_PROP2

VDS_VOLUME_PLEX_PROP	STRUC
id			VDS_OBJECT_ID <>
_type			VDS_VOLUME_PLEX_TYPE ?
status			VDS_VOLUME_PLEX_STATUS ?
health			VDS_HEALTH ?
TransitionState		VDS_TRANSITION_STATE ?
ullSize			ULONGLONG ?
ulStripeSize		ULONG ?
ulNumberOfMembers	ULONG ?
VDS_VOLUME_PLEX_PROP	ENDS
PVDS_VOLUME_PLEX_PROP	typedef ptr VDS_VOLUME_PLEX_PROP

VDS_DISK_EXTENT		STRUC
diskId			VDS_OBJECT_ID <>
_type			VDS_DISK_EXTENT_TYPE ?
ullOffset		ULONGLONG ?
ullSize			ULONGLONG ?
volumeId		VDS_OBJECT_ID <>
plexId			VDS_OBJECT_ID <>
memberIdx		ULONG ?
VDS_DISK_EXTENT		ENDS
PVDS_DISK_EXTENT	typedef ptr VDS_DISK_EXTENT

VDS_DISK_FREE_EXTENT	STRUC
diskId			VDS_OBJECT_ID <>
ullOffset		ULONGLONG ?
ullSize			ULONGLONG ?
VDS_DISK_FREE_EXTENT	ENDS
PVDS_DISK_FREE_EXTENT	typedef ptr VDS_DISK_FREE_EXTENT

VDS_INPUT_DISK		STRUC
diskId			VDS_OBJECT_ID <>
ullSize			ULONGLONG ?
plexId			VDS_OBJECT_ID <>
memberIdx		ULONG ?
VDS_INPUT_DISK		ENDS

GPT_PARTITION_NAME_LENGTH equ 36
VDS_PARTITION_INFO_GPT	STRUC
partitionType		GUID <>
partitionId		GUID <>
attributes		ULONGLONG ?
_name			WCHAR 36 dup(?)
VDS_PARTITION_INFO_GPT	ENDS

VDS_PARTITION_INFO_MBR	STRUC
partitionType		db ?
bootIndicator		BOOLEAN ?
recognizedPartition	BOOLEAN ?
hiddenSectors		dd ?
VDS_PARTITION_INFO_MBR	ENDS

VDS_PARTITION_PROP	STRUC
PartitionStyle		VDS_PARTITION_STYLE ?
ulFlags			ULONG ?
ulPartitionNumber	ULONG ?
ullOffset		ULONGLONG ?
ullSize			ULONGLONG ?
union
 Mbr			VDS_PARTITION_INFO_MBR <>
 Gpt			VDS_PARTITION_INFO_GPT <>
ends
VDS_PARTITION_PROP	ENDS

tag_VDS_PARTITION_STYLE typedef SDWORD
VDS_PARTITION_STYLE_MBR equ 0
VDS_PARTITION_STYLE_GPT equ ( VDS_PARTITION_STYLE_MBR + 1 )
VDS_PARTITION_STYLE_RAW equ ( VDS_PARTITION_STYLE_GPT + 1 )

VDS_PARTITION_INFORMATION_EX STRUC
dwPartitionStyle	VDS_PARTITION_STYLE ?
ullStartingOffset	ULONGLONG ?
ullPartitionLength	ULONGLONG ?
dwPartitionNumber	dd ?
bRewritePartition	BOOLEAN ?
union
 Mbr			VDS_PARTITION_INFO_MBR <>
 Gpt			VDS_PARTITION_INFO_GPT <>
ends
VDS_PARTITION_INFORMATION_EX ENDS

CREATE_PARTITION_PARAMETERS STRUC
style			VDS_PARTITION_STYLE ?
union
 struc MbrPartInfo
  partitionType		db ?
  bootIndicator		BOOLEAN ?
 ends
 struc GptPartInfo
  partitionType		GUID <>
  partitionId		GUID <>
  attributes		ULONGLONG ?
  _name			WCHAR 36 dup(?)
 ends
ends
CREATE_PARTITION_PARAMETERS ENDS

CHANGE_ATTRIBUTES_PARAMETERS STRUC
style			VDS_PARTITION_STYLE ?
union
 struc MbrPartInfo
  bootIndicator		BOOLEAN ?
 ends
 struc GptPartInfo
  attributes		ULONGLONG ?
 ends
ends
CHANGE_ATTRIBUTES_PARAMETERS ENDS

CHANGE_PARTITION_TYPE_PARAMETERS STRUC
style			VDS_PARTITION_STYLE ?
union
 struc MbrPartInfo
  partitionType		db ?
 ends
 struc GptPartInfo
  partitionType		GUID <>
 ends
ends
CHANGE_PARTITION_TYPE_PARAMETERS ENDS


externdef		__MIDL_itf_vds_0000_0005_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_vds_0000_0005_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IVdsSwProvider_INTERFACE_DEFINED__
__IVdsSwProvider_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsSwProvider:IID

.comdef IVdsSwProvider

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    QueryPacks		proc :ptr
    CreatePack		proc :ptr
    .ends

endif

ifndef __IVdsPack_INTERFACE_DEFINED__
__IVdsPack_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsPack:IID

.comdef IVdsPack

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties	proc :ptr
    GetProvider		proc :ptr
    QueryVolumes	proc :ptr
    QueryDisks		proc :ptr
    CreateVolume	proc :VDS_VOLUME_TYPE
    AddDisk		proc :VDS_OBJECT_ID, :VDS_PARTITION_STYLE, :BOOL
    MigrateDisks	proc :ptr, :ptr
    ReplaceDisk		proc :VDS_OBJECT_ID, :VDS_OBJECT_ID, :ptr
    RemoveMissingDisk	proc :VDS_OBJECT_ID
    Recover		proc :ptr
    .ends

endif

ifndef __IVdsPack2_INTERFACE_DEFINED__
__IVdsPack2_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsPack2:IID

.comdef IVdsPack2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    CreateVolume2	proc :VDS_VOLUME_TYPE
    .ends

endif

ifndef __IVdsDisk_INTERFACE_DEFINED__
__IVdsDisk_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsDisk:IID

.comdef IVdsDisk

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties	proc :ptr
    GetPack		proc :ptr
    GetIdentificationData proc :ptr
    QueryExtents	proc
    ConvertStyle	proc :VDS_PARTITION_STYLE
    SetFlags		proc :ULONG
    ClearFlags		proc :ULONG
    .ends

endif

ifndef __IVdsDisk2_INTERFACE_DEFINED__
__IVdsDisk2_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsDisk2:IID

.comdef IVdsDisk2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetSANMode		proc :BOOL
    .ends

endif

ifndef __IVdsDiskOnline_INTERFACE_DEFINED__
__IVdsDiskOnline_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsDiskOnline:IID

.comdef IVdsDiskOnline

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Online		proc
    Offline		proc
    .ends

endif

ifndef __IVdsAdvancedDisk_INTERFACE_DEFINED__
__IVdsAdvancedDisk_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsAdvancedDisk:IID

.comdef IVdsAdvancedDisk

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetPartitionProperties proc :ULONGLONG, :ptr
    QueryPartitions	proc
    CreatePartition	proc :ULONGLONG, :ULONGLONG, :ptr, :ptr
    DeletePartition	proc :ULONGLONG, :BOOL, :BOOL
    ChangeAttributes	proc :ULONGLONG, :ptr
    AssignDriveLetter	proc :ULONGLONG, :WCHAR
    DeleteDriveLetter	proc :ULONGLONG, :WCHAR
    GetDriveLetter	proc :ULONGLONG, :ptr
    FormatPartition	proc :ULONGLONG, :VDS_FILE_SYSTEM_TYPE, :LPWSTR, :DWORD, :BOOL, :BOOL, :BOOL, :ptr
    Clean		proc :BOOL, :BOOL, :BOOL, :ptr
    .ends

endif

ifndef __IVdsAdvancedDisk2_INTERFACE_DEFINED__
__IVdsAdvancedDisk2_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsAdvancedDisk2:IID

.comdef IVdsAdvancedDisk2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    ChangePartitionType proc :ULONGLONG, :BOOL, :ptr
    .ends

endif

ifndef __IVdsAdvancedDisk3_INTERFACE_DEFINED__
__IVdsAdvancedDisk3_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsAdvancedDisk3:IID

.comdef IVdsAdvancedDisk3

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties	proc :ptr
    GetUniqueId		proc :ptr
    .ends

endif

ifndef __IVdsCreatePartitionEx_INTERFACE_DEFINED__
__IVdsCreatePartitionEx_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsCreatePartitionEx:IID

.comdef IVdsCreatePartitionEx

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    CreatePartitionEx	proc :ULONGLONG, :ULONGLONG, :ULONG, :ptr, :ptr
    .ends

endif

ifndef __IVdsRemovable_INTERFACE_DEFINED__
__IVdsRemovable_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsRemovable:IID

.comdef IVdsRemovable

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    QueryMedia		proc
    Eject		proc
    .ends

endif

ifndef __IVdsVolume_INTERFACE_DEFINED__
__IVdsVolume_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsVolume:IID

.comdef IVdsVolume

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties	proc :ptr
    GetPack		proc :ptr
    QueryPlexes		proc :ptr
    Extend		proc
    Shrink		proc :ULONGLONG, :ptr
    AddPlex		proc :VDS_OBJECT_ID, :ptr
    BreakPlex		proc :VDS_OBJECT_ID, :ptr
    RemovePlex		proc :VDS_OBJECT_ID, :ptr
    Delete		proc :BOOL
    SetFlags		proc :ULONG, :BOOL
    ClearFlags		proc :ULONG
    .ends

endif

ifndef __IVdsVolume2_INTERFACE_DEFINED__
__IVdsVolume2_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsVolume2:IID

.comdef IVdsVolume2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties2	proc :ptr
    .ends

endif

ifndef __IVdsVolumeOnline_INTERFACE_DEFINED__
__IVdsVolumeOnline_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsVolumeOnline:IID

.comdef IVdsVolumeOnline

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Online		proc
    .ends

endif

ifndef __IVdsVolumePlex_INTERFACE_DEFINED__
__IVdsVolumePlex_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsVolumePlex:IID

.comdef IVdsVolumePlex

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties	proc :ptr
    GetVolume		proc :ptr
    QueryExtents	proc
    Repair		proc
    .ends

endif

ifndef __IVdsDisk3_INTERFACE_DEFINED__
__IVdsDisk3_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsDisk3:IID

.comdef IVdsDisk3

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties2	proc :ptr
    QueryFreeExtents	proc :ULONG
    .ends

endif


endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include winapifamily.inc
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)


VDS_SUB_SYSTEM_STATUS	typedef SDWORD
VDS_SSS_UNKNOWN		equ 0
VDS_SSS_ONLINE		equ 1
VDS_SSS_NOT_READY	equ 2
VDS_SSS_OFFLINE		equ 4
VDS_SSS_FAILED		equ 5
VDS_SSS_PARTIALLY_MANAGED equ 9

PVDS_SUB_SYSTEM_STATUS	typedef ptr VDS_SUB_SYSTEM_STATUS

VDS_SUB_SYSTEM_FLAG	typedef SDWORD
VDS_SF_LUN_MASKING_CAPABLE equ 0x1
VDS_SF_LUN_PLEXING_CAPABLE equ 0x2
VDS_SF_LUN_REMAPPING_CAPABLE equ 0x4
VDS_SF_DRIVE_EXTENT_CAPABLE equ 0x8
VDS_SF_HARDWARE_CHECKSUM_CAPABLE equ 0x10
VDS_SF_RADIUS_CAPABLE	equ 0x20
VDS_SF_READ_BACK_VERIFY_CAPABLE equ 0x40
VDS_SF_WRITE_THROUGH_CACHING_CAPABLE equ 0x80
VDS_SF_SUPPORTS_FAULT_TOLERANT_LUNS equ 0x200
VDS_SF_SUPPORTS_NON_FAULT_TOLERANT_LUNS equ 0x400
VDS_SF_SUPPORTS_SIMPLE_LUNS equ 0x800
VDS_SF_SUPPORTS_SPAN_LUNS equ 0x1000
VDS_SF_SUPPORTS_STRIPE_LUNS equ 0x2000
VDS_SF_SUPPORTS_MIRROR_LUNS equ 0x4000
VDS_SF_SUPPORTS_PARITY_LUNS equ 0x8000
VDS_SF_SUPPORTS_AUTH_CHAP equ 0x10000
VDS_SF_SUPPORTS_AUTH_MUTUAL_CHAP equ 0x20000
VDS_SF_SUPPORTS_SIMPLE_TARGET_CONFIG equ 0x40000
VDS_SF_SUPPORTS_LUN_NUMBER equ 0x80000
VDS_SF_SUPPORTS_MIRRORED_CACHE equ 0x100000
VDS_SF_READ_CACHING_CAPABLE equ 0x200000
VDS_SF_WRITE_CACHING_CAPABLE equ 0x400000
VDS_SF_MEDIA_SCAN_CAPABLE equ 0x800000
VDS_SF_CONSISTENCY_CHECK_CAPABLE equ 0x1000000

PVDS_SUB_SYSTEM_FLAG	typedef ptr VDS_SUB_SYSTEM_FLAG

VDS_SUB_SYSTEM_SUPPORTED_RAID_TYPE_FLAG typedef SDWORD
VDS_SF_SUPPORTS_RAID2_LUNS equ 0x1
VDS_SF_SUPPORTS_RAID3_LUNS equ 0x2
VDS_SF_SUPPORTS_RAID4_LUNS equ 0x4
VDS_SF_SUPPORTS_RAID5_LUNS equ 0x8
VDS_SF_SUPPORTS_RAID6_LUNS equ 0x10
VDS_SF_SUPPORTS_RAID01_LUNS equ 0x20
VDS_SF_SUPPORTS_RAID03_LUNS equ 0x40
VDS_SF_SUPPORTS_RAID05_LUNS equ 0x80
VDS_SF_SUPPORTS_RAID10_LUNS equ 0x100
VDS_SF_SUPPORTS_RAID15_LUNS equ 0x200
VDS_SF_SUPPORTS_RAID30_LUNS equ 0x400
VDS_SF_SUPPORTS_RAID50_LUNS equ 0x800
VDS_SF_SUPPORTS_RAID51_LUNS equ 0x1000
VDS_SF_SUPPORTS_RAID53_LUNS equ 0x2000
VDS_SF_SUPPORTS_RAID60_LUNS equ 0x4000
VDS_SF_SUPPORTS_RAID61_LUNS equ 0x8000

PVDS_SUB_SYSTEM_SUPPORTED_RAID_TYPE_FLAG typedef ptr VDS_SUB_SYSTEM_SUPPORTED_RAID_TYPE_FLAG

VDS_INTERCONNECT_FLAG	typedef SDWORD
VDS_ITF_PCI_RAID	equ 0x1
VDS_ITF_FIBRE_CHANNEL	equ 0x2
VDS_ITF_ISCSI		equ 0x4
VDS_ITF_SAS		equ 0x8

PVDS_INTERCONNECT_FLAG	typedef ptr VDS_INTERCONNECT_FLAG

VDS_CONTROLLER_STATUS	typedef SDWORD
VDS_CS_UNKNOWN		equ 0
VDS_CS_ONLINE		equ 1
VDS_CS_NOT_READY	equ 2
VDS_CS_OFFLINE		equ 4
VDS_CS_FAILED		equ 5
VDS_CS_REMOVED		equ 8

PVDS_CONTROLLER_STATUS	typedef ptr VDS_CONTROLLER_STATUS

VDS_PORT_STATUS		typedef SDWORD
VDS_PRS_UNKNOWN		equ 0
VDS_PRS_ONLINE		equ 1
VDS_PRS_NOT_READY	equ 2
VDS_PRS_OFFLINE		equ 4
VDS_PRS_FAILED		equ 5
VDS_PRS_REMOVED		equ 8

PVDS_PORT_STATUS	typedef ptr VDS_PORT_STATUS

VDS_DRIVE_STATUS	typedef SDWORD
VDS_DRS_UNKNOWN		equ 0
VDS_DRS_ONLINE		equ 1
VDS_DRS_NOT_READY	equ 2
VDS_DRS_OFFLINE		equ 4
VDS_DRS_FAILED		equ 5
VDS_DRS_REMOVED		equ 8

PVDS_DRIVE_STATUS	typedef ptr VDS_DRIVE_STATUS

VDS_DRIVE_FLAG		typedef SDWORD
VDS_DRF_HOTSPARE	equ 0x1
VDS_DRF_ASSIGNED	equ 0x2
VDS_DRF_UNASSIGNED	equ 0x4
VDS_DRF_HOTSPARE_IN_USE equ 0x8
VDS_DRF_HOTSPARE_STANDBY equ 0x10

PVDS_DRIVE_FLAG		typedef ptr VDS_DRIVE_FLAG

VDS_LUN_TYPE		typedef SDWORD
VDS_LT_UNKNOWN		equ 0
VDS_LT_DEFAULT		equ 1
VDS_LT_FAULT_TOLERANT	equ 2
VDS_LT_NON_FAULT_TOLERANT equ 3
VDS_LT_SIMPLE		equ 10
VDS_LT_SPAN		equ 11
VDS_LT_STRIPE		equ 12
VDS_LT_MIRROR		equ 13
VDS_LT_PARITY		equ 14
VDS_LT_RAID2		equ 15
VDS_LT_RAID3		equ 16
VDS_LT_RAID4		equ 17
VDS_LT_RAID5		equ 18
VDS_LT_RAID6		equ 19
VDS_LT_RAID01		equ 20
VDS_LT_RAID03		equ 21
VDS_LT_RAID05		equ 22
VDS_LT_RAID10		equ 23
VDS_LT_RAID15		equ 24
VDS_LT_RAID30		equ 25
VDS_LT_RAID50		equ 26
VDS_LT_RAID51		equ 27
VDS_LT_RAID53		equ 28
VDS_LT_RAID60		equ 29
VDS_LT_RAID61		equ 30

PVDS_LUN_TYPE		typedef ptr VDS_LUN_TYPE

VDS_LUN_STATUS		typedef SDWORD
VDS_LS_UNKNOWN		equ 0
VDS_LS_ONLINE		equ 1
VDS_LS_NOT_READY	equ 2
VDS_LS_OFFLINE		equ 4
VDS_LS_FAILED		equ 5

PVDS_LUN_STATUS		typedef ptr VDS_LUN_STATUS

VDS_LUN_FLAG		typedef SDWORD
VDS_LF_LBN_REMAP_ENABLED equ 0x1
VDS_LF_READ_BACK_VERIFY_ENABLED equ 0x2
VDS_LF_WRITE_THROUGH_CACHING_ENABLED equ 0x4
VDS_LF_HARDWARE_CHECKSUM_ENABLED equ 0x8
VDS_LF_READ_CACHE_ENABLED equ 0x10
VDS_LF_WRITE_CACHE_ENABLED equ 0x20
VDS_LF_MEDIA_SCAN_ENABLED equ 0x40
VDS_LF_CONSISTENCY_CHECK_ENABLED equ 0x80
VDS_LF_SNAPSHOT		equ 0x100

PVDS_LUN_FLAG		typedef ptr VDS_LUN_FLAG

VDS_LUN_PLEX_TYPE	typedef SDWORD
VDS_LPT_UNKNOWN		equ 0
VDS_LPT_SIMPLE		equ VDS_LT_SIMPLE
VDS_LPT_SPAN		equ VDS_LT_SPAN
VDS_LPT_STRIPE		equ VDS_LT_STRIPE
VDS_LPT_PARITY		equ VDS_LT_PARITY
VDS_LPT_RAID2		equ VDS_LT_RAID2
VDS_LPT_RAID3		equ VDS_LT_RAID3
VDS_LPT_RAID4		equ VDS_LT_RAID4
VDS_LPT_RAID5		equ VDS_LT_RAID5
VDS_LPT_RAID6		equ VDS_LT_RAID6
VDS_LPT_RAID03		equ VDS_LT_RAID03
VDS_LPT_RAID05		equ VDS_LT_RAID05
VDS_LPT_RAID10		equ VDS_LT_RAID10
VDS_LPT_RAID15		equ VDS_LT_RAID15
VDS_LPT_RAID30		equ VDS_LT_RAID30
VDS_LPT_RAID50		equ VDS_LT_RAID50
VDS_LPT_RAID53		equ VDS_LT_RAID53
VDS_LPT_RAID60		equ VDS_LT_RAID60

VDS_LUN_PLEX_STATUS	typedef SDWORD
VDS_LPS_UNKNOWN		equ 0
VDS_LPS_ONLINE		equ 1
VDS_LPS_NOT_READY	equ 2
VDS_LPS_OFFLINE		equ 4
VDS_LPS_FAILED		equ 5

VDS_LUN_PLEX_FLAG	typedef SDWORD
VDS_LPF_LBN_REMAP_ENABLED equ VDS_LF_LBN_REMAP_ENABLED

VDS_ISCSI_PORTAL_STATUS typedef SDWORD
VDS_IPS_UNKNOWN		equ 0
VDS_IPS_ONLINE		equ 1
VDS_IPS_NOT_READY	equ 2
VDS_IPS_OFFLINE		equ 4
VDS_IPS_FAILED		equ 5

VDS_STORAGE_POOL_STATUS typedef SDWORD
VDS_SPS_UNKNOWN		equ 0
VDS_SPS_ONLINE		equ 1
VDS_SPS_NOT_READY	equ 2
VDS_SPS_OFFLINE		equ 4

VDS_STORAGE_POOL_TYPE	typedef SDWORD
VDS_SPT_UNKNOWN		equ 0
VDS_SPT_PRIMORDIAL	equ 0x1
VDS_SPT_CONCRETE	equ 0x2

VDS_MAINTENANCE_OPERATION typedef SDWORD
BlinkLight		equ 1
BeepAlarm		equ 2
SpinDown		equ 3
SpinUp			equ 4
Ping			equ 5

VDS_HINTS		STRUC
ullHintMask		ULONGLONG ?
ullExpectedMaximumSize	ULONGLONG ?
ulOptimalReadSize	ULONG ?
ulOptimalReadAlignment	ULONG ?
ulOptimalWriteSize	ULONG ?
ulOptimalWriteAlignment ULONG ?
ulMaximumDriveCount	ULONG ?
ulStripeSize		ULONG ?
bFastCrashRecoveryRequired BOOL ?
bMostlyReads		BOOL ?
bOptimizeForSequentialReads BOOL ?
bOptimizeForSequentialWrites BOOL ?
bRemapEnabled		BOOL ?
bReadBackVerifyEnabled	BOOL ?
bWriteThroughCachingEnabled BOOL ?
bHardwareChecksumEnabled BOOL ?
bIsYankable		BOOL ?
sRebuildPriority	dw ?
VDS_HINTS		ENDS
PVDS_HINTS		typedef ptr VDS_HINTS


VDS_HINT_FASTCRASHRECOVERYREQUIRED equ 0x1
VDS_HINT_MOSTLYREADS	equ 0x2
VDS_HINT_OPTIMIZEFORSEQUENTIALREADS equ 0x4
VDS_HINT_OPTIMIZEFORSEQUENTIALWRITES equ 0x8
VDS_HINT_READBACKVERIFYENABLED equ 0x10
VDS_HINT_REMAPENABLED	equ 0x20
VDS_HINT_WRITETHROUGHCACHINGENABLED equ 0x40
VDS_HINT_HARDWARECHECKSUMENABLED equ 0x80
VDS_HINT_ISYANKABLE	equ 0x100

VDS_HINTS2		STRUC
ullHintMask		ULONGLONG ?
ullExpectedMaximumSize	ULONGLONG ?
ulOptimalReadSize	ULONG ?
ulOptimalReadAlignment	ULONG ?
ulOptimalWriteSize	ULONG ?
ulOptimalWriteAlignment ULONG ?
ulMaximumDriveCount	ULONG ?
ulStripeSize		ULONG ?
ulReserved1		ULONG ?
ulReserved2		ULONG ?
ulReserved3		ULONG ?
bFastCrashRecoveryRequired BOOL ?
bMostlyReads		BOOL ?
bOptimizeForSequentialReads BOOL ?
bOptimizeForSequentialWrites BOOL ?
bRemapEnabled		BOOL ?
bReadBackVerifyEnabled	BOOL ?
bWriteThroughCachingEnabled BOOL ?
bHardwareChecksumEnabled BOOL ?
bIsYankable		BOOL ?
bAllocateHotSpare	BOOL ?
bUseMirroredCache	BOOL ?
bReadCachingEnabled	BOOL ?
bWriteCachingEnabled	BOOL ?
bMediaScanEnabled	BOOL ?
bConsistencyCheckEnabled BOOL ?
BusType			VDS_STORAGE_BUS_TYPE ?
bReserved1		BOOL ?
bReserved2		BOOL ?
bReserved3		BOOL ?
sRebuildPriority	dw ?
VDS_HINTS2		ENDS
PVDS_HINTS2		typedef ptr VDS_HINTS2

VDS_HINT_ALLOCATEHOTSPARE equ 0x200
VDS_HINT_BUSTYPE	equ 0x400
VDS_HINT_USEMIRROREDCACHE equ 0x800
VDS_HINT_READCACHINGENABLED equ 0x1000
VDS_HINT_WRITECACHINGENABLED equ 0x2000
VDS_HINT_MEDIASCANENABLED equ 0x4000
VDS_HINT_CONSISTENCYCHECKENABLED equ 0x8000

VDS_SUB_SYSTEM_PROP	STRUC
id			VDS_OBJECT_ID <>
pwszFriendlyName	LPWSTR ?
pwszIdentification	LPWSTR ?
ulFlags			ULONG ?
ulStripeSizeFlags	ULONG ?
status			VDS_SUB_SYSTEM_STATUS ?
health			VDS_HEALTH ?
sNumberOfInternalBuses	SWORD ?
sMaxNumberOfSlotsEachBus SWORD ?
sMaxNumberOfControllers SWORD ?
sRebuildPriority	SWORD ?
VDS_SUB_SYSTEM_PROP	ENDS
PVDS_SUB_SYSTEM_PROP	typedef ptr VDS_SUB_SYSTEM_PROP

VDS_SUB_SYSTEM_PROP2	STRUC
id			VDS_OBJECT_ID <>
pwszFriendlyName	LPWSTR ?
pwszIdentification	LPWSTR ?
ulFlags			ULONG ?
ulStripeSizeFlags	ULONG ?
ulSupportedRaidTypeFlags ULONG ?
status			VDS_SUB_SYSTEM_STATUS ?
health			VDS_HEALTH ?
sNumberOfInternalBuses	SWORD ?
sMaxNumberOfSlotsEachBus SWORD ?
sMaxNumberOfControllers SWORD ?
sRebuildPriority	SWORD ?
ulNumberOfEnclosures	ULONG ?
VDS_SUB_SYSTEM_PROP2	ENDS
PVDS_SUB_SYSTEM_PROP2	typedef ptr VDS_SUB_SYSTEM_PROP2

VDS_CONTROLLER_PROP	STRUC
id			VDS_OBJECT_ID <>
pwszFriendlyName	LPWSTR ?
pwszIdentification	LPWSTR ?
status			VDS_CONTROLLER_STATUS ?
health			VDS_HEALTH ?
sNumberOfPorts		SWORD ?
VDS_CONTROLLER_PROP	ENDS
PVDS_CONTROLLER_PROP	typedef ptr VDS_CONTROLLER_PROP

VDS_DRIVE_PROP		STRUC
id			VDS_OBJECT_ID <>
ullSize			ULONGLONG ?
pwszFriendlyName	LPWSTR ?
pwszIdentification	LPWSTR ?
ulFlags			ULONG ?
status			VDS_DRIVE_STATUS ?
health			VDS_HEALTH ?
sInternalBusNumber	SWORD ?
sSlotNumber		SWORD ?
VDS_DRIVE_PROP		ENDS
PVDS_DRIVE_PROP		typedef ptr VDS_DRIVE_PROP

VDS_DRIVE_PROP2		STRUC
id			VDS_OBJECT_ID <>
ullSize			ULONGLONG ?
pwszFriendlyName	LPWSTR ?
pwszIdentification	LPWSTR ?
ulFlags			ULONG ?
status			VDS_DRIVE_STATUS ?
health			VDS_HEALTH ?
sInternalBusNumber	SWORD ?
sSlotNumber		SWORD ?
ulEnclosureNumber	ULONG ?
busType			VDS_STORAGE_BUS_TYPE ?
ulSpindleSpeed		ULONG ?
VDS_DRIVE_PROP2		ENDS
PVDS_DRIVE_PROP2	typedef ptr VDS_DRIVE_PROP2

VDS_DRIVE_EXTENT	STRUC
id			VDS_OBJECT_ID <>
LunId			VDS_OBJECT_ID <>
ullSize			ULONGLONG ?
bUsed			BOOL ?
VDS_DRIVE_EXTENT	ENDS

PVDS_DRIVE_EXTENT	typedef ptr VDS_DRIVE_EXTENT

VDS_REBUILD_PRIORITY_MIN equ 0
VDS_REBUILD_PRIORITY_MAX equ 16
VDS_LUN_PROP		STRUC
id			VDS_OBJECT_ID <>
ullSize			ULONGLONG ?
pwszFriendlyName	LPWSTR ?
pwszIdentification	LPWSTR ?
pwszUnmaskingList	LPWSTR ?
ulFlags			ULONG ?
_type			VDS_LUN_TYPE ?
status			VDS_LUN_STATUS ?
health			VDS_HEALTH ?
TransitionState		VDS_TRANSITION_STATE ?
sRebuildPriority	SWORD ?
VDS_LUN_PROP		ENDS
PVDS_LUN_PROP		typedef ptr VDS_LUN_PROP

VDS_LUN_PLEX_PROP	STRUC
id			VDS_OBJECT_ID <>
ullSize			ULONGLONG ?
_type			VDS_LUN_PLEX_TYPE ?
status			VDS_LUN_PLEX_STATUS ?
health			VDS_HEALTH ?
TransitionState		VDS_TRANSITION_STATE ?
ulFlags			ULONG ?
ulStripeSize		ULONG ?
sRebuildPriority	SWORD ?
VDS_LUN_PLEX_PROP	ENDS
PVDS_LUN_PLEX_PROP	typedef ptr VDS_LUN_PLEX_PROP

VDS_PORT_PROP		STRUC
id			VDS_OBJECT_ID <>
pwszFriendlyName	LPWSTR ?
pwszIdentification	LPWSTR ?
status			VDS_PORT_STATUS ?
VDS_PORT_PROP		ENDS
PVDS_PORT_PROP		typedef ptr VDS_PORT_PROP

VDS_ISCSI_PORTAL_PROP	STRUC
id			VDS_OBJECT_ID <>
address			VDS_IPADDRESS <>
status			VDS_ISCSI_PORTAL_STATUS ?
VDS_ISCSI_PORTAL_PROP	ENDS
PVDS_ISCSI_PORTAL_PROP	typedef ptr VDS_ISCSI_PORTAL_PROP

VDS_ISCSI_TARGET_PROP	STRUC
id			VDS_OBJECT_ID <>
pwszFriendlyName	LPWSTR ?
pwszIdentification	LPWSTR ?
bChapEnabled		BOOL ?
VDS_ISCSI_TARGET_PROP	ENDS
PVDS_ISCSI_TARGET_PROP	typedef ptr VDS_ISCSI_TARGET_PROP

VDS_ISCSI_PORTALGROUP_PROP STRUC
id			VDS_OBJECT_ID <>
tag			VDS_ISCSI_PORTALGROUP_TAG ?
VDS_ISCSI_PORTALGROUP_PROP ENDS
PVDS_ISCSI_PORTALGROUP_PROP typedef ptr VDS_ISCSI_PORTALGROUP_PROP

VDS_RAID_TYPE		typedef SDWORD
VDS_RT_UNKNOWN		equ 0
VDS_RT_RAID0		equ 10
VDS_RT_RAID1		equ 11
VDS_RT_RAID2		equ 12
VDS_RT_RAID3		equ 13
VDS_RT_RAID4		equ 14
VDS_RT_RAID5		equ 15
VDS_RT_RAID6		equ 16
VDS_RT_RAID01		equ 17
VDS_RT_RAID03		equ 18
VDS_RT_RAID05		equ 19
VDS_RT_RAID10		equ 20
VDS_RT_RAID15		equ 21
VDS_RT_RAID30		equ 22
VDS_RT_RAID50		equ 23
VDS_RT_RAID51		equ 24
VDS_RT_RAID53		equ 25
VDS_RT_RAID60		equ 26
VDS_RT_RAID61		equ 27

PVDS_RAID_TYPE		typedef ptr VDS_RAID_TYPE

VDS_POOL_CUSTOM_ATTRIBUTES STRUC
pwszName		LPWSTR ?
pwszValue		LPWSTR ?
VDS_POOL_CUSTOM_ATTRIBUTES ENDS

PVDS_POOL_CUSTOM_ATTRIBUTES typedef ptr VDS_POOL_CUSTOM_ATTRIBUTES

VDS_POOL_ATTRIBUTES	STRUC
ullAttributeMask	ULONGLONG ?
raidType		VDS_RAID_TYPE ?
busType			VDS_STORAGE_BUS_TYPE ?
pwszIntendedUsage	LPWSTR ?
bSpinDown		BOOL ?
bIsThinProvisioned	BOOL ?
ullProvisionedSpace	ULONGLONG ?
bNoSinglePointOfFailure BOOL ?
ulDataRedundancyMax	ULONG ?
ulDataRedundancyMin	ULONG ?
ulDataRedundancyDefault ULONG ?
ulPackageRedundancyMax	ULONG ?
ulPackageRedundancyMin	ULONG ?
ulPackageRedundancyDefault ULONG ?
ulStripeSize		ULONG ?
ulStripeSizeMax		ULONG ?
ulStripeSizeMin		ULONG ?
ulDefaultStripeSize	ULONG ?
ulNumberOfColumns	ULONG ?
ulNumberOfColumnsMax	ULONG ?
ulNumberOfColumnsMin	ULONG ?
ulDefaultNumberofColumns ULONG ?
ulDataAvailabilityHint	ULONG ?
ulAccessRandomnessHint	ULONG ?
ulAccessDirectionHint	ULONG ?
ulAccessSizeHint	ULONG ?
ulAccessLatencyHint	ULONG ?
ulAccessBandwidthWeightHint ULONG ?
ulStorageCostHint	ULONG ?
ulStorageEfficiencyHint ULONG ?
ulNumOfCustomAttributes ULONG ?
pPoolCustomAttributes	PVDS_POOL_CUSTOM_ATTRIBUTES ?
bReserved1		BOOL ?
bReserved2		BOOL ?
ulReserved1		ULONG ?
ulReserved2		ULONG ?
ullReserved1		ULONGLONG ?
ullReserved2		ULONGLONG ?
VDS_POOL_ATTRIBUTES	ENDS
PVDS_POOL_ATTRIBUTES	typedef ptr VDS_POOL_ATTRIBUTES

VDS_POOL_ATTRIB_RAIDTYPE equ 0x1
VDS_POOL_ATTRIB_BUSTYPE equ 0x2
VDS_POOL_ATTRIB_ALLOW_SPINDOWN equ 0x4
VDS_POOL_ATTRIB_THIN_PROVISION equ 0x8
VDS_POOL_ATTRIB_NO_SINGLE_POF equ 0x10
VDS_POOL_ATTRIB_DATA_RDNCY_MAX equ 0x20
VDS_POOL_ATTRIB_DATA_RDNCY_MIN equ 0x40
VDS_POOL_ATTRIB_DATA_RDNCY_DEF equ 0x80
VDS_POOL_ATTRIB_PKG_RDNCY_MAX equ 0x100
VDS_POOL_ATTRIB_PKG_RDNCY_MIN equ 0x200
VDS_POOL_ATTRIB_PKG_RDNCY_DEF equ 0x400
VDS_POOL_ATTRIB_STRIPE_SIZE equ 0x800
VDS_POOL_ATTRIB_STRIPE_SIZE_MAX equ 0x1000
VDS_POOL_ATTRIB_STRIPE_SIZE_MIN equ 0x2000
VDS_POOL_ATTRIB_STRIPE_SIZE_DEF equ 0x4000
VDS_POOL_ATTRIB_NUM_CLMNS equ 0x8000
VDS_POOL_ATTRIB_NUM_CLMNS_MAX equ 0x10000
VDS_POOL_ATTRIB_NUM_CLMNS_MIN equ 0x20000
VDS_POOL_ATTRIB_NUM_CLMNS_DEF equ 0x40000
VDS_POOL_ATTRIB_DATA_AVL_HINT equ 0x80000
VDS_POOL_ATTRIB_ACCS_RNDM_HINT equ 0x100000
VDS_POOL_ATTRIB_ACCS_DIR_HINT equ 0x200000
VDS_POOL_ATTRIB_ACCS_SIZE_HINT equ 0x400000
VDS_POOL_ATTRIB_ACCS_LTNCY_HINT equ 0x800000
VDS_POOL_ATTRIB_ACCS_BDW_WT_HINT equ 0x1000000
VDS_POOL_ATTRIB_STOR_COST_HINT equ 0x2000000
VDS_POOL_ATTRIB_STOR_EFFCY_HINT equ 0x4000000
VDS_POOL_ATTRIB_CUSTOM_ATTRIB equ 0x8000000

VDS_STORAGE_POOL_PROP	STRUC
id			VDS_OBJECT_ID <>
status			VDS_STORAGE_POOL_STATUS ?
health			VDS_HEALTH ?
_type			VDS_STORAGE_POOL_TYPE ?
pwszName		LPWSTR ?
pwszDescription		LPWSTR ?
ullTotalConsumedSpace	ULONGLONG ?
ullTotalManagedSpace	ULONGLONG ?
ullRemainingFreeSpace	ULONGLONG ?
VDS_STORAGE_POOL_PROP	ENDS
PVDS_STORAGE_POOL_PROP	typedef ptr VDS_STORAGE_POOL_PROP

VDS_STORAGE_POOL_DRIVE_EXTENT STRUC
id			VDS_OBJECT_ID <>
ullSize			ULONGLONG ?
bUsed			BOOL ?
VDS_STORAGE_POOL_DRIVE_EXTENT ENDS
PVDS_STORAGE_POOL_DRIVE_EXTENT typedef ptr VDS_STORAGE_POOL_DRIVE_EXTENT

externdef		__MIDL_itf_vds_0000_0021_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_vds_0000_0021_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IVdsHwProvider_INTERFACE_DEFINED__
__IVdsHwProvider_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsHwProvider:IID

.comdef IVdsHwProvider

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    QuerySubSystems	proc :ptr
    Reenumerate		proc
    Refresh		proc
    .ends

endif

ifndef __IVdsHwProviderType_INTERFACE_DEFINED__
__IVdsHwProviderType_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsHwProviderType:IID

.comdef IVdsHwProviderType

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProviderType	proc :ptr
    .ends

endif

ifndef __IVdsHwProviderType2_INTERFACE_DEFINED__
__IVdsHwProviderType2_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsHwProviderType2:IID

.comdef IVdsHwProviderType2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProviderType2	proc :ptr
    .ends

endif

ifndef __IVdsHwProviderStoragePools_INTERFACE_DEFINED__
__IVdsHwProviderStoragePools_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsHwProviderStoragePools:IID

.comdef IVdsHwProviderStoragePools

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    QueryStoragePools	proc :ULONG, :ULONGLONG, :ptr, :ptr
    CreateLunInStoragePool proc :VDS_LUN_TYPE, :ULONGLONG, :VDS_OBJECT_ID, :LPWSTR, :ptr, :ptr
    QueryMaxLunCreateSizeInStoragePool proc :VDS_LUN_TYPE, :VDS_OBJECT_ID, :ptr, :ptr
    .ends

endif

ifndef __IVdsSubSystem_INTERFACE_DEFINED__
__IVdsSubSystem_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsSubSystem:IID

.comdef IVdsSubSystem

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties	proc :ptr
    GetProvider		proc :ptr
    QueryControllers	proc :ptr
    QueryLuns		proc :ptr
    QueryDrives		proc :ptr
    GetDrive		proc :SWORD, :SWORD, :ptr
    Reenumerate		proc
    SetControllerStatus proc :ptr, :LONG
    CreateLun		proc :VDS_LUN_TYPE, :ULONGLONG
    ReplaceDrive	proc :VDS_OBJECT_ID, :VDS_OBJECT_ID
    SetStatus		proc :VDS_SUB_SYSTEM_STATUS
    QueryMaxLunCreateSize proc :VDS_LUN_TYPE
    .ends

endif

ifndef __IVdsSubSystem2_INTERFACE_DEFINED__
__IVdsSubSystem2_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsSubSystem2:IID

.comdef IVdsSubSystem2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties2	proc :ptr
    GetDrive2		proc :SWORD, :SWORD, :ULONG, :ptr
    CreateLun2		proc :VDS_LUN_TYPE, :ULONGLONG
    QueryMaxLunCreateSize2 proc :VDS_LUN_TYPE
    .ends

endif

ifndef __IVdsSubSystemNaming_INTERFACE_DEFINED__
__IVdsSubSystemNaming_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsSubSystemNaming:IID

.comdef IVdsSubSystemNaming

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetFriendlyName	proc :LPWSTR
    .ends

endif

ifndef __IVdsSubSystemIscsi_INTERFACE_DEFINED__
__IVdsSubSystemIscsi_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsSubSystemIscsi:IID

.comdef IVdsSubSystemIscsi

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    QueryTargets	proc :ptr
    QueryPortals	proc :ptr
    CreateTarget	proc :LPWSTR, :LPWSTR, :ptr
    SetIpsecGroupPresharedKey proc :ptr
    .ends

endif

ifndef __IVdsSubSystemInterconnect_INTERFACE_DEFINED__
__IVdsSubSystemInterconnect_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsSubSystemInterconnect:IID

.comdef IVdsSubSystemInterconnect

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetSupportedInterconnects proc :ptr
    .ends

endif

ifndef __IVdsControllerPort_INTERFACE_DEFINED__
__IVdsControllerPort_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsControllerPort:IID

.comdef IVdsControllerPort

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties	proc :ptr
    GetController	proc :ptr
    QueryAssociatedLuns proc :ptr
    Reset		proc
    SetStatus		proc :VDS_PORT_STATUS
    .ends

endif

ifndef __IVdsController_INTERFACE_DEFINED__
__IVdsController_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsController:IID

.comdef IVdsController

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties	proc :ptr
    GetSubSystem	proc :ptr
    GetPortProperties	proc :SWORD, :ptr
    FlushCache		proc
    InvalidateCache	proc
    Reset		proc
    QueryAssociatedLuns proc :ptr
    SetStatus		proc :VDS_CONTROLLER_STATUS
    .ends

endif

ifndef __IVdsControllerControllerPort_INTERFACE_DEFINED__
__IVdsControllerControllerPort_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsControllerControllerPort:IID

.comdef IVdsControllerControllerPort

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    QueryControllerPorts proc :ptr
    .ends

endif

ifndef __IVdsDrive_INTERFACE_DEFINED__
__IVdsDrive_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsDrive:IID

.comdef IVdsDrive

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties	proc :ptr
    GetSubSystem	proc :ptr
    QueryExtents	proc
    SetFlags		proc :ULONG
    ClearFlags		proc :ULONG
    SetStatus		proc :VDS_DRIVE_STATUS
    .ends

endif

ifndef __IVdsDrive2_INTERFACE_DEFINED__
__IVdsDrive2_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsDrive2:IID

.comdef IVdsDrive2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties2	proc :ptr
    .ends

endif

ifndef __IVdsLun_INTERFACE_DEFINED__
__IVdsLun_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsLun:IID

.comdef IVdsLun

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties	proc :ptr
    GetSubSystem	proc :ptr
    GetIdentificationData proc :ptr
    QueryActiveControllers proc :ptr
    Extend		proc :ULONGLONG
    Shrink		proc :ULONGLONG, :ptr
    QueryPlexes		proc :ptr
    AddPlex		proc :VDS_OBJECT_ID, :ptr
    RemovePlex		proc :VDS_OBJECT_ID, :ptr
    Recover		proc :ptr
    SetMask		proc :LPWSTR
    Delete		proc
    AssociateControllers proc :ptr, :LONG
    QueryHints		proc :ptr
    ApplyHints		proc :ptr
    SetStatus		proc :VDS_LUN_STATUS
    QueryMaxLunExtendSize proc
    .ends

endif

ifndef __IVdsLun2_INTERFACE_DEFINED__
__IVdsLun2_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsLun2:IID

.comdef IVdsLun2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    QueryHints2		proc :ptr
    ApplyHints2		proc :ptr
    .ends

endif

ifndef __IVdsLunNaming_INTERFACE_DEFINED__
__IVdsLunNaming_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsLunNaming:IID

.comdef IVdsLunNaming

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetFriendlyName	proc :LPWSTR
    .ends

endif

ifndef __IVdsLunNumber_INTERFACE_DEFINED__
__IVdsLunNumber_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsLunNumber:IID

.comdef IVdsLunNumber

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetLunNumber	proc :ptr
    .ends

endif

ifndef __IVdsLunControllerPorts_INTERFACE_DEFINED__
__IVdsLunControllerPorts_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsLunControllerPorts:IID

.comdef IVdsLunControllerPorts

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AssociateControllerPorts proc :ptr, :LONG
    QueryActiveControllerPorts proc :ptr
    .ends

endif

ifndef __IVdsLunMpio_INTERFACE_DEFINED__
__IVdsLunMpio_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsLunMpio:IID

.comdef IVdsLunMpio

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetPathInfo		proc
    GetLoadBalancePolicy proc :ptr
    SetLoadBalancePolicy proc :VDS_LOADBALANCE_POLICY_ENUM
    GetSupportedLbPolicies proc :ptr
    .ends

endif

ifndef __IVdsLunIscsi_INTERFACE_DEFINED__
__IVdsLunIscsi_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsLunIscsi:IID

.comdef IVdsLunIscsi

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AssociateTargets	proc
    QueryAssociatedTargets proc :ptr
    .ends

endif

ifndef __IVdsLunPlex_INTERFACE_DEFINED__
__IVdsLunPlex_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsLunPlex:IID

.comdef IVdsLunPlex

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties	proc :ptr
    GetLun		proc :ptr
    QueryExtents	proc
    QueryHints		proc :ptr
    ApplyHints		proc :ptr
    .ends

endif

ifndef __IVdsIscsiPortal_INTERFACE_DEFINED__
__IVdsIscsiPortal_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsIscsiPortal:IID

.comdef IVdsIscsiPortal

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties	proc :ptr
    GetSubSystem	proc :ptr
    QueryAssociatedPortalGroups proc :ptr
    SetStatus		proc :VDS_ISCSI_PORTAL_STATUS
    SetIpsecTunnelAddress proc :ptr, :ptr
    GetIpsecSecurity	proc :ptr, :ptr
    SetIpsecSecurity	proc :ptr, :ULONGLONG, :ptr
    .ends

endif

ifndef __IVdsIscsiTarget_INTERFACE_DEFINED__
__IVdsIscsiTarget_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsIscsiTarget:IID

.comdef IVdsIscsiTarget

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties	proc :ptr
    GetSubSystem	proc :ptr
    QueryPortalGroups	proc :ptr
    QueryAssociatedLuns proc :ptr
    CreatePortalGroup	proc :ptr
    Delete		proc :ptr
    SetFriendlyName	proc :LPWSTR
    SetSharedSecret	proc :ptr, :LPWSTR
    RememberInitiatorSharedSecret proc :LPWSTR, :ptr
    GetConnectedInitiators proc
    .ends

endif

ifndef __IVdsIscsiPortalGroup_INTERFACE_DEFINED__
__IVdsIscsiPortalGroup_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsIscsiPortalGroup:IID

.comdef IVdsIscsiPortalGroup

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties	proc :ptr
    GetTarget		proc :ptr
    QueryAssociatedPortals proc :ptr
    AddPortal		proc :VDS_OBJECT_ID, :ptr
    RemovePortal	proc :VDS_OBJECT_ID, :ptr
    Delete		proc :ptr
    .ends

endif

ifndef __IVdsStoragePool_INTERFACE_DEFINED__
__IVdsStoragePool_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsStoragePool:IID

.comdef IVdsStoragePool

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProvider		proc :ptr
    GetProperties	proc :ptr
    GetAttributes	proc :ptr
    QueryDriveExtents	proc
    QueryAllocatedLuns	proc :ptr
    QueryAllocatedStoragePools proc :ptr
    .ends

endif

ifndef __IVdsMaintenance_INTERFACE_DEFINED__
__IVdsMaintenance_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsMaintenance:IID

.comdef IVdsMaintenance

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    StartMaintenance	proc :VDS_MAINTENANCE_OPERATION
    StopMaintenance	proc :VDS_MAINTENANCE_OPERATION
    PulseMaintenance	proc :VDS_MAINTENANCE_OPERATION, :ULONG
    .ends

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
if (WINVER GE _WIN32_WINNT_WIN7)

VDS_CREATE_VDISK_PARAMETERS STRUC
UniqueId		GUID <>
MaximumSize		ULONGLONG ?
BlockSizeInBytes	ULONG ?
SectorSizeInBytes	ULONG ?
pParentPath		LPWSTR ?
pSourcePath		LPWSTR ?
VDS_CREATE_VDISK_PARAMETERS ENDS

PVDS_CREATE_VDISK_PARAMETERS typedef ptr VDS_CREATE_VDISK_PARAMETERS

externdef		__MIDL_itf_vds_0000_0048_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_vds_0000_0048_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IVdsVdProvider_INTERFACE_DEFINED__
__IVdsVdProvider_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsVdProvider:IID

.comdef IVdsVdProvider

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    QueryVDisks		proc :ptr
    CreateVDisk		proc :PVIRTUAL_STORAGE_TYPE, :LPWSTR, :LPWSTR, :CREATE_VIRTUAL_DISK_FLAG, :ULONG, :ULONG, :PVDS_CREATE_VDISK_PARAMETERS, :ptr
    AddVDisk		proc :PVIRTUAL_STORAGE_TYPE, :LPWSTR, :ptr
    GetDiskFromVDisk	proc :ptr, :ptr
    GetVDiskFromDisk	proc :ptr, :ptr
    .ends

endif

VDS_VDISK_STATE		typedef SDWORD
VDS_VST_UNKNOWN		equ 0
VDS_VST_ADDED		equ ( VDS_VST_UNKNOWN + 1 )
VDS_VST_OPEN		equ ( VDS_VST_ADDED + 1 )
VDS_VST_ATTACH_PENDING	equ ( VDS_VST_OPEN + 1 )
VDS_VST_ATTACHED_NOT_OPEN equ ( VDS_VST_ATTACH_PENDING + 1 )
VDS_VST_ATTACHED	equ ( VDS_VST_ATTACHED_NOT_OPEN + 1 )
VDS_VST_DETACH_PENDING	equ ( VDS_VST_ATTACHED + 1 )
VDS_VST_COMPACTING	equ ( VDS_VST_DETACH_PENDING + 1 )
VDS_VST_MERGING		equ ( VDS_VST_COMPACTING + 1 )
VDS_VST_EXPANDING	equ ( VDS_VST_MERGING + 1 )
VDS_VST_DELETED		equ ( VDS_VST_EXPANDING + 1 )
VDS_VST_MAX		equ ( VDS_VST_DELETED + 1 )

VDS_VDISK_PROPERTIES	STRUC
Id			VDS_OBJECT_ID <>
State			VDS_VDISK_STATE ?
VirtualDeviceType	VIRTUAL_STORAGE_TYPE <>
VirtualSize		ULONGLONG ?
PhysicalSize		ULONGLONG ?
pPath			LPWSTR ?
pDeviceName		LPWSTR ?
DiskFlag		DEPENDENT_DISK_FLAG ?
bIsChild		BOOL ?
pParentPath		LPWSTR ?
VDS_VDISK_PROPERTIES	ENDS

PVDS_VDISK_PROPERTIES	typedef ptr VDS_VDISK_PROPERTIES

externdef		__MIDL_itf_vds_0000_0049_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_vds_0000_0049_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IVdsVDisk_INTERFACE_DEFINED__
__IVdsVDisk_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsVDisk:IID

.comdef IVdsVDisk

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Open		proc :VIRTUAL_DISK_ACCESS_MASK, :OPEN_VIRTUAL_DISK_FLAG, :ULONG, :ptr
    GetProperties	proc :PVDS_VDISK_PROPERTIES
    GetHostVolume	proc :ptr
    GetDeviceName	proc :ptr
    .ends

endif

ifndef __IVdsOpenVDisk_INTERFACE_DEFINED__
__IVdsOpenVDisk_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsOpenVDisk:IID

.comdef IVdsOpenVDisk

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Attach		proc :LPWSTR, :ATTACH_VIRTUAL_DISK_FLAG, :ULONG, :ULONG, :ptr
    Detach		proc :DETACH_VIRTUAL_DISK_FLAG, :ULONG
    DetachAndDelete	proc :DETACH_VIRTUAL_DISK_FLAG, :ULONG
    Compact		proc :COMPACT_VIRTUAL_DISK_FLAG, :ULONG, :ptr
    Merge		proc :MERGE_VIRTUAL_DISK_FLAG, :ULONG, :ptr
    Expand		proc :EXPAND_VIRTUAL_DISK_FLAG, :ULONGLONG, :ptr
    .ends

endif

VDS_ATTACH_VIRTUAL_DISK_FLAG_USE_FILE_ACL equ 0x1

endif ;; _WIN32_WINNT_WIN7
endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)


;; {9C38ED61-D565-4728-AEEE-C80952F0ECDE}
DEFINE_GUID(CLSID_VdsLoader,0X9C38ED61,0xD565,0x4728,0xAE,0xEE,0xC8,0x09,0x52,0xF0,0xEC,0xDE)

;; {7D1933CB-86F6-4A98-8628-01BE94C9A575}
DEFINE_GUID(CLSID_VdsService,0x7D1933CB,0x86F6,0x4A98,0x86,0x28,0x01,0xBE,0x94,0xC9,0xA5,0x75)

MAX_FS_NAME_SIZE	equ ( 8 )
MAX_FS_FORMAT_SUPPORT_NAME_SIZE equ ( 32 )
MAX_FS_ALLOWED_CLUSTER_SIZES_SIZE equ ( 32 )

VDS_SERVICE_FLAG	typedef SDWORD
VDS_SVF_SUPPORT_DYNAMIC equ 0x1
VDS_SVF_SUPPORT_FAULT_TOLERANT equ 0x2
VDS_SVF_SUPPORT_GPT	equ 0x4
VDS_SVF_SUPPORT_DYNAMIC_1394 equ 0x8
VDS_SVF_CLUSTER_SERVICE_CONFIGURED equ 0x10
VDS_SVF_AUTO_MOUNT_OFF	equ 0x20
VDS_SVF_OS_UNINSTALL_VALID equ 0x40
VDS_SVF_EFI		equ 0x80
VDS_SVF_SUPPORT_MIRROR	equ 0x100L
VDS_SVF_SUPPORT_RAID5	equ 0x200L
VDS_SVF_SUPPORT_REFS	equ 0x400L

VDS_SERVICE_PROP	STRUC
pwszVersion		LPWSTR ?
ulFlags			ULONG ?
VDS_SERVICE_PROP	ENDS

VDS_SAN_POLICY		typedef SDWORD
VDS_SP_UNKNOWN		equ 0
VDS_SP_ONLINE		equ 0x1
VDS_SP_OFFLINE_SHARED	equ 0x2
VDS_SP_OFFLINE		equ 0x3
VDS_SP_OFFLINE_INTERNAL equ 0x4
VDS_SP_MAX		equ 0x5

VDS_REPARSE_POINT_PROP	STRUC
SourceVolumeId		VDS_OBJECT_ID <>
pwszPath		LPWSTR ?
VDS_REPARSE_POINT_PROP	ENDS
PVDS_REPARSE_POINT_PROP typedef ptr VDS_REPARSE_POINT_PROP

VDS_DRIVE_LETTER_FLAG	typedef SDWORD
VDS_DLF_NON_PERSISTENT	equ 0x1

VDS_DRIVE_LETTER_PROP	STRUC
wcLetter		WCHAR ?
volumeId		VDS_OBJECT_ID <>
ulFlags			ULONG ?
bUsed			BOOL ?
VDS_DRIVE_LETTER_PROP	ENDS
PVDS_DRIVE_LETTER_PROP	typedef ptr VDS_DRIVE_LETTER_PROP

VDS_FILE_SYSTEM_FLAG	typedef SDWORD
VDS_FSF_SUPPORT_FORMAT	equ 0x1
VDS_FSF_SUPPORT_QUICK_FORMAT equ 0x2
VDS_FSF_SUPPORT_COMPRESS equ 0x4
VDS_FSF_SUPPORT_SPECIFY_LABEL equ 0x8
VDS_FSF_SUPPORT_MOUNT_POINT equ 0x10
VDS_FSF_SUPPORT_REMOVABLE_MEDIA equ 0x20
VDS_FSF_SUPPORT_EXTEND	equ 0x40
VDS_FSF_ALLOCATION_UNIT_512 equ 0x10000
VDS_FSF_ALLOCATION_UNIT_1K equ 0x20000
VDS_FSF_ALLOCATION_UNIT_2K equ 0x40000
VDS_FSF_ALLOCATION_UNIT_4K equ 0x80000
VDS_FSF_ALLOCATION_UNIT_8K equ 0x100000
VDS_FSF_ALLOCATION_UNIT_16K equ 0x200000
VDS_FSF_ALLOCATION_UNIT_32K equ 0x400000
VDS_FSF_ALLOCATION_UNIT_64K equ 0x800000
VDS_FSF_ALLOCATION_UNIT_128K equ 0x1000000
VDS_FSF_ALLOCATION_UNIT_256K equ 0x2000000

VDS_FILE_SYSTEM_TYPE_PROP STRUC
_type			VDS_FILE_SYSTEM_TYPE ?
wszName			WCHAR 8 dup(?)
ulFlags			ULONG ?
ulCompressionFlags	ULONG ?
ulMaxLableLength	ULONG ?
pwszIllegalLabelCharSet LPWSTR ?
VDS_FILE_SYSTEM_TYPE_PROP ENDS
PVDS_FILE_SYSTEM_TYPE_PROP typedef ptr VDS_FILE_SYSTEM_TYPE_PROP

VDS_FILE_SYSTEM_FORMAT_SUPPORT_FLAG typedef SDWORD
VDS_FSS_DEFAULT		equ 0x1
VDS_FSS_PREVIOUS_REVISION equ 0x2
VDS_FSS_RECOMMENDED	equ 0x4

VDS_FILE_SYSTEM_FORMAT_SUPPORT_PROP STRUC
ulFlags			ULONG ?
usRevision		dw ?
ulDefaultUnitAllocationSize ULONG ?
rgulAllowedUnitAllocationSizes ULONG 32 dup(?)
wszName			WCHAR 32 dup(?)
VDS_FILE_SYSTEM_FORMAT_SUPPORT_PROP ENDS
PVDS_FILE_SYSTEM_FORMAT_SUPPORT_PROP typedef ptr VDS_FILE_SYSTEM_FORMAT_SUPPORT_PROP

VDS_FILE_SYSTEM_PROP_FLAG typedef SDWORD
VDS_FPF_COMPRESSED	equ 0x1

VDS_FORMAT_OPTION_FLAGS typedef SDWORD
VDS_FSOF_NONE		equ 0
VDS_FSOF_FORCE		equ 0x1
VDS_FSOF_QUICK		equ 0x2
VDS_FSOF_COMPRESSION	equ 0x4
VDS_FSOF_DUPLICATE_METADATA equ 0x8

VDS_FILE_SYSTEM_PROP	STRUC
_type			VDS_FILE_SYSTEM_TYPE ?
volumeId		VDS_OBJECT_ID <>
ulFlags			ULONG ?
ullTotalAllocationUnits ULONGLONG ?
ullAvailableAllocationUnits ULONGLONG ?
ulAllocationUnitSize	ULONG ?
pwszLabel		LPWSTR ?
VDS_FILE_SYSTEM_PROP	ENDS

PVDS_FILE_SYSTEM_PROP	typedef ptr VDS_FILE_SYSTEM_PROP

VDS_QUERY_PROVIDER_FLAG typedef SDWORD
VDS_QUERY_SOFTWARE_PROVIDERS equ 0x1
VDS_QUERY_HARDWARE_PROVIDERS equ 0x2
VDS_QUERY_VIRTUALDISK_PROVIDERS equ 0x4

externdef		__MIDL_itf_vds_0000_0051_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_vds_0000_0051_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IVdsServiceLoader_INTERFACE_DEFINED__
__IVdsServiceLoader_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsServiceLoader:IID

.comdef IVdsServiceLoader

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    LoadService		proc :LPWSTR, :ptr
    .ends

endif

ifndef __IVdsService_INTERFACE_DEFINED__
__IVdsService_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsService:IID

.comdef IVdsService

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    IsServiceReady	proc
    WaitForServiceReady proc
    GetProperties	proc :ptr
    QueryProviders	proc :DWORD, :ptr
    QueryMaskedDisks	proc :ptr
    QueryUnallocatedDisks proc :ptr
    GetObject		proc :VDS_OBJECT_ID, :VDS_OBJECT_TYPE, :ptr
    QueryDriveLetters	proc :WCHAR, :DWORD, :ptr
    QueryFileSystemTypes proc
    Reenumerate		proc
    Refresh		proc
    CleanupObsoleteMountPoints proc
    Advise		proc :ptr, :ptr
    Unadvise		proc :DWORD
    Reboot		proc
    SetFlags		proc :ULONG
    ClearFlags		proc :ULONG
    .ends

endif

ifndef __IVdsServiceUninstallDisk_INTERFACE_DEFINED__
__IVdsServiceUninstallDisk_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsServiceUninstallDisk:IID

.comdef IVdsServiceUninstallDisk

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDiskIdFromLunInfo proc :ptr, :ptr
    UninstallDisks	proc :ptr
    .ends

endif

ifndef __IVdsServiceHba_INTERFACE_DEFINED__
__IVdsServiceHba_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsServiceHba:IID

.comdef IVdsServiceHba

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    QueryHbaPorts	proc :ptr
    .ends

endif

ifndef __IVdsServiceIscsi_INTERFACE_DEFINED__
__IVdsServiceIscsi_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsServiceIscsi:IID

.comdef IVdsServiceIscsi

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetInitiatorName	proc :ptr
    QueryInitiatorAdapters proc :ptr
    SetIpsecGroupPresharedKey proc :ptr
    SetAllIpsecTunnelAddresses proc :ptr, :ptr
    SetAllIpsecSecurity proc :VDS_OBJECT_ID, :ULONGLONG, :ptr
    SetInitiatorSharedSecret proc :ptr, :VDS_OBJECT_ID
    RememberTargetSharedSecret proc :VDS_OBJECT_ID, :ptr
    .ends

endif

ifndef __IVdsServiceInitialization_INTERFACE_DEFINED__
__IVdsServiceInitialization_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsServiceInitialization:IID

.comdef IVdsServiceInitialization

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Initialize		proc :LPWSTR
    .ends

endif

ifndef __IVdsHbaPort_INTERFACE_DEFINED__
__IVdsHbaPort_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsHbaPort:IID

.comdef IVdsHbaPort

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties	proc :ptr
    SetAllPathStatuses	proc :VDS_PATH_STATUS
    .ends

endif

ifndef __IVdsIscsiInitiatorAdapter_INTERFACE_DEFINED__
__IVdsIscsiInitiatorAdapter_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsIscsiInitiatorAdapter:IID

.comdef IVdsIscsiInitiatorAdapter

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties	proc :ptr
    QueryInitiatorPortals proc :ptr
    LoginToTarget	proc :VDS_ISCSI_LOGIN_TYPE, :VDS_OBJECT_ID, :VDS_OBJECT_ID, :VDS_OBJECT_ID, :ULONG, :BOOL, :BOOL, :VDS_ISCSI_AUTH_TYPE, :ptr
    LogoutFromTarget	proc :VDS_OBJECT_ID, :ptr
    .ends

endif

ifndef __IVdsIscsiInitiatorPortal_INTERFACE_DEFINED__
__IVdsIscsiInitiatorPortal_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsIscsiInitiatorPortal:IID

.comdef IVdsIscsiInitiatorPortal

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperties	proc :ptr
    GetInitiatorAdapter proc :ptr
    SetIpsecTunnelAddress proc :ptr, :ptr
    GetIpsecSecurity	proc :VDS_OBJECT_ID, :ptr
    SetIpsecSecurity	proc :VDS_OBJECT_ID, :ULONGLONG, :ptr
    .ends

endif

ifndef __IVdsDiskPartitionMF_INTERFACE_DEFINED__
__IVdsDiskPartitionMF_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsDiskPartitionMF:IID

.comdef IVdsDiskPartitionMF

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetPartitionFileSystemProperties proc :ULONGLONG, :ptr
    GetPartitionFileSystemTypeName proc :ULONGLONG, :ptr
    QueryPartitionFileSystemFormatSupport proc :ULONGLONG
    FormatPartitionEx	proc :ULONGLONG, :LPWSTR, :USHORT, :ULONG, :LPWSTR, :BOOL, :BOOL, :BOOL, :ptr
    .ends

endif

ifndef __IVdsVolumeMF_INTERFACE_DEFINED__
__IVdsVolumeMF_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsVolumeMF:IID

.comdef IVdsVolumeMF

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetFileSystemProperties proc :ptr
    Format		proc :VDS_FILE_SYSTEM_TYPE, :LPWSTR, :DWORD, :BOOL, :BOOL, :BOOL, :ptr
    AddAccessPath	proc :LPWSTR
    QueryAccessPaths	proc
    QueryReparsePoints	proc
    DeleteAccessPath	proc
    Mount		proc
    Dismount		proc :BOOL, :BOOL
    SetFileSystemFlags	proc :ULONG
    ClearFileSystemFlags proc :ULONG
    .ends

endif

ifndef __IVdsVolumeMF2_INTERFACE_DEFINED__
__IVdsVolumeMF2_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsVolumeMF2:IID

.comdef IVdsVolumeMF2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetFileSystemTypeName proc :ptr
    QueryFileSystemFormatSupport proc
    FormatEx		proc :LPWSTR, :USHORT, :ULONG, :LPWSTR, :BOOL, :BOOL, :BOOL, :ptr
    .ends

endif

ifndef __IVdsVolumeShrink_INTERFACE_DEFINED__
__IVdsVolumeShrink_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsVolumeShrink:IID

.comdef IVdsVolumeShrink

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    QueryMaxReclaimableBytes proc :ptr
    Shrink		proc :ULONGLONG, :ULONGLONG, :ptr
    .ends

endif

ifndef __IVdsSubSystemImportTarget_INTERFACE_DEFINED__
__IVdsSubSystemImportTarget_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsSubSystemImportTarget:IID

.comdef IVdsSubSystemImportTarget

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetImportTarget	proc :ptr
    SetImportTarget	proc :LPWSTR
    .ends

endif

ifndef __IVdsIscsiPortalLocal_INTERFACE_DEFINED__
__IVdsIscsiPortalLocal_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsIscsiPortalLocal:IID

.comdef IVdsIscsiPortalLocal

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetIpsecSecurityLocal proc :ULONGLONG, :ptr
    .ends

endif

ifndef __IVdsServiceSAN_INTERFACE_DEFINED__
__IVdsServiceSAN_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsServiceSAN:IID

.comdef IVdsServiceSAN

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetSANPolicy	proc :ptr
    SetSANPolicy	proc :VDS_SAN_POLICY
    .ends

endif

ifndef __IVdsVolumeMF3_INTERFACE_DEFINED__
__IVdsVolumeMF3_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsVolumeMF3:IID

.comdef IVdsVolumeMF3

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    QueryVolumeGuidPathnames proc
    FormatEx2		proc :LPWSTR, :USHORT, :ULONG, :LPWSTR, :DWORD, :ptr
    OfflineVolume	proc
    .ends

endif

ifndef __IVdsDiskPartitionMF2_INTERFACE_DEFINED__
__IVdsDiskPartitionMF2_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsDiskPartitionMF2:IID

.comdef IVdsDiskPartitionMF2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    FormatPartitionEx2	proc :ULONGLONG, :LPWSTR, :USHORT, :ULONG, :LPWSTR, :DWORD, :ptr
    .ends

endif

ifndef __IVdsServiceSw_INTERFACE_DEFINED__
__IVdsServiceSw_INTERFACE_DEFINED__ equ 1

externdef		IID_IVdsServiceSw:IID

.comdef IVdsServiceSw

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetDiskObject	proc :LPCWSTR, :ptr
    .ends

endif
endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

externdef		__MIDL_itf_vds_0000_0070_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_vds_0000_0070_v0_0_s_ifspec:RPC_IF_HANDLE

endif


