; MENUS.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include string.inc
include conio.inc
include mouse.inc
include keyb.inc
include syserrls.inc
include dos.inc

PUBLIC	cp_copy
PUBLIC	cp_compress
PUBLIC	cp_decompress

extrn	cp_mkdir:BYTE
ifdef __ZIP__
extrn	cp_mkzip:BYTE
endif
ID_MPANELA	equ 0
ID_MFILE	equ 1
ID_MEDIT	equ 2
ID_MSETUP	equ 3
ID_MTOOLS	equ 4
ID_MHELP	equ 5
ID_MPANELB	equ 6

MENUSCMD	equ -1

_DATA	segment

CPW_PANELA	db 'Panel-&A',0
CPW_FILE	db '&File',0
CPW_EDIT	db '&'
cp_edit		db 'Edit',0
CPW_SETUP	db '&Setup',0
CPW_TOOLS	db '&'
cp_tools	db 'Tools',0
CPW_HELP	db '&'
cp_help		db 'Help',0
CPW_PANELB	db 'Panel-&B',0

cp_long		db 'Long/short filename',0
cp_detail	db 'Show detail',0
cp_wideview	db 'Wide view',0
cp_hidden	db 'Show hidden files',0
cp_mini		db 'Ministatus',0
cp_volinfo	db 'Volume information',0
cp_sort		db 'Sort current panel by Name, '
		db 'Type, Time, Size, or Unsorted',0
cp_toggle	db 'Toggle panel - on/off',0
cp_pfilter	db 'Panel filter',0
cp_subinfo	db 'Directory information',0
cp_update	db 'Re-read',0
cp_chdrv	db 'Select drive',0
cp_rename	db 'Rename file or directory',0
cp_view		db 'View File or Directory information',0
cp_copy		db 'Copy',0
cp_move		db 'Move',0
cp_delete	db 'Delete',0
cp_blkprop	db 'Edit file property',0
cp_compress	db 'Compress',0
cp_decompress	db 'Decompress',0
cp_history	db 'List of the last 16 DOS commands',0
cp_memory	db 'Memory Information',0
cp_search	db 'Search',0
cp_exit		db 'Exit program',0
cp_select	db 'Select files',0
cp_deselect	db 'Deselect files',0
cp_invert	db 'Invert selection',0
cp_mklist	db 'Create List File from selection',0
cp_qsearch	db 'Quick Search',0
cp_compare	db 'Compare directories',0
cp_toggleml	db 'Toggle Menus line - on/off',0
cp_togglecl	db 'Toggle Command line - on/off',0
cp_togglesl	db 'Toggle Status line - on/off',0
cp_toggleon	db 'Toggle panels - on/off',0
cp_togglehz	db 'Toggle panels - horizontal/vertical',0
cp_togglesz	db 'Toggle Panels - size',0
cp_egaline	db 'Toggle 25-50 lines',0
cp_swappanels	db 'Swap panels',0
cp_confirm	db 'Confirmations options',0
cp_screen	db 'Screen options',0
cp_panel	db 'Panel options',0
cp_config	db 'Configuration',0
cp_about	db 'About Doszip',0

menus_idd	dw 0
menus_obj	dw 0

IDDMENUS_LENGTH label WORD
	dw 11
	dw 8
	dw 8
	dw 9
	dw 9
	dw 8
	dw 11

IDDMENUS_XPOS label WORD
	dw 0
	dw 10
	dw 17
	dw 24
	dw 32
	dw 40
	dw 47

MENUS_OIDD label WORD
	dw ?
	dw ?
	dw ?
	dw ?
	dw ?
	dw ?
	dw ?

MENUS_PANELA	label	WORD
	GCMD	<offset cp_long>,	cmalong
	GCMD	<offset cp_detail>,	cmadetail
	GCMD	<offset cp_wideview>,	cmawideview
	GCMD	<offset cp_hidden>,	cmahidden
	GCMD	<offset cp_mini>,	cmamini
	GCMD	<offset cp_volinfo>,	cmavolinfo
	GCMD	<offset cp_sort>,	cmaname
	GCMD	<offset cp_sort>,	cmatype
	GCMD	<offset cp_sort>,	cmadate
	GCMD	<offset cp_sort>,	cmasize
	GCMD	<offset cp_sort>,	cmanosort
	GCMD	<offset cp_toggle>,	cmatoggle
	GCMD	<offset cp_pfilter>,	cmafilter
	GCMD	<offset cp_subinfo>,	cmasubinfo
	GCMD	<offset cp_update>,	cmaupdate
	GCMD	<offset cp_chdrv>,	cmachdrv

