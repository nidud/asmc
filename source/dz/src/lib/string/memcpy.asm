include string.inc
ifdef _SSE
include crtl.inc

	.data
	memcpy_p dd _rtl_memcpy
endif
	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

ifdef _SSE
memcpy_386:
else
memmove PROC dst:LPSTR, src:LPSTR, count:SIZE_T
memmove ENDP
memcpy	proc dst:LPSTR, src:LPSTR, count:SIZE_T
endif
	push	esi
	push	edi
	mov	eax,8[esp+4]	; dst -- return value
	mov	esi,8[esp+8]	; src
	mov	ecx,8[esp+12]	; count

	mov	edi,eax
	cmp	eax,esi
	ja	@F
	rep	movsb
	pop	edi
	pop	esi
	ret	12
@@:
	lea	esi,[esi+ecx-1]
	lea	edi,[edi+ecx-1]
	std
	rep	movsb
	cld
	pop	edi
	pop	esi
	ret	12

ifdef _SSE
memmove PROC dst:LPSTR, src:LPSTR, count:SIZE_T
memmove ENDP
memcpy	PROC base:LPSTR, char:SIZE_T, bsize:SIZE_T
	jmp	memcpy_p
memcpy	ENDP
	;
	; First call: set pointer and jump
	;
_rtl_memcpy:
	mov eax,memcpy_386
	.if sselevel & SSE_SSE2

		mov eax,memcpy_sse
	.endif

	mov memcpy_p,eax
	jmp eax
else
memcpy	ENDP
endif
	END
