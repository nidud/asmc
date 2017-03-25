include string.inc
ifdef _SSE
include crtl.inc

	.data
	strchri_p dd _rtl_strchri
endif
	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

ifdef _SSE
strchri_386:
else
strchri PROC string:LPSTR, char:SIZE_T
endif
	push	esi

	mov	esi,4[esp+4]
	movzx	eax,byte ptr 4[esp+8]

	sub	al,'A'
	cmp	al,'Z'-'A'+1
	sbb	cl,cl
	and	cl,'a'-'A'
	add	cl,al
	add	cl,'A'
@@:
	mov	al,[esi]
	test	eax,eax
	jz	toend
	add	esi,1
	sub	al,'A'
	cmp	al,'Z'-'A'+1
	sbb	ch,ch
	and	ch,'a'-'A'
	add	al,ch
	add	al,'A'
	cmp	al,cl
	jne	@B
	mov	eax,esi
	dec	eax
toend:
	pop	esi
	ret	8

ifdef _SSE

	ALIGN	4

strchri PROC string:LPSTR, char:SIZE_T
	jmp	strchri_p
strchri ENDP
	;
	; First call: set pointer and jump
	;
_rtl_strchri:
	mov	eax,strchri_386
	.if	sselevel & SSE_SSE2
		mov eax,strchri_sse
	.endif
	mov	strchri_p,eax
	jmp	eax
else
strchri ENDP
endif
	END
