; MEMSET.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

	.code

	option cstack:off
	option stackbase:esp

memset	proc uses edi dst:LPSTR, char:SINT, count:SIZE_T

	mov edi,dst
	mov eax,char
	mov ecx,count
	rep stosb
	mov eax,dst
	ret

memset	endp

	END
