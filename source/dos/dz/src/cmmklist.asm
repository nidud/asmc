; CMMKLIST.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include string.inc
include conio.inc
include keyb.inc
include mouse.inc
include io.inc
include iost.inc
include stdio.inc
include dos.inc
include progress.inc

; Make List File from selection set

PUBLIC	cp_ziplst
PUBLIC	CRLF$

extrn	format_u:BYTE
extrn	format_lu:BYTE
extrn	format_lst:BYTE
extrn	filelist_bat:BYTE

MKLID_LIST	equ 1*16
MKLID_APPEND	equ 2*16
MKLID_FORMAT	equ 3*16
MKLID_UNIX	equ 4*16
MKLID_EXLCD	equ 5*16
MKLID_EXLDRV	equ 6*16
MKLID_FILTER	equ 9*16

_DATA	segment

$BACK db '\'		; 5C
BACK$ db '\',0		; '\'
$SIGN db '\'		; 25
SIGN$ db '%',0		; '%'
$TAB9 db '\t',0		; 09
$CRLF db '\n',0		; 0D 0A
TAB9$ db 9,0
CRLF$ db 0Dh,0Ah
NULL$ db 0

$FILE db '%f',0		; File name
$PATH db '%p',0		; Path part of file
$CURD db '%cd',0	; Current directory
$HOME db '%dz',0	; Doszip directory
$name db '%n',0		; Name part of file
$TYPE db '%ext',0	; Extension of file
$SSTR db '%s',0		; Search string
$FCID db '%id',0	; File index or loop counter
$OFFS db '%o',0		; Offset string
$TMP1 db 7,1,0		; unlikely combination 1 '\\'
$TMP2 db 7,2,0		; unlikely combination 2 '\%'

cp_ziplst db	'ziplst',0
$FORSLASH db	'/',0
mklsubcnt dw	?
cp_mklist db	'MKList',0

GCMD_mklist	label WORD
GCMD KEY_F9,	mklevent_LOAD
		dw	0

_DATA	ENDS

_DZIP	segment

mklevent_FILTER PROC _CType PRIVATE
	call cmfilter
	les bx,tdialog
	mov bx,es:[bx+4]
	add bx,0A1Ch
	mov cl,bh
	mov al,' '
	.if WORD PTR filter
	    mov ax,7
	.endif
	invoke scputw,bx,cx,1,ax
	mov ax,_C_NORMAL
	ret
mklevent_FILTER ENDP

mklevent_LOAD PROC _CType PRIVATE USES si di
local	string[256]:BYTE
local	dialog:DWORD
	movmx dialog,tdialog
	les bx,tdialog
	mov al,es:[bx].S_DOBJ.dl_index
	.if !al || al == 2
	    invoke tools_idd,128,addr string,addr cp_mklist
	    mov si,ax
	    call msloop
	    mov ax,_C_NORMAL
	    .if si && si != MOUSECMD
		les di,dialog
		mov si,WORD PTR es:[di+MKLID_FORMAT].S_TOBJ.to_data
		lea di,string
		.if strchr(ss::di,'@')
		    xchg di,ax
		    mov BYTE PTR es:[di],0
		    les bx,dialog
		    .if ax != di
			invoke strcpy,es:[bx+MKLID_LIST].S_TOBJ.to_data,ss::ax
		    .endif
		    inc di
		.endif
		les dx,dialog
		invoke strcpy,es::si,ss::di
		mov ax,_C_REOPEN
	    .endif
	.else
	    mov ax,_C_NORMAL
	.endif
	ret
mklevent_LOAD ENDP

