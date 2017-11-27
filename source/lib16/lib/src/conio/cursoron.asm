; CURSORON.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

cursoron PROC _CType PUBLIC
	push	ax
	push	cx
	mov	cx,CURSOR_NORMAL
	mov	ah,1
	int	10h
	pop	cx
	pop	ax
	ret
cursoron ENDP

	END
