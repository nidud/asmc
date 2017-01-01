include string.inc

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

	.code

memchr	PROC base:LPSTR, char:SIZE_T, bsize:SIZE_T

	push	rdi
	mov	rdi,rcx		; base
	mov	rax,rdx		; char
	mov	rcx,r8		; buffer size
	test	rdi,rdi		; clear ZERO flag case ecx is zero
	repnz	scasb
	jnz	@F
	mov	rax,rdi		; clear ZERO flag if found..
	dec	rax
	pop	rdi
	ret
@@:
	xor	rax,rax
	pop	rdi
	ret

memchr	ENDP

	END
