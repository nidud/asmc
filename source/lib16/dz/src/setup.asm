; SETUP.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include dir.inc
include dos.inc
include io.inc
include iost.inc
include string.inc
include stdlib.inc
include conio.inc
include mouse.inc
include errno.inc
ifdef __TE__
include tinfo.inc
include stdio.inc
include keyb.inc
include alloc.inc
endif

PUBLIC	cmsystem
PUBLIC	cmscreen
PUBLIC	cmpanel
PUBLIC	cmconfirm
PUBLIC	cmcompression
PUBLIC	cmoptions
ifdef __TE__
PUBLIC	teoption
extrn	IDD_TEOptions:DWORD
endif

PUBLIC	format_u

_DATA	segment
format_u	db '%u',0
cf_panel	db 0
cf_panel_upd	dw 0
cp_cmdreload	db 'ECHO.',0
cp_pal		db '*.pal',0

color_Mono S_COLOR < \
	<0Fh,0Fh,0Fh,0Fh,0Fh,0Fh,0Fh,0Fh,0Fh,0Fh,0Fh,0Fh,0Fh,0Fh,0Fh,0Fh>,
	<00h,00h,00h,00h,00h,70h,70h,00h,70h,70h,00h,00h,00h,00h,07h,07h>,
	<0,1,2,3,4,5,20,7,56,57,58,59,60,61,62,63>>
color_Black S_COLOR < \
	<07h,0Fh,0Fh,07h,08h,08h,00h,07h,08h,07h,0Ah,0Bh,0Fh,0Bh,0Bh,0Bh>,
	<00h,00h,00h,00h,00h,10h,10h,00h,10h,10h,00h,00h,00h,00h,07h,07h>,
	<0,1,2,3,4,5,20,7,56,57,58,59,60,61,62,63>>
color_Blue S_COLOR < \
	<00h,0Fh,0Fh,07h,08h,00h,00h,07h,08h,00h,0Ah,0Bh,00h,0Fh,0Fh,0Fh>,
	<00h,10h,70h,70h,40h,30h,30h,70h,30h,30h,00h,00h,10h,10h,07h,07h>,
	<0,1,2,3,4,5,20,7,56,57,58,59,60,61,62,63>>
color_Navy S_COLOR < \
	<00h,0Fh,0Fh,07h,08h,00h,06h,07h,08h,09h,0Ah,0Bh,0Ch,0Dh,0Eh,0Fh>,
	<00h,10h,20h,30h,40h,50h,60h,70h,70h,70h,00h,00h,10h,10h,07h,07h>,
	<0,136,7,7,4,63,3,7,56,0,58,59,0,4,63,63>>

_DATA	ENDS

_DZIP	segment

