ifndef _LMUSE_
_LMUSE_ equ <>

include lmcons.inc
include lmuseflg.inc

;NET_API_STATUS
NetUseAdd proto WINAPI \
	 UncServerName: LMSTR,
		 Level: DWORD,
		   Buf: LPBYTE,
	     ParmError: LPDWORD

;NET_API_STATUS
NetUseDel proto WINAPI \
	 UncServerName: LMSTR,
	       UseName: LMSTR,
	     ForceCond: DWORD

;NET_API_STATUS
NetUseEnum proto WINAPI \
	 UncServerName: LMSTR,
		 Level: DWORD,
		BufPtr: ptr LPBYTE,
   PreferedMaximumSize: DWORD,
	   EntriesRead: LPDWORD,
	  TotalEntries: LPDWORD,
	  ResumeHandle: LPDWORD


;NET_API_STATUS
NetUseGetInfo proto WINAPI \
	 UncServerName: LMSTR,
	       UseName: LMSTR,
		 Level: DWORD,
		BufPtr: ptr LPBYTE


USE_INFO_0		STRUC
ui0_local		LMSTR ?
ui0_remote		LMSTR ?
USE_INFO_0		ENDS
PUSE_INFO_0		typedef ptr USE_INFO_0
LPUSE_INFO_0		typedef ptr USE_INFO_0

USE_INFO_1		STRUC
ui1_local		LMSTR ?
ui1_remote		LMSTR ?
ui1_password		LMSTR ?
ui1_status		dd ?
ui1_asg_type		dd ?
ui1_refcount		dd ?
ui1_usecount		dd ?
USE_INFO_1		ENDS
PUSE_INFO_1		typedef ptr USE_INFO_1
LPUSE_INFO_1		typedef ptr USE_INFO_1

USE_INFO_2		STRUC
ui2_local		LMSTR ?
ui2_remote		LMSTR ?
ui2_password		LMSTR ?
ui2_status		dd ?
ui2_asg_type		dd ?
ui2_refcount		dd ?
ui2_usecount		dd ?
ui2_username		LMSTR ?
ui2_domainname		LMSTR ?
USE_INFO_2		ENDS
PUSE_INFO_2		typedef ptr USE_INFO_2
LPUSE_INFO_2		typedef ptr USE_INFO_2

USE_INFO_3		STRUC
ui3_ui2			USE_INFO_2 <>
ui3_flags		ULONG ?
USE_INFO_3		ENDS
PUSE_INFO_3		typedef ptr USE_INFO_3
LPUSE_INFO_3		typedef ptr USE_INFO_3

USE_INFO_4		STRUC
ui4_ui3			USE_INFO_3 <>
ui4_auth_identity_length dd ?
ui4_auth_identity	PBYTE ?
USE_INFO_4		ENDS
PUSE_INFO_4		typedef ptr USE_INFO_4
LPUSE_INFO_4		typedef ptr USE_INFO_4

USE_LOCAL_PARMNUM	equ 1
USE_REMOTE_PARMNUM	equ 2
USE_PASSWORD_PARMNUM	equ 3
USE_ASGTYPE_PARMNUM	equ 4
USE_USERNAME_PARMNUM	equ 5
USE_DOMAINNAME_PARMNUM	equ 6

USE_OK			equ 0
USE_PAUSED		equ 1
USE_SESSLOST		equ 2
USE_DISCONN		equ 2
USE_NETERR		equ 3
USE_CONN		equ 4
USE_RECONN		equ 5

USE_WILDCARD		equ (-1)
USE_DISKDEV		equ 0
USE_SPOOLDEV		equ 1
USE_CHARDEV		equ 2
USE_IPC			equ 3

CREATE_NO_CONNECT	equ 0x1
CREATE_BYPASS_CSC	equ 0x2
CREATE_CRED_RESET	equ 0x4

USE_DEFAULT_CREDENTIALS equ 0x4

endif ;; _LMUSE_
