include consx.inc

	.code

rsevent PROC robj:PTR S_ROBJ, dobj:PTR S_DOBJ
	dlevent( dobj )
	mov	ecx,dobj
	mov	edx,[ecx+4]
	mov	ecx,robj
	mov	[ecx+6],edx
	ret
rsevent ENDP

	END