cmsystem PROC _CType USES si di
local DLG_DZSystemOptions:DWORD
local ifs:BYTE
	mov	al,_ifsmgr
	mov	ifs,al
	invoke	rsopen,IDD_DZSystemOptions
	jz	cmsystem_end
	stom	DLG_DZSystemOptions
	mov	cx,_O_FLAGB
	mov	ax,console
	test	ax,CON_IMODE
	jz	@F
	or	es:[bx+8*16],cl
     @@:
	test	ax,CON_REVGA
	jz	@F
	or	es:[bx+9*16],cl
     @@:
	mov	ax,cflag
	test	ax,_C_DELHISTORY
	jz	@F
	or	es:[bx+10*16],cl
     @@:
	test	ax,_C_ESCUSERSCR
	jz	@F
	or	es:[bx+11*16],cl
     @@:
	mov	ax,console
	invoke	tosetbitflag,es:[bx].S_DOBJ.dl_object,7,_O_FLAGB,ax::ax
	invoke	dlinit,DLG_DZSystemOptions
	invoke	rsevent,IDD_DZSystemOptions,DLG_DZSystemOptions
	mov	si,ax
	invoke	togetbitflag,es:[bx].S_DOBJ.dl_object,11,_O_FLAGB
	invoke	dlclose,DLG_DZSystemOptions
	mov	ax,si
	test	ax,ax
	jz	cmsystem_end
	mov	ax,dx
	mov	dx,cflag
	and	dx,not (_C_DELHISTORY or _C_ESCUSERSCR)
	.if ah & 2	; Auto Delete History
	    or dx,_C_DELHISTORY
	.endif
	.if ah & 4	; Use Esc for user screen
	    or dx,_C_ESCUSERSCR
	.endif
	mov	cflag,dx
	mov	dx,console
	and	dx,not 307Fh
	.if (ah & 1)	; Restore VGA palette on exit
	    or dx,CON_REVGA
	.endif
	.if (al & 80h)	; Init screen mode on startup
	    or dx,CON_IMODE
	.endif
	and	al,3Fh
	or	dl,al
	mov	console,dx
  ifdef __MOUSE__
	test	dl,CON_MOUSE
	jz	cmsystem_mouse
	call	mouseoff
	call	mouseon
  endif
	jmp	cmsystem_lfn
    cmsystem_mouse:
  ifdef __MOUSE__
	call	mouseoff
	mov	al,0
	call	mouseset
  endif
    cmsystem_lfn:
  ifdef __LFN__
	mov	dl,_ifsmgr
	test	BYTE PTR console,CON_IOLFN
	jnz	@F
  endif
	xor	ax,ax
  ifdef __LFN__
	mov	_ifsmgr,al
  endif
	and	path_a.wp_flag,not _W_LONGNAME
	and	path_b.wp_flag,not _W_LONGNAME
	jmp	cmsystem_cf
    @@:
  ifdef __LFN__
	cmp	ifs,0
	je	cmsystem_nolfn
	mov	al,ifs
	mov	_ifsmgr,al
	or	path_a.wp_flag,_W_LONGNAME
	or	path_b.wp_flag,_W_LONGNAME
	cmp	dl,al
	je	cmsystem_exit
  endif
    cmsystem_cf:
	cmp	cf_panel,1
	jne	cmsystem_updpn
	mov	cf_panel_upd,1
	jmp	cmsystem_exit
    cmsystem_nolfn:
	or	dx,dx
	jz	cmsystem_exit
	jmp	cmsystem_cf
    cmsystem_updpn:
	call	redraw_panels
    cmsystem_exit:
	mov	ax,1
    cmsystem_end:
	ret
cmsystem ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

ID_MEUSLINE	equ 1*16
ID_USEDATE	equ 2*16
ID_USETIME	equ 3*16
ID_USELDATE	equ 4*16
ID_USELTIME	equ 5*16
ID_COMMANDLINE	equ 6*16
ID_STAUSLINE	equ 7*16
ID_USECOLOR	equ 8*16
ID_PALETTE	equ 9*16
ID_ATTRIB	equ 10*16
ID_STANDARD	equ 11*16
ID_LOAD		equ 12*16
ID_SAVE		equ 13*16

event_usecolor PROC _CType PRIVATE USES si bx
	les bx,tdialog
	mov si,es:[bx+ID_USECOLOR]
	call dlcheckevent
	push ax
	les bx,tdialog
	mov ax,es:[bx+ID_USECOLOR]
	and ax,_O_FLAGB
	and si,_O_FLAGB
	.if ax != si
	    .if ax != _O_FLAGB
		call resetpal
		and BYTE PTR console,not CON_COLOR
	    .else
		or BYTE PTR console,CON_COLOR
		invoke loadpal,addr at_palett
	    .endif
	.endif
	pop ax
	ret
event_usecolor ENDP

event_reload PROC _CType PRIVATE
	invoke command,addr cp_cmdreload
	mov ax,_C_ESCAPE
	ret
event_reload ENDP

event_loadcolor PROC _CType PRIVATE USES si
	.if wgetfile(addr cp_pal,3)
	    push ax
	    invoke osread,ax,addr at_foreground,SIZE S_COLOR
	    mov si,ax
	    call close
	    mov ax,_C_NORMAL
	    .if si == SIZE S_COLOR
		call event_reload
	    .endif
	.endif
	ret
