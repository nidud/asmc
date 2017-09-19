; CSTART_.ASM--
;
; Startup module for Open Watcom (Win32)
;
include asmcver.inc
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
	db VERSSTR

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
