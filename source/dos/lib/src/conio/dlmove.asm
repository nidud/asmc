; DLMOVE.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include keyb.inc
include mouse.inc

	.code

dlmove PROC _CType PUBLIC USES di dobj:DWORD
	les	di,dobj
	mov	ax,es:[di]
	and	ax,_D_DMOVE or _D_DOPEN or _D_ONSCR
	cmp	ax,_D_DMOVE or _D_DOPEN or _D_ONSCR
	jne	dlmove_nul
	call	mousep
	jz	dlmove_nul
	mov	dx,es
	lea	ax,es:[di].S_DOBJ.dl_rect
	mov	cx,es:[di].S_DOBJ.dl_flag
	invoke	rcmsmove,dx::ax,es:[di].S_DOBJ.dl_wp,cx
	mov	ax,1
    dlmove_end:
	ret
    dlmove_nul:
	sub	ax,ax
	jmp	dlmove_end
dlmove	ENDP

	END
