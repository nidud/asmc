include consx.inc

	.code

dlhide	PROC USES edi dobj:PTR S_DOBJ
	mov edi,dobj
	.if rchide( [edi].S_DOBJ.dl_rect, [edi].S_DOBJ.dl_flag, [edi].S_DOBJ.dl_wp )
		and [edi].S_DOBJ.dl_flag,not _D_ONSCR
	.endif
	ret
dlhide	ENDP

	END
