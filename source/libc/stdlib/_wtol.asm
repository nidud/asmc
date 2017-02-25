include stdlib.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

_wtol	PROC string:LPWSTR

	mov	edx,[esp+4]
	xor	ecx,ecx
@@:
	movzx	eax,word ptr [edx]
	add	edx,2
	cmp	eax,' '
	je	@B
	push	eax
	cmp	eax,'-'
	je	@2
	cmp	eax,'+'
	jne	@F
@2:
	mov	ax,[edx]
	add	edx,2
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
	movzx	ecx,word ptr [edx]
	add	edx,2
	jmp	@B
@@:
	pop	ecx
	cmp	ecx,'-'
	jne	@F
	neg	eax
@@:
	ret	4
_wtol	ENDP

	END
