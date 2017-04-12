include io.inc
include share.inc

	.code

_open	PROC path:LPSTR, oflag:SINT, args:VARARG

	_sopen( rcx, edx, SH_DENYNO, addr args )
	ret

_open	ENDP

	END