event_loadcolor ENDP

event_savecolor PROC _CType PRIVATE
	.if wgetfile(addr cp_pal,2)
	    push ax
	    invoke oswrite,ax,addr at_foreground,SIZE S_COLOR
	    call close
	.endif
	mov ax,_C_NORMAL
	ret
event_savecolor ENDP

ifdef __AT__

event_editat PROC _CType PRIVATE
	call	editattrib
	test	ax,ax
	jnz	event_reload
	mov	ax,_C_NORMAL
	ret
event_editat ENDP

event_editpal PROC _CType PRIVATE
	call	editpal
	mov	ax,_C_NORMAL
	ret
event_editpal ENDP

endif

event_standard PROC _CType PRIVATE USES bx
	les bx,tdialog
	mov ax,es:[bx+4]
	add ax,0B0Ch
	mov bx,WORD PTR IDD_DZDefaultColor
	mov [bx+6],ax
	invoke rsmodal,IDD_DZDefaultColor
	.if ax == 4
	    mov ax,offset color_Mono
	.elseif ax == 3
	    call resetpal
	    mov ax,offset color_Black
	.elseif ax == 2
	    mov ax,offset color_Navy
	    or	BYTE PTR console,CON_COLOR
	.elseif ax == 1
	    call resetpal
	    mov ax,offset color_Blue
	.else
	    sub ax,ax
	.endif
	.if ax
	    mov dx,ds
	    invoke memcpy,addr at_foreground,dx::ax,SIZE S_COLOR
	    call event_reload
	.else
	    inc ax
	.endif
	ret
event_standard ENDP

cmscreen PROC _CType USES si di
local DLG_DZScreenOptions:DWORD
	.if rsopen(IDD_DZScreenOptions)
	    stom DLG_DZScreenOptions
	    mov di,ax
	    mov dl,_O_FLAGB
	    mov ax,cflag
	    .if ax & _C_MENUSLINE
		or es:[di+ID_MEUSLINE],dl
	    .endif
	    .if ax & _C_COMMANDLINE
		or es:[di+ID_COMMANDLINE],dl
	    .endif
	    .if ax & _C_STATUSLINE
		or es:[di+ID_STAUSLINE],dl
	    .endif
	    mov ax,console
	    .if ax & CON_UDATE
		or es:[di+ID_USEDATE],dl
	    .endif
	    .if ax & CON_LDATE
		or es:[di+ID_USELDATE],dl
	    .endif
	    .if ax & CON_UTIME
		or es:[di+ID_USETIME],dl
	    .endif
	    .if ax & CON_LTIME
		or es:[di+ID_USELTIME],dl
	    .endif
	    .if ax & CON_COLOR
		or es:[di+ID_USECOLOR],dl
	    .endif
	    movp es:[di].S_TOBJ.to_proc[ID_USECOLOR],event_usecolor
ifdef __AT__
	    movp es:[di].S_TOBJ.to_proc[ID_PALETTE],event_editpal
	    movp es:[di].S_TOBJ.to_proc[ID_ATTRIB],event_editat
else
	    or es:[di].S_TOBJ.to_flag[ID_PALETTE],_O_STATE
	    or es:[di].S_TOBJ.to_flag[ID_ATTRIB],_O_STATE
