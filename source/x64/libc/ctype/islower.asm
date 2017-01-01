include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

islower PROC char:SIZE_T
	lea	rax,__ctype
	mov	al,[rax+rcx+1]
	and	rax,_LOWER
	ret
islower ENDP

	END

