include direct.inc

	.code

_wgetcwd PROC buffer:LPWSTR, maxlen:SINT

	_wgetdcwd( 0, buffer, maxlen )
	ret
_wgetcwd ENDP

	END
