; crtdll.ASM--
;
; Startup module for DLL
;
	.486
	.model	FLAT, stdcall

	OPTION	casemap:none

include version.inc

includelib user32.lib
includelib kernel32.lib

PROCESS_DETACH	equ 0
PROCESS_ATTACH	equ 1

_INIT	SEGMENT DWORD FLAT PUBLIC 'INIT'
_INIT	ENDS
_IEND	SEGMENT DWORD FLAT PUBLIC 'INIT'
_IEND	ENDS
_EXIT	SEGMENT DWORD FLAT PUBLIC 'EXIT'
_EXIT	ENDS
_EEND	SEGMENT DWORD FLAT PUBLIC 'EXIT'
_EEND	ENDS

__initialize PROTO :DWORD, :DWORD

	.code

	db "DZ32JJV", VERSSTR

LibMain PROC hModule, dwReason, dwReserved
	.if	dwReason == PROCESS_DETACH
		mov	edx,offset _EXIT
		mov	eax,offset _EEND
		invoke	__initialize,edx,eax
	.elseif dwReason == PROCESS_ATTACH
		mov	edx,offset _INIT
		mov	eax,offset _IEND
		invoke	__initialize,edx,eax
	.endif
	mov	eax,1
	ret
LibMain ENDP

	END LibMain
