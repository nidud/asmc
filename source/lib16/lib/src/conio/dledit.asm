; DLEDIT.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include tinfo.inc
include string.inc

tiseto		PROTO
titoend		PROTO
timodal		PROTO
tiputs		PROTO
tiinitcursor	PROTO

	.code

dledit	PROC _CType PUBLIC USES di b:DWORD, rc:DWORD, bz:size_t, oflag:size_t
local	ti:S_TINFO
local	cursor:S_CURSOR
	invoke	cursorget,addr cursor
	mov	di,tinfo
	lea	ax,ti
	mov	tinfo,ax
	invoke	memzero,addr ti,S_TINFO
	mov	al,rc.S_RECT.rc_x
	mov	ti.ti_xpos,ax
	mov	al,rc.S_RECT.rc_y
	mov	ti.ti_ypos,ax
	mov	al,rc.S_RECT.rc_col
	mov	ti.ti_cols,ax
	mov	al,rc.S_RECT.rc_row
	mov	ti.ti_rows,ax
	mov	ax,bz
	mov	ti.ti_bcol,ax
	movmx	ti.ti_bp,b
	mov	ax,_T_OVERWRITE
	.if oflag & _O_CONTR
	    or ax,_T_USECONTROL or _T_SHOWTABS
	.endif
	mov	ti.ti_flag,ax
	call	tiinitcursor
	invoke	getxya,ti.ti_xpos,ti.ti_ypos
	mov	ti.ti_clch,250
	mov	ti.ti_clat,al	; save text color
      ifdef __CLIP__
	.if oflag & _O_DTEXT
	    call tiseto
	    call titoend
	    mov ax,ti.ti_boff
	    add ax,ti.ti_xoff
	    mov ti.ti_cleo,ax
	.endif
      endif
	call	tiseto
	call	timodal
	push	ax
	call	tiputs
	invoke	cursorset,addr cursor
	pop	ax
	mov	tinfo,di
	ret
dledit	ENDP

	END
