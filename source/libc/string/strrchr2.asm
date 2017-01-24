include string.inc

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

ifndef __SSE__

	.code

strrchr2 PROC string:LPSTR, char1:SIZE_T, char2:SIZE_T
strrchr2 ENDP

else	; SSE2 - Auto install

include crtl.inc

	.data
	strrchr2_p dd _rtl_strrchr2

	.code

strrchr2_SSE2:

	push	edi

	mov	edi,4[esp+4]

	invoke	strlen,edi		; get length

	mov	cl, 4[esp+8]
	mov	ch, 4[esp+12]

	test	eax,eax			; 0
	jz	exit_null
	test	eax,-16			; 1..15
	jz	exit_tail

	and	ecx,DWORD PTR 000000FFh ; fill
	imul	ecx,ecx,01010101h
	movd	xmm1,ecx
	pshufd	xmm1,xmm1,0		; populate char1 in xmm1

	movzx	ecx,BYTE PTR 4[esp+12]
	imul	ecx,ecx,01010101h
	movd	xmm2,ecx
	pshufd	xmm2,xmm2,0		; populate char2 in xmm2

	ALIGN	16

loop_16:
	sub	eax,16
	movups	xmm3,[edi+eax]
	movaps	xmm4,xmm3
	pcmpeqb xmm3,xmm1
	pcmpeqb xmm4,xmm2
	pmaxub	xmm3,xmm4		; combine result
	pmovmskb ecx,xmm3		; get result bits
	test	ecx,ecx
	jnz	exit_16
	cmp	eax,16
	ja	loop_16
	xor	eax,eax
	movups	xmm3,[edi]
	movaps	xmm4,xmm3
	pcmpeqb xmm3,xmm1
	pcmpeqb xmm4,xmm2
	pmaxub	xmm3,xmm4
	pmovmskb ecx,xmm3
	test	ecx,ecx
	jz	exit_fail
exit_16:
	bsr	ecx,ecx
	add	eax,ecx
exit_eax:
	add	eax,edi
	pop	edi
	ret	12

exit_null:
	;
	; If char is 0..?
	;
	cmp	cl,[edi+eax]
	je	exit_eax
	cmp	ch,[edi+eax]
	je	exit_eax

exit_fail:
	xor	eax,eax
	pop	edi
	ret	12

exit_tail:
	cmp	cl,[edi+eax-1]
	je	exit_count
	cmp	ch,[edi+eax-1]
	je	exit_count
	dec	eax
	jnz	exit_tail
	pop	edi
	ret	12

exit_count:
	add	eax,edi
	dec	eax
	pop	edi
	ret	12

	ALIGN	16

strrchr2 PROC string:LPSTR, char1:SIZE_T, char2:SIZE_T
	jmp	strrchr2_p
strrchr2 ENDP

	ALIGN	4
	;
	; First call: set pointer and jump
	;
_rtl_strrchr2:
	mov	eax,strrchr2_386
	.if	sselevel & SSE_SSE2
		mov eax,strrchr2_SSE2
	.endif
	mov	strrchr2_p,eax
	jmp	eax

	ALIGN	4

strrchr2_386:

endif
	push	edi
	mov	edi,4[esp+4]

	xor	eax,eax
	mov	ecx,-1
	repnz	scasb
	mov	eax,ecx
	not	eax
	dec	eax
	jz	toend

	mov	edi,4[esp+4]
	mov	cl, 4[esp+8]
	mov	ch, 4[esp+12]
	lea	eax,[edi+eax-1]
	ALIGN	4
lupe:
	cmp	cl,[eax]
	je	toend
	cmp	ch,[eax]
	je	toend
	dec	eax
	cmp	eax,edi
	jae	lupe
exit_0:
	xor	eax,eax
toend:
	test	eax,eax
	pop	edi
	ret	12

	END
