	.486
	.model	flat, stdcall

public	_iLDFD

	.code
	;
	; long double[eax] to double[edx]
	;
_iLDFD:

_fldtod PROC
	push	ecx
	push	ebx
	push	esi
	push	edx
	movzx	ecx,word ptr [eax+8]
	mov	edx,[eax+4]
	mov	eax,[eax]
	mov	esi,0FFFFF800h
	mov	ebx,eax
	shl	ebx,22
	jnc	L002
	jnz	@F
	add	esi,esi
@@:
	add	eax,00000800h
	adc	edx,0
	jnc	L002
	mov	edx,80000000h
	inc	ecx
L002:
	and	eax,esi
	mov	ebx,ecx
	and	ecx,00007FFFh
	add	ecx,0FFFFC400h
	and	ecx,0000FFFFh
	cmp	ecx,000007FFh
	jnc	L005
	test	ecx,ecx
	jnz	@F
	shrd	eax,edx,12
	add	edx,edx
	shr	edx,12
	jmp	L004
@@:
	shrd	eax,edx,11
	add	edx,edx
	shrd	edx,ecx,11
L004:
	shl	ebx,1
	rcr	edx,1
	jmp	toend
L005:
	cmp	ecx,0000C400h
	jb	L009
	cmp	ecx,0000FFCCh
	jl	L007
	sub	ecx,0000000Ch
	neg	ecx
	and	ecx,0FFFF0000h
	cmp	ecx,00000020h
	jb	L006
	sub	ecx,00000020h
	mov	esi,eax
	mov	eax,edx
	xor	edx,edx
L006:
	shrd	esi,eax,cl
	shrd	eax,edx,cl
	shr	edx,cl
	add	esi,esi
	adc	eax,0
	adc	edx,0
	jmp	toend
L007:
	xor	eax,eax
	xor	edx,edx
	shl	ebx,17
	rcr	edx,1
	jmp	toend
L009:
	shrd	eax,edx,11
	add	edx,edx
	shr	edx,11
	shl	ebx,1
	rcr	edx,1
	or	edx,7FF00000h
	cmp	ecx,000043FFh
	je	toend
	int	3	; OVERFLOW exception
toend:
	pop	esi
	mov	[esi],eax
	mov	[esi+4],edx
	pop	esi
	pop	ebx
	pop	ecx
	ret
_fldtod ENDP

	END
