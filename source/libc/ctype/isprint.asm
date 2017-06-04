include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isprint PROC char:SINT
	movzx	eax,BYTE PTR [esp+4]
	cmp	eax,20h
	jb	@F
	cmp	eax,7Fh
	jnb	@F
	ret
@@:
	xor	eax,eax
	ret
isprint ENDP

	END

