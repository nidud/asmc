include consx.inc

externdef at_background:BYTE
externdef at_foreground:BYTE

	.code

	OPTION	WIN64:0, STACKBASE:rsp

rsunzipat PROC USES rbx

	lea	r8,at_foreground
	lea	r9,at_background

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
			mov	ah,al
			and	eax,0FF0h
			shr	al,4
			movzx	rbx,al
			mov	al,[r9+rbx]
			mov	bl,ah
			or	al,[r8+rbx]
			.repeat
				stosb
				inc	rdi
				dec	edx
				.break .if ZERO?
			.untilcxz
			.break .if !ecx
		.else
			mov	ah,al
			and	eax,0FF0h
			shr	al,4
			movzx	rbx,al
			mov	al,[r9+rbx]
			mov	bl,ah
			or	al,[r8+rbx]
			stosb
			inc	rdi
		.endif
	.untilcxz
	ret

rsunzipat ENDP

	END
