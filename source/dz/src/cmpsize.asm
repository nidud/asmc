; CMPSIZE.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

	.code

cmpsizeup PROC
	mov	edx,panela
	mov	edx,[edx].S_PANEL.pn_dialog
	mov	al,9
	.if cflag & _C_HORIZONTAL
		dec	al
	.endif
	.if [edx+7] != al
		inc	BYTE PTR config.c_panelsize
		call	redraw_panels
	.endif
	ret
cmpsizeup ENDP

cmpsizedn PROC
	xor	eax,eax
	.if eax != config.c_panelsize
		dec	config.c_panelsize
		call	redraw_panels
	.endif
	ret
cmpsizedn ENDP

	END
