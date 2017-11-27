; PRECT.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include conio.inc
include mouse.inc
include string.inc
include dos.inc
ifdef __ROT__
include tinfo.inc
endif

_DATA	segment

S_PRECT STRUC
p_name	dw ?
p_type	dw ?	; 0+Name,1+Size,2+Date,3+Time
p_putf	dw ?
p_rect	S_RECT <>
S_PRECT ENDS

cp_name db 'Name',0
cp_date db 'Date',0
cp_time db 'Time',0
cp_size db 'Size',0

PRECT	label S_PRECT
	S_PRECT < 0,0,fbputsl,<1,2,12,1>>  ; Vertical Short List
	S_PRECT <26,3,fbputsd,<1,2,38,1>>  ; Vertical Short Detail
	S_PRECT < 0,0,fbputsl,<1,2,12,1>>  ; Horizontal Short List
	S_PRECT <26,3,fbputsd,<1,2,78,1>>  ; Horizontal Short Detail
	S_PRECT < 0,0,fbputll,<1,2,18,1>>  ; Vertical Long List
	S_PRECT <16,2,fbputld,<1,2,38,1>>  ; Vertical Long Detail
	S_PRECT < 0,0,fbputll,<1,2,18,1>>  ; Horizontal Long List
	S_PRECT <26,3,fbputld,<1,2,78,1>>  ; Horizontal Long Detail
	S_PRECT < 0,0,fbputlw,<1,2,38,1>>  ; Vertical Wide
	S_PRECT < 0,0,fbputhw,<1,2,78,1>>  ; Horizontal Wide

cp_strmega	db 0,'KMGT'
format_7luc	db '%7lu%c',0
format_10lu	db '%10lu',0
format_02lX	db ' VOL-%02lu ',0
cp_subdir	db " SUBDIR ",0
cp_updir	db " UP-DIR ",0
timex		dw 0
pflag		dw 0

_DATA	ENDS

_DZIP	segment

prect_hide PROC PUBLIC
	push si
	mov si,ax
	mov ax,[si].S_PANEL.pn_flag
	.if ax & _P_WHIDDEN
	    xor ax,_P_WHIDDEN
	    mov [si].S_PANEL.pn_flag,ax
	    mov ax,1
	.elseif ax & _P_VISIBLE
	    xor ax,_P_VISIBLE
	    mov [si].S_PANEL.pn_flag,ax
	    invoke dlclose,[si].S_PANEL.pn_xl
	    invoke dlhide,[si].S_PANEL.pn_dialog
	    mov ax,1
	.else
	    sub ax,ax
	.endif
	pop si
	ret
prect_hide ENDP

prect_close PROC PUBLIC
	push si
	mov si,ax
	mov ax,[si].S_PANEL.pn_flag
	and ax,_P_VISIBLE
	.if !ZERO?
	    mov ax,si
	    call prect_hide
	    invoke dlclose,[si].S_PANEL.pn_dialog
	    mov ax,1
	.endif
	pop si
	ret
prect_close ENDP

