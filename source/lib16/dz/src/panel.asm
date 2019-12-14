; PANEL.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include stdlib.inc
include io.inc
include dos.inc
include dir.inc
include math.inc
include alloc.inc
include string.inc
include conio.inc
include mouse.inc
include keyb.inc
include errno.inc
include progress.inc
ifdef __TE__
include tinfo.inc
endif

PUBLIC	cp_copyselected
extrn	MOBJ_STATUSLINE:WORD

_DATA	segment

ifdef __ROT__
cp_rot		db 'home',0
;cp_doc		db '.edit',0
cp_drv		db 'X:',0
endif
cp_openmsg	db 'open:',0
cp_pinfo0	db ' %s ',0
cp_pinfo1	db ' %c:\...%s ',0
cp_emptydisk	db '[%c:] Empty disk',0
cp_bselected	db '%s byte in %d file(s)',0
cp_copyselected db "%d file(s) to",0
ifdef __TEBLK__
TE_FFBLK	label	S_FFBLK
endif
DB_VIDISK	db 0		; ff_reserved	DB 21 dup(?)
CP_VIDISK	db 'C:\',0
CP_VIFREE	db ' Free:',10
CP_VITOTAL	db 'Total:',0
ifdef __TEBLK__
		dw ?
		db _A_SUBDIR or _A_SYSTEM
		dw ?		; ff_ftime	DW ?
		dw ?		; ff_fdate	DW ?
		dd ?		; ff_fsize	DD ?
		db '.edit',0	; ff_name	DB 13 dup(?)
endif
CP_VIBYTE	db 'byte',0
CP_NONAME	db 'NONAME',0
format_20s	db '%20s',0
format_24s	db '%24s',0
cp_error_chdir	db "Error open directory",0
cp_chdir_format db "Can't open the directory:",10,"%s",10,10,"%s",0

cp_emaxfb	db "This subdirectory contains more",10
		db "than %d files/directories.",10
		db "Only %d of the files is read.",0

qeax	dd ?	; Selected size
qedx	dd ?

_DATA	ENDS

_DZIP	segment

fblk_selectable PROC PRIVATE
	xor ax,ax
	.if !(BYTE PTR es:[bx] & _A_VOLID)
	    inc ax
	    .if BYTE PTR es:[bx] & _A_SUBDIR
		.if !(cflag & _C_SELECTDIR)
		    dec ax
		.endif
	    .endif
	.endif
	or ax,ax
	ret
fblk_selectable ENDP

fblk_select PROC pascal PUBLIC fblk:DWORD
	les bx,fblk
	call fblk_selectable
	.if !ZERO?
	    invoke fbselect,es::bx
	.endif
	ret
fblk_select ENDP

fblk_invert PROC pascal PUBLIC fblk:DWORD
	les bx,fblk
	call fblk_selectable
	.if !ZERO?
	    invoke fbinvert,es::bx
	.endif
	ret
fblk_invert ENDP

pcell_select PROC PRIVATE	; AX: panel
	push si
	mov si,ax
	call panel_curobj
	.if !ZERO?
	    invoke fblk_invert,dx::bx
	    .if ax
		mov ax,si
		call pcell_update
		mov ax,1
	    .endif
	.endif
	pop si
	ret
pcell_select ENDP

pcell_set PROC PRIVATE
	push si
	push di
	mov si,ax
	mov di,WORD PTR [si].S_PANEL.pn_xl
	mov al,[di].S_XCELL.xl_cols
	mul [di].S_XCELL.xl_rows
	mov dx,[si].S_PANEL.pn_fcb_count
	sub dx,[si].S_PANEL.pn_fcb_index
	.if ax >= dx
	    mov ax,dx
	.endif
	mov [si].S_PANEL.pn_cel_count,ax
	mov dx,[si].S_PANEL.pn_cel_index
	.if dx < ax
	    mov ax,dx
	.else
	    dec ax
	.endif
	mov [si].S_PANEL.pn_cel_index,ax
	cwd
	div [di].S_XCELL.xl_rows
	mov ah,0
	mov cx,ax
	mul [di].S_XCELL.xl_rows
	mov bx,[si].S_PANEL.pn_cel_index
	sub bx,ax
	mov al,[di].S_XCELL.xl_cpos.S_RECT.rc_col
	inc ax
	mul cx
	mov cx,ax
	mov ax,[di+12]
	add al,cl
	add ah,bl
	mov [di+4],ax
	mov ax,[di+14]
	mov [di+6],ax
	mov ax,[si].S_PANEL.pn_cel_index
	pop di
	pop si
	ret
pcell_set ENDP

pcell_open PROC PRIVATE
	mov bx,ax
	mov al,at_background[B_InvPanel]
	invoke dlopen,[bx].S_PANEL.pn_xl,ax,0
	ret
pcell_open ENDP

pcell_show PROC PUBLIC
	push si
	push di
	mov si,ax
	mov di,WORD PTR [si].S_PANEL.pn_xl
	xor ax,ax
	.if !([di].S_XCELL.xl_flag & _D_DOPEN or _D_ONSCR)
	    mov ax,si
	    call pcell_set
	    xor ax,ax
	    .if [si].S_PANEL.pn_cel_count != ax
		mov ax,si
		call pcell_open
		invoke dlshow,ds::di
		mov ax,1
	    .endif
	.endif
	pop di
	pop si
	ret
pcell_show ENDP

pcell_update PROC PUBLIC
	push si
	mov  si,ax
	invoke dlclose,[si].S_PANEL.pn_xl
	.if ax
	    mov	 ax,si
	    call pcell_set
	    mov	 ax,si
	    .if panel_curobj()
		push dx
		push bx
		xor  ax,ax
		mov  bx,WORD PTR [si].S_PANEL.pn_xl
		mov  al,[bx].S_XCELL.xl_rect.S_RECT.rc_x
		push ax
		mov  al,[bx].S_XCELL.xl_rect.S_RECT.rc_y
		push ax
		call [si].S_PANEL.pn_putfcb
		mov  ax,si
		call pcell_open
		invoke dlshow,[si].S_PANEL.pn_xl
		mov  ax,si
		call panel_putmini
		mov  ax,1
	    .endif
	.endif
	pop si
	ret
pcell_update ENDP

ifdef __MOUSE__

_XY_DRVINFO	= 8
_XY_CONFIG	= 7
_XY_MINISTATUS	= 6
_XY_NEWDISK	= 5
_XY_MOVEUP	= 4
_XY_MOVEDOWN	= 3
_XY_FILE	= 2
_XY_INSIDE	= 1
_XY_OUTSIDE	= 0