endif
	    movp es:[di].S_TOBJ.to_proc[ID_STANDARD],event_standard
	    movp es:[di].S_TOBJ.to_proc[ID_LOAD],event_loadcolor
	    movp es:[di].S_TOBJ.to_proc[ID_SAVE],event_savecolor
	    invoke dlinit,DLG_DZScreenOptions
	    invoke rsevent,IDD_DZScreenOptions,DLG_DZScreenOptions
	    mov si,ax
	    lodm DLG_DZScreenOptions
	    add ax,16
	    invoke togetbitflag,dx::ax,8,_O_FLAGB
	    invoke dlclose,DLG_DZScreenOptions	; return bit-flag in DX
	    mov ax,si
	    mov si,cflag
	    .if ax
		mov ax,dx
		mov dx,console
		and dx,not (CON_LTIME or CON_LDATE or CON_UTIME or CON_UDATE or CON_COLOR)
		.if al & 02h
		    or dx,CON_UDATE
		.endif
		.if al & 08h
		    or dx,CON_LDATE
		.endif
		.if al & 04h
		    or dx,CON_UTIME
		.endif
		.if al & 10h
		    or dx,CON_LTIME
		.endif
		.if al & 40h
		    or dx,CON_COLOR
		.endif
		and si,not (_C_MENUSLINE or _C_STATUSLINE or _C_COMMANDLINE)
		.if al & 01h
		    or si,_C_MENUSLINE
		.endif
		.if al & 20h
		    or si,_C_COMMANDLINE
		.endif
		.if al & 30h
		    or si,_C_STATUSLINE
		.endif
		.if console != dx
		    mov console,dx
		    .if cflag & _C_MENUSLINE
			.if !(dx & CON_UTIME)
			    invoke scputw,72,0,8,' '
			.endif
			.if !(dx & CON_UDATE)
			    invoke scputw,63,0,8,' '
			.endif
		    .endif
		.endif
		.if cflag != si
		    mov cflag,si
		    .if cf_panel == 1
			invoke dlhide,tdialog
		    .endif
		    call apiupdate
		    .if cf_panel == 1
			invoke dlshow,tdialog
		    .endif
		    jmp @F
		.endif
	    .else
	    @@:
		mov ax,_C_ESCAPE
		.if mainswitch != 1
		    mov ax,_C_NORMAL
		.endif
	    .endif
	.endif
	ret
cmscreen ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

cmpanel PROC _CType
	push	si
	invoke	rsopen, IDD_DZPanelOptions
	jz	cmpanel_end
	push	dx
	push	ax
	pushm	IDD_DZPanelOptions
	push	dx
	push	ax
	push	dx
	push	ax
	mov	dl,_O_FLAGB
	mov	ax,cflag
	test	ax,_C_INSMOVDN
	jz	cmpanel_select_sub
	or	es:[bx+1*16],dl
    cmpanel_select_sub:
	test	ax,_C_SELECTDIR
	jz	cmpanel_sort_sub
	or	es:[bx+2*16],dl
    cmpanel_sort_sub:
	test	ax,_C_SORTDIR
	jz	cmpanel_clr
	or	es:[bx+3*16],dl
    cmpanel_clr:
	test	ax,_C_CDCLRDONLY
	jz	cmpanel_dlg
	or	es:[bx+4*16],dl
    cmpanel_dlg:
	call	dlinit
	call	rsevent
	mov	si,ax
	push	es
	push	4+16
	push	4
	push	_O_FLAGB
	call	togetbitflag
	call	dlclose
	mov	ax,si
	or	ax,ax
	jz	cmpanel_end
	mov	ax,dx
	and	path_a.wp_flag,not _W_SORTSUB
	and	path_b.wp_flag,not _W_SORTSUB
	mov	dx,cflag
	and	dx,not (_C_INSMOVDN or _C_SELECTDIR or _C_SORTDIR or _C_CDCLRDONLY)
	test	al,01h
	jz	cmpanel_select_sub?
	or	dx,_C_INSMOVDN
    cmpanel_select_sub?:
	test	al,02h
	jz	cmpanel_sort?
	or	dx,_C_SELECTDIR
    cmpanel_sort?:
	test	al,04h
	jz	cmpanel_clr?
	or	dx,_C_SORTDIR
	or	path_a.wp_flag,_W_SORTSUB
	or	path_b.wp_flag,_W_SORTSUB
    cmpanel_clr?:
	test	al,08h
	jz	cmpanel_set
	or	dx,_C_CDCLRDONLY
    cmpanel_set:
	cmp	cflag,dx
	je	cmpanel_one
	mov	cflag,dx
	cmp	cf_panel,1
	jne	cmpanel_upd
	mov	cf_panel_upd,1
	jmp	cmpanel_one
    cmpanel_upd:
	call	redraw_panels
    cmpanel_one:
	mov	ax,1
    cmpanel_end:
	pop	si
	ret
