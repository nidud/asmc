; __ARGC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
IFDEF	_UNICODE
extern	__wargv:warray_t
ELSE
extern	__argv:array_t
ENDIF
public	_argc
	.data
	_argc label int_t
	__argc int_t 0

	END
