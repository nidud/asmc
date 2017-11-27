; CMPANEL.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include keyb.inc
include dos.inc
include dir.inc
include ini.inc
include iost.inc
include io.inc
include string.inc
include conio.inc
include mouse.inc
include errno.inc
include dir.inc

extrn	cp_selectmask:BYTE
extrn	panel_toggleact:near

_DATA	segment

cp_selectdrv	db 'Select disk Panel '
cp_selectdrv_X	db 'A',0

_DATA	ENDS

_DZIP	segment

ccedit	PROC PRIVATE	; rename or copy current file to a new name
	push bp
	push si
	push di
	mov bp,ax
	mov ax,cpanel
	.if panel_curobj()
	    mov si,dx
	    mov di,bx
	    .if !(cx & _A_UPDIR or _A_ROOTDIR)
		.if cx & _A_ARCHIVE
		    call notsup
		.else
ifdef __LFN__
		    invoke wlongname,dx::ax,0
endif
		    invoke strcpy,addr __srcfile,dx::ax
		    invoke strcpy,addr __outfile,dx::ax
		    .if __outfile
			mov bx,cpanel
			mov bx,WORD PTR [bx].S_PANEL.pn_xl
			mov dx,WORD PTR [bx].S_XCELL.xl_rect[2]
			mov bx,WORD PTR [bx].S_XCELL.xl_rect
			mov cl,dl
			mov ch,0
			mov al,bh
			invoke scputw,bx,ax,cx,0720h
			invoke dledit,addr __outfile,dx::bx,WMAXPATH-1,0
			.if ax != KEY_ESC
			    .if strcmp(addr __outfile,addr __srcfile)
				.if __outfile
				    .if bp
					mov es,si
					mov ax,es:[di]
					.if !(ax & _A_ARCHIVE)
					    invoke copyfile,es:[di].S_FBLK.fb_size,
						WORD PTR es:[di].S_FBLK.fb_time[2],
						WORD PTR es:[di].S_FBLK.fb_time,ax
					.endif
				    .else
					invoke rename,addr __srcfile,addr __outfile
				    .endif
				    mov ax,cpanel
				    call panel_reread
				.endif
			    .endif
			.endif
		    .endif
		    mov bx,cpanel
		    .if dlclose([bx].S_PANEL.pn_xl)
			mov ax,cpanel
			call pcell_show
		    .endif
		    mov ax,1
		.endif
	    .else
		sub ax,ax
	    .endif
	.endif
	pop di
	pop si
	pop bp
	ret
ccedit	ENDP

cmrename PROC _CType PUBLIC
	xor ax,ax
	call ccedit
	ret
cmrename ENDP

cmcopycell PROC _CType PUBLIC
	mov ax,1
	call ccedit
	ret
cmcopycell ENDP

cmpsizeup PROC _CType PUBLIC
	mov bx,panela
	mov bx,WORD PTR [bx].S_PANEL.pn_dialog
	mov al,9
	.if cflag & _C_HORIZONTAL
	    dec al
	.endif
	.if [bx+7] != al
	    inc BYTE PTR config.c_panelsize
	    call redraw_panels
	.endif
	ret
cmpsizeup ENDP

cmpsizedn PROC _CType PUBLIC
	xor ax,ax
	.if ax != config.c_panelsize
	    dec BYTE PTR config.c_panelsize
	    call redraw_panels
	.endif
	ret
cmpsizedn ENDP

cmupdir PROC _CType PUBLIC
	.if panel_event(cpanel,KEY_HOME)
	    invoke panel_event,cpanel,KEY_ENTER
	.endif
	ret
cmupdir ENDP

cmsubdir PROC _CType PUBLIC
	mov ax,cpanel
	.if panel_curobj()
	    .if cx & _A_SUBDIR
		invoke panel_event,cpanel,KEY_ENTER
	    .endif
	.endif
	ret
cmsubdir ENDP

