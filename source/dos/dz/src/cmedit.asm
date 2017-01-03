; CMEDIT.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include dir.inc
include ini.inc
include io.inc
include dos.inc
include string.inc
include conio.inc
include tinfo.inc
include stdio.inc
include stdlib.inc

ifdef __TE__
editzip		PROTO
tishow		PROTO _Ctype :WORD
endif

.data
ifdef __TE__
cp_edi		db '*.edi',0
endif

.code _DZIP

ifdef __TE__

topenh_atol PROC PUBLIC
	.if strchr(ds::si,',')
	    inc ax
	    mov si,ax
	    invoke atol,ds::si
	    mov dx,ax
	    mov ax,1
	.endif
	ret
topenh_atol ENDP

topenh PROC pascal PUBLIC USES si di bx fname:PTR BYTE
local section[2]:BYTE
local entry:WORD
local boff:WORD
local xoff:WORD
	mov WORD PTR section,'.'
	mov entry,0
	.repeat
	    mov ax,entry
	    call iniidtostr
	    lea cx,section
	    .break .if !inientry(ss::cx,dx::ax,fname)
	    mov si,ax
	    inc entry
	    invoke atol,ds::si
	    mov di,ax
	    .break .if !topenh_atol()
	    mov bx,dx
	    .break .if !topenh_atol()
	    mov boff,dx
	    .break .if !topenh_atol()
	    mov xoff,dx
	    .break .if !strchr(ds::si,',')
	    inc ax
	    mov si,ax
	    invoke dzexpenviron,dx::ax
	    .continue .if filexist(ds::si) != 1
	    .break .if !topen(ds::si)
	    mov si,tinfo
	    mov [si].S_TINFO.ti_loff,di
	    mov [si].S_TINFO.ti_yoff,bx
	    mov ax,xoff
	    mov [si].S_TINFO.ti_xoff,ax
	    mov ax,boff
	    mov [si].S_TINFO.ti_boff,ax
	.until 0
	ret
topenh ENDP

tsaveh	PROC pascal PUBLIC USES si di bx handle:size_t
local	buf[512]:BYTE
	call	tigetfile
	mov	si,ax
	mov	di,ax
	oswrite(handle,"[.]\r\n",5)
	sub	bx,bx
	.while	si
		sprintf(addr buf,"%d=%d,%d,%d,%d,%s\r\n",bx,
		[si].S_TINFO.ti_loff,
		[si].S_TINFO.ti_yoff,
		[si].S_TINFO.ti_boff,
		[si].S_TINFO.ti_xoff,
		[si].S_TEDIT.ti_file)
	    invoke strlen,addr buf
	    mov cx,ax
	    invoke oswrite,handle,addr buf,cx
	    inc bx
	    mov ax,[si].S_TEDIT.ti_next
	    mov si,ax
	    .break .if di == ax
	    .break .if !tistate()
	.endw
	ret
tsaveh	ENDP

tiloadfiles PROC _CType PUBLIC
local path[WMAXPATH]:BYTE
	.if wgetfile(addr cp_edi,3)
	    push si
	    push di
	    mov si,dx
	    mov di,ax
	    invoke strcpy,addr path,ds::si
	    invoke close,di
	    mov ax,tinfo
	    mov si,ax
	    .if tistate()
		invoke dlclose,addr [si].S_TEDIT.ti_DOBJ
	    .endif
	    invoke topenh,addr path
	    mov ax,tinfo
	    mov di,ax
	    .if tistate()
		invoke tishow,di
	    .endif
	    pop di
	    pop si
	.endif
	ret
tiloadfiles ENDP

topensession PROC PRIVATE
local cu:S_CURSOR
	invoke	cursorget,addr cu
	call	tiloadfiles
	sub	ax,ax
	call	tmodal
	invoke	cursorset,addr cu
	ret
topensession ENDP

tisavefiles PROC _CType PUBLIC USES si
	.if wgetfile(addr cp_edi,2)
	    mov si,ax
	    invoke tsaveh,si
	    invoke close,si
	.endif
	mov ax,_TI_CONTINUE
	ret
tisavefiles ENDP

wedit PROC pascal PRIVATE USES si di bx fcb:DWORD, count:size_t
	.repeat
	    invoke fbffirst,fcb,count
	    .break .if ZERO?
	    mov di,ax
	    and es:[di].S_FBLK.fb_flag,not _A_SELECTED
	    .if !(cx & _A_ARCHIVE or _A_SUBDIR)
		add ax,S_FBLK.fb_name
		invoke topen,dx::ax
	    .endif
	.until ZERO?
	sub ax,ax
	call tmodal
	ret
wedit	ENDP

endif

load_tedit PROC pascal PUBLIC USES si file:DWORD, etype:WORD
local path[WMAXPATH]:BYTE
	invoke strcpy,addr path,file
	mov si,ax
	.if !strchr(dx::ax,'.')
	    invoke strcat,ss::si,addr ds:[cp_dotdot+1]
	.endif
	loadiniproc("Edit",ss::si,etype)
	test ax,ax
ifdef __TE__
	.if ZERO?
	    call clrcmdl
	    mov ax,cpanel
	    .if panel_findnext()
		mov bx,cpanel
		mov bx,WORD PTR [bx].S_PANEL.pn_wsub
		invoke wedit,[bx].S_WSUB.ws_fcb,[bx].S_WSUB.ws_count
	    .else
		invoke tedit,ss::si,0
		call cmcupdate
		sub ax,ax
	    .endif
	.endif
endif
	ret
load_tedit ENDP

rereadab PROC PRIVATE
	push	ax
	mov	ax,panela
	call	panel_reread
	mov	ax,panelb
	call	panel_reread
	pop	ax
	ret
rereadab ENDP

cmedit	PROC _CType PUBLIC
	call	cm_loadfblk
	jz	cmedit_end
ifdef __TE__
	cmp	cx,2
	je	cmedit_zip
endif
	dec	cx
	jnz	cmedit_end
	cmp	di,cx
	jne	@F
	mov	di,4
    @@:
	invoke	load_tedit, dx::ax, di
    cmedit_end:
	add	sp,WMAXPATH
	call	rereadab
	pop	di
	pop	si
	pop	bp
	ret
ifdef __TE__
    cmedit_zip:
	call	editzip
	jmp	cmedit_end
endif
cmedit	ENDP

ifdef __TE__
cmwindowlist PROC _CType PUBLIC
	.if tdlgopen()
	    mov tinfo,ax
	    jmp cmtmodal
	.endif
	ret
cmwindowlist ENDP

cmtmodal PROC _CType PUBLIC
	mov ax,tinfo
	.if tistate()
	    call tmodal
	.else
	    call topensession
	.endif
	call rereadab
	ret
cmtmodal ENDP
endif

	END
