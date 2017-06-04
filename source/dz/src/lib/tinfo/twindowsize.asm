include doszip.inc

	.code

tgetrect proc
if 1
	mov	edx,cpanel
else
	mov	edx,panelb
	.if	edx == cpanel

		mov	edx,panela
	.endif
endif
	mov	eax,cflag
	mov	ecx,[edx].S_PANEL.pn_dialog
	.if	!([ecx].S_DOBJ.dl_flag & _D_ONSCR)

		and	eax,NOT _C_PANELEDIT
	.endif
	mov	cflag,eax
	.if	eax & _C_PANELEDIT

		mov	eax,[ecx].S_DOBJ.dl_rect
		add	eax,0x00000101
		sub	eax,0x02020000
	.else

		mov	edx,_scrrow
		inc	edx
		mov	eax,_scrcol
		mov	ah,dl
		shl	eax,16
	.endif
	ret

tgetrect endp

tsetrect proc ti:PTINFO, rect:S_RECT

	mov	edx,ti
	mov	eax,rect
	mov	[edx].S_TINFO.ti_DOBJ.dl_rect,eax
	movzx	ecx,ah
	movzx	eax,al
	mov	[edx].S_TINFO.ti_xpos,eax
	mov	al,rect.rc_col
	mov	[edx].S_TINFO.ti_cols,eax
	.if	[edx].S_TINFO.ti_xoff >= eax

		dec	eax
		mov	[edx].S_TINFO.ti_xoff,eax
	.endif
	mov	al,rect.rc_row
	.if	[edx].S_TINFO.ti_flag & _T_USEMENUS

		inc	ecx
		dec	eax
	.endif
	mov	[edx].S_TINFO.ti_ypos,ecx
	mov	[edx].S_TINFO.ti_rows,eax
	.if	[edx].S_TINFO.ti_yoff >= eax

		dec	eax
		mov	[edx].S_TINFO.ti_yoff,eax
	.endif
	mov	eax,rect
	ret

tsetrect endp


twindowsize PROC USES esi edi ebx

	.if	tigetfile( tinfo )

		ASSUME	esi:PTR S_TINFO

		mov	esi,eax
		mov	edi,edx
		xor	cflag,_C_PANELEDIT
		mov	ebx,tgetrect()
		.if	ebx != [esi].ti_DOBJ.dl_rect

			.while	esi

				tihide( esi )

				and	[esi].ti_flag,NOT _T_PANELB
				.if	cflag & _C_PANELEDIT

					or	[esi].ti_flag,_T_PANELB
					and	[esi].ti_flag,NOT _T_USEMENUS
					and	tiflags,NOT _T_USEMENUS
				.else
					or	[esi].ti_flag,_T_USEMENUS
					or	tiflags,_T_USEMENUS
				.endif
				tsetrect( esi, ebx )

				.break .if esi == edi
				mov	esi,[esi].ti_next
			.endw

			tishow( tinfo )
		.endif
	.endif
	ret

twindowsize endp

	END
