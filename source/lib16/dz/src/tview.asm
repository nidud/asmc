; TVIEW.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT
;
; 02/10/1998
;
; Change history:
; 2013-03-06 - added Memory View (doszip)
; 12/28/2011 - removed Binary View (doszip)
;	     - removed Class View (doszip)
;	     - removed View Memory (doszip)
;	     - added zoom function (F11)
; 08/02/2010 - added Class View
; 10/10/2009 - fixed bug in Clipboard
; 10/10/2009 - new malloc() and free()
; 11/15/2008 - added function Seek
; 11/13/2008 - Moved Binary View to F4
;	     - added switch /M, view memory [00000..FFFFF]
; 09/10/2008 - Divide error in putinfo(percent)
;	     - command END  in dump text (F2) moves to top of file
;	     - command UP   in dump text (F2) moves to top of file
;	     - command PGUP in dump text (F2) moves to top of file
;	     - command END  in hex view	 (F4) offset not aligned
;	     - command END  in HEX and BIN -- last offset + 1 < offset
;	     - added short key Ctrl+End -- End of line (End right)
;	     - added IO Bit Stream
; 04/20/2007 - added switch /O<offset>
; 03/15/2007 - fixed Short-Key ESC on zero byte files
; 03/12/2007 - added Binary View
;
include version.inc
include libc.inc
include alloc.inc
include string.inc
include stdio.inc
include stdlib.inc
include io.inc
include dir.inc
include dos.inc
include errno.inc
include iost.inc
include clip.inc
include conio.inc
include mouse.inc
include keyb.inc
include math.inc
include ini.inc
include macro.inc
include tview.inc

	public	tview

	extrn	tvflag: byte
	extrn	fsflag: byte
	extrn	IDD_TVCopy:dword
	extrn	IDD_TVSeek:dword
	extrn	IDD_TVMenusline:dword
	extrn	IDD_TVStatusline:dword
    ifdef __TVEXE__
	extrn	IDD_TVHelpEXE:dword
    else
	extrn	IDD_TVHelp:dword
    endif

	extrn	format_lu:byte

MAXLINES	equ 256

S_TVIEW		STRUC
tv_filename	dd ?
tv_offset	dd ?
ifdef __MEMVIEW__
tv_address	dd ?
endif
tv_fsize	dd ?
tv_dialog	dd ?		; main dialog pointer
tv_rowcnt	dw ?		; max lines (23/48)
tv_lcount	dw ?		; lines on screen
tv_scount	dd ?		; bytes on screen
tv_maxcol	dd ?		; max linesize on screen
tv_curcol	dd ?		; current line offset (col)
tv_screen	dd ?		; screen buffer
tv_menusline	dd ?
tv_statusline	dd ?
tv_switch	dw ?		; main switch
tv_cursor	S_CURSOR <>	; cursor (old)
tv_bsize	dw ?		; buffer size
tv_xpos		dw ?		; temp (mouse)
tv_ypos		dw ?		; temp (mouse)
tv_zpos		dw ?		; temp (mouse)
tv_tmp		dd ?		; temp 32
tv_line_table	dd  50 dup(?)	; line offset in file
tv_static_count dw ?		; line count
tv_static_table dd MAXLINES dup(?) ; offset of first <MAXLINES> lines
ifdef __CLASSVIEW__
tv_tdialog	dd ?
tv_CLDLG	S_DOBJ <?>
tv_CLOBJ	S_TOBJ CLCOUNT dup(<?>)
endif
S_TVIEW		ENDS

_DATA	SEGMENT

format_3d	db '%3d',0
format_8ld	db '%-8ld',0
format_08Xh	db '%08lXh',0
format_010lu	db '%010lu',0

ifdef __MEMVIEW__
	public	tvmem_offs
	public	tvmem_size
tvmem_offs	dd 00000000h
tvmem_size	dd 000FFFFFh
cp_memory	db 'MEMORY',0
endif

ifdef __CLASSVIEW__

format_byte	label size_t
	dw	offset format_d
	dw	offset format_u
	dw	offset format_02X
	dw	offset format_b

format_word	label size_t
	dw	offset format_d
	dw	offset format_u
	dw	offset format_04X
	dw	offset format_lb

format_dword	label size_t
	dw	offset format_ld
	dw	offset format_lu
	dw	offset format_08X
	dw	offset format_lbb

cp_tcl		db '*.tcl',0
cp_class	db 'Class'
DLG_TVClass	dd ?

M_WZIP	macro val, count
	db 0F0h or ((count and 0FF00h) shr 8)
	db count and 00FFh
	db val
	endm

S_OOBJ		STRUC
ro_flag		dw ?
ro_mem		db ?
ro_key		db ?
ro_rcx		db ?
ro_rcy		db ?
ro_rcc		db ?
ro_rcr		db ?
S_OOBJ		ENDS

TVABOUT_RC label word
	dw	1116		; Alloc size
	S_OOBJ	<005Ch,1,0,15,7,50,10>
	S_OOBJ	<_O_PBUTT,0,'O',20,8,8,1>
	M_WZIP	50h,50
	M_WZIP	2Ah,50*7+20
	M_WZIP	50h,3
	db	5Ch
	M_WZIP	50h,4
	M_WZIP	2Ah,50*2+20
	M_WZIP	' About',22
	M_WZIP	' The Doszip Commander Text Viewer v',78
	db	VERS?
	M_WZIP	' Copyright (c) 97-2016 Doszip Developers',12
	M_WZIP	' ',11
	M_WZIP	'Ä',39
	M_WZIP	' License:     GNU General Public License',11
%	M_WZIP	' Build Date:  &@Date  Time: &@Time',11
	M_WZIP	' OK   ',79
	db	'Ü'
	M_WZIP	' ',42
	M_WZIP	'ß',8
	M_WZIP	' ',21

endif

cp_deci		db 'Dec'
cp_hex		db 'Hex  '
cp_ascii	db 'Ascii'
cp_wrap		db 'Wrap  '
cp_unwrap	db 'Unwrap'
cp_byte		db 'byte',0

key_global label size_t
	dw	KEY_F1
	dw	KEY_F2
	dw	KEY_F3
	dw	KEY_F4
	dw	KEY_F5
	dw	KEY_F6
	dw	KEY_F7
  ifdef __BINVIEW__
	dw	KEY_F8
  endif
	dw	KEY_F10
	dw	KEY_ESC
	dw	KEY_ALTX
	dw	KEY_CTRLF5
	dw	KEY_ALTF5
	dw	KEY_CTRLB
	dw	KEY_CTRLM	; Toggle menus line on/off	Ctrl-M
	dw	KEY_CTRLS	; Toggle status line on/off	Ctrl-S
	dw	KEY_F11

global_count = (($ - offset key_global) / size_l)

key_local label size_t
	dw	KEY_UP
	dw	KEY_DOWN
	dw	KEY_PGUP
	dw	KEY_PGDN
	dw	KEY_LEFT
	dw	KEY_RIGHT
	dw	KEY_HOME
	dw	KEY_END
	dw	KEY_CTRLL
	dw	KEY_CTRLE
	dw	KEY_CTRLX
	dw	KEY_CTRLR
	dw	KEY_CTRLC
	dw	KEY_CTRLUP
	dw	KEY_CTRLDN
	dw	KEY_CTRLLEFT
	dw	KEY_CTRLRIGHT
	dw	KEY_SHIFTF3
	dw	KEY_CTRLEND
	dw	KEY_CTRLHOME
ifdef __CLASSVIEW__
	dw	KEY_ENTER
	dw	KEY_KPENTER
	dw	KEY_CTRLF2
	dw	KEY_CTRLF3
endif

local_count = (($ - offset key_global) / size_l)

proc_label label size_t
	dw	cmhelp
	dw	cmwrap
	dw	cmsearch
	dw	cmhex
	dw	cmcopy
	dw	cmoffset
	dw	cmseek
  ifdef __BINVIEW__
	dw	cmbinary
  endif
	dw	cmquit
	dw	cmquit
	dw	cmquit
	dw	cmcolor
	dw	cmconsole
	dw	cmconsole
	dw	event_togglemline
	dw	event_togglesline
	dw	event_togglesize
	dw	event_UP
	dw	event_DOWN
	dw	event_PGUP
	dw	event_PGDN
	dw	event_LEFT
	dw	event_RIGHT
	dw	event_HOME
	dw	event_END
	dw	event_search
	dw	event_UP
	dw	event_DOWN
	dw	event_PGUP
	dw	event_PGDN
	dw	event_PGUP
	dw	event_PGDN
	dw	event_PGLEFT
	dw	event_PGRIGHT
	dw	event_search
	dw	event_toend
	dw	event_tostart
ifdef __CLASSVIEW__
	dw	event_ENTER
	dw	event_ENTER
	dw	event_clsave
	dw	event_clload
endif

ifdef __MOUSE__

label_scroll label size_t
	dw	mouse_scroll_delay
	dw	mouse_scroll_up
	dw	mouse_scroll_down
	dw	mouse_scroll_left
	dw	mouse_scroll_right

endif

DLG_Textview	S_DOBJ <?>
UseClipboard	db ?
rsrows		db 24

_DATA	ENDS

ifdef DEBUG
_DZIP	SEGMENT WORD USE16 public 'CODE'
	ASSUME CS:_DZIP, DS:DGROUP
else
.code
endif

ifdef __MEMVIEW__
normalize:
	test	dx,0FFF0h
	jz	@F
	push	cx
	mov	cl,dh
	shl	dx,4
	add	ax,dx
	adc	cl,0
	shr	cl,4
	mov	dl,cl
	mov	dh,0
	pop	cx
    @@:
	ret
endif

cmp_bbscount1_fsize:
  ifndef __16__
	mov eax,[bp].S_TVIEW.tv_scount
	add eax,STDI.ios_bb
  else
	lodm [bp].S_TVIEW.tv_scount
	add ax,word ptr STDI.ios_bb
	adc dx,word ptr STDI.ios_bb+2
  endif

cmp_dxax1_fsize:
  ifndef __16__
	inc eax
	cmp eax,[bp].S_TVIEW.tv_fsize
	ret
  else
	add ax,1
	adc dx,0
  endif

cmp_dxax_fsize:
	cmp dx,word ptr [bp].S_TVIEW.tv_fsize+2
	jne @F
	cmp ax,word ptr [bp].S_TVIEW.tv_fsize
      @@:
	ret

cmp_dxax_bb:
	cmp dx,word ptr STDI.ios_bb+2
	jne @F
	cmp ax,word ptr STDI.ios_bb
    @@:
	ret

cmp_bx_fsize:
	mov	ax,[bx]
	mov	dx,[bx+2]
	jmp	cmp_dxax_fsize

add_offset:
	push	bx
	lea	bx,[bp].S_TVIEW.tv_line_table
	mov	ax,[bp].S_TVIEW.tv_lcount
	shl	ax,2
	add	bx,ax
	lodm	[bp].S_TVIEW.tv_offset
	mov	[bx],ax
	mov	[bx+2],dx
	inc	[bp].S_TVIEW.tv_lcount
	pop	bx
	ret

