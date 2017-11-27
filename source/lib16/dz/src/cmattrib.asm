; CMATTRIB.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include time.inc
include conio.inc
include dos.inc
include io.inc
include string.inc
ifdef __ZIP__
 include dzzip.inc
endif

externdef	scan_fblock:S_WFBLK

ID_RDONLY	equ 1*16
ID_HIDDEN	equ 2*16
ID_SYSTEM	equ 3*16
ID_ARCHIVE	equ 4*16
ID_CREATEDATE	equ 5*16
ID_CREATETIME	equ 6*16
ID_MODDATE	equ 7*16
ID_MODTIME	equ 8*16
ID_ACCESSDATE	equ 9*16
ID_ACCESSTIME	equ 10*16
ID_SET		equ 11*16
ID_CANCEL	equ 12*16

_DZIP	segment

cmfileattrib PROC pascal PRIVATE USES si di bx
local fblk:DWORD
local flag:size_t
local fname:DWORD
local dialog:DWORD
	stom fname
	mov ax,bx
	stom fblk
	mov flag,cx
	.if rsopen(IDD_DZFileAttributes)
	    stom dialog
	    les bx,dialog
	    mov al,_O_FLAGB
	    mov dx,flag
	    .if dl & _A_RDONLY
		or es:[bx][ID_RDONLY],al
	    .endif
	    .if dl & _A_HIDDEN
		or es:[bx][ID_HIDDEN],al
	    .endif
	    .if dl & _A_SYSTEM
		or es:[bx][ID_SYSTEM],al
	    .endif
	    .if dl & _A_ARCH
		or es:[bx][ID_ARCHIVE],al
	    .endif

ifdef __LFN__
	    mov al,_ifsmgr
	    .if al
		mov si,ax
		.if wfindfirst(fname,addr scan_fblock,00FFh) != -1
		    invoke wcloseff,ax
		    mov ax,si
		    mov _ifsmgr,al
		    les bx,dialog
		    invoke twtostr,es:[bx].S_TOBJ.to_data[ID_ACCESSTIME],
			scan_fblock.wf_timeaccess.ft_time
		    invoke dwtolstr,es:[bx].S_TOBJ.to_data[ID_ACCESSDATE],
			scan_fblock.wf_timeaccess.ft_date
		    invoke twtostr, es:[bx].S_TOBJ.to_data[ID_CREATETIME],
			scan_fblock.wf_timecreate.ft_time
		    invoke dwtolstr,es:[bx].S_TOBJ.to_data[ID_CREATEDATE],
			scan_fblock.wf_timecreate.ft_date
		.else
		    invoke dlclose,dialog
		    jmp @F
		.endif
	    .else
endif ; __LFN__

		sub ax,ax
		mov dx,ax
		stom scan_fblock.wf_timecreate
		stom scan_fblock.wf_timeaccess
		les bx,fblk
		mov ax,es:[bx]
		and ax,_A_FATTRIB
		mov WORD PTR scan_fblock.wf_attrib,ax
		lodm es:[bx].S_FBLK.fb_time
		stom scan_fblock.wf_time
		les bx,dialog
		mov ax,_O_STATE
		or es:[bx][ID_CREATEDATE],ax
		or es:[bx][ID_CREATETIME],ax
		or es:[bx][ID_ACCESSDATE],ax
		or es:[bx][ID_ACCESSTIME],ax
ifdef __LFN__
	    .endif
endif ; __LFN__

	    les bx,dialog
	    mov ax,WORD PTR scan_fblock.wf_time
	    invoke twtostr,es:[bx].S_TOBJ.to_data[ID_MODTIME],ax
	    mov ax,scan_fblock.wf_time.ft_date
	    invoke dwtolstr,es:[bx].S_TOBJ.to_data[ID_MODDATE],ax
	    invoke dlinit,dialog
	    invoke dlshow,dialog
	    mov ax,es:[bx]+4
	    add ax,0213h
	    mov dl,ah
	    invoke scpath,ax,dx,21,fname
	    .if dlevent(dialog)
		mov al,_O_FLAGB
		sub dx,dx
		.if es:[bx][ID_RDONLY] & al
		    or dl,_A_RDONLY
		.endif
		.if es:[bx][ID_SYSTEM] & al
		    or dl,_A_SYSTEM
		.endif
		.if es:[bx][ID_ARCHIVE] & al
		    or dl,_A_ARCH
		.endif
		.if es:[bx][ID_HIDDEN] & al
		    or dl,_A_HIDDEN
		.endif
		mov al,BYTE PTR flag
		and al,_A_ARCH or _A_SYSTEM or _A_HIDDEN or _A_RDONLY
		.if al != dl
		    .if BYTE PTR flag & _A_SUBDIR
			mov flag,dx
			.if _dos_setfileattr(fname,0)
			    jmp @F
			.endif
			mov dx,flag
		    .endif
		    invoke _dos_setfileattr,fname,dx
		.endif
		GetTime macro t
		    les bx,dialog
		    invoke strtodw,es:[bx].S_TOBJ.to_data[ID_&t&DATE]
		    mov di,ax
		    les bx,dialog
		    invoke strtotw,es:[bx].S_TOBJ.to_data[ID_&t&TIME]
		endm
		GetTime mod
ifdef __LFN__
		.if _ifsmgr == 0
endif
		    mov si,ax
		    .if osopen(fname,_A_NORMAL,M_RDONLY,A_OPEN) != -1
			push ax
			invoke _dos_setftime,ax,di,si
			call close
		    .endif
ifdef __LFN__
		.else
		    invoke wsetwrdate,fname,di,ax
		    GetTime CREATE
		    invoke wsetcrdate,fname,di,ax
		    GetTime ACCESS
		    invoke wsetacdate,fname,di
		.endif
endif
		invoke dlclose,dialog
		mov ax,cpanel
		call panel_reread
	    .else
		invoke dlclose,dialog
	    .endif
	.endif
      @@:
	ret
cmfileattrib ENDP

cmattrib PROC _CType PUBLIC
	mov ax,cpanel
	.if panel_curobj()
ifdef __ROT__
	    .if !(cx & _A_ROOTDIR)
endif
ifdef __ZIP__
		.if cx & _A_ARCHIVE
		    mov bx,cpanel
		    mov ax,WORD PTR [bx].S_PANEL.pn_wsub
		    invoke cmzipattrib,ax
		.else
		    call cmfileattrib
		.endif
else
		call cmfileattrib
endif ; __ZIP__
ifdef __ROT__
	    .endif
endif
	.endif
	ret
cmattrib ENDP

_DZIP	ENDS

	END

