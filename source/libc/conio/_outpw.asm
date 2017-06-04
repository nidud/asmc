include libc.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

_outpw	PROC port, w
	mov	dx,WORD PTR [esp+4]
	mov	ax,WORD PTR [esp+8]
	out	dx,ax
	ret
_outpw	ENDP

	END
