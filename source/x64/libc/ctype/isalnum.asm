include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isalnum PROC char:SIZE_T
	lea	rax,__ctype
	mov	al,[rax+rcx+1]
	and	rax,_UPPER or _LOWER or _DIGIT
	ret
isalnum ENDP

	END

