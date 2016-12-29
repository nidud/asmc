ifndef __LIBC_INC
 include libc.inc
endif

.xlist

_EXEC_BAT	equ 1
_EXEC_COM	equ 2
_EXEC_EXE	equ 3
_EXEC_CMD	equ 4

externdef	OldErrorMode:DWORD

__isexec	PROTO :LPSTR
__setenvp	PROTO :LPSTR
__setargv	PROTO :SIZE_T, :PVOID, :LPSTR
__initialize	PROTO :PVOID, :PVOID
__allocwpath	PROTO :LPSTR

getfattr	PROTO :LPTSTR
setfattr	PROTO :LPTSTR, :UINT


SSE_MMX		equ 0x0001
SSE_SSE		equ 0x0002
SSE_SSE2	equ 0x0004
SSE_SSE3	equ 0x0008
SSE_SSSE3	equ 0x0010
SSE_SSE41	equ 0x0020
SSE_SSE42	equ 0x0040
SSE_XGETBV	equ 0x0080
SSE_AVX		equ 0x0100
SSE_AVX2	equ 0x0200
SSE_AVXOS	equ 0x0400

externdef	sselevel:DWORD
GetSSELevel	PROTO

pragma_init MACRO pp, priority
_INIT	SEGMENT PARA FLAT PUBLIC 'INIT'
	SIZE_T pp
	SIZE_T priority
_INIT	ENDS
;_IEND	SEGMENT PARA FLAT PUBLIC 'INIT'
;_IEND	ENDS
	ENDM

pragma_exit MACRO pp, priority
_EXIT	SEGMENT PARA FLAT PUBLIC 'EXIT'
	SIZE_T pp
	SIZE_T priority
_EXIT	ENDS
;_EEND	SEGMENT PARA FLAT PUBLIC 'INIT'
;_EEND	ENDS
	ENDM

	.list