prect_open PROC pascal PUBLIC USES si di ; AX = panel
local	panel:WORD
local	rect:S_RECT
local	index:WORD
local	xcell:WORD
local	xlrc:S_RECT
local	dlwp:DWORD
local	rectp:S_RECT
	mov si,ax
	mov panel,ax
	call comhide
	mov di,[si].S_PANEL.pn_flag
	xor dx,dx		; x,y
	mov al,_scrcol		; cols
	shr al,1
	mov ah,_scrrow		; rows
	mov cx,cflag
	mov bh,9		; panel size (rows)
	.if !(cx & _C_COMMANDLINE)
	    inc ah		; rows++
	.endif
	.if cx & _C_MENUSLINE
	    inc dh		; y++
	    dec ah		; rows--
	.endif
	.if cx & _C_STATUSLINE
	    dec ah		; rows--
	.endif
	.if cx & _C_HORIZONTAL && !(cx & _C_WIDEVIEW)
	    shr ah,1		; rows / 2
	    dec bh
	.endif
	mov bl,ah
	sub bl,bh		; rows - bh (size)
	.if bl < BYTE PTR config.c_panelsize
	    mov BYTE PTR config.c_panelsize,bl
	.endif
	sub ah,BYTE PTR config.c_panelsize
	.if cx & _C_HORIZONTAL
	    mov al,_scrcol	; cols = 80
	    .if di & _P_PANELID && !(cx & _C_WIDEVIEW)
		add dh,ah	; y += rows
	    .endif
	.elseif di & _P_PANELID && !(cx & _C_WIDEVIEW)
	    mov dl,_scrcol	; x = 40
	    shr dl,1
	.endif
	mov WORD PTR rect,dx
	mov WORD PTR rect+2,ax
	xor bx,bx
	.if cx & _C_HORIZONTAL
	    mov bl,2
	.endif
	.if di & _P_DETAIL
	    inc bl
	.endif
ifdef __LFN__
	push bx
	mov  bx,[si]
	test [bx].S_PATH.wp_flag,_W_LONGNAME
	pop  bx
	.if !ZERO?
	    add bl,4
	.endif
endif
	.if di & _P_WIDEVIEW
ifdef __LFN__
	    mov bl,8
else
	    mov bl,4
