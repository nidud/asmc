include string.inc
ifdef _SSE
include crtl.inc

	.data
	memstri_p dd _rtl_memstri
endif
	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

ifdef _SSE
memstri_386:
else
memstri PROC s1:LPSTR, l1:SIZE_T, s2:LPSTR, l2:SIZE_T
endif

	push	esi
	push	edi
	push	ebx
	push	edx

	mov	edi,16[esp+4]		; s1
	mov	ecx,16[esp+8]		; l1
	mov	esi,16[esp+12]		; s2

	mov	al,[esi]
	sub	al,'A'
	cmp	al,'Z'-'A'+1
	sbb	bl,bl
	and	bl,'a'-'A'
	add	bl,al
	add	bl,'A'
scan:
	test	ecx,ecx
	jz	nomatch
	dec	ecx
	mov	al,[edi]
	add	edi,1
	sub	al,'A'
	cmp	al,'Z'-'A'+1
	sbb	bh,bh
	and	bh,'a'-'A'
	add	al,bh
	add	al,'A'
	cmp	al,bl
	jne	scan
	mov	edx,16[esp+16]		; l2
	dec	edx
	jz	match
	cmp	ecx,edx
	jl	nomatch
compare:
	dec	edx
	jl	match
	mov	al,[esi+edx+1]
	cmp	al,[edi+edx]
	je	compare
	mov	ah,[edi+edx]
	sub	ax,'AA'
	cmp	al,'Z'-'A' + 1
	sbb	bh,bh
	and	bh,'a'-'A'
	add	al,bh
	cmp	ah,'Z'-'A' + 1
	sbb	bh,bh
	and	bh,'a'-'A'
	add	ah,bh
	add	ax,'AA'
	cmp	al,ah
	je	compare
	jmp	scan
nomatch:
	xor	eax,eax
	jmp	toend
match:
	mov	eax,edi
	dec	eax
toend:
	pop	edx
	pop	ebx
	pop	edi
	pop	esi
	ret	16

ifdef _SSE
	ALIGN	4
memstri PROC s1:LPSTR, l1:SIZE_T, s2:LPSTR, l2:SIZE_T
	jmp	memstri_p
memstri ENDP
	;
	; First call: set pointer and jump
	;
_rtl_memstri:
	mov eax,memstri_386
	.if sselevel & SSE_SSE2

		mov eax,memstri_sse
	.endif
	mov memstri_p,eax
	jmp eax
else
memstri ENDP
endif
	END
