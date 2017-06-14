include stdlib.inc
IFDEF	_UNICODE
extern	__wargv:qword
ELSE
extern	__argv:qword
ENDIF
	.data
	__argc dd 0

	END
