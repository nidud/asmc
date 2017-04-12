include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isspace proc char:SINT
	lea	rax,_ctype
	mov	al,[rax+rcx*2+2]
	and	rax,_SPACE
	ret
isspace endp

	END