mklistidd PROC pascal PUBLIC USES si di
local DLG_DZMKList:DWORD
	.if rsopen(IDD_DZMKList)
	    stom DLG_DZMKList
	    movp es:[bx].S_TOBJ.to_proc[MKLID_FILTER],mklevent_FILTER
	    mov si,WORD PTR es:[bx+MKLID_LIST].S_TOBJ.to_data+2
	    mov di,WORD PTR es:[bx+MKLID_LIST].S_TOBJ.to_data
	    mov al,_O_FLAGB
	    mov dx,mklist.mkl_flag
	    .if dx & _MKL_APPEND
		or  es:[bx+MKLID_APPEND],al
	    .endif
	    .if dx & _MKL_UNIX
		or  es:[bx+MKLID_UNIX],al
	    .endif
	    .if dx & _MKL_EXCL_CD
		or  es:[bx+MKLID_EXLCD],al
	    .endif
	    .if dx & _MKL_EXCL_DRV
		or  es:[bx+MKLID_EXLDRV],al
	    .endif
	    mov WORD PTR es:[bx+MKLID_APPEND].S_TOBJ.to_data+2,ds
	    mov WORD PTR es:[bx+MKLID_APPEND].S_TOBJ.to_data,offset GCMD_mklist
	    invoke strcpy, es:[bx+MKLID_FORMAT].S_TOBJ.to_data, addr format_lst
	    invoke strcpy, si::di, addr filelist_bat
	    xor ax,ax
	    mov WORD PTR mklist.mkl_offset+2,ax
	    mov WORD PTR mklist.mkl_offset,ax
	    invoke dlinit, DLG_DZMKList
	    invoke dlevent, DLG_DZMKList
	    .if ax
		sub ax,ax
		mov WORD PTR mklist.mkl_count,ax
		mov WORD PTR mklist.mkl_count+2,ax
		mov dx,mklist.mkl_flag
		and dx,not (_MKL_APPEND or _MKL_UNIX or _MKL_EXCL_CD or _MKL_EXCL_DRV)
		or  dx,_MKL_MACRO
		mov al,es:[bx+MKLID_APPEND]
		.if al & _O_FLAGB
		    or dx,_MKL_APPEND
		.endif
		mov al,es:[bx+MKLID_UNIX]
		.if al & _O_FLAGB
		    or dx,_MKL_UNIX
		.endif
		mov al,es:[bx+MKLID_EXLCD]
		.if al & _O_FLAGB
		    or dx,_MKL_EXCL_CD
		.endif
		mov al,es:[bx+MKLID_EXLDRV]
		.if al & _O_FLAGB
		    or dx,_MKL_EXCL_DRV
		.endif
		mov mklist.mkl_flag,dx
		invoke strcpy,addr format_lst,es:[bx+MKLID_FORMAT].S_TOBJ.to_data
		invoke strcpy,addr filelist_bat,si::di
		invoke dlclose,DLG_DZMKList
		.if mklist.mkl_flag & _MKL_APPEND
		    invoke filexist,si::di
		    .if ax == 1
			.if openfile(si::di,M_WRONLY,A_OPEN)
			    mov mklist.mkl_handle,ax
			    invoke lseek,ax,0,SEEK_END
			    mov ax,1
			.endif
			jmp @F
		    .elseif ax == 2
			sub ax,ax
			jmp @F
		    .endif
		.endif
	    .else
		invoke dlclose,DLG_DZMKList
		sub ax,ax
		jmp @F
	    .endif
	    invoke ogetouth,si::di
	    mov mklist.mkl_handle,ax
	    test ax,ax
	.endif
      @@:
	ret
mklistidd ENDP

expand_macro PROC PRIVATE
	push ax
	push bp ; buf
	push ax
	push dx ; old
	push ax
	push cx ; new
	push ax
	push dx
	call strlen
	push ax ; len
	call strxchg
	ret
expand_macro ENDP

