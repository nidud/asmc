; __ARGC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
IFDEF	_UNICODE
extern	__wargv:qword
ELSE
extern	__argv:qword
ENDIF
	.data
	__argc dd 0

	END
