; STRCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

	.code

strcat	proc uses esi edi s1:LPSTR, s2:LPSTR
	mov	edi,s1
	mov	esi,s2
	xor	eax,eax
	or	ecx,-1
	repnz	scasb
	dec	edi
	.repeat
		mov al,[esi]
		mov [edi],al
		add esi,1
		add edi,1
	.until !al
	mov	eax,s1
	ret
strcat	ENDP

	END