getlinesize:
	shl	ax,2
	lea	bx,[bp].S_TVIEW.tv_line_table
	add	bx,ax
	mov	dx,[bx+6]
	mov	ax,[bx+4]
	mov	cx,[bx+2]
	mov	bx,[bx]
	sub	ax,bx
	sbb	dx,cx
	ret

setmaxcol:
	sub	cx,cx
    setmaxcol_00:
	cmp	cx,[bp].S_TVIEW.tv_lcount
	jnb	setmaxcol_02
	mov	ax,cx
	push	bx
	push	cx
	call	getlinesize
	pop	cx
	pop	bx
	cmp	dx,word ptr [bp].S_TVIEW.tv_maxcol+2
	jne	@F
	cmp	ax,word ptr [bp].S_TVIEW.tv_maxcol
      @@:
	jbe	setmaxcol_01
	stom	[bp].S_TVIEW.tv_maxcol
    setmaxcol_01:
	inc	cx
	jmp	setmaxcol_00
    setmaxcol_02:
	ret

getc:
	call	ogetc
	jz	getc_clc	; eof
	add	word ptr [bp].S_TVIEW.tv_offset,1
	adc	word ptr [bp].S_TVIEW.tv_offset+2,0
    getc_cmp:
	cmp	al,13
	je	getc_stc
	cmp	al,10
	je	getc_stc
    getc_clc:	; CF clear: normal byte or eof
	clc
	ret
    getc_stc:	; CF set: new line
	inc	ah
	stc
	ret

ungetc:
	call	oungetc
	jz	getc_clc
	sub	word ptr [bp].S_TVIEW.tv_offset,1
	sbb	word ptr [bp].S_TVIEW.tv_offset+2,0
	jmp	getc_cmp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

read_static_table:	; offset of first <MAXLINES> lines
	push	di
	lea	di,[bp].S_TVIEW.tv_static_table
	xor	ax,ax
	cwd
	mov	[di],ax
	mov	[di+2],ax
	add	di,4
	mov	word ptr [bp].S_TVIEW.tv_offset,ax
	mov	word ptr [bp].S_TVIEW.tv_offset+2,ax
	mov	[bp].S_TVIEW.tv_static_count,1
	call	oseek_dxax
	jz	static_table_05
    static_table_00:
	call	getc
	jc	static_table_02
	jnz	static_table_00
    static_table_01:
	call	static_table_add
	call	static_table_add
	dec	[bp].S_TVIEW.tv_static_count
	jmp	static_table_04
    static_table_02:
	call	getc
	jz	static_table_01
	jc	static_table_03
	call	ungetc
    static_table_03:
	call	static_table_add
	mov	ax,[bp].S_TVIEW.tv_static_count
	cmp	ax,MAXLINES-3
	jna	static_table_00
    static_table_04:
	dec	[bp].S_TVIEW.tv_static_count
    static_table_05:
	pop	di
	ret
    static_table_add:
	lodm	[bp].S_TVIEW.tv_offset
	stom	[di]
	add	di,4
	inc	[bp].S_TVIEW.tv_static_count
	ret

read_line_table:; read line offset in file
	push	si
	mov	[bp].S_TVIEW.tv_lcount,1
	lodm	STDI.ios_bb
	mov	word ptr [bp].S_TVIEW.tv_line_table,ax
	mov	word ptr [bp].S_TVIEW.tv_line_table+2,dx
	stom	[bp].S_TVIEW.tv_offset
	mov	bl,tvflag
  ifdef __CLASSVIEW__
	test	bl,_TV_HEXVIEW or _TV_CLASSVIEW
  else
	test	bl,_TV_HEXVIEW
  endif
	jz	line_table_txt
	jmp	line_table_hex
    line_table_txt:
	test	bl,_TV_WRAPLINES
	jnz	line_table_end
	lea	bx,[bp].S_TVIEW.tv_static_table
	mov	cx,[bp].S_TVIEW.tv_static_count
    line_table_static:
	cmp	dx,[bx+2]
	jne	@F
	cmp	ax,[bx]
      @@:
	je	line_table_stfound
	add	bx,4
	dec	cx
	jnz	line_table_static
	xor	bx,bx
    line_table_stfound:
	or	bx,bx
	jz	line_table_read
    line_table_add:
	add	bx,4
	mov	ax,[bx]
	mov	dx,[bx+2]
	stom	[bp].S_TVIEW.tv_offset
	call	add_offset
	mov	ax,[bp].S_TVIEW.tv_lcount
	cmp	ax,[bp].S_TVIEW.tv_rowcnt
	ja	line_table_max
	dec	cx
	jnz	line_table_add
    ifdef __3__
	mov eax,[bp].S_TVIEW.tv_offset
	cmp eax,[bp].S_TVIEW.tv_fsize
    else
	lodm [bp].S_TVIEW.tv_offset
	cmp dx,word ptr [bp].S_TVIEW.tv_fsize+2
	jne @F
	cmp ax,word ptr [bp].S_TVIEW.tv_fsize
      @@:
    endif
	je line_table_max
    line_table_read:
	call	oseek_dxax
	jz	line_table_end
	mov	si,8000h
    line_table_getc:
	call	ogetc
	jz	line_table_eof
	add	word ptr [bp].S_TVIEW.tv_offset,1
	adc	word ptr [bp].S_TVIEW.tv_offset+2,0
	cmp	al,0Dh
	je	line_table_crlf
	cmp	al,0Ah
	je	line_table_crlf
	dec	si
	jz	line_table_crlf
	jmp	line_table_getc
    line_table_eof:
	call	add_offset
	call	add_offset
	dec	[bp].S_TVIEW.tv_lcount
    line_table_max:
	dec	[bp].S_TVIEW.tv_lcount
    line_table_end:
	pop	si
	jnz	init_screenbuf
	ret
    line_table_hex:
	call	oseek_dxax
	jz	line_table_end
  ifdef __BINVIEW__
	mov	si,8
	.if !(tvflag & _TV_BINVIEW)
	    add si,si
	.endif
  else
	mov	si,16
  endif
	xor	cx,cx
    line_table_loop:
	lodm	[bp].S_TVIEW.tv_offset
	mov	bx,si
  ifdef __CLASSVIEW__
	test	tvflag,_TV_CLASSVIEW
	jz	line_table_addsi
	push	ax
	mov	bx,offset tv_class
	mov	ax,cx
	shl	ax,5
	add	bx,ax
	mov	bx,[bx].S_CLASS.cl_size
	pop	ax
  endif
    line_table_addsi:
	add	ax,bx
	adc	dx,0
	stom	[bp].S_TVIEW.tv_offset
	call	cmp_dxax_fsize
	ja	line_table_beof
	call	add_offset
	inc	cx
	cmp	cx,[bp].S_TVIEW.tv_rowcnt
	jb	line_table_loop
	jmp	line_table_eof
    line_table_beof:
	movmm	[bp].S_TVIEW.tv_offset,[bp].S_TVIEW.tv_fsize
	jmp	line_table_eof
    line_table_crlf:
	call	getc
	jz	line_table_eof
	jc	line_table_14
	call	ungetc
    line_table_14:
	call	add_offset
	mov	ax,[bp].S_TVIEW.tv_lcount
	cmp	ax,[bp].S_TVIEW.tv_rowcnt
	ja	line_table_max
	jmp	line_table_getc

init_screenbuf:
	push	di
	sub	ax,ax
	mov	al,_scrcol
	mul	[bp].S_TVIEW.tv_rowcnt
	mov	cx,ax
	les	di,[bp].S_TVIEW.tv_screen
	mov	al,20h
	cld?
	rep	stosb
	pop	di
	lodm	STDI.ios_bb
	stom	[bp].S_TVIEW.tv_offset

oseek_dxax:
	push	dx
	push	ax
	push	SEEK_SET
	call	oseekl
	ret

parse_line:
	push	si
	push	di
	xor	si,si
    parse_line_00:
	call	getc
	jz	parse_line_02
	jc	parse_line_04
	cmp	al,9
	je	parse_line_TAB
	test	al,al
	jnz	@F
	mov	al,' '
     @@:
	mov	es:[di],al
	inc	di
	inc	si
    parse_line_01:
	mov	ax,si
	cmp	al,_scrcol
	je	parse_line_07
	jb	parse_line_00
    parse_line_02:
	pop	di
	pop	si
	jz	parse_line_03
	sub	ax,ax
	mov	al,_scrcol
	add	di,ax
    parse_line_03:
	ret
    parse_line_04:
	call	getc
	jna	parse_line_02
    parse_line_05:
	sub	word ptr [bp].S_TVIEW.tv_offset,1
	sbb	word ptr [bp].S_TVIEW.tv_offset+2,0
	dec	STDI.ios_i
	jmp	parse_line_02
    parse_line_TAB:
	sub	si,di
	add	di,8
	and	di,-8
	add	si,di
	jmp	parse_line_01
    parse_line_07:
	call	getc
	jz	parse_line_02
	jc	parse_line_04
	jmp	parse_line_05

read_wrap:
	call	read_line_table
	jz	read_wrap_02
	push	di
	les	di,[bp].S_TVIEW.tv_screen
	xor	ax,ax
	mov	[bp].S_TVIEW.tv_bsize,ax
	mov	[bp].S_TVIEW.tv_lcount,ax
    read_wrap_00:
	mov	ax,[bp].S_TVIEW.tv_bsize
	inc	[bp].S_TVIEW.tv_bsize
	cmp	ax,[bp].S_TVIEW.tv_rowcnt
	jnc	read_wrap_01
	call	add_offset
	call	parse_line
	jnz	read_wrap_00
    read_wrap_01:
	lodm	[bp].S_TVIEW.tv_offset
	sub	ax,word ptr STDI.ios_bb
	sbb	dx,word ptr STDI.ios_bb+2
	stom	[bp].S_TVIEW.tv_scount
	or	ax,1
	pop	di
	ret
    read_wrap_02:
	xor	ax,ax
	ret

read_text:
	call	read_line_table
	jz	read_text_04
	call	setmaxcol
	push	di
	les	di,[bp].S_TVIEW.tv_screen
	mov	[bp].S_TVIEW.tv_bsize,0
    read_text_00:
	mov	ax,[bp].S_TVIEW.tv_bsize
	inc	[bp].S_TVIEW.tv_bsize
	cmp	ax,[bp].S_TVIEW.tv_lcount
	jnc	read_text_02
	call	getlinesize
	add	word ptr [bp].S_TVIEW.tv_scount,ax
	adc	word ptr [bp].S_TVIEW.tv_scount+2,dx
	cmp	dx,word ptr [bp].S_TVIEW.tv_curcol+2
	jne	@F
	cmp	ax,word ptr [bp].S_TVIEW.tv_curcol
      @@:
	ja	read_text_01
	sub	ax,ax
	mov	al,_scrcol
	add	di,ax
	jmp	read_text_00
    read_text_01:
	add	bx,word ptr [bp].S_TVIEW.tv_curcol
	add	cx,word ptr [bp].S_TVIEW.tv_curcol+2
	mov	ax,bx
	mov	dx,cx
	call	oseek_dxax
	jz	read_text_04
	call	parse_line
	jnz	read_text_00
    read_text_02:
	or	ax,1
    read_text_03:
	pop	di
	ret
    read_text_04:
	xor	ax,ax
	jmp	read_text_03

