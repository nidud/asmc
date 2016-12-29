include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

iscntrl PROC char
	mov	eax,[esp+4]
	mov	al,__ctype[eax+1]
	and	eax,_CONTROL
	ret	4
iscntrl ENDP

	END

