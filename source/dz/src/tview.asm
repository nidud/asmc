; TVIEW.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT
;
; Change history:
; 2016-03-09 - fixed CR/LF read
; 2013-09-19 - tview.asm -- 32 bit
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
; 2004-06-27 - tview.asm -- 16 bit
; 1998-02-10 - tview.c
;

include alloc.inc
include string.inc
include stdio.inc
include stdlib.inc
include io.inc
include direct.inc
include errno.inc
include iost.inc
include consx.inc
include crtl.inc
include time.inc
include tview.inc

externdef	tvflag: BYTE
externdef	fsflag: BYTE
externdef	IDD_TVCopy:DWORD
externdef	IDD_TVSeek:DWORD
externdef	IDD_TVHelp:DWORD
externdef	IDD_TVQuickMenu:DWORD


PUBLIC		format_lu

tvabout		PROTO
cmsearchidd	PROTO :DWORD

MAXLINE		equ 8000h
MAXLINES	equ 256

S_TVIEW		STRUC
tv_filename	dd ?
tv_offset	dd ?
tv_loffs	dd ?
tv_dialog	dd ?		; main dialog pointer
tv_rowcnt	dd ?		; max lines (23/48)
tv_lcount	dd ?		; lines on screen
tv_scount	dd ?		; bytes on screen
tv_maxcol	dd ?		; max linesize on screen
tv_curcol	dd ?		; current line offset (col)
tv_screen	dd ?		; screen buffer
tv_menusline	dd ?
tv_statusline	dd ?
tv_switch	dd ?		; main switch
tv_cursor	S_CURSOR <>	; cursor (old)
tv_bsize	dd ?		; buffer size
tv_xpos		dd ?		; temp (mouse)
tv_ypos		dd ?		; temp (mouse)
tv_zpos		dd ?		; temp (mouse)
tv_tmp		dd ?		; temp 32
tv_static_count dd ?		; line count
tv_line_table	dd 256 dup(?)	; line offset in file
tv_static_table dd MAXLINES dup(?) ; offset of first <MAXLINES> lines
S_TVIEW		ENDS

.data

cp_deci		db 'Dec'
cp_hex		db 'Hex  '
cp_ascii	db 'Ascii'
cp_wrap		db 'Wrap  '
cp_unwrap	db 'Unwrap'
cp_byte		db 'byte',0
cp_stlsearch	db 'Search for the string:',0
externdef	searchstring:BYTE

QuickMenuKeys	dd KEY_F5
		dd KEY_F7
		dd KEY_F2
		dd KEY_F4
		dd KEY_F6
		dd KEY_ESC

key_global	dd KEY_F1,	tvhelp
		dd KEY_F2,	cmwrap
		dd KEY_F3,	cmsearch
		dd KEY_F4,	cmhex
		dd KEY_F5,	cmcopy
		dd KEY_F6,	cmoffset
		dd KEY_F7,	cmseek
		dd KEY_F10,	cmquit
		dd KEY_ESC,	cmquit
		dd KEY_ALTX,	cmquit
		dd KEY_ALTF5,	cmconsole
		dd KEY_CTRLB,	cmconsole
		dd KEY_CTRLM,	event_togglemline
		dd KEY_CTRLS,	event_togglesline
		dd KEY_F11,	event_togglesize

global_count = (($ - offset key_global) / 8)

key_local	dd KEY_UP,	event_UP
		dd KEY_DOWN,	event_DOWN
		dd KEY_PGUP,	event_PGUP
		dd KEY_PGDN,	event_PGDN
		dd KEY_LEFT,	event_LEFT
		dd KEY_RIGHT,	event_RIGHT
		dd KEY_HOME,	event_HOME
		dd KEY_END,	event_END
		dd KEY_CTRLE,	event_UP
		dd KEY_CTRLX,	event_DOWN
		dd KEY_CTRLR,	event_PGUP
		dd KEY_CTRLC,	event_PGDN
		dd KEY_MOUSEUP, event_MOUSEUP
		dd KEY_MOUSEDN, event_MOUSEDN
		dd KEY_CTRLLEFT,event_PGLEFT
		dd KEY_CTRLRIGHT,event_PGRIGHT
		dd KEY_SHIFTF3, event_search
		dd KEY_CTRLL,	event_search
		dd KEY_CTRLEND, event_toend
		dd KEY_CTRLHOME,event_tostart

local_count = (($ - offset key_global) / 8)

label_scroll	dd mouse_scroll_delay
		dd mouse_scroll_up
		dd mouse_scroll_down
		dd mouse_scroll_left
		dd mouse_scroll_right

DLG_Textview	S_DOBJ <?>
UseClipboard	db ?
rsrows		db 24

format_lu	db "%u",0
format_08Xh	db "%08Xh",0

;******** Resource begin TVStatusline *
;	{ 0x0054,   0,	 0, { 0,24,80, 1} },
;******** Resource data	 *******************
Statusline_RC	dw 0200h,0054h,0000h
		db 0
Statusline_Y	db 24
Statusline_C0	db 80,1
		dw 03F3Ch,0F03Fh,03C07h,03F3Fh
		dw 09F0h,3F3Ch,0F03Fh,03C09h,03F3Fh,008F0h,03F3Ch,0F03Fh
		dw 03C07h,03F3Fh,006F0h,03F3Ch,0F03Fh,03C0Ah,03F0h
		db 3Fh,0F0h
Statusline_C1	db 6,3Ch
		dw 04620h,02031h,06548h,0706Ch,02020h,03246h,05720h
		dw 06172h,0F070h,02004h,03346h,05320h,06165h,06372h,02068h
		dw 04620h,02034h,06548h,0F078h,02004h,03546h,04320h,0706Fh
		dw 02079h,04620h,02036h,06544h,02063h,04620h,02037h,06553h
		dw 06B65h,005F0h,04520h,06373h,05120h,06975h
		db 74h
		db 0F0h
Statusline_C2	db 1,' '
IDD_Statusline	dd Statusline_RC

