include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isdigit PROC char:SINT
	lea	rax,_ctype
	mov	al,[rax+rcx*2+2]
	and	rax,_DIGIT
	ret
isdigit ENDP

	END

