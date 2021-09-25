ifndef _LMDFS_
define _LMDFS_

DFS_VOLUME_STATES	equ 0xF
DFS_VOLUME_STATE_OK	equ 1
DFS_VOLUME_STATE_INCONSISTENT equ 2
DFS_VOLUME_STATE_OFFLINE equ 3
DFS_VOLUME_STATE_ONLINE equ 4
DFS_VOLUME_STATE_RESYNCHRONIZE equ 0x10
DFS_VOLUME_STATE_STANDBY equ 0x20
DFS_VOLUME_STATE_FORCE_SYNC equ 0x40
DFS_VOLUME_FLAVORS	equ 0x0300
DFS_VOLUME_FLAVOR_UNUSED1 equ 0x0000
DFS_VOLUME_FLAVOR_STANDALONE equ 0x0100
DFS_VOLUME_FLAVOR_AD_BLOB equ 0x0200
DFS_STORAGE_FLAVOR_UNUSED2 equ 0x0300
DFS_STORAGE_STATES	equ 0xF
DFS_STORAGE_STATE_OFFLINE equ 1
DFS_STORAGE_STATE_ONLINE equ 2
DFS_STORAGE_STATE_ACTIVE equ 4

DFS_TARGET_PRIORITY_CLASS typedef SDWORD
DfsInvalidPriorityClass equ -1
DfsSiteCostNormalPriorityClass equ 0
DfsGlobalHighPriorityClass equ 2
DfsSiteCostHighPriorityClass equ 3
DfsSiteCostLowPriorityClass equ 4
DfsGlobalLowPriorityClass equ 5

DFS_TARGET_PRIORITY	STRUC
TargetPriorityClass	DFS_TARGET_PRIORITY_CLASS ?
TargetPriorityRank	USHORT ?
Reserved		USHORT ?
DFS_TARGET_PRIORITY	ENDS
PDFS_TARGET_PRIORITY	typedef ptr DFS_TARGET_PRIORITY

DFS_INFO_1		STRUC
EntryPath		LPWSTR ?
DFS_INFO_1		ENDS
PDFS_INFO_1		typedef ptr DFS_INFO_1
LPDFS_INFO_1		typedef ptr DFS_INFO_1

ifdef _WIN64
DFS_INFO_1_32		STRUC
EntryPath		ULONG ?
DFS_INFO_1_32		ENDS
PDFS_INFO_1_32		typedef ptr DFS_INFO_1_32
LPDFS_INFO_1_32		typedef ptr DFS_INFO_1_32
endif

DFS_INFO_2		STRUC
EntryPath		LPWSTR ?
_Comment		LPWSTR ?
State			dd ?
NumberOfStorages	dd ?
DFS_INFO_2		ENDS
PDFS_INFO_2		typedef ptr DFS_INFO_2
LPDFS_INFO_2		typedef ptr DFS_INFO_2

ifdef _WIN64
DFS_INFO_2_32		STRUC
EntryPath		ULONG ?
_Comment		ULONG ?
State			dd ?
NumberOfStorages	dd ?
DFS_INFO_2_32		ENDS
PDFS_INFO_2_32		typedef ptr DFS_INFO_2_32
LPDFS_INFO_2_32		typedef ptr DFS_INFO_2_32
endif

DFS_STORAGE_INFO	STRUC
State			ULONG ?
ServerName		LPWSTR ?
ShareName		LPWSTR ?
DFS_STORAGE_INFO	ENDS
PDFS_STORAGE_INFO	typedef ptr DFS_STORAGE_INFO
LPDFS_STORAGE_INFO	typedef ptr DFS_STORAGE_INFO

ifdef _WIN64
DFS_STORAGE_INFO_0_32	STRUC
State			ULONG ?
ServerName		ULONG ?
ShareName		ULONG ?
DFS_STORAGE_INFO_0_32	ENDS
PDFS_STORAGE_INFO_0_32	typedef ptr DFS_STORAGE_INFO_0_32
LPDFS_STORAGE_INFO_0_32 typedef ptr DFS_STORAGE_INFO_0_32
endif

DFS_STORAGE_INFO_1	STRUC
State			ULONG ?
ServerName		LPWSTR ?
ShareName		LPWSTR ?
TargetPriority		DFS_TARGET_PRIORITY <>
DFS_STORAGE_INFO_1	ENDS
PDFS_STORAGE_INFO_1	typedef ptr DFS_STORAGE_INFO_1
LPDFS_STORAGE_INFO_1	typedef ptr DFS_STORAGE_INFO_1