cmpath PROC pascal PRIVATE USES si di ini_id:WORD
local	path[WMAXPATH]:BYTE
	mov ax,cpanel
	.if panel_state()
	    .if inientryid(addr cp_directory,ini_id)
		mov es,dx
		mov bx,ax
		.if WORD PTR es:[bx] != '><'
		    .if strchr(dx::ax,',')
			inc ax
			invoke strstart,dx::ax
			mov cx,ax
			invoke strnzcpy,addr path,dx::cx,WMAXPATH
			invoke dzexpenviron,dx::ax
			.if path != '['
			    mov dx,ss
			    lea ax,path
			    call cpanel_setpath
			.endif
		    .endif
		.endif
	    .endif
	.endif
	ret
cmpath	ENDP

cmpathp macro q
cmpath&q PROC _CType PUBLIC
	invoke cmpath, q
	ret
cmpath&q ENDP
	endm

cmpathp 0
cmpathp 1
cmpathp 2
cmpathp 3
cmpathp 4
cmpathp 5
cmpathp 6
cmpathp 7

cmlfn PROC _CType PRIVATE
ifdef __LFN__
	push bx
	mov bx,[bx]
	mov ax,[bx]
	.if ax & _W_LONGNAME
	    and ax,not _W_LONGNAME
	.elseif _ifsmgr
	    or ax,_W_LONGNAME
	.endif
	mov [bx],ax
	pop ax
	call panel_update
endif
	ret
cmlfn ENDP

cmalong PROC _CType PUBLIC
	mov bx,panela
	jmp cmlfn
cmalong ENDP

cmblong PROC _CType PUBLIC
	mov bx,panelb
	jmp cmlfn
cmblong ENDP

cmclong PROC _CType PUBLIC
	mov bx,cpanel
	jmp cmlfn
cmclong ENDP

cmdetail PROC PRIVATE
	mov bx,dx
	mov ax,[bx].S_PANEL.pn_flag
	and ax,not _P_WIDEVIEW
	xor ax,_P_DETAIL
	mov [bx].S_PANEL.pn_flag,ax
	mov ax,dx
	call panel_redraw
	ret
cmdetail ENDP

cmadetail PROC _CType PUBLIC
	mov dx,panela
	call cmdetail
	ret
cmadetail ENDP

cmcdetail PROC _CType PUBLIC
	mov ax,panela
	cmp ax,cpanel
	je cmadetail
cmcdetail ENDP

cmbdetail PROC _CType PUBLIC
	mov dx,panelb
	call cmdetail
	ret
cmbdetail ENDP

cmwideview PROC PRIVATE
	mov bx,dx
	mov ax,[bx].S_PANEL.pn_flag
	and ax,not _P_DETAIL
	xor ax,_P_WIDEVIEW
	mov [bx].S_PANEL.pn_flag,ax
	mov ax,bx
	call panel_redraw
	ret
cmwideview ENDP

cmawideview PROC _CType PUBLIC
	mov dx,panela
	call cmwideview
	ret
cmawideview ENDP

cmbwideview PROC _CType PUBLIC
	mov dx,panelb
	call cmwideview
	ret
cmbwideview ENDP

cmcwideview PROC _CType PUBLIC
	mov dx,cpanel
	call cmwideview
	ret
cmcwideview ENDP

cmahidden PROC _CType PUBLIC
	xor path_a.wp_flag,_W_HIDDEN
	mov ax,panela
	call panel_update
	ret
cmahidden ENDP

cmchidden PROC _CType PUBLIC
	mov ax,panela
	cmp ax,cpanel
	je cmahidden
cmchidden ENDP

cmbhidden PROC _CType PUBLIC
	xor path_b.wp_flag,_W_HIDDEN
	mov ax,panelb
	call panel_update
	ret
cmbhidden ENDP

cmamini PROC _CType PUBLIC
	mov ax,panela
	call panel_xormini
	ret
cmamini ENDP

cmbmini PROC _CType PUBLIC
	mov ax,panelb
	call panel_xormini
	ret
cmbmini ENDP

cmcmini PROC _CType PUBLIC
	mov ax,cpanel
	call panel_xormini
	ret
cmcmini ENDP

cmvolinfo PROC _CType PUBLIC
	mov ax,cpanel
	call panel_xorinfo
	ret