MENUS_FILE label WORD
	GCMD	<offset cp_rename>,	cmrename
	GCMD	<offset cp_view>,	cmview
	GCMD	<offset cp_edit>,	cmedit
	GCMD	<offset cp_copy>,	cmcopy
	GCMD	<offset cp_move>,	cmmove
	GCMD	<offset cp_mkdir>,	cmmkdir
	GCMD	<offset cp_delete>,	cmdelete
	GCMD	<offset cp_blkprop>,	cmattrib
	GCMD	<offset cp_compress>,	cmcompress
	GCMD	<offset cp_decompress>, cmdecompress
  ifdef __ZIP__
	GCMD	<offset cp_mkzip>,	cmmkzip
  else
	GCMD	<offset CP_EAGAIN>,	notsup
  endif
  ifdef __FF__
	GCMD	<offset cp_search>,	cmsearch
  else
	GCMD	<offset cp_search>,	notsup
  endif
	GCMD	<offset cp_history>,	cmhistory
	GCMD	<offset cp_memory>,	cmmemory
	GCMD	<offset cp_exit>,	cmexit

MENUS_EDIT label WORD
	GCMD	<offset cp_select>,	cmselect
	GCMD	<offset cp_deselect>,	cmdeselect
	GCMD	<offset cp_invert>,	cminvert
	GCMD	<offset cp_mklist>,	cmmklist
	GCMD	<offset cp_qsearch>,	cmquicksearch
	GCMD	<offset cp_compare>,	cmcompare

MENUS_SETUP label WORD
	GCMD	<offset cp_toggleml>,	cmxormenubar
	GCMD	<offset cp_toggleon>,	cmtoggleon
	GCMD	<offset cp_togglesz>,	cmtogglesz
	GCMD	<offset cp_togglehz>,	cmtogglehz
	GCMD	<offset cp_togglecl>,	cmxorcmdline
	GCMD	<offset cp_togglesl>,	cmxorkeybar
	GCMD	<offset cp_egaline>,	cmegaline
	GCMD	<offset cp_swappanels>, cmswap

	GCMD	<offset cp_confirm>,	cmconfirm
	GCMD	<offset cp_panel>,	cmpanel
	GCMD	<offset cp_config>,	cmcompression
  ifdef __TE__
	GCMD	<offset cp_config>,	teoption
  else
	GCMD	<offset cp_config>,	notsup
  endif
	GCMD	<offset cp_screen>,	cmscreen
	GCMD	<offset cp_config>,	cmsystem
	GCMD	<offset cp_config>,	cmoptions

MENUS_HELP label WORD
	GCMD	<offset cp_help>,	cmhelp
	GCMD	<offset cp_about>,	cmabout

MENUS_PANELB label WORD
	GCMD	<offset cp_long>,	cmblong
	GCMD	<offset cp_detail>,	cmbdetail
	GCMD	<offset cp_wideview>,	cmbwideview
	GCMD	<offset cp_hidden>,	cmbhidden
	GCMD	<offset cp_mini>,	cmbmini
	GCMD	<offset cp_volinfo>,	cmbvolinfo
	GCMD	<offset cp_sort>,	cmbname
	GCMD	<offset cp_sort>,	cmbtype
	GCMD	<offset cp_sort>,	cmbdate
	GCMD	<offset cp_sort>,	cmbsize
	GCMD	<offset cp_sort>,	cmbnosort
	GCMD	<offset cp_toggle>,	cmbtoggle
	GCMD	<offset cp_pfilter>,	cmbfilter
	GCMD	<offset cp_subinfo>,	cmbsubinfo
	GCMD	<offset cp_update>,	cmbupdate
	GCMD	<offset cp_chdrv>,	cmbchdrv

MENUS_OID label WORD
	dw	offset MENUS_PANELA
	dw	offset MENUS_FILE
	dw	offset MENUS_EDIT
	dw	offset MENUS_SETUP
	dw	0
	dw	offset MENUS_HELP
	dw	offset MENUS_PANELB