endif
	    .if cx & _C_HORIZONTAL
		inc bl
	    .endif
	.endif
	push ax
	mov ax,sizeof(S_PRECT)
	mul bl
	add ax,offset PRECT
	mov xcell,ax
	mov bx,ax
	mov ax,WORD PTR [bx].S_PRECT.p_rect
	mov WORD PTR rectp,ax
	mov ax,WORD PTR [bx].S_PRECT.p_rect[2]
	mov dl,al
	mov WORD PTR rectp[2],ax
	mov al,_scrcol
	.if !dl == 78
	    shr al,1
	    .if !dl == 38
		.if dl == 18
		    shr al,1
		.else
		    mov al,14
		.endif
	    .endif
	.endif
	sub al,2
	pop cx
	mov rectp.rc_col,al
	mov ax,WORD PTR rectp
	add ax,WORD PTR rect
	mov dx,WORD PTR rectp[2]
	stom xlrc
	mov bx,WORD PTR [si].S_PANEL.pn_xl
	stom [bx].S_XCELL.xl_cpos
	sub ch,3
	mov [bx].S_XCELL.xl_rows,ch
	sub ax,ax
	mov al,cl
	dec al
	mov cl,xlrc.rc_col
	inc cl
	div cl
	mov [bx].S_XCELL.xl_cols,al
	mov bx,WORD PTR [si].S_PANEL.pn_dialog
	.if [bx].S_DOBJ.dl_flag & _D_DOPEN
	    invoke dlclose,[si].S_PANEL.pn_xl
	    invoke dlclose,[si].S_PANEL.pn_dialog
	.endif
	lodm rect
	stom [bx].S_DOBJ.dl_rect
	mov al,at_background[B_Panel]
	or  al,at_foreground[F_Frame]
	.if dlopen(ds::bx,ax,0)
	    xor ax,ax
	    mov WORD PTR rect,ax
	    lodm [bx].S_DOBJ.dl_wp
	    stom dlwp
	    sub cx,cx
	    mov cl,rect.rc_col
	    add ax,cx
	    add ax,cx
	    mov bx,ax
	    mov ah,at_background[B_Panel]
	    or	ah,at_foreground[F_Panel]
	    mov al,' '
	    invoke wcputw,dx::bx,cx,ax
	    .if di & _P_MINISTATUS
		mov al,2
		sub rect.rc_row,al
		mov bx,WORD PTR [si].S_PANEL.pn_xl
		sub [bx].S_XCELL.xl_rows,al
		.if di & _P_DRVINFO
		    sub rect.rc_row,al
		    sub [bx].S_XCELL.xl_rows,al
		    .if !(cflag & _C_HORIZONTAL)
			dec rect.rc_row
			dec [bx].S_XCELL.xl_rows
		    .endif
		.endif
		sub ax,ax
		cwd
		mov ah,at_background[B_Panel]
		or  ah,at_foreground[F_Frame]
		mov dl,rect.rc_col
		invoke rcframe,rect,dlwp,dx,ax
	    .endif
	    mov bx,xcell
	    mov ax,[bx].S_PRECT.p_putf
	    mov [si].S_PANEL.pn_putfcb,ax
	    lodm rect
	    stom xlrc
	    mov al,rectp.rc_col
	    add al,2
	    mov xlrc.rc_col,al
	    mov dl,12
	    mov dh,at_background[B_Panel]
	    or	dh,at_foreground[F_Frame]
	    sub cx,cx
	    mov cl,rect.rc_col
	    push di
	    les di,dlwp
	    mov ax,cx
	    add ax,ax
	    add di,ax
	    sub ax,ax
	    mov al,rectp.rc_col
	    mov si,ax
	    inc si
	    add si,si
	    and al,-2
	    sub al,2
	    .if [bx].S_PRECT.p_type == 0
		add di,ax
		.repeat
		    invoke wcputs,es::di,cx,cx,addr cp_name
		    add di,si
		    invoke rcframe,xlrc,dlwp,cx,dx
		    sub ax,ax
		    mov bx,ax
		    mov al,rectp.rc_col
		    inc ax
		    mov bl,xlrc.rc_x
		    add bx,ax
		    .break .if bh
		    add xlrc.rc_x,al
		    add ax,bx
		    .break .if ah
		    mov bl,xlrc.rc_col
		    add ax,bx
		    .break .if ah
		.until al > rect.rc_col
		mov al,rectp.rc_col
		add al,2
		.if al != rect.rc_col
		    invoke wcputs,es::di,cx,cx,addr cp_name
		.endif
	    .elseif [bx].S_PRECT.p_type == 2
		sub ax,[bx].S_PRECT.p_name
		add ax,di
		invoke wcputs,es::ax,cx,cx,addr cp_name
		mov ax,cx
		add ax,ax
		add di,ax
		sub di,14
		invoke wcputs,es::di,cx,cx,addr cp_date
		sub di,20
		invoke wcputs,es::di,cx,cx,addr cp_size
		sub xlrc.rc_col,9
		invoke rcframe,xlrc,dlwp,cx,dx
		sub xlrc.rc_col,11
		invoke rcframe,xlrc,dlwp,cx,dx
	    .elseif [bx].S_PRECT.p_type == 3
		sub ax,[bx].S_PRECT.p_name
		add ax,di
		invoke wcputs,es::ax,cx,cx,addr cp_name
		mov ax,cx
		add ax,ax
		add di,ax
		sub di,10
		invoke wcputs,es::di,cx,cx,addr cp_time
		sub di,16
		invoke wcputs,es::di,cx,cx,addr cp_date
		sub di,20
		invoke wcputs,es::di,cx,cx,addr cp_size
		sub xlrc.rc_col,6
		invoke rcframe,xlrc,dlwp,cx,dx
		sub xlrc.rc_col,9
		invoke rcframe,xlrc,dlwp,cx,dx
		sub xlrc.rc_col,11
		invoke rcframe,xlrc,dlwp,cx,dx
	    .endif
	    pop di
	    les bx,dlwp
	    sub ax,ax
	    mov dx,ax
	    mov al,rect.rc_col
	    add al,2
	    add ax,ax
	    add bx,ax
	    mov BYTE PTR es:[bx],':'
	    mov BYTE PTR es:[bx+2],25
	    mov bx,panel
	    mov bx,WORD PTR [bx].S_PANEL.pn_dialog
	    mov dl,[bx].S_DOBJ.dl_rect.rc_col
	    mov cx,WORD PTR [bx].S_DOBJ.dl_rect[2]
	    xor bx,bx
	    mov ax,6
	    mov ah,at_background[B_Panel]
	    or	ah,at_foreground[F_Frame]
	    invoke rcframe,cx::bx,dlwp,dx,ax
	    sub ax,ax
	    mov al,rect.rc_row
	    mov ah,rect.rc_col
	    les bx,dlwp
	    .if di & _P_MINISTATUS
		dec al
		mul ah
		add ax,ax
		add bx,ax
		.if di & _P_DRVINFO
		    mov BYTE PTR es:[bx+4],1Fh
		.else
		    mov BYTE PTR es:[bx+4],07h
		    sub ax,ax
		    mov al,rect.rc_col
		    add bx,ax
		    add bx,ax;word ptr dlwp
		    ;mov bx,ax
		    mov BYTE PTR es:[bx-6],1Fh
		.endif
	    .else
		mul ah
		add ax,ax
		add bx,ax
		mov BYTE PTR es:[bx-6],1Eh
	    .endif
	    mov si,panel
	    mov ax,cflag
	    and ax,_C_WIDEVIEW
	    .if !ax || (ax && si == cpanel)
		invoke dlshow,[si].S_PANEL.pn_dialog
		or di,_P_VISIBLE
		and di,not _P_WHIDDEN
	    .else
		or di,_P_WHIDDEN
	    .endif
	    mov [si].S_PANEL.pn_flag,di
	.endif
	push ax
	call comshow
	pop ax
	ret
