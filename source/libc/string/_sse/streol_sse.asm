include string.inc

ifdef __SSE__

	.code

	option	stackbase:esp

streol_sse proc string:LPSTR

	xorps	xmm0,xmm0	; zero * 16
	mov	eax,0A0A0A0Ah
	movd	xmm1,eax
	pshufd	xmm1,xmm1,0	; 16 dup('\n')
	mov	eax,string	; string

	mov	ecx,eax		; aligned 16 ?
	and	ecx,16-1
	jz	loop_16

	push	edx
	or	edx,-1		; create skip-mask
	shl	edx,cl
	sub	eax,ecx		; align 16 <--

	movaps	xmm2,[eax]
	movaps	xmm3,xmm2	; find end of line
	pcmpeqb xmm2,xmm1	; \n ?
	pcmpeqb xmm3,xmm0	; \0 ?
	pmaxub	xmm2,xmm3	; combine result
	pmovmskb ecx,xmm2
	add	eax,16
	and	ecx,edx		; test result
	pop	edx
	jnz	exit_16
	ALIGN	4
loop_16:
	movaps	xmm2,[eax]
	movaps	xmm3,xmm2	; find end of line
	pcmpeqb xmm2,xmm1	; \n ?
	pcmpeqb xmm3,xmm0	; \0 ?
	pmaxub	xmm2,xmm3	; combine result
	pmovmskb ecx,xmm2
	test	ecx,ecx
	lea	eax,[eax+16]
	jz	loop_16
exit_16:
	bsf	ecx,ecx
	lea	eax,[eax+ecx-16]
exit_eax:
	cmp	eax,string
	je	toend
	cmp	BYTE PTR [eax],0
	je	toend
	;
	; Clear ZERO if \r or \n
	;
	cmp	BYTE PTR [eax-1],0Dh
	jne	toend
	dec	eax
toend:
	ret
streol_sse endp
endif
	END
