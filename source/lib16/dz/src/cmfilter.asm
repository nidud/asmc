; CMFILTER.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include dir.inc
include fblk.inc
include stdio.inc
include stdlib.inc
include string.inc
include conio.inc
include mouse.inc
include keyb.inc
include wsub.inc

externdef	IDD_DZPanelFilter:DWORD
externdef	IDD_DZFindFile:DWORD

ID_READCOUNT	equ 1*16
ID_READMASK	equ 2*16
ID_DIRECTORY	equ 3*16
ID_OK		equ 4*16
ID_LOADPATH	equ 5*16
ID_CANCEL	equ 6*16

	.data

format_d	db '%d',0
path_dd		dd ?
cp_filter	db 'Filter',0
filter_keys	label WORD
GCMD KEY_F3,	cmfilter_load
GCMD KEY_F4,	cmfilter_date
		dw 0

_DZIP	segment

event_loadpath PROC _CType PRIVATE
local path[WMAXPATH]:BYTE
	mov path,0
	invoke tools_idd,WMAXPATH,addr path,addr cp_directory
	push ax
	call msloop
	pop ax
	mov dl,path
	.if !dl || !ax || ax == MOUSECMD
	    mov ax,_C_NORMAL
	.else
	    invoke dzexpenviron,addr path
	    invoke strcpy,path_dd,dx::ax
	    mov ax,_C_REOPEN
	.endif
	ret
event_loadpath ENDP

PanelFilter PROC pascal PRIVATE USES si di bx panel:WORD, xpos:BYTE
local	DLG_DZPanelFilter:DWORD
	mov si,WORD PTR IDD_DZPanelFilter
	mov al,xpos
	mov [si+6],al
	.if rsopen(IDD_DZPanelFilter)
	    stom DLG_DZPanelFilter
	    mov bx,WORD PTR panel
	    mov si,WORD PTR [bx].S_PANEL.pn_wsub
	    mov di,ax
	    movp es:[di].S_TOBJ.to_proc[ID_LOADPATH],event_loadpath
	    lodm es:[di].S_TOBJ.to_data[ID_DIRECTORY]
	    stom path_dd
	    invoke strcpy,dx::ax,[si].S_WSUB.ws_path
	    invoke strcpy,es:[di].S_TOBJ.to_data[ID_READMASK],[si].S_WSUB.ws_mask
	    invoke sprintf,es:[di].S_TOBJ.to_data[ID_READCOUNT],addr format_d,[si].S_WSUB.ws_maxfb
	    invoke dlinit,DLG_DZPanelFilter
	    .if dlevent(DLG_DZPanelFilter)
		pushm [si].S_WSUB.ws_mask
		pushm es:[di].S_TOBJ.to_data[ID_READMASK]
		pushm [si].S_WSUB.ws_path
		pushm es:[di].S_TOBJ.to_data[ID_DIRECTORY]
		invoke atol,es:[di].S_TOBJ.to_data[ID_READCOUNT]
		mov di,ax
		call strcpy
		call strcpy
		invoke dlclose,DLG_DZPanelFilter
		.if di != [si].S_WSUB.ws_maxfb && di > 10 && \
		    di < WMAXFBLOCK && WORD PTR [si].S_WSUB.ws_fcb != 0
		    invoke wsclose,ds::si
		    push [si].S_WSUB.ws_maxfb
		    mov	 [si].S_WSUB.ws_maxfb,di
		    invoke wsopen,ds::si
		    pop dx
		    .if ax
			mov ax,WORD PTR panel
			call panel_reread
			mov ax,WORD PTR panel
			.if ax == cpanel
			    invoke cominit,ds::si
			.endif
			mov ax,1
		    .else
			mov [si].S_WSUB.ws_maxfb,dx
			invoke wsopen,ds::si
			xor ax,ax
		    .endif
		.endif
	    .else
		invoke dlclose,DLG_DZPanelFilter
		xor ax,ax
	    .endif
	.endif
	ret
PanelFilter ENDP

cmafilter PROC _CType PUBLIC
	invoke PanelFilter,panela,3
	ret
cmafilter ENDP

cmbfilter PROC _CType PUBLIC
	invoke PanelFilter,panelb,42
	ret
cmbfilter ENDP

cmfilter_load PROC _CType PUBLIC USES si di bx
local	filt[FILT_MAXSTRING]:BYTE
local	dialog:DWORD
	movmx dialog,tdialog
	mov di,WORD PTR IDD_DZFindFile
	mov dl,[di].S_ROBJ.rs_count
	les bx,tdialog
	mov ax,1
	.if es:[bx].S_DOBJ.dl_count == dl
	    mov ax,0D0Dh
	.endif
	mov di,ax
	.if es:[bx].S_DOBJ.dl_index <= al
	    invoke tools_idd,128,addr filt,addr cp_filter
	    mov si,ax
	    call msloop
	    mov ax,_C_NORMAL
	    .if si
		.if si != MOUSECMD
		    les bx,dialog
		    mov dx,di
		    .if es:[bx].S_DOBJ.dl_index != dl
			mov es:[bx].S_DOBJ.dl_index,dh
		    .endif
		    mov al,es:[bx].S_DOBJ.dl_index
		    shl ax,4
		    les bx,es:[bx].S_DOBJ.dl_object
		    add bx,ax
		    invoke strcpy,es:[bx].S_TOBJ.to_data,addr filt
		    mov ax,_C_REOPEN
		.endif
	    .endif
	.else
	    mov ax,_C_NORMAL
	.endif
	ret
cmfilter_load ENDP

cmfilter_date PROC _CType PRIVATE USES di bx
  ifdef __CAL__
	les di,tdialog
	mov al,es:[di].S_DOBJ.dl_index
	.if al == 2 || al == 3
	    .if cmcalendar()
		les di,tdialog
		sub ah,ah
		mov al,es:[di].S_DOBJ.dl_index
		inc ax
		shl ax,4
		add di,ax
		invoke sprintf,es:[di].S_TOBJ.to_data,addr cp_datefrm,dx,bx,cx
		mov ax,_C_REOPEN
		jmp @F
	    .endif
	.endif
  endif
	mov ax,_C_NORMAL
      @@:
	ret
cmfilter_date ENDP

cmfilter PROC _CType PUBLIC
	invoke filter_edit,addr opfilter,addr filter_keys
	ret
cmfilter ENDP

cmloadpath PROC _CType PUBLIC
	sub	sp,WMAXPATH
	mov	ax,sp
	mov	WORD PTR path_dd,ax
	mov	WORD PTR path_dd+2,ss
	push	ax
	call	event_loadpath
	cmp	ax,_C_REOPEN
	pop	ax
	jne	cmloadpath_end
	mov	dx,ss
	call	cpanel_setpath
    cmloadpath_end:
	add	sp,WMAXPATH
	ret
cmloadpath ENDP

_DZIP	ENDS

	END
