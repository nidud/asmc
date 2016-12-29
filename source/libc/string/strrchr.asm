include string.inc

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

ifndef __SSE__

	.code

strrchr PROC string:LPSTR, char:SIZE_T

	push	edi
	mov	edi,4[esp+4]

	xor	eax,eax
	mov	ecx,-1
	repne	scasb
	not	ecx
	dec	edi
	mov	al,4[esp+8]
	std
	repne	scasb
	cld
	mov	al,0
	jne	@F
	lea	eax,[edi+1]
@@:
	test	eax,eax
	pop	edi
	ret	8
strrchr ENDP

else	; SSE2 - Auto install

include math.inc

	.data
	strrchr_p dd _rtl_strrchr

	.code

strrchr_SSE2:

	push	edi

	mov	edi,4[esp+4]
	push	edi
	call	strlen

	movzx	ecx,byte ptr 4[esp+8]

	test	eax,eax			; 0
	jz	exit_if_null
	test	eax,-16			; 1..15
	jz	exit_tail

	imul	ecx,ecx,01010101h
	movd	xmm1,ecx
	pshufd	xmm1,xmm1,0	; populate char in xmm1

	mov	ecx,DWORD PTR 0 ; filler..

	ALIGN	16

loop_16:
	sub	eax,16
	movups	xmm0,[edi+eax]	; scan in reverse for char
	pcmpeqb xmm0,xmm1	; compare
	pmovmskb ecx,xmm0	; get result
	test	ecx,ecx
	jnz	exit_16
	cmp	eax,16
	jnb	loop_16
	xor	eax,eax
	movups	xmm0,[edi]
	pcmpeqb xmm0,xmm1
	pmovmskb ecx,xmm0
	test	ecx,ecx
	jz	exit_null

exit_16:
	bsr	ecx,ecx
	add	eax,ecx
exit_eax:
	add	eax,edi
	pop	edi
	ret	8

exit_if_null:
	;
	; If char is 0..
	;
	cmp	cl,[edi+eax]
	je	exit_eax

exit_null:
	xor	eax,eax
	pop	edi
	ret	8

exit_tail:
	cmp	cl,[edi+eax-1]
	je	exit_count
	dec	eax
	jnz	exit_tail
	pop	edi
	ret	8

exit_count:
	add	eax,edi
	dec	eax
	pop	edi
	ret	8

	ALIGN	16

strrchr_386:

	push	edi
	mov	edi,4[esp+4]
	xor	eax,eax
	mov	ecx,-1
	repne	scasb
	not	ecx
	dec	edi
	mov	al,4[esp+8]
	std
	repne	scasb
	cld
	mov	al,0
	jne	@F
	lea	eax,[edi+1]
@@:
	test	eax,eax
	pop	edi
	ret	8

	ALIGN	16

strrchr PROC string:LPSTR, char:SIZE_T
	jmp	strrchr_p
strrchr ENDP

	ALIGN	4
	;
	; First call: set pointer and jump
	;
_rtl_strrchr:
	mov	eax,strrchr_386
	.if	sselevel & SSE_SSE2
		mov eax,strrchr_SSE2
	.endif
	mov	strrchr_p,eax
	jmp	eax

endif

	END
