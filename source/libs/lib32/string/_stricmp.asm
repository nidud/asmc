; _STRICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

	.code

_stricmp::

	push	esi
	push	edi
	mov	esi,[esp+12]
	mov	edi,[esp+16]
	mov	eax,1
@@:
	test	al,al
	jz	@F

	mov	al,[esi]
	mov	cl,[edi]
	inc	esi
	inc	edi
	cmp	al,cl
	je	@B

	mov	dl,al
	sub	al,'a'
	cmp	al,'Z'-'A'+1
	sbb	al,al
	and	al,'a'-'A'
	xor	al,dl

	mov	dl,cl
	sub	cl,'a'
	cmp	cl,'Z'-'A'+1
	sbb	cl,cl
	and	cl,'a'-'A'
	xor	cl,dl

	cmp	al,cl
	je	@B

	sbb	eax,eax
	sbb	eax,-1
@@:
	pop	edi
	pop	esi
	ret

	end

