include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isspace proc char:SIZE_T
	lea	rax,__ctype
	mov	al,[rax+rcx+1]
	and	rax,_SPACE
	ret
isspace endp

	END