mklistadd PROC PUBLIC		; dx:ax=file name
	push bp
	sub sp,WMAXPATH*3
	mov bp,sp
	push si
	push di
	mov bx,ax
	xor ax,ax
	mov cx,ax
	incm mklist.mkl_count
	.if mklist.mkl_flag & _MKL_EXCL_DRV
	    mov es,dx
	    .if BYTE PTR es:[bx+1] == ':'
		add cx,2
	    .endif
	.endif
	add bx,cx
	.if mklist.mkl_flag & _MKL_EXCL_CD
	    add bx,mklist.mkl_offspath
	    sub bx,cx
	.endif
	.if mklist.mkl_flag & _MKL_UNIX
	    invoke dostounix,dx::bx
	    mov bx,ax
	.endif
	lea di,[bp+WMAXPATH*2]
	invoke strcpy,ss::di,dx::bx
	invoke strcpy,ss::bp,addr format_lst
	.if !(mklist.mkl_flag & _MKL_MACRO)
	    invoke strcpy,dx::ax,dx::di
	    jmp mklistadd_nomacro
	.endif
	mov ax,dx
	mov dx,offset $BACK	; '\\'
	mov cx,offset $TMP1	; --> 07 01
	call expand_macro
	mov ax,ss
	mov dx,offset $CRLF	; '\n'
	mov cx,offset CRLF$	; --> 0D 0A
	call expand_macro
	mov ax,ss
	mov dx,offset $TAB9	; '\t'
	mov cx,offset TAB9$	; --> 09
	call expand_macro
	mov ax,ss
	mov dx,offset $SIGN ; '\%'
	mov cx,offset $TMP2	; --> 07 02
	call expand_macro
	mov ax,ss
	mov dx,offset $TMP1	; 07 01
	mov cx,offset BACK$	; --> '\'
	call expand_macro
	mov ax,ss
	mov dx,offset $HOME
	mov cx,offset configpath
	call expand_macro
	mov ax,ss
	mov dx,offset $FILE
	mov cx,di
	call expand_macro
	invoke strfn, ss::di
	mov si,ax
	invoke strrchr, dx::ax, '.'
	mov di,ax
	.if ZERO?
	    mov ax,offset NULL$
	.endif
	mov cx,ax
	mov ax,ss
	mov dx,offset $TYPE
	call expand_macro
	sub ax,ax
	.if ax != di
	    mov [di],al
	.endif
	mov cx,si
	mov ax,ss
	mov dx,offset $name
	call expand_macro
	lea di,[bp+WMAXPATH*2]
	.if di != si
	    mov cx,di
	    xor ax,ax
	    mov [si-1],al
	.else
	    mov cx,offset NULL$
	.endif
	mov ax,ss
	mov dx,offset $PATH
	call expand_macro
	xor ax,ax
	mov cx,di
	mov bx,di
	add bx,mklist.mkl_offspath
	.if bx != cx
	    dec bx
	.endif
	mov [bx],al
	mov ax,ss
	mov dx,offset $CURD
	call expand_macro
	mov ax,ss
	mov dx,offset $SSTR
	mov cx,offset searchstring
	call expand_macro
	mov ax,WORD PTR mklist.mkl_count
	dec ax
	invoke sprintf,ss::di,addr format_u,ax
	mov ax,ss
	mov dx,offset $FCID
	mov cx,di
	call expand_macro
	invoke sprintf,ss::di,addr format_lu,mklist.mkl_offset
	mov ax,ss
	mov dx,offset $OFFS
	mov cx,di
	call expand_macro
	mov ax,ss
	mov dx,offset $TMP2 ; 07 02 00
	mov cx,offset SIGN$ ; --> '%'
	call expand_macro
    mklistadd_nomacro:
	invoke strlen,ss::bp
	.if oswrite(mklist.mkl_handle,ss::bp,ax)
	    mov ax,0
	    .if !(mklist.mkl_flag & _MKL_MACRO)
		invoke oswrite,mklist.mkl_handle,addr CRLF$, 2
		sub ax,2
		.if ax
		    inc ax
		.endif
	    .endif
	.else
	   inc ax
	.endif
    mklistadd_end:
	or ax,ax
	pop di
	pop si
	add sp,WMAXPATH*3
	pop bp
	ret
mklistadd ENDP

fp_mklist PROC _CType PRIVATE path:DWORD, wblk:DWORD
	.if filter_wblk(wblk)
	    add WORD PTR wblk,S_WFBLK.wf_name
	    invoke strfcat,addr __srcfile,path,wblk
	    .if !progress_set(0,dx::ax,1)
		mov ax,offset __srcfile
		call mklistadd
	    .endif
	.endif
	ret