DFS_INFO_3		STRUC
EntryPath		LPWSTR ?
_Comment		LPWSTR ?
State			dd ?
NumberOfStorages	dd ?
Storage			LPDFS_STORAGE_INFO ?
DFS_INFO_3		ENDS
PDFS_INFO_3		typedef ptr DFS_INFO_3
LPDFS_INFO_3		typedef ptr DFS_INFO_3

ifdef _WIN64
DFS_INFO_3_32		STRUC
EntryPath		ULONG ?
_Comment		ULONG ?
State			dd ?
NumberOfStorages	dd ?
Storage			ULONG ?
DFS_INFO_3_32		ENDS
PDFS_INFO_3_32		typedef ptr DFS_INFO_3_32
LPDFS_INFO_3_32		typedef ptr DFS_INFO_3_32
endif

DFS_INFO_4		STRUC
EntryPath		LPWSTR ?
_Comment		LPWSTR ?
State			dd ?
Timeout			ULONG ?
Guid			GUID <>
NumberOfStorages	dd ?
Storage			LPDFS_STORAGE_INFO ?
DFS_INFO_4		ENDS
PDFS_INFO_4		typedef ptr DFS_INFO_4
LPDFS_INFO_4		typedef ptr DFS_INFO_4


ifdef _WIN64

DFS_INFO_4_32		STRUC
EntryPath		ULONG ?
_Comment		ULONG ?
State			dd ?
Timeout			ULONG ?
Guid			GUID <>
NumberOfStorages	dd ?
Storage			ULONG ?
DFS_INFO_4_32		ENDS
PDFS_INFO_4_32		typedef ptr DFS_INFO_4_32
LPDFS_INFO_4_32		typedef ptr DFS_INFO_4_32

endif

DFS_INFO_5		STRUC
EntryPath		LPWSTR ?
_Comment		LPWSTR ?
State			dd ?
Timeout			ULONG ?
Guid			GUID <>
PropertyFlags		ULONG ?
MetadataSize		ULONG ?
NumberOfStorages	dd ?
DFS_INFO_5		ENDS
PDFS_INFO_5		typedef ptr DFS_INFO_5
LPDFS_INFO_5		typedef ptr DFS_INFO_5

DFS_INFO_6		STRUC
EntryPath		LPWSTR ?
_Comment		LPWSTR ?
State			dd ?
Timeout			ULONG ?
Guid			GUID <>
PropertyFlags		ULONG ?
MetadataSize		ULONG ?
NumberOfStorages	dd ?
Storage			LPDFS_STORAGE_INFO_1 ?
DFS_INFO_6		ENDS
PDFS_INFO_6		typedef ptr DFS_INFO_6
LPDFS_INFO_6		typedef ptr DFS_INFO_6

DFS_INFO_7		STRUC
GenerationGuid		GUID <>
DFS_INFO_7		ENDS
PDFS_INFO_7		typedef ptr DFS_INFO_7
LPDFS_INFO_7		typedef ptr DFS_INFO_7

DFS_INFO_8		STRUC
EntryPath		LPWSTR ?
_Comment		LPWSTR ?
State			dd ?
Timeout			ULONG ?
Guid			GUID <>
PropertyFlags		ULONG ?
MetadataSize		ULONG ?
SdLengthReserved	ULONG ?
pSecurityDescriptor	PSECURITY_DESCRIPTOR ?
NumberOfStorages	dd ?
DFS_INFO_8		ENDS
PDFS_INFO_8		typedef ptr DFS_INFO_8
LPDFS_INFO_8		typedef ptr DFS_INFO_8

DFS_INFO_9		STRUC
EntryPath		LPWSTR ?
_Comment		LPWSTR ?
State			dd ?
Timeout			ULONG ?
Guid			GUID <>
PropertyFlags		ULONG ?
MetadataSize		ULONG ?
SdLengthReserved	ULONG ?
pSecurityDescriptor	PSECURITY_DESCRIPTOR ?
NumberOfStorages	dd ?
Storage			LPDFS_STORAGE_INFO_1 ?
DFS_INFO_9		ENDS
PDFS_INFO_9		typedef ptr DFS_INFO_9
LPDFS_INFO_9		typedef ptr DFS_INFO_9


