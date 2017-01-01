include consx.inc

	.code

	OPTION WIN64:0, STACKBASE:rsp

tosetbitflag PROC tobj:PTR S_TOBJ, count, flag, bitflag

	mov	eax,r9d
	not	eax
	.while	edx
		and	[rcx],ax
		shr	r9d,1
		.if	CARRY?
			or [rcx],r8w
		.endif
		add	rcx,SIZE S_TOBJ
		dec	edx
	.endw

	ret
tosetbitflag ENDP

	END
