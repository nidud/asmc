include ctype.inc

	.code

	option stackbase:esp

_tolower PROC char:SINT

	movzx	eax,BYTE PTR [esp+4]
	sub	al,'A'+'a'
	ret

_tolower ENDP

	END

