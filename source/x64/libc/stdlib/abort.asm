include stdlib.inc
include crtl.inc
include setjmp.inc

	.data
	jmp_exit S_JMPBUF <>

	.code

	OPTION	WIN64:2, STACKBASE:rsp

abort	PROC
	longjmp(addr jmp_exit, 1)
	ret
abort	ENDP

Install proc private
	.if _setjmp(addr jmp_exit)
	    exit(eax)
	.endif
	ret
Install endp

pragma_init Install, 1

	END
