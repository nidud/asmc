include io.inc
include share.inc

	.code

_wopen	PROC c path:LPWSTR, oflag:SINT, args:VARARG

	_wsopen( path, oflag, SH_DENYNO, addr args )
	ret

_wopen	ENDP

	END
