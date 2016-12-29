include libc.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

_inpw	PROC port
	mov	dx,WORD PTR [esp+4]
	in	ax,dx
	ret	4
_inpw	ENDP

	END
