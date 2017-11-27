; DLOPEN.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

dlopen	PROC _CType PUBLIC USES bx dobj:DWORD, at:size_t, ttl:DWORD
	les bx,dobj
	invoke rcopen,DWORD PTR es:[bx].S_DOBJ.dl_rect,es:[bx].S_DOBJ.dl_flag,
		at,ttl,es:[bx].S_DOBJ.dl_wp
	les bx,dobj
	stom es:[bx].S_DOBJ.dl_wp
	.if ax
	    or es:[bx].S_DOBJ.dl_flag,_D_DOPEN
	    mov ax,1
	.endif
	ret
dlopen	ENDP

	END
