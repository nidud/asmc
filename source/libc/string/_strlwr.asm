include string.inc

	.code

_strlwr PROC USES esi string:LPSTR
	mov	esi,string
	.repeat
		mov	al,[esi]
		.break .if !al
		sub	al,'A'
		cmp	al,'Z' - 'A' + 1
		sbb	al,al
		and	al,'a' - 'A'
		xor	[esi],al
		inc	esi
	.until	0
	mov	eax,string
	ret
_strlwr ENDP

	END
