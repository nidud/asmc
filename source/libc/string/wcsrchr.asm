include string.inc

	.code

wcsrchr PROC USES edi s1:ptr wchar_t, wc:wchar_t
	mov	edi,s1
	sub	eax,eax
	mov	ecx,-1
	repne	scasw
	not	ecx
	sub	edi,2
	std
	mov	ax,word ptr wc
	repne	scasw
	mov	ax,0
	jne	@F
	mov	eax,edi
	inc	eax
      @@:
	cld
	test	eax,eax
	ret
wcsrchr ENDP

	END
