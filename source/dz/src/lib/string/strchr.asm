include string.inc
ifdef _SSE
include crtl.inc

	.data
	strchr_p dd _rtl_strchr
endif
	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

ifdef _SSE
strchr_386:
else
strchr	PROC string:LPSTR, char:SIZE_T
endif

	push	esi
	push	edi
	push	ebx

	movzx	eax,BYTE PTR 12[esp+8]
	imul	ebx,eax,01010101h
	mov	edi,12[esp+4]

	mov	eax,edi
	neg	eax
	and	eax,3
	jz	loop_4

	cmp	bl,[edi]
	je	exit_0
	cmp	ah,[edi]
	je	exit_NULL

	cmp	bl,[edi+1]
	je	exit_1
	cmp	ah,[edi+1]
	je	exit_NULL

	cmp	bl,[edi+2]
	je	exit_2
	cmp	ah,[edi+2]
	je	exit_NULL

	lea	edi,[edi+eax]

	ALIGN	4
loop_4:
	mov	esi,[edi]
	add	edi,4
	lea	ecx,[esi-01010101h]
	not	esi
	and	ecx,esi
	and	ecx,80808080h
	not	esi
	xor	esi,ebx
	lea	eax,[esi-01010101h]
	not	esi
	and	eax,esi
	and	eax,80808080h
	or	ecx,eax
	jz	loop_4
	bsf	ecx,ecx
	shr	ecx,3
	lea	eax,[ecx+edi-4]
	cmp	[eax],bl
	je	toend
exit_NULL:
	xor	eax,eax
	ALIGN	4
toend:
	test	eax,eax
	pop	ebx
	pop	edi
	pop	esi
	ret	8
exit_0:
	mov	eax,edi
	jmp	toend
exit_1:
	lea	eax,[edi+1]
	jmp	toend
exit_2:
	lea	eax,[edi+2]
	jmp	toend

ifdef _SSE
strchr	PROC string:LPSTR, char:SIZE_T
	jmp	memrchr_p
strchr	ENDP
	;
	; First call: set pointer and jump
	;
_rtl_strchr:
	mov eax,strchr_386
	.if sselevel & SSE_SSE2

		mov eax,strchr_sse
	.endif
	mov strchr_p,eax
	jmp eax
else
strchr	ENDP
endif
	END
