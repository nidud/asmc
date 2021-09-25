ifndef _LMREMUTL_
define _LMREMUTL_

ifndef DESC_CHAR_UNICODE
DESC_CHAR		typedef CHAR
LPDESC			typedef LPSTR
else
DESC_CHAR		typedef WCHAR
LPDESC			typedef LPWSTR
endif

;NET_API_STATUS
NetRemoteTOD proto WINAPI \
	 UncServerName: LPCWSTR,
	     BufferPtr: ptr LPBYTE

;NET_API_STATUS
NetRemoteComputerSupports proto WINAPI \
	 UncServerName: LPCWSTR,
	 OptionsWanted: DWORD,
      OptionsSupported: LPDWORD

;NET_API_STATUS
RxRemoteApi proto _CDecl \
	     ApiNumber: DWORD,
	 UncServerName: LPCWSTR,
	ParmDescString: LPDESC,
	    DataDesc16: LPDESC,
	    DataDesc32: LPDESC,
	   DataDescSmb: LPDESC,
	     AuxDesc16: LPDESC,
	     AuxDesc32: LPDESC,
	    AuxDescSmb: LPDESC,
		 Flags: DWORD,
		      : VARARG


TIME_OF_DAY_INFO	STRUC
tod_elapsedt		dd ?
tod_msecs		dd ?
tod_hours		dd ?
tod_mins		dd ?
tod_secs		dd ?
tod_hunds		dd ?
tod_timezone		LONG ?
tod_tinterval		dd ?
tod_day			dd ?
tod_month		dd ?
tod_year		dd ?
tod_weekday		dd ?
TIME_OF_DAY_INFO	ENDS
PTIME_OF_DAY_INFO	typedef ptr TIME_OF_DAY_INFO
LPTIME_OF_DAY_INFO	typedef ptr TIME_OF_DAY_INFO



SUPPORTS_REMOTE_ADMIN_PROTOCOL equ 0x00000002
SUPPORTS_RPC		equ 0x00000004
SUPPORTS_SAM_PROTOCOL	equ 0x00000008
SUPPORTS_UNICODE	equ 0x00000010
SUPPORTS_LOCAL		equ 0x00000020
SUPPORTS_ANY		equ 0xFFFFFFFF


NO_PERMISSION_REQUIRED	equ 0x00000001
ALLOCATE_RESPONSE	equ 0x00000002
USE_SPECIFIC_TRANSPORT	equ 0x80000000

endif
