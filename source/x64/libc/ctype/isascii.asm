include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isascii PROC char:SIZE_T
	mov	rax,rcx
	and	rax,80h
	setz	al
	ret
isascii ENDP

	END

