include libc.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

_outpd	PROC port, d
	mov	dx,WORD PTR [esp+4]
	mov	eax,[esp+8]
	out	dx,eax
	ret
_outpd	ENDP

	END