pcell_move PROC pascal PRIVATE USES si di ; AX = panel
local	fblk:DWORD
local	rect:S_RECT
local	dialog:DWORD
local	mouse:WORD
local	dlflag:WORD
local	selected:WORD
	mov si,ax
	call cpanel_findfirst
	jz pcell_move_end
	mov WORD PTR fblk,bx
	mov WORD PTR fblk+2,dx
	mov di,WORD PTR [si].S_PANEL.pn_xl
	movmx rect,[di].S_XCELL.xl_rect
	mov ax,si
	call panel_selected
	mov selected,ax
	call mousep
	cmp ax,1
	jne pcell_move_end
	;
	; Create a movable object
	;
	mov mouse,ax
	les bx,keyshift
	.if BYTE PTR es:[bx] & 3
	    dec mouse
	.endif
	.if selected
	    mov rect.rc_col,15
	    jmp @F
	.endif
	mov ax,[si].S_PANEL.pn_flag
	.if ax & _P_DETAIL
	    sub rect.rc_col,26
	.endif
	.while 1
	    mov al,rect.rc_x
	    add al,rect.rc_col
	    dec al
	    mov bl,rect.rc_y
	    invoke getxyw,ax,bx
	    .break .if al != ' '
	    dec rect.rc_col
	.endw
	inc rect.rc_col
      @@:
	inc rect.rc_col
	dec rect.rc_x
	xor ax,ax
	mov al,at_background[B_Inverse]
	;or  al,at_foreground[F_Black]
	invoke rcopen,DWORD PTR rect,_D_DMOVE or _D_CLEAR or _D_COLOR,ax,0,0
	stom dialog
	add ax,2
	mov bx,ax
	mov cx,selected
	.if cx
	    invoke wcputf,es::bx,0,0,addr cp_copyselected,cx
	.else
	    mov	 cl,rect.rc_col
	    dec	 cl
	    lodm fblk
	    add	 ax,S_FBLK.fb_name
	    invoke wcputs,es::bx,0,cx,dx::ax
	.endif
	mov dlflag,_D_DMOVE or _D_CLEAR or _D_COLOR or _D_DOPEN
	invoke rcshow,DWORD PTR rect,dlflag,dialog
	or dlflag,_D_ONSCR
	mov bx,WORD PTR rect
	mov dl,bh
	invoke scputw,bx,dx,1,' '
	add bl,rect.rc_col
	dec bl
	mov ax,' '
	.if BYTE PTR mouse
	    mov al,'+'
	.endif
	invoke scputw,bx,dx,1,ax
	;
	; Move the object
	;
	.while 1
	    call mousep
	    .break .if ax != 1
	    call mousex
	    .if al == rect.rc_x
		call mousey
		cmp al,rect.rc_y
		je @F
	    .endif
	    call mousex
	    mov dx,ax
	    call mousey
	    mov cx,ax
	    invoke rcmove,addr rect,dialog,dlflag,dx,cx
	  @@:
	    les bx,keyshift
	    mov dl,es:[bx]
	    xor ax,ax
	    .if ax != mouse
		.if !(dl & 3)
		    .continue
		.endif
		mov mouse,ax
		mov bx,WORD PTR rect
		add bl,rect.rc_col
		dec bl
		mov dl,bh
		invoke scputw,bx,dx,1,' '
	    .else
		.if dl & 3
		    .continue
		.endif
		inc ax
		mov mouse,ax
		mov al,rect.rc_y
		mov bl,rect.rc_x
		add bl,rect.rc_col
		dec bl
		invoke scputw,bx,ax,1,'+'
	    .endif
	.endw
	invoke rcclose,DWORD PTR rect,dlflag,dialog
	;
	; Find out where the object is
	;
	push ds
	mov ax,[si].S_PANEL.pn_flag
	mov dx,offset spanela
	.if !(ax & _P_PANELID)
	    add dx,S_PANEL
	.endif
	push dx
	call mousex
	push ax
	mov  si,ax
	call mousey
	push ax
	mov  di,ax
	call panel_xycmd
	.if ax
	    mov ax,1
	    .if !mouse
		inc ax
	    .endif
	.endif
	.if !ax
	    mov cx,9
	    mov bx,offset MOBJ_STATUSLINE
	    mov ax,si
	    mov dx,di
	    call statusline_xy
	    .if !ZERO?
		mov ax,cx
		dec ax
		.if ax == 6
		    mov ax,3
		.elseif ax > 6
		    jmp @F
		.elseif ax == 4
		    mov ax,1
		.elseif ax > 4
		    mov ax,4
		.elseif ax == 3
		    mov ax,2
		.elseif ax == 2
		    jmp @F
		.else
		    mov ax,5
		.endif
		jmp pcell_move_end
	    .endif
	  @@:
	    .if cflag & _C_COMMANDLINE
		les bx,DLG_Commandline
		mov al,es:[bx+5]
		mov ah,0
		.if ax == di
		    mov ax,6
		.else
		    xor ax,ax
		.endif
	    .else
		xor ax,ax
	    .endif
	.endif
    pcell_move_end:
	ret
pcell_move ENDP

endif

xcell_getrect PROC pascal PRIVATE xcell:DWORD, index:WORD
	push	si
	push	di
	mov	cx,index
	les	bx,xcell
	mov	al,es:[bx].S_XCELL.xl_rows
	mov	ah,0
	mov	di,ax
	mov	ax,cx
	cwd
	div	di
	mov	si,ax
	mul	di
	sub	cx,ax
	mov	al,es:[bx+14]
	mov	ah,0
	inc	ax
	mul	si
	add	ax,es:[bx+12]
	mov	dx,es:[bx+14]
	add	ah,cl
	pop	di
	pop	si
	ret
xcell_getrect ENDP

ifdef __MOUSE__

pcell_setxy PROC pascal PUBLIC USES si di panel:WORD, xpos:WORD, ypos:WORD
local	rect:S_RECT
	mov si,panel
	mov ax,si
	call panel_state
	.if ax
	    invoke panel_xycmd,si,xpos,ypos
	    .while ax != 2
		call mousep
		.if ax != 2
		    xor ax,ax
		    jmp @F
		.endif
		call mousex
		mov di,ax
		call mousey
		mov si,ax
		invoke panel_xycmd,panel,di,si
		.if ax == _XY_FILE
		    invoke pcell_setxy,panel,di,si
		    jmp @F
		.endif
	    .endw
	    xor ax,ax
	    mov si,ax
	    mov di,ax
	    .while 1
		mov bx,panel
		mov ax,[bx].S_PANEL.pn_cel_count
		.if di < ax
		    invoke xcell_getrect,[bx].S_PANEL.pn_xl,di
		    stom rect
		    invoke rcxyrow,dx::ax,xpos,ypos
		    .if ZERO?
			inc di
		    .else
			inc si
			.break
		    .endif
		.endif
	    .endw
	    .if si == 1
		mov bx,panel
		mov ax,di
		.if ax != [bx].S_PANEL.pn_cel_index
		    mov [bx].S_PANEL.pn_cel_index,ax
		    mov ax,panel
		    call pcell_update
		.endif
	    .else
		.while 1
		    call mousep
		    .break .if ax != 2
		    push panel
		    call mousex
		    push ax
		    call mousey
		    push ax
		    call panel_xycmd
		    .break .if ax == _XY_FILE
		.endw
		.if ax == _XY_FILE
		    call mousex
		    mov si,ax
		    call mousey
		    invoke pcell_setxy, panel, si, ax
		.endif
		jmp @F
	    .endif
	    call mousep
	    .if ax != 2
		invoke mousewait, xpos, ypos, 1
		mov ax,panel
		call pcell_move
		.if ax == 1
		    call cmcopy
		.elseif ax == 2
		    call cmmove
		.elseif ax == 3
		    call cmview
		.elseif ax == 4
		    call cmedit
		.elseif ax == 5
		    call cmdelete
		.elseif ax == 6
		    call cmmklist
		.elseif !ax
		    mov di,10
		    .while di
			invoke delay, 16
			invoke mousep
			.break .if !ZERO?
			dec di
		    .endw
		    call mousep
		    .if !ZERO?
			call mousex
			.if ax == xpos
			    call mousey
			    .if ax == ypos
				invoke panel_event,panel,KEY_ENTER
			    .endif
			.endif
		    .endif
		    mov ax,1
		.endif
	    .else
		mov  ax,panel
		call pcell_select
		xor  ax,ax
		mov  al,rect.rc_x
		push ax
		mov  al,rect.rc_y
		push ax
		mov  al,rect.rc_col
		push ax
		call mousewait
		push panel
		call mousex
		push ax
		call mousey
		push ax
		call pcell_setxy
	    .endif
	.endif
      @@:
	ret
pcell_setxy ENDP

endif

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

cpanel_state PROC PUBLIC
	mov ax,cpanel
cpanel_state ENDP

panel_state PROC PUBLIC
	mov dx,ax
	mov bx,ax
	xor ax,ax
	mov bx,WORD PTR [bx].S_PANEL.pn_dialog
	.if WORD PTR [bx].S_DOBJ.dl_wp != ax
	    mov bx,dx
	    mov bx,WORD PTR [bx].S_PANEL.pn_wsub
	    mov ax,WORD PTR [bx].S_WSUB.ws_fcb
	    shr ax,2
	.endif
	ret
panel_state ENDP

panel_stateab PROC PUBLIC
	mov ax,panela
	call panel_state
	.if !ZERO?
	    mov ax,panelb
	    call panel_state
	.endif
	ret
panel_stateab ENDP

panel_open PROC pascal PRIVATE USES si di
local path[WMAXPATH]:BYTE
local wsub:DWORD
	mov si,ax
	mov di,[si]
	movmm wsub,[si].S_PANEL.pn_wsub
	invoke wsopen,dx::ax
	.if ax
	    xor ax,ax
	    mov [si].S_PANEL.pn_cel_count,ax
	    .if si == cpanel
		push [di]
		invoke strcpy,addr path,addr [di].S_PATH.wp_path
		mov [di].S_PATH.wp_path,0
		invoke cominit,wsub
		pop ax
ifdef __ZIP__
		.if ax & _W_ARCHIVE
		    push ax
		    invoke stricmp,addr path,addr [di].S_PATH.wp_path
		    pop dx
		    .if !ax
			mov [di],dx
		    .endif
		    or	ax,ax
		.endif
endif
	    .endif
	    .if [si].S_PANEL.pn_flag & _P_VISIBLE
		mov ax,si
		call panel_reread
		.if si == cpanel
		    mov ax,si
		    call panel_setactive
		.endif
	    .endif
	    mov ax,1
	.endif
	ret
panel_open ENDP

panel_open_ab PROC PUBLIC
	mov ax,cpanel
	call panel_open
	.if ax
	    mov ax,offset spanelb
	    .if cpanel == ax
		mov ax,offset spanela
	    .endif
	    call panel_open
	    mov ax,1
	.endif
	ret
