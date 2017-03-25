include string.inc

	.code

ifdef __SSE__

	option	stackbase:esp

strstr_sse proc uses esi edi ebp ebx edx dst:LPSTR, src:LPSTR

	mov	edi,dst
	mov	esi,src

	strlen( esi )
	jz	nomatch
	mov	ebx,eax

	strlen( edi )
	jz	nomatch
	mov	ebp,eax

	dec	ebx
	inc	esi

mainloop:

	movzx	eax,BYTE PTR [esi-1]
	strchr( edi, eax )
	jz	nomatch

	sub	eax,edi
	sub	ebp,eax
	cmp	ebx,ebp
	ja	nomatch

	lea	edi,[edi+eax+1]
	test	ebx,ebx
	jz	match

	mov	eax,edi
	mov	edx,esi
	mov	ecx,ebx
	repe	cmpsb
	mov	edi,eax
	mov	esi,edx
	jnz	mainloop

match:
	mov	eax,edi
	dec	eax
	jmp	toend

nomatch:
	xor	eax,eax

toend:
	ret

strstr_sse endp
endif
	END
