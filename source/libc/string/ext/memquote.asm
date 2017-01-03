include string.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

ifndef __SSE__

memquote PROC string:LPSTR, bsize:SIZE_T
memquote ENDP

else	; SSE2 - Auto install

include crtl.inc

	.data
	memquote_p dd _rtl_memquote

	.code

memquote_SSE2:

	push	ebx
	push	edx

	mov	eax,'""""'
	movd	xmm2,eax
	mov	eax,"''''"
	movd	xmm3,eax
	pshufd	xmm2,xmm2,0	; 16 dup('"')
	pshufd	xmm3,xmm3,0	; 16 dup("'")

	mov	eax,8[esp+4]	; string
	mov	ebx,8[esp+8]	; len
	add	ebx,eax

	test	eax,1111b
	jz	loop_16

	mov	ecx,eax		; seek back and test 16 bytes
	and	ecx,16-1	; create mask
	and	eax,-16
	movaps	xmm0,[eax]
	movaps	xmm1,xmm0	;
	pcmpeqb xmm1,xmm2	; " ?
	pmovmskb eax,xmm1
	pcmpeqb xmm0,xmm3	; ' ?
	pmovmskb edx,xmm0
	or	eax,edx

	or	edx,-1
	shl	edx,cl
	and	eax,edx
	mov	ecx,eax		; mask to ECX

	mov	eax,8[esp+4]	; align pointer
	and	eax,-16
	add	eax,16
	test	ecx,ecx
	jnz	exit_16

	ALIGN	4
loop_16:
	cmp	eax,ebx
	jae	noquote
	movaps	xmm0,[eax]
	movaps	xmm1,xmm0	; find quotes
	pcmpeqb xmm1,xmm2	; " ?
	pmovmskb ecx,xmm1
	movaps	xmm1,xmm0
	pcmpeqb xmm1,xmm3	; ' ?
	pmovmskb edx,xmm1
	or	ecx,edx
	lea	eax,[eax+16]
	jz	loop_16

exit_16:
	bsf	ecx,ecx
	lea	eax,[eax+ecx-16]
	cmp	eax,ebx
	sbb	ecx,ecx
	and	eax,ecx
	pop	edx
	pop	ebx
	ret	8

noquote:
	xor	eax,eax
	pop	edx
	pop	ebx
	ret	8

	ALIGN	16

memquote PROC string:LPSTR, len:SIZE_T
	jmp	memquote_p
memquote ENDP

	ALIGN	4
	;
	; First call: set pointer and jump
	;
_rtl_memquote:
	mov	eax,memquote_386
	.if	sselevel & SSE_SSE2
		mov eax,memquote_SSE2
	.endif
	mov	memquote_p,eax
	jmp	eax

	ALIGN	4

memquote_386:

endif

	push	edi
	push	ebx
	push	edx

	mov	eax,12[esp+4]	; string
	mov	ebx,12[esp+8]	; len

	test	ebx,ebx
	jz	failed

	test	eax,3
	jz	align_4

	mov	ecx,2227h

	cmp	[eax],cl
	je	exit_0
	cmp	[eax],ch
	je	exit_0
	cmp	ebx,1
	jz	failed

	cmp	[eax+1],cl
	je	exit_1
	cmp	[eax+1],ch
	je	exit_1
	cmp	ebx,2
	jz	failed

	cmp	[eax+2],cl
	je	exit_2
	cmp	[eax+2],ch
	je	exit_2
	cmp	ebx,3
	jz	failed

align_4:
	add	ebx,eax
	add	eax,3
	and	eax,-4

	ALIGN	4

loop_4:
	cmp	eax,ebx
	jae	failed

	mov	edx,[eax]
	mov	edi,edx
	add	eax,4
	xor	edx,'""""'
	xor	edi,"''''"
	lea	ecx,[edx-01010101h]
	not	edx
	and	ecx,edx
	lea	edx,[edi-01010101h]
	not	edi
	and	edx,edi
	and	ecx,80808080h
	and	edx,80808080h
	or	ecx,edx
	jz	loop_4
	bsf	ecx,ecx
	shr	ecx,3
	lea	eax,[eax+ecx-4]
	cmp	eax,ebx
	sbb	ecx,ecx
	and	eax,ecx
	pop	edx
	pop	ebx
	pop	edi
	ret	8
failed:
	xor	eax,eax
	pop	edx
	pop	ebx
	pop	edi
	ret	8
exit_2:
	inc	eax
exit_1:
	inc	eax
exit_0:
	test	eax,eax
	pop	edx
	pop	ebx
	pop	edi
	ret	8

	END
