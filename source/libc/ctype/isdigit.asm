include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isdigit PROC char
	mov	eax,[esp+4]
	mov	al,__ctype[eax+1]
	and	eax,_DIGIT
	ret	4
isdigit ENDP

	END

