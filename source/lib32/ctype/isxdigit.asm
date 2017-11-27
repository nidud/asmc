include ctype.inc

	.code

	option stackbase:esp

isxdigit PROC char:SINT
	movzx	eax,BYTE PTR [esp+4]
	mov	al, BYTE PTR _ctype[eax*2+2]
	and	eax,_HEX
	ret
isxdigit ENDP

	END

