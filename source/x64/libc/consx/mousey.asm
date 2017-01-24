include consx.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

mousey	PROC
	mov	eax,keybmouse_y
	ret
mousey	ENDP

	END
