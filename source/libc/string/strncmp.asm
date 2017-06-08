include string.inc

	.code

	option stackbase:esp

strncmp proc uses esi edi edx s1:LPSTR, s2:LPSTR, count:SIZE_T

	mov	edi,s1
	mov	esi,s2
	mov	edx,count

	xor	eax,eax
	test	edx,edx
	jz	toend
@@:
	mov	al,[edi]
	cmp	al,[esi]
	lea	esi,[esi+1]
	lea	edi,[edi+1]
	jne	@F
	test	eax,eax
	je	toend
	dec	edx
	jnz	@B
	xor	eax,eax
	jmp	toend
@@:
	sbb	eax,eax
	sbb	eax,-1
toend:
	ret

strncmp ENDP

	END
