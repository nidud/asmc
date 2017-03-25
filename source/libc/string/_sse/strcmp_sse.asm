include string.inc

ifdef __SSE__

	.code

	option	stackbase:esp

strcmp_sse proc uses esi edi s1:LPSTR, s2:LPSTR

	mov	eax,s1
	mov	ecx,s2
	mov	edi,eax
	mov	esi,ecx
	and	eax,16-1		;
	and	ecx,16-1		; aligned ?
	cmp	eax,ecx
	jne	misaligned

	push	edx

	pxor	xmm2,xmm2		; populate ZERO	 in xmm2
	xor	edx,edx
	test	eax,eax
	jz	loop_16

	sub	edi,ecx			; align 16 <-- left
	sub	esi,ecx

	sub	edx,1			; create mask
	shl	edx,cl			;

	movaps	xmm0,[esi]
	movaps	xmm1,[edi]
	pcmpeqb xmm1,xmm0		; compare 16 bytes
	pcmpeqb xmm0,xmm2		; test for zero
	pmovmskb eax,xmm1
	pmovmskb ecx,xmm0
	not	ax
	or	ecx,eax			; combine result
	and	ecx,edx			; remove bytes in front
	mov	edx,16
	jnz	done

	ALIGN	16
loop_16:
	movaps	xmm0,[esi+edx]
	movaps	xmm1,[edi+edx]
	pcmpeqb xmm1,xmm0		; compare
	pmovmskb eax,xmm1
	pcmpeqb xmm0,xmm2		; test for zero
	pmovmskb ecx,xmm0
	add	edx,16
	not	ax
	or	ecx,eax
	jz	loop_16
done:
	bsf	ecx,ecx
	lea	ecx,[edx+ecx-16]
	mov	al,[edi+ecx]
	cmp	al,[esi+ecx]
	jz	@F
	sbb	al,al
	sbb	al,-1
@@:
	movsx	eax,al
	pop	edx
toend:
	ret

misaligned:
	xor	eax,eax
	ALIGN	4
@@:
	xor	al,[edi]
	jz	zero_0
	sub	al,[esi]
	jnz	@F
	xor	al,[edi+1]
	jz	zero_1
	sub	al,[esi+1]
	jnz	@F
	xor	al,[edi+2]
	jz	zero_2
	sub	al,[esi+2]
	jnz	@F
	xor	al,[edi+3]
	jz	zero_3
	sub	al,[esi+3]
	jnz	@F
	lea	edi,[edi+4]
	lea	esi,[esi+4]
	jmp	@B
	ALIGN	4
@@:
	sbb	eax,eax
	sbb	eax,-1
	jmp	toend
zero_3: add	esi,1
zero_2: add	esi,1
zero_1: add	esi,1
zero_0: sub	al,[esi]
	jnz	@B
	jmp	toend
strcmp_sse endp
endif
	END
