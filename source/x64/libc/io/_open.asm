include io.inc
include share.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

_open	PROC path:LPSTR, oflag:UINT, args:VARARG
	_sopen( rcx, edx, SH_DENYNO, addr args )
	ret
_open	ENDP

	END
