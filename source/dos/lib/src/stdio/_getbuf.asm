; _GETBUF.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include alloc.inc

	.code

_getbuf PROC _CType PUBLIC USES bx fp:DWORD
	invoke malloc,_INTIOBUF
	les bx,fp
	.if !ZERO?
	    or	es:[bx].S_FILE.iob_flag,_IOMYBUF
	    mov es:[bx].S_FILE.iob_bufsize,_INTIOBUF
	.else
	    or	es:[bx].S_FILE.iob_flag,_IONBF
	    mov es:[bx].S_FILE.iob_bufsize,size_l
	    lea ax,es:[bx].S_FILE.iob_charbuf
	    mov dx,es
	.endif
	stom es:[bx].S_FILE.iob_bp
	stom es:[bx].S_FILE.iob_base
	mov  es:[bx].S_FILE.iob_cnt,0
	ret
_getbuf ENDP

	END
