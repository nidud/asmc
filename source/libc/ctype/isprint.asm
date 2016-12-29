include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isprint PROC char
	mov	eax,[esp+4]
	cmp	eax,20h
	jb	@F
	cmp	eax,7Fh
	jnb	@F
	ret	4
@@:
	xor	eax,eax
	ret	4
isprint ENDP

	END

