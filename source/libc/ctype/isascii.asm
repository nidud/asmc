include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isascii PROC char:SINT
	movzx	eax,BYTE PTR [esp+4]
	and	eax,80h
	setz	al
	ret
isascii ENDP

	END

