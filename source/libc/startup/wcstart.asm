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
_INIT	ENDS
_IEND	SEGMENT PARA FLAT PUBLIC 'INIT'
_IEND	ENDS

wmain	proto :dword, :ptr, :ptr

	.code

	dd 495A440Ah
	dd 564A4A50h
	db VERSSTR

wcstart:
	mov eax,offset _INIT
	mov edx,offset _IEND
	__initialize( eax, edx )
	exit( wmain( __argc, __wargv, _wenviron ) )

	end	wcstart
