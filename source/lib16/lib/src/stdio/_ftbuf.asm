; _FTBUF.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc

	.code

_ftbuf	PROC _CType PUBLIC flag:size_t, fp:DWORD
	push bx
	les bx,fp
	mov ax,es:[bx].S_FILE.iob_flag
	.if flag
	    .if ax & _IOFLRTN
		push ax
		invoke fflush,fp
		les bx,fp
		pop ax
		and ax,not (_IOYOURBUF or _IOFLRTN)
		mov es:[bx].S_FILE.iob_flag,ax
		xor ax,ax
		mov WORD PTR es:[bx].S_FILE.iob_bp+2,ax
		mov WORD PTR es:[bx].S_FILE.iob_base+2,ax
		mov WORD PTR es:[bx].S_FILE.iob_bp,ax
		mov WORD PTR es:[bx].S_FILE.iob_base,ax
		mov es:[bx].S_FILE.iob_bufsize,ax
	    .endif
	.else
	    and ax,_IOFLRTN
	    .if !ZERO?
		invoke fflush,fp
	    .endif
	.endif
	pop bx
	ret
_ftbuf	ENDP

	END
