ifndef _LMMSG_
define _LMMSG_

NetMessageNameAdd proto WINAPI :LPCWSTR, :LPCWSTR
NetMessageNameEnum proto WINAPI :LPCWSTR, :DWORD, :ptr, :DWORD, :LPDWORD, :LPDWORD, :LPDWORD
NetMessageNameGetInfo proto WINAPI :LPCWSTR, :LPCWSTR, :DWORD, :ptr
NetMessageNameDel proto WINAPI :LPCWSTR, :LPCWSTR
NetMessageBufferSend proto WINAPI :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPBYTE, :DWORD

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
