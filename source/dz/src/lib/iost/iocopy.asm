include iost.inc

	.code

	ASSUME	edx:ptr S_IOST
	ASSUME	ebx:ptr S_IOST

iocopy	PROC USES esi edi ebx ost:PTR S_IOST, ist:PTR S_IOST, len:qword
	xor	eax,eax
	mov	edx,ist
	mov	ebx,ost
	mov	esi,dword ptr len[4]
	mov	edi,dword ptr len
	test	esi,esi
	jnz	@F
	test	edi,edi
	jz	success			; copy zero byte is ok..
@@:
	mov	ecx,[edx].ios_c		; if count is zero -- file copy
	sub	ecx,[edx].ios_i
	jnz	@F
	mov	eax,edx
	call	iogetc
	jz	toend
	dec	[edx].ios_i
	mov	ecx,[edx].ios_c
	sub	ecx,[edx].ios_i
	jz	toend
@@:
	mov	eax,[ebx].ios_size	; copy max byte from STDI to STDO
	sub	eax,[ebx].ios_i
	cmp	eax,ecx
	ja	@F
	mov	ecx,eax
@@:
	test	esi,esi
	jnz	@F
	cmp	edi,ecx
	ja	@F
	mov	ecx,edi
@@:
	mov	eax,ecx
	push	esi
	push	edi
	mov	esi,[edx].ios_bp
	add	esi,[edx].ios_i
	mov	edi,[ebx].ios_bp
	add	edi,[ebx].ios_i
	rep	movsb
	pop	edi
	pop	esi
	add	[ebx].ios_i,eax
	add	[edx].ios_i,eax
	sub	edi,eax
	sbb	esi,0
	mov	eax,edi
	or	eax,esi
	jz	success
	mov	eax,[edx].ios_c
	test	eax,eax
	jz	@06
	sub	eax,[edx].ios_i ; flush inbuf
	jz	@06
@@:
	mov	eax,edx
	call	iogetc
	jz	toend
	mov	edx,ebx
	call	ioputc
	mov	edx,ist
	jz	toend
	sub	edi,eax
	sbb	esi,0
	mov	eax,esi
	or	eax,edi
	jz	success		; success if zero (inbuf > len)
	mov	eax,[edx].ios_i
	cmp	eax,[edx].ios_c
	jne	@B		; do byte copy from STDI to STDO
@06:
	ioflush( ebx )		; flush STDO
	jz	toend		; do block copy of bytes left
	push	[ebx].ios_size
	push	[ebx].ios_bp
	mov	eax,[edx].ios_bp
	mov	[ebx].ios_bp,eax
	mov	eax,[edx].ios_size
	mov	[ebx].ios_size,eax
@07:
	ioread( edx )
	jz	@13
	mov	eax,[edx].ios_c ; count
	test	esi,esi
	jnz	@08
	cmp	eax,edi
	jae	@12
@08:
	sub	edi,eax
	sbb	esi,0
	mov	[ebx].ios_i,eax		; fill STDO
	mov	[edx].ios_i,eax		; flush STDI
	ioflush( ebx )			; flush STDO
	jnz	@07			; copy next block
@09:
	pop	ecx
	mov	[ebx].ios_bp,ecx
	pop	ecx
	mov	[ebx].ios_size,ecx
	jmp	toend
success:
	xor	eax,eax
	inc	eax
toend:
	ret
@12:
	mov	eax,edi
	mov	[edx].ios_i,eax
	mov	[ebx].ios_i,eax
	ioflush( ebx )
	jmp	@09
@13:
	xor	eax,eax
	test	esi,esi
	jnz	@09
	test	edi,edi
	jnz	@09
	inc	eax
	jmp	@09
iocopy	ENDP

	END
