
	.x64
	.model	flat
	.code
entry:
	push	rbp
	mov	rbp,rsp
	sub	rsp,32
	movaps	[rbp-16],xmm0
	movaps	[rbp-32],xmm1
	leave
	ret

	END
