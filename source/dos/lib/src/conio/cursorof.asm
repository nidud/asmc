; CURSOROF.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

cursoroff PROC _CType PUBLIC
	push	ax
	push	cx
	mov	cx,CURSOR_HIDDEN
	mov	ax,0103h
	int	10h
	pop	cx
	pop	ax
	ret
cursoroff ENDP

	END
