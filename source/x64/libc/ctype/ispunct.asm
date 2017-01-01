include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

ispunct PROC char:SIZE_T
	lea	rax,__ctype
	mov	al,[rax+rcx+1]
	and	rax,_PUNCT
	ret
ispunct ENDP

	END