mk_hexword:
	mov	ah,al
	and	ax,0FF0h
	shr	al,04h
	add	ax,3030h
	cmp	ah,39h
	jbe	mk_hexword_00
	add	ah,07h
    mk_hexword_00:
	cmp	al,39h
	jbe	mk_hexword_01
	add	al,07h
    mk_hexword_01:
	ret

print_offset:	; cx = index, es:di = buffer
	lea	bx,[bp].S_TVIEW.tv_line_table
	mov	ax,cx
	shl	ax,2
	add	ax,3
	add	bx,ax
	mov	dx,4
  ifdef __BINVIEW__
	test	tvflag,_TV_HEXOFFSET or _TV_BINVIEW
  else
	test	tvflag,_TV_HEXOFFSET
  endif
	jnz	@F
	push	[bx-1]
	push	[bx-3]
	invoke	sprintf,es::di,addr format_010lu
	add	sp,4
	add	di,9
	ret
    @@:
	mov	al,[bx]
	call	mk_hexword
	stosw
	dec	bx
	dec	dx
	jnz	@B
	inc	di
	ret

read_hex:
	call	read_line_table
	jnz	read_hex_do
    read_hex_end:
	ret
    read_hex_do:
	call	ogetc
	jz	read_hex_end
	dec	STDI.ios_i
  ifdef __BINVIEW__
	mov	ax,8
	.if !(tvflag & _TV_BINVIEW)
	    add ax,ax
	.endif
  else
	mov	ax,16
  endif
	mul	[bp].S_TVIEW.tv_rowcnt
	cmp	ax,STDI.ios_c
	ja	read_hex_03
	mov	STDI.ios_c,ax
    read_hex_03:
	mov	ax,STDI.ios_c
	xor	cx,cx
	mov	word ptr [bp].S_TVIEW.tv_scount,ax
	mov	word ptr [bp].S_TVIEW.tv_scount+2,cx
	push	di
	les	di,[bp].S_TVIEW.tv_screen
    read_hex_04:
	push	di
	call	print_offset
	mov	dx,STDI.ios_c
  ifdef __BINVIEW__
	mov	ax,8
	.if !(tvflag & _TV_BINVIEW)
	    add ax,ax
	    add di,3
	.endif
  else
	mov	ax,16
	add	di,3
  endif
	cmp	dx,ax
	jb	read_hex_08
	mov	dx,ax
    read_hex_08:
	or	dx,dx
	jz	read_hex_16
	sub	STDI.ios_c,dx
	mov	bx,di
	add	bx,51
	push	cx
	mov	cx,dx
	xor	dx,dx
    read_hex_09:
  ifdef __BINVIEW__
	test	tvflag,_TV_BINVIEW
	jnz	@F
  endif
    read_hex_10:
	.if dx == 8
	    mov al,179
	    stosb
	    inc di
	.endif
    @@:
	mov	ax,STDI.ios_i
	push	es
	push	bx
	les	bx,dword ptr STDI
	add	bx,ax
	mov	al,es:[bx]
	pop	bx
	pop	es
	inc	STDI.ios_i
  ifdef __BINVIEW__
	test	tvflag,_TV_BINVIEW
	jnz	read_hex_12
  endif
	mov	es:[bx],al
	call	mk_hexword
	stosw
	inc	di
	inc	bx
	inc	dx
	dec	cx
	jnz	read_hex_10
	jmp	read_hex_15
    read_hex_12:
	mov	ah,al
	push	cx
	mov	cx,8
    read_hex_13:
	mov	al,ah
	shl	ah,1
	and	al,80h
	mov	al,'1'
	jnz	read_hex_14
	mov	al,'0'
    read_hex_14:
	mov	es:[di],al
	inc	di
	dec	cx
	jnz	read_hex_13
	pop	cx
	inc	di
	inc	dx
	dec	cx
	jnz	read_hex_09
    read_hex_15:
	pop	cx
	pop	di
	sub	ax,ax
	add	al,_scrcol
	add	di,ax
	inc	cx
	cmp	cx,[bp].S_TVIEW.tv_lcount
	jnb	read_hex_17
	jmp	read_hex_04
    read_hex_16:
	pop	di
    read_hex_17:
	or	ax,1
	pop	di
	ret

ifdef __CLASSVIEW__

class_getformat:
	mov	ah,0
	mov	al,[si].S_CLASS.cl_format
	add	ax,ax
	add	ax,dx
	mov	bx,ax
	mov	ax,[bx]
	mov	dx,word ptr [bp].S_TVIEW.tv_screen+2
	mov	bx,di
	ret

read_class:
	push	si
	push	di
	call	read_line_table
	jz	read_class_end
	call	ogetc
	jz	read_class_end
	dec	STDI.ios_i
	mov	bx,offset tv_class
	xor	ax,ax
	mov	ch,al
	mov	cl,[bp].S_TVIEW.tv_CLDLG.dl_count
      @@:
	add	ax,[bx].S_CLASS.cl_size
	add	bx,S_CLASS
	dec	cx
	jnz	@B
	mov	tv_classsize,ax
	cmp	ax,STDI.ios_c
	ja	@F
	mov	STDI.ios_c,ax
      @@:
	mov	ax,STDI.ios_c
	xor	cx,cx
	mov	word ptr [bp].S_TVIEW.tv_scount,ax
	mov	word ptr [bp].S_TVIEW.tv_scount+2,cx
	les	di,[bp].S_TVIEW.tv_screen
    read_class_do:
	push	di
	call	print_offset
	add	di,3
	mov	si,offset tv_class
	mov	ax,cx
	shl	ax,5
	add	si,ax
	mov	dx,word ptr [bp].S_TVIEW.tv_screen+2
	invoke	sprintf,dx::di,addr format_s,ds::si
	add	di,28
	les	bx,STDI
	add	bx,STDI.ios_i
	mov	al,[si].S_CLASS.cl_type
	cmp	al,CLTYPE_CHAR
	je	read_class_char
	cmp	al,CLTYPE_WORD
	je	read_class_word
	cmp	al,CLTYPE_DWORD
	je	read_class_dword
	cmp	al,CLTYPE_QWORD
	je	read_class_qword
	cmp	[si].S_CLASS.cl_size,1
	jne	read_class_bytes
	mov	dx,offset format_byte
	mov	al,es:[bx]
	cmp	[si].S_CLASS.cl_format,CLFORM_UNSIGNED
	jne	read_class_signed
	mov	ah,0
	jmp	read_class_int
    read_class_signed:
	cbw
	jmp	read_class_int
    read_class_bytes:
	cmp	al,CLTYPE_BYTE
	je	read_class_byte
	jmp	read_class_break
    read_class_loop:
	pop	di
	add	di,80
	mov	ax,[si].S_CLASS.cl_size
	add	STDI.ios_i,ax
	inc	cx
	cmp	cl,[bp].S_TVIEW.tv_CLDLG.dl_count
	jnb	read_class_break
	cmp	cx,[bp].S_TVIEW.tv_lcount
	jb	read_class_do
    read_class_break:
	pop	di
	jmp	read_class_ok
    read_class_char:
	mov	ax,[si].S_CLASS.cl_size
	push	cx
	mov	cx,39
	cmp	cx,ax
	jb	read_class_strl
	mov	cx,ax
    read_class_strl:
	mov	dx,ds
	mov	bx,si
	mov	ax,STDI.ios_i
	lds	si,STDI
	add	si,ax
	assert	cx,0,jne,"read_class"
	rep	movsb
	mov	ds,dx
	mov	si,bx
	pop	cx
	jmp	read_class_loop
    read_class_byte:
	mov	ax,[si].S_CLASS.cl_size
	mov	dx,13
	cmp	dx,ax
	jb	read_class_btrl
	mov	dx,ax
    read_class_btrl:
	assert	dx,0,jne,"read_class"
    read_class_xloop:
	mov	al,es:[bx]
	call	mk_hexword
	stosw
	inc	di
	inc	bx
	dec	dx
	jnz	read_class_xloop
	jmp	read_class_loop
    read_class_word:
	mov	dx,offset format_word
	mov	ax,es:[bx]
    read_class_int:
	push	ax
	call	class_getformat
	invoke	sprintf,dx::di,ds::ax
	add	sp,2
	jmp	read_class_loop
    read_class_dword:
	pushm	es:[bx]
	mov	dx,offset format_dword
	call	class_getformat
	invoke	sprintf,dx::di,ds::ax
	add	sp,4
	jmp	read_class_loop
    read_class_qword:
	cmp	[si].S_CLASS.cl_format,CLFORM_UNSIGNED
	ja	read_class_qbin
	push	cx
	push	es
	push	bx
	invoke	qwtostr, es:[bx+4], es:[bx]
	mov	bx,word ptr [bp].S_TVIEW.tv_screen+2
	invoke	sprintf,bx::di,addr format_s,dx::ax
	pop	bx
	pop	es
	pop	cx
	jmp	read_class_loop
    read_class_qbin:
	push	es:[bx+2]
	push	es:[bx]
	push	es:[bx+6]
	push	es:[bx+4]
	mov	ax,word ptr [bp].S_TVIEW.tv_screen+2
	invoke	sprintf,ax::di,addr format_16X
	add	sp,8
	jmp	read_class_loop
    read_class_ok:
	or	al,1
    read_class_end:
	pop	di
	pop	si
	ret

init_class:
	push	si
	push	di
	movmx	[bp].S_TVIEW.tv_tdialog,tdialog
	xor	ax,ax
	cwd
	test	tvflag,_TV_USEMLINE
	jz	@F
	inc	dl
      @@:
	mov	cx,CLCOUNT
	lea	si,[bp].S_TVIEW.tv_CLDLG
	mov	word ptr tdialog,si
	mov	word ptr tdialog+2,ss
	mov	[si].S_DOBJ.dl_flag,CLFLAGS
	mov	[si].S_DOBJ.dl_index,al
	mov	[si].S_DOBJ.dl_count,cl
	mov	[si].S_DOBJ.dl_rect.rc_x,al
	mov	[si].S_DOBJ.dl_rect.rc_y,dl
	mov	[si].S_DOBJ.dl_rect.rc_col,80
	mov	[si].S_DOBJ.dl_rect.rc_row,cl
	mov	al,_scrcol
	add	ax,ax
	mov	word ptr [si].S_DOBJ.dl_wp,ax
	mov	ax,_scrseg
	mov	word ptr [si].S_DOBJ.dl_wp+2,ax
	lea	ax,[bp].S_TVIEW.tv_CLOBJ
	mov	word ptr [si].S_DOBJ.dl_object,ax
	mov	word ptr [si].S_DOBJ.dl_object+2,ss
	mov	di,offset tv_class
	add	si,16
	xor	ax,ax
	cwd
    init_class_loop:
	mov	[si].S_TOBJ.to_flag,_O_XHTML
	mov	[si].S_TOBJ.to_count,al
	mov	[si].S_TOBJ.to_ascii,al
	mov	[si].S_TOBJ.to_rect.rc_x,al
	mov	[si].S_TOBJ.to_rect.rc_y,dl
	mov	[si].S_TOBJ.to_rect.rc_col,80
	mov	[si].S_TOBJ.to_rect.rc_row,1
	mov	word ptr [si].S_TOBJ.to_data,ax
	mov	word ptr [si].S_TOBJ.to_data+2,ax
	inc	dx
	add	si,16
	dec	cx
	jnz	init_class_loop
	pop	di
	pop	si
	ret

