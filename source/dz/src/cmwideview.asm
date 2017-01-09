; CMWIDEVIEW.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

	.code

cmawideview PROC
	mov	edx,panela
	jmp	cmwideview
cmawideview ENDP

cmbwideview PROC
	mov	edx,panelb
	jmp	cmwideview
cmbwideview ENDP

cmcwideview PROC
	mov	edx,cpanel
cmcwideview ENDP

cmwideview:
	mov	ecx,[edx].S_PANEL.pn_wsub
	mov	eax,[ecx].S_WSUB.ws_flag
	and	eax,not _W_DETAIL
	xor	eax,_W_WIDEVIEW
	mov	[ecx].S_WSUB.ws_flag,eax
	mov	eax,edx
	jmp	panel_redraw

	END
