; FF.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

ifdef __FF__

include alloc.inc
include dos.inc
include dir.inc
include io.inc
include iost.inc
include progress.inc
include string.inc
include syserrls.inc
include conio.inc
include mouse.inc
include keyb.inc
include errno.inc
include ff.inc
include helpid.inc

mklistidd PROTO pascal
mklistadd PROTO
externdef _bufin:BYTE
externdef format_u:BYTE
externdef findfilemask:BYTE
externdef findfilepath:BYTE
externdef IDD_DZFindFile:DWORD

ID_FILE equ 13
ID_GOTO equ 22

OF_MASK equ 14*16
OF_PATH equ 15*16
OF_SSTR equ 16*16
OF_SUBD equ 17*16
OF_CASE equ 18*16
OF_HEXA equ 19*16
OF_FIND equ 20*16
OF_FILT equ 21*16
OF_SAVE equ 22*16
OF_GOTO equ 23*16
OF_QUIT equ 24*16
OF_MSUP equ 25*16
OF_MSDN equ 26*16
OF_GCMD equ OF_MSUP

_DATA	segment

OUTPUT_BINARY	equ 0	; Binary dump (default)
OUTPUT_TEXT	equ 1	; Convert tabs, CR/LF
OUTPUT_LINE	equ 2	; Convert tabs, break on LF

DLG_FindFile	dd ?
FCB_FindFile	dw ?

GCMD_search	label WORD
GCMD KEY_F2,	event_mklist
GCMD KEY_F3,	event_view
GCMD KEY_F4,	event_edit
GCMD KEY_F5,	ffevent_filter
GCMD KEY_F6,	event_toggle_hex
GCMD KEY_F7,	event_find
GCMD KEY_F8,	event_delete
GCMD KEY_F9,	cmfilter_load
GCMD KEY_F10,	event_toggle_format
GCMD KEY_DEL,	event_delete
GCMD KEY_ALTX,	event_exit
		dw 0

ff_basedir	dd ?
cp_formatID	db '[%03d:%03d]',0
cp_format_l	db '(%u)',0

_DATA	ENDS

ff_directory	PROTO _CType directory:DWORD
ff_fileblock	PROTO _CType directory:DWORD, wfblk:DWORD

_DZIP	segment

whilekeyalt PROC PRIVATE	; Delay Alt-Key on exit
	les	bx,keyshift
	mov	bl,es:[bx]
	test	bl,KEY_ALT
	jnz	whilekeyalt
	ret
whilekeyalt ENDP

getcurobj PROC PRIVATE
	mov bx,FCB_FindFile
	.if [bx].S_LOBJ.ll_count
	    mov ax,[bx].S_LOBJ.ll_index
	    add ax,[bx].S_LOBJ.ll_celoff
	    shl ax,2
	    les bx,[bx].S_LOBJ.ll_list
	    add bx,ax
	    mov ax,es:[bx]
	    mov dx,es:[bx+2]
	.endif
	ret
getcurobj ENDP

getcurfile PROC PRIVATE
	call getcurobj
	.if !ZERO?
	    add ax,S_SBLK.sb_file
	.endif
	ret
getcurfile ENDP

putcelid PROC PRIVATE
	les	bx,DLG_FindFile
	mov	ah,00h
	mov	al,es:[bx].S_DOBJ.dl_index
	cmp	al,ID_FILE
	jb	@F
	sub	ax,ax
      @@:
	inc	ax
	mov	bx,FCB_FindFile
	add	ax,[bx].S_LOBJ.ll_index
	mov	cx,[bx].S_LOBJ.ll_count
	les	bx,DLG_FindFile
	mov	bx,es:[bx+4]
	add	bx,0F04h
	mov	dl,bh
	invoke	scputf,bx,dx,0,0,addr cp_formatID,ax,cx
	ret
putcelid ENDP

