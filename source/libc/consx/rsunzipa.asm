include consx.inc

externdef at_background:BYTE
externdef at_foreground:BYTE

	.code

rsunzipat PROC USES ebx
	.repeat
		lodsb
		mov	dl,al
		and	dl,0F0h
		.if	dl == 0F0h
			mov	ah,al
			lodsb
			and	eax,0FFFh
			mov	edx,eax
			lodsb
			call	@04
			.repeat
				stosb
				inc	edi
				dec	edx
				.break .if ZERO?
			.untilcxz
			.break .if !ecx
		.else
			call	@04
			stosb
			inc	edi
		.endif
	.untilcxz
	ret
@04:
	mov	ah,al
	and	eax,0FF0h
	shr	al,4
	movzx	ebx,al
	mov	al,at_background[ebx]
	mov	bl,ah
	or	al,at_foreground[ebx]
	retn
rsunzipat ENDP

	END
