include libc.inc

	.code

	option stackbase:esp

_outpw	PROC port, w
	mov	dx,WORD PTR port
	mov	ax,WORD PTR w
	out	dx,ax
	ret
_outpw	ENDP

	END
