; CMCOPY.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include dos.inc
include iost.inc
include errno.inc
include time.inc
include string.inc
include progress.inc
include conio.inc
include mouse.inc
ifdef __ZIP__
 include dzzip.inc
endif
ifdef __ROT__
 include tinfo.inc
endif

	extrn	cp_copy:BYTE
	extrn	copy_flag:BYTE
	extrn	copy_fast:BYTE
	extrn	copy_filecount:WORD
	extrn	copy_subdcount:WORD
	extrn	CP_DOSER04: BYTE ; "Data error (bad CRC)"


	PUBLIC	cmcopy
	PUBLIC	ret_update_AB
	PUBLIC	format_s
	PUBLIC	format_lu

_DATA	segment

cp_ercopy	db 'There was an error while copying',0
cp_fnisequal	db "You can't copy a file to itself",0
cp_recursive	db "You tried to recursively copy or move a directory",0
cp_needpanel	db "You need two file panels to use this command",0

format_sLsLLs	db '%s',10,'%s',10,10
format_s	db '%s',0
format_sLs	db '%s',10,'%s',0
format_sL_s_	db '%s',10
format_iSi	db "'%s'",0
cp_unixslash	db '/',0
cp_copyto	db "' to",0
copy_jump	dw 0

format_lu	db '%lu',0

_DATA	ENDS

_DZIP	segment

getpanelb PROC PUBLIC
	mov ax,panela
	.if ax == cpanel
	    mov ax,panelb
	.endif
	ret
getpanelb ENDP

error_copy PROC PRIVATE
	cmp	errno,ENOSPC
	je	error_diskfull
	invoke	ermsg,0,addr format_sLs,addr cp_ercopy,addr __outfile
	ret
error_copy ENDP

error_diskfull PROC PRIVATE
	invoke	ermsg,0,addr format_sLsLLs,addr cp_ercopy,
		addr __outfile,sys_errlist[ENOSPC*4]
	ret
error_diskfull ENDP

getcopycount PROC PRIVATE
	push si
	push di
	mov bx,cpanel
	mov bx,WORD PTR [bx].S_PANEL.pn_wsub
	mov cx,[bx].S_WSUB.ws_count
	les di,[bx].S_WSUB.ws_fcb
	mov si,es
	.while cx
	    mov es,si
	    les bx,es:[di]
	    add di,4
	    mov ax,es:[bx]
	    .if ax & _A_SELECTED
		.if ax & _A_SUBDIR
		    inc copy_subdcount
		    push cx
		    add bx,S_FBLK.fb_name
		    invoke recursive,es::bx,addr __srcpath,addr __outpath
		    pop cx
		    .if !ZERO?
			mov copy_flag,_COPY_RECURSIV
			.break
		    .endif
		.endif
		inc copy_filecount
	    .endif
	    dec cx
	.endw
	mov ax,copy_filecount
	add ax,copy_subdcount
	pop di
	pop si
	ret
getcopycount ENDP

cpyevent_filter PROC _CType PUBLIC
	call cmfilter
	les bx,tdialog
	mov bx,es:[bx+4]
	add bx,0510h
	mov dl,bh
	mov ax,' '
	.if WORD PTR filter
	    mov al,7
	.endif
	invoke scputw,bx,dx,1,ax
	mov ax,_C_NORMAL
	ret
cpyevent_filter ENDP

