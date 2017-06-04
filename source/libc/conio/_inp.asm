include libc.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

_inp	PROC port
	xor	eax,eax
	mov	dx,WORD PTR [esp+4]
	in	al,dx
	ret
_inp	ENDP

	END
