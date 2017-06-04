; CMMINI.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

	.code

cmamini PROC
	panel_xormini(panela)
	ret
cmamini ENDP

cmbmini PROC
	panel_xormini(panelb)
	ret
cmbmini ENDP

cmcmini PROC
	panel_xormini(cpanel)
	ret
cmcmini ENDP

cmvolinfo PROC
	panel_xorinfo(cpanel)
	ret
cmvolinfo ENDP

cmavolinfo PROC
	panel_xorinfo(panela)
	ret
cmavolinfo ENDP

cmbvolinfo PROC
	panel_xorinfo(panelb)
	ret
cmbvolinfo ENDP

	END
