; crt.ASM--
;
; Startup module for Win32
;
	.486
	.model	flat, stdcall

include version.inc

_INIT	SEGMENT DWORD FLAT PUBLIC 'INIT'
_INIT	ENDS
_IEND	SEGMENT DWORD FLAT PUBLIC 'INIT'
_IEND	ENDS

includelib user32.lib
includelib kernel32.lib

main	proto C
__initialize proto :dword, :dword
exit	proto :dword

	.code

	db "DZ32JJV", VERSSTR

mainCRTStartup PROC C
	mov	eax,offset _INIT
	mov	edx,offset _IEND
	invoke	__initialize,eax,edx
	call	main
	invoke	exit,eax
mainCRTStartup ENDP

	END	mainCRTStartup
