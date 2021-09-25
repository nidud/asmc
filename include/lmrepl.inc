ifndef _LMREPL_
define _LMREPL_

REPL_ROLE_EXPORT	equ 1
REPL_ROLE_IMPORT	equ 2
REPL_ROLE_BOTH		equ 3

REPL_INTERVAL_INFOLEVEL equ (PARMNUM_BASE_INFOLEVE + 0)
REPL_PULSE_INFOLEVEL	equ (PARMNUM_BASE_INFOLEVE + 1)
REPL_GUARDTIME_INFOLEVEL equ (PARMNUM_BASE_INFOLEVE + 2)
REPL_RANDOM_INFOLEVEL	equ (PARMNUM_BASE_INFOLEVE + 3)

REPL_INFO_0		STRUC
rp0_role		dd ?
rp0_exportpath		LPWSTR ?
rp0_exportlist		LPWSTR ?
rp0_importpath		LPWSTR ?
rp0_importlist		LPWSTR ?
rp0_logonusername	LPWSTR ?
rp0_interval		dd ?
rp0_pulse		dd ?
rp0_guardtime		dd ?
rp0_random		dd ?
REPL_INFO_0		ENDS
PREPL_INFO_0		typedef ptr REPL_INFO_0
LPREPL_INFO_0		typedef ptr REPL_INFO_0

REPL_INFO_1000		STRUC
rp1000_interval		dd ?
REPL_INFO_1000		ENDS
PREPL_INFO_1000		typedef ptr REPL_INFO_1000
LPREPL_INFO_1000	typedef ptr REPL_INFO_1000

REPL_INFO_1001		STRUC
rp1001_pulse		dd ?
REPL_INFO_1001		ENDS
PREPL_INFO_1001		typedef ptr REPL_INFO_1001
LPREPL_INFO_1001	typedef ptr REPL_INFO_1001

REPL_INFO_1002		STRUC
rp1002_guardtime	dd ?
REPL_INFO_1002		ENDS
PREPL_INFO_1002		typedef ptr REPL_INFO_1002
LPREPL_INFO_1002	typedef ptr REPL_INFO_1002

REPL_INFO_1003		STRUC
rp1003_random		dd ?
REPL_INFO_1003		ENDS
PREPL_INFO_1003		typedef ptr REPL_INFO_1003
LPREPL_INFO_1003	typedef ptr REPL_INFO_1003


;NET_API_STATUS
NetReplGetInfo proto WINAPI \
	    servername: LPCWSTR,
		 level: DWORD,
		bufptr: ptr LPBYTE

;NET_API_STATUS
NetReplSetInfo proto WINAPI \
	    servername: LPCWSTR,
		 level: DWORD,
		   buf: LPBYTE,
	      parm_err: LPDWORD


REPL_INTEGRITY_FILE	equ 1
REPL_INTEGRITY_TREE	equ 2

REPL_EXTENT_FILE	equ 1
REPL_EXTENT_TREE	equ 2

REPL_EXPORT_INTEGRITY_INFOLEVEL equ (PARMNUM_BASE_INFOLEVE + 0)
REPL_EXPORT_EXTENT_INFOLEVEL equ (PARMNUM_BASE_INFOLEVE + 1)


REPL_EDIR_INFO_0	STRUC
rped0_dirname		LPWSTR ?
REPL_EDIR_INFO_0	ENDS
PREPL_EDIR_INFO_0	typedef ptr REPL_EDIR_INFO_0
LPREPL_EDIR_INFO_0	typedef ptr REPL_EDIR_INFO_0

REPL_EDIR_INFO_1	STRUC
rped1_dirname		LPWSTR ?
rped1_integrity		dd ?
rped1_extent		dd ?
REPL_EDIR_INFO_1	ENDS
PREPL_EDIR_INFO_1	typedef ptr REPL_EDIR_INFO_1
LPREPL_EDIR_INFO_1	typedef ptr REPL_EDIR_INFO_1

REPL_EDIR_INFO_2	STRUC
rped2_dirname		LPWSTR ?
rped2_integrity		dd ?
rped2_extent		dd ?
rped2_lockcount		dd ?
rped2_locktime		dd ?
REPL_EDIR_INFO_2	ENDS
PREPL_EDIR_INFO_2	typedef ptr REPL_EDIR_INFO_2
LPREPL_EDIR_INFO_2	typedef ptr REPL_EDIR_INFO_2

