include string.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

strncpy PROC dst:LPSTR, src:LPSTR, count:SIZE_T

	push	rcx
	mov	r10,8080808080808080h
	mov	r11,0101010101010101h

	cmp	r8,8
	jb	tail

	mov	rax,[rdx]
	mov	r9,rax
	sub	r9,r11
	not	rax
	and	r9,rax
	and	r9,r10
	jnz	tail

	mov	rax,rcx		; align 8
	neg	rax
	and	rax,111B
	mov	r9,[rdx]	; copy the first 8 bytes
	mov	[rcx],r9
	add	rcx,rax		; add leading bytes
	add	rdx,rax		;
	sub	r8,rax
	jmp	start
lupe:
	sub	r8,8
	mov	rax,[rdx]	; copy 4 bytes
	mov	[rcx],rax
	add	rcx,8
	add	rdx,8
start:
	cmp	r8,4
	jb	tail
	mov	rax,[rdx]
	mov	r9,rax
	sub	r9,r11
	not	rax
	and	r9,rax
	and	r9,r10
	jz	lupe
tail:
	test	r8,r8
	jz	toend
@@:
	mov	al,[rdx]
	mov	[rcx],al
	dec	r8
	jz	toend
	inc	rcx
	inc	rdx
	test	al,al
	jnz	@B
	mov	rdx,rdi
	mov	rdi,rcx
	mov	rcx,r8
	rep	stosb
	mov	rdi,rdx
toend:
	pop	rax
	ret
strncpy ENDP

	END
