; wcstart.asm--
;
; Startup module for LIBC
;
include asmcver.inc
include stdlib.inc
include crtl.inc

includelib kernel32.lib
includelib user32.lib
includelib libc.lib

public wcstart

_INIT	SEGMENT PARA FLAT PUBLIC 'INIT'
IStart	label byte
_INIT	ENDS
_IEND	SEGMENT PARA FLAT PUBLIC 'INIT'
IEnd	label byte
_IEND	ENDS

wmain	proto :dword, :ptr, :ptr

	.code

	dd 495A440Ah
	dd 564A4A50h
	db VERSSTR

wcstart:
	lea rcx,IStart
	lea rdx,IEnd
	__initialize( rcx, rdx )

	mov ecx,__argc
	mov rdx,__wargv
	mov r8,_wenviron
	sub rsp,0x28
	exit( wmain( ecx, rdx, r8 ) )

	end	wcstart
