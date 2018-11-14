; _STRICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

	.code

	option stackbase:esp

_stricmp proc uses esi edi ecx dst:LPSTR, src:LPSTR
	mov	edi,dst
	mov	esi,src
	mov	eax,-1
	ALIGN	16
lupe:
	test	al,al
	jz	toend
	mov	al,[esi]
	cmp	al,[edi]
	lea	esi,[esi+1]
	lea	edi,[edi+1]
	je	lupe
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
	je	lupe
	sbb	al,al
	sbb	al,-1
toend:
	movsx	eax,al
	ret
_stricmp ENDP

	END