confirm_copy PROC pascal PRIVATE USES si di fblk:DWORD, move:WORD
local	dialog:DWORD
local	result:WORD
	xor bx,bx
	mov si,move
	mov ax,config.c_confirm
	.if si
	    and ax,_C_CONFCOPY
	.else
	    and ax,_C_CONFMOVE
	.endif
	.if ax
	    .if si
		pushm IDD_DZCopy
	    .else
		pushm IDD_DZMove
	    .endif
	    call rsopen
	    .if ax
		stom dialog
		.if si
		    mov WORD PTR filter,0
		    movp es:[bx+3*16+12],cpyevent_filter
		.endif
		invoke dlshow, dialog
		mov di,es:[bx+4]
		add di,0209h
		mov si,offset __outpath
		mov BYTE PTR es:[bx+1*16+2],16
		les bx,fblk
		mov bx,es:[bx]
		.if bx & _A_SELECTED
		    mov bx,di
		    mov ax,copy_filecount
		    add ax,copy_subdcount
		    mov cl,bh
		    invoke scputf,bx,cx,0,0,addr cp_copyselected,ax
		.else
		    mov bx,di
		    mov cl,bh
		    invoke scputw,bx,cx,1,0027h
		    inc bl
		    lodm fblk
		    add ax,S_FBLK.fb_name
		    invoke scpath,bx,cx,38,dx::ax
		    add bl,al
		    invoke scputs,bx,cx,0,0,addr cp_copyto
		    les bx,fblk
		    .if !(BYTE PTR es:[bx] & _A_SUBDIR)
			mov si,offset __outfile
		    .endif
		.endif
		.if copy_flag & _COPY_OARCHIVE
		    mov si,offset __outfile
		.endif
		les bx,dialog
		mov WORD PTR es:[bx].S_TOBJ.to_data[16],si
		mov WORD PTR es:[bx].S_TOBJ.to_data[18],ds
		.if copy_flag & (_COPY_IARCHIVE or _COPY_OARCHIVE)
		    invoke dlinit,dialog
		    or WORD PTR es:[bx+16],_O_STATE
		.endif
		.if move
		    lodm IDD_DZCopy
		.else
		    lodm IDD_DZMove
		.endif
		invoke rsevent,dx::ax,dialog
		invoke dlclose,dialog
		xor ax,ax
		.if dx
		    inc ax
		.endif
	    .endif
	.else
	    inc ax
	.endif
	ret
confirm_copy ENDP

init_copy PROC pascal PUBLIC USES si di fblk:DWORD, docopy:WORD
	xor ax,ax
	mov copy_fast,al
	mov copy_jump,ax		; set if skip file (jump)
	mov copy_flag,al		; type of copy
	mov copy_filecount,ax		; selected files
	mov copy_subdcount,ax
	call cpanel_gettarget		; get __outpath
	.if !ZERO?
	    mov si,ax			; DS:SI = target path
	    call getpanelb		; DS:BX = target panel
	    mov bx,ax
	    mov di,WORD PTR [bx].S_PANEL.pn_wsub; DS:DI = target directory struct
	    mov bx,[bx]
ifdef __ROT__
	    xor ax,ax
	    push bx
	    mov bx,cpanel
	    mov bx,[bx]
	    .if [bx].S_PATH.wp_flag & _W_ROOTDIR
		pop bx
		call notsup
		jmp @F
	    .endif
	    pop bx
	    .if [bx].S_PATH.wp_flag & _W_ROOTDIR
		jmp @F
	    .endif
endif
ifdef __ZIP__
	    mov ax,[bx]
	    and ax,_W_ARCHIVE
	    .if !ZERO?
		.if [di].S_WSUB.ws_count == 1
		    inc copy_fast
		.endif
		and ax,_W_ARCHEXT
		mov al,_COPY_OARCHIVE or _COPY_OEXTFILE
		.if ZERO?
		    mov al,_COPY_OARCHIVE or _COPY_OZIPFILE
		    .if ! BYTE PTR docopy
			call notsup	; moving files to archive..
			jmp @F
		    .endif
		.endif
	    .endif
	    mov copy_flag,al
endif
ifdef __LFN__
	    invoke wlongpath,ss::si,0
	    invoke strcpy,addr __outpath,dx::ax
	    mov bx,cpanel
	    mov bx,WORD PTR [bx].S_PANEL.pn_wsub
	    invoke wlongpath,[bx].S_WSUB.ws_path,0
	    invoke strcpy,addr __srcpath,dx::ax
else
	    invoke strcpy,addr __outpath,ss::si
	    mov bx,cpanel
	    mov bx,WORD PTR [bx].S_PANEL.pn_wsub
	    invoke strcpy,addr __srcpath,[bx].S_WSUB.ws_path
endif
	    lodm fblk
	    add ax,S_FBLK.fb_name
ifdef __LFN__
	    invoke wlongpath,addr __srcpath,dx::ax
	    invoke strcpy,addr __srcfile,dx::ax
else
	    invoke strfcat,addr __srcfile,addr __srcpath,dx::ax
endif
ifdef __ZIP__
	    .if copy_flag & _COPY_OARCHIVE
		invoke strfcat,addr __outfile,addr __outpath,[di].S_WSUB.ws_file
		invoke strcpy,addr __outpath,[di].S_WSUB.ws_arch
		invoke dostounix,dx::ax
	    .else
		invoke strfn,addr __srcfile
		invoke strfcat,addr __outfile,addr __outpath,dx::ax
	    .endif
else
	    invoke strfn,addr __srcfile
	    invoke strfcat,addr __outfile,addr __outpath,dx::ax
