include tinfo.inc

	.code

	ASSUME	edx: PTR S_TINFO

tioption PROC USES esi edi ti:PTINFO

	mov	edx,ti
	mov	esi,titabsize
	mov	edi,tiflags

	mov	eax,[edx].ti_flag
	mov	tiflags,eax

	mov	eax,[edx].ti_tabz
	mov	titabsize,eax

	call	toption

	mov	eax,titabsize
	mov	ecx,tiflags
	mov	tiflags,edi
	mov	titabsize,esi

	mov	esi,eax
	mov	edx,ti
	mov	eax,[edx].ti_flag
	mov	edi,eax
	and	ecx,_T_TECFGMASK
	and	eax,not _T_TECFGMASK
	or	eax,ecx
	mov	[edx].ti_flag,eax

	mov	eax,edi
	and	eax,_T_USETABS
	and	ecx,_T_USETABS

	.if	eax != ecx || esi != titabsize
		.if	edi & _T_MODIFIED
			.if	tisavechanges( edx )

				tiflush( ti )
			.endif
		.endif
		mov	edx,ti
		mov	[edx].ti_tabz,esi
		tireload( edx )
	.endif
	ret
tioption ENDP

	END
