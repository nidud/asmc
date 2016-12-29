include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isupper PROC char
	mov	eax,[esp+4]
	mov	al,__ctype[eax+1]
	and	eax,_UPPER
	ret	4
isupper ENDP

	END