;******** Resource begin TVMenusline *
;	{ 0x0050,   0,	 0, { 0, 0,80, 1} },
;******** Resource data	 *******************
Menusline_RC	dw 0200h,0050h,0000h,0000h
Menusline_C0	db 80,1,0F0h
Menusline_C1	db 80,3Ch,0F0h
Menusline_C2	db 80,' '
IDD_Menusline	dd Menusline_RC

	.code

	ASSUME	ebp:PTR S_TVIEW

	OPTION	PROC: PRIVATE

seek_eax PROC
	xor	edx,edx
	ioseek( addr STDI, edx::eax, SEEK_SET )
	ret
seek_eax ENDP

add_offset PROC USES edx
	mov	eax,[ebp].tv_lcount
	inc	[ebp].tv_lcount
	lea	edx,[ebp+eax*4].tv_line_table
	mov	eax,[ebp].tv_offset
	mov	[edx],eax
	ret
add_offset ENDP

read_static_table PROC USES esi edi	 ; offset of first <MAXLINES> lines
	lea	edi,[ebp].tv_static_table
	xor	eax,eax
	xor	esi,esi
	stosd
	mov	[ebp].tv_offset,eax
	mov	[ebp].tv_static_count,1
	call	seek_eax
	.if	!ZERO?
		.repeat
			call	ogetc
			.if	ZERO?
				mov	eax,[ebp].tv_offset
				stosd
				stosd
				jmp	toend
			.endif
			inc	[ebp].tv_offset
			inc	esi
			.if	esi == MAXLINE
				xor	esi,esi
				mov	eax,10
			.endif
			.if	eax == 10
				mov	eax,[ebp].tv_offset
				stosd
				inc	[ebp].tv_static_count
			.endif
		.until	[ebp].tv_static_count > MAXLINES-3
		dec	[ebp].tv_static_count
	.endif
toend:
	ret
read_static_table ENDP

read_line_table PROC
	push	esi

	mov	[ebp].tv_lcount,1
	mov	eax,[ebp].tv_loffs
	mov	[ebp].tv_line_table,eax
	mov	[ebp].tv_offset,eax

	movzx	ecx,tvflag
	test	ecx,_TV_HEXVIEW
	jnz	@hex
	test	ecx,_TV_WRAPLINES
	jnz	toend

	lea	edx,[ebp].tv_static_table
	mov	ecx,[ebp].tv_static_count
	.repeat
		.break .if eax == [edx]
		add	edx,4
	.untilcxz
	.if	ecx
		.repeat
			add	edx,4
			mov	eax,[edx]
			mov	[ebp].tv_offset,eax
			call	add_offset
			mov	eax,[ebp].tv_lcount
			cmp	eax,[ebp].tv_rowcnt
			ja	@max
		.untilcxz
		mov	eax,[ebp].tv_offset
		cmp	eax,DWORD PTR STDI.ios_fsize
		je	@max
	.endif

	call	seek_eax
	jz	toend
	xor	esi,esi
	.repeat
		call	ogetc
		.break .if ZERO?
		inc	[ebp].tv_offset
		inc	esi
		.if	esi == MAXLINE
			xor	esi,esi
			mov	eax,10
		.endif
		.if	eax == 10
			call	add_offset
			mov	eax,[ebp].tv_lcount
			cmp	eax,[ebp].tv_rowcnt
			ja	@max
		.endif
	.until	0
@eof:
	call	add_offset
	call	add_offset
	dec	[ebp].tv_lcount
@max:
	dec	[ebp].tv_lcount
toend:
	pop	esi
	jnz	init_screenbuf
	ret
@hex:
	call	seek_eax
	jz	toend
	mov	esi,16
	xor	ecx,ecx
@@:
	mov	eax,[ebp].tv_offset
	add	eax,esi
	mov	[ebp].tv_offset,eax
	cmp	eax,DWORD PTR STDI.ios_fsize
	ja	@F
	call	add_offset
	inc	ecx
	cmp	ecx,[ebp].tv_rowcnt
	jb	@B
	jmp	@eof
@@:
	mov	eax,DWORD PTR STDI.ios_fsize
	mov	[ebp].tv_offset,eax
	jmp	@eof
read_line_table ENDP

init_screenbuf PROC USES edi
	mov	eax,_scrcol
	mul	[ebp].tv_rowcnt
	mov	ecx,eax
	mov	edi,[ebp].tv_screen
	mov	eax,20h
	rep	stosb
	mov	eax,[ebp].tv_loffs
	mov	[ebp].tv_offset,eax
	call	seek_eax
	ret
init_screenbuf ENDP

parse_line PROC
	push	esi
	push	edi
	xor	esi,esi
lup:
	call	ogetc
	jz	break
	inc	[ebp].tv_offset
	cmp	al,10
	je	@04
	cmp	al,13
	je	@04
	cmp	al,9
	je	@TAB
	test	al,al
	jnz	@F
	mov	al,' '
@@:
	mov	[edi],al
	inc	edi
	inc	esi
@01:
	cmp	esi,_scrcol
	je	@07
	jb	lup
break:
	pop	edi
	pop	esi
	jz	toend
	add	edi,_scrcol
toend:
	ret
done:
	xor	eax,eax
	inc	eax
	jmp	break
@04:
	call	ogetc
	jz	break
	inc	[ebp].tv_offset
	cmp	al,13
	je	done
	cmp	al,10
	je	done
@05:
	dec	[ebp].tv_offset
	dec	STDI.ios_i
	jmp	done
@TAB:
	mov	eax,esi
	add	eax,[ebp].tv_curcol
	add	eax,8
	and	eax,-8
	sub	eax,esi
	sub	eax,[ebp].tv_curcol
	add	esi,eax
	add	edi,eax
	jmp	@01
@07:
	call	ogetc
	jz	break
	inc	[ebp].tv_offset
	cmp	al,10
	je	@04
	cmp	al,13
	je	@04
	jmp	@05
parse_line ENDP

read_wrap PROC USES edi
	call	read_line_table
	mov	eax,0
	jz	toend
	mov	edi,[ebp].tv_screen
	mov	[ebp].tv_bsize,eax
	mov	[ebp].tv_lcount,eax
