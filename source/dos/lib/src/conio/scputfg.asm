; SCPUTFG.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include mouse.inc

	.code

scputfg PROC _CType PUBLIC USES ax dx x:size_t, y:size_t, l:size_t, a:size_t
	mov	al,BYTE PTR x
	mov	ah,BYTE PTR y
	call	__getxypm
	invoke	wcputfg,dx::ax,l,a
	ShowMouseCursor
	ret
scputfg ENDP

	END
