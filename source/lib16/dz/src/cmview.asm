; CMVIEW.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include ini.inc
include string.inc
include stdlib.inc
include keyb.inc
include dos.inc
include conio.inc
ifdef __ZIP__
include io.inc
include time.inc
include progress.inc
endif

_DATA	segment

cp_F3		db 'F3',0
cp_F4		db 'F4',0
cp_Alt		db 'Alt',0
cp_Ctrl		db 'Ctrl',0
cp_Shift	db 'Shift',0
cp_section_view db 'View',0
cp_argerror	db 'TVIEW error: %s',0
ifdef __ZIP__
cp_unziptotemp	db 'Unzip file to TEMP',0
cp_missingTEMP	db 'Bad or missing TEMP directory',0
endif

_DATA	ENDS

_DZIP	segment

parse_type PROTO pascal :DWORD, :DWORD

; type 4: F4	- edit
; type 3: Alt	- edit/view
; type 2: Ctrl	- edit/view
; type 1: Shift - edit/view
; type 0: F3	- view

loadiniproc PROC pascal PUBLIC USES si di section:DWORD, filename:DWORD, itype:WORD
local	path[WMAXPATH]:BYTE
	mov di,WORD PTR filename
	mov si,WORD PTR filename+2
	mov al,BYTE PTR itype
	.if al == 4
	    mov ax,offset cp_F4
	.elseif al == 3
	    mov ax,offset cp_Alt
	.elseif al == 2
	    mov ax,offset cp_Ctrl
	.elseif al == 1
	    mov ax,offset cp_Shift
	.else
	    mov ax,offset cp_F3
	.endif
	invoke inientry, section, ds::ax, addr configfile
	.if ax
	    mov bx,ax
	    invoke strnzcpy, addr path, dx::bx, WMAXPATH-1
	    invoke strlen, dx::ax
	    push ax
	    invoke strlen, si::di
	    pop dx
	    add ax,dx
	    .if ax < WMAXPATH
		invoke parse_type, addr path, si::di
		invoke command, addr path
		mov ax,1
	    .else
		xor ax,ax
	    .endif
	.endif
	ret
loadiniproc ENDP

load_tview PROC pascal PUBLIC USES si di filename:DWORD, etype:WORD
local	offs:DWORD
	mov di,[bp+6]
	mov si,[bp+8]
	invoke loadiniproc, addr cp_section_view, si::di, etype
ifdef __TV__
	.if !ax
	    call clrcmdl
	    mov si,di
	    xor ax,ax
	    mov WORD PTR offs,ax
	    mov WORD PTR offs+2,ax
	    cld
	    .while 1	; %view% [-options] [file]
		lodsb
		.break .if !al
		.if al == '"'
		    mov di,si	; start of "file name"
		    @@:
			lodsb
			.if !al
			    jmp ltview_argerror
			.endif
			cmp al,'"'
			jne @B
			xor ax,ax
			mov [si-1],al
		    .break
		.elseif al == '/' && BYTE PTR [si-2] == ' '
		    lodsb
		    or al,20h
		    .if al == 't'
			and tvflag,not _TV_HEXVIEW
		    .elseif al == 'h'
			or tvflag,_TV_HEXVIEW
		    .elseif al == 'o'		; -o<offset> - Start offset
			invoke strtol, ss::si
			stom offs
		    .else
			ltview_argerror:
			invoke ermsg,0,addr cp_argerror,ss::di
			dec ax
			jmp @F
		    .endif
		    .while 1
			lodsb
			.break .if al <= ' '
		    .endw
		    .break .if !al
		    mov di,si
		.endif
	    .endw
ifdef __MEMVIEW__
	    invoke tview,ss::di,offs,0,0
else
	    invoke tview,ss::di,offs
endif
	    xor ax,ax
	.endif
      @@:
endif ; ifdef __TV__
	ret
load_tview ENDP

ifdef __ZIP__

unzip_to_temp PROC PRIVATE
	push si		; DX:BX &S_FBLK
	push di		; DX:AX &S_FBLK.fb_name
	mov si,dx	; return: DX:AX &config.c_pending_file == %TEMP%\name
	mov di,bx
	.if WORD PTR envtemp
	    invoke progress_open,addr cp_unziptotemp,addr cp_copy
	    mov es,si
	    invoke progress_set,addr es:[di].S_FBLK.fb_name,envtemp,es:[di].S_FBLK.fb_size
	    mov bx,cpanel
	    invoke wsdecomp,[bx].S_PANEL.pn_wsub,si::di,envtemp
	    call progress_close
	    .if !ax
		add di,S_FBLK.fb_name
		lea ax,config.c_pending_file
		invoke strfcat,ds::ax,envtemp,si::di
	    .else
		xor ax,ax
	    .endif
	.else
	    invoke ermsg,0,addr cp_missingTEMP
	.endif
	test ax,ax
	pop di
	pop si
	ret
