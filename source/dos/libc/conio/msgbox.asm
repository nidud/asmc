; MSGBOX.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include io.inc
include stdio.inc
include string.inc

	.data
	cp_ok db '&Ok',0
	cp_er db 'Error',0
	.code

center_text:
	.if BYTE PTR [di]
	    mul ah
	    add ax,3
	    add ax,ax
	    add bx,ax
	    sub cx,6
	    invoke wcenter,es::bx,cx,ds::di
	.endif
	ret

MAXLINES equ 17

msgbox PROC _CType PRIVATE USES si di bx dname:DWORD, flag:size_t, string:DWORD
local dobj:S_DOBJ
local tobj:S_TOBJ
local cols:size_t
local lcnt:size_t
local backgr:BYTE
	sub si,si
	invoke strlen,dname
	mov bx,ax
	.if !strchr(string,10)
	    invoke strlen,string
	    .if ax > bx
		mov bx,ax
	    .endif
	.endif
	mov al,at_background[B_Title]
	mov backgr,al
	les di,string
	.if BYTE PTR es:[di]
	    .repeat
		.break .if !strchr(es::di,10)
		mov dx,ax
		sub dx,di
		.if dx >= bx
		    mov bx,dx
		.endif
		inc si
		inc ax
		mov di,ax
	    .until si == MAXLINES
	.endif
	invoke strlen,es::di
	.if ax >= bx
	    mov bx,ax
	.endif
	mov dl,2
	mov dh,76
	.if bl && bl < 70
	    mov dh,bl
	    add dh,8
	    mov dl,80
	    sub dl,dh
	    shr dl,1
	.endif
	.if dh < 40
	    mov dx,2814h
	.endif
	mov ax,flag
	mov dobj.dl_flag,ax
	mov dobj.dl_rect.rc_x,dl
	mov dobj.dl_rect.rc_y,7
	mov ax,si
	add al,6
	mov dobj.dl_rect.rc_row,al
	mov dobj.dl_rect.rc_col,dh
	mov dobj.dl_count,1
	mov dobj.dl_index,0
	add al,7
	.if al > _scrrow
	    mov dobj.dl_rect.rc_y,1
	.endif
	lea ax,tobj
	mov WORD PTR dobj.dl_object,ax
	mov WORD PTR dobj.dl_object+2,ss
	mov tobj.to_flag,_O_PBUTT
	mov al,dh
	shr al,1
	sub al,3
	mov tobj.to_rect.rc_x,al
	mov ax,si
	add al,4
	mov tobj.to_rect.rc_y,al
	mov tobj.to_rect.rc_row,1
	mov tobj.to_rect.rc_col,6
	mov tobj.to_ascii,'O'
	mov al,at_background[B_Dialog]
	or al,at_foreground[F_Dialog]
	.if dobj.dl_flag & _D_STERR
	    mov at_background[B_Title],70h
	    mov al,at_background[B_Error]
	    or al,at_foreground[F_Desktop]
	    or tobj.to_flag,_O_DEXIT
	.endif
	mov dl,al
	.if dlopen(addr dobj,dx,dname)
	    les di,string
	    mov si,di
	    sub ax,ax
	    mov al,dobj.dl_rect.rc_col
	    mov cols,ax
	    mov lcnt,2
	    .repeat
		.break .if !BYTE PTR [si]
		invoke strchr,ds::di,10
		mov si,ax
		.break .if !ax
		mov BYTE PTR [si],0
		inc si
		mov cx,cols
		mov al,cl
		mov ah,BYTE PTR lcnt
		les bx,dobj.dl_wp
		call center_text
		mov di,si
		inc lcnt
	    .until lcnt == MAXLINES+2
	    invoke rcbprc,DWORD PTR tobj.to_rect,dobj.dl_wp,cols
	    sub cx,cx
	    mov cl,tobj.to_rect.rc_col
	    invoke wcpbutt,dx::ax,cols,cx,addr cp_ok
	    mov al,backgr
	    mov at_background[B_Title],al
	    mov cx,cols
	    mov al,cl
	    mov ah,BYTE PTR lcnt
	    les bx,dobj.dl_wp
	    call center_text
	    invoke dlmodal,addr dobj
	.endif
	ret
msgbox	ENDP

ermsg	PROC _CDecl PUBLIC USES bx wtitle:DWORD, format:DWORD, argptr:VARARG
	invoke ftobufin,format,addr argptr
	lodm wtitle
	.if !ax
	    mov ax,offset cp_er
	    mov dx,ds
	.endif
	invoke msgbox,dx::ax,_D_STDERR,addr _bufin
	sub ax,ax
	ret
ermsg	ENDP

stdmsg	PROC _CDecl PUBLIC wtitle:DWORD, format:DWORD, argptr:VARARG
	invoke ftobufin,format,addr argptr
	invoke msgbox,wtitle,_D_STDDLG,addr _bufin
	sub ax,ax
	ret
stdmsg	ENDP

	END
