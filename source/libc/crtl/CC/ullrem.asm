	.486
	.model	flat, stdcall

PUBLIC	_aullrem
PUBLIC	__ullmod
_div64U proto

	.code
__ullmod:
_aullrem:
	push	ebx
	mov	eax,4[esp+4]
	mov	edx,4[esp+8]
	mov	ebx,4[esp+12]
	mov	ecx,4[esp+16]
	call	_div64U
	mov	eax,ebx
	mov	edx,ecx
	pop	ebx
	ret	16

	END
