; _STDBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

PUBLIC	_stdbuf

	.data
	_stdbuf string_t 0 ; buffer for stdout and stderr
		string_t 0

	end
