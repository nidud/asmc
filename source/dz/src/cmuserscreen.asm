; CMUSERSCREEN.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

	.code

cmuserscreen PROC
	call	consuser
	ret
cmuserscreen ENDP

	END
