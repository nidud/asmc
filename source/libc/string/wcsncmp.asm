include string.inc

	.code

wcsncmp PROC USES esi edi edx s1:LPWSTR, s2:LPWSTR, count:SIZE_T
	mov	ecx,count
	test	ecx,ecx
	jz	toend
	mov	edx,ecx
	mov	edi,s1
	mov	esi,edi
	sub	eax,eax
	repne	scasw
	neg	ecx
	add	ecx,edx
	mov	edi,esi
	mov	esi,s2
	repe	cmpsw
	mov	ax,[esi-2]
	sub	ecx,ecx
	cmp	ax,[edi-2]
	ja	@F
	je	toend
	sub	ecx,2
@@:
	not	ecx
toend:
	mov	eax,ecx
	ret
wcsncmp ENDP

	END
