include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

dlhide	PROC USES rdi dobj:PTR S_DOBJ
	mov	rdi,rcx
	.if	rchide( [rdi].S_DOBJ.dl_rect, [rdi].S_DOBJ.dl_flag, [rdi].S_DOBJ.dl_wp )
		and [rdi].S_DOBJ.dl_flag,not _D_ONSCR
	.endif
	ret
dlhide	ENDP

	END