@@:
	mov	eax,[ebp].tv_bsize
	inc	[ebp].tv_bsize
	cmp	eax,[ebp].tv_rowcnt
	jnb	@F
	call	add_offset
	call	parse_line
	jnz	@B
@@:
	mov	eax,[ebp].tv_offset
	sub	eax,[ebp].tv_loffs
	mov	[ebp].tv_scount,eax
	or	eax,1
toend:
	ret
read_wrap ENDP

read_text PROC USES edi
	call	read_line_table
	jz	toend
	mov	edx,[ebp].tv_maxcol
	mov	eax,[ebp].tv_lcount
@@:
	test	eax,eax
	jz	@F
	mov	ecx,[ebp+eax*4].tv_line_table
	dec	eax
	sub	ecx,[ebp+eax*4].tv_line_table
	cmp	ecx,edx
	jna	@B
	mov	edx,ecx
	jmp	@B
@@:
	mov	[ebp].tv_maxcol,edx
	mov	edi,[ebp].tv_screen
	mov	[ebp].tv_bsize,0
lup:
	mov	eax,[ebp].tv_bsize
	inc	[ebp].tv_bsize
	cmp	eax,[ebp].tv_lcount
	jae	break
	lea	edx,[ebp+eax*4].tv_line_table
	mov	eax,[edx+4]
	sub	eax,[edx]
	add	[ebp].tv_scount,eax
	cmp	eax,[ebp].tv_curcol
	ja	@F
	add	edi,_scrcol
	jmp	lup
@@:
	mov	eax,[edx]
	add	eax,[ebp].tv_curcol
	call	seek_eax
	jz	toend
	call	parse_line
	jnz	lup
break:
	or	eax,1
toend:
	ret
read_text ENDP

mk_hexword PROC
	mov	ah,al
	and	eax,0FF0h
	shr	al,4
	or	eax,3030h
	cmp	ah,39h
	jna	@F
	add	ah,7
@@:
	cmp	al,39h
	jna	@F
	add	al,7
@@:
	ret
mk_hexword ENDP

read_hex PROC USES esi edi ebx
	call	read_line_table
	jz	toend
	call	ogetc
	jz	toend

	dec	STDI.ios_i
	push	STDI.ios_c
	mov	eax,[ebp].tv_rowcnt
	shl	eax,4
	cmp	eax,STDI.ios_c
	ja	@F
	mov	STDI.ios_c,eax
@@:
	mov	eax,STDI.ios_c
	xor	ecx,ecx
	mov	[ebp].tv_scount,eax
	mov	esi,[ebp].tv_screen
lup:
	mov	edi,esi
	lea	ebx,[ebp+ecx*4+3].tv_line_table
	test	tvflag,_TV_HEXOFFSET
	jnz	@F
	;push	ecx
	sprintf( edi, "%010u  ", [ebx-3] )
	;pop	ecx
	add	edi,9
	jmp	@2
@@:
	mov	edx,4
@@:
	mov	al,[ebx]
	call	mk_hexword
	stosw
	dec	ebx
	dec	edx
	jnz	@B
	inc	edi
@2:
	mov	edx,STDI.ios_c
	mov	eax,16
	add	edi,3
	cmp	edx,eax
	jb	@F
	mov	edx,eax
@@:
	test	edx,edx
	jz	break
	sub	STDI.ios_c,edx
	mov	ebx,edi
	add	ebx,51
	push	ecx
	mov	ecx,edx
	xor	edx,edx
lup2:
	cmp	edx,8
	jne	@F
	mov	al,179
	stosb
	inc	edi
@@:
	mov	eax,STDI.ios_i
	cmp	eax,DWORD PTR STDI.ios_fsize
	jae	break2
	add	eax,STDI.ios_bp
	mov	al,[eax]
	inc	STDI.ios_i
	mov	[ebx],al
	test	al,al
	jnz	@F
	mov	BYTE PTR [ebx],' '
@@:
	call	mk_hexword
	stosw
	inc	edi
	inc	ebx
	inc	edx
	dec	ecx
	jnz	lup2
break2:
	pop	ecx
	add	esi,_scrcol
	inc	ecx
	cmp	ecx,[ebp].tv_lcount
	jb	lup
break:
	pop	eax
	mov	STDI.ios_c,eax
	mov	eax,1
toend:
	ret
read_hex ENDP

previous_line PROC
	mov	eax,[ebp].tv_loffs
	mov	[ebp].tv_offset,eax
	test	eax,eax
	jz	toend
	cmp	eax,DWORD PTR STDI.ios_fsize
	ja	fsize
	test	tvflag,_TV_HEXVIEW
	jnz	hexview
	mov	eax,[ebp].tv_static_count
	mov	eax,[ebp+eax*4].tv_static_table
	cmp	eax,[ebp].tv_offset
	jb	seek_back
	mov	eax,[ebp].tv_offset
	mov	ecx,[ebp].tv_static_count
	dec	ecx
lup:
	lea	edx,[ebp+ecx*4].tv_static_table
	cmp	eax,[edx]
	ja	@F
	test	ecx,ecx
	jz	return_0
	dec	ecx
	jmp	lup
@@:
	mov	eax,[edx]
	test	tvflag,_TV_WRAPLINES
	jz	toend
	mov	edx,[ebp].tv_loffs
	cmp	eax,edx
	ja	return_0
	sub	edx,eax
	cmp	edx,8000h
	jb	@F
	add	eax,edx
	sub	eax,_scrcol
@@:
	mov	[ebp].tv_offset,eax
	mov	[ebp].tv_tmp,eax
	call	seek_eax
	jz	toend
	push	edi
@@:
	mov	edi,[ebp].tv_screen
	call	parse_line
	jz	@F
	mov	eax,[ebp].tv_offset
	cmp	eax,[ebp].tv_loffs
	jae	@F
	mov	[ebp].tv_tmp,eax
	jmp	@B
@@:
	pop	edi
	mov	eax,[ebp].tv_tmp
	ret
seek_back:
	mov	eax,[ebp].tv_offset
	call	seek_eax
	jz	return_0
	call	oungetc
	jz	return_0
	dec	[ebp].tv_offset
	push	esi
	mov	esi,8000h
	cmp	al,13
	je	@01
	cmp	al,10
	jne	@02
