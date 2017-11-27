include string.inc

	.code

wcslen	PROC USES edi string:LPWSTR
	sub	eax,eax
	mov	edi,string
	mov	ecx,-1
	repne	scasw
	not	ecx
	dec	ecx
	mov	eax,ecx
	ret
wcslen	ENDP

	END