FFAlloc PROC _CType PRIVATE path:DWORD, offs:DWORD, line:WORD, ll:WORD
local	fblk:DWORD
	push	si
	push	di
	invoke	strlen,path
	add	ax,BLOCKSIZE
	mov	di,ax
	invoke	malloc,ax
	jz	FFAlloc_end
	mov	si,dx
	invoke	memzero,dx::ax,di
	mov	dx,S_SBLK.sb_file[4]
	invoke	strcpy,es::dx,path
	mov	bx,ll
	push	0
	push	[bx].S_LOBJ.ll_count
	call	progress_update
	mov	cx,ax
	mov	bx,ll
	mov	ax,[bx].S_LOBJ.ll_count
	inc	[bx].S_LOBJ.ll_count
	mov	dx,[bx].S_LOBJ.ll_count
	.if dx >= ID_FILE
	    mov dx,ID_FILE
	.endif
	mov	[bx].S_LOBJ.ll_numcel,dx
	shl	ax,2
	les	bx,[bx].S_LOBJ.ll_list
	add	bx,ax
	mov	dx,si
	mov	ax,4
	stom	es:[bx]
	mov	es,dx
	mov	bx,ax
	mov	es:[bx].S_SBLK.sb_size,di
	movmw	es:[bx].S_SBLK.sb_line,line
	movmx	es:[bx].S_SBLK.sb_offs,offs
	mov	ax,bx
	or	cx,cx
	mov	cx,di
	jz	FFAlloc_end
	xor	ax,ax
    FFAlloc_end:
	or	ax,ax
	pop	di
	pop	si
	ret
FFAlloc ENDP

ff_fileblock PROC _CType PRIVATE USES si di directory:DWORD, wfblk:DWORD
local path[WMAXPATH*2]:BYTE
local fblk:DWORD
local offs:DWORD
local line:WORD
local fbsize:WORD
local ioflag:WORD
local iobuf:DWORD
local iosize:WORD
local result:WORD
	mov iosize,4096		; default to _bufin
	mov WORD PTR iobuf+2,ds
	mov WORD PTR iobuf,offset _bufin
	.if malloc(64000)		; try a big buffer..
	    mov iosize,64000
	    stom iobuf
	.endif
      ifdef __3__
	xor	eax,eax
	mov	offs,eax
      else
	xor	ax,ax
	mov	WORD PTR offs,ax
	mov	WORD PTR offs+2,ax
      endif
	mov	di,WORD PTR wfblk
	mov	si,WORD PTR wfblk+2
	mov	STDI.ios_l,ax
	mov	line,ax
	mov	dx,MAXHIT
	mov	result,dx
	mov	bx,FCB_FindFile
	cmp	[bx].S_LOBJ.ll_count,dx
	jnb	ffdofile_end
	mov	result,ax
	invoke	filter_wblk,si::di
	test	ax,ax
	jz	ffdofile_end
	add	di,S_WFBLK.wf_name
	invoke	strfcat,addr path,directory,si::di
	invoke	progress_set,0,si::di,1
	mov	result,ax
	jnz	ffdofile_end
	cmp	WORD PTR directory,ax
	jz	ffdofile_fail
	invoke	cmpwarg,si::di,fp_maskp
	jz	ffdofile_end
	cmp	searchstring,0
	je	ffdofile_found
	les	bx,wfblk
	invoke	osopen,addr path,WORD PTR es:[bx].S_WFBLK.wf_attrib,M_RDONLY,A_OPEN
	mov	si,ax
	inc	ax
	;
	; @v2.33 -- continue seacrh if open fails..
	;
	.if ZERO?
	    ;.if errno == EACCES
	    ;	jmp ffdofile_end
	    ;.endif
	    ;jmp ffdofile_fail
	    jmp ffdofile_end
	.endif
	xor ax,ax
	mov ioflag,ax
	les bx,DLG_FindFile
	.if BYTE PTR es:[bx+OF_CASE] & _O_FLAGB
	    mov ioflag,IO_SEARCHCASE
	.endif
	.if BYTE PTR es:[bx+OF_HEXA] & _O_FLAGB
	    or ioflag,IO_SEARCHHEX
	.endif
    ffdofile_search:
	les	bx,wfblk
	invoke	osearch,si,es:[bx].S_WFBLK.wf_sizeax,iobuf,iosize,ioflag
	stom	offs
	mov	line,cx
	inc	dx
	jz	ffdofile_close
    ffdofile_found:
	invoke	FFAlloc,addr path,offs,line,FCB_FindFile
	jz	ffdofile_abort
	stom	fblk
	mov	di,cx
	invoke	strlen,ff_basedir
	inc	ax
	les	bx,fblk
	mov	es:[bx],ax
	cmp	searchstring,0
	je	ffdofile_end
	invoke	lseek,si,offs,SEEK_SET
	lodm	fblk
	add	ax,di
	sub	ax,INFOSIZE
	invoke	osread,si,dx::ax,INFOSIZE-1
    ifdef __3__
	mov	eax,offs
	inc	eax
	les	bx,wfblk
	cmp	eax,es:[bx].S_WFBLK.wf_sizeax
	jb	@F
	mov	eax,es:[bx].S_WFBLK.wf_sizeax
      @@:
	invoke	lseek,si,eax,SEEK_SET
    else
	lodm	offs
	les	bx,wfblk
	add	ax,1
	adc	dx,0
	cmprm	es:[bx].S_WFBLK.wf_sizeax
	jb @F
	lodm	es:[bx].S_WFBLK.wf_sizeax
      @@:
	invoke	lseek,si,dx::ax,SEEK_SET
    endif
	cmp	result,0
	jne	ffdofile_close
	mov	bx,FCB_FindFile
	cmp	[bx].S_LOBJ.ll_count,MAXHIT
	jb	ffdofile_search
    ffdofile_close:
	invoke	close,si
    ffdofile_end:
	invoke	free,iobuf
	mov	ax,result
	ret
    ffdofile_abort:
	invoke	close,si
    ffdofile_fail:
	mov	result,-1
	jmp	ffdofile_end
