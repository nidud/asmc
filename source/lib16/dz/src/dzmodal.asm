; DZMODAL.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include string.inc
include conio.inc
include mouse.inc
include keyb.inc
include tinfo.inc

PUBLIC	MOBJ_STATUSLINE

extrn	com_info:DWORD
extrn	menus_getevent:near
scroll_delay PROTO _CType

S_MSOBJ STRUC
	mo_rect dd ?
	mo_proc p? ?
  ifndef __l__
	mo_align8 dw ?
  endif
S_MSOBJ ENDS

_DATA	segment

MSOBJ	macro	rc, name
	dd	rc
	dw	offset name
	dw	SEG _DZIP
	endm

MOBJ_STLCTRL label WORD
	MSOBJ	01091801h, cmatoggle
	MSOBJ	0109180Ch, cmbtoggle
	MSOBJ	01071817h, cmview
	MSOBJ	01071820h, cmedit
	MSOBJ	01071829h, cmcname
  ifdef __TE__
	MSOBJ	01091832h, teoption
  else
	MSOBJ	01091832h, notsup
  endif
	MSOBJ	0109183Ch, cmscreen
	MSOBJ	01091846h, cmsystem

MOBJ_STATUSLINE label WORD
	MSOBJ	01071801h, cmhelp
	MSOBJ	0106180Ah, cmrename
	MSOBJ	01071812h, cmview
	MSOBJ	0107181Bh, cmedit
	MSOBJ	01071824h, cmcopy
	MSOBJ	0107182Dh, cmmove
	MSOBJ	01071836h, cmmkdir
	MSOBJ	01071840h, cmdelete
	MSOBJ	01071848h, cmexit

cp_stlctrl label BYTE
	db '&F&1 PanelA  &F&2 PanelB  &F&3 View  &F&4 Edit  '
	db '&F&5 Name  &F&6 Editor &F&7 Screen &F&8 System',0

cp_space db ' ',0

_DATA	ENDS

_DZIP	segment

comaddstring PROC pascal PRIVATE string:DWORD
	xor ax,ax
	les bx,DLG_Commandline
	.if BYTE PTR es:[bx] & _D_ONSCR
	    mov bx,WORD PTR com_info
	    .if BYTE PTR [bx] != 0
		invoke strtrim,com_info
		invoke strcat,com_info,addr cp_space
	    .endif
	    invoke strcat,com_info,string
	    invoke strcat,dx::ax,addr cp_space
	    invoke comevent,KEY_END
	.endif
	ret
comaddstring ENDP

cmcfblktocmd PROC _CType PUBLIC
	mov ax,cpanel
	.if panel_curobj()
	    invoke comaddstring,dx::ax
	.endif
	ret
cmcfblktocmd ENDP

cmpathatocmd PROC _CType PUBLIC
	mov bx,panela
	mov ax,[bx]
	add ax,S_PATH.wp_path
	invoke comaddstring,ds::ax
	ret
cmpathatocmd ENDP

cmpathbtocmd PROC _CType PUBLIC
	mov bx,panela
	mov ax,[bx]
	add ax,S_PATH.wp_path
	invoke comaddstring,ds::ax
	ret
cmpathbtocmd ENDP

ifdef __MOUSE__

PANEL_SCROLLUP PROC PRIVATE
	push	bp
	mov	bp,sp
	mov	ax,cpanel
	cmp	ax,[bp+4]
	jnz	scrollup_03
    scrollup_00:
	xor	ax,ax
	mov	bx,[bp+4]
	cmp	[bx].S_PANEL.pn_cel_index,ax
	jz	scrollup_01
	mov	[bx].S_PANEL.pn_cel_index,ax
	mov	ax,bx
	call	pcell_update
	call	scroll_delay
	jmp	scrollup_02
    scrollup_01:
	push	WORD PTR [bp+4]
	push	KEY_UP
	call	panel_event
    scrollup_02:
	call	scroll_delay
	call	mousep
	cmp	ax,1
	je	scrollup_00
	mov	ax,1
	jmp	scrollup_04
    scrollup_03:
	mov	ax,[bp+4]
	call	panel_setactive
	xor	ax,ax
    scrollup_04:
	pop	bp
	ret	2
PANEL_SCROLLUP ENDP

