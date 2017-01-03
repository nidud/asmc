; CURSORSE.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

cursorset PROC _CType PUBLIC USES ax cursor:DWORD
	push	bx
	push	cx
	push	dx
	les	bx,cursor
	mov	cx,es:[bx].S_CURSOR.cr_type
	push	es:[bx].S_CURSOR.cr_xy
	mov	ah,1
	mov	bh,0
	int	10h
	pop	dx
	mov	ah,2
	int	10h
	pop	dx
	pop	cx
	pop	bx
	ret
cursorset ENDP

	END