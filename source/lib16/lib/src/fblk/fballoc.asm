; FBALLOC.ASM--
; Copyright (C) 2015 Doszip Developers

include fblk.inc
include alloc.inc
include string.inc

	.code

fballoc PROC _CType PUBLIC USES bx fname:PTR BYTE, ftime:DWORD, fsize:DWORD, flag:size_t
	invoke strlen,fname
	add ax,SIZE S_FBLK
	.if malloc(ax)
	    add ax,S_FBLK.fb_name
	    invoke strcpy,dx::ax,fname
	    sub ax,S_FBLK.fb_name
	    mov bx,ax
	    mov cx,flag
	    mov es:[bx].S_FBLK.fb_flag,cx
	    movmx es:[bx].S_FBLK.fb_time,ftime
	    movmx es:[bx].S_FBLK.fb_size,fsize
	    mov ax,bx
	.endif
	ret
fballoc ENDP

	END

