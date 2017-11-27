; _FMODE.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include fcntl.inc

	PUBLIC	_fmode

	.data
	_fmode	dw O_TEXT

	END
