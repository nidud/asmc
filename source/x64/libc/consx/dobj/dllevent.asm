include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

dllevent PROC USES rbx ldlg:PTR S_DOBJ, listp:PTR S_LOBJ
	mov	rbx,tdllist
	mov	tdllist,rdx
	dlevent( rcx )
	mov	tdllist,rbx
	ret
dllevent ENDP

	END
