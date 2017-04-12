include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isupper PROC char:SINT
	lea	rax,_ctype
	mov	al,[rax+rcx*2+2]
	and	rax,_UPPER
	ret
isupper ENDP

	END

