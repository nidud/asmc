; CALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

calloc	PROC n, nsize
	mov	eax,ecx
	mul	edx
	malloc( eax )
	ret
calloc	ENDP

	END
