include stdlib.inc

	.code

	option stackbase:esp

_atoi64 PROC string:LPSTR
	mov	eax,esp
	push	esi
	push	edi
	push	ebx
	push	ecx
	mov	ebx,[eax+4]
	xor	ecx,ecx
@@:
	mov	al,[ebx]
	inc	ebx
	cmp	al,' '
	je	@B
	push	eax
	cmp	al,'-'
	je	@2
	cmp	al,'+'
	jne	@F
@2:
	mov	al,[ebx]
	inc	ebx
@@:
	mov	cl,al
	xor	eax,eax
	xor	edx,edx
@@:
	sub	cl,'0'
	jc	@F
	cmp	cl,9
	ja	@F
	mov	esi,edx
	mov	edi,eax
	shld	edx,eax,3
	shl	eax,3
	add	eax,edi
	adc	edx,esi
	add	eax,edi
	adc	edx,esi
	add	eax,ecx
	adc	edx,0
	mov	cl,[ebx]
	inc	ebx
	jmp	@B
@@:
	pop	ecx
	cmp	cl,'-'
	jne	@F
	neg	eax
	neg	edx
	sbb	eax,0
@@:
	pop	ecx
	pop	ebx
	pop	edi
	pop	esi
	ret
_atoi64 ENDP

	END
