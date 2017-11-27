include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

islower PROC char:SINT
	lea	rax,_ctype
	mov	al,[rax+rcx*2+2]
	and	rax,_LOWER
	ret
islower ENDP

	END

