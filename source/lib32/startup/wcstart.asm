; wcstart.asm--
;
; Startup module for LIBC
;
include stdlib.inc
include crtl.inc

includelib kernel32.lib
includelib user32.lib
includelib libc.lib

public wcstart
public wmainCRTStartup

_INIT	SEGMENT PARA FLAT PUBLIC 'INIT'
_INIT	ENDS
_IEND	SEGMENT PARA FLAT PUBLIC 'INIT'
_IEND	ENDS

wmain	proto :dword, :ptr, :ptr

	.code

	dd 495A440Ah
	dd 564A4A50h
	db _ASMLIB_ / 100 + '0','.',_ASMLIB_ mod 100 / 10 + '0',_ASMLIB_ mod 10 + '0'

wmainCRTStartup:
	mov eax,offset _INIT
	and eax,-4096	; LINK - to start of page
	jmp @F
wcstart:
	mov eax,offset _INIT
@@:
	mov edx,offset _IEND
	__initialize( eax, edx )
	mov ecx,__argc
	mov edx,__wargv
	mov ebx,_wenviron
	exit( wmain( ecx, edx, ebx ) )

	end	wcstart
