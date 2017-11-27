include string.inc

	.code

wcscat PROC USES esi edi s1:LPWSTR, s2:LPWSTR
	xor	eax,eax
	mov	edi,s1
	mov	esi,s2
	mov	ecx,-1
	repne	scasw
	sub	edi,2
@@:
	mov	ax,[esi]
	mov	[edi],ax
	add	edi,2
	add	esi,2
	test	ax,ax
	jnz	@B
	mov	eax,s1
	ret
wcscat ENDP

	END
