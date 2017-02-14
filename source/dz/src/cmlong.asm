; CMLONG.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

	.code

cmalong PROC
	mov ecx,panela
	jmp cmlong
cmalong ENDP

cmblong PROC
	mov ecx,panelb
	jmp cmlong
cmblong ENDP

cmclong PROC
	mov ecx,cpanel
cmclong ENDP

cmlong:
	mov edx,[ecx].S_PANEL.pn_wsub
	xor [edx].S_WSUB.ws_flag,_W_LONGNAME
	panel_update(ecx)
	ret

	END