panel_open_ab ENDP

panel_close PROC PUBLIC
	push	si
	mov	si,ax
	call	panel_state
	push	ax
	mov	ax,dx
	call	prect_close
	invoke	wsclose,[si].S_PANEL.pn_wsub
	pop	ax
	pop	si
	ret
panel_close ENDP

panel_hide PROC PUBLIC
	push	ax
	call	prect_close
	pop	bx
	push	ax
	invoke	wsfree,[bx].S_PANEL.pn_wsub
	pop	ax
	ret
panel_hide ENDP

panel_show PROC PUBLIC
	mov	bx,ax
	or	[bx].S_PANEL.pn_flag,_P_VISIBLE
	call	panel_update
	ret
panel_show ENDP

panel_setactive PROC PUBLIC
	push si
	push di
	mov si,ax
	mov di,cpanel
	and cflag,not _C_PANELID
	.if [si].S_PANEL.pn_flag & _P_PANELID
	    or cflag,_C_PANELID
	.endif
	invoke cominit,[si].S_PANEL.pn_wsub
	invoke dlclose,[di].S_PANEL.pn_xl
	mov cpanel,si
	mov ax,di
	call panel_putinfo
	.if cflag & _C_WIDEVIEW && si != di
	    mov ax,si
	    .if panel_state()
		mov ax,di
		call prect_hide
		or [di].S_PANEL.pn_flag,_P_WHIDDEN
		and [si].S_PANEL.pn_flag,not _P_WHIDDEN
		mov ax,si
		call panel_show
	    .endif
	.else
	    mov ax,si
	    call pcell_show
	    mov ax,si
	    call panel_putinfo
	.endif
	pop di
	pop si
	ret
panel_setactive ENDP

panel_curobj PROC PUBLIC
	mov bx,ax
	mov ax,WORD PTR [bx].S_PANEL.pn_wsub
	.if ax
	    mov ax,[bx].S_PANEL.pn_fcb_index
	    add ax,[bx].S_PANEL.pn_cel_index
	    invoke wsfblk,[bx].S_PANEL.pn_wsub,ax
	    .if !ZERO?
		mov bx,ax
		add ax,S_FBLK.fb_name
	    .endif
	.endif
	ret
panel_curobj ENDP

panel_findnext PROC PUBLIC
	mov	bx,ax
	invoke	wsffirst,[bx].S_PANEL.pn_wsub
	jz	@F
	mov	bx,ax
	add	ax,S_FBLK.fb_name
      @@:
	ret
panel_findnext ENDP

panel_selected PROC PRIVATE
	push ds
	push si
	mov bx,ax
	xor ax,ax
	mov cx,[bx].S_PANEL.pn_fcb_count
	.if cx
	    push ds
	    pop es
	    mov bx,WORD PTR [bx].S_PANEL.pn_wsub
	    lds si,[bx].S_WSUB.ws_fcb
	    .if si
		.while cx
		    les bx,[si]
		    .if es:[bx].S_FBLK.fb_flag & _A_SELECTED
			inc ax
		    .endif
		    add si,4
		    dec cx
		.endw
	    .endif
	.endif
	pop si
	pop ds
	ret
panel_selected ENDP

panel_setid PROC PUBLIC ; panel:AX, index:DX
	push ax
	push dx
	mov bx,ax
	xor ax,ax
	mov [bx].S_PANEL.pn_cel_index,ax
	mov [bx].S_PANEL.pn_fcb_index,ax
	mov ax,bx
	call pcell_set
	pop ax
	pop bx
	.if ax < [bx].S_PANEL.pn_cel_count
	    mov [bx].S_PANEL.pn_cel_index,ax
	.else
	    sub ax,[bx].S_PANEL.pn_cel_count
	    inc ax
	    mov [bx].S_PANEL.pn_fcb_index,ax
	    mov ax,[bx].S_PANEL.pn_cel_count
	    dec ax
	    mov [bx].S_PANEL.pn_cel_index,ax
	.endif
	ret
panel_setid ENDP

panel_openmsg PROC PUBLIC
	push si
	mov si,ax
	mov bx,WORD PTR [si].S_PANEL.pn_dialog
	.if [bx].S_DOBJ.dl_flag & _D_ONSCR
	    sub ax,ax
	    .if WORD PTR [bx].S_DOBJ.dl_wp != ax
		mov ax,[si].S_PANEL.pn_flag
		and ax,_P_MINISTATUS
		.if ax
		    mov ax,[bx+4]
		    add ah,[bx+7]
		    sub ah,2
		    inc al
		    mov cl,[bx+6]
		    sub cl,2
		    mov ch,0
		    mov bx,ax
		    mov dl,ah
		    mov ah,at_background[B_Panel]
		    or	ah,at_foreground[F_System]
		    mov al,' '
		    invoke scputw,bx,dx,cx,ax
		    invoke scputs,bx,dx,0,5,addr cp_openmsg
		    mov ax,[si]
		    add ax,S_PATH.wp_path
		    sub cl,6
		    add bl,6
		    invoke scpath,bx,dx,cx,ds::ax
		.endif
	    .endif
	.endif
	pop si
	ret
panel_openmsg ENDP

panel_putinfo PROC pascal PRIVATE USES si di
local path[WMAXPATH]:BYTE
local xy:WORD
	.if panel_state()
	    mov di,dx
	    mov si,WORD PTR [di].S_PANEL.pn_dialog
	    .if [si].S_DOBJ.dl_flag & _D_ONSCR
		mov si,[di]
		mov bx,WORD PTR [di].S_PANEL.pn_dialog
		mov ax,[bx+4]
		mov xy,ax
		invoke strcpy,addr path,addr [si].S_PATH.wp_path
ifdef __LFN__
		invoke wlongpath,dx::ax,0
endif
ifdef __ZIP__
		.if [si].S_PATH.wp_flag & _W_ARCHIVE or _W_ROOTDIR
		    invoke strfcat,dx::ax,addr [si].S_PATH.wp_file,addr [si].S_PATH.wp_arch
		.endif
endif
		mov dx,ax
		mov bx,xy
		add bx,0101h
		mov cl,bh
		mov ah,at_background[B_Panel]
		or  ah,at_foreground[F_Panel]
		mov al,[si].S_PATH.wp_path
		invoke scputw,bx,cx,1,ax
		mov cx,38
		.if cflag & _C_HORIZONTAL
		    mov cx,78
		.endif
		push cx
		push dx
		dec bh
		mov ah,at_background[B_Panel]
		or  ah,at_foreground[F_Frame]
		mov al,205
		mov dl,bh
		invoke scputw,bx,dx,cx,ax
		pop dx
		invoke strlen,ds::dx
		xchg dx,ax
		pop bx
		mov cl,at_background[B_Panel]
		.if di == cpanel
		    mov cl,at_background[B_InvPanel]
		.endif
		or cl,at_foreground[F_Frame]
		dec bx
		.if dx >= bx
		    mov cl,bl
		    inc cl
		    mov bx,xy
		    inc bl
		    push ax
		    mov ch,0
		    mov dl,bh
		    invoke scputw,bx,dx,cx,' '
		    inc bl
		    sub cl,2
		    pop ax
		    invoke scpath,bx,dx,cx,ds::ax
		.else
		    mov si,ax
		    mov al,bl
		    shr dl,1
		    adc dl,0
		    shr al,1
		    adc al,0
		    mov bx,xy
		    add bl,al
		    sub bl,dl
		    mov dl,bh
		    invoke scputf,bx,dx,cx,0,addr cp_pinfo0,ds::si
		.endif
	    .endif
	.endif
	ret
panel_putinfo ENDP

;----------------------------------------------------------------------------
; Ministatus window(s)
;----------------------------------------------------------------------------

