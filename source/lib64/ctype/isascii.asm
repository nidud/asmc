include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isascii PROC char:SINT
	mov	rax,rcx
	and	rax,80h
	setz	al
	ret
isascii ENDP

	END