@01:
	call	oungetc
	jz	return_0_esi
	dec	[ebp].tv_offset
@02:
	call	oungetc
	jz	return_0_esi
	dec	[ebp].tv_offset
	dec	esi
	jz	@F
	cmp	al,13
	je	@F
	cmp	al,10
	jne	@02
@@:
	mov	eax,[ebp].tv_offset
	inc	eax
	pop	esi
	ret
return_0_esi:
	pop	esi
return_0:
	xor	eax,eax
toend:
	ret
fsize:
	mov	eax,DWORD PTR STDI.ios_fsize
	mov	[ebp].tv_loffs,eax
	ret
hexview:
	cmp	eax,16
	jbe	return_0
	sub	eax,16
	ret
previous_line ENDP


tvread	PROC
	mov	[ebp].tv_scount,0
	.if	tvflag & _TV_HEXVIEW
		call	read_hex
	.elseif tvflag & _TV_WRAPLINES
		call	read_wrap
	.else
		call	read_text
	.endif
	ret
tvread	ENDP

reread	PROC
	call	tvread
	test	eax,eax
	jz	@F
	call	putscreen
	mov	eax,1
@@:
	ret
reread	ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

putscreenb PROC USES esi edi ebx y, row, lp
	local	bz:COORD
	local	rect:SMALL_RECT
	local	lbuf[TIMAXSCRLINE]:CHAR_INFO

	mov	esi,lp
	mov	ebx,row
	mov	eax,_scrcol
	mov	bz.x,ax
	mov	bz.y,1
	mov	rect.Left,0
	dec	eax
	mov	rect.Right,ax
	.repeat
		lea	edi,lbuf
		mov	ecx,_scrcol
		movzx	eax,at_background[B_TextView]
		or	al,at_foreground[F_TextView]
		shl	eax,16
		.repeat
			lodsb
			stosd
		.untilcxz
		mov	eax,y
		add	eax,row
		sub	eax,ebx
		mov	rect.Top,ax
		mov	rect.Bottom,ax
		.break .if !WriteConsoleOutput( hStdOutput, addr lbuf, bz, 0, addr rect )
		dec	ebx
	.until	ZERO?
	ret
putscreenb ENDP

putscreen PROC
	.if	tvflag & _TV_USEMLINE
		mov	eax,[ebp].tv_scount
		add	eax,[ebp].tv_loffs
		.if	ZERO?
			mov	eax,100
		.else
			mov	ecx,100
			mul	ecx
			mov	ecx,DWORD PTR STDI.ios_fsize
			div	ecx
			and	eax,007Fh
			.if	eax > 100
				mov	eax,100
			.endif
		.endif
		mov	edx,_scrcol
		sub	edx,5
		scputf( edx, 0, 0, 0, "%3d", eax )
		sub	edx,10
		scputf( edx, 0, 0, 0, "%-8d", [ebp].tv_curcol )
	.endif
	mov	eax,DWORD PTR STDI.ios_fsize
	.if	eax
		xor	eax,eax
		.if	tvflag & _TV_USEMLINE
			inc	eax
		.endif
		putscreenb( eax, [ebp].tv_rowcnt, [ebp].tv_screen )
	.endif
	ret
putscreen ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

event_HOME PROC
	sub	eax,eax
	mov	[ebp].tv_loffs,eax
	mov	[ebp].tv_curcol,eax
	jmp	reread
event_HOME ENDP

event_END PROC
	mov	ecx,DWORD PTR STDI.ios_fsize
	mov	edx,[ebp].tv_rowcnt
	test	tvflag,_TV_HEXVIEW
	jz	@F
	mov	eax,edx
	shl	eax,4
	inc	eax
	cmp	eax,ecx
	jae	toend
	sub	eax,ecx
	not	eax
	add	eax,18
	and	eax,-16
	mov	[ebp].tv_loffs,eax
	jmp	reread
@@:
	mov	eax,[ebp].tv_lcount
	cmp	eax,edx
	jb	toend
	mov	eax,[ebp].tv_scount
	add	eax,[ebp].tv_loffs
	inc	eax
	cmp	eax,ecx
	jae	toend
	mov	[ebp].tv_loffs,ecx
	jmp	event_PGUP_text
toend:
	ret
event_END ENDP

event_UP PROC
	call	previous_line
	cmp	eax,[ebp].tv_loffs
	je	@F
	mov	[ebp].tv_loffs,eax
	jmp	reread
@@:
	ret
event_UP ENDP

event_DOWN PROC
	test	tvflag,_TV_HEXVIEW
	jz	@F
	mov	eax,[ebp].tv_scount
	add	eax,[ebp].tv_loffs
	inc	eax
	cmp	eax,DWORD PTR STDI.ios_fsize
	jae	toend
	add	eax,15
	cmp	eax,DWORD PTR STDI.ios_fsize
	jae	event_END
	add	[ebp].tv_loffs,16
	jmp	reread
@@:
	mov	eax,[ebp].tv_lcount
	cmp	eax,[ebp].tv_rowcnt
	jb	toend
	mov	eax,[ebp+4].tv_line_table
	mov	[ebp].tv_loffs,eax
	jmp	reread
toend:
	xor	eax,eax
	ret
event_DOWN ENDP

event_MOUSEUP PROC
	call	event_UP
	call	event_UP
	call	event_UP
	ret
event_MOUSEUP ENDP

event_MOUSEDN PROC
	call	event_DOWN
	call	event_DOWN
	call	event_DOWN
	ret
event_MOUSEDN ENDP

event_PGUP PROC
	mov	cl,tvflag
	mov	eax,[ebp].tv_loffs
	test	eax,eax
	jz	@04
	test	cl,_TV_HEXVIEW
	jz	event_PGUP_text
	mov	eax,[ebp].tv_rowcnt
	shl	eax,4
	cmp	eax,[ebp].tv_loffs
	jnb	@F
	sub	[ebp].tv_loffs,eax
	jmp	@03
@@:
	xor	eax,eax
	mov	[ebp].tv_loffs,eax
@03:
	jmp	reread
@04:
	ret
