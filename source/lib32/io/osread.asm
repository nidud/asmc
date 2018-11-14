; OSREAD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include winbase.inc

	.code

osread	PROC h:SINT, b:PVOID, z:SIZE_T
	push	eax
	mov	edx,esp
	mov	eax,h
	mov	eax,_osfhnd[eax*4]
	ReadFile( eax, b, z, edx, 0 )
	test	eax,eax
	mov	ecx,eax
	pop	eax
	jz	error
toend:
	ret
error:
	call	osmaperr
	xor	eax,eax
	jmp	toend
osread	ENDP

	END