endif
	    les bx,fblk
	    mov si,es:[bx].S_FBLK.fb_flag
	    .if si & _A_SELECTED
		call getcopycount	; copy/move selected files
		.if !ax
		    mov al,copy_flag
		    jmp @F
		.endif
		or copy_flag,_COPY_SELECTED
	    .elseif si & _A_SUBDIR
		lodm fblk
		add ax,S_FBLK.fb_name
		invoke recursive,dx::ax,addr __srcpath,addr __outpath
		.if !ZERO?
		    or copy_flag,_COPY_RECURSIV
		.endif
		mov copy_subdcount,1	; copy/move one directory
	    .else
		mov copy_filecount,1	; copy/move one file
	    .endif
	    mov ax,copy_filecount
	    add ax,copy_subdcount
	    .if ax
		les bx,fblk
		push es
		push bx
		push docopy
		mov ax,es:[bx]
		and ax,_A_ARCHIVE
		.if ax
		    mov al,_COPY_IARCHIVE
		    .if ax & _A_ARCHEXT
			or al,_COPY_IEXTFILE
		    .else
			or al,_COPY_IZIPFILE
		    .endif
		.endif
		or copy_flag,al
		call confirm_copy
		.if ax
ifdef __ZIP__
		    .if copy_flag & _COPY_IARCHIVE
			and copy_flag,not _COPY_RECURSIV
		    .else
endif
			invoke strcmp,addr __outfile,addr __srcfile
			.if ZERO?
			    invoke ermsg,0,addr cp_fnisequal
			    jmp @F
			.endif
ifdef __ZIP__
		    .endif
endif
		    .if copy_flag & _COPY_RECURSIV
			invoke ermsg,0,addr cp_recursive
			jmp @F
		    .endif
ifdef __ZIP__
		    .if !(copy_flag & _COPY_OARCHIVE)
endif
			invoke getfattr,addr __outpath
			inc ax
			.if ZERO?
			    invoke mkdir,addr __outpath
			    .if ax
				invoke ermkdir,addr __outpath
				inc ax
				jmp @F
			    .endif
			.endif
ifdef __ZIP__
		    .endif
endif
		    call setconfirmflag
		    mov ax,1
		.endif
	    .endif
	.else
	    invoke ermsg,0,addr cp_needpanel	; need two panels..
	.endif
      @@:
	test ax,ax
	ret
init_copy ENDP

copyfile PROC pascal PUBLIC USES si di file_size:DWORD,
	date:WORD, time:WORD, attrib:WORD
	xor si,si
	mov ax,offset __srcfile
	mov dx,offset __outfile
	call wscopy_open
	.if ax && ax != -1
	    or STDI.ios_flag,IO_USECRC
	    mov STDO.ios_flag,IO_USECRC or IO_UPDTOTAL or IO_USEUPD
	    invoke ocopy,file_size	; copy the file
	    mov si,ax
	    .if ax
		call oflush	; flush the stream
	    .endif
	    invoke oclose,addr STDI	; test CRC value
	    cmpmm STDI.ios_bb,STDO.ios_bb
	    .if ZERO?
		.if !si
		    call error_copy
		    mov ax,offset __outfile
		    call wscopy_remove
		    jmp @F
		.endif
		invoke progress_update,file_size ; test user break (ESC)
		mov si,ax
ifdef __LFN__
		.if _ifsmgr
		    invoke oclose,addr STDO
		    invoke wsetwrdate,addr __outfile,date,time
		.else
endif
		    invoke _dos_setftime,STDO.ios_file,date,time
		    invoke oclose,addr STDO
ifdef __LFN__
		.endif
endif
		mov ax,attrib
		.if al & _A_RDONLY && cflag & _C_CDCLRDONLY
		    mov bx,cpanel
		    mov bx,[bx]
		    mov bx,[bx]
		    .if bx & _W_CDROOM		; remove RDONLY if CD-ROOM
			xor al,_A_RDONLY	; @v2.18
		    .endif
		.endif
		and ax,_A_FATTRIB
		invoke _dos_setfileattr,addr __outfile,ax
		mov ax,si
	    .else
		mov ax,offset CP_DOSER04
		mov bx,errno
		.if bx
		    shl bx,2
		    mov ax,WORD PTR sys_errlist[bx]
		.endif
		invoke ermsg,0,addr format_sL_s_,addr cp_ercopy,ds::ax
	    .endif
	.endif
      @@:
	ret	; return 1: ok, -1: error, 0: jump (if exist)