event_PGUP ENDP

event_PGUP_text PROC
	push	edi
	mov	edi,1
	test	tvflag,_TV_WRAPLINES
	jnz	@wrap
@06:
	call	previous_line
	cmp	eax,[ebp].tv_loffs
	je	@08
	mov	[ebp].tv_loffs,eax
	inc	edi
	cmp	edi,[ebp].tv_rowcnt
	jnz	@06
@08:
	pop	edi
	jmp	reread
@wrap:
	cmp	eax,DWORD PTR STDI.ios_fsize
	jne	@06
	mov	edi,[ebp].tv_rowcnt
	dec	edi
@10:
	call	previous_line
	mov	[ebp].tv_loffs,eax
	dec	edi
	jnz	@10
	jmp	@08
event_PGUP_text ENDP

event_PGDN PROC
	mov	eax,[ebp].tv_scount
	add	eax,[ebp].tv_loffs
	inc	eax
	cmp	eax,DWORD PTR STDI.ios_fsize
	jnb	@03
	test	tvflag,_TV_HEXVIEW
	jz	@01
	mov	ebx,eax
	mov	eax,[ebp].tv_rowcnt
	shl	eax,4
	add	ebx,eax
	cmp	ebx,DWORD PTR STDI.ios_fsize
	jnc	@02
	add	[ebp].tv_loffs,eax
	jmp	reread
@01:
	mov	eax,[ebp].tv_lcount
	cmp	eax,[ebp].tv_rowcnt
	jne	@03
	dec	eax
	shl	eax,2
	lea	ebx,[ebp].tv_line_table
	add	ebx,eax
	mov	eax,[ebx]
	cmp	eax,DWORD PTR STDI.ios_fsize
	jnb	@02
	mov	[ebp].tv_loffs,eax
	jmp	reread
@02:
	jmp	event_END
@03:
	ret
event_PGDN ENDP

event_LEFT PROC
	test	tvflag,_TV_HEXVIEW or _TV_WRAPLINES
	jnz	@F
	mov	eax,[ebp].tv_curcol
	test	eax,eax
	jz	@F
	dec	[ebp].tv_curcol
	jmp	reread
@@:
	ret
event_LEFT ENDP

event_PGLEFT PROC
	test	tvflag,_TV_HEXVIEW or _TV_WRAPLINES
	jnz	toend
	xor	eax,eax
	or	eax,[ebp].tv_curcol
	jz	toend
	cmp	eax,_scrcol
	jb	@F
	sub	eax,_scrcol
	jmp	event_curcol
@@:
	xor	eax,eax
	jmp	event_curcol
toend:
	ret
event_PGLEFT ENDP

event_RIGHT PROC
	test	tvflag,_TV_HEXVIEW or _TV_WRAPLINES
	jnz	toend
	mov	eax,[ebp].tv_curcol
	cmp	eax,[ebp].tv_maxcol
	jae	toend
	inc	[ebp].tv_curcol
	jmp	reread
toend:
	ret
event_RIGHT ENDP

event_PGRIGHT PROC
	test	tvflag,_TV_HEXVIEW or _TV_WRAPLINES
	jnz	toend
	mov	edx,[ebp].tv_maxcol
	mov	eax,[ebp].tv_curcol
	cmp	eax,edx
	jae	toend
	add	eax,_scrcol
	cmp	eax,edx
	jbe	@F
	mov	eax,edx
@@:
	jmp	event_curcol
toend:
	ret
event_PGRIGHT ENDP

event_toend PROC
	test	tvflag,_TV_HEXVIEW or _TV_WRAPLINES
	jnz	toend
	mov	eax,[ebp].tv_maxcol
	cmp	eax,_scrcol
	jae	@F
toend:
	ret
@@:
	sub	eax,20
event_toend ENDP

event_curcol PROC
	mov	[ebp].tv_curcol,eax
	jmp	reread
event_curcol ENDP

event_tostart PROC
	xor	eax,eax
	jmp	event_curcol
event_tostart ENDP

event_togglemline PROC
	xor	tvflag,_TV_USEMLINE
	test	tvflag,_TV_USEMLINE
	jnz	@F
	dlhide( [ebp].tv_menusline )
	inc	[ebp].tv_rowcnt
	jmp	reread
@@:
	dlshow( [ebp].tv_menusline )
	dec	[ebp].tv_rowcnt
	jmp	reread
event_togglemline ENDP

event_togglesize PROC
	test	tvflag,_TV_USESLINE or _TV_USEMLINE
	jz	toggle
	test	tvflag,_TV_USEMLINE
	jz	@F
	call	event_togglemline
@@:
	test	tvflag,_TV_USESLINE
	jnz	toggle
	ret
toggle:
	call	event_togglemline
event_togglesize ENDP

event_togglesline PROC
	xor	tvflag,_TV_USESLINE
	test	tvflag,_TV_USESLINE
	jz	@F
	dlshow( [ebp].tv_statusline )
	dec	[ebp].S_TVIEW.tv_rowcnt
	jmp	reread
@@:
	dlhide( [ebp].tv_statusline )
	inc	[ebp].S_TVIEW.tv_rowcnt
	jmp	reread
event_togglesline ENDP

continuesearch PROC USES esi
	sub	esp,512
	mov	esi,esp
	xor	eax,eax
	cmp	searchstring,al
	je	toend
	wcpushst( esi, addr cp_stlsearch )
	mov	eax,_scrrow
	mov	edx,_scrcol
	sub	edx,24
	scputs( 24, eax, 0, edx, addr searchstring )
	mov	eax,[ebp].tv_loffs
	xor	edx,edx
	ioseek( addr STDI, edx::eax, SEEK_SET )
	jz	notfound
	call	osearch
	jz	notfound
	mov	[ebp].tv_loffs,eax
	mov	DWORD PTR STDI.ios_offset,eax
	mov	DWORD PTR STDI.ios_offset[4],edx
	mov	eax,1
	jmp	done
notfound:
	call	notfoundmsg
done:
	push	eax
	wcpopst( esi )
	pop	eax
toend:
	add	esp,512
	ret
continuesearch ENDP

