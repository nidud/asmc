; SCENTER.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include mouse.inc

	.code

scenter PROC _CType PUBLIC USES dx x,y,l:size_t,s:DWORD
	mov	al,BYTE PTR x
	mov	ah,BYTE PTR y
	call	__getxypm
	invoke	wcenter,dx::ax,l,s
	ShowMouseCursor
	ret
scenter ENDP

	END
