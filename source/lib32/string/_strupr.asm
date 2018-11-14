; _STRUPR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

	.code

_strupr PROC USES esi string:LPSTR
	mov	esi,string
@@:
	mov	al,[esi]
	test	al,al
	jz	@F
	sub	al,'a'
	cmp	al,'Z' - 'A' + 1
	sbb	al,al
	and	al,'a' - 'A'
	xor	[esi],al
	inc	esi
	jmp	@B
@@:
	mov	eax,string
	ret
_strupr ENDP

	END
