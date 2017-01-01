include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isdigit PROC char:SIZE_T
	lea	rax,__ctype
	mov	al,[rax+rcx+1]
	and	rax,_DIGIT
	ret
isdigit ENDP

	END

