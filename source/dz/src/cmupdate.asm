; CMUPDATE.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

	.code

cmaupdate PROC
	mov	eax,panela
	call	panel_reread
	ret
cmaupdate ENDP

cmbupdate PROC
	mov	eax,panelb
	call	panel_reread
	ret
cmbupdate ENDP

cmcupdate PROC
	mov	eax,cpanel
	call	panel_reread
	ret
cmcupdate ENDP

	END
