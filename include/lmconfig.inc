ifndef _LMCONFIG_
define _LMCONFIG_

REVISED_CONFIG_APIS equ 1

;NET_API_STATUS
NetConfigGet proto WINAPI \
		server: LPCWSTR,
	     component: LPCWSTR,
	     parameter: LPCWSTR,
		bufptr: ptr LPBYTE

;NET_API_STATUS
NetConfigGetAll proto WINAPI \
		server: LPCWSTR,
	     component: LPCWSTR,
		bufptr: ptr LPBYTE


;NET_API_STATUS
NetConfigSet proto WINAPI \
		server: LPCWSTR,
	     reserved1: LPCWSTR,
	     component: LPCWSTR,
		 level: DWORD,
	     reserved2: DWORD,
		   buf: LPBYTE,
	     reserved3: DWORD


CONFIG_INFO_0		STRUC
cfgi0_key		LPWSTR ?
cfgi0_data		LPWSTR ?
CONFIG_INFO_0		ENDS
PCONFIG_INFO_0		typedef ptr CONFIG_INFO_0
LPCONFIG_INFO_0		typedef ptr CONFIG_INFO_0

endif ;; _LMCONFIG_
