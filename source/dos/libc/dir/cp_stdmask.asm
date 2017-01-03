; CP_STDMASK.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc

	PUBLIC	cp_stdpath
	PUBLIC	cp_stdmask

	.data
	cp_stdpath db 'C:\'
	cp_stdmask db '*.*',0

	END
