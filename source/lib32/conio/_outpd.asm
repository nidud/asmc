include libc.inc

	.code

	option stackbase:esp

_outpd	PROC port, d
	mov	dx,WORD PTR port
	mov	eax,d
	out	dx,eax
	ret
_outpd	ENDP

	END
