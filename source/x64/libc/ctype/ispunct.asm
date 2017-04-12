include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

ispunct PROC char:SINT
	lea	rax,_ctype
	mov	al,[rax+rcx*2+2]
	and	rax,_PUNCT
	ret
ispunct ENDP

	END

