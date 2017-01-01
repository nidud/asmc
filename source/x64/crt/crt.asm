; CRT.ASM--
;
; Startup module for Win64
;
include version.inc
include stdlib.inc
include crtl.inc

IFDEF DEBUG
includelib	libd.lib
ELSE
includelib	libc.lib
ENDIF
includelib	user32.lib
includelib	kernel32.lib

_INIT		SEGMENT PARA FLAT PUBLIC 'INIT'
InitStart	label byte
_INIT		ENDS
_IEND		SEGMENT PARA FLAT PUBLIC 'INIT'
InitEnd		label byte
_IEND		ENDS

main	PROTO

	.code

	dd 495A440Ah
	dd 564A4A50h
	db VERSSTR

mainCRTStartup PROC
	lea	rcx,InitStart
	lea	rdx,InitEnd
	call	__initialize
	call	main
	mov	rcx,rax
	call	exit
mainCRTStartup ENDP

	END	mainCRTStartup
