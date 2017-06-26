; FBSELECT.ASM--
; Copyright (C) 2015 Doszip Developers

include fblk.inc

	.code

fbselect PROC _CType PUBLIC fblk:DWORD
	sub ax,ax
	les bx,fblk
	.if !es:[bx].S_FBLK.fb_flag & _A_UPDIR
	    or es:[bx].S_FBLK.fb_flag,_A_SELECTED
	    inc ax
	.endif
	ret
fbselect ENDP

	END
