include stdio.inc
include io.inc
include errno.inc
include string.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

perror	PROC USES rdi string:LPSTR
	mov	rax,rcx
	.if	rax
		mov	rdi,rax
		mov	al,[rdi]
		.if	al

			_write( 2, rdi, strlen( rdi ) )
			_write( 2, ": ", 2 )

			lea	rax,sys_errlist
			mov	edi,errno
			shl	edi,3
			add	rdi,rax
			mov	rdi,[rdi]

			strlen( rdi )
			_write( 2, rdi, rax )
			_write( 2, "\n", 1 )
		.endif
	.endif
	ret
perror	ENDP

	END