prect_open ENDP

prect_open_ab PROC PUBLIC
	mov al,BYTE PTR cflag
	and al,_C_PANELID
	mov ax,offset spanela
	.if !ZERO?
	    mov ax,offset spanelb
	.endif
	mov cpanel,ax
	xor ax,ax
	.if flaga & _P_VISIBLE
	    mov ax,offset spanela
	    call prect_open
	.endif
	.if flagb & _P_VISIBLE
	    mov ax,offset spanelb
	    call prect_open
	.endif
	ret
prect_open_ab ENDP

prect_clear PROC pascal PUBLIC USES si di rect:DWORD, ptype:WORD
local result:WORD
	xor ax,ax
	mov al,_scrcol
	add ax,ax
	mov si,ax
	mov al,[bp+4]
	.if al < 3
	    add WORD PTR [bp+6],0201h
	    sub WORD PTR [bp+8],0302h
	    mov bx,[bp+6]
	    mov al,bh
	    HideMouseCursor
	    invoke getxyp,bx,ax
	    mov di,ax
	    mov es,dx
	    xor ax,ax
	    mov al,[bp+9]	; rect.rc_row
	    mov bx,ax
	    mov al,[bp+8]	; rect.rc_col
	    mov dx,ax
	    cld
	    mov [bp-2],di
	    mov cx,dx
	    mov al,[bp+4]
	    .if al == 1
		dec bx
		.if !ZERO?
		    .repeat
			.repeat
			    add di,si
			    mov ax,es:[di]
			    sub di,si
			    stosw
			.untilcxz
			mov cx,dx
			add [bp-2],si
			mov di,[bp-2]
			dec bx
		    .until ZERO?
		    inc bx
		.endif
	    .elseif al
		dec bx
		.if !ZERO?
		    mov ax,si
		    mul bl
		    add di,ax
		    mov [bp-2],di
		    .repeat
			.repeat
			    sub di,si
			    mov ax,es:[di]
			    add di,si
			    stosw
			.untilcxz
			mov cx,dx
			sub [bp-2],si
			mov di,[bp-2]
			dec bx
		    .until ZERO?
		    mov bx,1
		.endif
	    .endif
	    .repeat
		.repeat
		    mov ax,es:[di]
		    .if al != '³'
			mov al,20h
			mov es:[di],ax
		    .endif
		    add di,2
		.untilcxz
		add [bp-2],si
		mov di,[bp-2]
		mov cx,dx
		.break .if !bx
		dec bx
	    .until ZERO?
	    ShowMouseCursor
	.endif
	ret