event_clsave:
	.if tvflag & _TV_CLASSVIEW
	    .if rsopen(IDD_TVSaveClass)
		push dx
		push ax
		push dx
		push ax
		invoke sprintf,es:[bx].S_TOBJ.to_data[16],addr format_u,tv_classrow
		call dlevent
		.if ax
		    .if strtol(es:[bx].S_TOBJ.to_data+16)
			.if ax <= 512
			    mov tv_classrow,ax
			    .if wgetfile(addr cp_tcl,2)
				push ax
				invoke oswrite,ax,addr tv_clversion,TCLSIZE
				call close
			    .endif
			.endif
		    .endif
		.endif
		call dlclose
	    .endif
	.endif
	ret

event_clload:
	push	si
	push	di
	test	tvflag,_TV_CLASSVIEW
	jz	event_clload_end
	invoke	wgetfile,addr cp_tcl,3
	jz	event_clload_end
	mov	si,offset _bufin
	push	ax
	invoke	osread,ax,ds::si,TCLSIZE
	mov	di,ax
	call	close
	cmp	di,TCLSIZE
	jne	event_clload_end
	mov	ax,[si]
	cmp	ax,CLVERSION
	jne	event_clload_end
	mov	ax,[si+4]
	lea	di,[si+6]
	mov	cx,ax
	mov	tv_classrow,ax
	xor	dx,dx
	cmp	ax,CLCOUNT
	jbe	event_clload_loop
	mov	cx,CLCOUNT
	mov	tv_classrow,cx
    event_clload_loop:
	mov	[di].S_CLASS.cl_name[27],0
	mov	ax,[di].S_CLASS.cl_size
	or	ax,ax
	jnz	event_clload_l01
	inc	ax
    event_clload_l01:
	cmp	ax,512
	jbe	event_clload_l02
	mov	ax,512
    event_clload_l02:
	mov	[di].S_CLASS.cl_size,ax
	add	dx,ax
	cmp	[di].S_CLASS.cl_type,CLTYPE_QWORD
	jbe	event_clload_l03
	mov	[di].S_CLASS.cl_type,CLTYPE_QWORD
    event_clload_l03:
	cmp	[di].S_CLASS.cl_format,CLFORM_BINARY
	jbe	event_clload_l04
	mov	[di].S_CLASS.cl_format,CLFORM_BINARY
    event_clload_l04:
	add	di,S_CLASS
	dec	cx
	jnz	event_clload_loop
	mov	tv_classsize,dx
	mov	ax,tv_classrow
	mov	[bp].S_TVIEW.tv_CLDLG.dl_count,al
	push	ds
	push	offset tv_clversion
	push	ds
	push	si
	push	TCLSIZE
	call	memcpy
	call	reread
    event_clload_end:
	pop	di
	pop	si
	ret

event_ENTER:
	push si
	push di
	.if tvflag & _TV_CLASSVIEW
	    mov si,offset tv_class
	    sub ax,ax
	    mov al,[bp].S_TVIEW.tv_CLDLG.dl_index
	    shl ax,5
	    add si,ax
	    .if rsopen(IDD_TVClass)
		stom DLG_TVClass
		mov di,dx
		invoke strcpy,es:[bx].S_TOBJ.to_data[6*16],ss::si ; .cl_name
		invoke sprintf,es:[bx].S_TOBJ.to_data[1*16],addr format_d,[si].S_CLASS.cl_size
		invoke sprintf,es:[bx].S_TOBJ.to_data[2*16],addr format_d,[si].S_CLASS.cl_size
		mov al,[si].S_CLASS.cl_type
		mov es:[bx].S_DOBJ.dl_index,al
		invoke dlinit,DLG_TVClass
		.if rsevent(IDD_TVClass,DLG_TVClass)
		    push ax
		    invoke strnzcpy,ss::si,es:[bx].S_TOBJ.to_data[6*16],27
		    pop ax
		    mov es,di
		    .if ax < 6
			dec ax
			mov [si].S_CLASS.cl_type,al
			.if al == CLTYPE_BYTE
			    mov ax,1
			    pushm es:[bx].S_TOBJ.to_data[2*16]
			.elseif al == CLTYPE_CHAR
			    mov ax,1
			    pushm es:[bx].S_TOBJ.to_data[1*16]
			.elseif al == CLTYPE_WORD
			    mov ax,2
			.elseif al == CLTYPE_DWORD
			    mov ax,4
			.else
			    mov ax,8
			.endif
			.if ax == 1
			    call strtol
			    .if ax > 512
				mov ax,512
			    .endif
			    .if !ax
				inc ax
			    .endif
			    mov [si].S_CLASS.cl_size,ax
			    .if ax != 1 || [si].S_CLASS.cl_type == CLTYPE_CHAR
				jmp @F
			    .endif
			.endif
			mov [si].S_CLASS.cl_size,ax
			.if rsopen(IDD_TVClassFormat)
			    mov cl,[si].S_CLASS.cl_format
			    mov es:[bx].S_DOBJ.dl_index,cl
			    .if !dlmodal(dx::ax)
				inc ax
			    .endif
			    dec ax
			    mov [si].S_CLASS.cl_format,al
			.endif
		    .endif
		.endif
	      @@:
		invoke dlclose,DLG_TVClass
		call reread
	    .endif
	.endif
	sub ax,ax
	pop di
	pop si
	ret

endif

previous_line:
	movmm	[bp].S_TVIEW.tv_offset,STDI.ios_bb
	mov	cx,dx
	or	cx,ax
	jnz	prevline_size?
    prevline_00:
	xor	ax,ax
	cwd
	ret
    prevline_size?:
	call	cmp_dxax_fsize
	jbe	prevline_hex?
    fsize_to_bb:
	movmm	STDI.ios_bb,[bp].S_TVIEW.tv_fsize
	ret
    prevline_hex?:
	xor	cx,cx
	mov	bl,tvflag
  ifdef __CLASSVIEW__
	test	bl,_TV_HEXVIEW or _TV_CLASSVIEW
	jz	previous_text
	test	bl,_TV_CLASSVIEW
	jz	@F
	mov	bx,1
	jmp	previous_hex_00
    @@:
	test	bl,_TV_BINVIEW
	mov	bx,8
	jnz	previous_hex_00
  else
	test	bl,_TV_HEXVIEW
	jz	previous_text
  endif
	mov	bx,16
    previous_hex_00:
	cmp	dx,cx
	jne	previous_hex_01
	cmp	ax,bx
    previous_hex_01:
	jbe	prevline_00
	sub	ax,bx
	sbb	dx,cx
	ret
    previous_text:
	lea	bx,[bp].S_TVIEW.tv_static_table ; get last offset
	mov	ax,[bp].S_TVIEW.tv_static_count
	shl	ax,2
	add	bx,ax
	mov	ax,[bx]
	mov	dx,[bx+2]
	cmp	dx,word ptr [bp].S_TVIEW.tv_offset+2
	jne	@F
	cmp	ax,word ptr [bp].S_TVIEW.tv_offset
      @@:
	jb	previous_seek_back
	lodm	[bp].S_TVIEW.tv_offset
	mov	cx,[bp].S_TVIEW.tv_static_count
	dec	cx
    previous_static_00:
	lea	bx,[bp].S_TVIEW.tv_static_table
	push	ax
	mov	ax,cx
	shl	ax,2
	add	bx,ax
	pop	ax
	cmp	dx,[bx+2]
	jne	@F
	cmp	ax,[bx]
      @@:
	ja	previous_static_01
	or	cx,cx
	jz	prevline_00
	dec	cx
	jmp	previous_static_00
    previous_static_01:
	mov	ax,[bx]
	mov	dx,[bx+2]
	jmp	prevline_wrap?
    previous_seek_back:
	lodm	[bp].S_TVIEW.tv_offset
	call	oseek_dxax
	jz	previous_seek_00
	call	ungetc
	jz	previous_seek_00
	push	si
	mov	si,8000h
	jnc	previous_back_01
	call	ungetc
	jz	prevline_si00
    previous_back_01:
	call	oungetc
	jz	prevline_si00
	sub	word ptr [bp].S_TVIEW.tv_offset,1
	sbb	word ptr [bp].S_TVIEW.tv_offset+2,0
	cmp	al,0Dh
	je	prevline_seek_01
	cmp	al,0Ah
	je	prevline_seek_01
	dec	si
	jz	prevline_seek_01
	jmp	previous_back_01
    prevline_si00:
	pop	si
    previous_seek_00:
	jmp	prevline_00
    prevline_seek_01:
	pop	si
	lodm	[bp].S_TVIEW.tv_offset
	add	ax,1
	adc	dx,0
    prevline_wrap?:
	test	tvflag,_TV_WRAPLINES
	jnz	prevline_wrap
	ret
    prevline_wrap:
	call	cmp_dxax_bb
	ja	prevline_wrap_home
	mov	bx,word ptr STDI.ios_bb
	mov	cx,word ptr STDI.ios_bb+2
	sub	bx,ax
	sbb	cx,dx
	or	cx,cx
	jnz	prevline_wrap_00
	cmp	bx,8000h
	jb	prevline_wrap_01
    prevline_wrap_00:
	add	ax,bx
	adc	dx,cx
	sub	cx,cx
	mov	cl,_scrcol
	sub	ax,cx
	sbb	dx,0
    prevline_wrap_01:
	stom	[bp].S_TVIEW.tv_offset
	stom	[bp].S_TVIEW.tv_tmp
	call	oseek_dxax
	jz	prevline_wrap_home
	push	di
    prevline_wrap_02:
	les	di,[bp].S_TVIEW.tv_screen
	call	parse_line
	jz	prevline_wrap_end
    ifndef __16__
	mov	eax,[bp].S_TVIEW.tv_offset
	cmp	eax,STDI.ios_bb
	jae	prevline_wrap_end
	mov	[bp].S_TVIEW.tv_tmp,eax
    else
	lodm	[bp].S_TVIEW.tv_offset
	cmp	dx,word ptr STDI.ios_bb+2
	jne	@F
	cmp	ax,word ptr STDI.ios_bb
      @@:
	jae	prevline_wrap_end
	stom	[bp].S_TVIEW.tv_tmp
    endif
	jmp	prevline_wrap_02
    prevline_wrap_home:
	jmp	prevline_00
    prevline_wrap_end:
	pop	di
	lodm	[bp].S_TVIEW.tv_tmp
	ret

