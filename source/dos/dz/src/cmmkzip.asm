; CMMKZIP.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
ifdef __ZIP__
include io.inc
include ini.inc
include iost.inc
include string.inc
include conio.inc
include dzzip.inc

cpyevent_filter PROTO _CType

PUBLIC	cp_mkzip

extrn	IDD_DZDecompress:DWORD
extrn	cp_compress:BYTE
extrn	cp_decompress:BYTE
extrn	cp_space:BYTE

_DATA	segment

cp_backslash	db '\',0
cp_alfa		db '@',0
cp_mkzip	db 'Create archive',0
default_zip	db 'default.zip',0

_DATA	ENDS

_DZIP	segment

PackerGetSection PROC pascal PRIVATE USES si di Section:DWORD
local ini[WMAXPATH]:BYTE
local DLG_DZHistory:DWORD
local OBJ_DZHistory:DWORD
	.if rsopen(IDD_DZHistory)
	    stom DLG_DZHistory
	    add ax,SIZE S_DOBJ
	    stom OBJ_DZHistory
	    sub si,si
	    .while inientryid(Section,si)
		les di,OBJ_DZHistory
		and es:[di].S_TOBJ.to_flag,not _O_STATE
		invoke strnzcpy,es:[di].S_TOBJ.to_data,dx::ax,128
		inc si
		add WORD PTR OBJ_DZHistory,SIZE S_TOBJ
	    .endw
	    mov ax,si
	    .if ax
		les di,DLG_DZHistory
		mov es:[di].S_DOBJ.dl_count,al
		invoke dlinit,DLG_DZHistory
		.if rsevent(IDD_DZHistory,DLG_DZHistory)
		    les di,DLG_DZHistory
		    shl ax,4
		    add di,ax
		    invoke strcpy,addr ini,es:[di].S_TOBJ.to_data
		.endif
	    .endif
	    invoke dlclose,DLG_DZHistory
	    mov ax,dx
	    mov dx,ss
	.endif
	ret
PackerGetSection ENDP

cmcompress PROC _CType PUBLIC USES si di
local section[128]:BYTE
local list[WMAXPATH]:BYTE
local archive[WMAXPATH]:BYTE
local cmd[WMAXPATH]:BYTE
	.if cpanel_findfirst() && !(cx & _A_ROOTDIR or _A_ARCHIVE)
	    .if cpanel_gettarget()
		mov di,ax
		invoke strfcat,addr archive,dx::di,addr default_zip
		.if PackerGetSection(addr cp_compress)
		    lea cx,section
		    invoke strcpy,ss::cx,dx::ax
		    .if inientryid(dx::ax,2)
			mov cx,ax
			invoke setfext,addr archive,dx::cx
		    .endif
		    mov ax,1
		.endif
	    .endif
	.endif
	.if ax
	    .if rsopen(IDD_DZCopy)
		mov di,ax
		lea si,archive
		mov WORD PTR filter,0
		mov WORD PTR es:[di].S_TOBJ.to_data[16],si
		mov WORD PTR es:[di].S_TOBJ.to_data[18],ss
		mov BYTE PTR es:[di].S_TOBJ.to_count[16],16
		movp es:[di].S_TOBJ.to_proc[3*16],cpyevent_filter
		invoke wcenter,es:[di].S_DOBJ.dl_wp,59,addr cp_compress
		.if dlmodal(dx::ax)
		    ; no unix path
		    ; no mask in directory\[*.*]
		    and mklist.mkl_flag,not (_MKL_UNIX or _MKL_MASK)
		    .if mkziplst_open()
			invoke strcpy,addr list,ss::dx
			.if mkziplst()
			    sub ax,ax
			.else
			    or ax,WORD PTR mklist.mkl_count
			    or ax,WORD PTR mklist.mkl_count+2
			.endif
		    .endif
		    .if ax
			.if inientryid(addr section,0)
			    lea si,cmd
			    invoke strcpy,dx::si,dx::ax
			    invoke strcat,dx::ax,addr cp_space
			    invoke strcat,dx::si,addr archive
			    invoke strcat,dx::ax,addr cp_space
			    .if inientryid(addr section,1)
				invoke strcat,dx::si,dx::ax
			    .else
				invoke strcat,ss::si,addr cp_alfa
			    .endif
			    invoke strcat,dx::si,addr list
			    invoke command,dx::ax
			.endif
		    .endif
		.endif
	    .endif
	.endif
	ret
