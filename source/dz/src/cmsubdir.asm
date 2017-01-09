; CMSUBDIR.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include io.inc

	.code

cmsubdir PROC
	mov	eax,cpanel
	.if	panel_curobj()
		.if	ecx & _A_SUBDIR
			panel_event( cpanel, KEY_ENTER )
		.endif
	.endif
	ret
cmsubdir ENDP

	END
