include consx.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

mousex	PROC
	mov	eax,keybmouse_x
	ret
mousex	ENDP

	END
