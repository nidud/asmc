include stdio.inc
include io.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

_print	PROC format:LPSTR, arglist:VARARG
	_write( 1, addr _bufin, ftobufin( format, addr arglist ) )
	ret
_print	ENDP

	END
