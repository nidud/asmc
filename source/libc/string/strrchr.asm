include string.inc

ifdef _SSE

include crtl.inc

	.data
	strrchr_p dd _rtl_strrchr
endif
	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

ifdef _SSE
strrchr_386:
else
strrchr PROC string:LPSTR, char:SIZE_T
endif

	push	edi
	mov	edi,4[esp+4]

	xor	eax,eax
	mov	ecx,-1
	repne	scasb
	not	ecx
	dec	edi
	mov	al,4[esp+8]
	std
	repne	scasb
	cld
	mov	al,0
	jne	@F
	lea	eax,[edi+1]
@@:
	test	eax,eax
	pop	edi
	ret	8

ifdef	_SSE
	ALIGN	4

strrchr PROC string:LPSTR, char:SIZE_T
	jmp	strrchr_p
strrchr ENDP
	;
	; First call: set pointer and jump
	;
_rtl_strrchr:
	mov eax,strrchr_386
	.if sselevel & SSE_SSE2

		mov eax,strrchr_sse
	.endif
	mov	strrchr_p,eax
	jmp	eax
else
strrchr endp
endif
	END
