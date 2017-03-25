include string.inc

ifdef __SSE__

	.code

option	stackbase:esp

memchr_sse proc base:LPSTR, char:SIZE_T, bsize:SIZE_T

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
toend:
	pop	edx
	pop	edi
	ret
fail:
	xor	eax,eax
	jmp	toend
memchr_sse endp
endif
	END
