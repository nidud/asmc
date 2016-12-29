include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isalpha PROC char
	mov	eax,[esp+4]
	mov	al,__ctype[eax+1]
	and	eax,_UPPER or _LOWER
	ret	4
isalpha ENDP

	END

