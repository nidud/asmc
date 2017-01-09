include stdlib.inc

	.code

xtol	PROC USES esi ecx string:LPSTR
	mov	esi,string
	xor	eax,eax
	xor	ecx,ecx
	xor	edx,edx
	.while	1
		mov	al,[esi]
		add	esi,1
		or	al,0x20
		.break .if al < '0'
		.break .if al > 'f'
		.if	al > '9'
			.break .if al < 'a'
			sub	al,'a' - 10
		.else
			sub	al,'0'
		.endif
		shld	edx,ecx,4
		shl	ecx,4
		add	ecx,eax
		adc	edx,0
	.endw
	mov	eax,ecx
	ret
xtol	ENDP

	END