cmvolinfo ENDP

cmavolinfo PROC _CType PUBLIC
	mov ax,panela
	call panel_xorinfo
	ret
cmavolinfo ENDP

cmbvolinfo PROC _CType PUBLIC
	mov ax,panelb
	call panel_xorinfo
	ret
cmbvolinfo ENDP

cm_sort PROC pascal PRIVATE USES si di	; AX: OFFSET panel, DX: sort flag
local	path[WMAXPATH]:BYTE
	mov si,dx
	.if panel_state()
	    mov cx,si
	    mov si,bx
	    mov di,dx
	    mov bx,WORD PTR [bx].S_WSUB.ws_flag
	    mov ax,[bx].S_PATH.wp_flag
	    and ax,not (_W_SORTSIZE or _W_NOSORT)
	    or ax,cx
	    mov [bx].S_PATH.wp_flag,ax
	    mov ax,di
	    .if panel_curobj()
		lea cx,path
		invoke strcpy,ss::cx,dx::ax
		invoke wssort,ss::si
		.if wsearch(ss::si,addr path) != -1
		    push ax
		    push di
		    invoke dlclose,[di].S_PANEL.pn_xl
		    pop ax
		    pop dx
		    call panel_setid
		    .if di == cpanel
			mov ax,di
			call pcell_show
		    .endif
		.endif
	    .endif
	    invoke panel_putitem,di,0
	    mov ax,1
	.endif
	ret
cm_sort ENDP

cm_nosort PROC PRIVATE
	push ax
	call panel_state
	pop ax
	.if !ZERO?
	    push dx
	    push 0
	    mov bx,WORD PTR [bx].S_WSUB.ws_flag
	    or [bx].S_PATH.wp_flag,_W_NOSORT
	    call panel_read
	    call panel_putitem
	    mov ax,1
	.endif
	ret
cm_nosort ENDP

cmanosort PROC _CType PUBLIC
	mov ax,panela
	call cm_nosort
	ret
cmanosort ENDP

cmbnosort PROC _CType PUBLIC
	mov ax,panelb
	call cm_nosort
	ret
cmbnosort ENDP

cmcnosort PROC _CType PUBLIC
	mov ax,cpanel
	call cm_nosort
	ret
cmcnosort ENDP

cmadate PROC _CType PUBLIC
	mov ax,panela
	mov dx,_W_SORTDATE
	call cm_sort
	ret
cmadate ENDP

cmbdate PROC _CType PUBLIC
	mov ax,panelb
	mov dx,_W_SORTDATE
	call cm_sort
	ret
cmbdate ENDP

cmcdate PROC _CType PUBLIC
	mov ax,cpanel
	mov dx,_W_SORTDATE
	call cm_sort
	ret
cmcdate ENDP

cmatype PROC _CType PUBLIC
	mov ax,panela
	mov dx,_W_SORTTYPE
	call cm_sort
	ret
cmatype ENDP

cmbtype PROC _CType PUBLIC
	mov ax,panelb
	mov dx,_W_SORTTYPE
	call cm_sort
	ret
cmbtype ENDP

cmctype PROC _CType PUBLIC
	mov ax,cpanel
	mov dx,_W_SORTTYPE
	call cm_sort
	ret
cmctype ENDP

cmasize PROC _CType PUBLIC
	mov ax,panela
	mov dx,_W_SORTSIZE
	call cm_sort
	ret
cmasize ENDP

cmbsize PROC _CType PUBLIC
	mov ax,panelb
	mov dx,_W_SORTSIZE
	call cm_sort
	ret
cmbsize ENDP

cmcsize PROC _CType PUBLIC
	mov ax,cpanel
	mov dx,_W_SORTSIZE
	call cm_sort
	ret
cmcsize ENDP

cmaname PROC _CType PUBLIC
	mov ax,panela
	mov dx,_W_SORTNAME
	call cm_sort
	ret
cmaname ENDP

cmbname PROC _CType PUBLIC
	mov ax,panelb
	mov dx,_W_SORTNAME
	call cm_sort
	ret
cmbname ENDP

