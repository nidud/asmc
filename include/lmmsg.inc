ifndef _LMMSG_
_LMMSG_ equ <>

;NET_API_STATUS
NetMessageNameAdd proto WINAPI \
	    servername: LPCWSTR,
	       msgname: LPCWSTR

;NET_API_STATUS
NetMessageNameEnum proto WINAPI \
	    servername: LPCWSTR,
		 level: DWORD,
		bufptr: ptr LPBYTE,
	    prefmaxlen: DWORD,
	   entriesread: LPDWORD,
	  totalentries: LPDWORD,
	 resume_handle: LPDWORD

;NET_API_STATUS
NetMessageNameGetInfo proto WINAPI \
	    servername: LPCWSTR,
	       msgname: LPCWSTR,
		 level: DWORD,
		bufptr: ptr LPBYTE

;NET_API_STATUS
NetMessageNameDel proto WINAPI \
	    servername: LPCWSTR,
	       msgname: LPCWSTR

;NET_API_STATUS
NetMessageBufferSend proto WINAPI \
	    servername: LPCWSTR,
	       msgname: LPCWSTR,
	      fromname: LPCWSTR,
		   buf: LPBYTE,
		buflen: DWORD


MSG_INFO_0		STRUC
msgi0_name		LPWSTR ?
MSG_INFO_0		ENDS
PMSG_INFO_0		typedef ptr MSG_INFO_0
LPMSG_INFO_0		typedef ptr MSG_INFO_0

MSG_INFO_1		STRUC
msgi1_name		LPWSTR ?
msgi1_forward_flag	dd ?
msgi1_forward		LPWSTR ?
MSG_INFO_1		ENDS
PMSG_INFO_1		typedef ptr MSG_INFO_1
LPMSG_INFO_1		typedef ptr MSG_INFO_1

MSGNAME_NOT_FORWARDED	equ 0
MSGNAME_FORWARDED_TO	equ 0x04
MSGNAME_FORWARDED_FROM	equ 0x10

endif
