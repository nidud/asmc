include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isalpha PROC char:SINT
	lea	rax,_ctype
	mov	al,[rax+rcx*2+2]
	and	rax,_UPPER or _LOWER
	ret
isalpha ENDP

	END

