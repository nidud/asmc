; CALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

	.code

calloc	PROC n, nsize
	mov eax,n
	mul nsize
	malloc(eax)
	ret
calloc	ENDP

	END
