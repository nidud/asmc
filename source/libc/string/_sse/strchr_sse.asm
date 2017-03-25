include string.inc

ifdef __SSE__

	.code

option	stackbase:esp

strchr_sse proc uses edi string:LPSTR, char:SINT

	mov	edi,string
	movzx	eax,BYTE PTR char

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
	ret

strchr_sse endp
endif
	END
