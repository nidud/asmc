; _STDBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

PUBLIC	_stdbuf

	.data
	_stdbuf dd 0	; buffer for stdout and stderr
		dd 0

	END