ff_fileblock ENDP

ff_directory PROC _CType PRIVATE directory:DWORD
	invoke progress_set,0,directory,0
	.if ZERO?
	    invoke scan_files,directory
	.endif
	ret
ff_directory ENDP

ffsearchinitpath PROC pascal PRIVATE path:DWORD
	les si,path
	mov ah,0
	mov dl,' '
	.if es:[si] == dl
	    inc si
	.endif
	.if BYTE PTR es:[si] == '"'
	    inc si
	    mov dl,'"'
	.endif
	push si
      @@:
	mov al,es:[si]
	test al,al
	jz @F
	inc si
	cmp al,dl
	jne @B
	mov es:[si-1],ah
      @@:
	pop ax
	ret
ffsearchinitpath ENDP

ffsearchpath PROC pascal PRIVATE USES si di directory:DWORD
local	path[WMAXPATH]:BYTE
	movp fp_fileblock,ff_fileblock
	movp fp_directory,ff_directory
	invoke strcpy,addr path,directory
	stom ff_basedir
	.if !path
	    mov path,'"'
	    inc ax
	    mov bx,com_wsub
	    invoke strcpy,dx::ax,[bx].S_WSUB.ws_path
	.endif
	;
	; Multi search using quotes:
	; Find Files: ["Long Name.type" *.c *.asm.......]
	; Location:   ["D:\My Documents" c: f:\doc......]
	;
	.repeat
	    invoke ffsearchinitpath,ff_basedir
	    mov WORD PTR ff_basedir,ax
	    push si
	    .if strlen(ff_basedir)
		push ax
		mov bx,WORD PTR ff_basedir
		dec ax
		add bx,ax
		.if BYTE PTR es:[bx] == '\'
		    mov BYTE PTR es:[bx],0
		.endif
		les bx,DLG_FindFile
		mov di,es:[bx+OF_SUBD]
		movmx fp_maskp,es:[bx].S_TOBJ.to_data[OF_MASK]
		.repeat
		    invoke ffsearchinitpath,fp_maskp
		    mov WORD PTR fp_maskp,ax
		    push dx
		    .if di & _O_FLAGB
			invoke scan_directory,1,ff_basedir
		    .else
			invoke ff_directory,ff_basedir
		    .endif
		    pop dx
		    mov WORD PTR fp_maskp,si
		    les bx,fp_maskp
		    .if dl == '"'
			mov es:[bx-1],dl
		    .endif
		    .break .if !(BYTE PTR es:[bx])
		    mov es:[bx-1],dl
		.until ax
		pop ax
	    .endif
	    pop si
	    mov WORD PTR ff_basedir,si
	    .break .if !(BYTE PTR [si])
	.until !ax
	ret
