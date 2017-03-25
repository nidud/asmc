include string.inc

ifdef __SSE__

	.code

option	stackbase:esp

memrchr_sse proc uses edi ebx base:LPSTR, char:SINT, bsize:SIZE_T

	mov	edi,base
	movzx	ebx,BYTE PTR char
	mov	eax,bsize
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
	jz	toend
exit_16:
	bsr	ecx,ecx
	add	eax,ecx
	add	eax,edi
toend:
	ret
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
	jmp	toend
	ALIGN	4
not_found:
	xor	eax,eax
	jmp	toend
memrchr_sse endp
endif
	END
