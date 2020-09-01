; STRLEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

	.code

	option stackbase:esp

strlen	PROC string:LPSTR

	mov	eax,string
	mov	ecx,string
	push	edx
	and	ecx,3
	jz	L2
	sub	eax,ecx
	shl	ecx,3
	mov	edx,-1
	shl	edx,cl
	not	edx
	or	edx,[eax]
	lea	ecx,[edx-01010101h]
	not	edx
	and	ecx,edx
	and	ecx,80808080h
	jnz	L3
L1:
	add	eax,4
L2:
	mov	edx,[eax]
	lea	ecx,[edx-01010101h]
	not	edx
	and	ecx,edx
	and	ecx,80808080h
	jz	L1
L3:
	pop	edx
	bsf	ecx,ecx
	shr	ecx,3
	add	eax,ecx
	sub	eax,string
	ret

strlen	endp

	END
