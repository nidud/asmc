; MEMCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

	.code

memcmp	PROC USES esi edi s1:ptr, s2:ptr, len:SIZE_T
	mov	edi,s1
	mov	esi,s2
	mov	ecx,len
	xor	eax,eax
	repe	cmpsb
	je	@F
	sbb	eax,eax
	sbb	eax,-1
@@:
	ret
memcmp	ENDP

	END
