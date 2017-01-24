include string.inc

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

ifndef __SSE__

	.code

strchri PROC string:LPSTR, char:SIZE_T
	push	esi

	mov	esi,4[esp+4]
	movzx	eax,byte ptr 4[esp+8]

	sub	al,'A'
	cmp	al,'Z'-'A'+1
	sbb	cl,cl
	and	cl,'a'-'A'
	add	cl,al
	add	cl,'A'
@@:
	mov	al,[esi]
	test	eax,eax
	jz	toend
	add	esi,1
	sub	al,'A'
	cmp	al,'Z'-'A'+1
	sbb	ch,ch
	and	ch,'a'-'A'
	add	al,ch
	add	al,'A'
	cmp	al,cl
	jne	@B
	mov	eax,esi
	dec	eax
toend:
	pop	esi
	ret	8
strchri ENDP

else	; SSE2 - Auto install

include crtl.inc

	.data
	strchri_p dd _rtl_strchri

	.code

strchri_SSE2:

	push	esi

	mov	esi,4[esp+4]
	movzx	eax,byte ptr 4[esp+8]

	pxor	xmm0,xmm0		; zero * 16

	sub	al,'A'
	cmp	al,'Z'-'A'+1
	sbb	ecx,ecx
	and	ecx,'a'-'A'
	add	eax,ecx
	add	al,'A'
	imul	ecx,eax,01010101h
	movd	xmm1,ecx
	pshufd	xmm1,xmm1,0		; tolower() * 16

	sub	al,'a'
	cmp	al,'z'-'a'+1
	sbb	ecx,ecx
	and	cl,'a'-'A'
	sub	eax,ecx
	add	al,'a'
	imul	eax,eax,01010101h
	movd	xmm2,eax
	pshufd	xmm2,xmm2,0		; toupper() * 16

	mov	ecx,esi			; aligned 16 ?
	and	ecx,16-1
	jz	loop_16

	mov	eax,-1			; create skip-mask
	shl	eax,cl
	sub	esi,ecx			; align 16 <--
	movaps	xmm3,[esi]
	movdqa	xmm4,xmm3
	movdqa	xmm5,xmm3
	pcmpeqb xmm3,xmm0		; test for 0, upper, and lower
	pcmpeqb xmm4,xmm1
	pcmpeqb xmm5,xmm2
	pmaxub	xmm3,xmm4		; combine result
	pmaxub	xmm3,xmm5
	pmovmskb ecx,xmm3
	add	esi,16
	and	ecx,eax
	jnz	exit_16

	ALIGN	16
loop_16:
	movaps	xmm3,[esi]
	movaps	xmm4,xmm3
	movaps	xmm5,xmm3
	pcmpeqb xmm3,xmm0
	pcmpeqb xmm4,xmm1
	pcmpeqb xmm5,xmm2
	pmaxub	xmm3,xmm4
	pmaxub	xmm3,xmm5
	pmovmskb ecx,xmm3
	add	esi,16
	test	ecx,ecx
	jz	loop_16
exit_16:
	bsf	ecx,ecx
	lea	eax,[esi+ecx-16]
	cmp	BYTE PTR [eax],0
	jne	toend
	xor	eax,eax
toend:
	pop	esi
	ret	8

	ALIGN	4

strchri_386:

	push	esi

	mov	esi,4[esp+4]
	movzx	eax,byte ptr 4[esp+8]

	sub	al,'A'
	cmp	al,'Z'-'A'+1
	sbb	cl,cl
	and	cl,'a'-'A'
	add	cl,al
	add	cl,'A'
@@:
	mov	al,[esi]
	test	eax,eax
	jz	toend
	add	esi,1
	sub	al,'A'
	cmp	al,'Z'-'A'+1
	sbb	ch,ch
	and	ch,'a'-'A'
	add	al,ch
	add	al,'A'
	cmp	al,cl
	jne	@B
	mov	eax,esi
	dec	eax
	jmp	toend

	ALIGN	16

strchri PROC string:LPSTR, char:SIZE_T
	jmp	strchri_p
strchri ENDP

	ALIGN	4
	;
	; First call: set pointer and jump
	;
_rtl_strchri:
	mov	eax,strchri_386
	.if	sselevel & SSE_SSE2
		mov eax,strchri_SSE2
	.endif
	mov	strchri_p,eax
	jmp	eax
endif

	END
