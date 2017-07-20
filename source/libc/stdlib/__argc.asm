include stdlib.inc
IFDEF	_UNICODE
extern	__wargv:dword
ELSE
extern	__argv:dword
ENDIF
public	_argc
	.data
	_argc label dword
	__argc dd 0

	END
