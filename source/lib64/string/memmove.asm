include string.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

memmove PROC dst:LPSTR, src:LPSTR, count:SIZE_T
	push	rsi
	push	rdi
	mov	rax,rcx		; dst -- return value
	mov	rsi,rdx		; src
	mov	rcx,r8		; count
	mov	rdi,rax
	cmp	rax,rsi
	ja	@F
	rep	movsb
	pop	rdi
	pop	rsi
	ret
@@:
	lea	rsi,[rsi+rcx-1]
	lea	rdi,[rdi+rcx-1]
	std
	rep	movsb
	cld
	pop	rdi
	pop	rsi
	ret
memmove ENDP

	END
