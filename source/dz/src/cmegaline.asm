; CMEGALINE.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

	.code

cmegaline PROC
	call	doszip_hide
	mov	eax,49
	.if	cflag & _C_EGALINE

		mov al,24
	.endif
	conssetl( eax )
	call	apiega
	call	doszip_show
	ret
cmegaline ENDP

	END
