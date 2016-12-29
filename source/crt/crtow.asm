; crtow.ASM--
;
; Startup module for Open watcom C - WCC386.EXE
;
	.486
	.model	flat

	OPTION	casemap:none

include version.inc

externdef	__argc:DWORD
externdef	__argv:DWORD
externdef	__environ:DWORD

externdef	main_:ABS
exit		PROTO STDCALL :DWORD
__initialize	PROTO STDCALL :DWORD, :DWORD

includelib	user32.lib
includelib	kernel32.lib

_INIT	SEGMENT DWORD FLAT PUBLIC 'INIT'
_INIT	ENDS
_IEND	SEGMENT DWORD FLAT PUBLIC 'INIT'
_IEND	ENDS

	.code

	db "DZ32JJV", VERSSTR

cstart_ PROC C
	mov	edx,offset _INIT
	mov	eax,offset _IEND
	invoke	__initialize,edx,eax
	mov	ebx,__environ
	mov	edx,__argv
	mov	eax,__argc
	call	main_
	invoke	exit,eax
cstart_ ENDP

	END	cstart_