cmpanel ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

cmconfirm PROC _CType
	push	si
	invoke	rsopen, IDD_DZConfirmations
	jz	cmconfirm_end
	push	dx
	push	ax
	pushm	IDD_DZConfirmations
	push	dx
	push	ax
	push	dx
	push	ax
	push	dx
	add	ax,16
	push	ax
	push	7
	push	_O_FLAGB
	push	ax
	mov	ax,config.c_confirm
	push	ax
	call	tosetbitflag
	call	dlinit
	call	rsevent
	mov	si,ax
	push	es
	push	4+16
	push	7
	push	_O_FLAGB
	call	togetbitflag
	call	dlclose
	or	si,si
	jz	cmconfirm_end
	mov	config.c_confirm,dx
    cmconfirm_end:
	xor	ax,ax
	pop	si
	ret
cmconfirm ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

cmcompression PROC _CType
	invoke	rsopen, IDD_DZCompression
	jz	compression_end
	push	dx
	push	ax
	pushm	IDD_DZCompression
	push	dx
	push	ax
	push	dx
	push	ax
	mov	ax,compresslevel
	cmp	al,9
	jna	compression_level
	mov	al,6
	mov	compresslevel,ax
    compression_level:
	inc	ax
	shl	ax,4
	push	bx
	add	bx,ax
	or	es:[bx].S_DOBJ.dl_flag,_O_RADIO
	pop	bx
	test	compressflag,_C_ZINCSUBDIR
	jz	compression_event
	or	es:[bx].S_DOBJ.dl_flag[11*16],_O_FLAGB
    compression_event:
	call	dlinit
	call	rsevent
	or	ax,ax
	jz	compression_end
	xor	ax,ax
	test	es:[bx].S_DOBJ.dl_flag[11*16],_O_FLAGB
	jz	compression_flag
	or	al,_C_ZINCSUBDIR
    compression_flag:
	mov	compressflag,ax
	xor	ax,ax
    compression_loop:
	add	bx,SIZE S_TOBJ
	test	es:[bx].S_DOBJ.dl_flag,_O_RADIO
	jnz	compression_lev
	inc	ax
	cmp	ax,10
	jb	compression_loop
	mov	al,6
    compression_lev:
	mov	compresslevel,ax
    compression_end:
	call	dlclose
	ret
cmcompression ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

ifdef __TE__

ID_USEMENUS	equ 1*16
ID_OPTIMALFILL	equ 2*16
ID_OVERWRITE	equ 3*16
ID_USEINDENT	equ 4*16
ID_USESTYLE	equ 5*16
ID_USETABS	equ 6*16
ID_USEBAKFILE	equ 7*16
ID_USECRLF	equ 8*16
ID_TABSIZE	equ 9*16
ID_LINESIZE	equ 10*16
ID_EMSPAGES	equ 11*16

