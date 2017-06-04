; CMLASTMENU.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

	.code

cmlastmenu PROC
	mov	eax,menus_obj
	mov	edx,menus_idd
	mov	ecx,menus_iddtable[edx*4]
	mov	[ecx].S_ROBJ.rs_index,al
	push	edx
	menus_modalidd( edx )
	pop	edx
	menus_event( edx, eax )
	ret
cmlastmenu ENDP

	END
