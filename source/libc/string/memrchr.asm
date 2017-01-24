include string.inc

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

	.code

ifndef __SSE__

memrchr PROC base:LPSTR, char:SIZE_T, bsize:SIZE_T
	push	edi
	mov	edi,4[esp+4]
	mov	al, 4[esp+8]
	mov	ecx,4[esp+12]
	test	ecx,ecx
	jz	@F
	lea	edi,[edi+ecx-1]
	std
	repnz	scasb
	cld
	jnz	@F
	mov	eax,edi
	inc	eax
	pop	edi
	ret	12
@@:
	xor	eax,eax
	pop	edi
	ret	12
memrchr ENDP

else	; SSE2 - Auto install

include crtl.inc

	.data
	memrchr_p dd _rtl_memrchr

	.code

memrchr_SSE2:

	push	edi
	push	ebx

	mov	edi,8[esp+4]
	movzx	ebx,BYTE PTR 8[esp+8]
	mov	eax,8[esp+12]

	cmp	eax,16
	jb	tail_16

	imul	ebx,ebx,01010101h
	movd	xmm1,ebx
	pshufd	xmm1,xmm1,0

	ALIGN	4
loop_16:
	sub	eax,16
	movups	xmm0,[edi+eax]
	pcmpeqb xmm0,xmm1
	pmovmskb ecx,xmm0
	test	ecx,ecx
	jnz	exit_16
	cmp	eax,16
	ja	loop_16

	xor	eax,eax
	movups	xmm0,[edi]
	pcmpeqb xmm0,xmm1
	pmovmskb ecx,xmm0
	test	ecx,ecx
	jz	not_found
exit_16:
	bsr	ecx,ecx
	add	eax,ecx
	add	eax,edi
	pop	ebx
	pop	edi
	ret	12
	ALIGN	4
tail_16:
	add	eax,edi
	ALIGN	4
tail:
	sub	eax,1
	cmp	eax,edi
	jb	not_found
	cmp	[eax],bl
	jne	tail
	test	eax,eax
	pop	ebx
	pop	edi
	ret	12
	ALIGN	4
not_found:
	xor	eax,eax
	pop	ebx
	pop	edi
	ret	12

	ALIGN	4

memrchr_386:
	push	edi
	mov	edi,4[esp+4]
	mov	al, 4[esp+8]
	mov	ecx,4[esp+12]
	test	ecx,ecx
	jz	@F
	lea	edi,[edi+ecx-1]
	std
	repnz	scasb
	cld
	jnz	@F
	mov	eax,edi
	inc	eax
	pop	edi
	ret	12
@@:
	xor	eax,eax
	pop	edi
	ret	12

	ALIGN	16

memrchr PROC base:LPSTR, char:SIZE_T, bsize:SIZE_T
	jmp	memrchr_p
memrchr ENDP

	ALIGN	4
	;
	; First call: set pointer and jump
	;
_rtl_memrchr:
	mov	eax,memrchr_386
	.if	sselevel & SSE_SSE2
		mov eax,memrchr_SSE2
	.endif
	mov	memrchr_p,eax
	jmp	eax

endif
	END