DFS_VALID_PROPERTY_FLAGS equ (DFS_PROPERTY_FLAG_INSITE_REFERRALS OR DFS_PROPERTY_FLAG_ROOT_SCALABILITY OR \
			      DFS_PROPERTY_FLAG_SITE_COSTING OR DFS_PROPERTY_FLAG_TARGET_FAILBACK OR \
			      DFS_PROPERTY_FLAG_CLUSTER_ENABLED OR DFS_PROPERTY_FLAG_ABDE)

DFS_PROPERTY_FLAG_INSITE_REFERRALS equ 0x00000001
DFS_PROPERTY_FLAG_ROOT_SCALABILITY equ 0x00000002
DFS_PROPERTY_FLAG_SITE_COSTING equ 0x00000004
DFS_PROPERTY_FLAG_TARGET_FAILBACK equ 0x00000008
DFS_PROPERTY_FLAG_CLUSTER_ENABLED equ 0x00000010
DFS_PROPERTY_FLAG_ABDE	equ 0x00000020

DFS_INFO_50		STRUC
NamespaceMajorVersion	ULONG ?
NamespaceMinorVersion	ULONG ?
NamespaceCapabilities	ULONGLONG ?
DFS_INFO_50		ENDS
PDFS_INFO_50		typedef ptr DFS_INFO_50
LPDFS_INFO_50		typedef ptr DFS_INFO_50


DFS_INFO_100		STRUC
_Comment		LPWSTR ?
DFS_INFO_100		ENDS
PDFS_INFO_100		typedef ptr DFS_INFO_100
LPDFS_INFO_100		typedef ptr DFS_INFO_100

DFS_INFO_101		STRUC
State			dd ?
DFS_INFO_101		ENDS
PDFS_INFO_101		typedef ptr DFS_INFO_101
LPDFS_INFO_101		typedef ptr DFS_INFO_101

DFS_INFO_102		STRUC
Timeout			ULONG ?
DFS_INFO_102		ENDS
PDFS_INFO_102		typedef ptr DFS_INFO_102
LPDFS_INFO_102		typedef ptr DFS_INFO_102

DFS_INFO_103		STRUC
PropertyFlagMask	ULONG ?
PropertyFlags		ULONG ?
DFS_INFO_103		ENDS
PDFS_INFO_103		typedef ptr DFS_INFO_103
LPDFS_INFO_103		typedef ptr DFS_INFO_103


DFS_INFO_104		STRUC
TargetPriority		DFS_TARGET_PRIORITY <>
DFS_INFO_104		ENDS
PDFS_INFO_104		typedef ptr DFS_INFO_104
LPDFS_INFO_104		typedef ptr DFS_INFO_104

DFS_INFO_105		STRUC
Comment			LPWSTR ?
State			dd ?
Timeout			ULONG ?
PropertyFlagMask	ULONG ?
PropertyFlags		ULONG ?
DFS_INFO_105		ENDS
PDFS_INFO_105		typedef ptr DFS_INFO_105
LPDFS_INFO_105		typedef ptr DFS_INFO_105

DFS_INFO_106		STRUC
State			dd ?
TargetPriority		DFS_TARGET_PRIORITY <>
DFS_INFO_106		ENDS
PDFS_INFO_106		typedef ptr DFS_INFO_106
LPDFS_INFO_106		typedef ptr DFS_INFO_106

DFS_INFO_107		STRUC
Comment			LPWSTR ?
State			dd ?
Timeout			ULONG ?
PropertyFlagMask	ULONG ?
PropertyFlags		ULONG ?

SdLengthReserved	ULONG ?
pSecurityDescriptor	PSECURITY_DESCRIPTOR ?
DFS_INFO_107		ENDS
PDFS_INFO_107		typedef ptr DFS_INFO_107
LPDFS_INFO_107		typedef ptr DFS_INFO_107

DFS_INFO_150		STRUC
SdLengthReserved	ULONG ?
pSecurityDescriptor	PSECURITY_DESCRIPTOR ?
DFS_INFO_150		ENDS
PDFS_INFO_150		typedef ptr DFS_INFO_150
LPDFS_INFO_150		typedef ptr DFS_INFO_150


DFS_INFO_200		STRUC
FtDfsName		LPWSTR ?
DFS_INFO_200		ENDS
PDFS_INFO_200		typedef ptr DFS_INFO_200
LPDFS_INFO_200		typedef ptr DFS_INFO_200


DFS_INFO_300		STRUC
Flags			dd ?
DfsName			LPWSTR ?
DFS_INFO_300		ENDS
PDFS_INFO_300		typedef ptr DFS_INFO_300
LPDFS_INFO_300		typedef ptr DFS_INFO_300