ffsearchpath ENDP

event_xcell PROC _CType PRIVATE
	call	putcelid
	les	bx,DLG_FindFile
	xor	ax,ax
	mov	al,es:[bx].S_DOBJ.dl_index
	mov	bx,FCB_FindFile
	mov	[bx].S_LOBJ.ll_celoff,ax
	call	dlxcellevent
	ret
event_xcell ENDP

event_hexa PROC _CType PRIVATE
	call	dlcheckevent
	cmp	ax,KEY_SPACE
	je	toggle_hex
	ret
event_hexa ENDP

event_toggle_format PROC _CType PRIVATE
	.if ffflag == OUTPUT_LINE
	    mov ffflag,OUTPUT_BINARY
	.elseif ffflag
	    mov ffflag,OUTPUT_LINE
	.else
	    mov ffflag,OUTPUT_TEXT
	.endif
	call	event_list
	jmp	event_normal
event_toggle_format ENDP

event_toggle_hex PROC _CType PRIVATE
	les	bx,DLG_FindFile
	cmp	es:[bx].S_DOBJ.dl_index,ID_FILE+2
	jne	event_normal
	xor	BYTE PTR es:[bx+OF_HEXA],_O_FLAGB
event_toggle_hex ENDP

toggle_hex PROC _CType PRIVATE
	les bx,DLG_FindFile
	pushm es:[bx+OF_SSTR].S_TOBJ.to_data
	.if BYTE PTR es:[bx+OF_HEXA] & _O_FLAGB
	    call atohex
	.else
	    call hextoa
	.endif
	call event_list
	jmp event_normal
toggle_hex ENDP

event_help PROC _CType PRIVATE
	mov	ax,HELPID_10
	call	view_readme
	ret
event_help ENDP

event_edit PROC _CType PRIVATE
	call	getcurfile
	jz	event_normal
	push	dx
	push	ax
  ifdef __TE__
	mov	es,dx
	mov	bx,ax
	push	es:[bx-6]
	invoke	dlhide,DLG_FindFile
	call	tedit
	invoke	dlshow,DLG_FindFile
	jmp	event_normal
  else
	or	cflag,_C_SWAPFF
	push	4
	call	load_tedit
  endif
event_edit ENDP

event_exit PROC _CType PRIVATE
	call	whilekeyalt
	mov	ax,_C_ESCAPE
	ret
event_exit ENDP

event_view PROC _CType PRIVATE
	les	bx,DLG_FindFile
	cmp	es:[bx].S_DOBJ.dl_index,ID_FILE
	jnb	event_normal
	call	getcurfile
	jz	event_normal
  ifdef __TV__
	les	bx,es:[bx]
    ifdef __MEMVIEW__
	invoke	tview,dx::ax,es:[bx].S_SBLK.sb_offs,0,0
    else
	invoke	tview,dx::ax,es:[bx].S_SBLK.sb_offs
    endif
  else
	invoke	load_tview,dx::ax,0
	cmp	mainswitch,0
	je	event_exit
	or	cflag,_C_SWAPFF
	jmp	event_exit
  endif
