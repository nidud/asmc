	.486
	.model	flat, stdcall

public	_I8M
public	_U8M

	.code

	;
	; edx:eax * ecx:ebx
	;
_I8M:
_U8M:

_mul64	PROC
	test	edx,edx
	jnz	L1
	test	ecx,ecx
	jnz	L1
	mul	ebx
	ret
L1:
	push	eax
	push	edx
	mul	ecx
	mov	ecx,eax
	pop	eax
	mul	ebx
	add	ecx,eax
	pop	eax
	mul	ebx
	add	edx,ecx
	ret
_mul64	ENDP

	END