prect_clear ENDP

;----------------------------------------------------------------------------

ypos	equ	[bp+4]
xpos	equ	[bp+4+2]
fblk	equ	[bp+4+4]

gettimex:
	mov	ax,[si].S_PANEL.pn_flag
	mov	pflag,ax
	sub	ax,ax
	mov	bx,WORD PTR [si].S_PANEL.pn_xl
	mov	al,[bx].S_DOBJ.dl_rect.rc_col
	add	al,xpos
	sub	al,5
	mov	timex,ax
	ret

fbputsize:
	push bx
	les bx,fblk
	mov ax,es:[bx].S_FBLK.fb_flag
	call fbcolor
	mov cx,ax
	mov ax,offset format_10lu
	.if es:[bx].S_FBLK.fb_flag & _A_VOLID
	    mov cl,at_foreground[F_Subdir]
	    or	cl,at_background[B_Panel]
	    mov ax,offset format_02lX
	.endif
	mov dx,timex
	sub dx,20
	invoke scputf,dx,ypos,cx,0,ds::ax,es:[bx].S_FBLK.fb_size
	pop bx
	ret

fbputsystem:
	les bx,fblk
	mov ax,es:[bx]
	.if al & (_A_HIDDEN or _A_SYSTEM)
	    call fbcolor
	    mov ah,al
	    mov al,'°'
	    invoke scputw,dx,ypos,1,ax
	.endif
	ret

fbputmax:
	push	bx
	mov	bl,al
	mov	al,'¯'
	mov	ah,at_foreground[F_Panel]
	or	ah,at_background[B_Panel]
	invoke	scputw,bx,ypos,1,ax
	pop	bx
	ret

fbputdate PROC pascal PRIVATE USES si di fb:DWORD, y:WORD
	les	bx,fb
	mov	di,es:[bx].S_FBLK.fb_flag
	mov	ax,WORD PTR es:[bx].S_FBLK.fb_time+2
	mov	si,ax
ifdef __ROT__
	.if di & _A_ROOTDIR
	    or di,_A_SYSTEM
	.endif
endif
	shr ax,9
	.if ax >= 20
	    sub ax,20
	.else
	    add ax,80
	.endif
	push	ax
	mov	ax,si
	shr	ax,5
	and	ax,000Fh
	push	ax
	mov	ax,si
	and	ax,001Fh
	push	ax
	mov	ax,di
	call	fbcolor
	mov	di,timex
	sub	di,9
	invoke	scputf,di,y,ax,0,addr cp_datefrm
	add	sp,6
	ret
fbputdate ENDP

fbputtime PROC pascal PRIVATE fb:DWORD, y:WORD
	les	bx,fb
	mov	ax,WORD PTR es:[bx].S_FBLK.fb_time
	shr	ax,5
	and	ax,003Fh
	push	ax
	mov	ax,WORD PTR es:[bx].S_FBLK.fb_time
	shr	ax,11
	and	ax,001Fh
	push	ax
	mov	ax,es:[bx].S_FBLK.fb_flag
ifdef __ROT__
	.if ax & _A_ROOTDIR
	    or ax,_A_SYSTEM
	.endif
endif
	call	fbcolor
	invoke	scputf,timex,y,ax,0,addr cp_timefrm
	add	sp,4
	ret
fbputtime ENDP

fbputdatetime:
	invoke	fbputtime,fblk,ypos
	invoke	fbputdate,fblk,ypos
	ret

