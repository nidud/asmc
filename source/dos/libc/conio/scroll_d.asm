; SCROLL_D.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include dos.inc

	.code

scroll_delay PROC _CType PUBLIC
	call	tupdate
	invoke	delay,8
	ret
scroll_delay ENDP

	END