MENUS_SHORTKEYS label WORD
	dw	1E00h	; A Panel-A
	dw	2100h	; F File
	dw	1200h	; E Edit
	dw	1F00h	; S Setup
	dw	1400h	; T Tools
	dw	2300h	; H Help
	dw	3000h	; B Panel-B

TOBJ_MENUSLINE label WORD
	S_TOBJ	<0006h,0,1Eh,< 0,0,11,1>,DGROUP:CPW_PANELA,0>
	S_TOBJ	<0006h,0,21h,<10,0,10,1>,DGROUP:CPW_FILE,0>
	S_TOBJ	<0006h,0,12h,<17,0, 8,1>,DGROUP:CPW_EDIT,0>
	S_TOBJ	<0006h,0,1Fh,<24,0,10,1>,DGROUP:CPW_SETUP,0>
	S_TOBJ	<0006h,0,14h,<32,0, 9,1>,DGROUP:CPW_TOOLS,0>
	S_TOBJ	<0006h,0,23h,<40,0, 8,1>,DGROUP:CPW_HELP,0>
	S_TOBJ	<0006h,0,30h,<47,0,11,1>,DGROUP:CPW_PANELB,0>
_DATA	ENDS

_DZIP	segment

open_idd PROC PUBLIC
	push ax
	add ax,ax
	mov bx,ax
	push ds
	push MENUS_OIDD[bx]
	call rsopen
	mov [bp-4],ax
	mov [bp-2],dx
	pop bx
	.if !ZERO?
	    add ax,16
	    mov [bp-8],ax
	    mov [bp-6],dx
	    .if cflag & _C_MENUSLINE
		add bx,bx
		mov dx,IDDMENUS_XPOS[bx]
		mov bx,IDDMENUS_LENGTH[bx]
		push dx
		push bx
		push ss
		lea ax,[bp-30]
		push ax
		push _scrseg
		add bx,bx
		add dx,dx
		push dx
		push bx
ifdef __MOUSE__
		call mousehide
endif
		call memcpy
ifdef __MOUSE__
		call mouseshow
endif
		mov al,at_foreground[F_MenusKey]
		mov ah,0
		pop cx
		pop bx
		mov dl,bh
		invoke scputa,bx,dx,cx,ax
	    .endif
	    or ax,1
	.endif
	ret
open_idd ENDP

close_idd PROC PUBLIC
	.if cflag & _C_MENUSLINE
	    push dx
	    push ax
	    push _scrseg
	    add bx,bx
	    mov ax,[bx+IDDMENUS_XPOS]
	    mov bx,[bx+IDDMENUS_LENGTH]
	    add ax,ax
	    add bx,bx
	    push ax
	    push ss
	    lea ax,[bp-30]
	    push ax
	    push bx
ifdef __MOUSE__
	    call mousehide
endif
	    call memcpy
ifdef __MOUSE__
	    call mouseshow
endif
	    pop ax
	    pop dx
	.endif
	ret
close_idd ENDP

modal_idd PROC PUBLIC
	push bx
	mov bx,ax
	lea ax,[bp-190]
	push ss
	push ax
	invoke wcpushst, ss::ax, dx::bx
	invoke dlinit, [bp-4]
	invoke dlevent, [bp-4]
	mov si,ax
	shl ax,4
	les bx,[bp-4]
	add bx,ax
	mov ax,es:[bx]
	and ax,_O_STATE or _O_FLAGB
	mov di,ax
	call wcpopst
	pop bx
	call close_idd
	ret
modal_idd ENDP

menus_idle PROC PRIVATE
	push si
	xor si,si
	.repeat
	    call tupdate
ifdef __MOUSE__
	    call mousep
	    .break .if !ZERO?
endif
	    les bx,keyshift
	    mov al,es:[bx]
	    and ax,KEY_CTRL
	    jnz @F
	    call getkey
	    mov si,ax
	.until ax
	mov ax,si
      @@:
	pop si
	ret
menus_idle ENDP

menus_modalidd_P PROC PRIVATE
	test	di,cx
	jz	menus_modalidd_D
	jmp	menus_modalidd_C
menus_modalidd_P ENDP

menus_modalidd_A PROC PRIVATE
	test	dx,cx
	jz	menus_modalidd_D
	jmp	menus_modalidd_C
menus_modalidd_A ENDP

menus_modalidd_B PROC PRIVATE
	cmp	dx,cx
	jne	menus_modalidd_D
