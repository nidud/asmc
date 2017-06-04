include asmc.inc

	.code

_atoow	PROC USES esi edi ebx dst:LPSTR, src:LPSTR, radix:SINT, bsize:SINT
	mov	esi,src
	mov	edx,dst
	mov	ebx,radix
	mov	edi,bsize

ifdef	CHEXPREFIX
	movzx	eax,WORD PTR [esi]
	or	eax,00002000h
	.if	eax == 'x0'
		add esi,2
		sub edi,2
	.endif
endif

	xor	eax,eax
	mov	[edx],eax
	mov	[edx+4],eax
	mov	[edx+8],eax
	mov	[edx+12],eax

	cmp	ebx,10
	je	radix_10
	jb	do_slow
	cmp	edi,16		; default to HEX DWORD
	ja	do_slow

radix_16:
	xor	edx,edx
	xor	ecx,ecx
	cmp	edi,8
	ja	radix_16_QWORD

	ALIGN	4
radix_16_DWORD:			; FFFFFFFF = 8
	mov	al,[esi]
	add	esi,1
	and	eax,not 30h
	bt	eax,6
	sbb	ebx,ebx
	and	ebx,55
	sub	eax,ebx
	shl	ecx,4
	add	ecx,eax
	dec	edi
	jnz	radix_16_DWORD
	jmp	done8

	ALIGN	4
radix_16_QWORD:			; FFFFFFFFFFFFFFFF = 16
	mov	al,[esi]
	add	esi,1
	and	eax,not 30h
	bt	eax,6
	sbb	ebx,ebx
	and	ebx,55
	sub	eax,ebx
	shld	edx,ecx,4
	shl	ecx,4
	add	ecx,eax
	adc	edx,0
	dec	edi
	jnz	radix_16_QWORD
	jmp	done8

	ALIGN	4
radix_10:
	cmp	edi,20
	ja	do_slow
	xor	edx,edx
	xor	ecx,ecx
	mov	cl,[esi]
	add	esi,1
	sub	cl,'0'
	cmp	edi,10
	jae	radix_10_QWORD

	ALIGN	4
radix_10_DWORD:			; FFFFFFFF - 4294967295 = 10
	dec	edi
	jz	done8
	mov	al,[esi]
	add	esi,1
	sub	al,'0'
	lea	ebx,[ecx*8+eax]
	lea	ecx,[ecx*2+ebx]
	jmp	radix_10_DWORD

	ALIGN	4
radix_10_QWORD:			; FFFFFFFFFFFFFFFF - 18446744073709551615 = 20
	dec	edi
	jz	done8
	mov	al,[esi]
	add	esi,1
	sub	al,'0'
	mov	ebx,edx
	mov	bsize,ecx
	shld	edx,ecx,3
	shl	ecx,3
	add	ecx,bsize
	adc	edx,ebx
	add	ecx,bsize
	adc	edx,ebx
	add	ecx,eax
	adc	edx,0
	jmp	radix_10_QWORD

	ALIGN	4
do_slow:
	mov	bsize,edi
	mov	edi,edx
	ALIGN	4
do:
	mov	al,[esi]
	and	eax,not 30h
	bt	eax,6
	sbb	ecx,ecx
	and	ecx,55
	sub	eax,ecx
	mov	ecx,8

	ALIGN	4
@@:
	movzx	edx,WORD PTR [edi]
	imul	edx,ebx
	add	eax,edx
	mov	[edi],ax
	add	edi,2
	shr	eax,16
	dec	ecx
	jnz	@B
	sub	edi,16
	add	esi,1
	dec	bsize
	jnz	do
	mov	eax,dst
	jmp	toend

	ALIGN	4
done8:
	mov	eax,dst
	mov	[eax],ecx
	mov	[eax+4],edx
toend:
	ret
_atoow	ENDP

	END
