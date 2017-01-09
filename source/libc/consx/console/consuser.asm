include consx.inc

	.code

consuser PROC
local	cursor:S_CURSOR
	GetCursor( addr cursor )
	SetCursor( addr console_cu )
	dlshow( addr console_dl )
	.while !getkey()

	.endw
	dlhide( addr console_dl )
	SetCursor( addr cursor )
	xor	eax,eax
	ret
consuser ENDP

	END
