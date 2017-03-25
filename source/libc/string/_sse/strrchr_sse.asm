include string.inc

ifdef __SSE__

	.code

	option	stackbase:esp

strrchr_sse proc uses edi string:LPSTR, char:SINT

	mov	edi,string
	strlen( edi )
	movzx	ecx,byte ptr char

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
toend:
	ret

exit_if_null:
	;
	; If char is 0..
	;
	cmp	cl,[edi+eax]
	je	exit_eax

exit_null:
	xor	eax,eax
	jmp	toend

exit_tail:
	cmp	cl,[edi+eax-1]
	je	exit_count
	dec	eax
	jnz	exit_tail
	jmp	toend

exit_count:
	add	eax,edi
	dec	eax
	jmp	toend
strrchr_sse endp
endif
	END
