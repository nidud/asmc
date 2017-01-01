; CRTDLL.ASM--
;
; Startup module for DLL
;
include version.inc

IFDEF DEBUG
includelib	libd.lib
ELSE
includelib	libc.lib
ENDIF
includelib	user32.lib
includelib	kernel32.lib

PROCESS_DETACH	equ 0
PROCESS_ATTACH	equ 1

_INIT		SEGMENT PARA FLAT PUBLIC 'INIT'
InitStart	label byte
_INIT		ENDS
_IEND		SEGMENT PARA FLAT PUBLIC 'INIT'
InitEnd		label byte
_IEND		ENDS
_EXIT		SEGMENT PARA FLAT PUBLIC 'EXIT'
ExitStart	label byte
_EXIT		ENDS
_EEND		SEGMENT PARA FLAT PUBLIC 'EXIT'
ExitEnd		label byte
_EEND		ENDS

__initialize	PROTO :QWORD, :QWORD

	.code

	dd 495A440Ah
	dd 564A4A50h
	db VERSSTR

LibMain PROC hModule:qword, dwReason, dwReserved

	.if	edx == PROCESS_DETACH
		lea	rcx,ExitStart
		lea	rdx,ExitEnd
		__initialize( rcx, rdx )
	.elseif edx == PROCESS_ATTACH
		lea	rcx,InitStart
		lea	rdx,InitEnd
		__initialize( rcx, rdx )
	.endif
	mov	eax,1
	ret

LibMain ENDP

	END LibMain
