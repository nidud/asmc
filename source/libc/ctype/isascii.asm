include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isascii PROC char
	mov	eax,[esp+4]
	and	eax,80h
	setz	al
	ret	4
isascii ENDP

	END

