include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isspace proc char:SINT
	movzx	eax,BYTE PTR [esp+4]
	mov	al, BYTE PTR _ctype[eax*2+2]
	and	eax,_SPACE
	ret
isspace endp

	END

