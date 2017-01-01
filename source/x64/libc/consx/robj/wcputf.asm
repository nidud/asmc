include consx.inc
include stdio.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

wcputf	PROC b:PVOID, l, max, format:LPSTR, argptr:VARARG
	ftobufin( format, addr argptr )
	wcputs( b, l, max, addr _bufin )
	ret
wcputf	ENDP

	END
