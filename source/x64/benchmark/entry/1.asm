
	.x64
	.model	flat
	.code
entry:
	sub	rsp,16*2 + 8
	movaps	[rsp+0],xmm0
	movaps	[rsp+16],xmm1
	add	rsp,16*2 + 8
	ret

	END
