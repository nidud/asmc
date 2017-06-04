include string.inc
ifdef _SSE
include crtl.inc

	.data
	streol_p dd _rtl_streol
endif
	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

ifdef _SSE
streol_386:
else
streol	PROC string:LPSTR
endif

	push	edx
	push	ebx

	mov	eax,8[esp+4]	; string

	ALIGN	4
@@:
	mov	edx,[eax]
	add	eax,4
	lea	ecx,[edx-01010101h]
	not	edx
	and	ecx,edx
	and	ecx,80808080h
	xor	edx,not 0A0A0A0Ah
	lea	ebx,[edx-01010101h]
	not	edx
	and	ebx,edx
	and	ebx,80808080h
	or	ecx,ebx
	jz	@B
@@:
	bsf	ecx,ecx
	shr	ecx,3
	lea	eax,[eax+ecx-4]
	pop	ebx

	cmp	eax,4[esp+4]	; string
	je	@F
	cmp	BYTE PTR [eax],0
	je	@F
	cmp	BYTE PTR [eax-1],0Dh
	jne	@F
	dec	eax
@@:
	pop	edx
	ret	4

ifdef _SSE
	ALIGN	4

streol	PROC string:LPSTR
	jmp	streol_p
streol	ENDP
	;
	; First call: set pointer and jump
	;
_rtl_streol:
	mov eax,streol_386
	.if sselevel & SSE_SSE2

		mov eax,streol_sse
	.endif
	mov streol_p,eax
	jmp eax
else
streol	ENDP
endif
	END
