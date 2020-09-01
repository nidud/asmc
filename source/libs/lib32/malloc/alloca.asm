; ALLOCA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

	.code

	option stackbase:esp

alloca	PROC byte_count:UINT

	lea	eax,[esp+8]
	mov	ecx,[eax-4]	; size to probe

	.while	ecx > _PAGESIZE_

	    sub	 eax,_PAGESIZE_
	    test [eax],eax
	    sub	 ecx,_PAGESIZE_
	.endw

	sub	eax,ecx
	and	eax,-16		; align 16
	test	[eax-4],eax	; probe page
	mov	ecx,[esp]
	lea	esp,[eax-4]
	jmp	ecx

alloca	ENDP

	END
