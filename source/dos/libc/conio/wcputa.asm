; WCPUTA.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

wcputxg PROTO

	.code

wcputa	PROC _CType PUBLIC USES cx bx wp:DWORD, l:size_t, attrib:size_t
	les	bx,wp
	mov	ax,attrib
	mov	cx,l
	and	ax,00FFh
	call	wcputxg
	ret
wcputa	ENDP

	END
