include ctype.inc

	.code

	option stackbase:esp

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
