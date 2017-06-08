include libc.inc

	.code

	option stackbase:esp

_outp	PROC port, b
	xor	eax,eax
	mov	dx,WORD PTR port
	mov	al,BYTE PTR b
	out	dx,al
	ret
_outp	ENDP

	END
