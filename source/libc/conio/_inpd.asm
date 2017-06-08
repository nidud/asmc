include libc.inc

	.code

	option stackbase:esp

_inpd	PROC port
	mov	dx,WORD PTR [esp+4]
	in	eax,dx
	ret
_inpd	ENDP

	END
