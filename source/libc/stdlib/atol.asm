include stdlib.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

atol	PROC string:LPSTR
	mov	edx,[esp+4]
	xor	ecx,ecx
@@:
	movzx	eax,byte ptr [edx]
	inc	edx
	cmp	eax,' '
	je	@B
	push	eax
	cmp	eax,'-'
	je	@2
	cmp	eax,'+'
	jne	@F
@2:
	mov	al,[edx]
	inc	edx
@@:
	mov	ecx,eax
	xor	eax,eax
@@:
	sub	ecx,'0'
	jb	@F
	cmp	ecx,9
	ja	@F
	lea	ecx,[eax*8+ecx]
	lea	eax,[eax*2+ecx]
	movzx	ecx,byte ptr [edx]
	inc	edx
	jmp	@B
@@:
	pop	ecx
	cmp	ecx,'-'
	jne	@F
	neg	eax
@@:
	ret
atol	ENDP

	END
