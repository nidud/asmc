ifndef _LMSHARE_
_LMSHARE_ equ <>

include lmcons.inc

;NET_API_STATUS
NetShareAdd proto WINAPI \
	    servername: LMSTR,
		 level: DWORD,
		   buf: LPBYTE,
	      parm_err: LPDWORD

;NET_API_STATUS
NetShareEnum proto WINAPI \
	    servername: LMSTR,
		 level: DWORD,
		bufptr: ptr LPBYTE,
	    prefmaxlen: DWORD,
	   entriesread: LPDWORD,
	  totalentries: LPDWORD,
	 resume_handle: LPDWORD

;NET_API_STATUS
NetShareEnumSticky proto WINAPI \
	    servername: LMSTR,
		 level: DWORD,
		bufptr: ptr LPBYTE,
	    prefmaxlen: DWORD,
	   entriesread: LPDWORD,
	  totalentries: LPDWORD,
	 resume_handle: LPDWORD

;NET_API_STATUS
NetShareGetInfo proto WINAPI \
	    servername: LMSTR,
	       netname: LMSTR,
		 level: DWORD,
		bufptr: ptr LPBYTE

;NET_API_STATUS
NetShareSetInfo proto WINAPI \
	    servername: LMSTR,
	       netname: LMSTR,
		 level: DWORD,
		   buf: LPBYTE,
	      parm_err: LPDWORD

;NET_API_STATUS
NetShareDel proto WINAPI \
	    servername: LMSTR,
	       netname: LMSTR,
	      reserved: DWORD

;NET_API_STATUS
NetShareDelSticky proto WINAPI \
	    servername: LMSTR,
	       netname: LMSTR,
	      reserved: DWORD


;NET_API_STATUS
NetShareCheck proto WINAPI \
	    servername: LMSTR,
		device: LMSTR,
		  type: LPDWORD

;NET_API_STATUS
NetShareDelEx proto WINAPI \
	    servername: LMSTR,
		 level: DWORD,
		   buf: LPBYTE

SHARE_INFO_0		STRUC
shi0_netname		LMSTR ?
SHARE_INFO_0		ENDS
PSHARE_INFO_0		typedef ptr SHARE_INFO_0
LPSHARE_INFO_0		typedef ptr SHARE_INFO_0

SHARE_INFO_1		STRUC
shi1_netname		LMSTR ?
shi1_type		dd ?
shi1_remark		LMSTR ?
SHARE_INFO_1		ENDS
PSHARE_INFO_1		typedef ptr SHARE_INFO_1
LPSHARE_INFO_1		typedef ptr SHARE_INFO_1

SHARE_INFO_2		STRUC
shi2_netname		LMSTR ?
shi2_type		dd ?
shi2_remark		LMSTR ?
shi2_permissions	dd ?
shi2_max_uses		dd ?
shi2_current_uses	dd ?
shi2_path		LMSTR ?
shi2_passwd		LMSTR ?
SHARE_INFO_2		ENDS
PSHARE_INFO_2		typedef ptr SHARE_INFO_2
LPSHARE_INFO_2		typedef ptr SHARE_INFO_2

SHARE_INFO_501		STRUC
shi501_netname		LMSTR ?
shi501_type		dd ?
shi501_remark		LMSTR ?
shi501_flags		dd ?
SHARE_INFO_501		ENDS
PSHARE_INFO_501		typedef ptr SHARE_INFO_501
LPSHARE_INFO_501	typedef ptr SHARE_INFO_501

SHARE_INFO_502		STRUC
shi502_netname		LMSTR ?
shi502_type		dd ?
shi502_remark		LMSTR ?
shi502_permissions	dd ?
shi502_max_uses		dd ?
shi502_current_uses	dd ?
shi502_path		LMSTR ?
shi502_passwd		LMSTR ?
shi502_reserved		dd ?
shi502_security_descriptor PSECURITY_DESCRIPTOR ?
SHARE_INFO_502		ENDS
PSHARE_INFO_502		typedef ptr SHARE_INFO_502
LPSHARE_INFO_502	typedef ptr SHARE_INFO_502

