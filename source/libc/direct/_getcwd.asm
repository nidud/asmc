include direct.inc

	.code

_getcwd PROC buffer:LPSTR, maxlen:SINT
	_getdcwd( 0, buffer, maxlen )
	ret
_getcwd ENDP

	END
