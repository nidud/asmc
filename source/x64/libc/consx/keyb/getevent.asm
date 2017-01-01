include consx.inc

	.code

	OPTION	WIN64:0, STACKBASE:rsp

getevent PROC
	call	getkey
	jnz	@F
	call	tdidle
	jnz	@F
	mov	rax,keyshift
	mov	eax,[rax]
	test	eax,SHIFT_MOUSEFLAGS
	jz	getevent
	call	mousep
	jz	getevent
	mov	eax,MOUSECMD
@@:
	ret
getevent ENDP

	END