event_view ENDP

event_normal PROC _CType PRIVATE
	mov	ax,_C_NORMAL
	ret
event_normal ENDP

ffevent_filter PROC _CType PRIVATE
	call cmfilter
	les bx,DLG_FindFile
	mov bx,es:[bx+4]
	add bx,1410h
	mov cl,bh
	mov ax,7
	.if WORD PTR filter == 0
	    mov al,' '
	.endif
	invoke scputw,bx,cx,1,ax
	jmp event_normal
ffevent_filter ENDP

event_mklist PROC _CType PRIVATE
	push si
	push di
	mov si,FCB_FindFile
	sub ax,ax
	.if [si].S_LOBJ.ll_count != ax
	    .if mklistidd()
		xor di,di
		.while di < [si].S_LOBJ.ll_count
		    les bx,[si].S_LOBJ.ll_list
		    mov ax,di
		    shl ax,2
		    add bx,ax
		    les bx,es:[bx]
		    mov ax,es:[bx]
		    mov mklist.mkl_offspath,ax
		    movmx mklist.mkl_offset,es:[bx].S_SBLK.sb_offs
		    mov dx,es
		    mov ax,bx
		    add ax,S_SBLK.sb_file
		    call mklistadd
		    inc di
		.endw
		invoke close,mklist.mkl_handle
		mov ax,cpanel
		.if panel_state()
		    invoke dlhide,DLG_FindFile
		    mov ax,cpanel
		    call panel_reread
		    invoke dlshow,DLG_FindFile
		.endif
		mov ax,_C_NORMAL
	    .endif
	.endif
	pop di
	pop si
	ret
event_mklist ENDP

event_list PROC _CType PRIVATE
	push	bp
	push	si
	push	di
	sub	sp,8
	mov	bp,sp
	invoke	dlinit,DLG_FindFile
	les	bx,DLG_FindFile
	sub	ax,ax
	mov	al,es:[bx+4]
	add	al,4
	mov	si,ax
	mov	al,es:[bx+5]
	mov	di,ax
	add	di,2
	mov	al,0
	mov	[bp+4],ax
	.repeat
	    mov bx,FCB_FindFile
	    .break .if ax >= [bx].S_LOBJ.ll_numcel
	    add ax,[bx].S_LOBJ.ll_index
	    shl ax,2
	    les bx,[bx].S_LOBJ.ll_list
	    add bx,ax
	    movmx [bp],es:[bx]
	    les bx,[bp]
	    add ax,es:[bx]	; strip search directory from filename
	    mov bx,si
	    mov dx,[bp+4]
	    add dx,di
	    mov bh,dl
	    mov cl,bh
	    add ax,S_SBLK.sb_file
	    mov dx,[bp+2]
	    invoke scpath,bx,cx,25,dx::ax
	    add al,bl
	    mov ah,bh
	    les bx,[bp]
	    mov bx,es:[bx].S_SBLK.sb_line
	    .if bx
		inc bx	; append (<line>) to filename
		mov dl,ah
		invoke scputf,ax,dx,0,7,addr cp_format_l,bx
	    .endif
	    HideMouseCursor
	    push ds
	    push si
	    push di
	    mov bx,si
	    add bx,33
	    mov ax,di
	    add ax,[bp+4]
	    mov bh,al
	    invoke getxyp,bx,ax
	    mov es,dx
	    mov di,ax
	    mov dx,ffflag
	    mov cx,36
	    lds si,[bp]
	    add si,[si].S_SBLK.sb_size
	    sub si,INFOSIZE
	    cld
	    .while cx
		lodsb
		.if dl == OUTPUT_LINE && (al == 10 || al == 13)
		    .break
		.elseif dl && (al == 9 || al == 10 || al == 13)
		    mov ah,al
		    mov al,'\'
		    stosb
		    .if ah == 13
			mov al,'n'
		    .elseif ah == 10
			mov al,'r'
		    .else
			mov al,'t'
		    .endif
		    inc di
		    dec cx
		    .break .if !cx
		.endif
		stosb
		inc di
		dec cx
	    .endw
	    pop di
	    pop si
	    pop ds
	    ShowMouseCursor
	    mov ax,[bp+4]
	    inc ax
	    mov [bp+4],ax
	.until 0
	mov ax,1
	add sp,8
	pop di
	pop si
	pop bp
	ret
