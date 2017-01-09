; CMDETAIL.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

	.code

cmadetail PROC
	mov	edx,panela
	jmp	cmdetail
cmadetail ENDP

cmbdetail PROC
	mov	edx,panelb
	jmp	cmdetail
cmbdetail ENDP

cmcdetail PROC
	mov	edx,cpanel
cmcdetail ENDP

cmdetail:
	mov	ecx,[edx].S_PANEL.pn_wsub
	mov	eax,[ecx].S_WSUB.ws_flag
	and	eax,not _W_WIDEVIEW
	xor	eax,_W_DETAIL
	mov	[ecx].S_WSUB.ws_flag,eax
	mov	eax,edx
	jmp	panel_redraw

	END
