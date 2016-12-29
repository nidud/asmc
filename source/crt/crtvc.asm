; crtvc.ASM--
;
; Startup module for Visual C - CL.EXE
;
	.486
	.model	flat

_INIT	SEGMENT DWORD FLAT PUBLIC 'INIT'
_INIT	ENDS
_IEND	SEGMENT DWORD FLAT PUBLIC 'INIT'
_IEND	ENDS

includelib	libc.lib
includelib	user32.lib
includelib	kernel32.lib

externdef	__argc:DWORD
externdef	__argv:DWORD
externdef	__environ:DWORD

main		PROTO C
exit		PROTO STDCALL :DWORD
__initialize	PROTO STDCALL :DWORD, :DWORD

	.code

include version.inc

	db "DZ32JJV", VERSSTR

mainCRTStartup PROC C
	mov	edx,offset _INIT
	mov	eax,offset _IEND
	invoke	__initialize,edx,eax
	push	__environ
	push	__argv
	push	__argc
	call	main
	invoke	exit,eax
mainCRTStartup ENDP

	END	mainCRTStartup
