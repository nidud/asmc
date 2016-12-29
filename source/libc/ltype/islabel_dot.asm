include ltype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

islabel_dot PROC char, dot
	movzx	eax,BYTE PTR [esp+4]
	movzx	eax,__ltype[eax+1]
	and	eax,_LABEL or _DOT
	cmp	BYTE PTR [esp+8],0
	jne	@F
	and	eax,_LABEL
@@:
	ret	8
islabel_dot ENDP

	END

