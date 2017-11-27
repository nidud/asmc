	.486
	.model	flat, c

public	_allrem
_I8D	proto

	.code

_allrem:
	push	ebx
	mov	eax,4[esp+4]
	mov	edx,4[esp+8]
	mov	ebx,4[esp+12]
	mov	ecx,4[esp+16]
	call	_I8D
	mov	eax,ebx
	mov	edx,ecx
	pop	ebx
	ret	16

	END
