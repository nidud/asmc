include string.inc

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

ifndef __SSE__

	.code


strchr	PROC string:LPSTR, char:SIZE_T

	push	edi

	mov	edi,4[esp+4]
	movzx	ecx,BYTE PTR 4[esp+8]

	xor	eax,eax
@@:
	mov	al,[edi]
	test	eax,eax
	jz	toend

	inc	edi
	cmp	eax,ecx
	jne	@B

	mov	eax,edi
	dec	eax
toend:

	pop	edi
	ret	8

strchr	ENDP


else	; SSE2 - Auto install

include math.inc

	.data
	strchr_p dd _rtl_strchr

	.code

strchr_SSE2:

	push	edi

	mov	edi,4[esp+4]
	movzx	eax,BYTE PTR 4[esp+8]

	imul	eax,eax,01010101h
	movd	xmm1,eax
	pshufd	xmm1,xmm1,0		; populate char in xmm1
	pxor	xmm0,xmm0		; populate zero in xmm0

	mov	ecx,edi
	and	ecx,16-1		; unaligned bytes - 0..15
	jz	loop_16

	or	eax,-1			; the bytes in front need to be excluded
	shl	eax,cl			; EDX is used as a mask for these bytes
	sub	edi,ecx			; to avoid a read-ahead over a page boundary
	movaps	xmm2,[edi]		; the pointer is aligned back on the first read
	movaps	xmm3,xmm2		; copy to xmm3
	pcmpeqb xmm3,xmm1		; test the first 1..16 bytes
	pcmpeqb xmm2,xmm0		; check for zero
	pmaxub	xmm2,xmm3		; combine result
	pmovmskb ecx,xmm2		; get result bits
	add	edi,16
	and	ecx,eax			; remove bytes in front
	jnz	exit_16			; all done ?

	ALIGN	4
loop_16:
	movaps	xmm2,[edi]		; continue testing 16-byte blocks
	movaps	xmm3,xmm2
	pcmpeqb xmm3,xmm1
	pcmpeqb xmm2,xmm0
	pmaxub	xmm2,xmm3		; combine result
	pmovmskb ecx,xmm2
	add	edi,16
	test	ecx,ecx
	jz	loop_16
exit_16:
	bsf	ecx,ecx			; get index of byte
	lea	eax,[edi+ecx-16]	; address of result
	cmp	BYTE PTR [eax],1	; points to zero or char
	sbb	ecx,ecx			; if zero the CARRY flag is set
	not	ecx			; 0 or -1
	and	eax,ecx			; 0 or pointer
	pop	edi
	ret	8

	ALIGN	16

strchr_386:

	push	esi
	push	edi
	push	ebx

	movzx	eax,BYTE PTR 12[esp+8]
	imul	ebx,eax,01010101h
	mov	edi,12[esp+4]

	mov	eax,edi
	neg	eax
	and	eax,3
	jz	loop_4

	cmp	bl,[edi]
	je	exit_0
	cmp	ah,[edi]
	je	exit_NULL

	cmp	bl,[edi+1]
	je	exit_1
	cmp	ah,[edi+1]
	je	exit_NULL

	cmp	bl,[edi+2]
	je	exit_2
	cmp	ah,[edi+2]
	je	exit_NULL

	lea	edi,[edi+eax]

	ALIGN	4
loop_4:
	mov	esi,[edi]
	add	edi,4
	lea	ecx,[esi-01010101h]
	not	esi
	and	ecx,esi
	and	ecx,80808080h
	not	esi
	xor	esi,ebx
	lea	eax,[esi-01010101h]
	not	esi
	and	eax,esi
	and	eax,80808080h
	or	ecx,eax
	jz	loop_4
	bsf	ecx,ecx
	shr	ecx,3
	lea	eax,[ecx+edi-4]
	cmp	[eax],bl
	je	toend
exit_NULL:
	xor	eax,eax
	ALIGN	4
toend:
	test	eax,eax
	pop	ebx
	pop	edi
	pop	esi
	ret	8
exit_0:
	mov	eax,edi
	jmp	toend
exit_1:
	lea	eax,[edi+1]
	jmp	toend
exit_2:
	lea	eax,[edi+2]
	jmp	toend

	ALIGN	16

strchr	PROC string:LPSTR, char:SIZE_T
	jmp	strchr_p
strchr	ENDP

	ALIGN	4
	;
	; First call: set pointer and jump
	;
_rtl_strchr:
	mov	eax,strchr_386
	.if	sselevel & SSE_SSE2
		mov eax,strchr_SSE2
	.endif
	mov	strchr_p,eax
	jmp	eax

endif

	END