event_search PROC
	call	continuesearch
	test	eax,eax
	jnz	event_tostart
	ret
event_search ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

cmsearch PROC
	and	STDI.ios_flag,not IO_SEARCHMASK
	mov	al,fsflag
	and	eax,IO_SEARCHMASK
	or	STDI.ios_flag,eax
	xor	eax,eax
	.if	DWORD PTR STDI.ios_fsize >= 16
		cmsearchidd( STDI.ios_flag )
		.if	!ZERO?
			mov	STDI.ios_flag,edx
			and	edx,IO_SEARCHCUR or IO_SEARCHSET
			push	edx
			call	continuesearch
			pop	edx
			or	STDI.ios_flag,edx
		.endif
	.endif
	push	eax
	and	fsflag,not IO_SEARCHMASK
	mov	eax,STDI.ios_flag
	and	STDI.ios_flag,not (IO_SEARCHSET or IO_SEARCHCUR)
	and	al,IO_SEARCHMASK
	or	fsflag,al
	pop	eax
	.if	eax
		call	reread
	.endif
	ret
cmsearch ENDP

cmseek_offset PROC
	mov	edx,[ebp].tv_loffs
	add	edx,[ebp].S_TVIEW.tv_curcol
	mov	[ebp].tv_curcol,0
	mov	eax,offset format_08Xh
	.if	!( tvflag & _TV_HEXOFFSET )
		mov	eax,offset format_lu
	.endif
	sprintf( [ebx+24], eax, edx )
	dlinit( ebx )
	ret
cmseek_offset ENDP

cmseek	PROC USES ebx
	.if	rsopen( IDD_TVSeek )
		mov	ebx,eax
		call	cmseek_offset
		rsevent( IDD_TVSeek, ebx )
		push	eax
		strtolx( [ebx+24] )
		dlclose( ebx )
		pop	eax
		.if	eax && edx <= DWORD PTR STDI.ios_fsize
			mov	[ebp].tv_loffs,edx
			call	reread
		.endif
	.endif
	xor	eax,eax
	ret
cmseek	ENDP

chexbuf PROC USES esi edi ebx off, len
	local	result

	mov	result,0
	mov	eax,len
	shr	eax,4
	add	eax,1
	mov	ecx,10+16*3+2+16+2
	mul	ecx
	inc	eax

	.if	malloc( eax )
		mov	edi,eax
		mov	result,eax

		.while	len

			sprintf( edi, "%08X  ", off )

			add	edi,eax
			mov	ebx,16
			add	off,ebx
			xor	esi,esi
			lea	edx,[edi+16*3+2]

			.while	ebx && esi < len
				.if	esi == 8
					strcpy( edi, "| " )
					add	edi,2
				.endif
				call	ogetc
				jz	toend
				push	eax
				sprintf(edi, "%02X", eax)
				add	edi,3
				mov	BYTE PTR [edi-1],' '
				pop	eax
				.if	eax < ' '
					mov	eax,'.'
				.endif
				sprintf(edx, "%c", eax)
				dec	ebx
				inc	edx
				inc	esi
			.endw
			sub	len,esi
			mov	eax,'    '
			.while	esi < 16
				.if	esi == 8
					stosw
				.endif
				stosw
				stosb
				inc	esi
			.endw
			mov	edi,edx
			mov	eax,0A0Dh
			stosw
		.endw
		mov	BYTE PTR [edi],0
		mov	edx,edi
		sub	edx,result
		inc	edx
	.endif
toend:
	mov	eax,result
	ret
chexbuf ENDP

cmcopy	PROC USES ebx edi
	.if	rsopen( IDD_TVCopy )
		mov	ebx,eax
		.if	UseClipboard
			or BYTE PTR [ebx+4*16],_O_FLAGB
		.endif
		cmseek_offset()
		.if	rsevent( IDD_TVCopy, ebx )
			mov	UseClipboard,0
			.if	BYTE PTR [ebx+4*16] & _O_FLAGB
				mov UseClipboard,1
			.endif
			.if	strtolx( [ebx+24] ) < DWORD PTR STDI.ios_fsize
				oseek( eax, SEEK_SET )
				.if	!ZERO?
					mov	edi,eax
					xor	eax,eax
					.if	UseClipboard != al
						.if	strtolx( [ebx+40] )
							mov	edx,eax
							.if	BYTE PTR [ebx+5*16] & _O_FLAGB
								chexbuf( edi, eax )
								mov	edi,eax
							.else
								oread()
								xor	edi,edi
							.endif
							.if	eax
								ClipboardCopy( eax, edx )
								ClipboardFree()
								free  ( edi )
								mov	eax,1
							.endif
						.endif
					.elseif ioinit( addr STDO, 8000h )
						.if	ogetouth( [ebx+56], M_WRONLY ) != -1
							mov	STDO.ios_file,eax
							strtolx([ebx+40])
							.if	BYTE PTR [ebx+5*16] & _O_FLAGB
								chexbuf(edi, eax)
								mov	edi,eax
								oswrite(STDO.ios_file, edi, edx)
								free(edi)
							.else
								xor	edx,edx
								iocopy( addr STDO, addr STDI, edx::eax )
								ioflush(addr STDO)
							.endif
							ioclose( addr STDO )
							mov	eax,1
						.else
							iofree( addr STDO )
							xor	eax,eax
						.endif
					.endif
				.endif
			.else
				xor	eax,eax
			.endif
		.endif
		dlclose( ebx )
		mov	eax,edx
	.endif
	test	eax,eax
	ret
cmcopy	ENDP

cmmcopy PROC USES esi edi ebx
	local	lb[128]:BYTE
	mov	edx,IDD_TVQuickMenu
	mov	eax,keybmouse_x
	mov	esi,eax
	mov	[edx+6],al
	mov	ebx,keybmouse_y
	mov	[edx+7],bl
	.if	rsmodal( edx )
		.if	eax != 1

			PushEvent( QuickMenuKeys[eax*4-8] )
		.else
			lea	edi,lb
			.while	esi < _scrcol
				getxyc( esi, ebx )
				stosb
				inc	esi
			.endw
			xor	eax,eax
			stosb
			lea	edi,lb
			.if	strtrim( edi )
				ClipboardCopy( edi, eax )
				call	ClipboardFree
				stdmsg( "Copy", "%s\n\nis copied to clipboard", edi )
			.endif
		.endif
	.endif
	ret
