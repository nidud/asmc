; CMHIDDEN.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

	.code

cmahidden PROC
	xor	config.c_apath.ws_flag,_W_HIDDEN
	mov	eax,panela
	call	panel_update
	ret
cmahidden ENDP

cmchidden PROC
	mov	eax,panela
	cmp	eax,cpanel
	je	cmahidden
cmchidden ENDP

cmbhidden PROC
	xor	config.c_bpath.ws_flag,_W_HIDDEN
	mov	eax,panelb
	call	panel_update
	ret
cmbhidden ENDP

	END