tvread:
	xor	ax,ax
	mov	word ptr [bp].S_TVIEW.tv_scount,ax
	mov	word ptr [bp].S_TVIEW.tv_scount+2,ax
	mov	al,tvflag
	test	al,_TV_HEXVIEW
	jnz	tvread_hex
  ifdef __CLASSVIEW__
	test	al,_TV_CLASSVIEW
	jz	@F
	call	read_class
	ret
    @@:
  endif
	test	al,_TV_WRAPLINES
	jnz	tvread_wrap
	call	read_text
	ret
    tvread_wrap:
	call	read_wrap
	ret
    tvread_hex:
	call	read_hex
	ret

reread:
	call	tvread
	jz	reread_00
	call	putscreen
	mov	ax,1
    reread_00:
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

putscreen:
	test	tvflag,_TV_USEMLINE
	jz	pustscreen_nomenus
  ifndef __16__
	mov	eax,[bp].S_TVIEW.tv_scount
	add	eax,STDI.ios_bb
	jz	@F
	mov	ecx,100
	mul	ecx
	mov	ecx,[bp].S_TVIEW.tv_fsize
	div	ecx
  else
	lodm	[bp].S_TVIEW.tv_scount
	add	ax,word ptr STDI.ios_bb
	adc	dx,word ptr STDI.ios_bb+2
	mov	cx,dx
	or	cx,ax
	jz	@F
	xor	cx,cx
	mov	bx,100
	call	_mul32
	mov	bx,word ptr [bp].S_TVIEW.tv_fsize
	mov	cx,word ptr [bp].S_TVIEW.tv_fsize+2
	call	_div32
  endif
	and	ax,007Fh
	cmp	ax,100
	jbe	putscreen_01
     @@:
	mov	ax,100
    putscreen_01:
	invoke	scputf,75,0,0,0,addr format_3d,ax
	invoke	scputf,65,0,0,0,addr format_8ld,[bp].S_TVIEW.tv_curcol
    pustscreen_nomenus:
	mov	ax,word ptr [bp].S_TVIEW.tv_fsize
	or	ax,word ptr [bp].S_TVIEW.tv_fsize+2
	jz	putscreen_04
    putscreen_02:
	HideMouseCursor
	mov	ax,_scrseg
	mov	es,ax
	xor	ax,ax
	cwd
	mov	dl,_scrcol
	add	dx,dx
	test	tvflag,_TV_USEMLINE
	jz	@F
	mov	ax,dx
      @@:
	push	ds
	push	si
	push	di
	mov	di,ax
	mov	bx,ax
	mov	al,_scrcol
	mov	cl,al
	mov	ch,byte ptr [bp].S_TVIEW.tv_rowcnt
	lds	si,[bp].S_TVIEW.tv_screen
	cld?
    putscreen_03:
	movsb
	inc	di
	dec	cl
	jnz	putscreen_03
	mov	cl,al
	add	bx,dx
	mov	di,bx
	dec	ch
	jnz	putscreen_03
	pop	di
	pop	si
	pop	ds
	ShowMouseCursor
    putscreen_04:
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

event_HOME:
	sub	ax,ax
  ifdef __CLASSVIEW__
	test	tvflag,_TV_CLASSVIEW
	jz	@F
	les	bx,tdialog
	cmp	es:[bx].S_DOBJ.dl_index,al
	je	@F
	mov	es:[bx].S_DOBJ.dl_index,al
	ret
    @@:
  endif
	mov word ptr [bp].S_TVIEW.tv_curcol,ax
	mov word ptr [bp].S_TVIEW.tv_curcol+2,ax
  ifdef __MEMVIEW__
	.if STDI.ios_flag & IO_MEMREAD
	    lodm [bp].S_TVIEW.tv_address
	    call normalize
	    stom STDI.ios_bb
	.else
	    mov word ptr STDI.ios_bb,ax
	    mov word ptr STDI.ios_bb+2,ax
	.endif
  else
	mov word ptr STDI.ios_bb,ax
	mov word ptr STDI.ios_bb+2,ax
  endif
	jmp reread

event_END:
  ifdef __CLASSVIEW__
	test	tvflag,_TV_HEXVIEW or _TV_CLASSVIEW
  else
	test	tvflag,_TV_HEXVIEW
  endif
	jnz	event_END_hex
	mov	ax,[bp].S_TVIEW.tv_lcount
	cmp	ax,[bp].S_TVIEW.tv_rowcnt
	jb	@F
	call	cmp_bbscount1_fsize
	jae	@F
	movmx	STDI.ios_bb,[bp].S_TVIEW.tv_fsize
	jmp	event_PGUP_text
    @@:
	ret
    event_END_hex:
  ifdef __CLASSVIEW__
	test	tvflag,_TV_CLASSVIEW
	jz	@F
	les	bx,tdialog
	mov	al,es:[bx].S_DOBJ.dl_count
	dec	al
	cmp	al,es:[bx].S_DOBJ.dl_index
	je	@F
	mov	es:[bx].S_DOBJ.dl_index,al
	ret
    @@:
  endif
	mov ax,[bp].S_TVIEW.tv_rowcnt
	mov cl,4
  ifdef __BINVIEW__
	.if tvflag & _TV_BINVIEW
	    dec cl
	.endif
  endif
  ifndef __16__
	movzx eax,ax
	shl eax,cl
	inc eax
	cmp eax,[bp].S_TVIEW.tv_fsize
  else
	xor dx,dx
	shl ax,cl
	call cmp_dxax1_fsize
  endif
	jb @F
	ret
    @@:
  ifndef __16__
	sub eax,[bp].S_TVIEW.tv_fsize
	not eax
	add eax,18
	and al,0F0h
	mov STDI.ios_bb,eax
  else
	sub ax,word ptr [bp].S_TVIEW.tv_fsize
	sbb dx,word ptr [bp].S_TVIEW.tv_fsize+2
	not ax
	not dx
	add ax,18
	adc dx,0
	and al,0F0h
	stom STDI.ios_bb
  endif
	jmp	reread

event_UP:
  ifdef __CLASSVIEW__
	test	tvflag,_TV_CLASSVIEW
	jz	@F
	les	bx,tdialog
	xor	ax,ax
	cmp	es:[bx].S_DOBJ.dl_index,al
	je	@F
	dec	es:[bx].S_DOBJ.dl_index
	ret
    @@:
  endif
	call	previous_line
	call	cmp_dxax_bb
	jz	@F
	stom	STDI.ios_bb
	jmp	reread
    @@:
	ret

event_DOWN:
	mov	al,tvflag
  ifdef __CLASSVIEW__
	test	al,_TV_CLASSVIEW
	jz	@F
	les	bx,tdialog
	mov	ah,es:[bx].S_DOBJ.dl_count
	dec	ah
	cmp	ah,es:[bx].S_DOBJ.dl_index
	je	@F
	inc	es:[bx].S_DOBJ.dl_index
	jmp	event_DOWN_03
    @@:
  endif
	sub cx,cx
  ifdef __CLASSVIEW__
	test al,_TV_HEXVIEW or _TV_CLASSVIEW
  else
	test al,_TV_HEXVIEW
  endif
	jz event_DOWN_02
  ifdef __CLASSVIEW__
	.if al & _TV_CLASSVIEW
	    mov bx,1
	.else
  endif
  ifdef __BINVIEW__
	    mov bx,8
	    .if !(al & _TV_BINVIEW)
		add bx,bx
	    .endif
  else
	mov bx,16
  endif
  ifdef __CLASSVIEW__
	.endif
  endif
	call cmp_bbscount1_fsize
	jnb event_DOWN_03
  ifndef __16__
	movzx ebx,bx
	add eax,ebx
	cmp eax,[bp].S_TVIEW.tv_fsize
	jnb event_END
	add STDI.ios_bb,ebx
  else
	add ax,bx
	adc dx,cx
	cmp dx,word ptr [bp].S_TVIEW.tv_fsize+2
	jne @F
	cmp ax,word ptr [bp].S_TVIEW.tv_fsize
      @@:
	jnb event_END
	add word ptr STDI.ios_bb,bx
	adc word ptr STDI.ios_bb+2,cx
  endif
	jmp reread
    event_DOWN_02:
	mov ax,[bp].S_TVIEW.tv_lcount
	cmp ax,[bp].S_TVIEW.tv_rowcnt
	jb event_DOWN_03
	lea bx,[bp].S_TVIEW.tv_line_table
	add bx,4
	movmx STDI.ios_bb,[bx]
	jmp reread
    event_DOWN_03:
	sub ax,ax
	ret

event_PGUP:
	mov	cl,tvflag
  ifdef __CLASSVIEW__
	sub	ax,ax
	test	cl,_TV_CLASSVIEW
	jz	@F
	les	bx,tdialog
	cmp	es:[bx].S_DOBJ.dl_index,al
	je	@F
	mov	es:[bx].S_DOBJ.dl_index,al
	jmp	event_PGUP_04
    @@:
  endif
  ifndef __16__
	mov eax,STDI.ios_bb
	test eax,eax
  else
	lodm STDI.ios_bb
	mov bx,ax
	or bx,dx
  endif
	jz event_PGUP_04
  ifdef __CLASSVIEW__
	test cl,_TV_HEXVIEW or _TV_CLASSVIEW
  else
	test cl,_TV_HEXVIEW
  endif
	jz event_PGUP_text
  ifndef __16__
	movzx eax,[bp].S_TVIEW.tv_rowcnt
	shl eax,4
	cmp eax,STDI.ios_bb
	jnb @F
	sub STDI.ios_bb,eax
	jmp event_PGUP_03
      @@:
	xor eax,eax
	mov STDI.ios_bb,eax
  else
	mov ax,[bp].S_TVIEW.tv_rowcnt
	mov cl,4
	shl ax,cl
	xor dx,dx
	call cmp_dxax_bb
	jnb event_PGUP_02
	sub word ptr STDI.ios_bb,ax
	sbb word ptr STDI.ios_bb+2,dx
	jmp event_PGUP_03
    event_PGUP_02:
	xor ax,ax
	mov word ptr STDI.ios_bb,ax
	mov word ptr STDI.ios_bb+2,ax
  endif
    event_PGUP_03:
	jmp reread
    event_PGUP_04:
	ret

    event_PGUP_text:
	push	di
	mov	di,1
	test	tvflag,_TV_WRAPLINES
	jnz	event_PGUP_wrap
    event_PGUP_06:
	call	previous_line
	call	cmp_dxax_bb
	jz	event_PGUP_08
	stom	STDI.ios_bb
	inc	di
	cmp	di,[bp].S_TVIEW.tv_rowcnt
	jnz	event_PGUP_06
    event_PGUP_08:
	pop	di
	jmp	reread
    event_PGUP_wrap:
	call	cmp_dxax_fsize
	jne	event_PGUP_06
	mov	di,[bp].S_TVIEW.tv_rowcnt
	dec	di
    event_PGUP_10:
	call	previous_line
	stom	STDI.ios_bb
	dec	di
	jnz	event_PGUP_10
	jmp	event_PGUP_08