event_list ENDP

event_find PROC _CType PRIVATE USES si di
local cursor:S_CURSOR
	les bx,DLG_FindFile
	.if !(es:[bx].S_TOBJ.to_flag[OF_GOTO] & _O_STATE)
	    invoke cursorget,addr cursor
	    call cursoroff
	    mov di,FCB_FindFile
	    mov si,[di].S_LOBJ.ll_count
	    mov di,WORD PTR [di].S_LOBJ.ll_list
	    .while si
		mov bx,FCB_FindFile
		les ax,[bx].S_LOBJ.ll_list
		invoke free,es:[di]
		add di,4
		dec si
	    .endw
	    sub ax,ax
	    mov di,FCB_FindFile
	    mov [di].S_LOBJ.ll_celoff,ax
	    mov [di].S_LOBJ.ll_index,ax
	    mov [di].S_LOBJ.ll_numcel,ax
	    mov [di].S_LOBJ.ll_count,ax
	    invoke dlinit,DLG_FindFile
	    les bx,DLG_FindFile
	    mov ax,es:[bx+4]
	    add ax,0F04h
	    mov dl,ah
	    invoke scputw,ax,dx,9,00C4h
	    invoke progress_open,addr cp_search,0
	    les bx,DLG_FindFile
	  ifdef __3__
	    mov eax,es:[bx].S_TOBJ.to_data[OF_PATH]
	    push eax
	    invoke progress_set,eax,0,MAXHIT+2
	  else
	    lodm es:[bx].S_TOBJ.to_data[OF_PATH]
	    push dx
	    push ax
	    invoke progress_set,dx::ax,0,MAXHIT+2
	  endif
	    call ffsearchpath
	    call progress_close
	    invoke cursorset,addr cursor
	    mov ax,[di].S_LOBJ.ll_count
	    .if ax >= ID_FILE
		mov ax,ID_FILE
	    .endif
	    mov [di].S_LOBJ.ll_numcel,ax
	    call update_cellid
	.endif
	ret
event_find ENDP

update_cellid PROC PRIVATE
	push di
	call putcelid
	call event_list
	les bx,DLG_FindFile
	mov di,FCB_FindFile
	mov cx,ID_FILE
	mov ax,_O_STATE
	.repeat
	    add bx,16
	    or es:[bx],ax
	.untilcxz
	mov bx,WORD PTR DLG_FindFile
	mov ax,not _O_STATE
	mov cx,[di].S_LOBJ.ll_numcel
	.while cx
	    add bx,16
	    and es:[bx],ax
	    dec cx
	.endw
	mov ax,_C_NORMAL
	pop di
	ret
update_cellid ENDP

event_delete PROC _CType PRIVATE
	.if getcurobj()
	    push dx
	    push ax
	    .repeat
		movmx es:[bx],es:[bx+4]
		add bx,4
	    .until !ax
	    call free
	    mov bx,FCB_FindFile
	    dec [bx].S_LOBJ.ll_count
	    mov ax,[bx].S_LOBJ.ll_count
	    mov dx,[bx].S_LOBJ.ll_index
	    mov cx,[bx].S_LOBJ.ll_celoff
	    .if ZERO?
		mov dx,ax
		mov cx,ax
	    .else
		.if dx
		    mov bx,ax
		    sub bx,dx
		    .if bx < ID_FILE
			dec dx
			inc cx
		    .endif
		.endif
		sub ax,dx
		.if ax >= ID_FILE
		    mov ax,ID_FILE
		.endif
		.if cx >= ax
		    dec cx
		.endif
	    .endif
	    mov bx,FCB_FindFile
	    mov [bx].S_LOBJ.ll_index,dx
	    mov [bx].S_LOBJ.ll_celoff,cx
	    mov [bx].S_LOBJ.ll_numcel,ax
	    les bx,DLG_FindFile
	    or ax,ax
	    mov al,cl
	    .if ZERO?
		mov al,ID_FILE
	    .endif
	    mov es:[bx].S_DOBJ.dl_index,al
	    call update_cellid
	.endif
	mov ax,_C_NORMAL
	ret
