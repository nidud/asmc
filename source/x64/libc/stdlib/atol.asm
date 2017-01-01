include stdlib.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

atol	PROC string:LPSTR

	xor	r8,r8
@@:
	movzx	rax,byte ptr [rcx]
	inc	rcx
	cmp	al,' '
	je	@B

	mov	r9,rax

	cmp	al,'-'
	je	@2
	cmp	al,'+'
	jne	@F
@2:
	mov	al,[rcx]
	inc	rcx
@@:
	sub	al,'0'
	jb	@F
	cmp	al,9
	ja	@F
	lea	rax,[r8*8+rax]
	lea	r8,[r8*2+rax]
	movzx	rax,byte ptr [rcx]
	inc	rcx
	jmp	@B
@@:
	cmp	r9b,'-'
	jne	@F
	neg	r8
@@:
	mov	rax,r8
	ret
atol	ENDP

	END
