include consx.inc
include stdio.inc

	.code

scputf	PROC x, y, a, l, f:LPSTR, p:VARARG
	ftobufin( f, addr p )
	scputs( x, y, a, l, addr _bufin )
	ret
scputf	ENDP

	END