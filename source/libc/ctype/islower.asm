include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

islower PROC char
	mov	eax,[esp+4]
	mov	al,__ctype[eax+1]
	and	eax,_LOWER
	ret	4
islower ENDP

	END

