; EDITPAL.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include keyb.inc
include mouse.inc
include string.inc

.data

externdef	IDD_EditColor:DWORD

dialog		dd 0
format_X	db "%X",0
format_3d	db "%3d",0
cp_palette	db "Palette",0
cp_value	db " Value",0

Background	db B_Title		; to foreground
		db B_Panel
		db B_Panel
		db B_Panel
		db B_Panel
		db B_Dialog
		db B_Menus
		db B_Desktop
		db B_Dialog
		db B_Dialog
		db B_Panel
		db B_Panel
		db B_Menus
		db B_Title
		db B_Dialog
		db B_Menus
Foreground	db F_Desktop		; to background
		db F_Panel
		db F_Dialog
		db F_Menus
		db F_Dialog
		db F_Title
		db F_Panel
		db F_Dialog
		db F_Title
		db F_Files
		db F_Dialog
		db F_Dialog
		db F_TextView
		db F_TextEdit
		db F_TextView
		db F_TextEdit

.code

putinfo PROC PRIVATE USES si di bx
	les bx,dialog
	mov ax,es:[bx+4+16]
	add ax,es:[bx+4]
	add al,2
	mov dx,ax
	mov cl,ah
	xor di,di
	.repeat
	    sub ax,ax
	    mov al,at_foreground[di]
	    invoke scputf,dx,cx,0,3,addr format_X,ax
	    add dl,5
	    sub ax,ax
	    mov al,Background[di]
	    mov si,ax
	    mov al,at_background[si]
	    or	al,at_foreground[di]
	    invoke scputa,dx,cx,13,ax
	    add dl,42
	    mov al,at_background[B_Dialog]
	    or	ax,di
	    invoke scputa,dx,cx,1,ax
	    sub dl,47
	    inc cx
	    inc di
	.until di == 16
	les bx,dialog
	mov ax,es:[bx+4+16*17]
	add ax,es:[bx+4]
	mov bl,al
	add bl,7
	add al,2
	mov dx,ax
	mov cl,ah
	xor di,di
	.repeat
	    sub ax,ax
	    mov al,at_background[di]
	    shr al,4
	    invoke scputf,dx,cx,0,3,addr format_X,ax
	    sub ax,ax
	    mov al,Foreground[di]
	    mov si,ax
	    mov al,at_foreground[si]
	    or	al,at_background[di]
	    invoke scputa,bx,cx,13,ax
	    inc cx
	    inc di
	.until di == 14
	sub ax,ax
	mov al,at_background[di]
	invoke scputf,dx,cx,0,3,addr format_X,ax
	sub ax,ax
	mov al,Foreground[di]
	mov si,ax
	mov al,at_foreground[si]
	or  al,at_background[B_TextView]
	invoke scputa,bx,cx,13,ax
	inc cx
	inc di
	sub ax,ax
	mov al,at_background[di]
	invoke scputf,dx,cx,0,3,addr format_X,ax
	sub ax,ax
	mov al,Foreground[di]
	mov si,ax
	mov al,at_foreground[si]
	or  al,at_background[B_TextEdit]
	invoke scputa,bx,cx,13,ax
	sub ax,ax
	ret
putinfo ENDP

event_editat PROC _CType PRIVATE USES si di bx
	call putinfo
	call dlxcellevent
	sub dx,dx
	les bx,tdialog
	mov bl,es:[bx].S_DOBJ.dl_index
	mov bh,0
	.if ax == KEY_PGUP
	    .if bx < 16
		.if at_foreground[bx] < 0Fh
		    inc dx
		    inc at_foreground[bx]
		.endif
	    .elseif bx < 30
		.if at_background[bx-16] < 0F0h
		    inc dx
		    add at_background[bx-16],10h
		.endif
	    .elseif bx < 32
		.if at_foreground[bx] < 0Fh
		    inc dx
		    inc at_foreground[bx]
		.endif
	    .endif
	.elseif ax == KEY_PGDN
	    .if bx < 16
		.if at_foreground[bx]
		    inc dx
		    dec at_foreground[bx]
		.endif
	    .elseif bx < 30
		.if at_background[bx-16] >= 10h
		    inc dx
		    sub at_background[bx-16],10h
		.endif
	    .elseif bx < 32
		.if at_foreground[bx]
		    inc dx
		    dec at_foreground[bx]
		.endif
	    .endif
	.endif
	.if dx
	    push ax
	    invoke rsreload,IDD_EditColor,tdialog
	    invoke putinfo
	    pop ax
	.endif
	ret
event_editat ENDP

event_editpal PROC _CType PRIVATE USES si di bx
	les bx,tdialog
	mov bx,es:[bx+4]
	add bx,0405h
	mov cl,bh
	xor si,si
	.repeat
	    sub ax,ax
	    mov al,at_palett[si]
	    invoke scputf,bx,cx,0,3,addr format_3d,ax
	    inc cx
	    inc si
	.until si == 16
	call dlxcellevent
	mov di,ax
	HideMouseCursor
	les bx,tdialog
	xor ax,ax
	mov al,es:[bx].S_DOBJ.dl_index
	mov si,ax
	.if di == KEY_PGUP
	    inc at_palett[si]
	    sub di,di
	.elseif di == KEY_PGDN
	    dec at_palett[si]
	    sub di,di
	.endif
	mov al,at_palett[si]
	invoke setpal,ax,si
	ShowMouseCursor
	mov ax,di
	ret
event_editpal ENDP

edit_open PROC PRIVATE
	.if rsopen(IDD_EditColor)
	    stom dialog
	    invoke memcpy,ss::si,addr at_background,sizeof(S_COLOR)
	    invoke dlshow,dialog
	    invoke putinfo
	    les bx,dialog
	    mov ax,1
	.endif
	ret
edit_open ENDP

edit_event PROC PRIVATE
	invoke rsevent,IDD_EditColor,dialog
	invoke dlclose,dialog
	.if dx
	    mov ax,1
	.else
	    invoke memcpy,addr at_background,ss::si,sizeof(S_COLOR)
	    xor ax,ax
	.endif
	ret
edit_event ENDP

editattrib PROC _CType PUBLIC USES si bx
local tmp:S_COLOR
	lea si,tmp
	.if edit_open()
	    add bx,16+S_TOBJ.to_proc
	    mov ax,event_editat
	    mov cx,16+16
	    .repeat
		mov es:[bx],ax
		movl es:[bx+2],cs
		add bx,S_TOBJ
	    .untilcxz
	    invoke edit_event
	.endif
	ret
editattrib ENDP

editpal PROC _CType PUBLIC USES si di bx
local tmp:S_COLOR
	lea si,tmp
	.if edit_open()
	    mov bx,es:[bx+4]
	    add bx,0203h
	    mov cl,bh
	    invoke scputw,bx,cx,35,' '
	    invoke scputs,bx,cx,0,0,addr cp_value
	    sub cx,2
	    add bx,22
	    invoke scputs,bx,cx,0,0,addr cp_palette
	    les bx,dialog
	    add bx,16+S_TOBJ.to_proc
	    mov ax,event_editpal
	    mov cx,16
	    .repeat
		mov es:[bx],ax
		movl es:[bx+2],cs
		add bx,S_TOBJ
	    .untilcxz
	    sub bx,S_TOBJ.to_proc
	    mov ax,_O_STATE
	    mov cx,16
	    .repeat
		or es:[bx].S_TOBJ.to_flag,ax
		add bx,S_TOBJ
	    .untilcxz
	    .if !edit_event()
		invoke loadpal,addr at_palett
		xor ax,ax
	    .endif
	.endif
	ret
editpal ENDP

	END
