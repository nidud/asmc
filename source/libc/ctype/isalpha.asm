include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isalpha PROC char:SINT
	movzx	eax,BYTE PTR [esp+4]
	mov	al,BYTE PTR _ctype[eax*2+2]
	and	eax,_UPPER or _LOWER
	ret	4
isalpha ENDP

	END

