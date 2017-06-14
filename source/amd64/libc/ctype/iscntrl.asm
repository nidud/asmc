include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

iscntrl PROC char:SINT
	lea	rax,_ctype
	mov	al,[rax+rcx*2+2]
	and	rax,_CONTROL
	ret
iscntrl ENDP

	END

