; TOUPPER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

	.code

	option stackbase:esp

toupper PROC char:SINT
	mov	eax,[esp+4]
	sub	al,'a'
	cmp	al,'z'-'a'+1
	sbb	ah,ah
	and	ah,'a'-'A'
	sub	al,ah
	add	al,'a'
	and	eax,000000FFh
	ret
toupper ENDP

	END

