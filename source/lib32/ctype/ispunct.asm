include ctype.inc

	.code

	option stackbase:esp

ispunct PROC char:SINT
	movzx	eax,BYTE PTR [esp+4]
	mov	al, BYTE PTR _ctype[eax*2+2]
	and	eax,_PUNCT
	ret
ispunct ENDP

	END

