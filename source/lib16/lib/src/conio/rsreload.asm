; RSRELOAD.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

rsreload PROC _CType PUBLIC USES bx robj:DWORD, dobj:DWORD
	les bx,dobj
	mov ax,es:[bx]
	and ax,_D_DOPEN
	.if ax
	    invoke dlhide,dobj
	    push ax
	    sub ax,ax
	    mov al,es:[bx].S_DOBJ.dl_count
	    inc ax
	    shl ax,3
	    add ax,2
	    add ax,WORD PTR robj
	    mov dx,WORD PTR robj+2
	    mov cx,ax
	    mov al,es:[bx].S_DOBJ.dl_rect.rc_col
	    mul es:[bx].S_DOBJ.dl_rect.rc_row
	    .if es:[bx].S_DOBJ.dl_flag & _D_RESAT
		or ax,8000h
	    .endif
	    xchg cx,ax
	    invoke wcunzip,es:[bx].S_DOBJ.dl_wp,dx::ax,cx
	    invoke dlinit,dobj
	    pop ax
	    .if ax
		invoke dlshow,dobj
	    .endif
	.endif
	ret
rsreload ENDP

	END