unzip_to_temp ENDP

viewzip PROC PRIVATE
	call unzip_to_temp
	.if ax
	    invoke strcpy,ss::bp,dx::ax
	    invoke load_tview,dx::ax,di
	    .if !ax
		invoke _dos_setfileattr,ss::bp,0
		invoke remove,ss::bp
	    .else
		mov ax,1
	    .endif
	.endif
	ret
viewzip ENDP

ifdef __TE__

zipadd PROC pascal PRIVATE USES si di archive:DWORD, path:DWORD, file:DWORD
	invoke strcpy,addr __srcfile,file
	invoke strcpy,addr __srcpath,dx::ax
	invoke strpath,dx::ax
	invoke strcpy,addr __outpath,path
	invoke strcpy,addr __outfile,archive
	invoke osopen,file,_A_NORMAL,M_RDONLY,A_OPEN
	mov si,ax
	inc ax
	.if ax
	    mov bx,si
	    xor cx,cx
	    mov dx,cx
	    mov ax,4202h
	    int 21h
	    .if !CARRY?
		push dx
		push ax
		invoke close, si
		call dosdate
		push ax
		call dostime
		push ax
		invoke getfattr,file
		push ax
		call wzipadd
	    .else
		invoke close,si
		dec ax
	    .endif
	.endif
	ret
zipadd	ENDP

editzip PROC PUBLIC
	push si
	push di
	call unzip_to_temp
	.if ax
	    invoke strcpy,ss::bp,dx::ax
	    invoke tedit,dx::ax,0
	    mov bx,cpanel
	    mov ax,[bx]
	    add ax,S_PATH.wp_file
	    push ss
	    push ax
	    add ax,S_PATH.wp_arch - S_PATH.wp_file
	    push ss
	    push ax
	    push ss
	    push bp
	    call zipadd
	    invoke _dos_setfileattr,ss::bp,0
	    invoke remove,ss::bp
	    mov ax,cpanel
	    call panel_reread
	.endif
	pop di
	pop si
	ret
editzip ENDP

 endif ; __TE__
endif ; __ZIP__

cm_loadfblk PROC PUBLIC ; (void)
	pop ax	; return adress
	push bp
	push si
	push di
	sub sp,WMAXPATH ; create buffer for file name
	mov bp,sp		; test shift state for F3 or F4
	xor di,di		; DI -> 0 (F3 or F4)
	mov si,ax
	les bx,keyshift
	mov al,es:[bx]
	.if al & KEY_SHIFT	; DI -> 1 (Shift)
	    mov di,1
	.elseif al & KEY_CTRL	; DI -> 2 (Ctrl)
	    mov di,2
	.elseif al & KEY_ALT	; DI -> 3 (Alt)
	    mov di,3
	.endif
	mov ax,cpanel
	call panel_curobj
	.if ZERO?
	    xor cx,cx
	.elseif cx & _A_ARCHIVE
	    .if cx & _A_SUBDIR
		xor cx,cx		; CX -> 0 (subdir in archive)
	    .else
		mov cx,2
	    .endif
	.else
	    .if cx & _A_SUBDIR
		mov cx,3		; CX -> 3 (subdir)
	    .else
		mov bx,cpanel		; CX -> 1 (file)
		mov bx,[bx]
		mov cx,[bx]
		and cx,_W_NETWORK
		.if cx == _W_NETWORK
		    add bx,S_PATH.wp_path
		    invoke strfcat,ss::bp,ds::bx,dx::ax
		.else
		    invoke strcpy,ss::bp,dx::ax
		.endif
		mov cx,1
	    .endif
	.endif
	or cx,cx
	jmp si
cm_loadfblk ENDP

cmview	PROC _CType PUBLIC
	call cm_loadfblk
	.if cx == 1
	    invoke load_tview, dx::ax, di
	.elseif cx == 3
	    call cmsubsize
ifdef __ZIP__
	.elseif cx == 2
	    call viewzip
endif
	.endif
	add sp,WMAXPATH
	pop di
	pop si
	pop bp
	ret
cmview	ENDP

_DZIP	ENDS

	END
