include consx.inc

	.code

	ASSUME	edi: PTR S_DOBJ

dlshow	PROC USES edi dobj:PTR S_DOBJ
	mov	edi,dobj
	.if	rcshow( [edi].dl_rect, [edi].dl_flag, [edi].dl_wp )
		or [edi].dl_flag,_D_ONSCR
	.endif
	ret
dlshow	ENDP

	END