SHARE_INFO_503		STRUC
shi503_netname		LMSTR ?
shi503_type		dd ?
shi503_remark		LMSTR ?
shi503_permissions	dd ?
shi503_max_uses		dd ?
shi503_current_uses	dd ?
shi503_path		LMSTR ?
shi503_passwd		LMSTR ?
shi503_servername	LMSTR ?
shi503_reserved		dd ?
shi503_security_descriptor PSECURITY_DESCRIPTOR ?
SHARE_INFO_503		ENDS
PSHARE_INFO_503		typedef ptr SHARE_INFO_503
LPSHARE_INFO_503	typedef ptr SHARE_INFO_503

SHARE_INFO_1004		STRUC
shi1004_remark		LMSTR ?
SHARE_INFO_1004		ENDS
PSHARE_INFO_1004	typedef ptr SHARE_INFO_1004
LPSHARE_INFO_1004	typedef ptr SHARE_INFO_1004

SHARE_INFO_1005		STRUC
shi1005_flags		dd ?
SHARE_INFO_1005		ENDS
PSHARE_INFO_1005	typedef ptr SHARE_INFO_1005
LPSHARE_INFO_1005	typedef ptr SHARE_INFO_1005

SHARE_INFO_1006		STRUC
shi1006_max_uses	dd ?
SHARE_INFO_1006		ENDS
PSHARE_INFO_1006	typedef ptr SHARE_INFO_1006
LPSHARE_INFO_1006	typedef ptr SHARE_INFO_1006

SHARE_INFO_1501		STRUC
shi1501_reserved	dd ?
shi1501_security_descriptor PSECURITY_DESCRIPTOR ?
SHARE_INFO_1501		ENDS
PSHARE_INFO_1501	typedef ptr SHARE_INFO_1501
LPSHARE_INFO_1501	typedef ptr SHARE_INFO_1501

SHARE_INFO_1503		STRUC
shi1503_sharefilter	GUID <>
SHARE_INFO_1503		ENDS
PSHARE_INFO_1503	typedef ptr SHARE_INFO_1503
LPSHARE_INFO_1503	typedef ptr SHARE_INFO_1503

;NET_API_STATUS
NetServerAliasAdd proto WINAPI \
	    servername: LMSTR,
		 level: DWORD,
		   buf: LPBYTE

;NET_API_STATUS
NetServerAliasDel proto WINAPI \
	    servername: LMSTR,
		 level: DWORD,
		   buf: LPBYTE

;NET_API_STATUS
NetServerAliasEnum proto WINAPI \
	    servername: LMSTR,
		 level: DWORD,
		bufptr: ptr LPBYTE,
	    prefmaxlen: DWORD,
	   entriesread: LPDWORD,
	  totalentries: LPDWORD,
	  resumehandle: LPDWORD


SERVER_ALIAS_INFO_0	STRUC
srvai0_alias		LMSTR ?
srvai0_target		LMSTR ?
srvai0_default		BOOLEAN ?
srvai0_reserved		ULONG ?
SERVER_ALIAS_INFO_0	ENDS
PSERVER_ALIAS_INFO_0	typedef ptr SERVER_ALIAS_INFO_0
LPSERVER_ALIAS_INFO_0	typedef ptr SERVER_ALIAS_INFO_0

SHARE_NETNAME_PARMNUM	equ 1
SHARE_TYPE_PARMNUM	equ 3
SHARE_REMARK_PARMNUM	equ 4
SHARE_PERMISSIONS_PARMNUM equ 5
SHARE_MAX_USES_PARMNUM	equ 6
SHARE_CURRENT_USES_PARMNUM equ 7
SHARE_PATH_PARMNUM	equ 8
SHARE_PASSWD_PARMNUM	equ 9
SHARE_FILE_SD_PARMNUM	equ 501
SHARE_SERVER_PARMNUM	equ 503

SHARE_REMARK_INFOLEVEL	equ (PARMNUM_BASE_INFOLEVE + SHARE_REMARK_PARMNUM)
SHARE_MAX_USES_INFOLEVEL equ (PARMNUM_BASE_INFOLEVE + SHARE_MAX_USES_PARMNUM)
SHARE_FILE_SD_INFOLEVEL equ (PARMNUM_BASE_INFOLEVE + SHARE_FILE_SD_PARMNUM)