cmmcopy ENDP

update_dialog PROC USES edi ebx
	xor	ebx,ebx
	mov	edi,_scrrow
	mov	dl,tvflag
	.if	dl & _TV_USESLINE
		mov	bl,35
		mov	ecx,5
		mov	eax,offset cp_hex
		.if	dl & _TV_HEXVIEW
			mov	eax,offset cp_ascii
		.endif
		scputs( ebx, edi, 0, ecx, eax )
		mov	bl,13
		inc	cl
		mov	eax,offset cp_unwrap
		.if	dl & _TV_WRAPLINES
			mov	eax,offset cp_wrap
		.endif
		scputs( ebx, edi, 0, ecx, eax )
		mov	bl,54
		mov	cl,3
		mov	eax,offset cp_deci
		.if	dl & _TV_HEXOFFSET
			mov	eax,offset cp_hex
		.endif
		scputs( ebx, edi, 0, ecx, eax )
	.endif
	ret
update_dialog ENDP

update_reread PROC
	call	update_dialog
	jmp	reread
update_reread ENDP

if_fsize PROC
	mov	eax,DWORD PTR STDI.ios_fsize
	test	eax,eax
	jnz	@F
	add	esp,4
@@:
	ret
if_fsize ENDP

cmwrap	PROC
	call	if_fsize
	test	tvflag,_TV_HEXVIEW
	jnz	@F
	xor	tvflag,_TV_WRAPLINES
	jmp	update_reread
@@:
	xor	eax,eax
	ret
cmwrap	ENDP

cmoffset PROC
	call	if_fsize
	xor	tvflag,_TV_HEXOFFSET
	jmp	update_reread
cmoffset ENDP

cmhex	PROC
	call	if_fsize
	mov	al,tvflag
	mov	ah,al
	and	al,not _TV_HEXVIEW
	test	ah,_TV_HEXVIEW
	jnz	@F
	or	al,_TV_HEXVIEW
@@:
	mov	tvflag,al
	and	al,_TV_HEXVIEW
	jnz	@F
	mov	eax,[ebp].tv_curcol
	cmp	eax,[ebp].tv_loffs
	ja	toend
	sub	[ebp].tv_loffs,eax
	jmp	update_reread
@@:
	mov	eax,[ebp].tv_curcol
	add	[ebp].tv_loffs,eax
	xor	eax,eax
	mov	[ebp].tv_curcol,eax
toend:
	jmp	update_reread
cmhex	ENDP

cmquit	PROC
	mov	eax,1
	mov	[ebp].tv_switch,eax
	dec	eax
	ret
cmquit	ENDP

cmconsole PROC
	dlhide( [ebp].tv_dialog )
	.while	!getkey()
	.endw
	dlshow( [ebp].tv_dialog )
	ret
cmconsole ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

mouse_scroll PROC
	xor	ecx,ecx
	cmp	edx,8
	jb	@07
	cmp	edx,edi
	ja	@06
	mov	ebx,esi
	sub	ebx,9
	cmp	eax,ebx
	jb	@05
	add	ebx,9+10
	cmp	eax,ebx
	ja	@04
	cmp	edx,12
	jnz	@01
	cmp	eax,esi
	ja	@04
	jmp	@05
@01:	cmp	edx,11
	jb	@02
	cmp	edx,13
	ja	@02
	mov	ebx,esi
	sub	ebx,4
	cmp	eax,ebx
	jb	@05
	add	ebx,4+5
	cmp	eax,45
	ja	@04
@02:	cmp	edx,12
	jb	@07
	ja	@06
@03:	ret
@04:	inc	ecx
@05:	inc	ecx
@06:	inc	ecx
@07:	inc	ecx
	push	ecx
	mov	ebx,esi
	sub	ebx,3
	cmp	eax,ebx
	jb	@09
	add	ebx,3+3
	cmp	eax,ebx
	jb	@08
	mov	ecx,_scrcol
	dec	ecx
	sub	ecx,eax
	mov	eax,ecx
	jmp	@09
@08:	xor	eax,eax
@09:	shl	eax,2
	cmp	edx,12
	je	@10
	jb	@11
	mov	ecx,_scrrow
	sub	ecx,edx
	mov	edx,ecx
	jmp	@11
@10:	xor	edx,edx
@11:	shl	edx,2
	pop	ecx
	ret
mouse_scroll ENDP

mouse_scroll_proc PROC USES esi edi ebx
	mov	esi,_scrcol
	mov	edi,_scrrow
	inc	edi
	shr	esi,1
	shr	edi,1
	call	mousey
	push	eax
	call	mousex
	pop	edx
	call	mouse_scroll
	ret
mouse_scroll_proc ENDP

mouse_scroll_up PROC
	mov	eax,KEY_UP
	jmp	mouse_scroll_updn
mouse_scroll_up ENDP

mouse_scroll_down PROC
	mov	eax,KEY_DOWN
mouse_scroll_down ENDP

mouse_scroll_updn PROC
	push	edx
	jmp	mouse_scroll_event
mouse_scroll_updn ENDP

mouse_scroll_left PROC
	push	eax
	mov	eax,KEY_LEFT
	jmp	mouse_scroll_event
mouse_scroll_left ENDP

mouse_scroll_right PROC
	push	eax
	mov	eax,KEY_RIGHT
mouse_scroll_right ENDP

mouse_scroll_event PROC
	call	tview_event
	pop	eax
	mov	edi,eax
mouse_scroll_event ENDP

mouse_scroll_delay PROC
	.if edi
		delay( edi )
	.endif
	ret
mouse_scroll_delay ENDP

scroll	PROC USES edi
	xor	edi,edi
	call	mouse_scroll_proc
	call	label_scroll[ecx*4]
	ret
scroll	ENDP

tvhelp	PROC
	rsmodal( IDD_TVHelp )
	ret
tvhelp	ENDP

