	.486
	.model	flat, c

public	_alldiv
public	__lldiv
_I8D	proto

	.code
__lldiv:
_alldiv:
	push	ebx
	mov	eax,4[esp+4]
	mov	edx,4[esp+8]
	mov	ebx,4[esp+12]
	mov	ecx,4[esp+16]
	call	_I8D
	pop	ebx
	ret	16

	END
