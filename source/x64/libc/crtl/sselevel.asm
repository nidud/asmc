include io.inc
include consx.inc
include stdlib.inc
include crtl.inc

PUBLIC	sselevel

	.data
	sselevel dd 0

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

GetSSELevel PROC

	pushfq
	pop	rax
	mov	rcx,200000h
	mov	rdx,rax
	xor	rax,rcx
	push	rax
	popfq
	pushfq
	pop	rax
	xor	rax,rdx
	and	rax,rcx
	push	rbx

	.if	!ZERO?
		xor	rax,rax
		cpuid
		.if	rax
			.if	ah == 5
				xor	rax,rax
			.else
				mov	eax,7
				xor	ecx, ecx
				cpuid			; check AVX2 support
				xor	eax,eax
				bt	ebx,5		; AVX2
				rcl	eax,1		; into bit 9
				push	rax
				mov	eax,1
				cpuid
				pop	rax
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
	push	rax
	xor	rcx,rcx
	xgetbv
	and	eax,6		; AVX support by OS?
	pop	rax
	jz	@F
	or	eax,SSE_AVXOS
@@:
	pop	rbx
	mov	sselevel,eax
	test	eax,SSE_SSE2
	jnz	@F
	and	console,not CON_SIMDE
@@:
	ret
GetSSELevel ENDP

pragma_init GetSSELevel,3

	END
