; MEMXCHG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strlib.inc

	option stackbase:esp

	.code

memxchg proc uses esi edi edx dst:LPSTR, src:LPSTR, count:SIZE_T

	mov	edi,dst
	mov	esi,src
	mov	ecx,count
tail:
	test	ecx,ecx
	jz	toend
	test	ecx,3
	jz	tail_4

	sub	ecx,1
	mov	al,[esi+ecx]
	mov	dl,[edi+ecx]
	mov	[esi+ecx],dl
	mov	[edi+ecx],al
	jmp	tail

	ALIGN	4
tail_4:
	sub	ecx,4
	mov	eax,[esi+ecx]
	mov	edx,[edi+ecx]
	mov	[esi+ecx],edx
	mov	[edi+ecx],eax
	jnz	tail_4
toend:
	mov	eax,edi
	ret

memxchg ENDP

	END
