; DLHIDE.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

dlhide	PROC _CType PUBLIC USES di dobj:DWORD
	les	di,dobj
	push	es
	invoke	rchide,DWORD PTR es:[di].S_DOBJ.dl_rect,
		es:[di].S_DOBJ.dl_flag,es:[di].S_DOBJ.dl_wp
	pop	es
	.if ax
	    and es:[di].S_DOBJ.dl_flag,not _D_ONSCR
	.endif
	ret
dlhide	ENDP

	END
