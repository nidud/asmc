include iost.inc
include string.inc

	.code

oreadb	PROC USES ecx edx b:LPSTR, z
	mov	eax,z
	call	oread
	jz	@F
	memcpy( b, eax, z )
	mov	ecx,z
	jmp	toend
@@:
	xor	ecx,ecx
	mov	edx,b
@@:
	cmp	ecx,z
	jnb	toend
	call	ogetc
	jz	toend
	mov	[edx],al
	inc	edx
	inc	ecx
	jmp	@B
toend:
	mov	eax,ecx
	ret
oreadb	ENDP

	END
