include libc.inc

	.code

	option stackbase:esp

_inpw	PROC port
	mov	dx,WORD PTR [esp+4]
	in	ax,dx
	ret
_inpw	ENDP

	END
