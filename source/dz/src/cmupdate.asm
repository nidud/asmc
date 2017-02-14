; CMUPDATE.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

	.code

cmaupdate PROC
	panel_reread(panela)
	ret
cmaupdate ENDP

cmbupdate PROC
	panel_reread(panelb)
	ret
cmbupdate ENDP

cmcupdate PROC
	panel_reread(cpanel)
	ret
cmcupdate ENDP

	END