ministatus_putselected:
      ifdef __3__
	xor eax,eax
	mov qeax,eax
	mov qedx,eax
      else
	xor ax,ax
	mov WORD PTR qeax+2,ax
	mov WORD PTR qeax,ax
	mov WORD PTR qedx+2,ax
	mov WORD PTR qedx,ax
      endif
	mov cx,[si].S_PANEL.pn_fcb_count
	.if cx
	    mov bx,WORD PTR [si].S_PANEL.pn_wsub
	    .if WORD PTR [bx].S_WSUB.ws_fcb != ax
		push bp
		push di
		push si
		mov di,ax
		les si,[bx].S_WSUB.ws_fcb
		mov bp,es
		.while cx
		    mov es,bp
		    les bx,es:[si]
		    mov ax,es:[bx].S_FBLK.fb_flag
		    .if ax & _A_SELECTED
			inc di
			.if !(al & _A_SUBDIR)
		      ifdef __3__
			    mov eax,es:[bx].S_FBLK.fb_size
			    add qeax,eax
			    adc qedx,0
		      else
			    lodm es:[bx].S_FBLK.fb_size
			    add WORD PTR qeax,ax
			    adc WORD PTR qeax+2,dx
			    adc WORD PTR qedx,0
			    adc WORD PTR qedx+2,0
		      endif
			.endif
		    .endif
		    add si,4
		    dec cx
		.endw
		mov cx,di
		pop si
		pop di
		pop bp
		push cx
		push ss
		push di
		invoke mkbstring,ss::di,qedx,qeax
		mov cl,at_background[B_Panel]
		or  cl,at_foreground[F_Panel]
		mov bx,[bp-6]
		inc bl
		mov dl,bh
		invoke scputf,bx,dx,cx,0,addr cp_bselected
		add sp,6
	    .endif
	.endif
	ret

volinfo_clear:
	mov	bx,[bp-6]
	sub	bh,2
	inc	bl
	mov	[bp-6],bx
	.if cflag & _C_HORIZONTAL
	    add bl,40
	.endif
	call	@F
	inc	bh
	call	@F
	dec	bh
	.if cflag & _C_HORIZONTAL
	    sub bl,40
	.else
	    dec bh
	.endif
      @@:
	mov	ah,at_background[B_Panel]
	or	ah,at_foreground[F_Panel]
	mov	al,' '
	mov	dl,bh
	invoke	scputw,bx,dx,37,ax
	ret

volinfo_putinfo:
	mov bx,[bp-6]
	.if (cflag & _C_HORIZONTAL)
	    add bl,40
	.endif
	mov	dl,bh
	invoke	scputs,bx,dx,0,0,addr CP_VIFREE
	add	bl,32
	invoke	scputs,bx,dx,0,0,addr CP_VIBYTE
	inc	dx
	invoke	scputs,bx,dx,0,0,addr CP_VIBYTE
	ret

volinfo_getdisk:
	mov bx,[si]
	add bx,S_PATH.wp_path
	mov ax,[bx]
	mov CP_VIDISK,al
	.if al && ah == ':'
	    and al,not 20h
	    mov CP_VIDISK,al
	    sub al,'@'
	    mov DB_VIDISK,al
	.else
	    mov DB_VIDISK,0FFh
	.endif
	ret

volinfo_putvolid:
	call volinfo_getdisk
	.if DB_VIDISK != 0FFh
	    mov ax,WORD PTR CP_VIDISK
	    mov [di],ax
	    mov ax,'*\'
	    mov [di+2],ax
	    mov ax,'*.'
	    mov [di+4],ax
	    mov BYTE PTR [di+6],0
	    invoke findfirst, ss::di, ss::di, _A_VOLID
	    or ax,ax
	    jnz @F
	.endif
	mov dx,ss
	mov ax,di
	add ax,S_FFBLK.ff_name
	mov ch,at_background[B_Panel]
	or  ch,at_foreground[F_Files]
	mov cl,0
	.if DB_VIDISK == 0FFh
	@@:
	    mov cl,at_background[B_Panel]
	    or	cl,at_foreground[F_Hidden]
	    mov ax,offset CP_NONAME
	    mov dx,ds
	.endif
	mov bl,[bp-5]
	.if !(cflag & _C_HORIZONTAL)
	    dec bl
	.endif
	invoke scputs,WORD PTR [bp-6],bx,0,cx,dx::ax
	ret

volinfo_putlfn:
      ifdef __LFN__
	invoke wvolinfo, addr CP_VIDISK, ss::di
	.if !ax
	    mov cl,at_background[B_Panel]
	    or	cl,at_foreground[F_Subdir]
	    mov bx,[bp-6]
	    add bl,12
	    .if !(cflag & _C_HORIZONTAL)
		dec bh
	    .endif
	    mov dl,bh
	    invoke scputf,bx,dx,cx,24,addr format_24s,ss::di
	.endif
      endif
	ret

ministatus_putvolinfo:
	call volinfo_clear
	call volinfo_putinfo
	call volinfo_putvolid
	call volinfo_putlfn
	invoke memzero,ss::di,S_DISKFREE
	push ss
	pop es
	stc
	mov ax,7303h
	mov cx,44
	mov dx,offset CP_VIDISK
	int 21h
	.if CARRY?
	    .if al
		ret
	    .endif
	    mov dl,DB_VIDISK
	    mov ah,36h
	    int 21h
	    .if ax == -1
		ret
	    .endif
	    mov WORD PTR [di].S_DISKFREE.df_sclus,ax
	    mov WORD PTR [di].S_DISKFREE.df_avail,bx
	    mov WORD PTR [di].S_DISKFREE.df_bsec, cx
	    mov WORD PTR [di].S_DISKFREE.df_total,dx
	.endif
    ifdef __3__
	mov eax,[di].S_DISKFREE.df_sclus
	push eax
	mul [di].S_DISKFREE.df_total
	mul [di].S_DISKFREE.df_bsec
	add di,S_DISKFREE
	invoke mkbstring,ss::di,edx,eax
	pop eax
	sub di,S_DISKFREE
	mul [di].S_DISKFREE.df_avail
	mul [di].S_DISKFREE.df_bsec
	add di,S_DISKFREE+20
	invoke mkbstring,ss::di,edx,eax
    else
	lodm [di].S_DISKFREE.df_sclus
	push ax
	push dx
	mov bx,WORD PTR [di].S_DISKFREE.df_total
	mov cx,WORD PTR [di].S_DISKFREE.df_total[2]
	call _mul32
	mov bx,WORD PTR [di].S_DISKFREE.df_bsec
	mov cx,WORD PTR [di].S_DISKFREE.df_bsec[2]
	call _mul32
	add di,S_DISKFREE
	invoke mkbstring,ss::di,cx::bx,dx::ax
	pop dx
	pop ax
	sub di,S_DISKFREE
	mov bx,WORD PTR [di].S_DISKFREE.df_avail
	mov cx,WORD PTR [di].S_DISKFREE.df_avail[2]
	call _mul32
	mov bx,WORD PTR [di].S_DISKFREE.df_bsec
	mov cx,WORD PTR [di].S_DISKFREE.df_bsec[2]
	call _mul32
	add di,S_DISKFREE + 20
	invoke mkbstring,ss::di,cx::bx,dx::ax
    endif
	push ss
	mov ax,di
	sub di,20
	push di
	push ss
	push ax
	mov cl,at_background[B_Panel]
	or  cl,at_foreground[F_Files]
	mov bx,[bp-6]
	add bl,11
	.if cflag & _C_HORIZONTAL
	    add bl,40
	.endif
	mov dl,bh
	invoke scputf,bx,dx,cx,0,addr format_20s
	add sp,4
	inc dl
	invoke scputf,bx,dx,cx,0,addr format_20s
	add sp,4
	ret

panel_putmini PROC pascal PRIVATE USES si di
local	path[138]:BYTE
	mov si,ax
	mov di,WORD PTR [si].S_PANEL.pn_dialog
	.if [di].S_DOBJ.dl_flag & _D_ONSCR
	    call panel_state
	    .if ax
		mov bx,di
		lea di,[bp-138]
		mov cx,[bx+6]
		mov bx,[bx+4]
		inc bl
		add bh,ch
		sub bh,2
		mov [bp-6],bx
		xor ax,ax
		mov al,bl
		mov [bp-2],ax
		mov al,bh
		mov [bp-4],ax
		mov bx,[si]
		mov ax,[si].S_PANEL.pn_flag
		.if ax & _P_MINISTATUS
		    .if ax & _P_DRVINFO
			push cx
			push [bp-6]
			call ministatus_putvolinfo
			pop bx
			mov [bp-6],bx
			pop cx
		    .endif
		    mov ch,0
		    sub cl,2
		    mov bl,[bp-2]
		    mov bh,[bp-4]
		    mov ah,at_background[B_Panel]
		    or	ah,at_foreground[F_Hidden]
		    mov al,' '
		    mov dx,ax
		    invoke scputw,bx,[bp-4],cx,ax
		    xor cx,cx
		    mov cl,dh
		    .if [si].S_PANEL.pn_fcb_count == 0
			mov dx,bx
			mov bx,[si]
			mov bl,[bx].S_PATH.wp_path
			mov cx,bx
			mov bx,dx
			mov dl,bh
			invoke scputf,bx,dx,cx,0,addr cp_emptydisk,cx
		    .else
			mov ax,[si].S_PANEL.pn_fcb_index
			add ax,[si].S_PANEL.pn_cel_index
			invoke wsfblk,[si].S_PANEL.pn_wsub,ax
			mov [bp-8],dx
			mov [bp-10],ax
			mov ax,si
			call panel_selected
			.if ax
			    call ministatus_putselected
			.else
			    push [bp-8]
			    push [bp-10]
			    push [bp-2]
			    push [bp-4]
			    call fbputfile
			    les bx,[bp-10]
			    .if es:[bx].S_FBLK.fb_flag & _A_UPDIR
				mov bx,[bp-6]
				mov al,bh
				invoke scputw,bx,ax,2,' '
				mov si,[si]
				invoke strfn,addr [si].S_PATH.wp_path
				mov cl,at_background[B_Panel]
				or  cl,at_foreground[F_System]
				invoke scputs,bx,[bp-5],cx,12,dx::ax
			    .endif
			.endif
		    .endif
		.endif
	    .endif
	.endif
	ret
