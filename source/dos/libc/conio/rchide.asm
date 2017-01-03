; RCHIDE.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

rchide	PROC _CType PUBLIC rect:DWORD, fl:size_t, wp:DWORD
	mov ax,fl
	.if ax & _D_DOPEN or _D_ONSCR
	    .if ax & _D_ONSCR
		invoke rcxchg,rect,wp
		.if fl & _D_SHADE
		    invoke rcclrshade,rect,wp
		.endif
	    .endif
	    mov ax,1
	.else
	    xor ax,ax
	.endif
	ret
rchide	ENDP

	END
