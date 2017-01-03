; DOSDATE.ASM--
; Copyright (C) 2015 Doszip Developers

include time.inc

.code

dosdate PROC _CType PUBLIC
	call dostime
	mov  ax,dx
	ret
dosdate ENDP

	END
