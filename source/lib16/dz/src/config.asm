; CONFIG.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include conio.inc
include io.inc
include iost.inc
include dos.inc
include errno.inc
include tinfo.inc
include string.inc
include alloc.inc
include ini.inc
include stdio.inc
include stdlib.inc
include keyb.inc

extrn	IDD_DZHistory:DWORD

PUBLIC	searchstring
PUBLIC	replacestring
PUBLIC	findfilemask
PUBLIC	findfilepath
PUBLIC	filelist_bat
PUBLIC	format_lst
PUBLIC	cp_selectmask

ifdef __TE__
topenh_atol	PROTO
topenh		PROTO pascal :PTR BYTE
tsaveh		PROTO pascal :WORD
endif

	.data

history		dd ?
doskey_bindex	db ?
doskey_isnext	db ?

searchstring	db 128 dup(?)
replacestring	db 128 dup(?)
cp_selectmask	db 32 dup(?)
filelist_bat	db "filelist.bat"
		db 80-12 dup(?)
format_lst	db "%f\n"
		db 256-4 dup(?)
findfilemask	db "*.*"
		db 128-3 dup(?)
findfilepath	db WMAXPATH dup(?)

cp_history	db "dz.cfg",0
cp_Config	db "config",0
cp_Doskey	db "Doskey",0
cp_Directory	db "Directory",0
cp_OpenFiles	db ".",0
cp_format_s	db "[%s]",10,0
cp_format_dw	db "%d=%X",10,0
cp_format_dd	db "%d=%lX",10,0
cp_format_e	db "%d=%s",10,0

cid_table_dw	dw  1, config.c_lflag
		dw  2, config.c_confirm
		dw  3, config.c_console
		dw  4, config.c_fsflag
		dw  5, config.c_tvflag
		dw  6, config.c_teflag
		dw  7, config.c_tepages
		dw  8, config.c_telsize
		dw  9, config.c_tetabsize
		dw 10, config.c_compress
		dw 11, config.c_ffflag
		dw 12, config.c_comprlevel
		dw 13, config.c_panelsize
		dw 14, config.c_flaga
		dw 15, config.c_fcb_indexa
		dw 16, config.c_cel_indexa
		dw 17, config.c_flagb
		dw 18, config.c_fcb_indexb
		dw 19, config.c_cel_indexb
		dw 20, config.c_apath
		dw 21, config.c_bpath
		dw 22, config.c_filter.of_flag
		dw 23, config.c_filter.of_max_date
		dw 24, config.c_filter.of_min_date
		dw 25, config.c_list.mkl_flag
		dw 0

cid_table_dd	dw 31, at_foreground
		dw 32, at_foreground[4]
		dw 33, at_foreground[8]
		dw 34, at_foreground[12]
		dw 35, at_background
		dw 36, at_background[4]
		dw 37, at_background[8]
		dw 38, at_background[12]
		dw 39, at_palett
		dw 40, at_palett[4]
		dw 41, at_palett[8]
		dw 42, at_palett[12]
		dw 43, config.c_filter.of_max_size
		dw 44, config.c_filter.of_min_size
		dw 0

cid_table_s	dw 50, config.c_apath.wp_mask
		dw 51, config.c_apath.wp_file
		dw 52, config.c_apath.wp_arch
		dw 53, config.c_apath.wp_path
		dw 54, config.c_bpath.wp_mask
		dw 55, config.c_bpath.wp_file
		dw 56, config.c_bpath.wp_arch
		dw 57, config.c_bpath.wp_path
		dw 60, config.c_pending_file
		dw 61, config.c_filter.of_include
		dw 62, config.c_filter.of_exclude
		dw 63, searchstring
		dw 64, replacestring
		dw 65, cp_selectmask
		dw 66, filelist_bat
		dw 67, format_lst
		dw 68, findfilemask
		dw 69, findfilepath
;		dw 71, default_arc
;		dw 72, default_zip
		dw 0

.code	_DZIP

config_read PROC PUBLIC USES si di bx
local fname[WMAXPATH]:BYTE
	invoke	strcpy,addr fname,addr configfile
	invoke	strfcat,addr configfile,addr configpath,addr cp_history
	invoke	inientryid,addr cp_Config,0
	jz	closeini
	invoke	xtol,dx::ax
	cmp	ax,VERSION
	ja	closeini
	cmp	ax,MINVERS
	jb	closeini
	lea	si,cid_table_dw
     @@:
	lodsw
	test	ax,ax
	jz	@F
	invoke	inientryid,addr cp_Config,ax
	mov	cx,ax
	lodsw
	mov	bx,ax
	jz	@B
	invoke	xtol,ds::cx
	mov	[bx],ax
	jmp	@B
     @@:
	lea	si,cid_table_dd
     @@:
	lodsw
	test	ax,ax
	jz	@F
	invoke	inientryid,addr cp_Config,ax
	mov	cx,ax
	lodsw
	mov	bx,ax
	jz	@B
	invoke	xtol,ds::cx
	mov	[bx],ax
	mov	[bx+2],dx
	jmp	@B
     @@:
	lea	si,cid_table_s
     @@:
	lodsw
	test	ax,ax
	jz	closeini
	invoke	inientryid,addr cp_Config,ax
	mov	cx,ax
	lodsw
	jz	@B
	invoke	strcpy,ds::ax,ds::cx
	jmp	@B