panel_putmini ENDP

panel_putitem PROC pascal PUBLIC USES si di panel:WORD, index:WORD
local	rc:S_RECT
local	result:WORD
local	count:WORD
	mov si,panel
	mov di,WORD PTR [si].S_PANEL.pn_dialog
	.if [di].S_DOBJ.dl_flag & _D_ONSCR
	    movmx rc,[di].S_DOBJ.dl_rect
	    mov ax,[si].S_PANEL.pn_flag
	    .if ax & _P_MINISTATUS
		sub rc.rc_row,2
		.if ax & _P_DRVINFO
		    sub rc.rc_row,3
		    .if cflag & _C_HORIZONTAL
			inc rc.rc_row
		    .endif
		.endif
	    .endif
	    mov ax,[si].S_PANEL.pn_fcb_count
	    .if ax
		invoke dlclose,[si].S_PANEL.pn_xl
		mov result,ax
		mov ax,si
		call pcell_set
		invoke prect_clear,DWORD PTR rc,index
		mov bx,WORD PTR [si].S_PANEL.pn_dialog
		xor ax,ax
		mov dx,ax
		mov dl,[bx+5]
		mov di,dx
		dec ax
		mov count,ax
		.while 1
		    inc count
		    mov ax,count
		    .if ax >= [si].S_PANEL.pn_cel_count
			.if result
			    mov ax,si
			    call pcell_show
			.endif
			mov ax,si
			call panel_putmini
			.break
		    .endif
		    invoke xcell_getrect,[si].S_PANEL.pn_xl,count
		    mov dx,index
		    .if dx == 1
			mov bx,WORD PTR [si].S_PANEL.pn_xl
			mov dx,di
			add dl,[bx].S_XCELL.xl_rows
			inc dl
		    .elseif dx == 2
			mov dx,di
			add dx,2
		    .else
			mov dl,ah
		    .endif
		    .if ah == dl
			mov bx,WORD PTR [si].S_PANEL.pn_wsub
			les bx,[bx].S_WSUB.ws_fcb
			mov dx,[si].S_PANEL.pn_fcb_index
			add dx,count
			shl dx,2
			add bx,dx
			pushm es:[bx]
			xor  dx,dx
			mov  dl,al
			push dx
			mov  dl,ah
			push dx
			call [si].S_PANEL.pn_putfcb
		    .endif
		.endw
	    .else
		invoke prect_clear,DWORD PTR rc,0
	    .endif
	.endif
	ret
panel_putitem ENDP

ifdef __ROT__

wsreadroot PROC pascal PRIVATE USES si di wsub:DWORD, panel:WORD
local	dtime:	WORD
local	ddate:	WORD
local	disk:	WORD
local	index:	WORD
	invoke	wsfree,wsub
	xor	ax,ax
	mov	disk,ax
	mov	index,ax
	les	bx,wsub
	les	bx,es:[bx].S_WSUB.ws_flag
	mov	ax,es:[bx].S_PATH.wp_flag
	and	ax,not (_W_ARCHIVE or _W_NETWORK)
	or	ax,_W_ROOTDIR
	mov	es:[bx].S_PATH.wp_flag,ax
	mov	ax,sys_ercode
	or	al,sys_erflag
	or	al,sys_erdrive
	jnz	@F
	call	getdrv
	mov	disk,ax
      @@:
	xor ax,ax
	mov es:[bx].S_PATH.wp_arch,al
	invoke strcpy,addr es:[bx].S_PATH.wp_file,addr cp_rot
	xor di,di
	xor si,si
	.while si < MAXDRIVES
	    .if _disk_type(si)
		mov ax,si
		mov ah,S_DISK
		mul ah
		mov bx,ax
		add bx,offset drvinfo
		.if fballoc(addr [bx].S_DISK.di_name,DWORD PTR [bx].S_DISK.di_time,[bx].S_DISK.di_sizeax,[bx].S_DISK.di_flag)
		    les bx,wsub
		    les bx,es:[bx].S_WSUB.ws_fcb
		    mov cx,di
		    shl cx,2
		    add bx,cx
		    stom es:[bx]
		    .if si == disk
			mov index,di
		    .endif
		    inc di
		.endif
	    .endif
	    inc si
	.endw
	les bx,wsub
	mov es:[bx].S_WSUB.ws_count,di
	mov ax,di
	mov dx,index
	ret
wsreadroot ENDP

endif

wsub_read PROC _CType USES si di bx wsub:DWORD
	xor	si,si
	mov	bx,WORD PTR wsub
	mov	di,WORD PTR [bx].S_WSUB.ws_flag
ifdef __ZIP__
	mov	ax,[di]
	and	ax,_W_ARCHIVE
	jz	wsread_fail
	cmp	ax,_W_ARCHZIP
	jne	@F
	invoke	wzipread,wsub
	jmp	wsread_test
      @@:
    wsread_test:
	cmp	ax,ER_READARCH
	jne	wsread_sort
    wsread_fail:
	mov	ax,[di]
	and	ax,not (_W_ARCHIVE or _W_ROOTDIR)
	mov	[di],ax
endif ; __ZIP__
	invoke	wsread,wsub
    wsread_sort:
	mov	si,ax
	cmp	si,1
	jle	@F
	test	[di].S_PATH.wp_flag,_W_NOSORT
	jnz	@F
	invoke	wssort,wsub
      @@:
	mov	bx,WORD PTR wsub
	mov	ax,[bx].S_WSUB.ws_maxfb
	cmp	ax,si
	jne	wsread_end
	invoke	stdmsg,addr cp_warning,addr cp_emaxfb,ax,ax
    wsread_end:
	mov	ax,si
	ret
wsub_read ENDP

panel_read PROC PUBLIC
	push si
	mov si,ax
	call panel_openmsg
ifdef __ROT__
	mov bx,[si]
	.if [bx].S_PATH.wp_path && [bx].S_PATH.wp_flag & _W_ROOTDIR
	    invoke wsreadroot,[si].S_PANEL.pn_wsub,si
	    mov [si].S_PANEL.pn_cel_index,dx
	.else
	    invoke wsub_read,[si].S_PANEL.pn_wsub
	.endif
else
	invoke wsub_read,[si].S_PANEL.pn_wsub
endif
	mov [si].S_PANEL.pn_fcb_count,ax
	.if ax <= [si].S_PANEL.pn_fcb_index
	    .if ax
		dec ax
		mov [si].S_PANEL.pn_fcb_index,ax
		inc ax
	    .else
		mov [si].S_PANEL.pn_fcb_index,ax
	    .endif
	.endif
	pop si
	ret
panel_read ENDP

panel_reread PROC PUBLIC
	push	si
	mov	si,ax
	mov	ax,[si].S_PANEL.pn_flag
	and	ax,_P_VISIBLE
	jz	@F
	mov	ax,si
	call	panel_read
	xor	ax,ax
	call	panel_putinfo_AX
	mov	ax,1
      @@:
	pop	si
	ret
panel_reread ENDP

panel_redraw PROC PUBLIC
	push	si
	mov	si,ax
	mov	ax,[si].S_PANEL.pn_flag
	and	ax,_P_VISIBLE
	jz	@F
	mov	ax,si
	call	prect_open
	xor	ax,ax
	call	panel_putinfo_AX
	mov	ax,1
	cmp	si,cpanel
	jne	@F
	mov	ax,si
	call	pcell_show
      @@:
	pop	si
	ret
panel_redraw ENDP

redraw_panel:
	mov	bx,ax
	or	[bx].S_PANEL.pn_flag,_P_VISIBLE
	call	panel_redraw
	ret

redraw_panels PROC PUBLIC
	mov	ax,panelb
	call	prect_hide
	push	ax
	mov	ax,panela
	call	prect_hide
	test	ax,ax
	jz	@F
	mov	ax,panela
	call	redraw_panel
     @@:
	pop	ax
	test	ax,ax
	jz	@F
	mov	ax,panelb
	call	redraw_panel
      @@:
	ret
