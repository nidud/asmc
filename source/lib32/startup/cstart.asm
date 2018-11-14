; CSTART.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
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
_INIT	ENDS
_IEND	SEGMENT PARA FLAT PUBLIC 'INIT'
_IEND	ENDS

main	proto :dword, :ptr, :ptr

	.code

	dd 495A440Ah
	dd 564A4A50h
	db __LIBC__ / 100 + '0','.',__LIBC__ mod 100 / 10 + '0',__LIBC__ mod 10 + '0'

mainCRTStartup:
	mov eax,offset _INIT
	and eax,-4096	; LINK - to start of page
	jmp @F
cstart:
	mov eax,offset _INIT
@@:
	mov edx,offset _IEND
	__initialize( eax, edx )
	mov ecx,__argc
	mov edx,__argv
	mov ebx,_environ
	exit( main( ecx, edx, ebx ) )

	end	cstart
