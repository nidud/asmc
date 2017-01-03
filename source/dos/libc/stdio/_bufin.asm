; _BUFIN.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc

	PUBLIC	_bufin

	.data
	_bufin	db _INTIOBUF dup(?)

	END
