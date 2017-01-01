include stdio.inc
include string.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

fputs	PROC USES rsi rdi rbx string:LPSTR, fp:LPFILE

	mov	rsi,rdx
	mov	rdi,rcx

	_stbuf( rdx )
	mov	rbx,rax
	strlen( rdi )
	fwrite( rdi, 1, eax, rsi )
	xchg	rbx,rax
	_ftbuf( rax, rsi )
	strlen( rdi )
	cmp	rax,rbx
	mov	rax,0
	je	@F
	dec	rax
@@:
	ret
fputs	ENDP

	END
