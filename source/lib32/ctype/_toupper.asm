; _TOUPPER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

	.code

	option stackbase:esp

_toupper PROC char:SINT

	movzx	eax,BYTE PTR [esp+4]
	sub	al,'a'-'A'
	ret

_toupper ENDP

	END

