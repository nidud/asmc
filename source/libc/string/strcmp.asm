include string.inc

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

ifndef __SSE__

	.code

strcmp	PROC s1:LPSTR, s2:LPSTR
	push	edx
	mov	edx,4[esp+4]
	mov	ecx,4[esp+8]
	xor	eax,eax
	ALIGN	4
@@:
	xor	al,[edx]
	jz	zero_0
	sub	al,[ecx]
	jnz	done
	xor	al,[edx+1]
	jz	zero_1
	sub	al,[ecx+1]
	jnz	done
	xor	al,[edx+2]
	jz	zero_2
	sub	al,[ecx+2]
	jnz	done
	xor	al,[edx+3]
	jz	zero_3
	sub	al,[ecx+3]
	jnz	done
	lea	edx,[edx+4]
	lea	ecx,[ecx+4]
	jmp	@B
	ALIGN	4
done:
	sbb	eax,eax
	sbb	eax,-1
	pop	edx
	ret	8
zero_3:
	add	ecx,1
zero_2:
	add	ecx,1
zero_1:
	add	ecx,1
zero_0:
	sub	al,[ecx]
	jnz	done
	pop	edx
	ret	8
strcmp	ENDP

else	; SSE2 - Auto install

include math.inc

	.data
	strcmp_p dd _rtl_strcmp

	.code

strcmp_SSE2:

	mov	eax,[esp+4]		; dst
	mov	ecx,[esp+8]		; src

	push	esi
	push	edi

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
	pop	edi
	pop	esi
	ret	8

	ALIGN	16

strcmp_386:

	push	esi
	push	edi


	mov	edi,8[esp+4]		; dst
misaligned:
	mov	esi,8[esp+8]		; src

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
	pop	edi
	pop	esi
	ret	8
zero_3:
	add	esi,1
zero_2:
	add	esi,1
zero_1:
	add	esi,1
zero_0:
	sub	al,[esi]
	jnz	@B
	pop	edi
	pop	esi
	ret	8

	ALIGN	16

strcmp	PROC s1:LPSTR, s2:LPSTR
	jmp	strcmp_p
strcmp	ENDP

	ALIGN	4
	;
	; First call: set pointer and jump
	;
_rtl_strcmp:
	mov	eax,strcmp_386
	.if	sselevel & SSE_SSE2
		mov eax,strcmp_SSE2
	.endif
	mov	strcmp_p,eax
	jmp	eax

endif

	END
