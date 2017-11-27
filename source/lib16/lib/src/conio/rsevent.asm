; RSEVENT.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

.code

rsevent PROC _CType PUBLIC robj:DWORD, dobj:DWORD
	invoke	dlevent,dobj
	push	es
	push	bx
	les	bx,dobj
	mov	dx,es:[bx+4]
	les	bx,robj
	mov	es:[bx+6],dx
	pop	bx
	pop	es
	ret
rsevent ENDP

	END