REPL_EDIR_INFO_1000	STRUC
rped1000_integrity	dd ?
REPL_EDIR_INFO_1000	ENDS
PREPL_EDIR_INFO_1000	typedef ptr REPL_EDIR_INFO_1000
LPREPL_EDIR_INFO_1000	typedef ptr REPL_EDIR_INFO_1000

REPL_EDIR_INFO_1001	STRUC
rped1001_extent		dd ?
REPL_EDIR_INFO_1001	ENDS
PREPL_EDIR_INFO_1001	typedef ptr REPL_EDIR_INFO_1001
LPREPL_EDIR_INFO_1001	typedef ptr REPL_EDIR_INFO_1001


;NET_API_STATUS
NetReplExportDirAdd proto WINAPI \
	    servername: LPCWSTR,
		 level: DWORD,
		   buf: LPBYTE,
	      parm_err: LPDWORD

;NET_API_STATUS
NetReplExportDirDel proto WINAPI \
	    servername: LPCWSTR,
	       dirname: LPCWSTR

;NET_API_STATUS
NetReplExportDirEnum proto WINAPI \
	    servername: LPCWSTR,
		 level: DWORD,
		bufptr: ptr LPBYTE,
	    prefmaxlen: DWORD,
	   entriesread: LPDWORD,
	  totalentries: LPDWORD,
	  resumehandle: LPDWORD

;NET_API_STATUS
NetReplExportDirGetInfo proto WINAPI \
	    servername: LPCWSTR,
	       dirname: LPCWSTR,
		 level: DWORD,
		bufptr: ptr LPBYTE

;NET_API_STATUS
NetReplExportDirSetInfo proto WINAPI \
	    servername: LPCWSTR,
	       dirname: LPCWSTR,
		 level: DWORD,
		   buf: LPBYTE,
	      parm_err: LPDWORD

;NET_API_STATUS
NetReplExportDirLock proto WINAPI \
	    servername: LPCWSTR,
	       dirname: LPCWSTR


;NET_API_STATUS
NetReplExportDirUnlock proto WINAPI \
	    servername: LPCWSTR,
	       dirname: LPCWSTR,
	   unlockforce: DWORD


REPL_UNLOCK_NOFORCE	equ 0
REPL_UNLOCK_FORCE	equ 1


REPL_IDIR_INFO_0	STRUC
rpid0_dirname		LPWSTR ?
REPL_IDIR_INFO_0	ENDS
PREPL_IDIR_INFO_0	typedef ptr REPL_IDIR_INFO_0
LPREPL_IDIR_INFO_0	typedef ptr REPL_IDIR_INFO_0

REPL_IDIR_INFO_1	STRUC
rpid1_dirname		LPWSTR ?
rpid1_state		dd ?
rpid1_mastername	LPWSTR ?
rpid1_last_update_time	dd ?
rpid1_lockcount		dd ?
rpid1_locktime		dd ?
REPL_IDIR_INFO_1	ENDS
PREPL_IDIR_INFO_1	typedef ptr REPL_IDIR_INFO_1
LPREPL_IDIR_INFO_1	typedef ptr REPL_IDIR_INFO_1


;NET_API_STATUS
NetReplImportDirAdd proto WINAPI \
	    servername: LPCWSTR,
		 level: DWORD,
		   buf: LPBYTE,
	      parm_err: LPDWORD

;NET_API_STATUS
NetReplImportDirDel proto WINAPI \
	    servername: LPCWSTR,
	       dirname: LPCWSTR

;NET_API_STATUS
NetReplImportDirEnum proto WINAPI \
	    servername: LPCWSTR,
		 level: DWORD,
		bufptr: ptr LPBYTE,
	    prefmaxlen: DWORD,
	   entriesread: LPDWORD,
	  totalentries: LPDWORD,
	  resumehandle: LPDWORD

;NET_API_STATUS
NetReplImportDirGetInfo proto WINAPI \
	    servername: LPCWSTR,
	       dirname: LPCWSTR,
		 level: DWORD,
		bufptr: ptr LPBYTE

;NET_API_STATUS
NetReplImportDirLock proto WINAPI \
	    servername: LPCWSTR,
	       dirname: LPCWSTR

;NET_API_STATUS
NetReplImportDirUnlock proto WINAPI \
	    servername: LPCWSTR,
	       dirname: LPCWSTR,
	   unlockforce: DWORD


REPL_STATE_OK		equ 0
REPL_STATE_NO_MASTER	equ 1
REPL_STATE_NO_SYNC	equ 2
REPL_STATE_NEVER_REPLICATED equ 3

endif
