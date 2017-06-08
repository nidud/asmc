include ctype.inc

	.code

	option stackbase:esp

isspace proc char:SINT
	movzx	eax,BYTE PTR [esp+4]
	mov	al, BYTE PTR _ctype[eax*2+2]
	and	eax,_SPACE
	ret
isspace endp

	END

