; MEMRCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strlib.inc

	.code

	option stackbase:esp

memrchr PROC uses edi base:LPSTR, char:SIZE_T, bsize:SIZE_T

	mov	edi,base
	mov	al, byte ptr char
	mov	ecx,bsize
	test	ecx,ecx
	jz	@F
	lea	edi,[edi+ecx-1]
	std
	repnz	scasb
	cld
	jnz	@F
	mov	eax,edi
	inc	eax
	ret
@@:
	xor	eax,eax
	ret

memrchr ENDP

	END
