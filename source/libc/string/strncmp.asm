include string.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

strncmp PROC s1:LPSTR, s2:LPSTR, count:SIZE_T

	push	esi
	push	edi
	push	edx

	mov	edi,12[esp+4]
	mov	esi,12[esp+8]
	mov	edx,12[esp+12]

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
	pop	edx
	pop	edi
	pop	esi
	ret

strncmp ENDP

	END