closeini:
	invoke	strcpy,addr configfile,addr fname
toend:
	ret
config_read ENDP

history_read PROC PUBLIC USES si di bx
local fname[WMAXPATH]:BYTE
local entry:WORD
local boff:WORD
local xoff:WORD
local loff:WORD
	invoke	malloc,S_HISTORY
	mov	WORD PTR history,ax
	mov	WORD PTR history[2],dx
	jnz	@F
	jmp	toend
     @@:
	invoke	memzero,dx::ax,S_HISTORY
	invoke	strcpy,addr fname,addr configfile
	invoke	strfcat,addr configfile,addr configpath,addr cp_history
	mov	di,WORD PTR history
	mov	entry,0
	test	di,di
	jz	break_cmd
     do:
	invoke	inientryid,addr cp_Directory,entry
	jz	break
	mov	si,ax
	invoke	xtol,ds::si
	mov	loff,ax
	invoke	topenh_atol
	jz	break
	mov	bx,dx
	invoke	topenh_atol
	jz	break
	mov	boff,dx
	invoke	strchr,ds::si,','
	jz	break
	inc	ax
	mov	si,ax
	invoke	filexist,ds::si
	cmp	ax,2
	jne	@F
	les	ax,history
	invoke	strcpy,addr es:[di].S_DIRECTORY.path,ds::si
	mov	ax,loff
	mov	es:[di].S_DIRECTORY.flag,ax
	mov	es:[di].S_DIRECTORY.fcb_index,bx
	mov	ax,boff
	mov	es:[di].S_DIRECTORY.cel_index,ax
     @@:
	add	di,S_DIRECTORY
	inc	entry
	jmp	do
break:
	les	di,history
	add	di,S_HISTORY.h_doskey
	mov	si,MAXDOSKEYS
	xor	bx,bx
do_cmd:
	invoke	inientryid,addr cp_Doskey,bx
	jz	break_cmd
	mov	dx,WORD PTR history[2]
	invoke	strcpy,dx::di,ds::ax
	add	di,MAXDOSKEY
	inc	bx
	dec	si
	jnz	do_cmd
break_cmd:
	invoke	strcpy,addr configfile,addr fname
ifdef __TE__
	invoke	strfcat,addr fname,addr configpath,addr cp_history
	invoke	topenh,addr fname
endif
toend:
	ret
history_read ENDP

config_save PROC PUBLIC USES si di bx
local section[2]:BYTE
local boff:WORD
local xoff:WORD
local loff:WORD
	invoke	strfcat,addr __srcfile,addr configpath,addr cp_history
	invoke	osopen,dx::ax,_A_NORMAL,M_WRONLY,A_CREATETRUNC
	mov	STDO.ios_file,ax
	inc	ax
	jz	toend
	invoke	oinitst,addr STDO,4000h
	jz	error_nomem
	invoke	oprintf,addr cp_format_s,addr cp_Config
	invoke	oprintf,addr cp_format_dw,0,VERSION
	lea	si,cid_table_dw
     @@:
	lodsw
	test	ax,ax
	jz	@F
	mov	cx,ax
	lodsw
	mov	bx,ax
	mov	ax,[bx]
	invoke	oprintf,addr cp_format_dw,cx,ax
	jmp	@B
	lea	si,cid_table_dd
     @@:
	lodsw
	test	ax,ax
	jz	@F
	mov	cx,ax
	lodsw
	mov	bx,ax
	mov	ax,[bx]
	mov	dx,[bx+2]
	invoke	oprintf,addr cp_format_dd,cx,dx::ax
	jmp	@B
     @@:
	lea	si,cid_table_s
     @@:
	lodsw
	test	ax,ax
	jz	@F
	mov	cx,ax
	lodsw
	invoke	oprintf,addr cp_format_e,cx,ds::ax
	jmp	@B
     @@:
	les	di,history
	test	di,di
	jz	flush
	invoke	oprintf,addr cp_format_s,addr cp_Directory
	xor	si,si
     @@:
	les	ax,history
	cmp	es:[di].S_DIRECTORY.path,0
	je	@F
	oprintf("%d=%X,%d,%d,%s\n",si,es:[di].S_DIRECTORY.flag,
		es:[di].S_DIRECTORY.fcb_index,es:[di].S_DIRECTORY.cel_index,
		addr es:[di].S_DIRECTORY.path)
	add	di,S_DIRECTORY
	inc	si
	cmp	si,MAXHISTORY
	jb	@B
     @@:
	invoke	oprintf,addr cp_format_s,addr cp_Doskey
	les	di,history
	lea	di,[di].S_HISTORY.h_doskey
	sub	si,si
     @@:
	les	ax,history
	cmp	BYTE PTR es:[di],0
	je	flush
	invoke	oprintf,addr cp_format_e,si,es::di
	add	di,MAXDOSKEY
	inc	si
	cmp	si,MAXDOSKEYS
	jb	@B
