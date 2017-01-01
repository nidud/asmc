include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

rsevent PROC USES rsi rdi robj:PTR S_ROBJ, dobj:PTR S_DOBJ

	mov	rsi,rdx
	mov	rdi,rcx

	dlevent( rsi )

	mov	edx,[rsi].S_DOBJ.dl_rect
	mov	[rdi].S_ROBJ.rs_rect,edx

	ret
rsevent ENDP

	END
