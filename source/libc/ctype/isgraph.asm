include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isgraph PROC char
	mov	eax,[esp+4]
	cmp	eax,21h
	jb	@F
	cmp	eax,7Fh
	jnb	@F
	ret	4
@@:
	xor	eax,eax
	ret	4
isgraph ENDP

	END
