include stdlib.inc
include crtl.inc
include setjmp.inc

	.data
	jmp_exit S_JMPBUF <>

	.code

abort	PROC
	longjmp( addr jmp_exit, 1 )
	ret
abort	ENDP

Install:
	.if _setjmp( addr jmp_exit )

	    exit( eax )
	.endif
	ret

pragma_init Install, 1

	END
