include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isspace proc char
	mov	eax,[esp+4]
	mov	al,__ctype[eax+1]
	and	eax,_SPACE
	ret	4
isspace endp

	END