redraw_panels ENDP

panel_toggle PROC PUBLIC
	push si
	push di
	mov  si,ax
	call getpanelb
	mov  di,ax
	call panel_state
	mov cx,ax
	mov bx,WORD PTR [si].S_PANEL.pn_dialog
	mov ax,[bx]
	.if ax & _D_ONSCR
	    mov ax,di
	    mov di,bx
	    .if cx && si == cpanel
		call panel_setactive
	    .endif
	    mov ax,[di]
	    .if ax & _D_ONSCR
		mov ax,si
		call panel_hide
	    .endif
	.else
	    mov ax,si
	    call panel_show
	    mov di,cpanel
	    mov di,WORD PTR [di].S_PANEL.pn_dialog
	    mov ax,[di]
	    .if !(ax & _D_ONSCR)
		mov ax,si
		call panel_setactive
	    .endif
	.endif
	xor ax,ax
	pop di
	pop si
	ret
panel_toggle ENDP

panel_update PROC PUBLIC
	push	si
	mov	si,ax
	mov	ax,[si].S_PANEL.pn_flag
	and	ax,_P_VISIBLE
	jz	@F
	mov	ax,si
	call	panel_read
	mov	ax,si
	call	panel_redraw
      @@:
	pop	si
	ret
panel_update ENDP

panel_xormini PROC PUBLIC
	mov	bx,ax
	mov	ax,[bx].S_PANEL.pn_flag
	xor	ax,_P_MINISTATUS
	mov	[bx].S_PANEL.pn_flag,ax
	test	ax,_P_VISIBLE
	mov	ax,bx
	jz	@F
	call	panel_redraw
      @@:
	call	msloop
	xor	ax,ax
	ret
panel_xormini ENDP

panel_xorinfo PROC PUBLIC
	push	si
	mov	si,ax
	mov	ax,[si].S_PANEL.pn_flag
	xor	ax,_P_DRVINFO
	test	ax,_P_DRVINFO
	jz	@F
	or	ax,_P_MINISTATUS
      @@:
	mov	[si].S_PANEL.pn_flag,ax
	mov	ax,si
	call	panel_redraw
	pop	si
	ret
panel_xorinfo ENDP

panel_xycmd PROC pascal PUBLIC USES si di panel:WORD, xpos:WORD, ypos:WORD
local rect:S_RECT
local endx:WORD
	mov ax,panel
	.if panel_state()
	    dec ax
	    mov si,dx
	    mov di,WORD PTR [si].S_PANEL.pn_dialog
	    .if [di].S_DOBJ.dl_flag & _D_ONSCR
		movmx rect,[di].S_DOBJ.dl_rect
		sub ah,ah
		add al,rect.rc_col
		dec al
		mov endx,ax
		invoke rcxyrow,DWORD PTR rect,xpos,ypos
		mov dx,ax
		sub ax,ax
		.if dx
		    .if dx == 1
			mov ax,_XY_MOVEUP
		    .else
			mov di,dx
			.if dx == 2
			    mov dl,rect.rc_x
			    .if xpos == dx
				mov ax,_XY_INSIDE
			    .else
				add dx,2
				.if xpos <= dx
				    mov ax,_XY_NEWDISK
				.else
				    inc dx
				    .if dx == xpos
					mov ax,_XY_CONFIG
				    .else
					mov ax,_XY_MOVEUP
				    .endif
				.endif
			    .endif
			.else
			    mov bx,[si]
			    .if [si].S_PANEL.pn_flag & _P_MINISTATUS
				mov dl,rect.rc_row
				sub dl,2
				.if [si].S_PANEL.pn_flag & _P_DRVINFO
				    sub dl,2
				    .if !(cflag & _C_HORIZONTAL)
					dec dl
				    .endif
				.endif
				mov rect.rc_row,dl
				.if di > dx
				    mov ax,_XY_MOVEDOWN
				.elseif di != dx
				    jmp panel_xycmd_11
				.else
				    mov dl,rect.rc_x
				    add dl,2
				    .if xpos == dx
					mov ax,_XY_DRVINFO
				    .else
					jmp panel_xycmd_01
				    .endif
				.endif
			    .else
				mov dl,rect.rc_row
				.if dx != di
				    jmp panel_xycmd_11
				.else
				    jmp panel_xycmd_01
				.endif
			    .endif
			.endif
		    .endif
		.endif
	    .endif
	.endif
      @@:
	ret
    panel_xycmd_01:
	mov	dx,endx
	sub	dx,2
	mov	ax,_XY_MINISTATUS
	cmp	dx,xpos
	je	@B
	mov	ax,_XY_MOVEDOWN
	jmp	@B
    panel_xycmd_11:
	xor di,di
	.while di < [si].S_PANEL.pn_cel_count
	    invoke xcell_getrect,[si].S_PANEL.pn_xl,di
	    invoke rcxyrow,dx::ax,xpos,ypos
	    mov ax,_XY_INSIDE
	    .if !ZERO?
		mov ax,_XY_FILE
		.break
	    .endif
	    inc di
	.endw
	jmp @B
panel_xycmd ENDP

panel_putinfo_ZX:
	sub	ax,ax
	mov	[si].S_PANEL.pn_cel_index,ax
	mov	[si].S_PANEL.pn_fcb_index,ax

panel_putinfo_AX:
	push	ax
	mov	ax,si
	call	panel_putinfo
	pop	ax

panel_putitem_AX:
	invoke	panel_putitem,si,ax
	mov	ax,1
	ret

panel_sethdd PROC pascal PUBLIC USES si di panel:WORD, hdd:WORD
	call getdrv
	mov di,ax
	mov si,panel
	invoke _disk_init, hdd
	pushm [si].S_PANEL.pn_wsub
	push ax
	call historysave
	call wschdrv
	mov ax,si
	call panel_read
	.if si == cpanel
	    invoke cominit,[si].S_PANEL.pn_wsub
	.else
	    mov dx,di
	    mov ah,0Eh
	    int 21h
	.endif
	call panel_putinfo_ZX
	ret
panel_sethdd ENDP

cpanel_findfirst PROC PUBLIC
	mov ax,cpanel
	call panel_state
	.if !ZERO?
	    mov ax,dx
	    call panel_findnext
	    .if ZERO?
		mov ax,cpanel
		call panel_curobj
	    .endif
	    .if !ZERO? && !(cx & _A_UPDIR)
		test ax,ax
		ret
	    .endif
	.endif
	xor ax,ax
	ret
cpanel_findfirst ENDP

cpanel_gettarget PROC PUBLIC
	call panel_stateab
	.if !ZERO?
	    mov dx,ds
	    mov ax,offset path_a.wp_path
	    .if cpanel == offset spanela
		mov ax,offset path_b.wp_path
	    .endif
	.endif
	or ax,ax
	ret
cpanel_gettarget ENDP

cpanel_setpath PROC PUBLIC	; DX:AX
	mov	bx,cpanel
	mov	bx,[bx]
	and	WORD PTR [bx],not (_W_NETWORK or _W_ARCHIVE or _W_ROOTDIR)
	add	bx,S_PATH.wp_path
	invoke	strcpy,ds::bx,dx::ax
	mov	bx,cpanel
	invoke	cominit,[bx].S_PANEL.pn_wsub
	mov	ax,cpanel
	call	panel_reread
	ret
cpanel_setpath ENDP

cpanel_deselect PROC pascal PUBLIC USES si di fblk:DWORD
	les bx,fblk
	and es:[bx].S_FBLK.fb_flag,not _A_SELECTED
	mov di,progress_dobj.S_DOBJ.dl_flag
	and di,_D_ONSCR
	.if !ZERO?
	    invoke dlhide,addr progress_dobj
	.endif
	invoke panel_putitem,cpanel,0
	mov si,offset spanela
	.if si == cpanel
	    mov si,offset spanelb
	.endif
	mov bx,WORD PTR [si].S_PANEL.pn_wsub
	mov ax,[bx].S_WSUB.ws_maxfb
	sub ax,2
	.if ax > [bx].S_WSUB.ws_count
	    lodm fblk
	    add ax,S_FBLK.fb_name
	    invoke strlen,dx::ax
	    add ax,S_FBLK
	    push ax
	    invoke malloc,ax
	    pop bx
	    .if ax
		invoke memcpy,dx::ax,fblk,bx
		inc [si].S_PANEL.pn_fcb_count
		inc [si].S_PANEL.pn_cel_count
		mov bx,WORD PTR [si].S_PANEL.pn_wsub
		mov cx,[bx].S_WSUB.ws_count
		inc [bx].S_WSUB.ws_count
		les bx,[bx].S_WSUB.ws_fcb
		shl cx,2
		add bx,cx
		stom es:[bx]
		invoke panel_event,si,KEY_END
	    .endif
	.endif
	.if di
	    invoke dlshow,addr progress_dobj
	.endif
	ret