SHI1_NUM_ELEMENTS	equ 4
SHI2_NUM_ELEMENTS	equ 10

STYPE_DISKTREE		equ 0
STYPE_PRINTQ		equ 1
STYPE_DEVICE		equ 2
STYPE_IPC		equ 3

STYPE_TEMPORARY		equ 0x40000000
STYPE_SPECIAL		equ 0x80000000

SHI_USES_UNLIMITED	equ -1

SHI1005_FLAGS_DFS	equ 0x0001
SHI1005_FLAGS_DFS_ROOT	equ 0x0002

CSC_MASK_EXT		equ 0x2030
CSC_MASK		equ 0x0030

CSC_CACHE_MANUAL_REINT	equ 0x0000
CSC_CACHE_AUTO_REINT	equ 0x0010
CSC_CACHE_VDO		equ 0x0020
CSC_CACHE_NONE		equ 0x0030

SHI1005_FLAGS_RESTRICT_EXCLUSIVE_OPENS equ 0x0100
SHI1005_FLAGS_FORCE_SHARED_DELETE equ 0x0200
SHI1005_FLAGS_ALLOW_NAMESPACE_CACHING equ 0x0400
SHI1005_FLAGS_ACCESS_BASED_DIRECTORY_ENUM equ 0x0800
SHI1005_FLAGS_FORCE_LEVELII_OPLOCK equ 0x1000
SHI1005_FLAGS_ENABLE_HASH equ 0x2000

SHI1005_VALID_FLAGS_SET equ (CSC_MASK OR SHI1005_FLAGS_RESTRICT_EXCLUSIVE_OPENS OR \
	SHI1005_FLAGS_FORCE_SHARED_DELETE OR SHI1005_FLAGS_ALLOW_NAMESPACE_CACHING OR \
	SHI1005_FLAGS_ACCESS_BASED_DIRECTORY_ENUM OR SHI1005_FLAGS_FORCE_LEVELII_OPLOCK OR \
	SHI1005_FLAGS_ENABLE_HASH)

endif


ifndef _LMSESSION_
_LMSESSION_ equ <>

;NET_API_STATUS
NetSessionEnum proto WINAPI \
	    servername: LMSTR,
	 UncClientName: LMSTR,
	      username: LMSTR,
		 level: DWORD,
		bufptr: ptr LPBYTE,
	    prefmaxlen: DWORD,
	   entriesread: LPDWORD,
	  totalentries: LPDWORD,
	 resume_handle: LPDWORD

;NET_API_STATUS
NetSessionDel proto WINAPI \
	    servername: LMSTR,
	 UncClientName: LMSTR,
	      username: LMSTR

;NET_API_STATUS
NetSessionGetInfo proto WINAPI \
	    servername: LMSTR,
	 UncClientName: LMSTR,
	      username: LMSTR,
		 level: DWORD,
		bufptr: ptr LPBYTE


SESSION_INFO_0		STRUC
sesi0_cname		LMSTR ?
SESSION_INFO_0		ENDS
PSESSION_INFO_0		typedef ptr SESSION_INFO_0
LPSESSION_INFO_0	typedef ptr SESSION_INFO_0

SESSION_INFO_1		STRUC
sesi1_cname		LMSTR ?
sesi1_username		LMSTR ?
sesi1_num_opens		dd ?
sesi1_time		dd ?
sesi1_idle_time		dd ?
sesi1_user_flags	dd ?
SESSION_INFO_1		ENDS
PSESSION_INFO_1		typedef ptr SESSION_INFO_1
LPSESSION_INFO_1	typedef ptr SESSION_INFO_1

SESSION_INFO_2		STRUC
sesi2_cname		LMSTR ?
sesi2_username		LMSTR ?
sesi2_num_opens		dd ?
sesi2_time		dd ?
sesi2_idle_time		dd ?
sesi2_user_flags	dd ?
sesi2_cltype_name	LMSTR ?
SESSION_INFO_2		ENDS
PSESSION_INFO_2		typedef ptr SESSION_INFO_2
LPSESSION_INFO_2	typedef ptr SESSION_INFO_2

