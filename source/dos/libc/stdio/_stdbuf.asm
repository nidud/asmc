; _STDBUF.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc

	PUBLIC	_stdbuf

	.data
	_stdbuf dd ?	; buffer for stdout and stderr
		dd ?

	END