;NET_API_STATUS
NetDfsAdd proto WINAPI \
	  DfsEntryPath: LPWSTR,
	    ServerName: LPWSTR,
	     ShareName: LPWSTR,
	      _Comment: LPWSTR,
		 Flags: DWORD


DFS_ADD_VOLUME		equ 1
DFS_RESTORE_VOLUME	equ 2


;NET_API_STATUS
NetDfsAddStdRoot proto WINAPI \
	    ServerName: LPWSTR,
	     RootShare: LPWSTR,
	      _Comment: LPWSTR,
		 Flags: DWORD

;NET_API_STATUS
NetDfsRemoveStdRoot proto WINAPI \
	    ServerName: LPWSTR,
	     RootShare: LPWSTR,
		 Flags: DWORD

;NET_API_STATUS
NetDfsAddFtRoot proto WINAPI \
	    ServerName: LPWSTR,
	     RootShare: LPWSTR,
	     FtDfsName: LPWSTR,
	      _Comment: LPWSTR,
		 Flags: DWORD

;NET_API_STATUS
NetDfsRemoveFtRoot proto WINAPI \
	    ServerName: LPWSTR,
	     RootShare: LPWSTR,
	     FtDfsName: LPWSTR,
		 Flags: DWORD

;NET_API_STATUS
NetDfsRemoveFtRootForced proto WINAPI \
	    DomainName: LPWSTR,
	    ServerName: LPWSTR,
	     RootShare: LPWSTR,
	     FtDfsName: LPWSTR,
		 Flags: DWORD

;NET_API_STATUS
NetDfsManagerInitialize proto WINAPI \
	    ServerName: LPWSTR,
		 Flags: DWORD


;NET_API_STATUS
NetDfsAddStdRootForced proto WINAPI \
	    ServerName: LPWSTR,
	     RootShare: LPWSTR,
	      _Comment: LPWSTR,
		 Store: LPWSTR


;NET_API_STATUS
NetDfsGetDcAddress proto WINAPI \
	    ServerName: LPWSTR,
	   DcIpAddress: ptr LPWSTR,
		IsRoot: PBOOLEAN,
	       Timeout: PULONG

NET_DFS_SETDC_FLAGS	equ 0x00000000
NET_DFS_SETDC_TIMEOUT	equ 0x00000001
NET_DFS_SETDC_INITPKT	equ 0x00000002


DFS_SITENAME_INFO	STRUC
SiteFlags		ULONG ?
SiteName		LPWSTR ?
DFS_SITENAME_INFO	ENDS
PDFS_SITENAME_INFO	typedef ptr DFS_SITENAME_INFO
LPDFS_SITENAME_INFO	typedef ptr DFS_SITENAME_INFO

DFS_SITE_PRIMARY	equ 0x1

DFS_SITELIST_INFO	STRUC
cSites			ULONG ?
Site			DFS_SITENAME_INFO 1 dup(<>)
DFS_SITELIST_INFO	ENDS
PDFS_SITELIST_INFO	typedef ptr DFS_SITELIST_INFO
LPDFS_SITELIST_INFO	typedef ptr DFS_SITELIST_INFO

;NET_API_STATUS
NetDfsRemove proto WINAPI \
	  DfsEntryPath: LPWSTR,
	    ServerName: LPWSTR,
	     ShareName: LPWSTR


;NET_API_STATUS
NetDfsEnum proto WINAPI \
	       DfsName: LPWSTR,
		 Level: DWORD,
	    PrefMaxLen: DWORD,
		Buffer: ptr LPBYTE,
	   EntriesRead: LPDWORD,
	  ResumeHandle: LPDWORD


;NET_API_STATUS
NetDfsGetInfo proto WINAPI \
	  DfsEntryPath: LPWSTR,
	    ServerName: LPWSTR,
	     ShareName: LPWSTR,
		 Level: DWORD,
		Buffer: ptr LPBYTE


;NET_API_STATUS
NetDfsSetInfo proto WINAPI \
	  DfsEntryPath: LPWSTR,
	    ServerName: LPWSTR,
	     ShareName: LPWSTR,
		 Level: DWORD,
		Buffer: LPBYTE


;NET_API_STATUS
NetDfsGetClientInfo proto WINAPI \
	  DfsEntryPath: LPWSTR,
	    ServerName: LPWSTR,
	     ShareName: LPWSTR,
		 Level: DWORD,
		Buffer: ptr LPBYTE