PANEL_SCROLLDN PROC PRIVATE
	push	bp
	mov	bp,sp
	mov	ax,cpanel
	cmp	ax,[bp+4]
	jnz	scrolldn_03
    scrolldn_00:
	mov	bx,[bp+4]
	mov	ax,[bx].S_PANEL.pn_cel_count
	dec	ax
	cmp	[bx].S_PANEL.pn_cel_index,ax
	jnl	scrolldn_01
	mov	[bx].S_PANEL.pn_cel_index,ax
	mov	ax,bx
	call	pcell_update
	call	scroll_delay
	jmp	scrolldn_02
    scrolldn_01:
	push	WORD PTR [bp+4]
	push	KEY_DOWN
	call	panel_event
    scrolldn_02:
	call	scroll_delay
	call	mousep
	cmp	ax,1
	je	scrolldn_00
	mov	ax,1
	jmp	scrolldn_04
    scrolldn_03:
	mov	ax,[bp+4]
	call	panel_setactive
	xor	ax,ax
    scrolldn_04:
	pop	bp
	ret	2
PANEL_SCROLLDN ENDP

endif

CTRLEVENT PROC PRIVATE
	push	bp
	mov	bp,sp
	sub	sp,168
	push	si
	push	di
	les	bx,keyshift
	mov	al,es:[bx]
	and	al,KEY_ALT
	jz	ctrlevent_00
	call	cmquicksearch
	jmp	ctrlevent_06
    ctrlevent_00:
	xor	ax,ax
	test	cflag,_C_STATUSLINE
	jz	ctrlevent_01
	invoke	cursorget,addr [bp-168]
	call	cursoroff
	invoke	wcpushst,addr [bp-164],addr cp_stlctrl
	jmp	ctrlevent_03
    ctrlevent_01:
	call	tupdate
	call	getkey
	mov	di,ax
	or	ax,ax
	jnz	ctrlevent_04
  ifdef __MOUSE__
	call	mousep
	jz	ctrlevent_03
	call	mousey
	mov	[bp-4],ax
	mov	dx,ax
	call	mousex
	mov	[bp-2],ax
	mov	cx,8
	mov	bx,offset MOBJ_STLCTRL
	mov	di,MOUSECMD
	call	statusline_xy
	jz	ctrlevent_02
	call	[bx].S_MSOBJ.mo_proc
    ctrlevent_02:
	call	msloop
	jmp	ctrlevent_04
  endif
    ctrlevent_03:
	les	bx,keyshift
	mov	al,es:[bx]
	and	al,00001100B
	cmp	al,KEY_CTRL
	je	ctrlevent_01
    ctrlevent_04:
	test	cflag,_C_STATUSLINE
	jz	ctrlevent_05
	invoke	wcpopst,addr [bp-164]
	invoke	cursorset,addr [bp-168]
    ctrlevent_05:
	mov	ax,di
    ctrlevent_06:
	pop	di
	pop	si
	mov	sp,bp
	pop	bp
	ret
CTRLEVENT ENDP

ifdef __MOUSE__

