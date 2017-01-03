; CONSOLE.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	PUBLIC	console

	.data

ifdef __MOUSE__
 console dw CON_UBEEP or CON_MOUSE or CON_IOLFN or CON_CLIPB
else
 console dw CON_UBEEP or CON_IOLFN or CON_CLIPB
endif

	END
