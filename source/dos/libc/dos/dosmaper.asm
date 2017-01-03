; DOSMAPER.ASM--
; Copyright (C) 2015 Doszip Developers
include dos.inc

	.code

dosmaperr PROC _CType PUBLIC doserr:size_t
	mov  ax,doserr
	call osmaperr
	ret
dosmaperr ENDP

	END
