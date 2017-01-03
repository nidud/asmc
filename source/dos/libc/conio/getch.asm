; GETCH.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

getch	PROC _CType PUBLIC
	mov	ah,0
	int	16h
	cbw
	ret
getch	ENDP

	END
