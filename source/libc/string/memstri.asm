include string.inc

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

ifndef __SSE__

	.code

memstri PROC s1:LPSTR, l1:SIZE_T, s2:LPSTR, l2:SIZE_T
memstri ENDP

else	; SSE2 - Auto install

include crtl.inc

	.data
	memstri_p dd _rtl_memstri

	.code

memstri_SSE2:

	push	esi
	push	edi
	push	ebx
	push	edx

	mov	edi,16[esp+4]		; s1
	mov	ecx,16[esp+8]		; l1
	mov	esi,16[esp+12]		; s2

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
	mov	ecx,16[esp+16]
	bsf	eax,eax
	lea	edi,[edi+eax-16]
	lea	eax,[edi+ecx-1]
	cmp	eax,ebx
	jae	nomatch_16

	inc	edi

	ALIGN	4
compare_16:
	sub	ecx,1
	jz	match_16
	mov	al,[esi+ecx]
	cmp	al,[edi+ecx-1]
	je	compare_16
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
	je	compare_16
	jmp	loop_16U
nomatch_16:
	xor	eax,eax
	jmp	toend
match_16:
	mov	eax,edi
	dec	eax
	jmp	toend

	ALIGN	16

memstri PROC s1:LPSTR, l1:SIZE_T, s2:LPSTR, l2:SIZE_T
	jmp	memstri_p
memstri ENDP

	ALIGN	4
	;
	; First call: set pointer and jump
	;
_rtl_memstri:
	mov	eax,memstri_386
	.if	sselevel & SSE_SSE2
		mov eax,memstri_SSE2
	.endif
	mov	memstri_p,eax
	jmp	eax

	ALIGN	16

memstri_386:

endif
	push	esi
	push	edi
	push	ebx
	push	edx

	mov	edi,16[esp+4]		; s1
	mov	ecx,16[esp+8]		; l1
	mov	esi,16[esp+12]		; s2

	mov	al,[esi]
	sub	al,'A'
	cmp	al,'Z'-'A'+1
	sbb	bl,bl
	and	bl,'a'-'A'
	add	bl,al
	add	bl,'A'
scan:
	test	ecx,ecx
	jz	nomatch
	dec	ecx
	mov	al,[edi]
	add	edi,1
	sub	al,'A'
	cmp	al,'Z'-'A'+1
	sbb	bh,bh
	and	bh,'a'-'A'
	add	al,bh
	add	al,'A'
	cmp	al,bl
	jne	scan
	mov	edx,16[esp+16]		; l2
	dec	edx
	jz	match
	cmp	ecx,edx
	jl	nomatch
compare:
	dec	edx
	jl	match
	mov	al,[esi+edx+1]
	cmp	al,[edi+edx]
	je	compare
	mov	ah,[edi+edx]
	sub	ax,'AA'
	cmp	al,'Z'-'A' + 1
	sbb	bh,bh
	and	bh,'a'-'A'
	add	al,bh
	cmp	ah,'Z'-'A' + 1
	sbb	bh,bh
	and	bh,'a'-'A'
	add	ah,bh
	add	ax,'AA'
	cmp	al,ah
	je	compare
	jmp	scan
nomatch:
	xor	eax,eax
	jmp	toend
match:
	mov	eax,edi
	dec	eax
toend:
	pop	edx
	pop	ebx
	pop	edi
	pop	esi
	ret	16

	END
