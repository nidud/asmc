; RCMOVE.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

rcmove PROC _CType PUBLIC USES di pRECT:DWORD, wp:DWORD, flag:size_t, x:size_t, y:size_t
local	rc:DWORD
	les di,pRECT
	movmx rc,es:[di]
	push es
	.if rchide(rc,flag,wp)
	    mov al,BYTE PTR x
	    mov ah,BYTE PTR y
	    mov rc.S_RECT.rc_x,al
	    mov rc.S_RECT.rc_y,ah
	    mov ax,flag
	    and ax,not _D_ONSCR
	    invoke rcshow,rc,ax,wp
	.endif
	pop es
	lodm rc
	stom es:[di]
	ret
rcmove	ENDP

	END
