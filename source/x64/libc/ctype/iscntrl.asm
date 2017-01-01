include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

iscntrl PROC char:SIZE_T
	lea	rax,__ctype
	mov	al,[rax+rcx+1]
	and	rax,_CONTROL
	ret
iscntrl ENDP

	END

