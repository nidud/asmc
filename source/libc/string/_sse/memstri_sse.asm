include string.inc

ifdef __SSE__

	.code

option	stackbase:esp

memstri_sse proc uses esi edi ebx edx s1:LPSTR, l1:SIZE_T, s2:LPSTR, l2:SIZE_T

	mov	edi,s1
	mov	ecx,l1
	mov	esi,s2

	movzx	eax,BYTE PTR [esi]
	sub	al,'A'
	cmp	al,'Z'-'A'+1
	sbb	bl,bl
	and	bl,'a'-'A'
	add	al,bl
	add	al,'A'
	imul	eax,eax,01010101h
	movd	xmm1,eax
	pshufd	xmm1,xmm1,0		; tolower() * 16

	movzx	eax,al
	sub	al,'a'
	cmp	al,'z'-'a'+1
	sbb	bl,bl
	and	bl,'a'-'A'
	sub	al,bl
	add	al,'a'
	imul	eax,eax,01010101h
	movd	xmm2,eax
	pshufd	xmm2,xmm2,0		; toupper() * 16

	lea	ebx,[edi+ecx]		; limit

	ALIGN	4
loop_16U:

	test	edi,15
	jz	loop_16

	mov	ecx,edi			; seek back and test 16 bytes
	and	ecx,16-1		; create mask
	sub	edi,ecx
	movaps	xmm0,[edi]
	movaps	xmm4,xmm0		; test block
	pcmpeqb xmm0,xmm1		;
	pmovmskb eax,xmm0
	pcmpeqb xmm4,xmm2
	pmovmskb edx,xmm4
	add	edi,16
	or	eax,edx
	or	edx,-1
	shl	edx,cl
	and	eax,edx			; remove head bytes..
	jnz	exit_16

	ALIGN	4
loop_16:
	cmp	edi,ebx
	jae	nomatch_16
	movaps	xmm0,[edi]
	movaps	xmm4,xmm0
	pcmpeqb xmm0,xmm1
	pmovmskb eax,xmm0
	pcmpeqb xmm4,xmm2
	pmovmskb ecx,xmm4
	add	edi,16
	or	eax,ecx
	jz	loop_16

exit_16:
	mov	ecx,l2
	bsf	eax,eax
	lea	edi,[edi+eax-16]
	lea	eax,[edi+ecx-1]
	cmp	eax,ebx
	jae	nomatch

	inc	edi

	ALIGN	4
compare:
	sub	ecx,1
	jz	match
	mov	al,[esi+ecx]
	cmp	al,[edi+ecx-1]
	je	compare
	mov	ah,[edi+ecx-1]
	sub	ax,'AA'
	cmp	al,'Z'-'A' + 1
	sbb	dl,dl
	and	dl,'a'-'A'
	cmp	ah,'Z'-'A' + 1
	sbb	dh,dh
	and	dh,'a'-'A'
	add	ax,dx
	add	ax,'AA'
	cmp	al,ah
	je	compare
	jmp	loop_16U
nomatch:
	xor	eax,eax
	jmp	toend
match:
	mov	eax,edi
	dec	eax
toend:
	ret
memstri_sse endp
endif
	END
