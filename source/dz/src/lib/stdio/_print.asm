include stdio.inc
include io.inc

	.code

_print	PROC C format:LPSTR, arglist:VARARG
	_write( 1, addr _bufin, ftobufin( format, addr arglist ) )
	ret
_print	ENDP

	END
