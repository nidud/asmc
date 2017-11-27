include string.inc

	.code

wcsncpy PROC USES esi edi s1:LPWSTR, s2:LPWSTR, count:SIZE_T
	mov	esi,s2
	mov	edi,s1
	sub	eax,eax
	mov	ecx,count
	test	ecx,ecx
	jz	toend
@@:
	mov	ax,[esi]
	mov	[edi],ax
	add	edi,2
	add	esi,2
	dec	ecx
	jz	toend
	test	ax,ax
	jnz	@B
	sub	edi,2
toend:
	mov	word ptr [edi],0
	mov	eax,s1
	ret
wcsncpy ENDP

	END
