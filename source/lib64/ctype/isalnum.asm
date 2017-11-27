include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isalnum PROC char:SINT
	lea	rax,_ctype
	mov	al,[rax+rcx*2+2]
	and	rax,_UPPER or _LOWER or _DIGIT
	ret
isalnum ENDP

	END

