include consx.inc
include stdio.inc

	.code

wcputf	PROC c b:PVOID, l, max, format:LPSTR, argptr:VARARG
	ftobufin( format, addr argptr )
	wcputs( b, l, max, addr _bufin )
	ret
wcputf	ENDP

	END
