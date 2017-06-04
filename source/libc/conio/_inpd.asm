include libc.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

_inpd	PROC port
	mov	dx,WORD PTR [esp+4]
	in	eax,dx
	ret
_inpd	ENDP

	END
