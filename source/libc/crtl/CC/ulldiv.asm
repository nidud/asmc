	.486
	.model	flat, stdcall

PUBLIC	_aulldiv
_div64U proto

	.code

_aulldiv:
	push	ebx
	mov	eax,4[esp+4]
	mov	edx,4[esp+8]
	mov	ebx,4[esp+12]
	mov	ecx,4[esp+16]
	call	_div64U
	pop	ebx
	ret	16

	END