cpanel_deselect ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

panelevent_updatecell PROC PRIVATE
	mov ax,si
	call pcell_update
	ret
panelevent_updatecell ENDP

panelevent_LEFT PROC PRIVATE
	mov bx,WORD PTR [si].S_PANEL.pn_xl
	xor ax,ax
	cwd
	mov al,[bx+3]
	.if ax <= [si].S_PANEL.pn_cel_index
	    sub [si].S_PANEL.pn_cel_index,ax
	    jmp panelevent_updatecell
	.endif
	.if [si].S_PANEL.pn_cel_index != dx
	    mov [si].S_PANEL.pn_cel_index,dx
	    jmp panelevent_updatecell
	.endif
	.if [si].S_PANEL.pn_fcb_index == dx
	    xor ax,ax
	    ret
	.endif
	.if ax <= [si].S_PANEL.pn_fcb_index
	    sub [si].S_PANEL.pn_fcb_index,ax
	.else
	    mov [si].S_PANEL.pn_fcb_index,dx
	.endif
	mov ax,dx
	jmp panel_putitem_AX
panelevent_LEFT ENDP

panelevent_RIGHT PROC PRIVATE
	mov bx,WORD PTR [si].S_PANEL.pn_xl
	xor cx,cx
	mov cl,[bx+3]
	mov ax,[si].S_PANEL.pn_cel_index
	add ax,cx
	mov dx,[si].S_PANEL.pn_cel_count
	dec dx
	.if ax <= dx
	    add [si].S_PANEL.pn_cel_index,cx
	    jmp panelevent_updatecell
	.endif
	mov ax,[si].S_PANEL.pn_cel_index
	add ax,[si].S_PANEL.pn_fcb_index
	add ax,cx
	.if ax < [si].S_PANEL.pn_fcb_count
	    add [si].S_PANEL.pn_fcb_index,cx
	    xor ax,ax
	    jmp panel_putitem_AX
	.endif
	.if [si].S_PANEL.pn_cel_index < dx
	    mov [si].S_PANEL.pn_cel_index,dx
	    jmp panelevent_updatecell
	.endif
	xor ax,ax
	ret
panelevent_RIGHT ENDP

panelevent_UP PROC PRIVATE
	xor ax,ax
	.if [si].S_PANEL.pn_cel_index != ax
	    dec [si].S_PANEL.pn_cel_index
	    jmp panelevent_updatecell
	.endif
	.if [si].S_PANEL.pn_fcb_index == ax
	    ret
	.endif
	dec [si].S_PANEL.pn_fcb_index
	mov ax,2
	jmp panel_putitem_AX
panelevent_UP ENDP

panelevent_DOWN PROC PRIVATE
	mov ax,[si].S_PANEL.pn_cel_count
	dec ax
	cmp ax,[si].S_PANEL.pn_cel_index
	jbe @F
	inc [si].S_PANEL.pn_cel_index
	jmp panelevent_updatecell
      @@:
	jne @F
	mov ax,[si].S_PANEL.pn_fcb_count
	sub ax,[si].S_PANEL.pn_fcb_index
	sub ax,[si].S_PANEL.pn_cel_index
	cmp ax,1
	jle @F
	inc [si].S_PANEL.pn_fcb_index
	mov ax,1
	jmp panel_putitem_AX
      @@:
	xor ax,ax
	ret
panelevent_DOWN ENDP

panelevent_INS PROC PRIVATE
	mov ax,si
	call pcell_select
	.if ax
	    .if cflag & _C_INSMOVDN
		jmp panelevent_DOWN
	    .endif
	    mov ax,1
	.endif
	ret
panelevent_INS ENDP

panelevent_END PROC PRIVATE
	mov dx,[si].S_PANEL.pn_cel_count
	mov ax,[si].S_PANEL.pn_fcb_count
	.if dx < ax
	    sub ax,dx
	    mov [si].S_PANEL.pn_fcb_index,ax
	    dec dx
	    mov [si].S_PANEL.pn_cel_index,dx
	    xor ax,ax
	    jmp panel_putitem_AX
	.else
	    xor ax,ax
	    dec dx
	    .if dx > [si].S_PANEL.pn_cel_index
		mov [si].S_PANEL.pn_cel_index,dx
		mov [si].S_PANEL.pn_fcb_index,ax
		jmp panel_putitem_AX
	    .else
		ret
	    .endif
	.endif
panelevent_END ENDP

panelevent_HOME PROC PRIVATE
	xor ax,ax
	mov dx,[si].S_PANEL.pn_cel_index
	or  dx,[si].S_PANEL.pn_fcb_index
	.if dx
	    mov [si].S_PANEL.pn_cel_index,ax
	    mov [si].S_PANEL.pn_fcb_index,ax
	    jmp panel_putitem_AX
	.endif
	ret
panelevent_HOME ENDP

panelevent_PGUP PROC PRIVATE
	xor ax,ax
	mov dx,[si].S_PANEL.pn_cel_index
	or  dx,[si].S_PANEL.pn_fcb_index
	.if dx
	    .if [si].S_PANEL.pn_cel_index != ax
		mov [si].S_PANEL.pn_cel_index,ax
		jmp panelevent_updatecell
	    .endif
	    mov cx,ax
	    mov bx,WORD PTR [si].S_PANEL.pn_xl
	    mov al,[bx+2]
	    mov cl,[bx+3]
	    imul cx
	    .if ax <= [si].S_PANEL.pn_fcb_index
		sub [si].S_PANEL.pn_fcb_index,ax
	    .else
		mov [si].S_PANEL.pn_fcb_index,0
	    .endif
	    xor ax,ax
	    jmp panel_putitem_AX
	.endif
	ret
panelevent_PGUP ENDP

panelevent_PGDN PROC PRIVATE
	mov ax,[si].S_PANEL.pn_cel_count
	dec ax
	.if ax != [si].S_PANEL.pn_cel_index
	    mov [si].S_PANEL.pn_cel_index,ax
	    jmp panelevent_updatecell
	.endif
	add ax,[si].S_PANEL.pn_fcb_index
	inc ax
	.if ax == [si].S_PANEL.pn_fcb_count
	  @@:
	    xor ax,ax
	    ret
	.endif
	mov ax,[si].S_PANEL.pn_fcb_index
	add ax,[si].S_PANEL.pn_cel_count
	cmp ax,[si].S_PANEL.pn_fcb_count
	jnb @B
	mov ax,[si].S_PANEL.pn_cel_count
	dec ax
	add [si].S_PANEL.pn_fcb_index,ax
	xor ax,ax
	mov [si].S_PANEL.pn_cel_index,ax
	jmp panel_putitem_AX
panelevent_PGDN ENDP

;----------------------------------------------------------------------------
; Panel Event ENTER
;----------------------------------------------------------------------------

S_PEVENT STRUC
pe_fblk	 dd ?
pe_name	 dd ?
pe_flag	 dw ?
pe_panel dw ?
pe_event dw ?
pe_file	 db WMAXPATH dup(?)
pe_path	 db WMAXPATH dup(?)
S_PEVENT ENDS

panel_savepath PROC PRIVATE
	push cx
	push dx
	push ss
	lea  ax,[bp].S_PEVENT.pe_file
	push ax
	mov  ax,di
	mov  cx,[di].S_PATH.wp_flag
ifdef __ZIP__
	.if cx & _W_ARCHIVE or _W_ROOTDIR
	    .if [di].S_PATH.wp_arch
		add ax,S_PATH.wp_arch
		jmp panel_savepath_00
	    .else
		add ax,S_PATH.wp_file
		mov dx,ds
		jmp panel_savepath_01
	    .endif
	.endif
endif
      add ax,S_PATH.wp_path
ifdef __LFN__
	.if cx & _W_LONGNAME
	    invoke wlongname,ds::ax,0
	    jmp panel_savepath_01
	.else
	    invoke wshortname,ds::ax
	.endif
endif
    panel_savepath_00:
	invoke strfn,ds::ax
    panel_savepath_01:
	push dx
	push ax
	call strcpy
	pop dx
	pop cx
	ret
panel_savepath ENDP

ifdef __ROT__

panel_enter_rootdir PROC PRIVATE
	mov [di].S_PATH.wp_arch,0
	.if !(cx & _A_UPDIR)
	    invoke strcpy,addr [di].S_PATH.wp_arch,[bp].S_PEVENT.pe_name
	.endif
	or [di].S_PATH.wp_flag,_W_ROOTDIR
	jmp panel_enter_read
panel_enter_rootdir ENDP

endif

