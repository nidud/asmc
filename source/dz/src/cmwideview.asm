; CMWIDEVIEW.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

	.code

cmawideview PROC
	mov ecx,panela
	jmp cmwideview
cmawideview ENDP

cmbwideview PROC
	mov ecx,panelb
	jmp cmwideview
cmbwideview ENDP

cmcwideview PROC
	mov ecx,cpanel
cmcwideview ENDP

cmwideview:
	mov edx,[ecx].S_PANEL.pn_wsub
	mov eax,[edx].S_WSUB.ws_flag
	and eax,not _W_DETAIL
	xor eax,_W_WIDEVIEW
	mov [edx].S_WSUB.ws_flag,eax

	panel_redraw(ecx)
	ret

	END
