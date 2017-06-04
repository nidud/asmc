include stdlib.inc
IFDEF	_UNICODE
extern	__wargv:dword
ELSE
extern	__argv:dword
ENDIF
	.data
	__argc dd 0

	END
