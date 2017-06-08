include libc.inc

	.code

	option stackbase:esp

_inp	PROC port
	xor	eax,eax
	mov	dx,WORD PTR [esp+4]
	in	al,dx
	ret
_inp	ENDP

	END
