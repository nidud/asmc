include iost.inc

	.code

	ASSUME	edx:ptr S_IOST

ogetc	PROC
	lea	eax,STDI
ogetc	ENDP

iogetc	PROC
	push	edx
	mov	edx,eax
	mov	eax,[edx].ios_i
	cmp	eax,[edx].ios_c
	je	read
do:
	inc	[edx].ios_i
	add	eax,[edx].ios_bp
	movzx	eax,byte ptr [eax]
toend:
	pop	edx
	ret
read:
	test	[edx].ios_flag,IO_MEMBUF
	jnz	@F
	push	ecx
	ioread( edx )
	pop	ecx
	mov	eax,[edx].ios_i
	jnz	do
@@:
	or	eax,-1
	xor	edx,edx
	jmp	toend
iogetc	ENDP

	END
