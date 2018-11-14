; STRRCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

	.code

	option stackbase:esp

strrchr proc uses edi string:LPSTR, char:SIZE_T

	mov	edi,string
	xor	eax,eax
	mov	ecx,-1
	repne	scasb
	not	ecx
	dec	edi
	mov	al,byte ptr char
	std
	repne	scasb
	cld
	mov	al,0
	jne	@F
	lea	eax,[edi+1]
@@:
	test	eax,eax
	ret

strrchr endp

	END
