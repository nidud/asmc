include string.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

strncmp PROC s1:LPSTR, s2:LPSTR, count:SIZE_T

	xor	eax,eax
	test	r8,r8
	jz	toend
@@:
	mov	al,[rcx]
	cmp	al,[rdx]
	lea	rdx,[rdx+1]
	lea	rcx,[rcx+1]
	jne	@F
	test	al,al
	je	toend
	dec	r8
	jnz	@B
	xor	eax,eax
	jmp	toend
@@:
	sbb	rax,rax
	sbb	rax,-1
toend:
	ret
strncmp ENDP

	END