copyfile ENDP

fblk_copyfile PROC pascal PRIVATE fblk:DWORD, skip_outfile:WORD
	.if filter_fblk(fblk)
	    lodm fblk
	    add ax,S_FBLK.fb_name
	    invoke strfcat,addr __srcfile,addr __srcpath,dx::ax
	    .if BYTE PTR skip_outfile == 0
ifdef __ZIP__
		.if !(copy_flag & _COPY_OARCHIVE)
endif
		    lodm fblk
		    add ax,S_FBLK.fb_name
		    invoke strfcat,addr __outfile,addr __outpath,dx::ax
ifdef __ZIP__
		.endif
endif
	    .endif
	    les bx,fblk
	    invoke progress_set,addr es:[bx].S_FBLK.fb_name,addr __outpath,es:[bx].S_FBLK.fb_size
	    .if ZERO?
		les bx,fblk
		mov dx,es:[bx].S_FBLK.fb_flag
ifdef __ZIP__
		.if dx & _A_ARCHIVE
		    mov bx,cpanel
		    invoke wsdecomp,[bx].S_PANEL.pn_wsub,fblk,addr __outpath
		.else
endif
		    pushm es:[di].S_FBLK.fb_size
		    pushm es:[di].S_FBLK.fb_time
		    push dx
ifdef __ZIP__
		    .if copy_flag & _COPY_OARCHIVE
			call wzipadd
		    .else
endif
			call copyfile
ifdef __ZIP__
		    .endif
		.endif
endif
	    .endif
	.endif
	ret
fblk_copyfile ENDP

fp_copyfile PROC _CType PUBLIC directory:DWORD, wblk:DWORD
	.if filter_wblk(wblk)
	    mov bx,WORD PTR wblk
	    invoke strfcat,addr __srcfile,directory,addr [bx].S_WFBLK.wf_name
ifdef __ZIP__
	    .if !(copy_flag & _COPY_OARCHIVE)
endif
	    invoke strfcat,addr __outfile,addr __outpath,addr [bx].S_WFBLK.wf_name
ifdef __ZIP__
	    .endif
endif
	    .if !progress_set(addr [bx].S_WFBLK.wf_name,addr __outpath,[bx].S_WFBLK.wf_sizeax)
		pushm [bx].S_WFBLK.wf_sizeax
		pushm [bx].S_WFBLK.wf_time
		mov   ax,WORD PTR [bx].S_WFBLK.wf_attrib
		and   ax,_A_FATTRIB
		push  ax
ifdef __ZIP__
		.if copy_flag & _COPY_OARCHIVE
		    call wzipadd
		.else
endif
		    call copyfile
ifdef __ZIP__
		.endif
endif
	    .endif
	.endif
	ret
fp_copyfile ENDP

fp_copydirectory PROC _CType PUBLIC USES si di directory:DWORD
local	path[WMAXPATH]:BYTE
	invoke strlen,addr __srcpath
	mov di,WORD PTR directory+2
	les si,directory
	add si,ax
	.if BYTE PTR es:[si] == '\'
	    inc si
	.endif
	invoke strcpy,addr path,addr __outpath
ifdef __ZIP__
	.if copy_flag & _COPY_OARCHIVE
	    .if __outpath
		invoke strcat,addr __outpath,addr cp_unixslash
	    .endif
	    invoke strcat,addr __outpath,di::si
	    invoke strcat,dx::ax,addr cp_unixslash
	    invoke dostounix,dx::ax
	    mov __srcfile,0
	    .if compressflag & _C_ZINCSUBDIR
		push 0
		push 0
		call dosdate
		push ax
		call dostime
		push ax
		invoke getfattr,directory
		push ax
		call wzipadd
	    .endif
	.else
endif
	    invoke strfcat,addr __outpath,0,di::si
	    invoke mkdir,dx::ax
	    .if ax != -1
		invoke _dos_setfileattr,addr __outpath,0
		.if !ax
		    invoke getfattr, directory
		    and ax,not _A_SUBDIR
		    invoke _dos_setfileattr,addr __outpath,ax
		.endif
	    .endif
ifdef __ZIP__
	.endif
endif
	invoke scan_files, directory
	mov si,ax
	invoke strcpy,addr __outpath,addr path
	mov ax,si
	ret
fp_copydirectory ENDP

