; _MEMICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

	.code

	option stackbase:esp

_memicmp proc uses esi edi s1:LPSTR, s2:LPSTR, l:SIZE_T

	mov	esi,s1
	mov	edi,s2
	mov	ecx,l
@@:
	test	ecx,ecx
	jz	@F
	sub	ecx,1
	mov	al,[esi]
	cmp	al,[edi]
	lea	esi,[esi+1]
	lea	edi,[edi+1]
	je	@B
	mov	ah,[edi-1]
	sub	ax,'AA'
	cmp	al,'Z'-'A' + 1
	sbb	dl,dl
	and	dl,'a'-'A'
	cmp	ah,'Z'-'A' + 1
	sbb	dh,dh
	and	dh,'a'-'A'
	add	ax,dx
	add	ax,'AA'
	cmp	al,ah
	je	@B
	sbb	ecx,ecx
	sbb	ecx,-1
@@:
	mov	eax,ecx
	ret

_memicmp ENDP

	END