panel_enter_local PROC PRIVATE
      ifdef __ROT__
	test [bp].S_PEVENT.pe_flag,_A_ROOTDIR
	jnz panel_enter_rootdir
      endif
	invoke strfcat,addr [bp].S_PEVENT.pe_path,addr [di].S_PATH.wp_path,[bp].S_PEVENT.pe_name
	invoke chdir,addr [bp].S_PEVENT.pe_path
	inc ax
	.if ax
	    sub ax,ax
	    mov al,[di].S_PATH.wp_path
	    and al,not 20h
	    sub al,'@'
	    mov cx,ax
	  ifdef __LFN__
	    .if _ifsmgr && [di].S_PATH.wp_flag & _W_LONGNAME
		invoke wfullpath,addr [di].S_PATH.wp_path,cx
	    .else
		invoke fullpath,addr [di].S_PATH.wp_path,cx
	    .endif
	  else
	    invoke fullpath,addr [di].S_PATH.wp_path,cx
	  endif
	.else
	    ret
	.endif
panel_enter_local ENDP

panel_enter_read PROC PRIVATE
	invoke	cominit,[si].S_PANEL.pn_wsub
	mov	ax,si
	call	panel_read
	or	si,si
	ret
panel_enter_read ENDP

panel_add_to_path:
	add bx,S_FBLK.fb_name
	xor ax,ax
	.if [di] == al
	    invoke strcpy,ds::di,dx::bx
	.else
	    invoke strfcat,ds::di,ax::ax,dx::bx
	.endif
	ret

panel_reduce_path:
	invoke strrchr,ds::di,'\'
	mov bx,di
	.if ax
	    mov bx,ax
	    xor ax,ax
	.endif
	mov [bx],al
	ret

panel_enter_network:
	add di,S_PATH.wp_path
	.if cl & _A_UPDIR
	    mov ax,di
	    add ax,2
	    .if strrchr(ds::ax,'\')
		call panel_reduce_path
	    .endif
	.else
	    call panel_add_to_path
	.endif
	jmp panel_enter_read


ifdef __ZIP__

panel_enter_archive:
	.if cx & _A_UPDIR
	    .if ![di].S_PATH.wp_arch
		and [di].S_PATH.wp_flag,not (_W_ARCHIVE or _W_ROOTDIR)
	    .else
		add di,S_PATH.wp_arch
		call panel_reduce_path
	    .endif
	.else
	    add di,S_PATH.wp_arch
	    call panel_add_to_path
	.endif
	jmp panel_enter_read

endif

enter_directory_error:
	invoke errnomsg,addr cp_error_chdir,addr cp_chdir_format,addr [bp].S_PEVENT.pe_path
	ret

panel_enter_directory:
	mov di,[si]
	.if [di].S_PATH.wp_path[1] != ':'
	    .if [di].S_PATH.wp_path != '\'
		jmp enter_directory_error
	    .endif
	.endif
ifdef __ZIP__
	.if !(cx & _A_ARCHIVE)
endif
	    call historysave
ifdef __ZIP__
	.endif
endif
	sub ax,ax
	mov [bp].S_PEVENT.pe_file,al
	.if cl & _A_UPDIR
	    push bx
	    call panel_savepath
	    pop bx
	.endif
ifdef __ZIP__
	.if cx & _A_ARCHIVE
	    call panel_enter_archive
	.elseif [di].S_PATH.wp_path[1] == ':'
else
	.if [di].S_PATH.wp_path[1] == ':'
endif
	    call panel_enter_local
	    jz enter_directory_error
	.else
	    call panel_enter_network
	.endif
	.if !([bp.S_PEVENT.pe_flag] & _A_ROOTDIR)
	    sub ax,ax
	    mov [si].S_PANEL.pn_cel_index,ax
	    mov [si].S_PANEL.pn_fcb_index,ax
	    .if [bp].S_PEVENT.pe_file != al
		invoke wsearch,[si].S_PANEL.pn_wsub,addr [bp].S_PEVENT.pe_file
		.if ax != -1
		    mov dx,ax
		    mov ax,si
		    call panel_setid
		.endif
	    .endif
	.endif
	xor ax,ax
	jmp panel_putinfo_AX

panelevent_Enter PROC PRIVATE
	mov	ax,si
	call	panel_curobj
	stom	[bp].S_PEVENT.pe_name
	mov	WORD PTR [bp].S_PEVENT.pe_fblk,bx
	mov	WORD PTR [bp].S_PEVENT.pe_fblk+2,dx
	mov	[bp].S_PEVENT.pe_flag,cx
	jnz	@F
	ret
      @@:
	test	cl,_A_SUBDIR
	jz	@F
	jmp	panel_enter_directory
      @@:
	test	cx,_A_ARCHIVE
	jz	panelevent_enter_root
	xor	ax,ax
	ret

panelevent_enter_root:

ifdef __ROT__
	.if cx & _A_ROOTDIR
	    .if cx & _A_VOLID
		mov bx,cpanel
		mov bx,[bx]
		and [bx].S_PATH.wp_flag,not _W_ROOTDIR
		les bx,[bp].S_PEVENT.pe_name
		mov ah,0
		mov al,es:[bx]
		sub al,'A'
		invoke panel_sethdd,cpanel,ax
		mov ax,1
		ret
	    .endif
	.endif
endif

	.if isexec()
panel_enter_cmd:
	    lodm [bp].S_PEVENT.pe_name	; exe/com/bat
ifdef __LFN__
	    invoke wshortname,dx::ax
endif
	    invoke command,dx::ax
	    ret
	.endif

	invoke fbinitype,[bp].S_PEVENT.pe_fblk,addr [bp].S_PEVENT.pe_file
	.if ax
	    mov ax,1
	    ret
	.endif

ifdef __ZIP__
	mov	bx,[si]
	invoke	strfcat,addr [bp].S_PEVENT.pe_file,addr [bx].S_PATH.wp_path,[bp].S_PEVENT.pe_name
	invoke	readword,dx::ax
	.if ax == 4B50h ; 'PK'
	    mov ax,_W_ARCHZIP
	    jmp panel_enter_extern
	.endif
endif ; __ZIP__

	.if console & CON_NTCMD
	    jmp panel_enter_cmd
	.endif
	ret

ifdef __ZIP__
panel_enter_extern:
	.if path_a.wp_flag & _W_ARCHIVE || path_b.wp_flag & _W_ARCHIVE
	    xor ax,ax
	    ret
	.endif
	mov di,[si]
	mov [di].S_PATH.wp_arch,0
	and [di].S_PATH.wp_flag,not _W_ARCHIVE
	or  [di].S_PATH.wp_flag,ax
	add di,S_PATH.wp_file
	invoke strcpy,ds::di,[bp].S_PEVENT.pe_name
endif ; __ZIP__

panelevent_enter_read:
	mov	ax,si
	call	panel_read
	call	panel_putinfo_ZX
	ret
panelevent_Enter ENDP

;-----------------------------------------------------------------------------

panel_event PROC pascal PUBLIC USES si di panel:WORD, event:WORD
local pe:S_PEVENT
	push bp
	mov ax,panel
	call panel_state
	.if !ZERO?
	    mov pe.pe_panel,dx
	    mov ax,event
	    mov pe.pe_event,ax
	    lea bp,pe
	    mov si,dx
	    mov cx,pekey_count
	    xor bx,bx
	    .if ax == KEY_INS
		les bx,keyshift
		mov dl,es:[bx]
		.if dl & 3
		    xor ax,ax
		    jmp @F
		.endif
		xor bx,bx
	    .endif
	    .while cx
		.if ax == pekey_table[bx]
		    call peproc_table[bx]
		    jmp @F
		.endif
		add bx,2
		dec cx
	    .endw
	    xor ax,ax
	.endif
      @@:
	pop bp
	ret
panel_event ENDP

_DZIP	ENDS

_DATA	segment

pekey_table label WORD
	dw	KEY_LEFT
	dw	KEY_RIGHT
	dw	KEY_UP
	dw	KEY_INS
	dw	KEY_DOWN
	dw	KEY_END
	dw	KEY_HOME
	dw	KEY_PGUP
	dw	KEY_PGDN
	dw	KEY_ENTER
	dw	KEY_KPENTER

peproc_table label WORD
	dw	offset panelevent_LEFT
	dw	offset panelevent_RIGHT
	dw	offset panelevent_UP
	dw	offset panelevent_INS
	dw	offset panelevent_DOWN
	dw	offset panelevent_END
	dw	offset panelevent_HOME
	dw	offset panelevent_PGUP
	dw	offset panelevent_PGDN
	dw	offset panelevent_Enter
	dw	offset panelevent_Enter

pekey_count = (($ - offset peproc_table) / 2)

_DATA	ENDS

	END
