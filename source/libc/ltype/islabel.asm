include ltype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

islabel PROC char
	movzx	eax,BYTE PTR [esp+4]
	test	__ltype[eax+1],_LABEL or _DIGIT
	jnz	@F
	xor	eax,eax
@@:
	ret	4
islabel ENDP

	END

