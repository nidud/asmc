include string.inc

	.code

wcsstr	PROC USES ebx esi edi s1:LPWSTR, s2:LPWSTR
	mov	edi,s1
	mov	esi,s2
	cmp	word ptr [esi],0
	je	strstr_nul
    strstr_lup:
	mov	cx,[esi]
     @@:
	mov	ax,[edi]
	test	ax,ax
	jz	strstr_nul
	add	edi,2
	cmp	ax,cx
	jne	@B
	mov	ebx,edi
	add	esi,2
     @@:
	mov	ax,[esi]
	test	ax,ax
	jz	@F
	cmp	[ebx],ax
	jne	@F
	add	esi,2
	add	ebx,2
	jmp	@B
     @@:
	mov	esi,s2
	jne	strstr_lup
	mov	eax,edi
	sub	eax,2
    strstr_end:
	ret
    strstr_nul:
	sub	eax,eax
	jmp	strstr_end
wcsstr	ENDP

	END
