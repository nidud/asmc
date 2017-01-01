include consx.inc
include stdio.inc

	.code

scputfEx PROC x, y, a, l, f:LPSTR, p:VARARG
	ftobufin( f, addr p )
	scputsEx( x, y, a, l, addr _bufin )
	ret
scputfEx ENDP

	END