event_PGDN:
	mov	al,tvflag
  ifdef __CLASSVIEW__
	test	al,_TV_CLASSVIEW
	jz	@F
	les	bx,tdialog
	mov	al,es:[bx].S_DOBJ.dl_count
	dec	al
	cmp	es:[bx].S_DOBJ.dl_index,al
	je	@F
	mov	es:[bx].S_DOBJ.dl_index,al
	jmp	event_PGDN_03
    @@:
  endif
	call	cmp_bbscount1_fsize
	jnb	event_PGDN_03
  ifdef __CLASSVIEW__
	test	tvflag,_TV_HEXVIEW or _TV_CLASSVIEW
  else
	test	tvflag,_TV_HEXVIEW
  endif
	jz	event_PGDN_01
  ifndef __16__
	mov	ebx,eax
	movzx	eax,[bp].S_TVIEW.tv_rowcnt
  else
	mov	cx,dx
	mov	bx,ax
	mov	ax,[bp].S_TVIEW.tv_rowcnt
	push	cx
  endif
	mov	cl,4
  ifdef __BINVIEW__
	.if tvflag & _TV_BINVIEW
	    dec cl
	.endif
  endif
  ifndef __16__
	shl	eax,cl
	add	ebx,eax
	cmp	ebx,[bp].S_TVIEW.tv_fsize
	jnc	event_PGDN_02
	add	STDI.ios_bb,eax
  else
	shl	ax,cl
	pop	cx
	xor	dx,dx
	add	bx,ax
	adc	cx,dx
	cmp	cx,word ptr [bp].S_TVIEW.tv_fsize+2
	jne	event_PGDN_04
	cmp	bx,word ptr [bp].S_TVIEW.tv_fsize
    event_PGDN_04:
	jnc	event_PGDN_02
	add	word ptr STDI.ios_bb,ax
	adc	word ptr STDI.ios_bb+2,dx
  endif
	jmp	reread
    event_PGDN_01:
	mov	ax,[bp].S_TVIEW.tv_lcount
	cmp	ax,[bp].S_TVIEW.tv_rowcnt
	jne	event_PGDN_03
	;mov	ax,[bp].S_TVIEW.tv_lcount
	dec	ax
	shl	ax,2
	lea	bx,[bp].S_TVIEW.tv_line_table
	add	bx,ax
      ifndef __16__
	mov	eax,[bx]
	cmp	eax,[bp].S_TVIEW.tv_fsize
	jnb	event_PGDN_02
	mov	STDI.ios_bb,eax
      else
	mov	ax,[bx]
	mov	dx,[bx+2]
	cmp	dx,word ptr [bp].S_TVIEW.tv_fsize+2
	jne	@F
	cmp	ax,word ptr [bp].S_TVIEW.tv_fsize
      @@:
	jnb	event_PGDN_02
	stom	STDI.ios_bb
      endif
	jmp	reread
    event_PGDN_02:
	jmp	event_END
    event_PGDN_03:
	ret

event_LEFT:
  ifdef __BINVIEW__
	test	tvflag,_TV_HEXVIEW or _TV_BINVIEW or _TV_WRAPLINES
  else
	test	tvflag,_TV_HEXVIEW or _TV_WRAPLINES
  endif
	jnz	@F
      ifndef __16__
	.if [bp].S_TVIEW.tv_curcol
	    dec [bp].S_TVIEW.tv_curcol
	    jmp reread
	.endif
      else
	mov	ax,word ptr [bp].S_TVIEW.tv_curcol
	or	ax,word ptr [bp].S_TVIEW.tv_curcol+2
	jz	@F
	sub	word ptr [bp].S_TVIEW.tv_curcol,1
	sbb	word ptr [bp].S_TVIEW.tv_curcol+2,0
	jmp	reread
      endif
      @@:
	ret

event_PGLEFT:
  ifdef __BINVIEW__
	test	tvflag,_TV_HEXVIEW or _TV_BINVIEW or _TV_WRAPLINES
  else
	test	tvflag,_TV_HEXVIEW or _TV_WRAPLINES
  endif
	jnz	event_PGLEFT_02
      ifndef __16__
	mov eax,[bp].S_TVIEW.tv_curcol
	.if eax
	    .if eax >= 80
		sub eax,80
	    .else
		xor eax,eax
	    .endif
	    mov [bp].S_TVIEW.tv_curcol,eax
	    jmp reread
	.endif
      else
	lodm	[bp].S_TVIEW.tv_curcol
	mov	cx,dx
	or	cx,ax
	jz	event_PGLEFT_02
	or	dx,dx
	jnz	event_PGLEFT_00
	cmp	ax,80
	jnbe	event_PGLEFT_00
	xor	ax,ax
	cwd
	jmp	event_PGLEFT_01
    event_PGLEFT_00:
	sub	ax,80
	sbb	dx,0
    event_PGLEFT_01:
	stom	[bp].S_TVIEW.tv_curcol
	jmp	reread
      endif
    event_PGLEFT_02:
	ret

event_RIGHT:
	test	tvflag,_TV_HEXVIEW or _TV_WRAPLINES
	jnz	event_RIGHT_00
      ifndef __16__
	mov	eax,[bp].S_TVIEW.tv_curcol
	cmp	eax,[bp].S_TVIEW.tv_maxcol
      else
	lodm	[bp].S_TVIEW.tv_curcol
	cmp	dx,word ptr [bp].S_TVIEW.tv_maxcol+2
	jne	@F
	cmp	ax,word ptr [bp].S_TVIEW.tv_maxcol
      @@:
      endif
	jae	event_RIGHT_00
	incm	[bp].S_TVIEW.tv_curcol
	jmp	reread
    event_RIGHT_00:
	ret

event_PGRIGHT:
  ifdef __BINVIEW__
	test tvflag,_TV_HEXVIEW or _TV_BINVIEW or _TV_WRAPLINES
  else
	test tvflag,_TV_HEXVIEW or _TV_WRAPLINES
  endif
	jz @F
	ret
    @@:
      ifndef __16__
	mov eax,[bp].S_TVIEW.tv_curcol
	cmp eax,[bp].S_TVIEW.tv_maxcol
      else
	lodm [bp].S_TVIEW.tv_curcol
	cmp dx,word ptr [bp].S_TVIEW.tv_maxcol+2
	jne @F
	cmp ax,word ptr [bp].S_TVIEW.tv_maxcol
      @@:
      endif
	jb event_PGRIGHT_01
	ret
    event_PGRIGHT_01:
      ifndef __16__
	add eax,80
	.if eax > [bp].S_TVIEW.tv_maxcol
	    mov eax,[bp].S_TVIEW.tv_maxcol
	.endif
	mov [bp].S_TVIEW.tv_curcol,eax
      else
	add ax,80
	adc dx,0
	cmp dx,word ptr [bp].S_TVIEW.tv_maxcol+2
	jne @F
	cmp ax,word ptr [bp].S_TVIEW.tv_maxcol
      @@:
	jb @F
	lodm [bp].S_TVIEW.tv_maxcol
      @@:
	stom [bp].S_TVIEW.tv_curcol
      endif
	jmp reread

event_toend:
  ifdef __BINVIEW__
	test	tvflag,_TV_HEXVIEW or _TV_BINVIEW or _TV_WRAPLINES
  else
	test	tvflag,_TV_HEXVIEW or _TV_WRAPLINES
  endif
	jnz	event_toend_00
	lodm	[bp].S_TVIEW.tv_maxcol
	test	dx,dx
	jnz	event_toend_01
	cmp	ax,80
	jnbe	event_toend_01
    event_toend_00:
	ret
    event_toend_01:
	sub	ax,20
	sbb	dx,0

event_toend_curcol:
	stom	[bp].S_TVIEW.tv_curcol
	jmp	reread

event_tostart:
	sub	ax,ax
	cwd
	jmp	event_toend_curcol

event_togglemline:
	xor	tvflag,_TV_USEMLINE
	test	tvflag,_TV_USEMLINE
	jnz	@F
	invoke	dlhide,[bp].S_TVIEW.tv_menusline
	inc	[bp].S_TVIEW.tv_rowcnt
	jmp	reread
    @@:
	invoke	dlshow,[bp].S_TVIEW.tv_menusline
	dec	[bp].S_TVIEW.tv_rowcnt
	jmp	reread

event_togglesize:
	mov al,tvflag
	.if al & (_TV_USESLINE or _TV_USEMLINE)
	    .if al & _TV_USEMLINE
		call event_togglemline
	    .endif
	    .if !(tvflag & _TV_USESLINE)
		ret
	    .endif
	.else
	    call event_togglemline
	.endif

event_togglesline:
	xor	tvflag,_TV_USESLINE
	test	tvflag,_TV_USESLINE
	jnz	@F
	invoke	dlhide,[bp].S_TVIEW.tv_statusline
	inc	[bp].S_TVIEW.tv_rowcnt
	jmp	reread
    @@:
	invoke	dlshow,[bp].S_TVIEW.tv_statusline
	dec	[bp].S_TVIEW.tv_rowcnt
	jmp	reread

event_search:
	call	continuesearch
	test	ax,ax
	jnz	event_tostart
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

cmsearch:
	and	STDI.ios_flag,not IO_SEARCHMASK
	mov	al,fsflag
	and	ax,IO_SEARCHMASK
	or	STDI.ios_flag,ax
	pushm	[bp].S_TVIEW.tv_fsize
	call	cmdsearch
	push	ax
	and	fsflag,not IO_SEARCHMASK
	mov	ax,STDI.ios_flag
	and	STDI.ios_flag,not (IO_SEARCHSET or IO_SEARCHCUR)
	and	al,IO_SEARCHMASK
	or	fsflag,al
	pop	ax
	or	ax,ax
	jz	cmsearch_00
	jmp	reread
    cmsearch_00:
	ret

cmseek_offset:
	push	dx
	push	ax
      ifdef __3__
	mov	eax,STDI.ios_bb
	add	eax,[bp].S_TVIEW.tv_curcol
	push	eax
	xor	eax,eax
	mov	[bp].S_TVIEW.tv_curcol,eax
      else
	lodm	STDI.ios_bb
	add	ax,word ptr [bp].S_TVIEW.tv_curcol
	adc	dx,word ptr [bp].S_TVIEW.tv_curcol+2
	push	dx
	push	ax
	xor	ax,ax
	mov	word ptr [bp].S_TVIEW.tv_curcol,ax
	mov	word ptr [bp].S_TVIEW.tv_curcol+2,ax
      endif
	mov	ax,offset format_08Xh
	test	tvflag,_TV_HEXOFFSET
	jnz	cmseek_offset_hex
	mov	ax,offset format_lu
    cmseek_offset_hex:
	invoke	sprintf,es:[bx+24],ds::ax
	add	sp,4
	call	dlinit
	ret