event_delete ENDP

FFOpen PROC _CType PRIVATE ll:WORD
	mov ax,ll
	invoke memzero,ss::ax,SIZE S_LOBJ
	mov bx,ll
	mov [bx].S_LOBJ.ll_dcount,ID_FILE
	movp [bx].S_LOBJ.ll_proc,event_list
	invoke malloc,(MAXHIT*4)+4
	mov bx,ll
	stom [bx].S_LOBJ.ll_list
	.if ax
	    invoke memzero,dx::ax,(MAXHIT*4)+4
	    inc ax
	.endif
	ret
FFOpen	ENDP

FFClose PROC _CType PRIVATE USES si di ll:WORD
	mov si,ll
	mov ax,WORD PTR [si].S_LOBJ.ll_list
	.if ax
	    xor di,di
	    .while di < [si].S_LOBJ.ll_count
		les bx,[si].S_LOBJ.ll_list
		mov ax,di
		shl ax,2
		add bx,ax
		invoke free,es:[bx]
		inc di
	    .endw
	    invoke free,[si].S_LOBJ.ll_list
	    xor ax,ax
	    mov WORD PTR [si].S_LOBJ.ll_list,ax
	.endif
	ret
FFClose ENDP

FindFile PROC _CType PUBLIC USES si di wspath:DWORD, ll_off:WORD
local sbfile:DWORD
local cursor:S_CURSOR
local oldll:WORD
local ll:S_LOBJ
	movmw oldll,FCB_FindFile
	mov ax,ll_off
	mov FCB_FindFile,ax
	.if !ax
	    lea ax,ll
	    mov FCB_FindFile,ax
	    invoke FFOpen,ax
	    jz findfile_nomem
	.endif
	call clrcmdl
	invoke cursorget,addr cursor
	pushl cs
	push offset event_help
	call thelp_set
	xor si,si
	invoke rsopen,IDD_DZFindFile
	jz findfile_somem
	stom DLG_FindFile
	mov WORD PTR es:[bx].S_TOBJ.to_data[OF_GCMD],offset GCMD_search
	mov WORD PTR es:[bx].S_TOBJ.to_data[OF_GCMD+2],ds
	mov ax,offset findfilemask
	mov dx,ds
	stom es:[bx].S_TOBJ.to_data[OF_MASK]
	mov bx,ax
	.if BYTE PTR [bx] == 0
	    invoke strcpy,dx::ax,addr cp_stdmask
	.endif
	les bx,DLG_FindFile
	mov si,offset searchstring
	mov WORD PTR es:[bx].S_TOBJ.to_data[OF_SSTR],si
	mov WORD PTR es:[bx].S_TOBJ.to_data[OF_SSTR+2],ds
	.if ll_off
	    invoke strcpy,es:[bx].S_TOBJ.to_data[OF_PATH],wspath
	.else
	    lodm wspath
	    stom es:[bx].S_TOBJ.to_data[OF_PATH]
	.endif
	movp es:[bx].S_TOBJ.to_proc[OF_HEXA],event_hexa
	movp es:[bx].S_TOBJ.to_proc[OF_FIND],event_find
	movp es:[bx].S_TOBJ.to_proc[OF_FILT],ffevent_filter
	movp es:[bx].S_TOBJ.to_proc[OF_SAVE],event_mklist
	mov ah,BYTE PTR fsflag
	mov al,_O_FLAGB
	.if ah & IO_SEARCHCASE
	    or es:[bx+OF_CASE],al
	.endif
	.if ah & IO_SEARCHHEX
	    or es:[bx+OF_HEXA],al
	.endif
	.if ah & IO_SEARCHSUB
	    or es:[bx+OF_SUBD],al
	.endif
	mov bx,S_TOBJ.to_proc[20]
	mov cx,ID_FILE
	mov ax,offset event_xcell
	movl dx,cs
	.repeat
	    mov es:[bx],ax
	    movl es:[bx+2],dx
	    add bx,16
	.untilcxz
	invoke dlshow,DLG_FindFile
	invoke dlinit,DLG_FindFile
	mov WORD PTR filter,0
	mov ax,FCB_FindFile
	mov WORD PTR tdllist,ax
	mov WORD PTR tdllist+2,ds
	.if ll_off
	    mov ax,_O_STATE
	    or es:[bx+OF_FIND],ax
	    or es:[bx+OF_GOTO],ax
	    call update_cellid
	.endif
	.repeat
	    .break .if !rsevent(IDD_DZFindFile,DLG_FindFile)
	    mov si,ax
	    mov di,cx
	    les bx,DLG_FindFile
	    mov al,es:[bx].S_DOBJ.dl_index
	    .if al < ID_FILE
		call event_view
		.break .if ax != _C_NORMAL
	    .elseif al == ID_GOTO
		.break
	    .elseif !ll_off
		call event_find
	    .endif
	.until 0
	mov ah,BYTE PTR fsflag
	and ah,not (IO_SEARCHCASE or IO_SEARCHSUB or IO_SEARCHHEX)
	mov al,_O_FLAGB
	les bx,DLG_FindFile
	.if es:[bx+OF_CASE] & al
	    or ah,IO_SEARCHCASE
	.endif
	.if es:[bx+OF_HEXA] & al
	    or ah,IO_SEARCHHEX
	.endif
	.if es:[bx+OF_SUBD] & al
	    or ah,IO_SEARCHSUB
	.endif
	mov BYTE PTR fsflag,ah
	mov al,es:[bx].S_DOBJ.dl_index
	mov ah,00h
	invoke dlclose, DLG_FindFile
	.if dx == ID_GOTO
	    mov bx,FCB_FindFile
	    .if [bx].S_LOBJ.ll_count
		mov ax,cpanel
		.if panel_state()
		    mov bx,FCB_FindFile
		    mov ax,[bx].S_LOBJ.ll_index
		    add ax,[bx].S_LOBJ.ll_celoff
		    les bx,[bx].S_LOBJ.ll_list
		    shl ax,2
		    add bx,ax
		  ifdef __3__
		    mov eax,es:[bx]
		    add ax,S_SBLK.sb_file
		    mov sbfile,eax
		    .if strrchr(eax,'\')
		  else
		    mov dx,es:[bx+2]
		    mov ax,es:[bx]
		    add ax,S_SBLK.sb_file
		    stom sbfile
		    .if strrchr(dx::ax,'\')
		  endif
			mov bx,ax
			mov BYTE PTR es:[bx],0
			mov ax,WORD PTR sbfile
			call cpanel_setpath
		    .endif
		.endif
	    .endif
	.endif
	invoke	FFClose,FCB_FindFile
    findfile_end:
	movmw	FCB_FindFile,oldll
	call	thelp_pop
	invoke	cursorset,addr cursor
	mov	ax,si		; Exit code
	mov	cx,di		; Exit key
	ret
    findfile_somem:
	invoke	FFClose,FCB_FindFile
    findfile_nomem:
	mov	si,-1
	invoke	ermsg,0,addr CP_ENOMEM
	jmp	findfile_end
FindFile ENDP

cmsearch PROC _CType PUBLIC
	invoke FindFile,addr findfilepath,0
	ret
cmsearch ENDP

_DZIP	ENDS
endif
	END
