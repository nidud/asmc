; MEMQUOTE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strlib.inc

	.code

	option stackbase:esp

memquote proc uses edi ebx edx string:LPSTR, bsize:SIZE_T

	mov	eax,string
	mov	ebx,bsize

	test	ebx,ebx
	jz	failed

	test	eax,3
	jz	align_4

	mov	ecx,2227h

	cmp	[eax],cl
	je	exit_0
	cmp	[eax],ch
	je	exit_0
	cmp	ebx,1
	jz	failed

	cmp	[eax+1],cl
	je	exit_1
	cmp	[eax+1],ch
	je	exit_1
	cmp	ebx,2
	jz	failed

	cmp	[eax+2],cl
	je	exit_2
	cmp	[eax+2],ch
	je	exit_2
	cmp	ebx,3
	jz	failed

align_4:
	add	ebx,eax
	add	eax,3
	and	eax,-4

	ALIGN	4

loop_4:
	cmp	eax,ebx
	jae	failed

	mov	edx,[eax]
	mov	edi,edx
	add	eax,4
	xor	edx,'""""'
	xor	edi,"''''"
	lea	ecx,[edx-01010101h]
	not	edx
	and	ecx,edx
	lea	edx,[edi-01010101h]
	not	edi
	and	edx,edi
	and	ecx,80808080h
	and	edx,80808080h
	or	ecx,edx
	jz	loop_4
	bsf	ecx,ecx
	shr	ecx,3
	lea	eax,[eax+ecx-4]
	cmp	eax,ebx
	sbb	ecx,ecx
	and	eax,ecx
	ret
failed:
	xor	eax,eax
	ret
exit_2:
	inc	eax
exit_1:
	inc	eax
exit_0:
	test	eax,eax
	ret

memquote ENDP

	END