cmcompress ENDP

cmdecompress PROC _CType PUBLIC USES si di
local DLG_DZDecompress:DWORD
local archive:DWORD
local section[128]:BYTE
local cmd[WMAXPATH]:BYTE
local path[WMAXPATH]:BYTE
	.if cpanel_findfirst() && !(cx & _A_SUBDIR or _A_ROOTDIR or _A_ARCHIVE)
	    stom archive
	    .if cpanel_gettarget()
		lea si,path
		invoke strcpy,ss::si,dx::ax
		.if PackerGetSection(addr cp_decompress)
		    lea cx,section
		    invoke strcpy,ss::cx,dx::ax
		    .if rsopen(IDD_DZDecompress)
			stom DLG_DZDecompress
			mov di,ax
			mov WORD PTR es:[di].S_TOBJ.to_data[16],si
			mov WORD PTR es:[di].S_TOBJ.to_data[18],ss
			invoke dlinit,DLG_DZDecompress
			invoke dlshow,DLG_DZDecompress
			mov ax,es:[di+4]
			add ax,020Eh
			mov dl,ah
			invoke scpath,ax,dx,50,archive
			invoke dlmodal,DLG_DZDecompress
		    .endif
		.endif
	    .endif
	.endif
	.if ax
	    .if inientryid(addr section,0)
		lea si,cmd
		invoke strcpy,dx::si,dx::ax
		invoke strcat,dx::ax,addr cp_space
		.if inientryid(addr section,1)
		    invoke strcat,dx::si,dx::ax
		    invoke strcat,dx::si,addr path
		    invoke strcat,dx::ax,addr cp_space
		    invoke strcat,dx::ax,archive
		.else
		    invoke strcat,ss::si,archive
		    invoke strcat,dx::ax,addr cp_space
		    invoke strcat,dx::si,addr path
		    invoke strcat,dx::ax,addr cp_backslash
		.endif
		invoke command,dx::ax
	    .endif
	.endif
	ret
cmdecompress ENDP

cmmkzip PROC _CType PUBLIC USES si di
local	path[WMAXPATH]:BYTE
	lea di,path
	call cpanel_state
	.if !ZERO?
	    invoke strcpy,ss::di,addr default_zip
	    .if tgetline(addr cp_mkzip,dx::ax,40,WMAXPATH or 8000h)
		.if [di] != ah
		    invoke ogetouth,ss::di
		    mov si,ax
		    .if ax && ax != -1
		      ifdef __ZIP__
			mov bx,cpanel
			mov bx,[bx]
			mov ax,[bx]
			mov [bx].S_PATH.wp_arch,0
			and ax,not _W_ARCHIVE
			or  ax,_W_ARCHZIP
			mov [bx],ax
			add bx,S_PATH.wp_file
			invoke strcpy,ss::bx,addr path
		      endif
			mov bx,di
			push ss
			pop es
			cld?
			mov ax,ZIPHEADERID
			stosw
			mov ax,ZIPENDSENTRID
			stosw
			mov cx,9
			xor ax,ax
			rep stosw
			invoke oswrite,si,ss::bx,SIZE S_ZEND
			invoke close,si
			call ret_update_AB
		    .endif
		.endif
	    .endif
	.endif
	ret
cmmkzip ENDP

_DZIP	ENDS
endif
	END
