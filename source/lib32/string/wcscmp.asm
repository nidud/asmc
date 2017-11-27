include string.inc

	.code

wcscmp	PROC USES esi edi s1:LPWSTR, s2:LPWSTR
	mov	esi,s2
	mov	edi,s1
	mov	al,-1
@@:
	test	ax,ax
	jz	@F
	mov	ax,[esi]
	add	esi,2
	mov	cx,[edi]
	add	edi,2
	cmp	cx,ax
	je	@B
	sbb	ax,ax
	sbb	ax,-1
@@:
	movsx	eax,ax
	ret
wcscmp ENDP

	END
