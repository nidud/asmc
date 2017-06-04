include iost.inc

	.code

oseek	PROC offs, from
	mov	eax,offs
	xor	edx,edx
	ioseek( addr STDI, edx::eax, from )
	jz	@F
	test	STDI.ios_flag,IO_MEMBUF
	jnz	@F
	push	edx
	push	eax
	ioread( addr STDI )
	pop	eax
	pop	edx
@@:
	ret
oseek	ENDP

	END
