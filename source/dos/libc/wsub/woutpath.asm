; WOUTPATH.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc

	PUBLIC	__srcpath
	PUBLIC	__outpath
	PUBLIC	__srcfile
	PUBLIC	__outfile

	.data
	__srcpath db WMAXPATH dup(?)
	__outpath db WMAXPATH dup(?)
	__srcfile db WMAXPATH dup(?)
	__outfile db WMAXPATH dup(?)

	END