cmseek:
	invoke	rsopen, IDD_TVSeek
	jz	cmseek_02
	push	dx
	push	ax
	pushm	IDD_TVSeek
	push	dx
	push	ax
	call	cmseek_offset
	call	rsevent
	or	ax,ax
	jz	@F
	invoke	strtol, es:[bx+24]
    ifdef __MEMVIEW__
	.if STDI.ios_flag & IO_MEMREAD
	    call normalize
	.endif
    endif
	call	cmp_dxax_fsize
	ja	@F
	stom	STDI.ios_bb
	call	dlclose
	jmp	reread
    @@:
	call	dlclose
	xor	ax,ax
    cmseek_02:
	ret

cmcopy:
	invoke	rsopen,IDD_TVCopy
	jz	cmcopy_end
	push	dx
	push	ax
	pushm	IDD_TVCopy
	push	dx
	push	ax
	stom	[bp].S_TVIEW.tv_tmp
	cmp	UseClipboard,0
	jz	@F
	or	byte ptr es:[bx+4*16],_O_FLAGB
      @@:
	call	cmseek_offset
	call	rsevent
	or	ax,ax
	jz	cmcopy_close
	mov	UseClipboard,0
	test	byte ptr es:[bx+4*16],_O_FLAGB
	jz	@F
	mov	UseClipboard,1
      @@:
	invoke	strtol, es:[bx+24]
	call	cmp_dxax_fsize
	jb	cmcopy_05
	xor	ax,ax
    cmcopy_close:
	call	dlclose
	mov	ax,dx
	or	ax,ax
    cmcopy_end:
	ret
    cmcopy_04:
	mov	ax,1
	jmp	cmcopy_close
    cmcopy_05:
	invoke	oseek, dx::ax, SEEK_SET
	jz	cmcopy_06
	cmp	UseClipboard,0
	jne	cmcopy_07
	mov	ax,OSTDO
	invoke	oinitst,addr STDO,8000h
	jz	cmcopy_close
	les	bx,[bp].S_TVIEW.tv_tmp
	invoke	ogetouth, es:[bx+56]
	cmp	ax,-1
	je	cmcopy_06
	mov	STDO.ios_file,ax
	les	bx,[bp].S_TVIEW.tv_tmp
	invoke	strtol, es:[bx+40]
	invoke	ocopy, dx::ax
	call	oflush
	invoke	oclose,addr STDO
	jmp	cmcopy_04
    cmcopy_06:
	invoke	ofreest,addr STDO
	jmp	cmcopy_04
    cmcopy_07:
	les	bx,[bp].S_TVIEW.tv_tmp
	invoke	strtol, es:[bx+40]
	or	dx,dx
	jnz	cmcopy_04
	or	ax,ax
	jz	cmcopy_04
	cmp	ax,STDI.ios_c
	ja	cmcopy_04
	invoke	ClipboardCopy, STDI.ios_bp, ax
	call	ClipboardFree
	jmp	cmcopy_04

cmmcopy:
  ifdef __MOUSE__
	push	bp
	mov	bp,sp
	sub	sp,81
	push	si
	push	di
	push	ds
	call	mousex
	mov	bx,ax
	call	mousey
	mov	bh,al
	invoke	rcsprc,ax::bx
	mov	ds,dx
	mov	si,ax
	lea	di,[bp-81]
	mov	cx,80
	sub	cl,bl
	mov	bx,di
	push	ss
	pop	es
	cld?
    cmmcopy_loop:
	lodsw
	stosb
	dec	cx
	jnz	cmmcopy_loop
	xor	ax,ax
	stosb
	pop	ds
	push	ss
	push	bx
	call	strtrim
	jz	cmmcopy_end
	push	ss
	push	bx
	push	ax
	call	ClipboardCopy
	call	ClipboardFree
    cmmcopy_end:
	pop	di
	pop	si
	mov	sp,bp
	pop	bp
  endif
	ret

update_dialog:
	push di
	xor bx,bx
	xor di,di
	.if tvflag & _TV_USEMLINE
	    inc di
	.endif
	mov cx,[bp].S_TVIEW.tv_rowcnt
	mov dh,0
	mov dl,_scrcol
	mov al,at_background[B_TextView]
	or  al,at_foreground[F_Textview]
	.if tvflag & _TV_HIGHCOLOR
	    mov al,0Fh
	.endif
	.repeat
	    invoke scputa,bx,di,dx,ax
	    inc di
	.untilcxz
	.if tvflag & _TV_USESLINE
	    mov bl,35
	    mov cx,5
	    mov ax,offset cp_hex
    ifdef __CLASSVIEW__
	    .if tvflag & _TV_HEXVIEW or _TV_CLASSVIEW
		mov ax,offset cp_class
		.if tvflag & _TV_HEXVIEW
		    mov ax,offset cp_ascii
		.endif
	    .endif
    else
	    .if tvflag & _TV_HEXVIEW
		mov ax,offset cp_ascii
	    .endif
    endif
	    invoke scputs,bx,di,0,cx,ds::ax
	    mov bl,13
	    inc cl
	    mov ax,offset cp_unwrap
	    .if tvflag & _TV_WRAPLINES
		mov ax,offset cp_wrap
	    .endif
	    invoke scputs,bx,di,0,cx,ds::ax
	    mov bl,54
	    mov cl,3
	    mov ax,offset cp_deci
	    .if tvflag & _TV_HEXOFFSET
		mov ax,offset cp_hex
	    .endif
	    invoke scputs,bx,di,0,cx,ds::ax
	.endif
	pop di
	ret

update_reread:
	call	update_dialog
	jmp	reread

if_fsize:
	mov	ax,word ptr [bp].S_TVIEW.tv_fsize+2
	or	ax,word ptr [bp].S_TVIEW.tv_fsize
	jnz	@F
	pop	ax
	xor	ax,ax
      @@:
	ret

cmwrap:
	call	if_fsize
	test	tvflag,_TV_HEXVIEW
	jnz	cmwrap_00
	xor	tvflag,_TV_WRAPLINES
	jmp	update_reread
    cmwrap_00:
	xor	ax,ax
	ret

cmoffset:
	call	if_fsize
	xor	tvflag,_TV_HEXOFFSET
	jmp	update_reread

ifdef __BINVIEW__
cmbinary:
	call	if_fsize
	test	tvflag,_TV_HEXVIEW
	jnz	cmbinary_00
	or	tvflag,_TV_HEXVIEW or _TV_BINVIEW
	jmp	update_reread
    cmbinary_00:
	xor	tvflag,_TV_BINVIEW
	jmp	update_reread
endif

cmhex:
	call	if_fsize
	mov	al,tvflag
	mov	ah,al
    ifdef __CLASSVIEW__
      ifdef __BINVIEW__
	and	al,not (_TV_HEXVIEW or _TV_CLASSVIEW or _TV_BINVIEW)
      else
	and	al,not (_TV_HEXVIEW or _TV_CLASSVIEW)
      endif
	test	ah,_TV_HEXVIEW or _TV_CLASSVIEW
	jz	@F
	test	ah,_TV_CLASSVIEW
	jnz	cmhex_set
	or	al,_TV_CLASSVIEW
	jmp	cmhex_set
      @@:
    else
      ifdef __BINVIEW__
	and	al,not (_TV_HEXVIEW or _TV_BINVIEW)
      else
	and	al,not _TV_HEXVIEW
      endif
	test	ah,_TV_HEXVIEW
	jnz	cmhex_set
    endif
	or	al,_TV_HEXVIEW
    cmhex_set:
	mov	tvflag,al
    ifdef __CLASSVIEW__
	and	al,_TV_HEXVIEW or _TV_CLASSVIEW
    else
	and	al,_TV_HEXVIEW
    endif
	jnz	cmhex_hex
    ifdef __3__
	mov eax,[bp].S_TVIEW.tv_curcol
	.if eax <= STDI.ios_bb
	    sub STDI.ios_bb,eax
	.endif
    else
	lodm [bp].S_TVIEW.tv_curcol
	cmp dx,word ptr STDI.ios_bb+2
	jne @F
	cmp ax,word ptr STDI.ios_bb
      @@:
	ja @F
	sub word ptr STDI.ios_bb,ax
	sbb word ptr STDI.ios_bb+2,dx
      @@:
    endif
	jmp	update_reread
    cmhex_hex:
    ifdef __3__
	mov eax,[bp].S_TVIEW.tv_curcol
	add STDI.ios_bb,eax
	xor eax,eax
	mov [bp].S_TVIEW.tv_curcol,eax
    else
	lodm [bp].S_TVIEW.tv_curcol
	add word ptr STDI.ios_bb,ax
	adc word ptr STDI.ios_bb+2,dx
	xor ax,ax
	mov word ptr [bp].S_TVIEW.tv_curcol,ax
	mov word ptr [bp].S_TVIEW.tv_curcol+2,ax
    endif
	jmp	update_reread

cmcolor:
	xor	tvflag,_TV_HIGHCOLOR
	call	update_dialog
	mov	ax,1
	ret

ifdef __TVEXE__
cmabout proc _CType
	invoke	rsmodal, addr TVABOUT_RC
	ret
cmabout endp
endif

cmhelp:
    ifdef __TVEXE__
	.if rsopen(IDD_TVHelpEXE)
	    push dx
	    push ax
	    push dx
	    push ax
	    movp es:[bx].S_TOBJ.to_proc+32,cmabout
	    call dlevent
	    call dlclose
	.endif
    else
	invoke rsmodal,IDD_TVHelp
    endif
	ret

cmquit:
	mov	ax,1
	mov	[bp].S_TVIEW.tv_switch,ax
	dec	ax
	ret

cmconsole:
	invoke	dlhide,[bp].S_TVIEW.tv_dialog
      @@:
	call	getkey
	or	ax,ax
	jz	@B
	invoke	dlshow,[bp].S_TVIEW.tv_dialog
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

ifdef __MOUSE__

