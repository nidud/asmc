; WDLGOPEN.ASM--
; Copyright (C) 2015 Doszip Developers

include wsub.inc
include fblk.inc
include conio.inc
include string.inc
include dos.inc

extrn	IDD_WOpenFile:DWORD

ID_CNT	equ 13
ID_OK	equ ID_CNT
ID_EXIT equ ID_CNT+1
ID_FILE equ ID_CNT+2
ID_PATH equ ID_CNT+3
ID_L_UP equ ID_CNT+4
ID_L_DN equ ID_CNT+5
O_PATH	equ ID_PATH*16+16
O_FILE	equ ID_FILE*16+16

FLAG_OPEN equ 1
FLAG_LOCK equ 2

	.data
	o_list	dd ?
	o_wsub	dd ?
	a_open	db ?
	dialog	dd ?
	cp_save db 'Save',0

	.code

init_list:
	push	si
	push	di
	push	bp
	push	bx
	push	ds
	cld?
	mov	cx,ID_CNT
	mov	bx,WORD PTR o_list
	mov	[bx].S_LOBJ.ll_numcel,0
	mov	ax,[bx].S_LOBJ.ll_index
	shl	ax,2
	add	ax,WORD PTR [bx].S_LOBJ.ll_list
	mov	dx,WORD PTR [bx].S_LOBJ.ll_list+2
	mov	bp,bx
	les	di,dialog
	mov	bx,es:[di]+4
	add	bx,es:[di]+20
	lea	di,[di].S_TOBJ.to_data[16]
	mov	ds,dx
	mov	si,ax
    event_list_loop:
	lodsw
	or	BYTE PTR es:[di]-7,80h
	test	ax,ax
	jz	event_list_null
	push	es
	push	di
	push	cx
	les	di,[si-2]
	push	ss
	pop	ds
	mov	cx,28
	mov	al,es:[di]
	and	al,_A_SUBDIR
	mov	al,at_foreground[F_Dialog]
	jz	event_list_fg
	mov	al,at_foreground[F_Inactive]
    event_list_fg:
	push	dx
	mov	dl,bh
	invoke	scputfg,bx,dx,cx,ax
	pop	dx
	inc	bh
	mov	ds,dx
	mov	ax,di
	pop	cx
	pop	di
	pop	es
	add	ax,S_FBLK.fb_name
	and	BYTE PTR es:[di]-7,not 80h
	inc	[bp].S_LOBJ.ll_numcel
    event_list_null:
	stosw
	movsw
	add	di,12
	dec	cx
	jnz	event_list_loop
	pop	ds
	pop	bx
	pop	bp
	pop	di
	pop	si
	ret

event_list:
	call	init_list
	invoke	dlinit,dialog
	mov	ax,_C_NORMAL
	retx

read_wsub:
	push	bx
	sub	ax,ax
	mov	bx,WORD PTR o_list
	mov	[bx].S_LOBJ.ll_index,ax
	mov	[bx].S_LOBJ.ll_count,ax
	mov	[bx].S_LOBJ.ll_numcel,ax
	invoke	wsread,o_wsub
	mov	[bx].S_LOBJ.ll_count,ax
	pop	bx
	ret

event_file:
	push	bx
	les	bx,dialog
	mov	dx,es
	mov	ax,WORD PTR es:[bx].S_TOBJ.to_data[O_FILE]
	mov	bx,WORD PTR o_wsub
	test	a_open,FLAG_OPEN
	jnz	event_file_open
	push	dx
	push	ax
	invoke	strrchr,dx::ax,'*'
	pop	ax
	pop	dx
	jnz	event_file_open?
	invoke	strrchr,dx::ax,'?'
	jz	event_file_ret
    event_file_open?:
	test	a_open,FLAG_LOCK
	jnz	event_file_continue
    event_file_open:
	push	ss
	push	bx
	push	dx
	push	ax
	invoke	strnzcpy,[bx].S_WSUB.ws_mask,dx::ax,32
	call	read_wsub
	pushl	cs
	call	event_list
	call	wsearch
	inc	ax
	jz	event_file_continue
    event_file_ret:
	mov	ax,_C_RETURN
    event_file_end:
	pop	bx
	retx
    event_file_continue:
	mov	ax,_C_NORMAL
	jmp	event_file_end

event_path:
	call	read_wsub
	pushl	cs
	call	event_list
	mov	ax,_C_NORMAL
	retx

case_files:
	push	si
	push	di
	push	bx
	mov	bx,WORD PTR o_list
	mov	ax,[bx].S_LOBJ.ll_index
	add	ax,[bx].S_LOBJ.ll_celoff
	shl	ax,2
	add	ax,WORD PTR [bx].S_LOBJ.ll_list
	mov	di,ax
	mov	ax,WORD PTR [bx].S_LOBJ.ll_list+2
	mov	es,ax
	les	di,es:[di]
	mov	si,es
	mov	ax,es:[di]
	test	al,_A_SUBDIR
	jnz	case_directory
	les	bx,dialog
	mov	es:[bx].S_DOBJ.dl_index,ID_FILE
	mov	dx,si
	lea	ax,[di].S_FBLK.fb_name
	invoke	strcpy,es:[bx].S_TOBJ.to_data[O_FILE],dx::ax
	pushl	cs
	call	event_file
	cmp	ax,_C_RETURN
	jne	case_files_continue
	inc	ax
	jmp	case_files_end
    case_files_continue:
	xor	ax,ax
    case_files_end:
	pop	bx
	pop	di
	pop	si
	ret
    case_directory:
	mov	bx,WORD PTR o_wsub
	and	ax,_A_UPDIR
	jz	case_directory_add
	invoke	strfn,[bx].S_WSUB.ws_path
	jz	case_files_continue
	mov	si,ax
	xor	ax,ax
	mov	[si-1],al
	mov	bx,WORD PTR o_list
	mov	[bx].S_LOBJ.ll_celoff,ax
	pushl	cs
	call	event_path
	invoke	wsearch,o_wsub,ds::si
	cmp	ax,-1
	je	case_files_continue
	;mov	bx,o_list
	cmp	ax,ID_CNT
	jnb	case_directory_index
	les	bx,dialog
	mov	es:[bx].S_DOBJ.dl_index,al
	jmp	case_directory_event
    case_directory_index:
	mov	[bx].S_LOBJ.ll_index,ax
    case_directory_event:
	pushl	cs
	call	event_list
	jmp	case_files_continue
    case_directory_add:
	push	bx
	les	bx,dialog
	mov	es:[bx].S_DOBJ.dl_index,al
	pop	bx
	mov	dx,si
	lea	ax,[di].S_FBLK.fb_name
	invoke	strfcat,[bx].S_WSUB.ws_path,0,dx::ax
	pushl	cs
	call	event_path
	jmp	case_files_continue

