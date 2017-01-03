; _FREEBUF.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include alloc.inc

	.code

_freebuf PROC _CType PUBLIC USES bx fp:DWORD
	les	bx,fp
	mov	ax,es:[bx].S_FILE.iob_flag
	mov	dx,ax
	and	ax,_IOREAD or _IOWRT or _IORW
	jz	@F
	and	dx,_IOMYBUF
	jz	@F
	invoke	free,es:[bx].S_FILE.iob_base
	sub	ax,ax
	mov	dx,ax
	les	bx,fp
	stom	es:[bx].S_FILE.iob_bp
	stom	es:[bx].S_FILE.iob_base
	mov	es:[bx].S_FILE.iob_flag,ax
	mov	es:[bx].S_FILE.iob_bufsize,ax
	mov	es:[bx].S_FILE.iob_cnt,ax
      @@:
	ret
_freebuf ENDP

	END
