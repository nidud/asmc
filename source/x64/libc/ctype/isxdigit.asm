include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isxdigit PROC char:SIZE_T
	lea	rax,__ctype
	mov	al,[rax+rcx+1]
	and	rax,_HEX
	ret
isxdigit ENDP

	END

