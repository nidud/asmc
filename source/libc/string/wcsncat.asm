include string.inc

	.code

wcsncat PROC USES esi edi s1:LPWSTR, s2:LPWSTR, max:SIZE_T
	sub	eax,eax
	mov	edi,s1
	mov	esi,s2
	mov	ecx,-1
	repne	scasw
	sub	edi,2
	mov	ecx,max
@@:
	test	ecx,ecx
	jz	cxzero
	mov	ax,[esi]
	mov	[edi],ax
	add	edi,2
	add	esi,2
	sub	ecx,1
	test	eax,eax
	jnz	@B
toend:
	mov	eax,s1
	ret
cxzero:
	sub	eax,eax
	stosw
	jmp	toend
wcsncat ENDP

	END
