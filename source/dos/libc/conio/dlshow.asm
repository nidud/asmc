; DLSHOW.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

dlshow	PROC _CType PUBLIC USES di dobj:DWORD
	les di,dobj
	push es
	invoke rcshow,DWORD PTR es:[di].S_DOBJ.dl_rect,es:[di].S_DOBJ.dl_flag,es:[di].S_DOBJ.dl_wp
	pop es
	.if ax
	    or es:[di].S_DOBJ.dl_flag,_D_ONSCR
	    mov ax,1
	.endif
	ret
dlshow	ENDP

	END