menus_modalidd_B ENDP

menus_modalidd_C PROC PRIVATE
	or	es:[bx],ax
menus_modalidd_C ENDP

menus_modalidd_D PROC PRIVATE
	add	bx,16
	ret
menus_modalidd_D ENDP

menus_modalidd PROC pascal PRIVATE USES si di id:WORD
local	buf[190]:BYTE
	mov di,id
	.if di == ID_MTOOLS
	    invoke tools_idd,128,0,addr cp_tools
	.else
	    mov bx,WORD PTR IDD_DZMenuPanel
	    mov BYTE PTR [bx+6],0
	    .if di == ID_MPANELB
		mov BYTE PTR [bx+6],42
	    .endif
	    mov ax,di
	    call open_idd
	    .if !ZERO?
		xor cx,cx
		les bx,[bp-4]
		mov dl,es:[bx].S_DOBJ.dl_count
		add bx,S_TOBJ.to_data[16]
		mov si,di
		add si,si
		mov si,MENUS_OID[si]
		.while dl > cl
		    mov ax,[si]
		    mov es:[bx],ax
		    mov es:[bx+2],ds
		    add bx,SIZE S_TOBJ
ifdef __l__
		    add si,6
else
		    add si,4
endif
		    inc cx
		.endw
		xor dx,dx
		.if !di
		    mov dx,path_a.wp_flag
		    mov di,flaga
		.elseif di == ID_MPANELB
		    mov dx,path_b.wp_flag
		    mov di,flagb
		.endif
		.if dx
		    les bx,[bp-4]
		    add bx,16
ifdef __LFN__
		    .if !_ifsmgr
endif
		    or es:[bx].S_TOBJ.to_flag,_O_STATE
ifdef __LFN__
		    .endif
endif
		    mov ax,_O_FLAGB
		    mov cx,_W_LONGNAME
		    call menus_modalidd_A
		    mov cx,_P_DETAIL
		    call menus_modalidd_P
		    mov cx,_P_WIDEVIEW
		    call menus_modalidd_P
		    mov cx,_W_HIDDEN
		    call menus_modalidd_A
		    mov cx,_P_MINISTATUS
		    call menus_modalidd_P
		    mov cx,_P_DRVINFO
		    call menus_modalidd_P
		    mov ax,_O_RADIO
		    .if dx & _W_NOSORT
			or es:[bx+64],ax
		    .else
			and dx,_W_SORTSIZE
			mov cx,_W_SORTNAME
			call menus_modalidd_B
			mov cx,_W_SORTTYPE
			call menus_modalidd_B
			mov cx,_W_SORTDATE
			call menus_modalidd_B
			mov cx,_W_SORTSIZE
			call menus_modalidd_B
		    .endif
		.endif
		mov di,id
		mov bx,di
		shl bx,4
		lodm TOBJ_MENUSLINE[bx].S_TOBJ.to_data
		mov bx,di
		call modal_idd
		.if si
		    les bx,[bp-4]
		    mov al,es:[bx].S_DOBJ.dl_count
		    mov ah,0
		    .if ax >= si
			invoke dlclose,[bp-4]
			mov bx,[bp+4]
			mov menus_idd,bx
			mov ax,si
			dec ax
			mov menus_obj,ax
			and di,_O_STATE
			.if ZERO?
			    add bx,bx
			    mov bx,MENUS_OID[bx]
			  ifdef __l__
			    mov ah,SIZE S_GLCMD
			    mul ah
			  else
			    shl ax,2
			  endif
			    add bx,ax
			    call [bx].S_GLCMD.gl_proc
			.endif
			jmp @F
		    .endif
		.endif
		invoke dlclose,[bp-4]
ifdef __MOUSE__
		.if mousep()
		    mov si,MOUSECMD
		.endif
endif
	      @@:
		mov ax,si
	    .endif
	.endif
	ret
menus_modalidd ENDP