mouse_event PROC
	call	mousep
	jz	@07
	cmp	eax,2
	je	@09
	call	mousex
	mov	[ebp].tv_xpos,eax
	call	mousey
	mov	[ebp].tv_ypos,eax
	inc	eax
	cmp	al,rsrows
	jne	@08
	test	tvflag,_TV_USESLINE
	jz	@08
	call	msloop
	mov	eax,[ebp].tv_xpos
	cmp	al,9
	jnb	@00
	jmp	tvhelp
@00:	je	@07
	cmp	al,20
	jnb	@01
	jmp	cmwrap
@01:	jz	@07
	cmp	al,31
	jnb	@02
	jmp	cmsearch
@02:	je	@07
	cmp	al,41
	jnb	@03
	jmp	cmhex
@03:	je	@07
	cmp	al,50
	jnb	@04
	jmp	cmcopy
@04:	je	@07
	cmp	al,58
	jnb	@05
	jmp	cmoffset
@05:	je	@07
	cmp	al,66
	jnbe	@06
	jmp	cmseek
@06:	cmp	al,70
	jbe	@07
	call	cmquit
@07:	xor	eax,eax
	ret
@08:	call	mousep
	cmp	eax,1
	jne	@07
	call	scroll
	jmp	@08
@09:	call	cmmcopy
	call	msloop
	ret
mouse_event ENDP

tview_event PROC
	xor	edx,edx
	mov	ecx,local_count
	.if	edx == DWORD PTR STDI.ios_fsize

		mov	ecx,global_count
	.endif
	.repeat
		.if eax == key_global[edx]

			jmp key_global[edx+4]
		.endif
		add	edx,8
	.untilcxz
	ret
tview_event ENDP

tview_update PROC
	xor	eax,eax
	ret
tview_update ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	OPTION	PROC: PUBLIC

tview PROC USES esi edi ebx filename, offs

	alloca( sizeof(S_TVIEW) )
	mov	ebx,offs
	mov	edx,filename
	push	ebp
	mov	ebp,eax
	mov	[ebp].tv_offset,ebx
	mov	[ebp].tv_filename,edx

	mov	STDI.ios_flag,0
	mov	eax,_scrcol
	mov	Statusline_C0,al
	mov	Menusline_C0,al
	mov	Menusline_C1,al
	mov	Menusline_C2,al
	mov	Statusline_C1,6
	mov	Statusline_C2,1
	sub	al,80
	add	Statusline_C1,al
	add	Statusline_C2,al
	mov	esi,STDI.ios_flag
	lea	edi,[ebp+8]
	xor	eax,eax
	mov	ecx,SIZE S_TVIEW - 8
	rep	stosb
	mov	[ebp].tv_loffs,ebx
	mov	eax,_scrrow
	mov	ebx,IDD_Statusline
	mov	[ebx+7],al
	inc	al
	mov	rsrows,al
	.if	tvflag & _TV_USEMLINE
		dec	al
	.endif
	.if	tvflag & _TV_USESLINE
		dec	al
	.endif
	mov	[ebp].tv_rowcnt,eax		; adapt to current screen size
	add	eax,2
	mul	_scrcol
	.if	malloc( eax )
		mov	[ebp].tv_screen,eax
		.if	!( esi & IO_MEMBUF )
			mov	ebx,[ebp].tv_offset
			.if	ioopen( addr STDI, [ebp].tv_filename, M_RDONLY, OO_MEMBUF ) != -1
				xor	eax,eax
				.if	eax != dword ptr STDI.ios_fsize[4]
					mov	DWORD PTR STDI.ios_fsize[4],eax
					sub	eax,2
					mov	DWORD PTR STDI.ios_fsize,eax
				.endif
				mov	[ebp].tv_loffs,ebx
				.if	!( STDI.ios_flag & IO_MEMBUF )
					mov	eax,8000h
					mov	STDI.ios_c,eax
					mov	STDI.ios_size,eax
				.endif
			.else
				free  ( [ebp].tv_screen )
				xor	eax,eax
				jmp	toend
			.endif
		.endif
		mov	al,at_background[B_TextView]
		or	al,at_foreground[F_TextView]
		.if	dlscreen( addr DLG_Textview, eax )
			mov	[ebp].tv_dialog,eax
			dlshow( eax )
			rsopen( IDD_Menusline )
			mov	[ebp].tv_menusline,eax
			dlshow( eax )
			rsopen( IDD_Statusline )
			mov	[ebp].tv_statusline,eax
			.if	tvflag & _TV_USESLINE
				dlshow( eax )
			.endif
			scpath( 1, 0, 41, [ebp].tv_filename )
			mov	eax,_scrcol
			sub	eax,38
			mov		edx,DWORD PTR STDI.ios_fsize
			scputf( eax, 0, 0, 0, "%12u byte", edx )
			mov	edx,_scrcol
			sub	edx,5
			scputs( edx, 0, 0, 0, "100%" )
			sub	edx,14
			scputs ( edx, 0, 0, 0, "col" )
			.if	!( tvflag & _TV_USEMLINE )
				dlhide( [ebp].tv_menusline )
			.endif
			GetCursor( addr [ebp].tv_cursor )
			_gotoxy( 0, 1 )
			call	CursorOff
			push	tupdate
			mov	tupdate,tview_update
			call	update_dialog
			call	msloop
			call	read_static_table
			call	reread
			.while	[ebp].tv_switch == 0
				.if	tgetevent() == MOUSECMD
					call	mouse_event
					call	msloop
				.else
					call	tview_event
				.endif
			.endw
			ioclose( addr STDI )
			free   ( [ebp].tv_screen )
			dlclose( [ebp].tv_statusline )
			dlclose( [ebp].tv_menusline )
			dlclose( [ebp].tv_dialog )
			SetCursor( addr [ebp].tv_cursor )
			pop	eax
			mov	tupdate,eax
			xor	eax,eax
			mov	STDI.ios_flag,eax
		.else
			free  ( [ebp].tv_screen )
			_close( STDI.ios_file )
			mov	eax,1
		.endif
	.endif
toend:
	pop	ebp
	mov	esp,ebp
	ret
tview ENDP

	END
