; CSTART_.ASM--
;
; Startup module for Open Watcom (Win32)
;
include stdlib.inc
include crtl.inc

_INIT	segment para flat public 'INIT'
_INIT	ENDS
_IEND	segment para flat public 'INIT'
_IEND	ends

main_	proto syscall

	.code

	dd 495A440Ah
	dd 564A4A50h
	db _ASMLIB_ / 100 + '0','.',_ASMLIB_ mod 100 / 10 + '0',_ASMLIB_ mod 10 + '0'

cstart_ PROC
	mov eax,offset _INIT
	mov edx,offset _IEND
	__initialize(eax, edx)
	mov ecx,__argc
	mov edx,__argv
	mov ebx,_environ
	mov eax,ecx
	exit(main_())

cstart_ endp

	END	cstart_
