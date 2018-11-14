; __ARGC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

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
