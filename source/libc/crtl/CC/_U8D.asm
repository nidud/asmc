	.486
	.model	flat, c
	.code

_U8D	proc	; edx:eax / ecx:ebx

	test	ecx,ecx
	jnz	noteasy
	dec	ebx
	jz	quit
	inc	ebx
	cmp	ebx,edx
	ja	@F
	mov	ecx,eax
	mov	eax,edx
	xor	edx,edx
	div	ebx
	xchg	ecx,eax
@@:
	div	ebx
	mov	ebx,edx
	mov	edx,ecx
	xor	ecx,ecx
quit:
	ret
noteasy:
	cmp	ecx,edx
	jb	thehardway
	jne	@F
	cmp	ebx,eax
	ja	@F
	sub	eax,ebx
	mov	ebx,eax
	xor	ecx,ecx
	xor	edx,edx
	mov	eax,1
	ret
@@:
	xor	ecx,ecx
	xor	ebx,ebx
	xchg	ebx,eax
	xchg	ecx,edx
	ret
thehardway:
	push	ebp
	push	esi
	push	edi
	sub	esi,esi
	mov	edi,esi
	mov	ebp,esi
@@:
	add	ebx,ebx
	adc	ecx,ecx
	jc	L009
	inc	ebp
	cmp	ecx,edx
	jc	@B
	ja	@F
	cmp	ebx,eax
	jbe	@B
@@:
	clc
lupe:
	adc	esi,esi
	adc	edi,edi
	dec	ebp
	js	toend
L009:
	rcr	ecx,1
	rcr	ebx,1
	sub	eax,ebx
	sbb	edx,ecx
	cmc
	jc	lupe
@@:
	add	esi,esi
	adc	edi,edi
	dec	ebp
	js	done
	shr	ecx,1
	rcr	ebx,1
	add	eax,ebx
	adc	edx,ecx
	jnc	@B
	jmp	lupe
done:
	add	eax,ebx
	adc	edx,ecx
toend:
	mov	ebx,eax
	mov	ecx,edx
	mov	eax,esi
	mov	edx,edi
	pop	edi
	pop	esi
	pop	ebp
	ret
_U8D	endp

	END
