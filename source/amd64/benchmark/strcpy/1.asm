
	.x64
	.model	flat

	.code

	mov	r8,rsi
	mov	r9,rdi
	mov	r10,rcx
	xor	rax,rax
	mov	rcx,-1
	mov	rdi,rdx
	repnz	scasb
	mov	rdi,r10
	mov	rsi,rdx
	mov	rax,rdi
	not	rcx
	rep	movsb
	mov	rsi,r8
	mov	rdi,r9
	ret

	END
