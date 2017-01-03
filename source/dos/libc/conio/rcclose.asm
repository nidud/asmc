; RCCLOSE.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include alloc.inc

	.code

rcclose PROC _CType PUBLIC rect:DWORD, fl:size_t, wp:DWORD
	mov ax,fl
	.if ax & _D_DOPEN
	    .if ax & _D_ONSCR
		invoke rchide,rect,fl,wp
		mov ax,fl
	    .endif
	    .if !(ax & _D_MYBUF)
		invoke free,wp
	    .endif
	.endif
	mov ax,fl
	and ax,_D_DOPEN
	ret
rcclose ENDP

	END
