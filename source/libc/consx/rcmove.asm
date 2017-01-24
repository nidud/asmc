include consx.inc

	.code

rcmove	PROC pRECT:PVOID, wp:PVOID, flag, x, y
	mov	eax,pRECT
	mov	eax,[eax]
	push	eax
	.if	rchide( eax, flag, wp )
		pop	eax
		mov	ecx,pRECT
		mov	al,BYTE PTR x
		mov	ah,BYTE PTR y
		mov	[ecx],eax
		push	eax
		mov	ecx,flag
		and	ecx,not _D_ONSCR
		rcshow( eax, ecx, wp )
	.endif
	pop	eax
	ret
rcmove	ENDP

	END