;NET_API_STATUS
NetDfsSetClientInfo proto WINAPI \
	  DfsEntryPath: LPWSTR,
	    ServerName: LPWSTR,
	     ShareName: LPWSTR,
		 Level: DWORD,
		Buffer: LPBYTE


;NET_API_STATUS
NetDfsMove proto WINAPI \
       OldDfsEntryPath: LPWSTR,
       NewDfsEntryPath: LPWSTR,
		 Flags: ULONG

DFS_MOVE_FLAG_REPLACE_IF_EXISTS equ 0x00000001

;NET_API_STATUS
NetDfsRename proto WINAPI \
		  Path: LPWSTR,
	       NewPath: LPWSTR

;NET_API_STATUS
NetDfsAddRootTarget proto WINAPI \
	      pDfsPath: LPWSTR,
	   pTargetPath: LPWSTR,
	  MajorVersion: ULONG,
	      pComment: LPWSTR,
		 Flags: ULONG

ifndef DFS_FORCE_REMOVE
DFS_FORCE_REMOVE	equ 0x80000000
endif

;NET_API_STATUS
NetDfsRemoveRootTarget proto WINAPI \
	      pDfsPath: LPWSTR,
	   pTargetPath: LPWSTR,
		 Flags: ULONG

;NET_API_STATUS
NetDfsGetSecurity proto WINAPI \
	  DfsEntryPath: LPWSTR,
   SecurityInformation: SECURITY_INFORMATION,
  ppSecurityDescriptor: ptr PSECURITY_DESCRIPTOR,
lpcbSecurityDescriptor: LPDWORD

;NET_API_STATUS
NetDfsSetSecurity proto WINAPI \
	  DfsEntryPath: LPWSTR,
   SecurityInformation: SECURITY_INFORMATION,
   pSecurityDescriptor: PSECURITY_DESCRIPTOR

;NET_API_STATUS
NetDfsGetStdContainerSecurity proto WINAPI \
	   MachineName: LPWSTR,
   SecurityInformation: SECURITY_INFORMATION,
  ppSecurityDescriptor: ptr PSECURITY_DESCRIPTOR,
lpcbSecurityDescriptor: LPDWORD

;NET_API_STATUS
NetDfsSetStdContainerSecurity proto WINAPI \
	   MachineName: LPWSTR,
   SecurityInformation: SECURITY_INFORMATION,
   pSecurityDescriptor: PSECURITY_DESCRIPTOR

;NET_API_STATUS
NetDfsGetFtContainerSecurity proto WINAPI \
	    DomainName: LPWSTR,
   SecurityInformation: SECURITY_INFORMATION,
  ppSecurityDescriptor: ptr PSECURITY_DESCRIPTOR,
lpcbSecurityDescriptor: LPDWORD

;NET_API_STATUS
NetDfsSetFtContainerSecurity proto WINAPI \
	    DomainName: LPWSTR,
   SecurityInformation: SECURITY_INFORMATION,
   pSecurityDescriptor: PSECURITY_DESCRIPTOR

DFS_NAMESPACE_VERSION_ORIGIN	typedef SDWORD
PDFS_NAMESPACE_VERSION_ORIGIN	typedef ptr SDWORD

DFS_NAMESPACE_VERSION_ORIGIN_COMBINED equ 0
DFS_NAMESPACE_VERSION_ORIGIN_SERVER equ 1
DFS_NAMESPACE_VERSION_ORIGIN_DOMAIN equ 2

DFS_NAMESPACE_CAPABILITY_ABDE equ (0x0000000000000001)

DFS_SUPPORTED_NAMESPACE_VERSION_INFO  STRUC
DomainDfsMajorVersion	ULONG ?
DomainDfsMinorVersion	ULONG ?
DomainDfsCapabilities	ULONGLONG ?
StandaloneDfsMajorVersion ULONG ?
StandaloneDfsMinorVersion ULONG ?
StandaloneDfsCapabilities ULONGLONG ?
DFS_SUPPORTED_NAMESPACE_VERSION_INFO ENDS
PDFS_SUPPORTED_NAMESPACE_VERSION_INFO typedef ptr DFS_SUPPORTED_NAMESPACE_VERSION_INFO

;NET_API_STATUS
NetDfsGetSupportedNamespaceVersion proto WINAPI \
		Origin: DFS_NAMESPACE_VERSION_ORIGIN,
		 pName: PWSTR,
	 ppVersionInfo: ptr PDFS_SUPPORTED_NAMESPACE_VERSION_INFO

endif
