include string.inc

ifdef _SSE

include crtl.inc

	.data
	strncmp_p dd _rtl_strncmp
endif
	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

ifdef _SSE
strncmp_386:
else
strncmp PROC s1:LPSTR, s2:LPSTR, count:SIZE_T
endif
	push	esi
	push	edi
	push	edx

	mov	edi,12[esp+4]
	mov	esi,12[esp+8]
	mov	edx,12[esp+12]

	xor	eax,eax
	test	edx,edx
	jz	toend
@@:
	mov	al,[edi]
	cmp	al,[esi]
	lea	esi,[esi+1]
	lea	edi,[edi+1]
	jne	@F
	test	eax,eax
	je	toend
	dec	edx
	jnz	@B
	xor	eax,eax
	jmp	toend
@@:
	sbb	eax,eax
	sbb	eax,-1
toend:
	pop	edx
	pop	edi
	pop	esi
	ret	12

ifdef _SSE
	ALIGN	4

strncmp PROC s1:LPSTR, s2:LPSTR, n:SIZE_T
	jmp	strncmp_p
strncmp ENDP
	;
	; First call: set pointer and jump
	;
_rtl_strncmp:
	mov eax,strncmp_386
	.if sselevel & SSE_SSE2

		mov eax,strncmp_SSE2
	.endif
	mov strncmp_p,eax
	jmp eax
else
strncmp ENDP
endif

	END
