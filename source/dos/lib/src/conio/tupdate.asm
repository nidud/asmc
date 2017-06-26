; TUPDATE.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	PUBLIC	tupdate

	.code

tdummy	PROC _CType PRIVATE
	xor ax,ax
	ret
tdummy	ENDP

	.data
	tupdate p? _TEXT:tdummy

	END
