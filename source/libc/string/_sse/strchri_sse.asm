include string.inc

ifdef __SSE__

	.code

option	stackbase:esp

strchri_sse proc uses esi string:LPSTR, char:SINT

	mov	esi,string
	movzx	eax,byte ptr char

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
	ret
strchri_sse endp
endif
	END