cmcname PROC _CType PUBLIC
	mov ax,cpanel
	mov dx,_W_SORTNAME
	call cm_sort
	ret
cmcname ENDP

cmchdrv PROC PRIVATE
	push si
	mov si,ax
	.if panel_state()
	    mov errno,0
	    .if _disk_select(addr cp_selectdrv)
		push ax
		dec ax
		invoke panel_sethdd,si,ax
		call msloop
		pop ax
	    .endif
	.endif
	pop si
	ret
cmchdrv ENDP

cmachdrv PROC _CType PUBLIC
	mov ax,panela
	mov cp_selectdrv_X,'A'
	call cmchdrv
	ret
cmachdrv ENDP

cmbchdrv PROC _CType PUBLIC
	mov ax,panelb
	mov cp_selectdrv_X,'B'
	call cmchdrv
	ret
cmbchdrv ENDP

cmaupdate PROC _CType PUBLIC
	mov ax,panela
	call panel_reread
	ret
cmaupdate ENDP

cmbupdate PROC _CType PUBLIC
	mov ax,panelb
	call panel_reread
	ret
cmbupdate ENDP

cmcupdate PROC _CType PUBLIC
	mov ax,cpanel
	call panel_reread
	ret
cmcupdate ENDP

select PROC PRIVATE
	mov ax,cpanel
	.if panel_state()
	    push si
	    push di
	    mov si,dx
	    mov di,WORD PTR [si].S_PANEL.pn_wsub
	    mov cx,[si].S_PANEL.pn_fcb_count
	    mov si,WORD PTR [di].S_WSUB.ws_fcb[2]
	    mov di,WORD PTR [di].S_WSUB.ws_fcb
	    .while cx
		mov es,si
		les bx,es:[di]
		push cx
		.if cmpwarg(addr es:[bx].S_FBLK.fb_name,addr cp_selectmask)
		    mov es,si
		    invoke fblk_select,es:[di]
		.endif
		add di,4
		pop cx
		dec cx
	    .endw
	    invoke panel_putitem,cpanel,0
	    mov ax,1
	    pop di
	    pop si
	.endif
	ret
select ENDP

cmselect PROC _CType PUBLIC
	.if !cp_selectmask
	    invoke strcpy,addr cp_selectmask,addr cp_stdmask
	.endif
	.if tgetline(addr cp_select,addr cp_selectmask,12,32+8000h)
	    .if cp_selectmask
		call select
	    .endif
	.endif
	ret
cmselect ENDP

deselect PROC PRIVATE
	mov ax,cpanel
	.if panel_state()
	    push si
	    push di
	    mov si,dx
	    mov di,WORD PTR [si].S_PANEL.pn_wsub
	    mov cx,[si].S_PANEL.pn_fcb_count
	    mov si,WORD PTR [di].S_WSUB.ws_fcb[2]
	    mov di,WORD PTR [di].S_WSUB.ws_fcb
	    .repeat
		mov es,si
		push cx
		lodm es:[di]
		add ax,S_FBLK.fb_name
		.if cmpwarg(dx::ax,addr cp_selectmask)
		    mov es,si
		    les bx,es:[di]
		    and es:[bx].S_FBLK.fb_flag,not _A_SELECTED
		.endif
		add di,4
		pop cx
	    .untilcxz
	    invoke panel_putitem,cpanel,0
	    mov ax,1
	    pop di
	    pop si
	.endif
	ret
deselect ENDP

cmdeselect PROC _CType PUBLIC
	.if !cp_selectmask
	    invoke strcpy,addr cp_selectmask,addr cp_stdmask
	.endif
	.if tgetline(addr cp_deselect,addr cp_selectmask,12,32+8000h)
	    .if cp_selectmask
		call deselect
	    .endif
	.endif
	ret
cmdeselect ENDP

