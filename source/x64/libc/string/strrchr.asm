include string.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

strrchr PROC string:LPSTR, char:SIZE_T

	push	rdi
	mov	rdi,rcx

	xor	rax,rax
	mov	rcx,-1
	repne	scasb
	not	rcx
	dec	rdi
	mov	al,dl
	std
	repne	scasb
	cld
	mov	al,0
	jne	@F
	lea	rax,[rdi+1]
@@:
	test	rax,rax
	pop	rdi
	ret

strrchr ENDP

	END
