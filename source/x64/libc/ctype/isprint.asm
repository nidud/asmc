include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isprint PROC char:SIZE_T
	mov	rax,rcx
	cmp	al,20h
	jb	@F
	cmp	al,7Fh
	jnb	@F
	ret
@@:
	xor	rax,rax
	ret
isprint ENDP

	END

