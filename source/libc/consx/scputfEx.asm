include consx.inc
include stdio.inc

	.code

scputfEx PROC c USES edx ecx x, y, a, l, f:LPSTR, p:VARARG
	ftobufin( f, addr p )
	scputsEx( x, y, a, l, addr _bufin )
	ret
scputfEx ENDP

	END
