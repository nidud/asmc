	.486
	.model	flat, c
	.code

_iLDFD	proc uses ecx ebx esi
	;
	; long double[eax] to double[edx]
	;
	push	edx
	movzx	ecx,word ptr [eax+8]
	mov	edx,[eax+4]
	mov	eax,[eax]
	mov	esi,0FFFFF800h
	mov	ebx,eax
	shl	ebx,22
	jnc	L002
	jnz	@F
	shl	esi,1
@@:
	add	eax,0800h
	adc	edx,0
	jnc	L002
	mov	edx,80000000h
	inc	cx
L002:
	and	eax,esi
	mov	ebx,ecx
	and	cx,7FFFh
	add	cx,03FFh-3FFFh
	cmp	cx,07FFh
	jae	L005
	test	cx,cx
	jnz	@F
	shrd	eax,edx,12
	shl	edx,1
	shr	edx,12
	jmp	L004
@@:
	shrd	eax,edx,11
	shl	edx,1
	shrd	edx,ecx,11
L004:
	shl	bx,1
	rcr	edx,1
	jmp	toend
L005:
	cmp	cx,0C400h
	jb	L009
	cmp	cx,-52
	jl	L007
	sub	cx,12
	neg	cx
	cmp	cl,32
	jb	L006
	sub	cl,32
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
	shl	edx,1
	shr	edx,11
	shl	bx,1
	rcr	edx,1
	or	edx,7FF00000h
	cmp	cx,43FFh
	je	toend
	;int	3	; OVERFLOW exception
toend:
	pop	esi
	mov	[esi],eax
	mov	[esi+4],edx
	ret
_iLDFD	endp

	END