menus_event PROC pascal PRIVATE USES si di id:WORD, key:WORD
	mov di,key
	mov si,1
	.while 1
	    .if di == MOUSECMD
		xor di,di
		mov si,di
	    .elseif di == MENUSCMD
		invoke menus_modalidd,id
		mov si,1
	    .elseif di == KEY_RIGHT
		mov ax,di
		.break .if !si
		mov ax,id
		inc ax
		.if ax > ID_MPANELB
		    xor ax,ax
		.endif
	      @@:
		mov id,ax
		invoke menus_modalidd,ax
		mov di,ax
	    .elseif di == KEY_LEFT
		mov ax,di
		.if si
		    mov ax,id
		    dec ax
		    .if ax == -1
			mov ax,ID_MPANELB
		    .endif
		    jmp @B
		.endif
		.break
	    .elseif di == KEY_ESC
		mov ax,di
		.break .if !si
		xor ax,ax
		.break
	    .elseif si
		call msloop
		.break
	    .else
		.if di
		    mov cx,7
		    xor bx,bx
		    .repeat
			.if di == [bx+MENUS_SHORTKEYS]
			    shr bx,1
			    mov id,bx
			    invoke menus_modalidd,bx
			    mov di,ax
			    mov si,1
			    jmp @F
			.else
			    add bx,2
			.endif
		    .untilcxz
		    mov ax,di
		    .break .if !si
		.endif
	    .endif
	  @@:
	    .if !si
		call menus_idle
		mov di,ax
		.break .if ax == KEY_CTRL
	    .endif
	    .if cflag & _C_MENUSLINE
ifdef __MOUSE__
		call mousey
		or ax,ax
		jnz @F
endif
		or di,di
		jnz @F
ifdef __MOUSE__
		call mousex
		mov dx,ax
else
		xor dx,dx
endif
		mov cx,ID_MPANELB
		.if ax >= 57
		    mov ax,MOUSECMD
		    .break
		.endif
		.repeat
		    mov bx,cx
		    dec cx
		    shl bx,4
		    add bx,offset TOBJ_MENUSLINE
		.until al >= [bx+4]
		mov ah,[bx].S_TOBJ.to_ascii
		mov al,0
		mov di,ax
		inc cx
		mov id,cx
		.continue
	    .endif
	  @@:
	    .if di
		.continue
	    .endif
	    mov ax,MOUSECMD
	    .break
	.endw
	ret
menus_event ENDP

menus_getevent PROC PUBLIC
	invoke	menus_event,0,MOUSECMD
	ret
menus_getevent ENDP

statusline_xy PROC PUBLIC	; BX Offset MOBJ
	push si			; CX count
	mov si,ax		; AX xpos
	mov ax,cflag		; DX ypos
	and ax,_C_STATUSLINE
	.if !ZERO?
	    .if dl != _scrrow
		xor ax,ax
	    .else
		.repeat
		    mov [bx+1],dl
		    invoke rcxyrow,[bx],si,dx
		    .break .if !ZERO?
		    add bx,8
		.untilcxz
	    .endif
	.endif
	pop si
	ret
statusline_xy ENDP

cmxorcmdline PROC _CType PUBLIC
	xor  cflag,_C_COMMANDLINE
	call apiupdate
	ret
cmxorcmdline ENDP

cmxorkeybar PROC _CType PUBLIC
	xor  cflag,_C_STATUSLINE
	call apiupdate
	ret
cmxorkeybar ENDP

cmxormenubar PROC _CType PUBLIC
	xor	cflag,_C_MENUSLINE
	call	apiupdate
	ret
cmxormenubar ENDP

cmlastmenu PROC _CType PUBLIC
	mov	dx,menus_idd
	mov	bx,dx
	add	bx,bx
	mov	bx,[bx+MENUS_OIDD]
	mov	ax,menus_obj
	mov	[bx].S_ROBJ.rs_index,al
	push	dx
	invoke	menus_modalidd,dx
	push	ax
	call	menus_event
	ret
cmlastmenu ENDP

menusinit_OIDD PROC PUBLIC
	push	di
	push	ds
	pop	es
	cld
	mov	di,offset MENUS_OIDD
	mov	ax,WORD PTR IDD_DZMenuPanel
	stosw
	mov	ax,WORD PTR IDD_DZMenuFile
	stosw
	mov	ax,WORD PTR IDD_DZMenuEdit
	stosw
	mov	ax,WORD PTR IDD_DZMenuSetup
	stosw
	mov	ax,WORD PTR IDD_DZMenuTools
	stosw
	mov	ax,WORD PTR IDD_DZMenuHelp
	stosw
	mov	ax,WORD PTR IDD_DZMenuPanel
	stosw
	pop	di
	ret
menusinit_OIDD ENDP

_DZIP	ENDS

	END