teoption PROC _CType USES si di bx
	.if rsopen(IDD_TEOptions)
	    push dx
	    push ax
	    pushm IDD_TEOptions
	    push dx
	    push ax
	    push dx
	    push ax
	    push dx
	    push ax
	    mov ax,tetabsize
	    invoke sprintf,es:[bx].S_TOBJ.to_data[ID_TABSIZE],addr format_u,ax
	    mov ax,128
	    mov cx,telsize
	    shl ax,cl
	    invoke sprintf,es:[bx].S_TOBJ.to_data[ID_LINESIZE],addr format_u,ax
	    invoke sprintf,es:[bx].S_TOBJ.to_data[ID_EMSPAGES],addr format_u,tepages
	    mov ax,teflag
	    shr ax,5
	    invoke tosetbitflag,es:[bx].S_DOBJ.dl_object,8,_O_FLAGB,ax::ax
	    call dlshow
	    call dlinit
	    .if rsevent()
		invoke togetbitflag,es:[bx].S_DOBJ.dl_object,8,_O_FLAGB
		shl ax,5
		mov teflag,ax
		invoke strtol,es:[bx].S_TOBJ.to_data[ID_TABSIZE]
		mov ah,al
		mov al,128
		.repeat
		    shl ah,1
		    .break .if CARRY?
		    shr al,1
		.until ZERO?
		.if al > TIMAXTABSIZE
		    mov al,TIMAXTABSIZE
		.elseif al < 2
		    mov al,2
		.endif
		mov BYTE PTR tetabsize,al
		invoke strtol,es:[bx].S_TOBJ.to_data[ID_EMSPAGES]
		.if ax >= EMSMINPAGES
		    mov tepages,ax
		.endif
		invoke strtol,es:[bx].S_TOBJ.to_data[ID_LINESIZE]
ifdef __3__
		bsr ax,ax
else
		xor cx,cx
		.while ax
		    shr ax,1
		    inc cx
		.endw
		mov ax,cx
endif
		.if ax > 10
		    mov ax,10
		.elseif ax < 7
		    mov ax,7
		.elseif ax
		.endif
		sub ax,7
		mov telsize,ax
	    .endif
	    call dlclose
	    mov ax,dx
	.endif
	ret
teoption ENDP

endif

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

cmoptions PROC _CType
	push	si
	mov	cf_panel,1
	mov	cf_panel_upd,0
	invoke	rsopen, IDD_DZConfiguration
	jz	cmoptions_03
	push	dx
	push	ax
	pushm	IDD_DZConfiguration
	push	dx
	push	ax
	push	dx
	push	ax
	movl	ax,cs
	movl	WORD PTR es:[bx].S_TOBJ.to_proc[1*16+2],ax
	movl	WORD PTR es:[bx].S_TOBJ.to_proc[2*16+2],ax
	movl	WORD PTR es:[bx].S_TOBJ.to_proc[3*16+2],ax
	movl	WORD PTR es:[bx].S_TOBJ.to_proc[5*16+2],ax
	movl	WORD PTR es:[bx].S_TOBJ.to_proc[6*16+2],ax
  ifdef __TE__
	movl	WORD PTR es:[bx].S_TOBJ.to_proc[4*16+2],ax
	mov	WORD PTR es:[bx].S_TOBJ.to_proc[4*16],offset teoption
  else
	movl	WORD PTR es:[bx].S_TOBJ.to_proc[4*16+2],SEG _TEXT
	mov	WORD PTR es:[bx].S_TOBJ.to_proc[4*16],offset notsup
  endif
	mov	WORD PTR es:[bx].S_TOBJ.to_proc[5*16],offset cmconfirm
	mov	WORD PTR es:[bx].S_TOBJ.to_proc[6*16],offset cmcompression
	mov	WORD PTR es:[bx].S_TOBJ.to_proc[1*16],offset cmsystem
	mov	WORD PTR es:[bx].S_TOBJ.to_proc[2*16],offset cmscreen
	mov	WORD PTR es:[bx].S_TOBJ.to_proc[3*16],offset cmpanel
	test	cflag,_C_AUTOSAVE
	jz	@F
	or	BYTE PTR es:[bx+7*16],_O_FLAGB
    @@:
	call	dlinit
	call	rsevent
	mov	si,es:[bx+7*16]
	call	dlclose
	mov	cf_panel_upd,0
	add	dx,cf_panel_upd
	jz	cmoptions_03
	and	cflag,not _C_AUTOSAVE
	test	si,_O_FLAGB
	jz	@F
	or	cflag,_C_AUTOSAVE
    @@:
	call	redraw_panels
    cmoptions_03:
	mov	cf_panel,0
	pop	si
	ret
cmoptions ENDP

_DZIP	ENDS

	END
