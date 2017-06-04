include libc.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

_outp	PROC port, b
	xor	eax,eax
	mov	dx,WORD PTR [esp+4]
	mov	al,BYTE PTR [esp+8]
	out	dx,al
	ret
_outp	ENDP

	END
