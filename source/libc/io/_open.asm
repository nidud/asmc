include io.inc
include share.inc

	.code

_open	PROC c path:LPSTR, oflag:SIZE_T, args:VARARG
	_sopen( path, oflag, SH_DENYNO, addr args )
	ret
_open	ENDP

	END