cminvert PROC _CType PUBLIC
	mov ax,cpanel
	.if panel_state()
	    push si
	    push di
	    mov si,dx
	    mov di,WORD PTR [si].S_PANEL.pn_wsub
	    mov cx,[si].S_PANEL.pn_fcb_count
	    mov si,WORD PTR [di].S_WSUB.ws_fcb[2]
	    mov di,WORD PTR [di].S_WSUB.ws_fcb
	    .repeat
		mov es,si
		invoke fblk_invert,es:[di]
		add di,4
	    .untilcxz
	    invoke panel_putitem,cpanel,0
	    mov ax,1
	    pop di
	    pop si
	.endif
	ret
cminvert ENDP

cmswap	PROC _CType PUBLIC
	.if panel_stateab()
	    push si
	    push di
	    mov si,flaga
	    mov di,flagb
	    mov ax,panela
	    call panel_close
	    mov ax,panelb
	    call panel_close
	    mov ax,offset config.c_fcb_indexa
	    mov dx,offset config.c_fcb_indexb
	    invoke memxchg,ds::ax,ds::dx,4
	    mov ax,offset spanela.pn_fcb_index
	    mov dx,offset spanelb.pn_fcb_index
	    invoke memxchg,ds::ax,ds::dx,4
	    invoke memxchg,addr path_a,addr path_b,SIZE S_PATH
	    xor si,_P_PANELID
	    xor di,_P_PANELID
	    mov flaga,di
	    mov flagb,si
	    xor cflag,_C_PANELID
	    call prect_open_ab
	    call panel_open_ab
	    call panel_toggleact
	    mov ax,1
	    pop di
	    pop si
	.endif
	ret
cmswap	ENDP

cmatoggle PROC _CType PUBLIC
	mov ax,panela
cmatoggle ENDP

cmabtoggle PROC _CType PRIVATE
	call panel_toggle
	ret
cmabtoggle ENDP

cmbtoggle PROC _CType PUBLIC
	mov ax,panelb
	jmp cmabtoggle
cmbtoggle ENDP

cmtoggleon PROC _CType PUBLIC
	push si
	push di
	mov ax,panela
	call panel_state
	mov si,ax
	mov ax,panelb
	call panel_state
	mov di,ax
	.if ax != si
	    .if si
		call cmatoggle
	    .else
		call cmbtoggle
	    .endif
	.elseif ax
	    mov ax,cpanel
	    .if ax != panelb
		push panelb
	    .else
		push panela
	    .endif
	    call panel_hide
	    pop ax
	    call panel_hide
	.else
	    call comhide
	    mov ax,cpanel
	    push ax
	    push ax
	    .if ax == panelb
		mov ax,panela
	    .else
		mov ax,panelb
	    .endif
	    call panel_show
	    pop ax
	    call panel_show
	    pop ax
	    call panel_setactive
	.endif
	xor ax,ax
	pop di
	pop si
	ret
cmtoggleon ENDP

cmtogglesz PROC _CType PUBLIC
	xor ax,ax
	.if ax == config.c_panelsize
	    mov al,_scrrow
	    shr al,1
	    dec al
	.endif
	mov config.c_panelsize,ax
	call redraw_panels
	ret
cmtogglesz ENDP

cmtogglehz PROC _CType PUBLIC
	mov ax,config.c_panelsize
	mov cx,cflag
	.if cx & _C_WIDEVIEW && cx & _C_HORIZONTAL
	    and cx,not _C_WIDEVIEW
	    shl al,1
	.elseif cx & _C_HORIZONTAL
	    and cx,not _C_HORIZONTAL
	    shl al,1
	.else
	    or cx,_C_WIDEVIEW or _C_HORIZONTAL
	.endif
	mov cflag,cx
	mov config.c_panelsize,ax
	call redraw_panels
	ret
cmtogglehz ENDP

cmhomedir PROC _CType PUBLIC
	mov ax,cpanel
	.if panel_state()
	    mov bx,cpanel
	    mov bx,[bx]
	    mov ax,[bx]
	    or ax,_W_ROOTDIR
	    and ax,not _W_ARCHIVE
	    mov [bx],ax
	    mov [bx].S_PATH.wp_arch,0
	    mov ax,cpanel
	    call panel_read
	    invoke panel_putitem,cpanel,0
	.endif
	ret
cmhomedir ENDP

_DZIP	ENDS

	END
