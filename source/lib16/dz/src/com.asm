; COM.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include string.inc
include conio.inc
include tinfo.inc
include keyb.inc

PUBLIC	com_base
PUBLIC	com_wsub
PUBLIC	com_info

tihndlevent PROTO _CType :WORD, :WORD

	.data
	com_push db 1
	com_base db WMAXPATH dup(?)
	com_info S_TINFO <DGROUP:com_base, \
		_T_OVERWRITE, 0, 24, 80, WMAXPATH, 0, 0, 07h, ' ',<0018h,CURSOR_NORMAL>>
	com_wsub dw offset wspanela
		 dw SEG _DATA

_DZIP	segment

comhndlevent PROC PRIVATE
	.if cflag & _C_COMMANDLINE
	    push offset com_info
	    push ax
	    call cursoron
	    call tihndlevent
	.else
	    xor ax,ax
	.endif
	ret
comhndlevent ENDP

comevent PROC pascal PUBLIC USES si event:WORD
	mov ax,event
	mov si,1
	.if ax == KEY_UP
	    call cpanel_state
	    .if !ZERO?
		dec si
	    .else
		call cmdoskey_up
	    .endif
	.elseif ax == KEY_DOWN
	    call cpanel_state
	    .if !ZERO?
		dec si
	    .else
		call cmdoskey_dn
	    .endif
	.elseif ax == KEY_ALTRIGHT
	     call cmpathright
	.elseif ax == KEY_ALTLEFT
	     call cmpathleft
	.else
	     .if !ax || ax == KEY_CTRLX
		 dec si
	     .elseif comhndlevent()
		 dec si
	     .endif
	.endif
	mov ax,si
	ret
comevent ENDP

comhide PROC PUBLIC
	invoke	dlhide,DLG_Commandline
	call	cursoroff
	ret
comhide ENDP

comshow PROC PUBLIC
	mov ax,com_info.ti_ypos
	xor bx,bx
	.if BYTE PTR prect_b & _D_ONSCR
	    mov bx,offset prect_b
	.elseif BYTE PTR prect_a & _D_ONSCR
	    mov bx,offset prect_a
	.endif
	.if bx
	    mov dl,[bx].S_DOBJ.dl_rect.S_RECT.rc_y
	    add dl,[bx].S_DOBJ.dl_rect.S_RECT.rc_row
	    .if dl > al
		mov al,dl
	    .endif
	.endif
	.if !al && cflag & _C_MENUSLINE
	    inc al
	.endif
	.if al >= _scrrow && cflag & _C_STATUSLINE
	    dec al
	.endif
	.if al > _scrrow
	    mov al,_scrrow
	.endif
	mov BYTE PTR com_info.ti_ypos,al
	les bx,DLG_Commandline
	mov es:[bx+5],al
	.if cflag & _C_COMMANDLINE
	    invoke gotoxy,0,ax
	    call cursoron
	    invoke dlshow,DLG_Commandline
	    call cominitline
	.endif
	ret
comshow ENDP

cominitline PROC PRIVATE
	les bx,DLG_Commandline
	.if BYTE PTR es:[bx] & _D_ONSCR
	    mov ax,es:[bx+4]
	    mov com_info.ti_cursor.cr_xy,ax
	    mov BYTE PTR com_info.ti_ypos,ah
	    mov BYTE PTR com_info.ti_xpos,al
	    mov bx,com_wsub
	    invoke strlen,[bx].S_WSUB.ws_path
	    inc ax
	    .if ax > 51
		mov ax,51
	    .endif
	    mov com_info.ti_xpos,ax
	    mov dl,80
	    sub dl,al
	    mov BYTE PTR com_info.ti_cols,dl
	    mov dx,com_info.ti_ypos
	    invoke scputw,0,dx,80,' '
	    mov bx,com_wsub
	    invoke scpath,0,dx,50,[bx].S_WSUB.ws_path
	    mov bl,BYTE PTR com_info.ti_xpos
	    dec bl
	    invoke scputw,bx,dx,1,62 ; '>'
	    inc bl
	    invoke gotoxy,bx,dx
	    mov ax,KEY_PGUP
	    call comhndlevent
	.endif
	ret
cominitline ENDP

cominit PROC pascal PUBLIC wsub:DWORD
	movmm	com_wsub,wsub
	invoke	wsinit,dx::ax
	call	cominitline
	mov	ax,1
	ret
cominit ENDP

cmclrcmdl PROC _CType PUBLIC
	.if cflag & _C_ESCUSERSCR
	    call cmtoggleon
	.endif
cmclrcmdl ENDP

clrcmdl PROC _CType PUBLIC
	invoke	comevent, KEY_HOME
	mov	com_base,0
	call	cominitline
	ret
clrcmdl ENDP

_DZIP	ENDS

	END
