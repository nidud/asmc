include io.inc
include share.inc

	.code

_open	proc c path:LPSTR, oflag:SINT, args:VARARG

	_sopen( path, oflag, SH_DENYNO, addr args )
	ret

_open	endp

	END
