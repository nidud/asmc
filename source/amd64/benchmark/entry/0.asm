
	.x64
	.model	flat
	.code
entry:
	enter	32,0
	movaps	[rbp-16],xmm0
	movaps	[rbp-32],xmm1
	leave
	ret

	END
