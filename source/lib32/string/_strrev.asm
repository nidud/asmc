; _STRREV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

	.code

_strrev PROC USES ecx esi edi string:LPSTR
	mov	esi,string
	mov	edi,esi
	xor	eax,eax
	mov	ecx,-1
	repnz	scasb
	cmp	ecx,-2
	je	toend
	sub	edi,2
	xchg	esi,edi
	cmp	edi,esi
	jae	toend
@@:
	mov	al,[edi]
	movsb
	mov	[esi-1],al
	sub	esi,2
	cmp	edi,esi
	jb	@B
toend:
	mov	eax,string
	ret
_strrev ENDP

	END