fbput83 PROC pascal PRIVATE x:WORD, y:WORD, at:WORD, fname:DWORD
	invoke strext,fname
	push ax
	mov bx,timex
	add bx,2
	.if pflag & _P_DETAIL
	    sub bx,26
	.endif
	mov cx,bx
	sub cx,x
	sub cx,1
	.if ax
	    sub ax,WORD PTR fname
	    .if al <= cl
		mov cl,al
	    .endif
	.endif
	invoke scputs,x,y,at,cx,fname
	pop ax
	.if ax
	    push ax
	    inc ax
	    mov dx,WORD PTR fname+2
	    invoke scputs,bx,y,at,3,dx::ax
	    pop ax
	.endif
	ret
fbput83 ENDP

fbputsl PROC pascal PRIVATE fb:DWORD, x:WORD, y:WORD
	call gettimex
	les bx,fb
	mov ax,es:[bx].S_FBLK.fb_flag
	call fbcolor
	.if es:[bx].S_FBLK.fb_flag & _A_UPDIR
	    mov cl,al
	    invoke scputs,x,y,cx,0,addr es:[bx].S_FBLK.fb_name
	.else
	    invoke fbput83,x,y,ax,addr es:[bx].S_FBLK.fb_name
	    mov dx,bx
	    dec dx
	    call fbputsystem
	.endif
	ret
fbputsl ENDP

fbputsd PROC pascal PRIVATE fb:DWORD, x:WORD, y:WORD
	invoke fbputsl,fb,x,y
	les bx,fb
	mov ax,es:[bx]
	.if ax & _A_SUBDIR
	    mov dx,ax
	    call fbcolor
	    mov cl,al
	    mov bx,timex
	    sub bx,20
	    mov ax,offset cp_subdir
	    .if dx & _A_UPDIR
		mov ax,offset cp_updir
	    .endif
	    invoke scputs,bx,y,cx,0,ds::ax
	.else
	    call fbputsize
	.endif
	call fbputdatetime
	ret
fbputsd ENDP

fbloadbock:
	call gettimex
	lodm fblk
	mov  bx,ax
	add  ax,S_FBLK.fb_name
	mov  di,ax
	invoke strlen,dx::ax
	mov  si,ax
	mov  ax,es:[bx]
	mov  cx,ax
	call fbcolor
	ret

ifdef __LFN__

fbputll PROC pascal PRIVATE USES si di fb:DWORD, x:WORD, y:WORD
	call fbloadbock
	mov cx,x;17
	.if cx == 58
	    mov cx,19
	.else
	    .if cx == 20
		push ax
		add cx,18
		invoke getxyc,cx,ypos
		mov cx,17
		.if al == ' '
		    inc cx
		.endif
		pop ax
	    .else
		mov cx,17
	    .endif
	.endif
	invoke scputs,x,y,ax,cx,dx::di
	.if si > cx
	    mov ax,timex
	    add ax,3
	    call fbputmax
	.endif
	mov dx,timex
	add dx,4
	call fbputsystem
	ret
fbputll ENDP

