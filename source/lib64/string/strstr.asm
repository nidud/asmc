include string.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

strstr	PROC dst:LPSTR, src:LPSTR

	push	rdi
	mov	rdi,rcx

	strlen( rdx )
	jz	nomatch

	mov	r10,rax
	strlen( rdi )
	jz	nomatch

	mov	rcx,rax
	dec	r10
scan:
	mov	al,[rdx]
	repne	scasb
	jne	nomatch
	test	r10,r10
	jz	match
	cmp	rcx,r10
	jb	nomatch
	mov	r11,r10
compare:
	mov	al,[rdx+r11]
	cmp	al,[rdi+r11-1]
	jne	scan
	dec	r11
	jnz	compare
match:
	mov	rax,rdi
	dec	rax
	jmp	toend
nomatch:
	xor	rax,rax
toend:
	pop	rdi
	ret
strstr	ENDP

	END
