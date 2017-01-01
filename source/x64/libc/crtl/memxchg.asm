include string.inc

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

	.code

memxchg PROC dst:LPSTR, src:LPSTR, count:SIZE_T

	mov	r9,rcx
	mov	r10,rdx
	mov	rcx,r8
tail:
	test	rcx,rcx
	jz	toend
	test	rcx,3
	jz	tail_4

	sub	rcx,1
	mov	al,[r10+rcx]
	mov	dl,[r9+rcx]
	mov	[r10+rcx],dl
	mov	[r9+rcx],al
	jmp	tail

tail_4:
	sub	rcx,4
	mov	eax,[r10+rcx]
	mov	edx,[r9+rcx]
	mov	[r10+rcx],edx
	mov	[r9+rcx],eax
	jnz	tail_4
toend:
	mov	rax,r9
	ret

memxchg ENDP

	END
