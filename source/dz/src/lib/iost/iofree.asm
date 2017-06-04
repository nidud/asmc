include iost.inc
include alloc.inc

	.code

iofree	PROC USES eax edx io:PTR S_IOST
	xor	eax,eax
	mov	ecx,io
	push	[ecx].S_IOST.ios_bp
	mov	[ecx].S_IOST.ios_bp,eax
	call	free
	ret
iofree	ENDP

	END
