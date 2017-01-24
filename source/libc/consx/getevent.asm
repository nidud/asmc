include consx.inc

	.code

getevent PROC

	call	getkey
	jnz	@F
	call	tdidle
	jnz	@F
	mov	eax,keyshift
	mov	eax,[eax]
	test	eax,SHIFT_MOUSEFLAGS
	jz	getevent
	call	mousep
	jz	getevent
	mov	eax,MOUSECMD
@@:
	ret

getevent ENDP

	END