fp_mklist ENDP

mksublist PROC pascal PRIVATE USES si di zip_list:WORD, path:DWORD
local fblk:DWORD
	mov ax,1
	or mklist.mkl_flag,_MKL_MACRO
	mov dx,ds
	.if zip_list == ax
	    or mklist.mkl_flag,_MKL_EXCL_CD
	    mov ax,offset cp_ziplst
	    and mklist.mkl_flag,not _MKL_MACRO
	.else
	    call mklistidd
	    mov ax,offset filelist_bat
	    jz mksublist_end
	.endif
	movl WORD PTR fp_fileblock+2,cs
	movl WORD PTR fp_directory+2,SEG _TEXT
	mov WORD PTR fp_fileblock,offset fp_mklist
	mov WORD PTR fp_directory,offset scan_files
	invoke progress_open,dx::ax,0
	invoke strlen,path
	mov bx,WORD PTR path
	add bx,ax
	.if BYTE PTR es:[bx-1] != '\'
	    inc ax
	.endif
	mov mklist.mkl_offspath,ax
	.if cpanel_findfirst()
	  @@:
	    .if cx & _A_ARCHEXT
		mov mklist.mkl_offspath,0
	    .endif
	    mov di,cx
	    mov [bp-4],bx
	    mov [bp-2],dx
	    invoke strfcat,addr __outpath,path,dx::ax
	    .if !progress_set(0,dx::ax,1)
		.if di & _A_SUBDIR
		    .if di & _A_ARCHIVE
			invoke strcat,addr __outpath,addr BACK$
			.if mklist.mkl_flag & _MKL_MASK
			    mov bx,cpanel
			    mov bx,WORD PTR [bx].S_PANEL.pn_wsub
			    invoke strcat,dx::ax,[bx].S_WSUB.ws_mask
			.endif
			call mklistadd
			inc mklsubcnt
		    .else
			.if scansub(addr __outpath,addr cp_stdmask,0)
			    jmp @F
			.endif
		    .endif
		.else
		    .if filter_fblk(fblk)
			mov dx,ds
			mov ax,offset __outpath
			call mklistadd
		    .endif
		.endif
		les bx,fblk
		and es:[bx].S_FBLK.fb_flag,not _A_SELECTED
		mov ax,cpanel
		call panel_findnext
		jnz @B
	    .endif
	  @@:
	    push ax
	    call progress_close
	    invoke close,mklist.mkl_handle
	    pop ax
	.else
	    jmp @B
	.endif
    mksublist_end:
	ret
mksublist ENDP

mkwslist PROC PRIVATE
	push si
	mov si,ax
	.if cpanel_findfirst()
	    mov bx,cpanel
	    mov bx,[bx]
	    mov ax,[bx]
	    .if ax & _W_ARCHIVE
		add bx,S_PATH.wp_arch
	    .else
		add bx,S_PATH.wp_path
	    .endif
	    invoke mksublist,si,ds::bx
	.endif
	pop si
	ret
mkwslist ENDP

cmmklist PROC _CType PUBLIC
	sub	ax,ax
	call	mkwslist
	mov	ax,cpanel
	call	panel_reread
	ret
cmmklist ENDP

mkziplst_open PROC _CType PUBLIC
	push bp
	sub sp,WMAXPATH
	mov bp,sp
	invoke strfcat,ss::bp,envtemp,addr cp_ziplst
	invoke ogetouth,dx::ax
	add sp,WMAXPATH
	mov dx,bp
	pop bp
	mov mklist.mkl_handle,ax
	.if ax
	    inc ax
	    .if ax
		or cflag,_C_DELTEMP
		mov ax,1
	    .endif
	.endif
	ret
mkziplst_open ENDP

mkziplst PROC _CType PUBLIC
	sub	ax,ax
	mov	mklsubcnt,ax
	inc	ax
	call	mkwslist
	mov	bx,mklsubcnt
	ret
mkziplst ENDP

_DZIP	ENDS

	END
