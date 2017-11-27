include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

_toupper PROC char:SINT

	movzx	eax,BYTE PTR [esp+4]
	sub	al,'a'-'A'
	ret	4

_toupper ENDP

	END

