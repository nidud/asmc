include crtl.inc
include dzlib.inc

PUBLIC	sselevel

	.data
	sselevel dd 0

	.code
	.686
	.xmm

GetSSELevel PROC
	pushfd
	pop	eax
	mov	ecx,200000h
	mov	edx,eax
	xor	eax,ecx
	push	eax
	popfd
	pushfd
	pop	eax
	xor	eax,edx
	and	eax,ecx
	push	ebx
	.if	!ZERO?
		xor	eax,eax
		cpuid
		.if	eax
			.if	ah == 5
				xor	eax,eax
			.else
				mov	eax,7
				xor	ecx, ecx
				cpuid			; check AVX2 support
				xor	eax,eax
				bt	ebx,5		; AVX2
				rcl	eax,1		; into bit 9
				push	eax
				mov	eax,1
				cpuid
				pop	eax
				bt	ecx,28		; AVX support by CPU
				rcl	eax,1		; into bit 8
				bt	ecx,27		; XGETBV supported
				rcl	eax,1		; into bit 7
				bt	ecx,20		; SSE4.2
				rcl	eax,1		; into bit 6
				bt	ecx,19		; SSE4.1
				rcl	eax,1		; into bit 5
				bt	ecx,9		; SSSE3
				rcl	eax,1		; into bit 4
				bt	ecx,0		; SSE3
				rcl	eax,1		; into bit 3
				bt	edx,26		; SSE2
				rcl	eax,1		; into bit 2
				bt	edx,25		; SSE
				rcl	eax,1		; into bit 1
				bt	ecx,0		; MMX
				rcl	eax,1		; into bit 0
			.endif
		.endif
	.endif
	test	eax,SSE_XGETBV
	jz	@F
	push	eax
	xor	ecx,ecx
	xgetbv
	and	eax,6		; AVX support by OS?
	pop	eax
	jz	@F
	or	eax,SSE_AVXOS
@@:
	pop	ebx
	mov	sselevel,eax
	ret
GetSSELevel ENDP

pragma_init GetSSELevel,3

	END