mouse_scroll:
	xor	cx,cx
	mov	es,cx
	mov	cl,es:[0484h]
	xor	bx,bx
	cmp	cx,24
	jz	mouse_scroll_00
	shr	ax,1
	shr	dx,1
    mouse_scroll_00:
	cmp	dx,8
	jc	mouse_scroll_07
	cmp	dx,16
	ja	mouse_scroll_06
	cmp	dx,8
	jc	mouse_scroll_03
	cmp	dx,16
	ja	mouse_scroll_03
	cmp	ax,31
	jc	mouse_scroll_05
	cmp	ax,50
	ja	mouse_scroll_04
	cmp	dx,12
	jnz	mouse_scroll_01
	cmp	ax,39
	ja	mouse_scroll_04
	jmp	mouse_scroll_05
    mouse_scroll_01:
	cmp	dx,11
	jb	mouse_scroll_02
	cmp	dx,13
	ja	mouse_scroll_02
	cmp	ax,36
	jb	mouse_scroll_05
	cmp	ax,45
	ja	mouse_scroll_04
    mouse_scroll_02:
	cmp	dx,12
	jb	mouse_scroll_07
	ja	mouse_scroll_06
    mouse_scroll_03:
	ret
    mouse_scroll_04:
	inc	bx
    mouse_scroll_05:
	inc	bx
    mouse_scroll_06:
	inc	bx
    mouse_scroll_07:
	inc	bx
	push	bx
	cmp	ax,37
	jb	mouse_scroll_09
	cmp	ax,43
	jb	mouse_scroll_08
	mov	bx,79
	sub	bx,ax
	mov	ax,bx
	jmp	mouse_scroll_09
    mouse_scroll_08:
	xor	ax,ax
    mouse_scroll_09:
	shl	ax,2
	cmp	dx,12
	je	mouse_scroll_10
	jb	mouse_scroll_11
	mov	cx,24
	sub	cx,dx
	mov	dx,cx
	jmp	mouse_scroll_11
    mouse_scroll_10:
	xor	dx,dx
    mouse_scroll_11:
	add	dx,dx
	add	dx,dx
	pop	bx
	ret
    mouse_scroll_proc:
	call	mousey
	push	ax
	call	mousex
	pop	dx
	call	mouse_scroll
	ret
    mouse_scroll_up:
	mov	ax,KEY_UP
	jmp	mouse_scroll_updn
    mouse_scroll_down:
	mov	ax,KEY_DOWN
    mouse_scroll_updn:
	push	dx
	jmp	mouse_scroll_event
    mouse_scroll_left:
	push	ax
	mov	ax,KEY_LEFT
	jmp	mouse_scroll_event
    mouse_scroll_right:
	push	ax
	mov	ax,KEY_RIGHT
    mouse_scroll_event:
	call	tview_event
	pop	ax
	mov	di,ax
    mouse_scroll_delay:
	or	di,di
	jz	@F
	push	di
	call	delay
      @@:
	ret
    scroll:
	push	di
	xor	di,di
	call	mouse_scroll_proc
	add	bx,bx
	call	[bx+label_scroll]
	pop	di
	ret

mouse_event:
	call	mousep
	jz	mouse_event_07
	cmp	ax,2
	je	mouse_event_09
	call	mousex
	mov	[bp].S_TVIEW.tv_xpos,ax
	call	mousey
	mov	[bp].S_TVIEW.tv_ypos,ax
	inc	ax
	cmp	al,rsrows
	jne	mouse_event_08
	test	tvflag,_TV_USESLINE
	jz	mouse_event_08
	call	msloop
	mov	ax,[bp].S_TVIEW.tv_xpos
	cmp	al,9
	jnb	mouse_event_00
	jmp	cmhelp
    mouse_event_00:
	je	mouse_event_07
	cmp	al,20
	jnb	mouse_event_01
	jmp	cmwrap
    mouse_event_01:
	jz	mouse_event_07
	cmp	al,31
	jnb	mouse_event_02
	jmp	cmsearch
    mouse_event_02:
	je	mouse_event_07
	cmp	al,41
	jnb	mouse_event_03
	jmp	cmhex
    mouse_event_03:
	je	mouse_event_07
	cmp	al,50
	jnb	mouse_event_04
	jmp	cmcopy
    mouse_event_04:
	je	mouse_event_07
	cmp	al,58
	jnb	mouse_event_05
	jmp	cmoffset
    mouse_event_05:
	je	mouse_event_07
	cmp	al,66
	jnbe	mouse_event_06
	jmp	cmseek
    mouse_event_06:
	cmp	al,70
	jbe	mouse_event_07
	call	cmquit
    mouse_event_07:
	xor	ax,ax
	ret
    mouse_event_08:
	call	mousep
	cmp	ax,1
	jne	mouse_event_07
	call	scroll
	jmp	mouse_event_08
    mouse_event_09:
	call	cmmcopy
	call	msloop
	ret

endif ; __MOUSE__

tview_event:
	mov	cx,local_count
	xor	bx,bx
	mov	dx,word ptr [bp].S_TVIEW.tv_fsize
	or	dx,word ptr [bp].S_TVIEW.tv_fsize+2
	jnz	@F
	mov	cx,global_count
      @@:
	cmp	ax,[bx+key_global]
	je	@F
	add	bx,2
	dec	cx
	jnz	@B
	ret
      @@:
	jmp	[bx+proc_label]

modal:
	cmp	[bp].S_TVIEW.tv_switch,0
	jne	modal_exit
  ifdef __CLASSVIEW__
	test	tvflag,_TV_CLASSVIEW
	jz	modal_event
	call	dlxcellevent
	cmp	ax,-1
	je	modal_event
	jmp	modal_hndevent
  endif
    modal_event:
  ifdef __MOUSE__
	call	mousep
	or	ax,ax
	jnz	modal_mouse
  endif
	call	getkey
    modal_hndevent:
	or	ax,ax
	jz	modal_event
	call	tview_event
	jmp	modal
  ifdef __MOUSE__
    modal_mouse:
	call	mouse_event
	call	msloop
	jmp	modal
  endif
    modal_exit:
	xor	ax,ax
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

dummy_update proc _CType private
	xor	ax,ax
	ret
dummy_update endp

ifdef __MEMVIEW__
tview proc _CType public filename:dword, offs:dword, address:dword, memsize:dword
else
tview proc _CType public filename:dword, offs:dword
endif
local	tv:S_TVIEW
	push	si
	push	di
	push	bp
	mov	si,STDI.ios_flag
	lodm	offs
  ifdef __MEMVIEW__
	.if si & IO_MEMREAD
	    call normalize		; offset == pointer
	.endif
  endif
	stom	tv.tv_offset
	movmx	tv.tv_filename,filename
  ifdef __MEMVIEW__
	movmm	tv.tv_address,address
	call	normalize
	stom	tvmem_offs
	mov	bx,word ptr memsize
	mov	cx,word ptr memsize+2
	add	ax,bx
	adc	dx,cx
	or	bx,cx
	.if dx > 000Fh || !bx
	    mov dx,000Fh
	    mov ax,0FFFFh
	.endif
	stom	tvmem_size
  endif
	lea	bp,tv
	mov	ax,bp
  ifdef __MEMVIEW__
	add	ax,12
	invoke	memzero, ss::ax, S_TVIEW - 12
  else
	add	ax,8
	invoke	memzero, ss::ax, S_TVIEW - 8
  endif
	mov	STDI.ios_flag,si
	movmx	STDI.ios_bb,[bp].S_TVIEW.tv_offset
	mov	ah,0
	mov	al,_scrrow
	mov	bx,word ptr IDD_TVStatusline
	mov	[bx+7],al
	inc	al
	mov	rsrows,al
	test	tvflag,_TV_USEMLINE
	jz	@F
	dec	al
      @@:
	test	tvflag,_TV_USESLINE
	jz	@F
	dec	al
      @@:
	mov	[bp].S_TVIEW.tv_rowcnt,ax ; adapt to current screen size
	mov	STDI.ios_size,8000h	  ; init stream
	xor	ax,ax
  ifdef __MEMVIEW__
	test	si,IO_MEMREAD
	jnz	@F
  else
	mov	STDI.ios_flag,ax
  endif
	invoke	osopen,[bp].S_TVIEW.tv_filename,ax,ax,A_OPEN
	mov	STDI.ios_file,ax
	inc	ax
	jz	textview_05
      @@:
  ifdef __CLASSVIEW__
	call	init_class
  endif
	mov	ax,[bp].S_TVIEW.tv_rowcnt
	add	ax,2
	sub	cx,cx
	mov	cl,_scrcol
	mul	cx
	add	ax,800Ch
	invoke	malloc,ax
	stom	STDI.ios_bp
	mov	bx,ax
	add	ax,800Ch
	stom	[bp].S_TVIEW.tv_screen
	or	bx,bx
	jz	@F
	mov	al,at_background[B_TextView]
	or	al,at_foreground[F_Textview]
	invoke	dlscreen,addr DLG_Textview,ax
	jnz	textview_06
	invoke	free, STDI.ios_bp
      @@:
  ifdef __MEMVIEW__
	test	STDI.ios_flag,IO_MEMREAD
	jnz	@F
  endif
	invoke	close, STDI.ios_file
      @@:
	mov	ax,1
    textview_05:
	pop	bp
	pop	di
	pop	si
	ret
    textview_06:
	stom	[bp].S_TVIEW.tv_dialog
	invoke	dlshow, dx::ax
	invoke	rsopen, IDD_TVMenusline
	stom	[bp].S_TVIEW.tv_menusline
	invoke	dlshow, dx::ax
	invoke	rsopen, IDD_TVStatusline
	stom	[bp].S_TVIEW.tv_statusline
	test	tvflag,_TV_USESLINE
	jz	@F
	invoke	dlshow, dx::ax
      @@:
  ifdef __MOUSE__
	call	mouseoff
  endif
	lodm	[bp].S_TVIEW.tv_filename
  ifdef __MEMVIEW__
	test	ax,ax
	jnz	@F
	mov	ax,offset cp_memory
	mov	dx,ds
      @@:
  endif
	invoke	scpath,1,0,41,dx::ax
	add	ax,14
	mov	si,ax
  ifdef __MEMVIEW__
	mov	ax,word ptr tvmem_size
	mov	dx,word ptr tvmem_size+2
	test	STDI.ios_flag,IO_MEMREAD
	jnz	textview_08
  endif
	mov	ax,4202h
	mov	bx,STDI.ios_file
	xor	cx,cx
	xor	dx,dx
	int	21h
	jc	textview_09
    textview_08:
	stom	[bp].S_TVIEW.tv_fsize
    textview_09:
	invoke	qwtobstr,0,dx::ax
	mov	bx,si
	mov	cl,bh
	invoke	scputs,bx,cx,0,0,dx::ax
	add	bl,al
	invoke	scputs,bx,cx,0,0,addr cp_byte
	test	tvflag,_TV_USEMLINE
	jnz	@F
	invoke	dlhide,[bp].S_TVIEW.tv_menusline
      @@:
	invoke	cursorget,addr [bp].S_TVIEW.tv_cursor
	invoke	gotoxy,0,1
	call	cursoroff
	pushl	word ptr tupdate+2
	push	word ptr tupdate
	movl	word ptr tupdate+2,cs
	mov	word ptr tupdate,offset dummy_update
  ifdef __MOUSE__
	call	mouseon
  endif
	call	update_dialog
  ifdef __MOUSE__
	call	msloop
  endif
	call	read_static_table
	call	reread
	call	modal
	pop	ax
	popl	dx
	mov	word ptr tupdate,ax
	movl	word ptr tupdate+2,dx
	invoke	dlclose, [bp].S_TVIEW.tv_statusline
	invoke	dlclose, [bp].S_TVIEW.tv_menusline
	invoke	dlclose, [bp].S_TVIEW.tv_dialog
	invoke	free, STDI.ios_bp
  ifdef __CLASSVIEW__
	movmx	tdialog,[bp].S_TVIEW.tv_tdialog
  endif
  ifdef __MEMVIEW__
	test	STDI.ios_flag,IO_MEMREAD
	jnz	textview_10
  endif
	invoke	close, STDI.ios_file
    textview_10:
	xor	ax,ax
	mov	STDI.ios_flag,ax
	invoke	cursorset,addr [bp].S_TVIEW.tv_cursor
	jmp	textview_05
tview endp

ifdef DEBUG
_DZIP	ENDS
endif
	END
