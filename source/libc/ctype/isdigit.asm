include ctype.inc

	.code

	option stackbase:esp

isdigit PROC char:SINT
	movzx	eax,BYTE PTR [esp+4]
	mov	al, BYTE PTR _ctype[eax*2+2]
	and	eax,_DIGIT
	ret
isdigit ENDP

	END

