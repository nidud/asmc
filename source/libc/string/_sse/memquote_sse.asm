include string.inc

ifdef __SSE__

	.code

option	stackbase:esp

memquote_sse proc uses ebx edx string:LPSTR, bsize:SIZE_T

	mov	eax,'""""'
	movd	xmm2,eax
	mov	eax,"''''"
	movd	xmm3,eax
	pshufd	xmm2,xmm2,0	; 16 dup('"')
	pshufd	xmm3,xmm3,0	; 16 dup("'")

	mov	eax,string	; string
	mov	ebx,bsize	; len
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

	mov	eax,string	; align pointer
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
toend:
	ret
noquote:
	xor	eax,eax
	jmp	toend
memquote_sse endp
endif
	END
