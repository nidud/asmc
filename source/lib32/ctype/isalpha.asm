; ISALPHA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

	.code

	option stackbase:esp

isalpha PROC char:SINT
	movzx	eax,BYTE PTR [esp+4]
	mov	al,BYTE PTR _ctype[eax*2+2]
	and	eax,_UPPER or _LOWER
	ret
isalpha ENDP

	END