MOUSEEVENT PROC PRIVATE
	push	si
	push	di
	call	mousep
	jz	mouseevent_end
	call	mousex
	mov	di,ax
	call	mousey
	mov	si,ax
  ifdef __CAL__
	test	cflag,_C_MENUSLINE
	jz	ypos
	test	ax,ax
	jnz	ypos
	mov	al,_scrcol
	sub	al,5
	cmp	di,ax
	jl	@F
	invoke	cmscreen
	jmp	mouseevent_end
     @@:
	sub	ax,13
	cmp	di,ax
	jle	ypos
	invoke	cmcalendar
	jmp	mouseevent_end
    ypos:
  endif
	test	si,si
	jnz	@F
	test	cflag,_C_MENUSLINE
	jnz	@F
	cmp	di,56
	ja	@F
	call	cmxormenubar
	call	menus_getevent
	call	cmxormenubar
	jmp	mouseevent_end
      @@:
	mov	cx,9
	mov	bx,offset MOBJ_STATUSLINE
	mov	ax,di
	mov	dx,si
	call	statusline_xy
	jz	mouseevent_do
	call	msloop
	call	[bx].S_MSOBJ.mo_proc
	jmp	mouseevent_end
    mouseevent_do:
	invoke	panel_xycmd,panela,di,si
	mov	bx,panela
	or	ax,ax
	jnz	XY1_INSIDE
    mouseevent_B:
	invoke	panel_xycmd,panelb,di,si
	mov	bx,panelb
	or	ax,ax
	jnz	XY1_INSIDE
	jmp	mouseevent_end
    XY1_INSIDE:
	dec	ax
	jz	XY2_FILE
	dec	ax
	jnz	XY3_MOVEDOWN
    XY2_FILE:
	push	bx
	push	di
	push	si
	mov	ax,bx
	call	panel_setactive
	call	pcell_setxy
	jmp	mouseevent_null
    XY3_MOVEDOWN:
	dec	ax
	jnz	XY4_MOVEUP
	push	bx
	call	PANEL_SCROLLDN
	jmp	mouseevent_null
    XY4_MOVEUP:
	dec	ax
	jnz	XY5_NEWDISK
	push	bx
	call	PANEL_SCROLLUP
	jmp	mouseevent_null
    XY5_NEWDISK:
	dec	ax
	jnz	XY6_MINISTATUS
	cmp	bx,panela
	je	XY5_NEWDISKA
	call	cmbchdrv
	jmp	mouseevent_null
      XY5_NEWDISKA:
	call	cmachdrv
	jmp	mouseevent_null
    XY6_MINISTATUS:
	dec	ax
	jnz	XY7_CONFIG
	mov	ax,bx
	call	panel_xormini
	jmp	mouseevent_null
    XY7_CONFIG:
	dec	ax
	jnz	XY8_DRVINFO
	cmp	bx,panela
	je	XY7_CONFIGA
	call	cmbfilter
	jmp	mouseevent_null
      XY7_CONFIGA:
	call	cmafilter
	jmp	mouseevent_null
    XY8_DRVINFO:
	dec	ax
	jnz	mouseevent_B
	mov	ax,bx
	call	panel_xorinfo
    mouseevent_null:
	xor	ax,ax
    mouseevent_end:
	pop	di
	pop	si
	ret
MOUSEEVENT ENDP

endif

panel_toggleact PROC PUBLIC
	call panel_stateab
	.if !ZERO?
	    call historysave
	    call getpanelb
	    mov bx,ax
	    call panel_setactive
	    mov ax,1
	.endif
	test ax,ax
	ret
panel_toggleact ENDP

globalcmd PROC PRIVATE
	mov	bx,offset global_key
      @@:
	mov	ax,[bx].S_GLCMD.gl_key
	or	ax,ax
	jz	@F
	mov	dx,bx
	add	bx,SIZE S_GLCMD
	cmp	ax,si
	jne	@B
	mov	bx,dx
	call	[bx].S_GLCMD.gl_proc
	mov	ax,1
      @@:
	ret
globalcmd ENDP

dzmodal PROC PUBLIC
	push si
	.while mainswitch == 0
	    call tupdate
	    les bx,keyshift
	    .if BYTE PTR es:[bx] & KEY_CTRL
		call ctrlevent
	    .else
		call menus_getevent
	    .endif
	    mov si,ax
	    .if ax == KEY_ENTER || ax == KEY_KPENTER
		.if cflag & _C_COMMANDLINE && com_base
		    .if doskeysave()
			invoke command,addr com_base
		    .endif
		    .if !ax
			invoke comevent,KEY_END
		    .endif
		    .continue
		.endif
	    .endif
	    .if cflag & _C_COMMANDLINE && com_base
		.if comevent(si)
		    .continue
		.endif
	    .endif
	    call cpanel_state
	    .if !ZERO?
		.if panel_event(cpanel,si)
		    .continue
		.endif
	    .endif
	    .break .if mainswitch
	  ifdef __MOUSE__
	    .if si == MOUSECMD
		call mouseevent
		call msloop
		.continue
	    .endif
	  endif
	    .if si == KEY_TAB
		call panel_toggleact
		.continue
	    .endif
	    call globalcmd
	    .if !ax
		invoke comevent,si
	    .else
		call msloop
		.continue
	    .endif
	    .if si == KEY_KPPLUS || si == KEY_KPMIN || si == KEY_KPSTAR
		invoke comevent,si
	    .endif
	.endw
	pop si
	ret
dzmodal ENDP

_DZIP	ENDS

	END
