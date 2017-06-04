include consx.inc

	.code

dllevent PROC ldlg:PTR S_DOBJ, listp:PTR S_LOBJ
	push	tdllist
	mov	eax,listp
	mov	tdllist,eax
	dlevent( ldlg )
	pop	ecx
	mov	tdllist,ecx
	ret
dllevent ENDP

	END
