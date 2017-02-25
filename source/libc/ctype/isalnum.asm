include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isalnum PROC char:SINT
	movzx	eax,BYTE PTR [esp+4]
	mov	al,byte ptr _ctype[eax*2+2]
	and	eax,_UPPER or _LOWER or _DIGIT
	ret	4
isalnum ENDP

	END

