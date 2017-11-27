include string.inc

	.code

_wcsnicmp proc uses esi edi ebx s1:LPWSTR, s2:LPWSTR, count:SIZE_T
	mov edi,s1
	mov esi,s2
	mov edx,count
	mov ax,-1
@@:
	test	ax,ax
	jz	@F
	xor	eax,eax
	test	edx,edx
	jz	toend
	mov	ax,[esi]
	cmp	ax,[edi]
	lea	esi,[esi+2]
	lea	edi,[edi+2]
	lea	edx,[edx-1]
	je	@B
	mov	bx,[edi-2]
	sub	ax,'A'
	cmp	ax,'Z'-'A'+1
	sbb	ecx,ecx
	and	ecx,'a'-'A'
	add	ax,cx
	add	ax,'A'
	sub	bx,'A'
	cmp	bx,'Z'-'A'+1
	sbb	ecx,ecx
	and	ecx,'a'-'A'
	add	bx,cx
	add	bx,'A'
	cmp	bx,ax
	je	@B
	sbb	ax,ax
	sbb	ax,-1
@@:
	movsx	eax,ax
toend:
	ret
_wcsnicmp ENDP

	END