flush:
	invoke	oflush
	invoke	ofreest,addr STDO
ifdef __TE__
	invoke	tsaveh,STDO.ios_file
endif
	invoke	close,STDO.ios_file
	mov	ax,1
toend:
	ret
error_nomem:
	invoke	close,STDO.ios_file
	xor	ax,ax
	jmp	toend
config_save ENDP

cmsavesetup PROC _CType PUBLIC
	.if rsmodal(IDD_DZSaveSetup)
	    .if !config_save()
		invoke eropen,addr __srcfile
		inc ax
	    .endif
	.endif
	ret
cmsavesetup ENDP

historyremove PROC PUBLIC
local historyfile[WMAXPATH]:BYTE
	invoke	strfcat,addr historyfile,addr configpath,addr cp_history
	invoke	_dos_setfileattr,dx::ax,0
	invoke	remove,addr historyfile
	ret
historyremove ENDP

historymove PROC PRIVATE USES si di ; AL direction
local directory:S_DIRECTORY
local dirptr:DWORD
	cmp	WORD PTR history,0
	je	toend
	lea	di,directory
	mov	WORD PTR dirptr+2,ss
	mov	WORD PTR dirptr,di
	lds	si,history
	les	di,dirptr
	mov	cx,S_DIRECTORY
	mov	dx,S_DIRECTORY * (MAXHISTORY-1)
	test	al,al
	jnz	@F
	add	si,dx
     @@:
	rep	movsb
	lds	si,dirptr
	les	di,history
	lds	si,history
	add	si,S_DIRECTORY
	mov	cx,dx
	test	al,al
	jnz	@F
	xchg	si,di
	dec	dx
	add	si,dx
	add	di,dx
	inc	dx
	std
     @@:
	rep	movsb
	lds	si,dirptr
	les	di,history
	mov	cx,S_DIRECTORY
	cld
	test	al,al
	jz	@F
	add	di,dx
     @@:
	rep	movsb
  toend:
	ret
historymove ENDP

historysave PROC USES si di cx dx
	mov	si,cpanel
	mov	si,[si]
	mov	dx,[si]
	sub	ax,ax
	and	dx,_W_ARCHIVE or _W_ROOTDIR
	jnz	@F
	mov	si,offset _bufin
	invoke	fullpath,ds::si,0
	test	ax,ax
	jz	@F
	invoke	strcmp,ds::si,history
	test	ax,ax
	jz	@F
	xor	ax,ax
	invoke	historymove
	invoke	strcpy,history,addr _bufin
	mov	si,cpanel
	mov	ax,[si].S_PANEL.pn_fcb_index
	les	di,history
	mov	es:[di].S_DIRECTORY.fcb_index,ax
	mov	ax,[si].S_PANEL.pn_cel_index
	mov	es:[di].S_DIRECTORY.cel_index,ax
	mov	si,[si]
	mov	ax,[si]
	mov	es:[di].S_DIRECTORY.flag,ax
	inc	ax
     @@:
	ret
historysave ENDP

historytocpanel PROC PRIVATE USES si di
	les	di,history
	xor	ax,ax
	test	di,di
	jz	@F
	cmp	al,es:[di]
	jz	@F
	mov	si,cpanel
	mov	si,[si]
	mov	dx,[si]
	test	dx,_W_ARCHIVE or _W_ROOTDIR
	jnz	@F
	mov	ax,dx
	or	ax,es:[di].S_DIRECTORY.flag
	mov	[si],ax
	mov	ax,es:[di].S_DIRECTORY.fcb_index
	mov	dx,es:[di].S_DIRECTORY.cel_index
	mov	si,cpanel
	mov	[si].S_PANEL.pn_fcb_index,ax
	mov	[si].S_PANEL.pn_cel_index,dx
	mov	ax,di
	mov	dx,es
	invoke	cpanel_setpath
	mov	ax,cpanel
	invoke	panel_redraw
	mov	ax,1
     @@:
	test	ax,ax
	ret
