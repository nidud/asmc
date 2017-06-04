include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isgraph PROC char:SINT
	movzx	eax,BYTE PTR [esp+4]
	cmp	eax,21h
	jb	@F
	cmp	eax,7Fh
	jnb	@F
	ret
@@:
	xor	eax,eax
	ret
isgraph ENDP

	END
