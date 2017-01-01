include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp
	ASSUME	rdi: PTR S_DOBJ

dlshow	PROC USES rdi dobj:PTR S_DOBJ
	mov	rdi,rcx
	.if	rcshow( [rdi].dl_rect, [rdi].dl_flag, [rdi].dl_wp )
		or [rdi].dl_flag,_D_ONSCR
	.endif
	ret
dlshow	ENDP

	END
