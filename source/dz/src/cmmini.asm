; CMMINI.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

	.code

cmamini PROC
	mov	eax,panela
	call	panel_xormini
	ret
cmamini ENDP

cmbmini PROC
	mov	eax,panelb
	call	panel_xormini
	ret
cmbmini ENDP

cmcmini PROC
	mov	eax,cpanel
	call	panel_xormini
	ret
cmcmini ENDP

cmvolinfo PROC
	mov	eax,cpanel
	call	panel_xorinfo
	ret
cmvolinfo ENDP

cmavolinfo PROC
	mov	eax,panela
	call	panel_xorinfo
	ret
cmavolinfo ENDP

cmbvolinfo PROC
	mov	eax,panelb
	call	panel_xorinfo
	ret
cmbvolinfo ENDP

	END
