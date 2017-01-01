include ltype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

islabel_dot PROC char, dot
	movzx	rax,cl
	lea	rcx,__ltype
	mov	al,[rcx+rax+1]
	and	al,_LABEL or _DOT
	test	dl,dl
	jnz	@F
	and	al,_LABEL
@@:
	ret
islabel_dot ENDP

	END

