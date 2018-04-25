; cstart.asm--
;
; Startup module for LIBC
;
include stdlib.inc
include crtl.inc

includelib kernel32.lib
includelib user32.lib
includelib libc.lib

public cstart
public mainCRTStartup

_INIT	SEGMENT PARA FLAT PUBLIC 'INIT'
IStart	label byte
_INIT	ENDS
_IEND	SEGMENT PARA FLAT PUBLIC 'INIT'
IEnd	label byte
_IEND	ENDS

main	proto :dword, :ptr, :ptr

	.code

	dd 495A440Ah
	dd 564A4A50h
	db _ASMLIB_ / 100 + '0','.',_ASMLIB_ mod 100 / 10 + '0',_ASMLIB_ mod 10 + '0'

mainCRTStartup::

	lea rcx,IStart
	and rcx,-4096	; LINK - to start of page
	jmp @F

cstart::

	lea rcx,IStart
@@:
	lea rdx,IEnd
	__initialize( rcx, rdx )

	mov ecx,__argc
	mov rdx,__argv
	mov r8,_environ
	sub rsp,0x28
	exit( main( ecx, rdx, r8 ) )

	end	cstart
