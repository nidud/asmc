ifndef __LIBC_INC
 include libc.inc
endif

.xlist

INIMAXLABEL	equ 32
INIMAXVALUE	equ 256

externdef	cinifile:SIZE_T

iniopen		PROTO :LPSTR
iniclose	PROTO
inientryid	PROTO :LPSTR, :DWORD
inientry	PROTO :LPSTR, :LPSTR
inientryf	PROTO :LPSTR, :LPSTR, :LPSTR
inierror	PROTO :LPSTR, :LPSTR

.list
