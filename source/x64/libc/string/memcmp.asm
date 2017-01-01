include string.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

memcmp	PROC s1:LPSTR, s2:LPSTR, len:SIZE_T
	push	rsi
	push	rdi
	mov	rdi,rcx
	mov	rsi,rdx
	mov	rcx,r8
	xor	rax,rax
	repe	cmpsb
	je	@F
	sbb	rax,rax
	sbb	rax,-1
@@:
	pop	rdi
	pop	rsi
	ret
memcmp	ENDP

	END
