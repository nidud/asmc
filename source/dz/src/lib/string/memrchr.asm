include string.inc
ifdef _SSE
include crtl.inc

	.data
	memrchr_p dd _rtl_memrchr
endif
	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

ifdef _SSE
memrchr_386:
else
memrchr PROC base:LPSTR, char:SIZE_T, bsize:SIZE_T
endif

	push	edi
	mov	edi,4[esp+4]
	mov	al, 4[esp+8]
	mov	ecx,4[esp+12]
	test	ecx,ecx
	jz	@F
	lea	edi,[edi+ecx-1]
	std
	repnz	scasb
	cld
	jnz	@F
	mov	eax,edi
	inc	eax
	pop	edi
	ret	12
@@:
	xor	eax,eax
	pop	edi
	ret	12

ifdef _SSE
memrchr PROC base:LPSTR, char:SIZE_T, bsize:SIZE_T
	jmp	memrchr_p
memrchr ENDP
	;
	; First call: set pointer and jump
	;
_rtl_strlen:
	mov	eax,memrchr_386
	.if	sselevel & SSE_SSE2
		mov eax,memrchr_sse
	.endif
	mov	memrchr_p,eax
	jmp	eax
else
memrchr ENDP
endif

	END
