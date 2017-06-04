include iost.inc

	.code

oupdcrc PROC USES ebx eax
	add	edx,[esi].S_IOST.ios_bp
	mov	ecx,eax
	mov	eax,[esi].S_IOST.ios_crc
	.while	ecx
		movzx	ebx,al
		xor	bl,[edx]
		shr	eax,8
		xor	eax,crctab[ebx*4]
		inc	edx
		dec	ecx
	.endw
	mov	[esi].S_IOST.ios_crc,eax
	ret
oupdcrc ENDP

	END