fbputld PROC pascal PUBLIC USES si di fb:DWORD, x:WORD, y:WORD
	call fbloadbock
	shl ax,8
	or  si,ax
	mov bx,timex
	.if cflag & _C_HORIZONTAL	; Long Horizontal Detail
	    sub bx,20
	    .if cl & _A_UPDIR
		mov cx,si
		and si,00FFh
		mov dx,WORD PTR fb+2
		mov cl,ch
		invoke scputs,x,y,cx,si,dx::di
		invoke scputs,bx,y,cx,0,addr cp_updir
	    .else
		push cx
		sub bx,3
		mov ax,bx
		sub ax,x
		mov cx,si
		.if cl > al
		    mov cl,al
		    mov al,bl
		    call fbputmax
		.endif
		mov al,ch
		mov dx,WORD PTR fb+2
		invoke scputs,x,y,ax,cx,dx::di
		mov dx,bx
		inc dx
		push bx
		call fbputsystem
		pop dx
		pop ax
		add dx,3
		.if ax & _A_SUBDIR
		    mov cx,si
		    mov cl,ch
		    invoke scputs,dx,y,cx,0,addr cp_subdir
		.else
		    les bx,fb
		    call fbputsize
		.endif
	    .endif
	    call fbputdatetime
	.else			; Long Vertical Detail
	    add timex,6
	    .if cx & _A_UPDIR
		mov cx,si
		mov al,ch
		mov ch,0
		mov dx,WORD PTR fb+2
		invoke scputs,x,y,ax,cx,dx::di
	    .elseif cx & _A_SUBDIR
		mov ax,si
		mov al,ah
		sub bx,14
		invoke scputs,bx,y,ax,0,addr cp_subdir
		sub bx,6
		mov ax,bx
		sub ax,x
		mov cx,si
		.if cl > al
		    mov cl,al
		    mov al,bl
		    call fbputmax
		.endif
		mov al,ch
		mov ch,0
		mov dx,WORD PTR fb+2
		invoke scputs,x,y,ax,cx,dx::di
		mov dx,bx
		inc dx
		call fbputsystem
	    .else
		sub bx,14
		mov dx,bx
		call fbputsize
		mov ax,si
		mov al,ah
		push bx
		les bx,fb
		invoke fbput83,x,y,ax,addr es:[bx].S_FBLK.fb_name
		.if ax
		    mov si,ax
		    sub si,di
		.endif
		pop di
		sub di,6
		mov dx,di
		inc dx
		call fbputsystem
		mov ax,di
		sub ax,x
		mov cx,si
		.if cl > al
		    mov ax,di
		    call fbputmax
		.endif
	    .endif
	    invoke fbputdate,fb,y
	.endif
	ret
fbputld ENDP

endif ; __LFN__

fbputlw PROC pascal PRIVATE USES si di bx fb:DWORD, x:WORD, y:WORD
	call fbloadbock
	invoke scputs,x,y,ax,37,dx::di
	.if si >= 37
	    mov al,BYTE PTR x
	    add al,36
	    call fbputmax
	.endif
	mov  dl,BYTE PTR x
	add  dl,37
	call fbputsystem
	ret
fbputlw ENDP

fbputhw PROC pascal PRIVATE USES si di fb:DWORD, x:WORD, y:WORD
	call fbloadbock
	invoke scputs,x,y,ax,77,dx::di
	.if si >= 77
	    mov al,BYTE PTR x
	    add al,76
	    call fbputmax
	.endif
	mov dl,BYTE PTR x
	add dl,77
	call fbputsystem
	ret
fbputhw ENDP

fbputfile PROC pascal PUBLIC USES si di fb:DWORD, x:WORD, y:WORD
ifdef __LFN__
	invoke	fbputll,fb,x,y
else
	invoke	fbputsl,fb,x,y
endif
	sub	ax,ax
	mov	di,WORD PTR [si].S_PANEL.pn_dialog
	mov	al,[di].S_DOBJ.dl_rect.rc_col
	sub	al,7
	add	ax,x
	mov	timex,ax
	les	bx,fb
	mov	ax,es:[bx]
	mov	si,ax
	call	fbcolor
	mov	cx,ax
	lodm	es:[bx].S_FBLK.fb_size
	mov	bx,timex
	sub	bl,19
	.if si & _A_SUBDIR
	    and si,_A_UPDIR
	    mov ax,offset cp_subdir+1
	    .if !ZERO?
		mov ax,offset cp_updir+1
	    .endif
	    invoke scputs,bx,y,cx,7,ds::ax
	.else
	    mov si,cx
	    mov cl,2
	    push bx
	    xor bx,bx
	    .while dx >= 15
		mov al,ah
		mov ah,dl
		shr ax,cl
		mov dl,0
		shr dx,cl
		or  ah,dl
		mov dl,dh
		mov dh,0
		inc bx
	    .endw
	    mov cl,cp_strmega[bx]
	    pop bx
	    invoke scputf,bx,y,si,0,addr format_7luc,ax,dx,cx
	.endif
	call fbputdatetime
	ret
fbputfile ENDP

_DZIP	ENDS

	END