wdlgopen PROC _CType PUBLIC USES si di bx apath:PTR BYTE, amask:PTR BYTE, asave:size_t
local	wsub:	S_WSUB
local	path:	S_PATH
local	list:	S_LOBJ
	mov	ax,asave
	mov	a_open,al
	mov	dx,ss
	mov	es,dx
	cld?
	lea	di,list
	mov	WORD PTR o_list+2,ss
	mov	WORD PTR o_list,di
	mov	cx,(SIZE S_LOBJ + SIZE S_PATH)/2
	sub	ax,ax
	rep	stosw
	mov	si,di
	mov	wsub.ws_count,ax
	mov	wsub.ws_maxfb,5000
	mov	WORD PTR o_wsub,di
	mov	ax,dx
	mov	WORD PTR o_wsub+2,ax
	mov	WORD PTR wsub.ws_flag+2,ax
	mov	WORD PTR wsub.ws_mask+2,ax
	mov	WORD PTR wsub.ws_path+2,ax
	mov	WORD PTR wsub.ws_file+2,ax
	mov	WORD PTR wsub.ws_arch+2,ax
	lea	ax,path.wp_flag
	mov	WORD PTR wsub.ws_flag,ax
	lea	ax,path.wp_mask
	mov	WORD PTR wsub.ws_mask,ax
	lea	ax,path.wp_path
	mov	WORD PTR wsub.ws_path,ax
	lea	ax,path.wp_file
	mov	WORD PTR wsub.ws_file,ax
	lea	ax,path.wp_arch
	mov	WORD PTR wsub.ws_arch,ax
	invoke	strcpy,wsub.ws_mask,amask
	invoke	strcpy,wsub.ws_path,apath
	sub	di,di
	invoke	wsopen,addr wsub
	jz	wdlgopen_end
	invoke	rsopen,IDD_WOpenFile
	mov	si,dx
	jz	wdlgopen_wsclose
	stom	dialog
	invoke	dlshow,dx::ax
	les	bx,dialog
	lodm	wsub.ws_path
	stom	es:[bx].S_TOBJ.to_data[O_PATH]
	mov	es:[bx].S_TOBJ.to_count[O_PATH],16
	invoke	strcpy,es:[bx].S_TOBJ.to_data[O_FILE],wsub.ws_mask
	movl	ax,cs
	movl	WORD PTR list.ll_proc+2,ax
	movl	WORD PTR es:[bx].S_TOBJ.to_proc[O_FILE+2],ax
	movl	WORD PTR es:[bx].S_TOBJ.to_proc[O_PATH+2],ax
	mov	WORD PTR list.ll_proc,offset event_list
	mov	WORD PTR es:[bx].S_TOBJ.to_proc[O_FILE],offset event_file
	mov	WORD PTR es:[bx].S_TOBJ.to_proc[O_PATH],offset event_path
	mov	list.ll_dcount,ID_CNT
	mov	list.ll_celoff,ID_CNT
	movmx	list.ll_list,wsub.ws_fcb
	test	a_open,FLAG_OPEN
	jnz	wdlgopen_open
	mov	dl,es:[bx]+5
	mov	al,es:[bx]+4
	add	al,21
	invoke	scputs,ax,dx,0,0,addr cp_save
    wdlgopen_open:
  ifdef __LFN__
	cmp	_ifsmgr,0
	je	wdlgopen_read
	mov	path.wp_flag,_W_LONGNAME
    wdlgopen_read:
  endif
	call	read_wsub
	call	init_list
	invoke	dlinit,dialog
    wdlgopen_event:
	invoke	dllevent,dialog,addr list
	jz	wdlgopen_twclose
	cmp	ax,ID_CNT
	ja	wdlgopen_break
	call	case_files
	jz	wdlgopen_event
    wdlgopen_break:
	les	bx,dialog
	invoke	strfcat,wsub.ws_path,0,es:[bx].S_TOBJ.to_data[O_FILE]
	mov	di,ax
	test	a_open,FLAG_LOCK
	jz	wdlgopen_twclose
	invoke	strrchr,dx::ax,'.'
	jnz	wdlgopen_twclose
    wdlgopen_addext:
	lodm	amask
	inc	ax
	invoke	strcat,ss::di,dx::ax
    wdlgopen_twclose:
	invoke	dlclose,dialog
    wdlgopen_wsclose:
	invoke	wsclose,addr wsub
	mov	ax,di
	mov	dx,ax
	test	ax,ax
	jz	wdlgopen_end
	mov	dx,ss
    wdlgopen_end:
	ret
wdlgopen ENDP

	END