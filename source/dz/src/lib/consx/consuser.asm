include consx.inc

	.code

consuser PROC
local	cursor:S_CURSOR
	CursorGet( addr cursor )
	CursorSet( addr console_cu )
	dlshow( addr console_dl )
	.while !getkey()

	.endw
	dlhide( addr console_dl )
	CursorSet( addr cursor )
	xor	eax,eax
	ret
consuser ENDP

	END
