include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isupper PROC char:SIZE_T
	lea	rax,__ctype
	mov	al,[rax+rcx+1]
	and	rax,_UPPER
	ret
isupper ENDP

	END

