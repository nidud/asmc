include stdlib.inc

	.code

_wtoi	PROC string:LPWSTR

	_wtol(string)
	ret

_wtoi	ENDP

	END
