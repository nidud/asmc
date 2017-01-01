include stdlib.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

_atoi64 PROC string:LPSTR

	xor	rax,rax
	xor	rdx,rdx
@@:
	mov	al,[rcx]
	inc	rcx
	cmp	al,' '
	je	@B

	mov	r8,rax

	cmp	al,'-'
	je	@2
	cmp	al,'+'
	jne	@F
@2:
	mov	al,[rcx]
	inc	rcx
@@:
	sub	al,'0'
	jc	@F
	cmp	al,9
	ja	@F

	shl	rdx,3
	add	rdx,rax
	mov	al,[rcx]
	inc	rcx
	jmp	@B
@@:

	cmp	r8b,'-'
	jne	@F
	neg	rdx
@@:
	mov	rax,rdx
	ret
_atoi64 ENDP

	END
