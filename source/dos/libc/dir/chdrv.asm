; CHDRV.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc

	.code

chdrv	PROC _CType PUBLIC drv:WORD
	mov	dx,drv
	mov	ah,0Eh
	int	21h
	ret
chdrv	ENDP

	END
