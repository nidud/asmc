include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isxdigit PROC char:SINT
	lea	rax,_ctype
	mov	al,[rax+rcx*2+2]
	and	rax,_HEX
	ret
isxdigit ENDP

	END

