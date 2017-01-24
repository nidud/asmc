include string.inc

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

ifndef __SSE__

	.code

streol	PROC string:LPSTR

	push	edx
	push	ebx

	mov	eax,8[esp+4]	; string

	ALIGN	4
@@:
	mov	edx,[eax]
	add	eax,4
	lea	ecx,[edx-01010101h]
	not	edx
	and	ecx,edx
	and	ecx,80808080h
	xor	edx,not 0A0A0A0Ah
	lea	ebx,[edx-01010101h]
	not	edx
	and	ebx,edx
	and	ebx,80808080h
	or	ecx,ebx
	jz	@B
@@:
	bsf	ecx,ecx
	shr	ecx,3
	lea	eax,[eax+ecx-4]
	pop	ebx

	cmp	eax,4[esp+4]	; string
	je	@F
	cmp	BYTE PTR [eax],0
	je	@F
	cmp	BYTE PTR [eax-1],0Dh
	jne	@F
	dec	eax
@@:
	pop	edx
	ret	4
streol	ENDP

else	; SSE2 - Auto install

include crtl.inc

	.data
	streol_p dd _rtl_streol

	.code

streol_SSE2:

	xorps	xmm0,xmm0	; zero * 16

	mov	eax,0A0A0A0Ah
	movd	xmm1,eax
	pshufd	xmm1,xmm1,0	; 16 dup('\n')

	mov	eax,[esp+4]	; string

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
	cmp	eax,[esp+4]	; string
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
	ret	4

streol_386:

	push	edx
	push	ebx

	mov	eax,8[esp+4]	; string

	ALIGN	4
@@:
	mov	edx,[eax]
	add	eax,4
	lea	ecx,[edx-01010101h]
	not	edx
	and	ecx,edx
	and	ecx,80808080h
	xor	edx,not 0A0A0A0Ah
	lea	ebx,[edx-01010101h]
	not	edx
	and	ebx,edx
	and	ebx,80808080h
	or	ecx,ebx
	jz	@B
@@:
	bsf	ecx,ecx
	shr	ecx,3
	lea	eax,[eax+ecx-4]
	pop	ebx
	pop	edx
	jmp	exit_eax

	ALIGN	16

streol	PROC string:LPSTR
	jmp	streol_p
streol	ENDP

	ALIGN	4
	;
	; First call: set pointer and jump
	;
_rtl_streol:
	mov	eax,streol_386
	.if	sselevel & SSE_SSE2
		mov eax,streol_SSE2
	.endif
	mov	streol_p,eax
	jmp	eax
endif

	END
