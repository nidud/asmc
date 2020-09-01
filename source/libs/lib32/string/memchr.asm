; MEMCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

	.code

	option stackbase:esp

memchr	PROC uses esi edi ebx base:ptr, char:SINT, bsize:SIZE_T

	mov	edi,base
	mov	eax,char
	mov	ecx,bsize

	cmp	ecx,8
	jb	tail

	cmp	al,[edi]
	je	exit_0
	cmp	al,[edi+1]
	je	exit_1
	cmp	al,[edi+2]
	je	exit_2

	add	ecx,edi			; limit
	imul	esi,eax,01010101h	; populate char
	add	edi,3
	and	edi,-4			; align 4
	ALIGN	16
loop_4:
	cmp	edi,ecx
	jae	exit_NULL
	mov	ebx,[edi]
	add	edi,4
	xor	ebx,esi
	lea	eax,[ebx-01010101h]
	not	ebx
	and	eax,ebx
	and	eax,80808080h
	jz	loop_4
	bsf	eax,eax
	shr	eax,3
	lea	eax,[eax+edi-4]
	cmp	eax,ecx
	jb	toend
	jmp	exit_NULL
tail:
	test	ecx,ecx
	jz	exit_NULL
@@:
	cmp	al,[edi]
	je	exit_0
	add	edi,1
	sub	ecx,1
	jnz	@B
exit_NULL:
	xor	eax,eax
	ret
exit_2:
	add	edi,1
exit_1:
	add	edi,1
exit_0:
	mov	eax,edi
toend:
	ret
memchr	endp

	END
