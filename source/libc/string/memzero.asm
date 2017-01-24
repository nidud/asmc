include string.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

memzero PROC dst:LPSTR, count:SIZE_T

	push	edi

	mov	edi,4[esp+4]
	mov	ecx,4[esp+8]

	xor	eax,eax
	rep	stosb

	mov	eax,4[esp+4]
	pop	edi
	ret	8

memzero endp

	END
