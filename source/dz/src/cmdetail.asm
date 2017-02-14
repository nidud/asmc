; CMDETAIL.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

	.code

cmadetail PROC
	mov	ecx,panela
	jmp	cmdetail
cmadetail ENDP

cmbdetail PROC
	mov	ecx,panelb
	jmp	cmdetail
cmbdetail ENDP

cmcdetail PROC
	mov	ecx,cpanel
cmcdetail ENDP

cmdetail:
	mov	edx,[ecx].S_PANEL.pn_wsub
	mov	eax,[edx].S_WSUB.ws_flag
	and	eax,not _W_WIDEVIEW
	xor	eax,_W_DETAIL
	mov	[edx].S_WSUB.ws_flag,eax

	panel_redraw(ecx)
	ret

	END
