include string.inc

	.code

	option stackbase:esp

streol	PROC uses ebx edx string:LPSTR

	mov	eax,string
	ALIGN	4
@@:
	mov	edx,[eax]
	add	eax,4
	lea	ecx,[edx-01010101h]
	not	edx
	and	ecx,edx
	and	ecx,80808080h
	xor	edx,not 0A0A0A0Ah
	lea	ebx,[edx-01010101h]
	not	edx
	and	ebx,edx
	and	ebx,80808080h
	or	ecx,ebx
	jz	@B
@@:
	bsf	ecx,ecx
	shr	ecx,3
	lea	eax,[eax+ecx-4]

	cmp	eax,string
	je	@F
	cmp	BYTE PTR [eax],0
	je	@F
	cmp	BYTE PTR [eax-1],0Dh
	jne	@F
	dec	eax
@@:
	ret

streol	ENDP

	END
