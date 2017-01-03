; WSCHDRV.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc
include wsub.inc

	.code

wschdrv PROC _CType PUBLIC USES bx wsub:DWORD, drv:size_t
	les	bx,wsub
	les	bx,es:[bx].S_WSUB.ws_flag
	and	es:[bx].S_PATH.wp_flag,not (_W_ARCHIVE or _W_ROOTDIR)
	invoke	chdrv,drv
	invoke	wslocal,wsub
	ret
wschdrv ENDP

	END
