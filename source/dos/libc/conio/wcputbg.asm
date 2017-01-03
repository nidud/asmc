; WCPUTBG.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

wcputxg PROTO

	.code

wcputbg PROC _CType PUBLIC USES cx bx wp:DWORD, l:size_t, attrib:size_t
	mov	ax,attrib
	mov	ah,0Fh
	and	al,70h
	mov	cx,l
	les	bx,wp
	call	wcputxg
	ret
wcputbg ENDP

	END