historytocpanel ENDP

doskeysave PROC USES di
	.if strtrim(addr com_base)
	    les di,history
	    mov ax,di
	    .if di
		add di,S_HISTORY.h_doskey
		.if strcmp(es::di,addr com_base)
		    lea ax,[di+MAXDOSKEY]
		    invoke memmove,es::ax,es::di,MAXDOSKEY*(MAXDOSKEYS-1)
		    invoke strcpy,es::di,addr com_base
		.endif
		mov ax,1
	    .endif
	.endif
	ret
doskeysave ENDP

doskeytocommand PROC PRIVATE USES di
	les	di,history
	add	di,S_HISTORY.h_doskey
	sub	ax,ax
	mov	ah,doskey_bindex
	shr	ax,1
	add	di,ax
	invoke	strcpy,addr com_base,es::di
	ret
doskeytocommand ENDP

cmhistory PROC _CType PUBLIC USES si di bx
	les	bx,DLG_Commandline
	mov	ax,es:[bx]
	and	ax,_D_ONSCR
	jz	toend
	invoke	rsopen,IDD_DZHistory
	jz	toend
	push	dx		; twclose
	push	ax
	pushm	IDD_DZHistory
	push	dx
	push	ax
	push	dx		; tdinit
	push	ax
	push	dx		; .copy
	push	ax
	les	di,history
	add	di,S_HISTORY.h_doskey
	add	bx,16
	push	ds
	mov	si,es
	mov	ds,dx
	mov	dx,not _O_STATE
	xor	cx,cx
     @@:
	mov	WORD PTR [bx].S_TOBJ.to_data,di
	mov	WORD PTR [bx].S_TOBJ.to_data[2],si
	cmp	BYTE PTR es:[di],0
	jz	event
	and	[bx],dx
	add	bx,S_TOBJ
	add	di,MAXDOSKEY
	inc	cx
	cmp	cx,MAXDOSKEYS
	jb	@B
	jmp	event
   done:
	call	dlclose
	mov	ax,dx
  toend:
	ret
  event:
	pop	ds
	pop	bx
	pop	es
	mov	es:[bx].S_DOBJ.dl_count,cl
	mov	al,doskey_bindex
	mov	es:[bx].S_DOBJ.dl_index,al
	cmp	al,cl
	jb	@F
	mov	es:[bx].S_DOBJ.dl_index,ch
     @@:
	call	dlinit
	call	rsevent
	test	ax,ax
	jz	done
	dec	ax
	mov	doskey_bindex,al
	inc	ax
	shl	ax,4
	add	bx,ax
	invoke	strcpy,addr com_base,es:[bx].S_TOBJ.to_data
	call	dlclose
	invoke	comevent,KEY_END
	mov	ax,1
	jmp	toend
cmhistory ENDP

cmdoskey_up PROC _CType PUBLIC
	les	bx,DLG_Commandline
	mov	ax,es:[bx]
	and	ax,_D_ONSCR
	jz	toend
	mov	al,1
	cmp	doskey_isnext,al
	jne	@F
	mov	com_base,ah
	jmp	@@01
     @@:
	call	doskeytocommand
	inc	doskey_bindex
	cmp	doskey_bindex,MAXDOSKEYS
	jb	@@01
	mov	doskey_bindex,0
   @@01:
	push	KEY_END
	call	comevent
	mov	ax,1
	mov	doskey_isnext,ah
  toend:
	ret
cmdoskey_up ENDP

cmdoskey_dn PROC _CType PUBLIC
	les	bx,DLG_Commandline
	mov	ax,es:[bx]
	and	ax,_D_ONSCR
	jz	toend
	cmp	doskey_isnext,ah
	jne	@F
	mov	com_base,ah
	jmp	done
     @@:
	cmp	doskey_bindex,0
	jne	@F
	mov	doskey_bindex,MAXDOSKEYS-1
	jmp	cmd
     @@:
	dec	doskey_bindex
    cmd:
	call	doskeytocommand
   done:
	push	KEY_END
	call	comevent
	mov	ax,1
	mov	doskey_isnext,al
  toend:
	ret
cmdoskey_dn ENDP

cmpathleft PROC _CType PUBLIC	; Alt-Left - Previous Directory
	call	historysave
	mov	ax,1
	call	historymove
	call	historytocpanel
	jz	@F
	ret
     @@:
	call	historymove
	ret
cmpathleft ENDP

cmpathright PROC _CType PUBLIC	; Alt-Right - Next Directory
	call	historysave
	xor	ax,ax
	call	historymove
	call	historytocpanel
	jz	@F
	ret
     @@:
	inc	ax
	call	historymove
	ret
cmpathright ENDP

	END
