include string.inc

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

ifndef __SSE__

	.code

strncmp PROC s1:LPSTR, s2:LPSTR, count:SIZE_T

	push	esi
	push	edi
	push	edx

	mov	edi,12[esp+4]
	mov	esi,12[esp+8]
	mov	edx,12[esp+12]

	xor	eax,eax
	test	edx,edx
	jz	toend
@@:
	mov	al,[edi]
	cmp	al,[esi]
	lea	esi,[esi+1]
	lea	edi,[edi+1]
	jne	@F
	test	eax,eax
	je	toend
	dec	edx
	jnz	@B
	xor	eax,eax
	jmp	toend
@@:
	sbb	eax,eax
	sbb	eax,-1
toend:
	pop	edx
	pop	edi
	pop	esi
	ret	12
strncmp ENDP

else	; SSE2 - Auto install

include math.inc

	.data
	strncmp_p dd _rtl_strncmp

	.code

strncmp_SSE2:

	push	esi
	push	edi
	push	edx

	mov	edi,12[esp+4]
	mov	esi,12[esp+8]
	mov	edx,12[esp+12]

	mov	eax,edi
	mov	ecx,esi
	and	eax,16-1		;
	and	ecx,16-1		; aligned ?
	cmp	eax,ecx
	jne	misaligned

	pxor	xmm2,xmm2
	add	edx,edi
	test	eax,eax
	jz	loop_16

	sub	edi,eax
	sub	esi,eax
	movaps	xmm0,[esi]
	movaps	xmm1,[edi]
	add	edi,16
	add	esi,DWORD PTR 16
	mov	eax,-1
	shl	eax,cl
	push	eax
	pcmpeqb xmm0,xmm1	; compare s2, s1
	pmovmskb ecx,xmm0
	pcmpeqb xmm1,xmm2	; compare s1, 0
	pmovmskb eax,xmm1
	not	cx
	or	ecx,eax
	pop	eax
	and	ecx,eax
	jnz	exit_16

	ALIGN	16
loop_16:
	cmp	edi,edx
	jae	equal
	movaps	xmm0,[esi]
	movaps	xmm1,[edi]
	pcmpeqb xmm0,xmm1	; compare s2, s1
	pmovmskb ecx,xmm0
	pcmpeqb xmm1,xmm2	; compare s1, 0
	pmovmskb eax,xmm1
	add	edi,16
	add	esi,16
	not	cx
	or	ecx,eax
	jz	loop_16

exit_16:
	bsf	ecx,ecx
	lea	edi,[edi+ecx-16]
	cmp	edi,edx
	jae	equal
	mov	al,[edi]
	cmp	al,[esi+ecx-16]
	jne	notequal
	jmp	equal

	ALIGN	16

strncmp_386:

	push	esi
	push	edi
	push	edx

	mov	edi,12[esp+4]
	mov	esi,12[esp+8]
	mov	edx,12[esp+12]

misaligned:

	xor	eax,eax
	test	edx,edx
	jz	toend
loop_1:
	mov	al,[edi]
	cmp	al,[esi]
	lea	esi,[esi+1]
	lea	edi,[edi+1]
	jne	notequal
	test	eax,eax
	jz	toend
	dec	edx
	jnz	loop_1
	ALIGN	4
equal:
	xor	eax,eax
toend:
	pop	edx
	pop	edi
	pop	esi
	ret	12

	ALIGN	4
notequal:
	sbb	eax,eax
	sbb	eax,-1
	pop	edx
	pop	edi
	pop	esi
	ret	12

	ALIGN	16

strncmp PROC s1:LPSTR, s2:LPSTR, n:SIZE_T
	jmp	strncmp_p
strncmp ENDP

	ALIGN	4
	;
	; First call: set pointer and jump
	;
_rtl_strncmp:
	mov	eax,strncmp_386
	.if	sselevel & SSE_SSE2
		mov eax,strncmp_SSE2
	.endif
	mov	strncmp_p,eax
	jmp	eax

endif

	END
