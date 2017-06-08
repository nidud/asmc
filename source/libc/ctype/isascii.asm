include ctype.inc

	.code

	option stackbase:esp

isascii PROC char:SINT
	movzx	eax,BYTE PTR [esp+4]
	and	eax,80h
	setz	al
	ret
isascii ENDP

	END

