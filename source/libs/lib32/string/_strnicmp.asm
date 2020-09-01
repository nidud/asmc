; _STRNICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

	.code

	option stackbase:esp

_strnicmp PROC s1:LPSTR, s2:LPSTR, count:SIZE_T
	mov	eax,esp
	push	esi
	push	edi
	push	edx
	mov	edi,[eax+4]
	mov	esi,[eax+8]
	mov	edx,[eax+12]
	mov	al,-1
	ALIGN	16
@@:
	test	al,al
	jz	@F
	xor	eax,eax
	test	edx,edx
	jz	toend
	mov	al,[esi]
	cmp	al,[edi]
	lea	esi,[esi+1]
	lea	edi,[edi+1]
	lea	edx,[edx-1]
	je	@B
	mov	ah,[edi-1]
	sub	ax,'AA'
	cmp	al,'Z'-'A'+1
	sbb	cl,cl
	and	cl,'a'-'A'
	cmp	ah,'Z'-'A'+1
	sbb	ch,ch
	and	ch,'a'-'A'
	add	ax,cx
	add	ax,'AA'
	cmp	ah,al
	je	@B
	sbb	al,al
	sbb	al,-1
@@:
	movsx	eax,al
toend:
	pop	edx
	pop	edi
	pop	esi
	ret
_strnicmp ENDP

	END
