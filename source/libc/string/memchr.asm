include string.inc

ifdef _SSE

include crtl.inc

	.data
	memchr_p dd _rtl_memchr
endif
	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

ifdef _SSE
memchr_386:
else
memchr	PROC base:LPSTR, char:SIZE_T, bsize:SIZE_T
endif

	push	esi
	push	edi
	push	ebx

	mov	edi,12[esp+4]
	mov	eax,12[esp+8]
	mov	ecx,12[esp+12]

	cmp	ecx,8
	jb	tail

	cmp	al,[edi]
	je	exit_0
	cmp	al,[edi+1]
	je	exit_1
	cmp	al,[edi+2]
	je	exit_2

	add	ecx,edi			; limit
	imul	esi,eax,01010101h	; populate char
	add	edi,3
	and	edi,-4			; align 4
	ALIGN	16
loop_4:
	cmp	edi,ecx
	jae	exit_NULL
	mov	ebx,[edi]
	add	edi,4
	xor	ebx,esi
	lea	eax,[ebx-01010101h]
	not	ebx
	and	eax,ebx
	and	eax,80808080h
	jz	loop_4
	bsf	eax,eax
	shr	eax,3
	lea	eax,[eax+edi-4]
	cmp	eax,ecx
	jb	toend
	jmp	exit_NULL
tail:
	test	ecx,ecx
	jz	exit_NULL
@@:
	cmp	al,[edi]
	je	exit_0
	add	edi,1
	sub	ecx,1
	jnz	@B
exit_NULL:
	xor	eax,eax
	pop	ebx
	pop	edi
	pop	esi
	ret	12
exit_2:
	add	edi,1
exit_1:
	add	edi,1
exit_0:
	mov	eax,edi
toend:
	pop	ebx
	pop	edi
	pop	esi
	ret	12

ifdef _SSE
memchr	PROC base:LPSTR, char:SIZE_T, bsize:SIZE_T
	jmp	memchr_p
memchr	ENDP
	;
	; First call: set pointer and jump
	;
_rtl_memchr:
	mov eax,memchr_386
	.if sselevel & SSE_SSE2

		mov eax,memchr_sse
	.endif

	mov memchr_p,eax
	jmp eax
else
memchr	ENDP
endif
	END
