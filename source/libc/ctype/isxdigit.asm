include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isxdigit PROC char
	mov	eax,[esp+4]
	mov	al,__ctype[eax+1]
	and	eax,_HEX
	ret	4
isxdigit ENDP

	END

