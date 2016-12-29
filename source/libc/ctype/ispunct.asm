include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

ispunct PROC char
	mov	eax,[esp+4]
	mov	al,__ctype[eax+1]
	and	eax,_PUNCT
	ret	4
ispunct ENDP

	END