copydirectory PROC pascal PRIVATE fblk:DWORD
local	path[WMAXPATH]:BYTE
	add WORD PTR fblk,S_FBLK.fb_name
	invoke progress_set,fblk,addr __outpath,0
	.if !ax
ifdef __ZIP__
	    .if !(copy_flag & _COPY_OARCHIVE)
		invoke mkdir,addr __outpath
	    .endif
else
	    invoke mkdir,addr __outpath
endif
	    invoke strfcat,addr path,addr __srcpath,fblk
	    push dx
	    push ax
	    push ds
	    push offset cp_stdmask
	    push 1
ifdef __ZIP__
	    .if copy_flag & _COPY_OARCHIVE && copy_fast != 1
		mov ax,panela
		.if ax == cpanel
		    mov ax,panelb
		.endif
		; if panel name is not found: use fast copy
		mov bx,ax
		invoke wsearch,[bx].S_PANEL.pn_wsub,fblk
		inc ax
		.if ZERO?
		    inc copy_fast
		    call wzipopen
		    .if !ZERO?
			call mousehide
			call scansub
			dec copy_fast
			call wzipclose
			call mouseshow
		    .else
			dec copy_fast
			dec ax
		    .endif
		    jmp @F
		.endif
	    .endif
endif
	    call scansub
	.endif
    @@:
	ret
copydirectory ENDP

copyselected PROC PRIVATE
	call getpanelb
	mov bx,ax
	push [bx].S_PANEL.pn_fcb_index
	push [bx].S_PANEL.pn_cel_index
	mov cx,si
	.while 1
ifdef __ZIP__
	    .if cx & _A_ARCHIVE
		mov bx,cpanel
		invoke wsdecomp,[bx].S_PANEL.pn_wsub,bp::di,addr __outpath
	    .elseif cl & _A_SUBDIR
else
	    .if cl & _A_SUBDIR
endif
		invoke copydirectory,bp::di
	    .else
		invoke fblk_copyfile,bp::di,0
	    .endif
	    .break .if ax
	    invoke cpanel_deselect,bp::di
	    mov ax,cpanel
	    call panel_findnext
	    mov bp,dx
	    mov di,bx
	    .break .if !ax
	.endw
	mov dx,ax
	call getpanelb
	mov bx,ax
	pop ax
	mov [bx].S_PANEL.pn_cel_index,ax
	pop ax
	mov [bx].S_PANEL.pn_fcb_index,ax
	mov ax,dx
	ret
copyselected ENDP

reread_panels PROC PRIVATE
	mov ax,panela
	call panel_state
	.if ax
	    mov ax,panela
	    call panel_reread
	.endif
	mov ax,panelb
	call panel_state
	.if ax
	    mov ax,panelb
	    call panel_reread
	.endif
	ret
reread_panels ENDP

ret_update_AB PROC
	push ax
	call progress_close
	.if !mainswitch
	    call reread_panels
	.endif
	pop ax
	ret
ret_update_AB ENDP

cmcopy	PROC _CType
	push bp
	push si
	push di
	.if cpanel_findfirst()
	    mov bp,dx
	    mov di,bx
	    mov si,cx
	    .if init_copy(dx::bx,1)
		invoke progress_open,addr cp_copy,addr cp_copy
		movp fp_fileblock,fp_copyfile
		movp fp_directory,fp_copydirectory
ifdef __ZIP__
		.if copy_flag & _COPY_OARCHIVE
		    invoke dostounix,addr __outpath
		    .if copy_flag & _COPY_OZIPFILE && copy_fast
			call wzipopen
			jz cmcopy_ret
		    .endif
		.endif
endif
		.if si & _A_SELECTED
		    call copyselected
		.else
		    .if si & _A_SUBDIR
ifdef __ZIP__
			.if si & _A_ARCHIVE
			    mov bx,cpanel
			    invoke wsdecomp,[bx].S_PANEL.pn_wsub,bp::di,addr __outpath
			.else
endif
			    invoke copydirectory,bp::di
ifdef __ZIP__
			.endif
endif
		    .else
			invoke fblk_copyfile,bp::di,1
		    .endif
		.endif
		cmcopy_upd:
ifdef __ZIP__
		.if copy_flag & _COPY_OZIPFILE && copy_fast
		    call wzipclose
		.endif
		cmcopy_ret:
endif
		call ret_update_AB
	    .endif
	.endif
    cmcopy_end:
	mov copy_fast,0
	pop di
	pop si
	pop bp
	ret
cmcopy	ENDP

_DZIP	ENDS

	END

