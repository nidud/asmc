; WCPUTFG.ASM--
; Copyright (C) 2015 Doszip Developers
include conio.inc

wcputxg PROTO

	.code

wcputfg PROC _CType PUBLIC USES cx bx wp:DWORD, l:size_t, attrib:size_t
	mov	ax,attrib
	mov	ah,70h
	and	al,0Fh
	mov	cx,l
	les	bx,wp
	call	wcputxg
	ret
wcputfg ENDP

	END
