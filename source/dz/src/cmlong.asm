; CMLONG.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

	.code

cmalong PROC
	mov	eax,panela
	jmp	cmlong
cmalong ENDP

cmblong PROC
	mov	eax,panelb
	jmp	cmlong
cmblong ENDP

cmclong PROC
	mov	eax,cpanel
cmclong ENDP

cmlong:
	mov	edx,[eax].S_PANEL.pn_wsub
	xor	[edx].S_WSUB.ws_flag,_W_LONGNAME
	jmp	panel_update

	END
