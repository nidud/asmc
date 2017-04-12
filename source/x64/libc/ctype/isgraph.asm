include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isgraph PROC char:SINT
	mov	rax,rcx
	cmp	al,21h
	jb	@F
	cmp	al,7Fh
	jnb	@F
	ret
@@:
	xor	rax,rax
	ret
isgraph ENDP

	END
