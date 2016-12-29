include string.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

_memicmp PROC s1:LPSTR, s2:LPSTR, l:SIZE_T

	push	esi
	push	edi
	mov	esi,8[esp+4]		; s1
	mov	edi,8[esp+8]		; s2
	mov	ecx,8[esp+12]		; l
@@:
	test	ecx,ecx
	jz	@F
	sub	ecx,1
	mov	al,[esi]
	cmp	al,[edi]
	lea	esi,[esi+1]
	lea	edi,[edi+1]
	je	@B
	mov	ah,[edi-1]
	sub	ax,'AA'
	cmp	al,'Z'-'A' + 1
	sbb	dl,dl
	and	dl,'a'-'A'
	cmp	ah,'Z'-'A' + 1
	sbb	dh,dh
	and	dh,'a'-'A'
	add	ax,dx
	add	ax,'AA'
	cmp	al,ah
	je	@B
	sbb	ecx,ecx
	sbb	ecx,-1
@@:
	mov	eax,ecx
	pop	edi
	pop	esi
	ret	12
_memicmp ENDP

	END
