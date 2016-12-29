include string.inc

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

ifndef __SSE__

	.code

memchr	PROC base:LPSTR, char:SIZE_T, bsize:SIZE_T

	push	edi
	mov	edi,4[esp+4]	; base
	mov	eax,4[esp+8]	; char
	mov	ecx,4[esp+12]	; buffer size
	test	edi,edi		; clear ZERO flag case ecx is zero
	repnz	scasb
	jnz	@F
	mov	eax,edi		; clear ZERO flag if found..
	dec	eax
	pop	edi
	ret	12
@@:
	xor	eax,eax
	pop	edi
	ret	12

memchr	ENDP

else	; SSE2 - Auto install

include math.inc

	.data
	memchr_p dd _rtl_memchr

	.code

memchr_SSE2:

	mov	eax,esp			; align 16..

	push	edi
	push	edx

	mov	edi,[eax+4]		; base
	mov	ecx,[eax+12]		; buffer size
	mov	eax,[eax+8]		; char

	lea	edx,[edi+ecx]		; pointer (limit)

	imul	eax,eax,01010101h
	movd	xmm1,eax
	pshufd	xmm1,xmm1,0		; populate char in xmm1

	mov	ecx,edi
	mov	eax,ecx
	and	ecx,32-1		; unaligned bytes - 0..15
	and	eax,-32			; align EDI 16

	movaps	xmm0,[eax]		; load 16 bytes
	or	edi,-1			; create mask
	shl	edi,cl
	pcmpeqb xmm0,xmm1		; check for char
	pmovmskb ecx,xmm0
	and	ecx,edi			; remove bytes in front
	jnz	done

	movaps	xmm0,[eax+16]		;
	pcmpeqb xmm0,xmm1		;
	pmovmskb ecx,xmm0
	shl	ecx,16
	and	ecx,edi			;
	jnz	done

	ALIGN	16
scan:
	add	eax,32
	cmp	eax,edx
	jae	fail

	movdqa	xmm0,[eax]
	pcmpeqb xmm0,xmm1
	pmovmskb edi,xmm0

	movdqa	xmm0,[eax+16]
	pcmpeqb xmm0,xmm1
	pmovmskb ecx,xmm0

	shl	ecx,16
	or	ecx,edi
	jz	scan

done:
	bsf	ecx,ecx
	add	eax,ecx
	cmp	eax,edx
	sbb	ecx,ecx
	and	eax,ecx
	pop	edx
	pop	edi
	ret	12
fail:
	xor	eax,eax
	pop	edx
	pop	edi
	ret	12

	ALIGN	16

memchr_386:

	push	esi
	push	edi
	push	ebx

	mov	edi,12[esp+4]
	mov	eax,12[esp+8]
	mov	ecx,12[esp+12]

	cmp	ecx,8
	jb	tail

	cmp	al,[edi]
	je	exit_0
	cmp	al,[edi+1]
	je	exit_1
	cmp	al,[edi+2]
	je	exit_2

	add	ecx,edi			; limit
	imul	esi,eax,01010101h	; populate char
	add	edi,3
	and	edi,-4			; align 4
	ALIGN	16
loop_4:
	cmp	edi,ecx
	jae	exit_NULL
	mov	ebx,[edi]
	add	edi,4
	xor	ebx,esi
	lea	eax,[ebx-01010101h]
	not	ebx
	and	eax,ebx
	and	eax,80808080h
	jz	loop_4
	bsf	eax,eax
	shr	eax,3
	lea	eax,[eax+edi-4]
	cmp	eax,ecx
	jb	toend
	jmp	exit_NULL
tail:
	test	ecx,ecx
	jz	exit_NULL
@@:
	cmp	al,[edi]
	je	exit_0
	add	edi,1
	sub	ecx,1
	jnz	@B
exit_NULL:
	xor	eax,eax
	pop	ebx
	pop	edi
	pop	esi
	ret	12
exit_2:
	add	edi,1
exit_1:
	add	edi,1
exit_0:
	mov	eax,edi
toend:
	pop	ebx
	pop	edi
	pop	esi
	ret	12

	ALIGN	16

memchr	PROC base:LPSTR, char:SIZE_T, bsize:SIZE_T
	jmp	memchr_p
memchr	ENDP

	ALIGN	4
	;
	; First call: set pointer and jump
	;
_rtl_memchr:
	mov	eax,memchr_386
	.if	sselevel & SSE_SSE2
		mov eax,memchr_SSE2
	.endif
	mov	memchr_p,eax
	jmp	eax

endif

	END
