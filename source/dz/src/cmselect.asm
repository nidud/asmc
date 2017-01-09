; CMSELECT.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include string.inc

externdef cp_select:BYTE
externdef cp_deselect:BYTE
externdef cp_selectmask:BYTE

	.code

cmselect PROC USES esi edi
	.if !cp_selectmask
		strcpy( addr cp_selectmask, addr cp_stdmask )
	.endif
	.if tgetline( addr cp_select, addr cp_selectmask, 12, 32+8000h )
		.if cp_selectmask
			mov eax,cpanel
			.if panel_state()
				mov	edi,[eax].S_PANEL.pn_wsub
				mov	esi,[eax].S_PANEL.pn_fcb_count
				mov	edi,[edi].S_WSUB.ws_fcb
				.while	esi
					mov	eax,[edi]
					.if cmpwarg( addr [eax].S_FBLK.fb_name, addr cp_selectmask )
						fblk_select( [edi] )
					.endif
					add	edi,4
					dec	esi
				.endw
				panel_putitem( cpanel, 0 )
				mov	eax,1
			.endif
		.endif
	.endif
	ret
cmselect ENDP

cmdeselect PROC USES esi edi
	.if !cp_selectmask
		strcpy( addr cp_selectmask, addr cp_stdmask )
	.endif
	.if tgetline( addr cp_deselect, addr cp_selectmask, 12, 32+8000h )
		.if cp_selectmask
			mov eax,cpanel
			.if panel_state()
				mov	edi,[eax].S_PANEL.pn_wsub
				mov	esi,[eax].S_PANEL.pn_fcb_count
				mov	edi,[edi].S_WSUB.ws_fcb
				.while	esi
					mov	eax,[edi]
					add	eax,S_FBLK.fb_name
					.if cmpwarg( eax, addr cp_selectmask )
						mov	eax,[edi]
						and	[eax].S_FBLK.fb_flag,not _FB_SELECTED
					.endif
					add	edi,4
					dec	esi
				.endw
				panel_putitem( cpanel, 0 )
				mov	eax,1
			.endif
		.endif
	.endif
	ret
cmdeselect ENDP

cminvert PROC USES esi edi
	mov eax,cpanel
	.if panel_state()
		mov	edi,[eax].S_PANEL.pn_wsub
		mov	esi,[eax].S_PANEL.pn_fcb_count
		mov	edi,[edi].S_WSUB.ws_fcb
		.while	esi
			fblk_invert( [edi] )
			add edi,4
			dec esi
		.endw
		panel_putitem( cpanel, 0 )
		mov	eax,1
	.endif
	ret
cminvert ENDP

	END
