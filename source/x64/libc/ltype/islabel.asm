include ltype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

islabel PROC char
	movzx	rax,cl
	lea	rcx,__ltype
	test	BYTE PTR [rcx+rax+1],_LABEL or _DIGIT
	jnz	@F
	xor	eax,eax
@@:
	ret
islabel ENDP

	END

