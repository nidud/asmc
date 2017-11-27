	.486
	.model	flat, c
	.code

_FLDA	PROC USES esi edi ecx
	;
	; long double[EBX] = long double[EAX] + long double[EDX]
	;
	push	ebx
	movzx	esi,WORD PTR [edx+8]
	mov	ecx,[edx+4]
	mov	ebx,[edx]
	shl	esi,16
	movzx	esi,WORD PTR [eax+8]
	mov	edx,[eax+4]
	mov	eax,[eax]
	xor	edi,edi
	call	L012
	pop	ebx
	mov	[ebx],eax
	mov	[ebx+4],edx
	mov	[ebx+8],si
	ret
_FLDA	ENDP

_FLDS	PROC USES esi edi ecx
	;
	; long double[EBX] = long double[EAX] - long double[EDX]
	;

	push	ebx
	movzx	esi,WORD PTR [edx+8]
	mov	ecx,[edx+4]
	mov	ebx,[edx]
	shl	esi,16
	movzx	esi,WORD PTR [eax+8]
	mov	edx,[eax+4]
	mov	eax,[eax]
	mov	edi,80000000h
	call	L012
	pop	ebx
	mov	[ebx],eax
	mov	[ebx+4],edx
	mov	[ebx+8],si
	ret
_FLDS	ENDP

L012:
	add	si,1
	jc	L001
	jo	L001
	add	esi,0FFFFh
	jc	L010
	jo	L010
	sub	esi,10000h
	xor	esi,edi
	test	eax,eax
	jnz	L015
	test	edx,edx
	jnz	L015
	add	si,si
	jnz	L014
	shr	esi,16
	mov	eax,ebx
	mov	edx,ecx
	add	esi,esi
	or	bx,si
	or	ebx,edx
	jz	@F
	shr	esi,1
@@:
	ret
L001:
	dec	si
	add	esi,10000h
	jc	@F
	jo	@F
	ret
@@:
	sub	esi,10000h
	test	eax,eax
	jnz	L006
	test	ebx,ebx
	jnz	L006
	cmp	edx,80000000h
	jnz	L006
	cmp	ecx,edx
	jnz	L006
	mov	eax,esi
	shr	eax,16
	cmp	si,ax
	mov	eax,ebx
	jnz	@F
	test	edi,edi
	jnz	L004
	ret
@@:
	or	edi,edi
	jnz	L009
L004:
	sar	edx, 1
	mov	esi,65535
	ret
L006:
	cmp	edx,ecx
	jnz	@F
	cmp	eax,ebx
@@:
	ja	L009
	jnz	@F
	or	edi,edi
@@:
	jz	L009
	mov	edx,ecx
	mov	eax,ebx
	shr	esi,16
L009:
	ret
L010:
	mov	edx,ecx
	mov	eax,ebx
	sub	esi,10000h
	test	eax,eax
	jnz	@F
	cmp	edx,80000000h
	jnz	@F
	xor	esi,edi
@@:
	shr	esi,16
	ret
L014:
	rcr	si,1
L015:
	or	ecx,ecx
	jnz	@F
	or	ebx,ebx
	jnz	@F
	test	esi,7FFF0000h
	jnz	@F
	ret
@@:
	push	ebp
	xchg	esi,ecx
	mov	edi,ecx
	rol	edi,16
	sar	edi,16
	sar	ecx,16
	and	edi,80007FFFh
	and	ecx,80007FFFh
	mov	ebp,ecx
	rol	edi,16
	rol	ecx,16
	add	cx,di
	rol	edi,16
	rol	ecx,16
	sub	cx,di
	jz	L018
	jnc	@F
	mov	ebp,edi
	neg	cx
	xchg	ebx,eax
	xchg	esi,edx
@@:
	cmp	cx,64
	jbe	L018
	add	ebp,ebp
	rcr	bp,1
	mov	eax,ebx
	mov	edx,esi
	mov	esi,ebp
	pop	ebp
	ret
L018:
	mov	ch,0
	test	ecx,ecx
	jns	@F
	mov	ch,-1
	neg	esi
	neg	ebx
	sbb	esi,0
	xor	ebp,80000000h
@@:
	sub	edi,edi
	cmp	cl,0
	jz	L022
	push	ebx
	sub	ebx,ebx
	cmp	cl,32
	jc	L021
	test	eax,eax
	setne	bl
	mov	edi,ebx
	sub	ebx,ebx
	cmp	cl,64
	jnz	@F
	or	edi,edx
	sub	edx,edx
@@:
	mov	eax,edx
	sub	edx,edx
L021:
	shrd	ebx,eax,cl
	or	edi,ebx
	sub	ebx,ebx
	shrd	eax,edx,cl
	shrd	edx,ebx,cl
	pop	ebx
L022:
	add	eax,ebx
	adc	edx,esi
	adc	ch,0
	jns	L024
	cmp	cl,64
	jnz	@F
	test	edi,7FFFFFFFh
	setne	bl
	shr	ebx,1
	adc	eax,0
	adc	edx,0
	adc	ch,0
@@:
	neg	edx
	neg	eax
	sbb	edx,0
	mov	ch,0
	xor	ebp,80000000h
L024:
	mov	ebx,eax
	or	bl,ch
	or	ebx,edx
	jz	L029
	test	bp,bp
	jz	toend
	cmp	ch,0
	jnz	L026
	rol	edi,1
	ror	edi,1
@@:
	dec	bp
	jz	toend
	adc	eax,eax
	adc	edx,edx
	jnc	@B
L026:
	inc	bp
	cmp	bp,7FFFh
	jz	overflow
	stc
	rcr	edx,1
	rcr	eax,1
	jnc	toend
	add	edi,edi
	jnz	@F
	ror	eax,1
	rol	eax,1
@@:
	adc	eax,0
	adc	edx,0
	jnc	toend
	rcr	edx,1
	rcr	eax,1
	inc	bp
	cmp	bp,7FFFh
	je	overflow
	jmp	toend
L029:
	mov	ebp,ebx
toend:
	add	ebp,ebp
	rcr	bp,1
	mov	esi,ebp
	pop	ebp
	ret
overflow:
	mov	ebp,00007FFFh
	xor	eax,eax
	mov	edx,80000000h
	jmp	toend

	END
