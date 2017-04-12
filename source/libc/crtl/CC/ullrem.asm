	.486
	.model	flat, c

PUBLIC	_aullrem
PUBLIC	__ullmod
_U8D	proto

	.code
__ullmod:
_aullrem:
	push	ebx
	mov	eax,4[esp+4]
	mov	edx,4[esp+8]
	mov	ebx,4[esp+12]
	mov	ecx,4[esp+16]
	call	_U8D
	mov	eax,ebx
	mov	edx,ecx
	pop	ebx
	ret	16

	END
