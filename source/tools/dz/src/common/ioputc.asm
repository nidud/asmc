include iost.inc

	.code

	ASSUME	edx:ptr S_IOST

oputc	PROC
	push	edx
	push	ecx
	lea	edx,STDO
oputc	ENDP

oputc_lk:
	mov	ecx,[edx].ios_i
	cmp	ecx,[edx].ios_size
	je	flush
	add	ecx,[edx].ios_bp
	inc	[edx].ios_i
	mov	[ecx],al
	mov	eax,1
toend:
	pop	ecx
	pop	edx
	ret
flush:
	push	eax
	ioflush( edx )
	pop	eax
	jnz	oputc_lk
	xor	eax,eax
	jmp	toend

ioputc	PROC
	push	edx
	push	ecx
	jmp	oputc_lk
ioputc	ENDP

	END