SESSION_INFO_10		STRUC
sesi10_cname		LMSTR ?
sesi10_username		LMSTR ?
sesi10_time		dd ?
sesi10_idle_time	dd ?
SESSION_INFO_10		ENDS
PSESSION_INFO_10	typedef ptr SESSION_INFO_10
LPSESSION_INFO_10	typedef ptr SESSION_INFO_10

SESSION_INFO_502	STRUC
sesi502_cname		LMSTR ?
sesi502_username	LMSTR ?
sesi502_num_opens	dd ?
sesi502_time		dd ?
sesi502_idle_time	dd ?
sesi502_user_flags	dd ?
sesi502_cltype_name	LMSTR ?
sesi502_transport	LMSTR ?
SESSION_INFO_502	ENDS
PSESSION_INFO_502	typedef ptr SESSION_INFO_502
LPSESSION_INFO_502	typedef ptr SESSION_INFO_502

SESS_GUEST		equ 0x00000001
SESS_NOENCRYPTION	equ 0x00000002

SESI1_NUM_ELEMENTS	equ 8
SESI2_NUM_ELEMENTS	equ 9

endif

ifndef _LMCONNECTION_
_LMCONNECTION_ equ <>

;NET_API_STATUS
NetConnectionEnum proto WINAPI \
	    servername: LMSTR,
	     qualifier: LMSTR,
		 level: DWORD,
		bufptr: ptr LPBYTE,
	    prefmaxlen: DWORD,
	   entriesread: LPDWORD,
	  totalentries: LPDWORD,
	 resume_handle: LPDWORD


CONNECTION_INFO_0	STRUC
coni0_id		dd ?
CONNECTION_INFO_0	ENDS
PCONNECTION_INFO_0	typedef ptr CONNECTION_INFO_0
LPCONNECTION_INFO_0	typedef ptr CONNECTION_INFO_0

CONNECTION_INFO_1	STRUC
coni1_id		dd ?
coni1_type		dd ?
coni1_num_opens		dd ?
coni1_num_users		dd ?
coni1_time		dd ?
coni1_username		LMSTR ?
coni1_netname		LMSTR ?
CONNECTION_INFO_1	ENDS
PCONNECTION_INFO_1	typedef ptr CONNECTION_INFO_1
LPCONNECTION_INFO_1	typedef ptr CONNECTION_INFO_1

endif

ifndef _LMFILE_
_LMFILE_ equ <>

;NET_API_STATUS
NetFileClose proto WINAPI \
	    servername: LMSTR,
		fileid: DWORD

;NET_API_STATUS
NetFileEnum proto WINAPI \
	    servername: LMSTR,
	      basepath: LMSTR,
	      username: LMSTR,
		 level: DWORD,
		bufptr: ptr LPBYTE,
	    prefmaxlen: DWORD,
	   entriesread: LPDWORD,
	  totalentries: LPDWORD,
	 resume_handle: PDWORD_PTR

;NET_API_STATUS
NetFileGetInfo proto WINAPI \
	    servername: LMSTR,
		fileid: DWORD,
		 level: DWORD,
		bufptr: ptr LPBYTE

FILE_INFO_2		STRUC
fi2_id			dd ?
FILE_INFO_2		ENDS
PFILE_INFO_2		typedef ptr FILE_INFO_2
LPFILE_INFO_2		typedef ptr FILE_INFO_2

FILE_INFO_3		STRUC
fi3_id			dd ?
fi3_permissions		dd ?
fi3_num_locks		dd ?
fi3_pathname		LMSTR ?
fi3_username		LMSTR ?
FILE_INFO_3		ENDS
PFILE_INFO_3		typedef ptr FILE_INFO_3
LPFILE_INFO_3		typedef ptr FILE_INFO_3

PERM_FILE_READ		equ 0x1
PERM_FILE_WRITE		equ 0x2
PERM_FILE_CREATE	equ 0x4

endif
