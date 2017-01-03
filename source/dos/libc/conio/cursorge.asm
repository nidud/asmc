; CURSORGE.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

.code

cursorget PROC _CType PUBLIC USES bx cursor:DWORD
	mov	ah,3
	mov	bh,0
	int	10h
	xor	ax,ax
	les	bx,cursor
	mov	es:[bx],dx
	mov	es:[bx+2],cx
	cmp	cx,CURSOR_HIDDEN
	je	@F
	inc	ax
      @@:
	ret
cursorget ENDP

	END
