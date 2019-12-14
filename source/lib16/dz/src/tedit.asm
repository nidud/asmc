; TEDIT.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include dos.inc
include alloc.inc
include string.inc
include stdio.inc
include stdlib.inc
include io.inc
include ini.inc
include iost.inc
include wsub.inc
include clip.inc
include conio.inc
include tinfo.inc
include keyb.inc
include mouse.inc
include ctype.inc
include helpid.inc
ifdef __TE__

ifndef __DZ__
externdef	IDD_TEHelp:DWORD
endif
externdef	IDD_TEReload:DWORD
externdef	IDD_TEReload2:DWORD
externdef	IDD_TESave:DWORD
externdef	IDD_TEOpenFiles:DWORD
externdef	IDD_TESeek:DWORD
externdef	IDD_Replace:DWORD
externdef	IDD_ReplacePrompt:DWORD

externdef	CP_ENOMEM:BYTE
externdef	format_u:BYTE
externdef	cp_linetolong:BYTE

ticurcp		PROTO
ticurlp		PROTO
tiseto		PROTO
tiputs		PROTO
ticontinue	PROTO
tihome		PROTO
tidown		PROTO
tialignx	PROTO
tialigny	PROTO
tinocando	PROTO
tireadstyle	PROTO pascal
tihome		PROTO
tiputc		PROTO
titoend		PROTO
tievent		PROTO
tiprevword	PROTO
tinextword	PROTO
tidoiflines	PROTO
tiretevent	PROTO

ifdef __DZ__
view_readme	PROTO _CType
endif

ifdef __CLIP__

tigetline	PROTO
tiremline	PROTO
tidelete	PROTO
tiflushl	PROTO

externdef IDD_ClipboardWarning:DWORD

.code

;
; Cut		Shift-Del	Ctrl-X
; Copy		Ctrl-Ins	Ctrl-C
; Paste		Shift-Ins	Ctrl-V
; Clear		Del		Ctrl-Del
;

tiselected PROC PUBLIC USES bx
	mov	bx,tinfo
    ifdef __TE__
	mov	ax,[bx].S_TINFO.ti_clel ; CX line count
	sub	ax,[bx].S_TINFO.ti_clsl
	mov	cx,ax
	jnz	@F
    endif
	mov	ax,[bx].S_TINFO.ti_cleo ; AX byte count
	sub	ax,[bx].S_TINFO.ti_clso
      @@:
	ret
tiselected ENDP

ticlipset PROC PUBLIC USES bx	; set clipboard to current position
	mov	bx,tinfo
	mov	ax,[bx].S_TINFO.ti_boff
	add	ax,[bx].S_TINFO.ti_xoff
	mov	[bx].S_TINFO.ti_clso,ax
	mov	[bx].S_TINFO.ti_cleo,ax
    ifdef __TE__
	test	[bx].S_TINFO.ti_flag,_T_LINEBUF
	jz	@F
	mov	ax,[bx].S_TINFO.ti_loff
	add	ax,[bx].S_TINFO.ti_yoff
	mov	[bx].S_TINFO.ti_clsl,ax
	mov	[bx].S_TINFO.ti_clel,ax
      @@:
    endif
	ret
ticlipset ENDP

alignxy:
	test	cx,cx		; subtract ax then dx while cx--
	je	alignxy_end
	cmp	ax,cx
	jb	alignxy_00
	sub	ax,cx
    alignxy_end:
	ret
    alignxy_00:
	sub	cx,ax
	xor	ax,ax
	sub	dx,cx
	ret

tialigncl:
	push	bx		; goto start of selection
	mov	bx,tinfo
    ifdef __TE__
	test	[bx].S_TINFO.ti_flag,_T_LINEBUF
	jz	@F
	mov	dx,[bx].S_TINFO.ti_loff
	mov	ax,[bx].S_TINFO.ti_yoff
	mov	cx,dx
	add	cx,ax
	sub	cx,[bx].S_TINFO.ti_clsl
	call	alignxy
	mov	[bx].S_TINFO.ti_loff,dx
	mov	[bx].S_TINFO.ti_yoff,ax
      @@:
    endif
	mov	dx,[bx].S_TINFO.ti_boff
	mov	ax,[bx].S_TINFO.ti_xoff
	mov	cx,dx
	add	cx,ax
	sub	cx,[bx].S_TINFO.ti_clso
	call	alignxy
	mov	[bx].S_TINFO.ti_boff,dx
	mov	[bx].S_TINFO.ti_xoff,ax
	pop	bx
	ret

ifdef __TE__

tiremline PROC PUBLIC USES si di bx bp
	mov	bx,ax		; AX index of line to remove
	mov	bp,tinfo	; DX number of lines to remove
	mov	cx,[bp].S_TEDIT.ti_lcnt
	mov	ax,[bp].S_TINFO.ti_bcol
	sub	sp,ax
	mov	bp,sp
	push	ax		; [bp-2] line size
	mov	ax,dx
	sub	cx,bx
	push	cx		; [bp-4] max lines
	add	dx,bx
	push	dx		; [bp-6] last line
	push	ax		; [bp-8] count
      @@:
	mov	ax,[bp-6]
	call	tigetline
	jc	@F
	mov	ds,dx
	mov	si,ax
	mov	cx,[bp-2]
	shr	cx,1
	push	ss
	pop	es
	mov	di,bp
	rep	movsw
	push	ss
	pop	ds
	mov	ax,bx
	call	tigetline
	jc	tiremlines_err
	mov	es,dx
	mov	di,ax
	mov	cx,[bp-2]
	shr	cx,1
	mov	si,bp
	rep	movsw
	inc	bx
	inc	WORD PTR [bp-6]
	dec	WORD PTR [bp-4]
	jnz	@B
      @@:
	mov	bx,[bp-8]
	mov	si,tinfo
      @@:
	mov	ax,[si].S_TEDIT.ti_lcnt
	dec	ax
	call	tigetline
	jz	tiremlines_end
	mov	es,dx
	mov	di,ax
	xor	ax,ax
	mov	cx,[bp-2]
	shr	cx,1
	rep	stosw
	dec	[si].S_TEDIT.ti_lcnt
	dec	bx
	jnz	@B
	inc	ax
    tiremlines_end:
	add	sp,[bp-2]
	add	sp,8
	or	ax,ax
	ret
    tiremlines_err:
	xor	ax,ax
	jmp	tiremlines_end
tiremline ENDP

endif

ticlipdel PROC PUBLIC USES si di bx
	invoke	tiselected
  ifdef __TE__
	mov	di,cx		; DI line count selected
	jz	ticlipdel_end
	call	tialigncl	; goto start
	mov	bx,tinfo
	mov	ax,[bx].S_TINFO.ti_clsl
	call	tigetline	; get line
	jz	ticlipdel_end
	test	di,di
	jnz	@F
	or	[bx].S_TINFO.ti_flag,_T_MODIFIED
	mov	cx,ax
	add	ax,[bx].S_TINFO.ti_clso
	add	cx,[bx].S_TINFO.ti_cleo
	invoke	strcpy,dx::ax,dx::cx
	jmp	ticlipdel_set
      @@:
	mov	es,dx		; multi line
	mov	si,ax
	sub	ax,ax
	add	si,[bx].S_TINFO.ti_clso
	mov	es:[si],al	; start=0
	mov	ax,[bx].S_TINFO.ti_clel
	call	tigetline	; get last selected line
	jz	ticlipdel_end
	or	[bx].S_TINFO.ti_flag,_T_MODIFIED
	mov	cx,ax
	add	cx,[bx].S_TINFO.ti_cleo
	invoke	strcpy,dx::ax,dx::cx
	dec	di
	jz	ticlipdel_del
	mov	si,[bx].S_TINFO.ti_clsl
	inc	si
    ticlipdel_lines:
	mov	ax,si
	mov	dx,di
	call	tiremline
    ticlipdel_del:
	call	tidelete
  else	; __TE__
	jz	ticlipdel_end
	mov	bx,tinfo
	lodm	[bx].S_TINFO.ti_bp
	mov	si,ax
	mov	di,[bx].S_TINFO.ti_cleo
	add	ax,[bx].S_TINFO.ti_clso
	mov	cx,si
	add	cx,di
	invoke	strcpy,dx::ax,dx::cx
	mov	dx,si
	add	dx,di
	sub	dx,ax
	mov	cx,si
	add	cx,[bx].S_TINFO.ti_boff
	add	cx,[bx].S_TINFO.ti_xoff
	cmp	ax,cx
	je	ticlipdel_set
	sub	[bx].S_TINFO.ti_xoff,dx
  endif
    ticlipdel_set:
	call	tiseto
	call	ticlipset
	sub	ax,ax
	inc	ax
    ticlipdel_end:
	ret
ticlipdel ENDP

ifdef __TE__

tiselectall PROC PUBLIC
	push	bx
	mov	bx,tinfo
	xor	ax,ax
	mov	[bx].S_TINFO.ti_clsl,ax
	mov	[bx].S_TINFO.ti_clso,ax
	mov	[bx].S_TINFO.ti_clel,ax
	mov	ax,[bx].S_TINFO.ti_bcol
	mov	[bx].S_TINFO.ti_cleo,ax
	cmp	[bx].S_TEDIT.ti_lcnt,ax
	je	@F
	mov	ax,[bx].S_TEDIT.ti_lcnt
	dec	ax
	mov	[bx].S_TINFO.ti_clel,ax
      @@:
	pop	bx
	jmp	ticontinue
tiselectall ENDP

endif

ifdef	__TE__
ticopyselection:
	push	di
	push	bx
	xor	di,di
	invoke	oinitst,addr STDO,MAXCLIPSIZE
	jnz	@F
	invoke	oinitst,addr STDO,1000h
	jz	ticopyselection_eof
      @@:
	inc	di
	mov	STDO.ios_flag,IO_CLIPBOARD
	mov	ax,[si].S_TINFO.ti_clsl
	mov	dx,[si].S_TINFO.ti_clso
	mov	cx,[si].S_TINFO.ti_clel
	mov	bx,[si].S_TINFO.ti_cleo
	call	tiflushl
	jnz	@F
	mov	ax,bx
	mov	[si].S_TINFO.ti_clsl,dx
	mov	[si].S_TINFO.ti_clso,ax
	inc	di
	invoke	rsmodal,IDD_ClipboardWarning
      @@:
	call	oflush
	invoke	ofreest,addr STDO
    ticopyselection_eof:
	mov	ax,di
	test	ax,ax
	pop	bx
	pop	di
	ret
endif

ticlipcut PROC PRIVATE USES si di
	mov	si,tinfo
	mov	di,ax			; AX: Copy == 0, Cut == 1
	call	tiselected		; get size of selection
	jz	ticlipcut_set
    ifdef __TE__
	call	ticopyselection
	jz	ticlipcut_eof
	dec	ax
	jnz	ticlipcut_eof
    else
	mov	cx,ax
	lodm	[si].S_TINFO.ti_bp
	add	ax,[si].S_TINFO.ti_clso
	invoke	ClipboardCopy,dx::ax,cx
    endif
	test	di,di
	jz	ticlipcut_set
	call	ticlipdel
    ticlipcut_set:
	call	ticlipset
    ticlipcut_eof:
	sub	ax,ax
	ret
ticlipcut ENDP

ticlipget PROC PRIVATE USES si di bx
	mov	si,tinfo
	mov	ax,[si].S_TINFO.ti_flag
	and	ax,_T_OVERWRITE
	jnz	@F
	call	ticlipset
	jmp	ticlipget_get
      @@:
	call	ticlipdel
    ticlipget_get:
	call	ClipboardPaste
	jz	ticlipget_end
  ifdef __TE__
	push	[si].S_TINFO.ti_yoff
	push	[si].S_TINFO.ti_loff
  endif
	push	[si].S_TINFO.ti_xoff
	push	[si].S_TINFO.ti_boff
	mov	si,clipbsize
	mov	di,ax
	mov	es,dx
  ifdef __TE__
	mov	dx,ax		; Problem of inserting text by pushing
	mov	cx,si		; a long line in front - EOL == abort
	cld?
	mov	ax,0Ah		; Insert '\n' if clipboard contain a '\n'
	repne	scasb		; then move back to prev pos
	mov	di,dx
	jne	ticlipget_00
	mov	bx,si
	cmp	es:[di+bx-2],al ; remove '\n' from end if exist
	jne	@F		; This align line-based clip-set
	mov	es:[di+bx-2],ah
      @@:
	push	es
	call	tiputc
	pop	es
	test	ax,ax
	jnz	ticlipget_01
	pop	dx
	pop	ax
	pop	cx
	pop	bx
	push	bx
	push	cx
	push	ax
	push	dx
	mov	si,tinfo
	mov	[si].S_TINFO.ti_xoff,ax
	mov	[si].S_TINFO.ti_boff,dx
	mov	[si].S_TINFO.ti_yoff,cx
	mov	[si].S_TINFO.ti_loff,bx
	mov	si,clipbsize
  endif
    ticlipget_00:
	mov	al,es:[di]
	test	al,al
	jz	ticlipget_01
	inc	di
	push	es
	call	tiputc
	pop	es
	test	ax,ax
	jnz	ticlipget_01
	dec	si
	jnz	ticlipget_00
    ticlipget_01:
	pop	dx
	pop	ax
	mov	si,tinfo
	mov	[si].S_TINFO.ti_xoff,ax
	mov	[si].S_TINFO.ti_boff,dx
  ifdef __TE__
	pop	dx
	pop	ax
	mov	[si].S_TINFO.ti_yoff,ax
	mov	[si].S_TINFO.ti_loff,dx
  endif
    ticlipget_end:
	xor	ax,ax
	ret
ticlipget ENDP

	.data
	cl_proctable label WORD
		dw ticlip_Copy
		dw ticlip_Copy
		dw ticlipget
		dw ticlip_Cut
		dw ticlip_Cut
	cl_keytable label WORD
		dw KEY_CTRLINS
		dw KEY_CTRLC
		dw KEY_CTRLV
		dw KEY_CTRLX
		dw KEY_CTRLDEL
	cl_keycount = (($ - offset cl_keytable) / 2)
	cl_shiftkeytable label WORD
		dw KEY_HOME
		dw KEY_LEFT
		dw KEY_RIGHT
		dw KEY_END
	    ifdef __TE__
		dw KEY_UP
		dw KEY_DOWN
		dw KEY_PGUP
		dw KEY_PGDN
	    endif
	cl_shiftkeycount = (($ - offset cl_shiftkeytable) / 2)
	cl_nodeletekeys label size_t
		dw KEY_ESC
	    ifdef __MOUSE__
		dw MOUSECMD
	    endif
		dw KEY_BKSP
		dw KEY_ENTER
		dw KEY_KPENTER
	cl_nodeletecount = (($ - offset cl_nodeletekeys) / 2)

	.code

ticlip_Copy:
	sub	ax,ax
	jmp	ticlipcut

ticlip_Cut:
	mov	ax,1
	jmp	ticlipcut

ticlipevent PROC PUBLIC USES si di bx
	mov	si,ax
	call	tiselected
	jnz	@F
	call	ticlipset
      @@:
	xor	di,di
	mov	cx,cl_keycount
	jmp	ticlipevent_loop
    ticlipevent_found:
	call	cl_proctable[di]
	jmp	ticlipevent_end
    ticlipevent_loop:
	cmp	si,cl_keytable[di]
	je	ticlipevent_found
	add	di,size_l
	dec	cx
	jnz	ticlipevent_loop
	les	bx,keyshift
	mov	al,es:[bx]
	and	al,KEY_SHIFT
	jnz	@F
	cmp	si,KEY_DEL
	jne	ticlipevent_ESC
	call	ticlipdel
	jz	ticlipevent_set
	xor	ax,ax
	jmp	ticlipevent_end
      @@:
	cmp	si,KEY_INS
	jne	@F
	call	ticlipget
	jmp	ticlipevent_end
      @@:
	cmp	si,KEY_DEL
	jne	@F
	mov	ax,1
	call	ticlipcut
	jmp	ticlipevent_end
      @@:
	mov	di,offset cl_shiftkeytable
	mov	cx,cl_shiftkeycount
  ifdef __TE__
	mov	bx,tinfo
	test	[bx].S_TINFO.ti_flag,_T_LINEBUF
	jnz	@F
	sub	cx,4
  endif
      @@:
	cmp	si,[di]
	je	ticlipevent_MOVE
	add	di,size_l
	dec	cx
	jnz	@B
    ticlipevent_ESC:
	mov	cx,cl_nodeletecount
	xor	di,di
      @@:
	cmp	si,cl_nodeletekeys[di]
	je	ticlipevent_set
	add	di,size_l
	dec	cx
	jnz	@B
	mov	ax,si
	test	al,al
	jz	ticlipevent_set
    ifdef __TE__
	mov	bx,tinfo
	test	[bx].S_TINFO.ti_flag,_T_LINEBUF
	jnz	@F
	cmp	si,KEY_TAB
	je	ticlipevent_set
      @@:
    endif
	call	ticlipdel
    ticlipevent_set:
	call	ticlipset
	mov	ax,si
    ticlipevent_end:
	ret
    ticlipevent_MOVE:
	mov	ax,si
	call	tievent
	test	ax,ax
	jnz	ticlipevent_nul
	mov	bx,tinfo
    ifdef __TE__
	mov	cx,[bx].S_TINFO.ti_loff
	add	cx,[bx].S_TINFO.ti_yoff
	cmp	cx,[bx].S_TINFO.ti_clsl
	jb	ticlipevent_MOVEBACK
    endif
	mov	ax,[bx].S_TINFO.ti_boff
	add	ax,[bx].S_TINFO.ti_xoff
	cmp	ax,[bx].S_TINFO.ti_clso
	jb	ticlipevent_MOVEBACK
	cmp	si,KEY_RIGHT
	jne	@F
	mov	dx,ax
	dec	dx
	cmp	dx,[bx].S_TINFO.ti_clso
	jne	@F
	cmp	dx,[bx].S_TINFO.ti_cleo
	jne	ticlipevent_MOVEBACK
      @@:
	mov	[bx].S_TINFO.ti_cleo,ax
    ifdef __TE__
	mov	[bx].S_TINFO.ti_clel,cx
    endif
	jmp	ticlipevent_nul
    ticlipevent_MOVEBACK:
	mov	[bx].S_TINFO.ti_clso,ax
    ifdef __TE__
	mov	[bx].S_TINFO.ti_clsl,cx
    endif
    ticlipevent_nul:
	xor	ax,ax
	jmp	ticlipevent_end
ticlipevent ENDP

endif ; __CLIP__

ifdef __TE__
tienter		PROTO
tienterni	PROTO
tigetline	PROTO		; AX line
tiexpand	PROTO
tistrip		PROTO
tistripl	PROTO
tistripline	PROTO
tiremline	PROTO
tistyle		PROTO pascal
endif
	.data

ti_keytable label size_t
	dw _TI_CONTINUE
	dw KEY_ESC
	dw KEY_LEFT
	dw KEY_RIGHT
	dw KEY_HOME
	dw KEY_END
	dw KEY_BKSP
	dw KEY_TAB
	dw KEY_DEL
	dw MOUSECMD
	dw KEY_CTRLRIGHT
	dw KEY_CTRLLEFT
	dw KEY_ENTER
	dw KEY_KPENTER
	dw KEY_UP
	dw KEY_DOWN
ifdef __TE__
	dw KEY_PGUP
	dw KEY_PGDN
	dw KEY_CTRLPGUP
	dw KEY_CTRLPGDN
	dw KEY_CTRLHOME
	dw KEY_CTRLEND
	dw KEY_CTRLUP	; Scroll up one line
	dw KEY_CTRLDN	; Scroll down one line
endif

ti_proctab label size_t
	dw ticontinue
	dw tiesc
	dw tileft
	dw tiright
	dw tihome
	dw titoend
	dw tibacksp
	dw titab
	dw tidelete
	dw timouse
	dw tinextword
	dw tiprevword
  ifdef __TE__
	dw tienter
	dw tienter
	dw tiup
	dw tidown
	dw tipgup
	dw tipgdn
	dw tictrlhome
	dw tictrlend
	dw tictrlpgup
	dw tictrlpgdn
	dw tiscrollup
	dw tiscrolldn
  else
	dw tiesc
	dw tiesc
	dw tiesc
	dw tiesc
  endif

ti_key_count = (($ - offset ti_proctab) / size_l)

	cp_linetolong db 'Line too long, was truncated',0
PUBLIC	cp_linetolong

	.code

tinocando PROC PUBLIC
	invoke	beep,9,1
	mov	ax,_TI_CMFAILED ; end of line/buffer
	ret
tinocando ENDP

ticurlp PROC PUBLIC USES bx
	mov	bx,tinfo
    ifdef __TE__
	mov	ax,[bx].S_TINFO.ti_loff ; this return ZF set if NULL
	add	ax,[bx].S_TINFO.ti_yoff
	call	tigetline
	jz	@F
	call	tistrlen
	test	dx,dx
      @@:
    else
	lodm	[bx].S_TINFO.ti_bp
    endif
	ret
ticurlp ENDP

ticurcp PROC PUBLIC USES bx
	mov	bx,tinfo
	call	ticurlp
	add	ax,[bx].S_TINFO.ti_boff ; no ZF flag if __TE__
	add	ax,[bx].S_TINFO.ti_xoff
	ret
ticurcp ENDP

ticontinue PROC PUBLIC
	sub ax,ax
	ret
ticontinue ENDP

tiretevent PROC PUBLIC
	mov ax,_TI_RETEVENT
	ret
tiretevent ENDP

tiesc PROC PRIVATE
	jmp tiretevent
tiesc ENDP

tileft PROC PRIVATE USES bx
	mov bx,tinfo
	sub ax,ax
	.if ax == [bx].S_TINFO.ti_xoff
	    .if ax == [bx].S_TINFO.ti_boff
		mov ax,_TI_CMFAILED
	    .else
		dec [bx].S_TINFO.ti_boff
	    .endif
	.else
	    dec [bx].S_TINFO.ti_xoff
	.endif
	ret
tileft	ENDP

tiincvalue PROC pascal PRIVATE USES si di dx boff:DWORD, soff:DWORD,
	bmax:size_t, smax:size_t
	mov si,WORD PTR boff
	mov di,WORD PTR soff
	mov ax,[si]
	add ax,[di]
	inc ax
	.if ax >= bmax
	    sub ax,ax
	.else
	    mov dx,[si]
	    mov ax,[di]
	    inc ax
	    .if ax >= smax
		mov ax,smax
		dec ax
		inc dx
	    .endif
	    mov [di],ax
	    mov [si],dx
	.endif
	ret
tiincvalue ENDP

tiincx PROC PRIVATE USES bx ax
	mov bx,tinfo
	invoke tiincvalue,addr [bx].S_TINFO.ti_boff,addr [bx].S_TINFO.ti_xoff,
		[bx].S_TINFO.ti_bcol,[bx].S_TINFO.ti_cols
	ret
tiincx ENDP

tiright PROC PRIVATE USES di bx
	mov	bx,tinfo
    ifdef __TE__
	test	[bx].S_TINFO.ti_flag,_T_LINEBUF
	jz	@F
	call	tiincx
	jmp	tiright_ok
      @@:
    endif
	call	ticurcp
	mov	es,dx
	mov	di,ax
	mov	al,es:[di]
	sub	di,[bx].S_TINFO.ti_xoff
	test	al,al
	jz	tiright_00
	mov	ax,[bx].S_TINFO.ti_cols
	dec	ax
	cmp	ax,[bx].S_TINFO.ti_xoff
	jbe	tiright_00
	inc	[bx].S_TINFO.ti_xoff
    tiright_ok:
	call	ticontinue
    tiright_end:
	ret
    tiright_00:
	invoke	strlen,es::di
	cmp	ax,[bx].S_TINFO.ti_cols
	jb	tiright_eof
	inc	[bx].S_TINFO.ti_boff
	jmp	tiright_ok
    tiright_eof:
	call	tinocando
	jmp	tiright_end
tiright ENDP

tihome PROC PRIVATE USES bx
    ifdef __TE__
	call	tistripline
    endif
	mov	bx,tinfo
	sub	ax,ax
	mov	[bx].S_TINFO.ti_xoff,ax
	mov	[bx].S_TINFO.ti_boff,ax
	ret
tihome ENDP

titoend PROC PUBLIC USES bx
    ifdef __TE__
	call	tistripline
    endif
	mov	bx,tinfo
	mov	dx,[bx].S_TINFO.ti_cols
	dec	dx
	mov	ax,[bx].S_TINFO.ti_bcnt
	cmp	ax,dx
	jle	@F
	mov	ax,dx
      @@:
	mov	[bx].S_TINFO.ti_xoff,ax
	mov	dx,[bx].S_TINFO.ti_bcnt
	sub	dx,[bx].S_TINFO.ti_cols
	inc	dx
	xor	ax,ax
	cmp	ax,dx
	jg	@F
	mov	ax,dx
      @@:
	mov	[bx].S_TINFO.ti_boff,ax
	add	ax,[bx].S_TINFO.ti_xoff
	cmp	ax,[bx].S_TINFO.ti_bcnt
	jbe	@F
	dec	[bx].S_TINFO.ti_boff
      @@:
	call	ticontinue
	ret
titoend ENDP

; set byte count in line to .ti_bcnt
; set line[size-1]=0
; return CX strlen(DX:AX)

tistrlen PROC PRIVATE USES si di bx
	mov	bx,tinfo
	push	es
	mov	es,dx
	mov	si,ax
	mov	di,ax
	xor	ax,ax
	add	di,[bx].S_TINFO.ti_bcol
	dec	di
	mov	es:[di],al
	mov	di,si
	mov	cx,ax
	dec	cx
	cld?
	repnz	scasb
	not	cx
	dec	cx
	mov	[bx].S_TINFO.ti_bcnt,cx
	mov	ax,si
	pop	es
	ret
tistrlen ENDP

tidecvalue PROC pascal PRIVATE USES si di dx boff:DWORD, soff:DWORD,
	bmax:size_t, smax:size_t
	mov si,WORD PTR boff
	mov di,WORD PTR soff
	mov ax,[si]
	add ax,[di]
	.if ax
	    mov dx,[si]
	    mov ax,[di]
	    .if ax
		dec ax
		and si,si
		stc
	    .else
		dec dx
		and si,si
		clc
	    .endif
	    mov [di],ax
	    mov [si],dx
	.endif
	ret
tidecvalue ENDP

tidecx PROC PRIVATE USES ax bx
	mov	bx,tinfo
	invoke	tidecvalue,addr [bx].S_TINFO.ti_boff,addr [bx].S_TINFO.ti_xoff,
		[bx].S_TINFO.ti_bcol,[bx].S_TINFO.ti_cols
	ret
tidecx ENDP

tialignx PROC PUBLIC USES bx cx
	mov	bx,tinfo
	mov	cx,[bx].S_TINFO.ti_xoff
	add	cx,[bx].S_TINFO.ti_boff
	cmp	cx,ax
	jb	tialignx_inc
	je	tialignx_end
    tialignx_dec:
	call	tidecx
	jz	tialignx_end
	dec	cx
	cmp	ax,cx
	jne	tialignx_dec
	jmp	tialignx_ok
    tialignx_inc:
	call	tiincx
	jz	tialignx_end
	inc	cx
	cmp	ax,cx
	jne	tialignx_inc
    tialignx_ok:
	inc	cx
    tialignx_end:
	ret
tialignx ENDP

ifdef __TE__

tidoiflines PROC PUBLIC
	mov	ax,tinfo
	xchg	ax,bx
	test	[bx].S_TINFO.ti_flag,_T_LINEBUF
	xchg	ax,bx
	jnz	@F
	pop	ax
	jmp	tiretevent
      @@:
    ifdef __TE__
	push	ax
	call	tistripline
	pop	ax
    endif
	ret
tidoiflines ENDP

tiup PROC PRIVATE
	call tidoiflines
	push bx
	mov bx,ax
	sub ax,ax
	.if ax != [bx].S_TINFO.ti_yoff
	    dec [bx].S_TINFO.ti_yoff
	.elseif ax != [bx].S_TINFO.ti_loff
	    dec [bx].S_TINFO.ti_loff
	.endif
	pop bx
	ret
tiup ENDP

tidown PROC PUBLIC
	call	tidoiflines
	push	bx
	mov	bx,ax
	mov	dx,[bx].S_TINFO.ti_loff
	mov	cx,[bx].S_TINFO.ti_yoff
	mov	ax,dx
	add	ax,cx
	inc	ax
	cmp	ax,[bx].S_TINFO.ti_brow
	jae	tidown_retevent
	cmp	ax,[bx].S_TEDIT.ti_lcnt
	jae	tidown_continue
	mov	ax,[bx].S_TINFO.ti_rows
	dec	ax
	cmp	cx,ax
	jae	@F
	inc	[bx].S_TINFO.ti_yoff
	jmp	tidown_continue
      @@:
	mov	ax,[bx].S_TINFO.ti_brow
	sub	ax,dx
	sub	ax,cx
	jz	tidown_retevent
	dec	ax
	jz	tidown_retevent
	inc	[bx].S_TINFO.ti_loff
    tidown_continue:
	pop	bx
	jmp	ticontinue
    tidown_retevent:
	pop	bx
	jmp	tiretevent
tidown	ENDP

tipgup PROC PRIVATE
	call	tidoiflines
	push	bx
	mov	bx,ax
	mov	ax,[bx].S_TINFO.ti_loff
	test	ax,ax
	jz	tipgup_tictrlhome
	cmp	ax,[bx].S_TINFO.ti_rows
	jb	tipgup_tictrlhome
	sub	ax,[bx].S_TINFO.ti_rows
	mov	[bx].S_TINFO.ti_loff,ax
    tipgup_continue:
	pop	bx
	jmp	ticontinue
    tipgup_tictrlhome:
	pop	bx
	jmp	tictrlhome
tipgup ENDP

tipgdn PROC PRIVATE
	call	tidoiflines
	push	bx
	mov	bx,ax
	mov	ax,[bx].S_TINFO.ti_rows
	add	ax,ax
	add	ax,[bx].S_TINFO.ti_loff
	cmp	ax,[bx].S_TEDIT.ti_lcnt
	jnb	tipgdn_ctrlend
	mov	ax,[bx].S_TINFO.ti_loff
	add	ax,[bx].S_TINFO.ti_rows
	mov	[bx].S_TINFO.ti_loff,ax
    tipgdn_continue:
	pop	bx
	jmp	ticontinue
    tipgdn_ctrlend:
	pop	bx
	jmp	tictrlend
tipgdn ENDP

tictrlpgup PROC PRIVATE
	call	tidoiflines
	push	bx
	mov	bx,ax
	sub	ax,ax
	mov	[bx].S_TINFO.ti_yoff,ax
	pop	bx
	ret
tictrlpgup ENDP

tictrlpgdn PROC PRIVATE
	call	tidoiflines
	push	bx
	mov	bx,ax
	mov	ax,[bx].S_TINFO.ti_rows
	dec	ax
	mov	[bx].S_TINFO.ti_yoff,ax
	add	ax,[bx].S_TINFO.ti_loff
	cmp	ax,[bx].S_TEDIT.ti_lcnt
	pop	bx
	jb	@F
	ret
      @@:
	jmp	tictrlend
tictrlpgdn ENDP

tictrlend PROC PRIVATE
	call	tidoiflines
	xchg	bx,ax
	mov	bx,[bx].S_TEDIT.ti_lcnt
	xchg	bx,ax
	dec	ax
	call	tialigny
	jmp	ticontinue
tictrlend ENDP

tictrlhome PROC PRIVATE
	call	tictrlpgup
	push	bx
	mov	bx,tinfo
	mov	[bx].S_TINFO.ti_loff,ax
	pop	bx
	ret
tictrlhome ENDP

tiscrollup PROC PRIVATE
	call	tidoiflines
	push	bx
	mov	bx,ax
	sub	ax,ax
	cmp	ax,[bx].S_TINFO.ti_loff
	je	@F
	dec	[bx].S_TINFO.ti_loff
      @@:
	pop	bx
	ret
tiscrollup ENDP

tiscrolldn PROC PRIVATE
	call	tidoiflines
	push	bx
	mov	bx,ax
	mov	ax,[bx].S_TINFO.ti_loff
	add	ax,[bx].S_TINFO.ti_yoff
	inc	ax
	cmp	ax,[bx].S_TEDIT.ti_lcnt
	jae	@F
	inc	[bx].S_TINFO.ti_loff
      @@:
	pop	bx
	jmp	ticontinue
tiscrolldn ENDP

tidecy PROC PRIVATE USES bx ax
	mov	bx,tinfo
	invoke	tidecvalue,addr [bx].S_TINFO.ti_loff,addr [bx].S_TINFO.ti_yoff,
		[bx].S_TINFO.ti_brow,[bx].S_TINFO.ti_rows
	ret
tidecy ENDP

tiincy PROC PRIVATE USES si bx ax
	mov	bx,tinfo
	mov	si,[bx].S_TINFO.ti_rows
;	test	[bx].S_TINFO.ti_flag,_T_USEMENUS
;	jz	@F
;	dec	si
      @@:
	invoke	tiincvalue,addr [bx].S_TINFO.ti_loff,addr [bx].S_TINFO.ti_yoff,
		[bx].S_TINFO.ti_brow,si
	ret
tiincy ENDP

tialigny PROC PUBLIC USES bx cx
	mov	bx,tinfo	; Align yoff and loff to AX
	mov	cx,[bx].S_TINFO.ti_yoff
	add	cx,[bx].S_TINFO.ti_loff
	cmp	cx,ax
	jb	tialigny_inc
	je	tialigny_end
      @@:
	call	tidecy
	jz	tialigny_end
	dec	cx
	cmp	ax,cx
	jne	@B
	jmp	tialigny_ok
    tialigny_inc:
	call	tiincy
	jz	tialigny_end
	inc	cx
	cmp	ax,cx
	jne	tialigny_inc
    tialigny_ok:
	inc	cx
    tialigny_end:
	ret
tialigny ENDP

endif

tiseto PROC PUBLIC USES si di bx
	call	ticurlp
	mov	di,ax
  ifdef __TE__
	jz	tiseto_00
	mov	bx,2020h
	call	tistripl
	mov	bx,tinfo
	mov	ax,[bx].S_TINFO.ti_boff ; test if char is visible
	add	ax,[bx].S_TINFO.ti_xoff
	cmp	ax,cx
	jbe	tiseto_00
	test	[bx].S_TINFO.ti_flag,_T_LINEBUF
	jz	tiseto_01
	add	di,cx			; length of line
	mov	es,dx			; ES to segment
	mov	cx,ax
	sub	cx,[bx].S_TINFO.ti_bcnt ; CX to pad count
   ifdef _PADD_WITH_TABS
	test	[bx].S_TINFO.ti_flag,_T_OPTIMALFILL
	jz	tiseto_space
    tiseto_tab:
	mov	dx,di			; insert '\t' if possible
	add	dx,cx
	mov	ax,di
	and	ax,not 7
	add	ax,8
	cmp	ax,dx
	ja	tiseto_space
	sub	ax,di
	mov	ah,al
	mov	al,9
      @@:
	stosb
	mov	al,TITABCHAR
	dec	cx
	dec	ah
	jnz	@B
	jmp	tiseto_tab
    tiseto_space:			; padd the rest with ' '
   endif
	mov	ax,' '
	cld?
	rep	stosb
	mov	al,ah
	stosb
	jmp	tiseto_01
  else
	mov	bx,tinfo
	mov	cx,ax
	add	cx,[bx].S_TINFO.ti_bcol
	dec	cx
	mov	es,dx
	mov	bx,cx
	mov	BYTE PTR es:[bx],0
	invoke	strlen,dx::ax
	mov	dx,ax
	mov	bx,tinfo
	mov	[bx].S_TINFO.ti_bcnt,ax
	mov	ax,[bx].S_TINFO.ti_boff ; test if char is visible
	add	ax,[bx].S_TINFO.ti_xoff
	cmp	ax,dx
	jb	tiseto_00
  endif
    tiseto_toend:
	call	titoend			; if not --> to end of line
    tiseto_01:
	mov	ax,1
    tiseto_end:
	ret
    tiseto_00:
	xor	ax,ax
	jmp	tiseto_end
	ret
tiseto ENDP

ifdef __TE__
tigetindent PROTO
tibacksp PROC PRIVATE USES si di bx
else
tibacksp PROC PRIVATE USES bx
endif
	mov bx,tinfo
	xor cx,cx
	mov ax,[bx].S_TINFO.ti_boff
	add ax,[bx].S_TINFO.ti_xoff
	.if ax
  ifdef __TE__
	    .if [bx].S_TINFO.ti_flag & _T_USEINDENT
		mov di,ax
		mov ax,[bx].S_TINFO.ti_loff
		add ax,[bx].S_TINFO.ti_yoff
		mov si,ax
		call tigetindent
		.if ax == di
		    .while si
			dec si
			mov ax,si
			call tigetindent
			.break .if ax < di
			mov ax,di
		    .endw
		    .if ax < di
			sub di,ax
			.repeat
			    call tileft
			    call tidelete
			    dec di
			.until !di
			jmp tibacksp_end
		    .endif
		.endif
	    .endif
	    call tileft
  else
	    call tileft
  endif
	    jmp tibacksp_delete
	.else
  ifdef __TE__
	    .if [bx].S_TINFO.ti_flag & _T_LINEBUF
		mov ax,[bx].S_TINFO.ti_loff
		add ax,[bx].S_TINFO.ti_yoff
		.if ax
		    .if [bx].S_TINFO.ti_yoff
			dec [bx].S_TINFO.ti_yoff
		    .else
			dec [bx].S_TINFO.ti_loff
		    .endif
		    jmp @F
		.endif
	    .endif
  endif
	    call tinocando
	    jmp tibacksp_end
	.endif
      @@:
	call tiseto
	call titoend
    tibacksp_delete:
	call tidelete
    tibacksp_end:
	ret
tibacksp ENDP

ifdef	__TE__

tistr0B PROC PRIVATE USES di ax
	mov	di,ax
	mov	ax,2000h+TITABCHAR
	cmp	es:[di],al
	jne	tistr0B_end
	mov	es:[di],ah
	cmp	es:[di+1],al
	jne	@F
	mov	BYTE PTR es:[di],9
      @@:
	test	di,di
	jz	tistr0B_end
      @@:
	dec	di
	cmp	es:[di],al
	jne	@F
	mov	es:[di],ah
	or	di,di
	jnz	@B
      @@:
	cmp	BYTE PTR es:[di],9
	jne	tistr0B_end
	mov	es:[di],ah
    tistr0B_end:
	ret
tistr0B ENDP

endif

tiputc_add:
	mov	ax,[bx].S_TINFO.ti_bcnt
	inc	ax
	cmp	ax,[bx].S_TINFO.ti_bcol
	jae	tiputc_eof
  ifdef __TE__
	call	tiincx
	jz	tiputc_eof
	inc	[bx].S_TINFO.ti_bcnt
	push	cx
	call	ticurlp
	pop	cx
	jz	tiputc_eof
	or	[bx].S_TINFO.ti_flag,_T_MODIFIED
	mov	es,dx
	add	ax,[bx].S_TINFO.ti_xoff
	add	ax,[bx].S_TINFO.ti_boff
	test	[bx].S_TINFO.ti_flag,_T_LINEBUF
	jnz	tiputc_lbuf
    tiputc_insert:
	dec	ax
	mov	bx,ax
	mov	ah,cl
    tiputc_addcl:
	mov	al,es:[bx]
	mov	es:[bx],ah
	mov	ah,al
	inc	bx
	test	al,al
	jnz	tiputc_addcl
	mov	es:[bx],al
	jmp	tiputc_CONTINUE
    tiputc_lbuf:
	dec	ax
	push	ax
	test	[bx].S_TINFO.ti_flag,_T_USETABS
	jz	@F
	call	tistr0B
	call	tistrip
      @@:
	inc	ax
	call	tiputc_insert
	pop	ax
	push	cx
	call	tiexpand
	push	ax
	call	ticurlp
	pop	cx
	mov	bx,ax
	mov	ah,' '
      @@:
	cmp	bx,cx
	je	@F
	mov	al,es:[bx]
	inc	bx
	or	al,al
	jnz	@B
	mov	es:[bx]-1,ah
	jmp	@B
      @@:
	pop	cx
	mov	bx,tinfo
	cmp	cl,9
	jne	tiputc_CONTINUE
	mov	ax,[bx].S_TINFO.ti_xoff ; Align xoff and boff to next TAB
	add	ax,[bx].S_TINFO.ti_boff
	mov	cx,ax
	mov	dx,tetabsize
	dec	dl
	and	dl,TIMAXTABSIZE-1
	test	al,dl
	jz	tiputc_CONTINUE
	not	dl
	and	al,dl
	add	ax,tetabsize
	cmp	cx,ax			; Align xoff and boff to AX
	jb	tiputc_inc
	je	tiputc_CONTINUE
    tiputc_dec:
	call	tidecx
	jz	tiputc_CONTINUE
	dec	cx
	cmp	ax,cx
	jne	tiputc_dec
	jmp	tiputc_CONTINUE
    tiputc_inc:
	call	tiincx
	jz	tiputc_CONTINUE
	inc	cx
	cmp	ax,cx
	jne	tiputc_inc
  else
	push	cx
	call	ticurcp
	push	si
	push	di
	mov	cx,[bx].S_TINFO.ti_bcol
	sub	cx,[bx].S_TINFO.ti_xoff
	sub	cx,[bx].S_TINFO.ti_boff
	dec	cx
	mov	ds,dx
	mov	es,dx
	mov	di,ax
	mov	si,ax
	inc	di
	dec	cx
	mov	ax,si
	add	si,cx
	add	di,cx
	inc	cx
	std
	rep	movsb
	cld
	mov	bx,ax
	pop	di
	pop	si
	pop	ax
	mov	[bx],al
	mov	ax,ss
	mov	ds,ax
	mov	bx,tinfo
	inc	[bx].S_TINFO.ti_bcnt
	inc	[bx].S_TINFO.ti_xoff
	mov	ax,[bx].S_TINFO.ti_cols
	cmp	[bx].S_TINFO.ti_xoff,ax
	jl	tiputc_CONTINUE
	dec	ax
	mov	[bx].S_TINFO.ti_xoff,ax
	add	ax,[bx].S_TINFO.ti_boff
	cmp	[bx].S_TINFO.ti_bcnt,ax
	jbe	tiputc_CONTINUE
	inc	[bx].S_TINFO.ti_boff
  endif
    tiputc_CONTINUE:
	mov	ax,_TI_CONTINUE
	ret
  ifdef __TE__
    tiputc_strbuf:
  else
    tiputc_CONTROL:
  endif
	test	al,al
	jz	tiputc_ret
	test	[bx].S_TINFO.ti_flag,_T_USECONTROL
	jnz	tiputc_add
    tiputc_ret:
	mov	ax,_TI_RETEVENT
	ret
    tiputc_eof:
  ifdef __TE__
	mov	ax,[bx].S_TINFO.ti_bcol
	dec	ax
	mov	[bx].S_TINFO.ti_bcnt,ax
	invoke	ermsg,0,addr cp_linetolong
    tiputc_nocando:
  endif
	jmp	tinocando
  ifdef __TE__
    tiputc_ENTER:
	jmp	tienterni
    tiputc_CONTROL:
	test	[bx].S_TINFO.ti_flag,_T_LINEBUF
	jz	tiputc_strbuf
	cmp	al,9
	je	tiputc_TAB
	cmp	al,0Ah
	je	tiputc_ENTER
	cmp	al,0Dh
	je	tiputc_CONTINUE
	jmp	tiputc_ret
    tiputc_TAB:
	.if [bx].S_TINFO.ti_flag & _T_USETABS
	    call tiputc_add
	.else
	    call ticurcp
	    push di
	    mov di,ax
	    mov cx,ax
	    mov ax,tetabsize
	    add di,ax
	    dec ax
	    not ax
	    and di,ax
	    sub di,cx
	    .while di
		mov cl,' '
		call tiputc_add
		.break .if ax != _TI_CONTINUE
		dec di
	    .endw
	    pop di
	.endif
	cmp ax,_TI_CONTINUE
	jne tiputc_nocando
	jmp tiputc_CONTINUE
  endif

tiputc PROC PUBLIC USES bx
	mov bx,tinfo
	mov cx,ax
	call getctype
	.if ah & _CONTROL
	    call tiputc_CONTROL
	.else
	    call tiputc_add
	.endif
	ret
tiputc ENDP

titab PROC PRIVATE USES bx
	mov bx,tinfo
	.if [bx].S_TINFO.ti_flag & _T_LINEBUF
	    call tiputc
	    call ticontinue
	.else
	    call tiretevent
	.endif
	ret
titab ENDP

tidelete PROC PUBLIC USES si di bp bx
	mov  bx,tinfo
	call ticurcp
	mov  es,dx
	mov  di,ax
	or   [bx].S_TINFO.ti_flag,_T_MODIFIED
	.if  BYTE PTR es:[di] == 0
    ifdef __TE__
	    .if [bx].S_TINFO.ti_flag & _T_LINEBUF
		mov ax,[bx].S_TINFO.ti_loff
		add ax,[bx].S_TINFO.ti_yoff
		inc ax
		.if ax < [bx].S_TINFO.ti_brow && ax < [bx].S_TEDIT.ti_lcnt
		    call tigetline
		    .if !CARRY?
			push ax
			invoke strlen,dx::ax
			add ax,[bx].S_TINFO.ti_bcnt
			mov cx,ax
			pop ax
			.if cx < [bx].S_TINFO.ti_bcol
			    sub sp,[bx].S_TINFO.ti_bcol ; add next line to this
			    mov bp,sp
			    invoke strcpy,ss::bp,dx::ax
			    mov ax,[bx].S_TINFO.ti_loff
			    add ax,[bx].S_TINFO.ti_yoff
			    mov si,ax
			    call tigetline
			    .if !CARRY?
				invoke strcat,dx::ax,ss::bp
				add sp,[bx].S_TINFO.ti_bcol
				inc si
				mov ax,si
				mov dx,1
				call tiremline
			    .endif
			.endif
		    .endif
		.endif
	    .endif
    endif
	.else
    ifdef __TE__
	    mov cx,[bx].S_TINFO.ti_flag
	    .if cx & _T_LINEBUF && cx & _T_USETABS
		call tistrip
		mov bx,ax
		mov ah,BYTE PTR tetabsize
		dec ah
		and ah,TIMAXTABSIZE-1
		.if al & ah
		    mov ah,es:[bx]
		    mov al,es:[bx][-1]
		    .if al == 9
			mov BYTE PTR es:[bx][-1],' '
			jmp @F
		    .elseif al == TITABCHAR
			mov di,bx
			mov ah,' '
			.repeat
			    dec di
			    .break .if es:[di] != al
			    mov es:[di],ah
			.until !di
			mov es:[di],ah
			jmp @F
		    .endif
		.endif
		.repeat
		    mov ax,bx
		    inc ax
		    invoke strcpy,dx::bx,dx::ax
		.until BYTE PTR es:[bx] != TITABCHAR
	      @@:
		mov  ax,bx
		call tiexpand
		mov  bx,tinfo
		or   [bx].S_TINFO.ti_flag,_T_MODIFIED
		jmp  @F
	    .endif
    endif
	    dec [bx].S_TINFO.ti_bcnt
	    mov cx,ax
	    inc cx
	    invoke strcpy,dx::ax,dx::cx
	.endif
      @@:
	call ticontinue
	ret
tidelete ENDP

tiisword PROC PRIVATE
	call	getctype
	and	ah,_UPPER or _LOWER or _DIGIT
	jnz	@F
	cmp	al,'_'
	jne	tiisword_nul
	test	al,al
      @@:
	ret
    tiisword_nul:
	cmp	al,al
	ret
tiisword ENDP

tinextword PROC PRIVATE USES si bp
	push	ds
	call	ticurcp
	mov	bp,tinfo
	mov	ds,dx
	mov	si,ax
	mov	dx,ax
	cld?
      @@:
	lodsb
	call	tiisword
	jnz	@B
	test	al,al
	jz	tinextword_eof
      @@:
	lodsb
	test	al,al
	jz	tinextword_eof
	call	tiisword
	jz	@B
	dec	si
	sub	si,dx
	mov	ax,[bp].S_TINFO.ti_boff
	add	ax,[bp].S_TINFO.ti_xoff
	add	ax,si
	cmp	ax,[bp].S_TINFO.ti_bcnt
	ja	tinextword_eof
	mov	ax,si
	add	ax,[bp].S_TINFO.ti_xoff
	mov	dx,[bp].S_TINFO.ti_cols
	cmp	ax,dx
	jb	@F
	dec	dx
	sub	ax,dx
	add	[bp].S_TINFO.ti_boff,ax
	mov	ax,dx
     @@:
	mov	[bp].S_TINFO.ti_xoff,ax
	pop	ds
	call	ticontinue
    tinextword_end:
	ret
    tinextword_eof:
	; next line..
	pop	ds
	call	titoend
	jmp	tinextword_end
tinextword ENDP

tiprevword PROC PRIVATE USES si di bp bx
	mov	di,ds
	mov	bp,tinfo
	mov	ax,[bp].S_TINFO.ti_boff
	add	ax,[bp].S_TINFO.ti_xoff
	test	ax,ax
	jz	tiprevword_eof
	mov	si,ax
	mov	cx,ax
	call	ticurlp
	mov	ds,dx
	add	si,ax
	mov	bx,si
	mov	dx,ax
	std
	lodsb
	inc	si
	call	tiisword
	jnz	tiprevword_start
	test	al,al
	jnz	tiprevword_l1
	dec	si
    tiprevword_l1:
	lodsb
	cmp	si,dx
	jbe	tiprevword_eof
	test	al,al
	jz	tiprevword_eof
	call	tiisword
	jz	tiprevword_l1
    tiprevword_l2:
	lodsb
	cmp	si,dx
	jbe	tiprevword_eof
	test	al,al
	jz	tiprevword_eof
	call	tiisword
	jnz	tiprevword_l2
	cld
	add si,2
	mov ds,di
	mov ax,si
	sub ax,dx
	.if ax < [bp].S_TINFO.ti_cols
	    mov [bp].S_TINFO.ti_xoff,ax
	    mov [bp].S_TINFO.ti_boff,0
	.else
	    sub ax,[bp].S_TINFO.ti_xoff
	    mov [bp].S_TINFO.ti_boff,ax
	.endif
	jmp tiprevword_continue
    tiprevword_start:
	mov	al,[si-1]
	call	tiisword
	jnz	tiprevword_l2
	dec	si
	jmp	tiprevword_l1
    tiprevword_continue:
	call	ticontinue
    tiprevword_end:
	ret
    tiprevword_eof:
	cld
	mov	ds,di
	call	tihome
	jmp	tiprevword_end
tiprevword ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

tiinitcursor PROC PUBLIC
	push	bx
	mov	bx,tinfo
	mov	[bx].S_TINFO.ti_cursor.cr_type,CURSOR_NORMAL
	pop	bx
tiinitcursor ENDP

tisetcursor PROC PRIVATE USES bx
	mov	bx,tinfo
	mov	ax,[bx].S_TINFO.ti_xpos
	add	ax,[bx].S_TINFO.ti_xoff
	mov	ah,BYTE PTR [bx].S_TINFO.ti_ypos
    ifdef __TE__
	test	[bx].S_TINFO.ti_flag,_T_LINEBUF
	jz	@F
	add	ah,BYTE PTR [bx].S_TINFO.ti_yoff
      @@:
    endif
	mov	[bx].S_TINFO.ti_cursor.cr_xy,ax
	mov	[bx].S_TINFO.ti_cursor.cr_type,CURSOR_NORMAL
	invoke	cursorset,addr [bx].S_TINFO.ti_cursor
	ret
tisetcursor ENDP

timouse PROC PRIVATE USES bx
  ifdef __MOUSE__
	mov	bx,tinfo
	call	mousey
   ifdef __TE__
	mov	dx,ax
	call	mousex
	mov	cx,ax
	mov	ax,[bx].S_TINFO.ti_xpos
	cmp	cx,ax
	jb	timouse_esc
	add	ax,[bx].S_TINFO.ti_cols
	cmp	cx,ax
	jae	timouse_esc
	mov	ax,[bx].S_TINFO.ti_ypos
	cmp	dx,ax
	jb	timouse_esc
	add	ax,[bx].S_TINFO.ti_rows
	cmp	dx,ax
	jae	timouse_esc
	sub	dx,[bx].S_TINFO.ti_ypos
	mov	[bx].S_TINFO.ti_yoff,dx
	push	cx
	call	ticurlp
	jz	@F
	invoke	strlen,dx::ax
     @@:
	pop	cx
	sub	cx,[bx].S_TINFO.ti_xpos
	cmp	cx,ax
	jg	@F
	mov	ax,cx
     @@:
	mov	[bx].S_TINFO.ti_xoff,ax
	call	tisetcursor
	call	msloop
   else
	cmp	ax,[bx].S_TINFO.ti_ypos
	jne	timouse_esc
	call	mousex
	mov	dx,[bx].S_TINFO.ti_xpos
	cmp	al,dl
	jb	timouse_esc
	add	dx,[bx].S_TINFO.ti_cols
	cmp	ax,dx
	jnb	timouse_esc
	sub	ax,[bx].S_TINFO.ti_xpos
	mov	[bx].S_TINFO.ti_xoff,ax
	lodm	[bx].S_TINFO.ti_bp
	add	ax,[bx].S_TINFO.ti_boff
	invoke	strlen,dx::ax
	cmp	ax,[bx].S_TINFO.ti_xoff
	jnb	@F
	mov	[bx].S_TINFO.ti_xoff,ax
      @@:
	mov	ax,[bx].S_TINFO.ti_xpos
	add	ax,[bx].S_TINFO.ti_xoff
	invoke	gotoxy,ax,[bx].S_TINFO.ti_ypos
	call	msloop
   endif ; __TE__
	call	ticontinue
    timouse_end:
	ret
    timouse_esc:
	call	tiesc
	jmp	timouse_end
  else
	call	ticontinue
	ret
  endif ; __MOUSE__
timouse ENDP

tievent PROC PUBLIC
	mov	dx,bx
	mov	cx,ti_key_count
	xor	bx,bx
    tievent_loop:
	test	cx,cx
	jz	tievent_break
	cmp	ax,ti_keytable[bx]
	jne	tievent_next
	mov	bx,ti_proctab[bx]
	xchg	bx,dx
	jmp	dx
    tievent_next:
	add	bx,size_l
	dec	cx
	jnz	tievent_loop
    tievent_break:
	mov	bx,dx
	call	tiputc
	ret
tievent ENDP

tiputl PROC PRIVATE USES si di bx
local	lb[2+TIMAXSCRLINE]:BYTE
local	wc[2*TIMAXSCRLINE]:BYTE
local	line:size_t	; current line 0..max
local	loff:size_t	; adress of line
local	lseg:size_t
local	llen:size_t	; length of line
local	clst:size_t	; clip start
local	clen:size_t	; clip end
	mov si,tinfo
  ifdef __TE__
	mov	line,ax
	mov	ah,[si].S_TINFO.ti_clat
	mov	al,[si].S_TINFO.ti_clch
	test	[si].S_TINFO.ti_flag,_T_USESTYLE
	jz	@F
	mov	ah,[si].S_TEDIT.ti_stat
	mov	al,[si].S_TEDIT.ti_stch
      @@:
  else
	mov	ah,[si].S_TINFO.ti_clat
	mov	al,[si].S_TINFO.ti_clch
  endif
	push	ss
	pop	es
	lea	dx,wc
	mov	di,dx
	mov	cx,TIMAXSCRLINE
	cld?
	rep	stosw
	mov	di,dx
  ifdef __TE__
	mov	ax,line
	call	tigetline
	mov	loff,ax
	mov	lseg,dx
	jz	tiputl_screen
  else
	lodm	[si].S_TINFO.ti_bp
	mov	loff,ax
	mov	lseg,dx
  endif
	push	dx
	push	ax
	lea	bx,lb
	add	ax,[si].S_TINFO.ti_boff
	invoke	memcpy,ss::bx,dx::ax,TIMAXSCRLINE
	mov	[bx+TIMAXSCRLINE],cl
	call	strlen
	mov	es,dx
	mov	llen,ax
	cmp	ax,[si].S_TINFO.ti_boff
	jbe	tiputl_color
	xchg	si,bx
	mov	cx,TIMAXSCRLINE
    tiputl_cl:
	lodsb
	or	al,al
	jz	tiputl_break
	cmp	al,TITABCHAR
	jne	@F
	mov	al,' '
    @@:
	cmp	al,9
	jne	@F
	test	[bx].S_TINFO.ti_flag,_T_SHOWTABS
	jnz	@F
	mov	al,' '
    @@:
	stosb
	inc	di
	dec	cx
	jnz	tiputl_cl
    tiputl_break:
	mov	si,bx
  ifdef __TE__
	test	[si].S_TINFO.ti_flag,_T_USESTYLE
	jz	tiputl_color
	push	es
	mov	ax,loff
	mov	di,lseg
	lea	dx,wc
	mov	cx,llen
	mov	bx,line
	call	tistyle
	pop	es
  endif
    tiputl_color:
  ifdef __CLIP__
	xor	ax,ax
	mov	clen,ax ; clip end to	0000
	dec	ax		; clip start to FFFF
	mov	clst,ax
	call	tiselected
	jz	tiputl_screen
  ifdef __TE__
	xor	dx,dx
	cmp	WORD PTR [si].S_TINFO.ti_bp,dx
	jne	tiputl_local
	mov	ax,line
	cmp	ax,[si].S_TINFO.ti_clsl
	jb	tiputl_screen
	je	tiputl_clst
	cmp	ax,[si].S_TINFO.ti_clel
	ja	tiputl_screen
	mov	clst,dx
	je	tiputl_clen
	dec	dx
	mov	clen,dx
	jmp	tiputl_clput
    tiputl_clen:
	mov	ax,[si].S_TINFO.ti_cleo
	mov	clen,ax
	jmp	tiputl_clput
    tiputl_clst:
	dec	dx
	mov	clen,dx
	cmp	ax,[si].S_TINFO.ti_clel
	mov	ax,[si].S_TINFO.ti_clso
	mov	clst,ax
	je	tiputl_clen
	jmp	tiputl_clput
    tiputl_local:
  endif
	mov	ax,[si].S_TINFO.ti_clso
	add	ax,WORD PTR [si].S_TINFO.ti_bp
	mov	clst,ax
	mov	ax,[si].S_TINFO.ti_cleo
	add	ax,WORD PTR [si].S_TINFO.ti_bp
	mov	clen,ax
    tiputl_clput:
	mov	cx,TIMAXSCRLINE
	lea	di,wc+1
	mov	al,at_background[B_Inverse]
	mov	bx,loff
	add	bx,[si].S_TINFO.ti_boff
	mov	dx,clst
    tiputl_cloop:
	cmp	bx,dx
	jb	@F
	cmp	bx,clen
	jae	tiputl_screen
	stosb
	jmp	tiputl_inc
    @@:
	inc	di
    tiputl_inc:
	inc	bx
	inc	di
	dec	cx
	jnz	tiputl_cloop
  endif
    tiputl_screen:
	mov	ax,[si].S_TINFO.ti_xpos
	mov	dx,[si].S_TINFO.ti_ypos
    ifdef __TE__
	add	dx,line
	sub	dx,[si].S_TINFO.ti_loff
    endif
	HideMouseCursor
	invoke	getxyp,ax,dx
	mov	es,dx
	mov	di,ax
	mov	cx,[si].S_TINFO.ti_cols
	lea	si,wc
	assert	cx,TIMAXSCRLINE,jna,"tiputl"
	rep	movsw
	ShowMouseCursor
	xor	ax,ax
	ret
tiputl	ENDP

tiputs PROC PUBLIC
	call	tisetcursor
    ifdef __TE__
	push	si
	push	di
	mov	di,tinfo
	mov	si,[di].S_TINFO.ti_rows
	mov	di,[di].S_TINFO.ti_loff
	.if !si
	    inc si
	.endif
	.while si
	    mov	 ax,di
	    call tiputl
	    inc	 di
	    dec	 si
	.endw
	pop	di
	pop	si
    else
	sub	ax,ax
	call	tiputl
    endif
	ret
tiputs ENDP

timodal PROC PUBLIC USES si di
	mov si,_TI_CONTINUE
	.while si != _TI_RETEVENT
	    call tiseto
	    call tiputs
	    call tgetevent
	  ifdef __CLIP__
	    call ticlipevent
	  endif
	    mov	 di,ax
	    call tievent
	    mov	 si,ax
	.endw
	call	ticurlp
	invoke	strlen,dx::ax
	mov	si,tinfo
	mov	[si].S_TINFO.ti_bcnt,ax
	mov	ax,di
	ret
timodal ENDP

;-----------------------------------------------------------------------------
; Alloc file buffer
;-----------------------------------------------------------------------------

	.data
	emmp	dd 0		; Allocated page
	curh	dw -1		; Current owners handle
	curp	dw -1		; Current page for this handle
	cp_noname db 'NONAME.ASM',0

	.code

	;--------------------------------------------------------------
	; Validate tinfo (AX)
	; return CX .ti_flag, DL .dl_flag, ES:AX dialog
	;--------------------------------------------------------------

tistate PROC _CType PUBLIC USES bx
	mov	bx,ax
	test	ax,ax
	jz	@F
	sub	ax,ax
	mov	cx,[bx].S_TINFO.ti_flag
	push	ss
	pop	es
	lea	bx,[bx].S_TEDIT.ti_DOBJ
	test	cx,_T_MALLOC
	jz	@F
	test	cx,_T_LINEBUF
	jz	@F
	mov	dl,BYTE PTR [bx].S_DOBJ.dl_flag
	mov	ax,bx
      @@:
	ret
tistate ENDP

tialloc PROC PRIVATE USES si di bx
	xor	di,di
	mov	si,ax
	cmp	tepages,EMSMINPAGES
	jb	tialloc_lokal
	call	emmnumfreep
	cmp	ax,EMSMINPAGES
	jb	tialloc_lokal
	cmp	ax,tepages
	jb	@F
	mov	ax,tepages
      @@:
	mov	di,ax
	lodm	emmp
	test	dx,dx		; same page for all files..
	jnz	@F
	mov	ax,0402h
	call	palloc
	jz	tialloc_fail
	inc	dx		; + 16
	xor	ax,ax		; zero offset
	stom	emmp
      @@:
	stom	[si].S_TINFO.ti_bp	; base pointer to page
	or	[si].S_TINFO.ti_flag,_T_MALLOC
	invoke	emmalloc,di
	inc	ax
	jz	tialloc_emmfail
	mov	[si].S_TEDIT.ti_emmh,dx
	mov	[si].S_TEDIT.ti_emmp,0
	or	[si].S_TINFO.ti_flag,_T_EMMBUF
	jmp	tialloc_style
    tialloc_fail?:
	mov	ax,si
	call	tifree
    tialloc_fail:
	invoke	ermsg,0,addr CP_ENOMEM
	sub	ax,ax
	jmp	tialloc_end
    tialloc_emmfail:
	mov	ax,si
	call	tifree
    tialloc_lokal:
	mov	ax,tinfo
	call	tistate
	jnz	tialloc_fail
	mov	ax,4004h
	call	palloc
	jz	tialloc_fail
	inc	dx
	sub	ax,ax
	or	[si].S_TINFO.ti_flag,_T_MALLOC
	stom	[si].S_TINFO.ti_bp
	mov	di,16
    tialloc_style:
	mov	ax,WMAXPATH/16
	call	palloc
	jz	tialloc_fail?
	invoke	strcpy,dx::ax,addr cp_noname
	stom	[si].S_TEDIT.ti_file
	mov	ax,128
	mov	cx,telsize
	shl	ax,cl
	mov	[si].S_TINFO.ti_bcol,ax
	mov	bx,ax
	sub	ax,ax
	cwd
	inc	dx
	div	bx
	shr	di,2
	mul	di
	mov	[si].S_TINFO.ti_brow,ax
	mov	ax,si
	call	timemzero
	inc	ax
    tialloc_end:
	ret
tialloc ENDP

tifree	PROC PRIVATE USES si
	mov	si,ax
	mov	ax,[si].S_TINFO.ti_flag
	test	ax,_T_MALLOC or _T_EMMBUF
	jz	tifree_end
	test	ax,_T_EMMBUF
	jz	@F
	invoke	emmfree,[si].S_TEDIT.ti_emmh
	mov	ax,-1
	mov	curh,ax		; Force a reread of the page
	mov	curp,ax
	jmp	tifree_name
      @@:
	mov	ax,[si].S_TINFO.ti_flag
	test	ax,_T_MALLOC
	jz	tifree_end
	mov	ax,WORD PTR [si].S_TINFO.ti_bp[2] ; free seg - 1
	dec	ax
	invoke	free,ax::ax		; free() only use segment..
    tifree_name:
	invoke	free,[si].S_TEDIT.ti_file
	invoke	free,[si].S_TEDIT.ti_style
    tifree_end:
	and	[si].S_TINFO.ti_flag,not (_T_MALLOC or _T_EMMBUF)
	ret
tifree	ENDP

;-----------------------------------------------------------------------------
; Open
;-----------------------------------------------------------------------------

tigetfile PROC _CType PUBLIC USES bx
	sub ax,ax	; AX first file
	mov dx,ax	; DX last file
	mov bx,tinfo
	.if bx
	    .if [bx].S_TINFO.ti_flag & _T_FILE
		mov dx,bx
		.repeat
		    mov ax,bx
		    mov bx,[bx].S_TEDIT.ti_prev
		    .break .if !bx
		.until bx == dx
		mov bx,dx
		.repeat
		    mov dx,bx
		    mov bx,[bx].S_TEDIT.ti_next
		    .break .if !bx
		.until bx == ax
		inc bx
	    .endif
	.endif
	ret
tigetfile ENDP

tishow PROC _Ctype PUBLIC USES si bx ti:size_t
	mov si,ti
	.if !([si].S_TEDIT.ti_DOBJ.dl_flag & _D_DOPEN)
	    .if dlscreen(addr [si].S_TEDIT.ti_DOBJ,[si].S_TINFO.ti_clat)
		invoke dlshow,dx::ax
		sub ax,ax
		mov al,[si].S_TEDIT.ti_DOBJ.dl_rect.rc_col
		mov [si].S_TINFO.ti_cols,ax
		mov al,[si].S_TEDIT.ti_DOBJ.dl_rect.rc_row
		mov [si].S_TINFO.ti_rows,ax
		invoke cursorset,addr [si].S_TINFO.ti_cursor
		.if [si].S_TINFO.ti_flag & _T_USEMENUS
		    dec [si].S_TINFO.ti_rows
		    mov dx,WORD PTR [si].S_TEDIT.ti_DOBJ.dl_rect
		    mov cx,[si].S_TINFO.ti_cols
		    mov bl,dh
		    mov ah,at_background[B_Menus]
		    mov al,' '
		    invoke scputw,dx,bx,cx,ax
		    inc dl
		    sub cx,19
		    invoke scpath,dx,bx,cx,[si].S_TEDIT.ti_file
		.endif
		call tiputs
	    .endif
	.endif
	ret
tishow ENDP

tihide PROC pascal PRIVATE USES si ti:size_t
	mov si,ti
	invoke dlclose,addr [si].S_TEDIT.ti_DOBJ
	ret
tihide ENDP

tiopen PROC PRIVATE USES si bx
	.if nalloc(S_TEDIT)
	    push ax
	    invoke memzero,ss::ax,S_TEDIT
	    pop si
	    mov al,at_background[B_TextEdit]
	    or	al,at_foreground[F_TextEdit]
	    mov [si].S_TINFO.ti_clat,al
	    mov [si].S_TEDIT.ti_stat,al
	    mov [si].S_TINFO.ti_cursor.cr_type,CURSOR_NORMAL
	    mov al,' '
	    mov [si].S_TINFO.ti_clch,al
	    mov [si].S_TEDIT.ti_stch,al
	    sub ax,ax
	    mov al,_scrcol	; adapt to current screen
	    mov [si].S_TINFO.ti_cols,ax
	    mov al,_scrrow
	    inc al
	    mov [si].S_TINFO.ti_rows,ax
	    mov ax,si
	    .if tialloc()
		.if tigetfile()
		    mov bx,dx
		    mov [si].S_TEDIT.ti_prev,bx ; Link to last file
		    mov [bx].S_TEDIT.ti_next,si
		.endif
		mov ax,teflag
		or  [si].S_TINFO.ti_flag,ax
		.if [si].S_TINFO.ti_flag & _T_USEMENUS
		    inc [si].S_TINFO.ti_ypos
		    inc BYTE PTR [si].S_TINFO.ti_cursor.cr_xy[size_l/2]
		    dec [si].S_TINFO.ti_rows
		.endif
		mov  ax,si
		test ax,ax
		jmp  @F
	    .endif
	    invoke nfree,si
	    jmp tiopen_nomem
	.else
	    jmp tiopen_nomem
	.endif
      @@:
	ret
    tiopen_nomem:
	invoke ermsg,0,addr CP_ENOMEM
	xor ax,ax
	jmp @B
tiopen ENDP

;-----------------------------------------------------------------------------
; Get line from buffer
;-----------------------------------------------------------------------------

tipushh PROC PRIVATE
	mov	ax,curh
	cmp	ax,-1
	je	@F
	cmp	ax,[si].S_TEDIT.ti_emmh
	je	tipushh_end
	invoke	emmwrite,emmp,curh,curp
      @@:
	mov	ax,[si].S_TEDIT.ti_emmh
	mov	curh,ax
	mov	ax,[si].S_TEDIT.ti_emmp
	mov	curp,ax
	invoke	emmread,emmp,curh,curp
    tipushh_end:
	ret
tipushh ENDP

tigetline PROC PUBLIC	; Get line from <tinfo> - tigetline(AX) --> DX:AX
	mov	dx,tinfo
tigetline ENDP

timemline PROC PRIVATE	; Get line from <[dx]> - timemline(AX,DX) --> DX:AX
	push	si
	push	di
	mov	di,ax				; line
	mov	si,dx				; &tinfo
	mov	ax,[si].S_TINFO.ti_flag
	test	ax,_T_LINEBUF
	jz	timemline_nol
	cmp	di,[si].S_TINFO.ti_brow
	jnb	timemline_null
	test	ax,_T_EMMBUF
	mov	ax,[si].S_TINFO.ti_bcol
	jz	timemline_malloc
	mov	ax,[si].S_TEDIT.ti_emmh ; Init current EMM handle
	cmp	curh,ax			; same handle ?
	je	@F
	call	tipushh
      @@:
	mov	ax,[si].S_TINFO.ti_bcol ; size of line
	shl	ax,2				; * 4 (align segment)
	mul	di				; * line (DX to page)
	cmp	dx,[si].S_TEDIT.ti_emmp
	je	timemline_pageok
	push	dx
	push	ax
	push	dx
	invoke	emmwrite,[si].S_TINFO.ti_bp,[si].S_TEDIT.ti_emmh,[si].S_TEDIT.ti_emmp
	pop	ax
	invoke	emmread,[si].S_TINFO.ti_bp,[si].S_TEDIT.ti_emmh,ax
	test	ax,ax
	pop	ax
	pop	dx
	jnz	timemline_null
    timemline_pageok:
	mov	[si].S_TEDIT.ti_emmp,dx ; save page offset
	mov	curp,dx
	shr	ax,6
    timemline_ok:
	add	ax,WORD PTR [si].S_TINFO.ti_bp+2 ; + segment
	mov	dx,ax
	xor	ax,ax
	cmp	di,[si].S_TEDIT.ti_lcnt
	jnb	timemline_new
	test	dx,dx
	clc				; Carry set if new line
    timemline_end:
	pop	di
	pop	si
	ret
    timemline_null:			; ZF and CF set on error
	xor	ax,ax
	mov	dx,ax
	jmp	timemline_new
    timemline_nol:
	lodm	[si].S_TINFO.ti_bp
    timemline_new:
	test	dx,dx
	stc
	jmp	timemline_end
    timemline_malloc:
	shr	ax,4			; line size in para
	mul	di			; * line offset
	jmp	timemline_ok
timemline ENDP

timemzero PROC PRIVATE USES si di bx
	mov bx,ax
	mov ax,[bx].S_TINFO.ti_flag
	.if dzemm && ax & _T_EMMBUF
	    mov dx,[bx].S_TEDIT.ti_emmh
	    mov ax,7100h
	    int 67h
	    test ah,ah
	    jz timemzero_end
	.endif
	sub	si,si
	cld
      @@:
	mov	ax,si
	mov	dx,bx
	call	timemline
	jz	timemzero_end
	mov	es,dx
	mov	di,ax
	sub	ax,ax
	mov	cx,[bx].S_TINFO.ti_bcol
	shr	cx,1
	rep	stosw
	inc	si
	jmp	@B
    timemzero_end:
	ret
timemzero ENDP

ticlose PROC PRIVATE USES si di bx
	mov si,ax
	sub di,di
	.if [si].S_TINFO.ti_flag & _T_MALLOC or _T_EMMBUF
	    call tifree
	    invoke dlclose,addr [si].S_TEDIT.ti_DOBJ
	.endif
	.if tigetfile()
	    mov di,[si].S_TEDIT.ti_prev
	    mov bx,[si].S_TEDIT.ti_next
	    mov [si].S_TEDIT.ti_prev,0
	    mov [si].S_TEDIT.ti_next,0
	    .if bx && [bx].S_TEDIT.ti_prev == si
		mov [bx].S_TEDIT.ti_prev,di
	    .endif
	    .if di && [di].S_TEDIT.ti_next == si
		mov [di].S_TEDIT.ti_next,bx
	    .else
		mov di,bx
	    .endif
	.endif
	mov tinfo,di
	invoke nfree,si
	sub ax,ax
	ret
ticlose ENDP

tisavechanges PROC pascal PRIVATE USES di
local DLG_TESave:DWORD
	.if rsopen(IDD_TESave)
	    stom   DLG_TESave
	    invoke dlshow,dx::ax
	    les	  di,DLG_TESave
	    sub	   cx,cx
	    mov	   cl,es:[di][6]
	    sub	   cl,10
	    mov	   ax,es:[di][4]
	    add	   ax,0205h
	    mov	   dl,ah
	    mov	   di,tinfo
	    invoke scpath,ax,dx,cx,[di].S_TEDIT.ti_file
	    invoke rsevent,IDD_TESave,DLG_TESave
	    invoke dlclose,DLG_TESave
	    mov	   ax,dx
	.endif
	ret
tisavechanges ENDP

;-----------------------------------------------------------------------------
;
;-----------------------------------------------------------------------------

	.data
	cp_linefeed db 0Dh,0Ah,0
	.code

tiofread PROC PUBLIC USES si dx
	mov	ax,STDI.ios_l	; current line
	cmp	STDI.ios_c,0	; first line ?
	je	@F
	inc	STDI.ios_l	; get next line
	inc	ax
      @@:
	call	tigetline
	jc	tiofread_eof
	invoke	strcpy,STDI.ios_bp,dx::ax
	invoke	strcat,dx::ax,addr cp_linefeed
	mov	si,ax
	mov	ah,' '
	cld
      @@:
	lodsb
	test	al,al
	jz	@F
	cmp	al,TITABCHAR
	jne	@B
	mov	[si-1],ah
	jmp	@B
      @@:
	invoke	strlen,STDI.ios_bp
	mov	STDI.ios_c,ax
	sub	ax,ax
	mov	STDI.ios_i,ax
	inc	ax
    tiofread_end:
	ret
    tiofread_eof:
	sub	ax,ax
	jmp	tiofread_end
tiofread ENDP

tiseekst PROC PUBLIC	; cx dx:ax | ecx eax
      @@:
	push	ax			; ax: offset
	mov	[si].S_IOST.ios_l,dx	; dx: line
	mov	[si].S_IOST.ios_c,0
	call	tiofread
	pop	ax
	jz	tiseekst_fail
	cmp	[si].S_IOST.ios_c,ax
	ja	tiseekst_end
	inc	cx
	sub	ax,ax
	jmp	@B
    tiseekst_end:
	mov	[si].S_IOST.ios_i,ax
	inc	ax
	ret
    tiseekst_fail:
	sub	ax,ax
	ret
tiseekst ENDP

	;----------------------------------------------------
	; This is used by all search funtions
	; lines is copyed to _bufin and converted
	;
	; .ios_l - current line
	; .ios_i - current offset
	; .ios_c - strlen line
	; ?
	; .ios_bb (low word) -- offset
	; .ios_bb (high word) - line
	;----------------------------------------------------

titostdi PROC PRIVATE USES bx
	invoke	oinitst,addr STDI,0
	mov	ax,fsflag
	and	al,IO_SEARCHMASK
	or	ax,IO_LINEBUF
	mov	STDI.ios_flag,ax
	call	ticurcp
	mov	es,dx
	mov	bx,ax		; cursor may be set above actual line size
	cmp	BYTE PTR es:[bx],0
	jne	@F
	call	titoend
      @@:
	mov	bx,tinfo
	mov	ax,[bx].S_TINFO.ti_boff
	add	ax,[bx].S_TINFO.ti_xoff
	mov	WORD PTR STDI.ios_bb,ax
	mov	ax,[bx].S_TINFO.ti_loff
	add	ax,[bx].S_TINFO.ti_yoff
	mov	STDI.ios_l,ax
	mov	WORD PTR STDI.ios_bb+2,ax
	call	tiofread
	mov	ax,WORD PTR STDI.ios_bb
	mov	STDI.ios_i,ax
	ret
titostdi ENDP

;-----------------------------------------------------------------------------
;
;-----------------------------------------------------------------------------

	.data
	cp_filetolong	db 'File too big, no more memory',0
	tab_c1 db ?
	tab_c2 db ?
	usetab db ?

	.code

tilineerror:
	push	dx
	call	oungetc
	test	[si].S_TINFO.ti_flag,_T_MODIFIED
	jnz	@F
	or	[si].S_TINFO.ti_flag,_T_MODIFIED
	invoke	ermsg,0,addr cp_linetolong
      @@:
	pop	dx
	ret

tireaderror:
	invoke	ermsg,0,addr cp_filetolong
	ret

tiiost:
	push	ax
	invoke	memzero,ss::bx,S_IOST
	pop	ax
	mov	[bx].S_IOST.ios_file,ax
	mov	[bx].S_IOST.ios_size,2048
	mov	WORD PTR [bx].S_IOST.ios_bp,offset _bufin + 2048
	mov	WORD PTR [bx].S_IOST.ios_bp[2],ds
	ret

tiread	PROC PRIVATE
	push	si	; AX tinfo
	push	di
	push	bx
	push	bp
	mov	si,ax
	; v2.49 -- auto detect CR/LF
	and	[si].S_TINFO.ti_flag,7FFFh ; not _T_USECRLF
	mov	tab_c1,' '	; v2.39 - include Use Tabs and Tab Size
	mov	tab_c2,' '
	mov	usetab,0
	test	[si].S_TINFO.ti_flag,_T_USETABS
	jz	@F
	mov	tab_c1,9
	mov	tab_c2,TITABCHAR
	mov	usetab,1
      @@:
	call	tiftime
	stom	[si].S_TEDIT.ti_time
	invoke	openfile,[si].S_TEDIT.ti_file,M_RDONLY,A_OPEN
	inc	ax
	mov	bp,ax
	jz	tiread_end
	dec	ax
	mov	bx,offset STDI
	call	tiiost
	invoke	lseek,STDI.ios_file,0,SEEK_END
	stom	[si].S_TEDIT.ti_size
	invoke	lseek,STDI.ios_file,0,SEEK_SET
	xor	ax,ax
	mov	bp,ax
	call	tigetline
	jz	tiread_error
	mov	di,bp
    tiread_read:
	call	ogetc
	mov	es,dx
	jz	tiread_eof
	test	al,al
	jz	tiread_line	; binary file
	cmp	al,0Dh
	je	tiread_0Dh
	cmp	al,0Ah
	je	tiread_line
	cmp	al,09h
	je	tiread_tab
	cmp	di,[si].S_TINFO.ti_bcol
	je	tiread_maxlen
	stosb
	jmp	tiread_read
    tiread_0Dh:
	or	[si].S_TINFO.ti_flag,8000h ; _T_USECRLF
	jmp	tiread_read
    tiread_tab:
	cmp	usetab,0
	jne	tiread_do
	inc	usetab
	or	[si].S_TINFO.ti_flag,_T_MODIFIED
    tiread_do:
	mov	al,tab_c1
	stosb
	mov	al,tab_c2
	mov	cx,tetabsize
	dec	cl
	and	cx,TIMAXTABSIZE-1
    tiread_tloop:
	test	di,cx
	jz	tiread_read
	cmp	di,[si].S_TINFO.ti_bcol
	je	tiread_maxlen
	stosb
	jmp	tiread_tloop
    tiread_maxlen:			; line to big..
	mov	es:[di-1],ah
	call	tilineerror
    tiread_line:
	inc	bp
	mov	ax,bp
	call	tigetline
	jz	tiread_tobig
	xor	di,di
	jmp	tiread_read
    tiread_tobig:
	call	tireaderror		; file to big..
    tiread_error:
	mov	bp,-1
    tiread_eof:
	invoke	close,STDI.ios_file
	inc	bp
	mov	[si].S_TEDIT.ti_lcnt,bp
    tiread_end:
	test	bp,bp
	jz	@F
	mov	ax,[si].S_TINFO.ti_flag
	and	[si].S_TINFO.ti_flag,not (_T_USECRLF or 8000h)
	test	ax,8000h
	jz	@F
	or	[si].S_TINFO.ti_flag,_T_USECRLF
     @@:
	mov	ax,bp
	test	ax,ax
	pop	bp
	pop	bx
	pop	di
	pop	si
	ret
tiread	ENDP

topen PROC _CType PUBLIC USES si file:DWORD
	xor ax,ax
	.if tiopen()
	    mov si,ax
	    or [si].S_TINFO.ti_flag,_T_FILE
	    mov tinfo,ax
	    lodm file
	    .if ax
		invoke wlongpath,0,dx::ax
	    .else
		mov dx,ds
		mov ax,offset cp_noname
		inc [si].S_TEDIT.ti_lcnt ; set line count to 1
	    .endif
	    invoke strcpy,[si].S_TEDIT.ti_file,dx::ax
	    .if ax != offset cp_noname
		.if !tireadstyle()
		    invoke ermsg,0,addr CP_ENOMEM
		    jmp @F
		.endif
		mov ax,si
		call tiread
		.if ZERO?
		  @@:
		    mov ax,si
		    call ticlose
		    sub si,si
		.endif
	    .endif
	    mov ax,si
	.endif
	test ax,ax
	ret
topen ENDP

tclose PROC _CType PRIVATE USES bx
	mov ax,tinfo
	.if tistate()
	    mov bx,tinfo
	    .if [bx].S_TINFO.ti_flag & _T_MODIFIED
		.if tisavechanges()
		    mov ax,tinfo
		    call tiflush
		.endif
	    .endif
	    mov ax,tinfo
	    call ticlose
	    mov ax,tinfo
	.endif
	test ax,ax
	ret
tclose ENDP

tcloseall PROC _CType PUBLIC
	call	tclose
	jnz	tcloseall
	ret
tcloseall ENDP

;-----------------------------------------------------------------------------
; Open files
;-----------------------------------------------------------------------------

	.data

DLG_OpenFiles	dd ?
FCB_OpenFiles	dw ?
MAXDLGOBJECT	equ 16
MAXOBJECTLEN	equ 38

	.code

event_xcell:
	push	bx
	les	bx,DLG_OpenFiles
	xor	ax,ax
	mov	al,es:[bx].S_DOBJ.dl_index
	mov	bx,FCB_OpenFiles
	mov	[bx].S_LOBJ.ll_celoff,ax
	call	dlxcellevent
	pop	bx
	retx

event_list:
	push bp
	push si
	push di
	push bx
	invoke dlinit,DLG_OpenFiles
	les bx,DLG_OpenFiles
	add bx,S_TOBJ
	mov cx,MAXDLGOBJECT
	.repeat
	    or es:[bx].S_TOBJ.to_flag,_O_STATE
	    add bx,S_TOBJ
	.untilcxz
	mov bx,WORD PTR DLG_OpenFiles
	sub ax,ax
	mov al,es:[bx][4]
	add al,3
	mov si,ax		; x-pos
	mov al,es:[bx][5]
	add ax,1
	mov di,ax		; y
	xor bp,bp		; loop
	mov dx,es
	mov cx,bx
	.repeat
	    mov ax,bp
	    mov bx,FCB_OpenFiles
	    .break .if ax >= [bx].S_LOBJ.ll_numcel
	    add ax,[bx].S_LOBJ.ll_index
	    add ax,ax
	    les bx,[bx].S_LOBJ.ll_list
	    add bx,ax
	    mov bx,es:[bx]
	    .if [bx].S_TINFO.ti_flag & _T_MODIFIED
		mov ax,si
		dec ax
		invoke scputc,ax,di,1,'*'
	    .endif
	    invoke scpath,si,di,MAXOBJECTLEN,[bx].S_TEDIT.ti_file
	    add cx,S_TOBJ
	    mov es,dx
	    mov bx,cx
	    and es:[bx].S_TOBJ.to_flag,not _O_STATE
	    inc di
	    inc bp
	.until 0
	mov ax,1
	pop bx
	pop di
	pop si
	pop bp
	retx

tdlgopen PROC _CType PUBLIC USES si di bx
local ll:S_LOBJ
local ti[TIMAXFILES]:WORD
	lea	ax,ll
	mov	FCB_OpenFiles,ax
	invoke	memzero,ss::ax,S_LOBJ
	lea	ax,ti
	mov	WORD PTR ll.ll_list,ax
	mov	WORD PTR ll.ll_list+2,ss
	invoke	memzero,ss::ax,TIMAXFILES*2
	mov	ll.ll_dcount,MAXDLGOBJECT	; number of cells (max)
	movp	ll.ll_proc,event_list
	.if tigetfile()
	    mov si,ax
	    sub bx,bx
	    mov di,WORD PTR ll.ll_list
	    .repeat
		mov ax,si
		.break .if !tistate()
		mov [di],si
		add di,2
		mov si,[si].S_TEDIT.ti_next
		inc bx
	    .until bx == TIMAXFILES
	    mov ll.ll_count,bx
	    mov ax,bx
	    .if ax >= MAXDLGOBJECT
		mov ax,MAXDLGOBJECT
	    .endif
	    mov ll.ll_numcel,ax
	    .if rsopen(IDD_TEOpenFiles)
		stom DLG_OpenFiles
		mov  di,ax
		mov  cx,MAXDLGOBJECT
		mov  ax,offset event_xcell
		movl dx,cs
		.repeat
		    add	 di,S_TOBJ
		    stom es:[di].S_TOBJ.to_proc
		.untilcxz
		invoke dlshow,DLG_OpenFiles
		pushl  cs
		call   event_list
		invoke dllevent,DLG_OpenFiles,addr ll
		les   bx,DLG_OpenFiles
		mov    dx,es:[bx][4]
		les   bx,IDD_TEOpenFiles
		mov    es:[bx][6],dx
		invoke dlclose,DLG_OpenFiles
		mov ax,dx
		.if ax
		    sub ax,ax
		    mov bx,FCB_OpenFiles
		    .if [bx].S_LOBJ.ll_count
			mov ax,[bx].S_LOBJ.ll_index
			add ax,[bx].S_LOBJ.ll_celoff
			add ax,ax
			lea bx,ti
			add bx,ax
			mov ax,[bx]
		    .endif
		.endif
	    .endif
	.endif
	test ax,ax
	ret
tdlgopen ENDP

titogglemenus PROC PRIVATE
	mov ax,tinfo
	.if tistate()
	    push si
	    mov si,tinfo
	    invoke tihide,si
	    mov dx,WORD PTR [si].S_TEDIT.ti_DOBJ[4]
	    mov cx,WORD PTR [si].S_TEDIT.ti_DOBJ[6]
	    mov ax,[si].S_TINFO.ti_flag
	    xor ax,_T_USEMENUS
	    mov [si].S_TINFO.ti_flag,ax
	    and ax,_T_USEMENUS
	    .if !ZERO?
		mov al,dh
		inc al
		mov [si].S_TINFO.ti_ypos,ax
		mov al,ch
		dec al
		mov [si].S_TINFO.ti_rows,ax
	    .else
		mov al,dh
		mov [si].S_TINFO.ti_ypos,ax
		mov al,ch
		mov [si].S_TINFO.ti_rows,ax
	    .endif
	    invoke tishow,si
	    pop si
	.endif
	jmp ticontinue
titogglemenus ENDP

	.data
	cp_extbak db '.bak',0
	cp_exttmp db '.$$$',0

	.code

tistrip PROC PUBLIC USES si di ax cx
	push	ds
	mov	cx,tetabsize
	dec	cl
	and	cx,TIMAXTABSIZE-1
	mov	es,dx
	mov	ds,dx
	mov	si,ax
	mov	di,ax
	cld
	mov	ah,cl
	inc	ah
      @@:
	lodsb
	dec	ah
	jz	@F
	cmp	al,TITABCHAR
	je	@B
      @@:
	dec	si
    tistrip_lod:
	lodsb
	test	al,al
	jz	tistrip_eof
	cmp	al,9
	je	tistrip_09h
    tistrip_sto:
	stosb
	jmp	tistrip_lod
    tistrip_09h:
	stosb
	test	si,cx
	jz	tistrip_lod
	mov	ah,cl
	inc	ah
      @@:
	lodsb
	test	al,al
	jz	tistrip_eof
	cmp	al,9
	je	tistrip_09h
	cmp	al,TITABCHAR
	jne	tistrip_sto
	dec	ah
	jz	tistrip_sto
	jmp	@B
    tistrip_eof:
	stosb
    tistrip_end:
	pop	ds
	ret
tistrip ENDP

; strip space, BH and BL from end of line (DX:AX)
; uses CX, tinfo.ti_bcnt
; return CX strlen(line)

tistripl PROC PUBLIC USES si di bx bp
	mov	bp,tinfo
	push	es
	mov	si,ax
	invoke	strlen,dx::ax
	mov	di,si
	add	di,ax
	mov	cx,ax
	mov	ax,[bp].S_TINFO.ti_flag
	test	ax,_T_LINEBUF
	jz	tistripl_end
	and	ax,_T_USECONTROL
	jnz	tistripl_end
    tistripl_len:
	dec	di
	cmp	di,si
	jl	tistripl_end
	mov	al,es:[di]
	cmp	al,bl
	je	@F
	cmp	al,bh
	je	@F
	cmp	al,' '
	jne	tistripl_end
      @@:
	mov	es:[di],ah
	dec	cx
	jnz	tistripl_len
    tistripl_end:
	test	cx,cx
	mov	[bp].S_TINFO.ti_bcnt,cx
	mov	ax,si
	pop	es
	ret
tistripl ENDP

tistripline PROC PUBLIC USES bx
	call	ticurlp
	mov	bl,9
	mov	bh,TITABCHAR
	call	tistripl
	ret
tistripline ENDP

size_of_line	equ [bp-size_l]

; xchange line [AX] <--> [BP]
; size of line: [BP-2]
; uses DI
;
; while (getline(AX++))
;     xchange(AX, BP);
;
; return AX + 1 or -1

tixchgl PROC PRIVATE USES si
    tixchgl_get:
	push	ax
	call	tigetline
	mov	cx,size_of_line
	mov	es,dx
	mov	di,ax
	mov	si,bp
	jc	tixchgl_eof
      @@:
	mov	al,es:[di]
	movsb
	mov	[si-1],al
	dec	cx
	jnz	@B
	pop	ax
	inc	ax
	jmp	tixchgl_get
    tixchgl_eof:
	jz	tixchgl_end
      @@:
	mov	al,es:[di]
	movsb
	mov	[si-1],al
	dec	cx
	jnz	@B
	inc	cx
    tixchgl_end:
	pop	ax
	ret
tixchgl ENDP

; Insert a line below line[AX]

tinsline PROC PRIVATE USES si di bp
	mov	si,tinfo
	mov	bx,ax		; BX to line index
	mov	ax,[si].S_TINFO.ti_bcol
	sub	sp,ax		; create a line buffer on the stack
	mov	bp,sp		; buffer to BP
	push	ax
	invoke	memzero,ss::bp,ax
	mov	ax,[si].S_TEDIT.ti_lcnt ; room for one more line ?
	cmp	ax,[si].S_TINFO.ti_brow
	jae	tinsline_eof
	mov	ax,bx		; insert the blank line
	inc	ax
	call	tixchgl		; return index to last line
	cmp	ax,[si].S_TEDIT.ti_lcnt
	jne	tinsline_eof
	inc	[si].S_TEDIT.ti_lcnt
    tinsline_end:
	add	sp,[bp-size_l]; free buffer
	pop	cx		; line size
	test	ax,ax		; line count
	ret
    tinsline_eof:
	xor	ax,ax
	jmp	tinsline_end
	ret
tinsline ENDP

simove:				; move string to &string[1]
	lodsb
	cmp	si,cx		; CX max offset
	jae	simove_eof
	mov	[si-1],ah
	mov	ah,al
	test	al,al
	jnz	simove
	test	cx,cx
    simove_end:
	mov	[si],al ; terminate string
	ret
    simove_eof:
	xor	ax,ax
	jmp	simove_end

tiexpand PROC PUBLIC USES si di bp bx ax
	push	ds
	mov	bx,tetabsize
	mov	bp,tinfo
	test	[bp].S_TINFO.ti_flag,_T_USETABS
	jz	tiexpand_ret
	mov	es,dx
	mov	ds,dx
	dec	bl
	and	bx,TIMAXTABSIZE-1
	mov	si,ax
	mov	di,ax
	cld
	mov	cx,[bp].S_TINFO.ti_bcol
	dec	cx
    tiexpand_next:
	lodsb
	test	al,al
	jz	tiexpand_eos
	cmp	al,9
	je	tiexpand_09h
	cmp	di,cx
	je	tiexpand_end
	stosb
	jmp	tiexpand_next
    tiexpand_end:
	mov	al,0
	stosb
    tiexpand_ret:
	pop	ds
	ret
    tiexpand_eos:
	test	cx,cx
	jmp	tiexpand_end
    tiexpand_09h:		; insert TAB char
	stosb
	cmp	di,cx
	jae	tiexpand_end
      @@:			; insert "spaces" to next Tab offset
	mov	ah,TITABCHAR
	test	si,bx
	jz	tiexpand_next
	push	si
	call	simove
	pop	si
	jz	tiexpand_ret
	inc	si
	mov	di,si
	jmp	@B
tiexpand ENDP

tienterni PROC PUBLIC USES si di bp bx
	mov	si,tinfo
	mov	bx,[si].S_TINFO.ti_brow
	mov	ax,[si].S_TINFO.ti_loff
	add	ax,[si].S_TINFO.ti_yoff
	mov	di,ax
	inc	ax
	cmp	ax,bx
	mov	ax,_TI_RETEVENT
	jb	tienterni_do
	dec	bx
	jz	tienterni_end
    tienterni_nocando:
	call	tinocando
	jmp	tienterni_end
    tienterni_CONTINUE:
	mov	ax,_TI_CONTINUE
    tienterni_end:
	ret
    tienterni_do:
	mov	ax,di
	call	tinsline
	jz	tienterni_nocando
	mov	cx,[si].S_TINFO.ti_bcol
	or	[si].S_TINFO.ti_flag,_T_MODIFIED
	sub	sp,cx
	mov	bp,sp
	call	ticurcp
	push	dx
	push	ax
	invoke	strcpy,ss::bp,dx::ax
	pop	bx
	pop	es
	sub	ax,ax
	mov	es:[bx],al
	call	ticurlp
	mov	bx,ax
	sub	cx,cx
	mov	[si].S_TINFO.ti_boff,cx
	mov	[si].S_TINFO.ti_xoff,cx
     @@:
	mov	al,es:[bx]
	inc	cx
	inc	bx
	call	isspace
	jnz	@B
	mov	bl,al		; add indent if last char is zero
	mov	bh,0
	mov	ax,di
	inc	ax
	call	tigetline
	jz	tienterni_home
	mov	di,ax
	dec	cx
	jz	tienterni_home
	test	bl,bl
	jnz	tienterni_home
	mov	al,' '
	mov	es,dx
	mov	bx,cx
;	mov	[si].S_TINFO.ti_boff,0
	mov	[si].S_TINFO.ti_xoff,cx
	rep	stosb
    tienterni_push:
	mov	al,TITABCHAR
     @@:
	cmp	[bp],al
	jne	tienterni_cpy
	inc	bp
	jmp	@B
    tienterni_home:
	sub	bx,bx
	jmp	tienterni_push
    tienterni_cpy:
	invoke	strcpy,dx::di,ss::bp
	test	[si].S_TINFO.ti_flag,_T_USETABS
	jz	tienterni_done
	call	tistrip
	call	tiexpand
    tienterni_done:
	add	sp,[si].S_TINFO.ti_bcol
	call	tidown
	jmp	tienterni_end
if 0
	test	bx,bx
	jz	@F
	call	tidown
	call	tiprevword
	call	tinextword
	jmp	tienterni_end
      @@:
	call	tihome
	call	tidown
	jmp	tienterni_end
endif
tienterni ENDP

tienter_putc:
	mov	ax,[si].S_TINFO.ti_xoff
	add	ax,[si].S_TINFO.ti_boff
	push	ax
	mov	al,dl
	call	tiputc
	cmp	ax,_TI_CONTINUE
	pop	dx
	mov	ax,0
	jne	@F
	mov	ax,[si].S_TINFO.ti_xoff
	add	ax,[si].S_TINFO.ti_boff
	sub	ax,dx
      @@:
	test	ax,ax
	ret

tigetindent PROC PUBLIC
	push	si
	push	di
	mov	si,tinfo
	call	tigetline
	jz	tigetindent_end
	mov	es,dx
	mov	di,ax
	add	ax,[si].S_TINFO.ti_bcol
	mov	dx,ax
	xor	cx,cx
      @@:
	mov	al,es:[di]
	call	isspace
	jz	@F
	inc	cx
	inc	di
	cmp	di,dx
	jb	@B
      @@:
	mov	ax,cx
    tigetindent_end:
	pop	di
	pop	si
	ret
tigetindent ENDP

tienter PROC PUBLIC
	call	tidoiflines
	push	si
	push	di
	mov	si,tinfo
	call	tienterni
	cmp	ax,_TI_CONTINUE
	je	@F
	cmp	ax,_TI_RETEVENT
	je	tienter_ret
	jmp	tienter_end
     @@:
	mov	ax,[si].S_TINFO.ti_flag
	and	ax,_T_USEINDENT
	jz	tienter_end
	mov	ax,[si].S_TINFO.ti_loff
	add	ax,[si].S_TINFO.ti_yoff
	dec	ax
	call	tigetindent
if 0
	mov	dx,[si].S_TINFO.ti_xoff
	add	dx,[si].S_TINFO.ti_boff
	cmp	ax,dx
	jb	@F
	mov	ax,dx
     @@:
endif
	test	ax,ax
	jz	tienter_end
	mov	di,ax
	test	[si].S_TINFO.ti_flag,_T_OPTIMALFILL
	jz	tienter_space
     @@:
	cmp	di,8
	jb	tienter_space
	mov	dl,9
	call	tienter_putc
	jz	tienter_end
	cmp	di,ax
	jbe	tienter_end
	sub	di,ax
	jmp	@B
    tienter_space:
	mov	dl,' '
	call	tienter_putc
	jz	tienter_end
	dec	di
	jnz	tienter_space
    tienter_end:
	pop	di
	pop	si
	jmp	ticontinue
    tienter_ret:
	pop	di
	pop	si
	jmp	tiretevent
tienter ENDP

tioptimalfill PROC PRIVATE USES si bx cx
	mov	bl,9
	mov	bh,TITABCHAR
	call	tistripl
	mov	si,tinfo
	test	[si].S_TINFO.ti_flag,_T_LINEBUF
	jz	optimalfill_end
	test	[si].S_TINFO.ti_flag,_T_OPTIMALFILL
	jz	optimalfill_end
	test	[si].S_TINFO.ti_flag,_T_USETABS
	jz	optimalfill_end
	cmp	tetabsize,8
	jne	optimalfill_end
	cmp	cx,8
	jb	optimalfill_end
	push	ds
	push	ax
	mov	si,ax
	mov	ds,dx
	mov	es,dx
	mov	ah,0
    optimalfill_load:
	mov	bx,si
	lodsb
	cmp	al,39
	je	optimalfill_quote
	cmp	al,'"'
	je	optimalfill_quote
	cmp	al,' '
	jne	optimalfill_test
	test	ah,ah
	jnz	optimalfill_load
;	test	bx,7
;	jnz	optimalfill_load
      @@:
	lodsb
	cmp	al,' '
	je	@B
	mov	cx,si
	sub	cx,bx
	mov	si,bx
	lodsb
	cmp	cx,9
	jb	optimalfill_test
	xchg	bx,di
	mov	al,9
	stosb
	mov	al,TITABCHAR
	mov	cx,7
	rep	stosb
	mov	si,di
	mov	di,bx
	dec	si
    optimalfill_skip:
	lodsb
    optimalfill_test:
	test	al,al
	jnz	optimalfill_load
	pop	ax
	pop	ds
    optimalfill_end:
	ret
    optimalfill_quote:
	.if !ah
	    mov ah,al
	    jmp optimalfill_load
	.endif
	.if al == ah
	    mov ah,0
	.endif
	jmp optimalfill_load
tioptimalfill ENDP

tiflushl PROC PUBLIC USES si di bp
	;
	; Produce output to clipboard or file
	;
	; args: AX start line	?, 0
	;	DX start offset ?, 0
	;	CX end line	?, line count - 1 ?
	;	BX end offset	?, -1
	;
	mov	si,tinfo
	mov	bp,ax
	mov	di,dx
	call	tigetline
	jnz	@F
	jmp	tiflushl_eoi
     @@:
	jnc	@F		; CF set if string buffer
	test	[si].S_TINFO.ti_flag,_T_LINEBUF
	jnz	tiflushl_eoi	; else CF is EOF
     @@:
	call	tioptimalfill
	add	di,ax
	add	bx,ax
    tiflushl_loop:
	mov	es,dx
	inc	di
	mov	ax,[si].S_TINFO.ti_bcol
	cmp	bp,cx
	jne	@F
	mov	ax,bx
     @@:
	cmp	di,ax
	ja	tiflushl_eob
	mov	al,es:[di-1]
	or	al,al
	jz	tiflushl_eol
	cmp	al,9
	je	tiflushl_tab
    tiflushl_put:
	assert	al,0,jne,"tiflushl: al=0"
	call	oputc
	jnz	tiflushl_loop	; out of space..
    tiflushl_eof:
	xor	ax,ax
	stc
	jmp	tiflushl_end
    tiflushl_tab:
	mov	ah,TIMAXTABSIZE-1
     @@:
	mov	al,es:[di]
	cmp	al,TITABCHAR
	jne	tiflushl_putt
	inc	di
	dec	ah
	jnz	@B
    tiflushl_putt:
	mov	al,9
	jmp	tiflushl_put
    tiflushl_eob:		; end of selection buffer
	cmp	bp,cx		; break if last line
	je	tiflushl_eok
    tiflushl_eol:		; end of line
	inc	bp
	cmp	bp,cx
	ja	tiflushl_last	; break if last line (BP==CX)
	mov	ax,bp
	call	tigetline
	jbe	tiflushl_eoi	; break if last line (EOF)
	call	tioptimalfill
	mov	di,ax
	test	[si].S_TINFO.ti_flag,_T_USECRLF
	jz	@F		; insert line: 0D0A or 0A
	mov	al,0Dh
	call	oputc
     @@:
	mov	al,0Ah
	call	oputc
	jz	tiflushl_eof
	mov	ax,di
	jmp	tiflushl_loop
    tiflushl_eoi:		; end of input (CF)
	xor	ax,ax
	inc	ax
	stc
	jmp	tiflushl_end
    tiflushl_last:
	dec	bp
    tiflushl_eok:
	xor	ax,ax
	inc	ax
	clc
    tiflushl_end:		; out:	AX result
	mov	bx,di		;	DX line index
	mov	dx,bp		;	BX line offset
	ret
tiflushl ENDP

tisave	PROC PRIVATE
	mov  bx,ax
	test [bx].S_TINFO.ti_flag,_T_FILE
	jnz  tiflush
	jmp  ticontinue
tisave ENDP

tiflush PROC PRIVATE USES si di
local path[WMAXPATH]:BYTE
	mov si,ax
	lea di,path
	invoke strcpy,ss::di,[si].S_TEDIT.ti_file
	invoke setfext,ss::di,addr cp_exttmp
	.if sword PTR oopen(dx::ax,M_WRONLY) > 0
	    xor ax,ax
	    mov dx,ax
	    mov cx,[si].S_TEDIT.ti_lcnt
	    dec cx
	    mov bx,ax
	    dec bx
	    .if !tiflushl()
		invoke oclose,addr STDO
		invoke remove,ss::di
		xor di,di
	    .else
		call oflush
		invoke oclose,addr STDO
		.if [si].S_TINFO.ti_flag & _T_USEBAKFILE
		    invoke setfext,ss::di,addr cp_extbak
		    invoke remove,ss::di
		    invoke rename,[si].S_TEDIT.ti_file,ss::di
		    invoke setfext,ss::di,addr cp_exttmp
		.endif
		invoke remove,[si].S_TEDIT.ti_file
		invoke rename,ss::di,[si].S_TEDIT.ti_file
		inc ax
		mov di,ax
		and [si].S_TINFO.ti_flag,not _T_MODIFIED
		mov ax,si
		call tiftime
		stom [si].S_TEDIT.ti_time
	    .endif
	.else
	    sub di,di
	.endif
	mov  ax,di
	test ax,ax
	ret
tiflush ENDP

tilseek PROC PRIVATE USES bx
local DLG_TESeek:DWORD
	.if rsopen(IDD_TESeek)
	    stom DLG_TESeek
	    mov bx,tinfo
	    mov cx,[bx].S_TINFO.ti_loff
	    add cx,[bx].S_TINFO.ti_yoff
	    mov bx,ax
	    invoke sprintf,es:[bx][24],addr format_u,cx
	    invoke dlinit,DLG_TESeek
	    .if rsevent(IDD_TESeek,DLG_TESeek)
		les bx,DLG_TESeek
		invoke strtol,es:[bx][24]
		call tialigny
	    .endif
	    invoke dlclose,DLG_TESeek
	    call tiputs
	.endif
	sub ax,ax
	ret
tilseek ENDP

	.data
	;
	; These are characters used as valid identifiers (Alt-S)
	;
	idchars db '0123456789_?@abcdefghijklmnopqrstuvwxyz',0

	.code

tisearchfound PROC PRIVATE
	push	bx
	mov	ax,STDI.ios_l
	call	tialigny
	invoke	strlen,addr searchstring
	mov	dx,STDI.ios_i
	sub	dx,ax
	push	ax
	mov	ax,dx
	dec	ax
	call	tialignx
	call	ticurcp ; v2.38 - line may be short by 1
	pop	cx	; - the real reason is currently unknown..
	push	cx
	invoke	strnicmp,dx::ax,addr searchstring,cx
	jz	@F
	mov	bx,tinfo
	inc	[bx].S_TINFO.ti_loff
      @@:
	call	ticlipset
	pop	ax
	push	ax
	mov	bx,tinfo
	add	[bx].S_TINFO.ti_cleo,ax
	call	tiputs
	call	ticlipset
	pop	cx
	pop	bx
	jmp	ticontinue
tisearchfound ENDP

tisearch PROC PRIVATE
	call	titostdi
	call	ogetc
	invoke	cmdsearch,00010000h
	push	ax
	and	fsflag,not IO_SEARCHMASK
	mov	ax,STDI.ios_flag
	and	al,IO_SEARCHMASK
	or	BYTE PTR fsflag,al
	pop	ax
	test	ax,ax
	jnz	tisearchfound
	jmp	ticontinue
tisearch ENDP

ticontinuesearch PROC PRIVATE
	call	titostdi
	and	STDI.ios_flag,not (IO_SEARCHSET or IO_SEARCHCUR)
	call	continuesearch
	test	ax,ax
	jnz	tisearchfound
	inc	ax
	ret
ticontinuesearch ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

ID_YES	equ	1
ID_ALL	equ	2
ID_NO	equ	3

iddreplaceprompt PROC PRIVATE
	mov ax,1
	mov bx,tinfo
	.if [bx].S_TINFO.ti_flag & _T_PROMPTONREP
	    .if rsmodal(IDD_ReplacePrompt)
		mov dx,ax
		.if ax
		    dec dx
		.endif
		mov bx,WORD PTR IDD_ReplacePrompt
		mov [bx].S_ROBJ.rs_index,dl
		mov bx,tinfo
		.if ax == ID_ALL
		    xor [bx].S_TINFO.ti_flag,_T_PROMPTONREP
		.endif
	    .endif
	.endif
	test ax,ax
	ret
iddreplaceprompt ENDP

ID_OLDSTRING	equ 1*16
ID_NEWSTRING	equ 2*16
ID_USECASE	equ 3*16
ID_PROMPT	equ 4*16
ID_CURSOR	equ 5*16
ID_GLOBAL	equ 6*16
ID_OK		equ 7
ID_CHANGEALL	equ 8

iddreplace PROC pascal PRIVATE USES bx sflag:size_t
local	DLG_Replace:DWORD
	.if rsopen(IDD_Replace)
	    stom DLG_Replace
	    mov es:[bx].S_TOBJ.to_count[ID_OLDSTRING],128 shr 4
	    mov es:[bx].S_TOBJ.to_count[ID_NEWSTRING],128 shr 4
	    mov dx,ds
	    mov ax,offset searchstring
	    stom es:[bx].S_TOBJ.to_data[ID_OLDSTRING]
	    mov	 ax,offset replacestring
	    stom es:[bx].S_TOBJ.to_data[ID_NEWSTRING]
	    mov ax,sflag
	    mov dl,_O_FLAGB
	    .if ax & IO_SEARCHCASE
		or es:[bx][ID_USECASE],dl
	    .endif
	    .if ax & _T_PROMPTONREP
		or es:[bx][ID_PROMPT],dl
	    .endif
	    mov dl,_O_RADIO
	    .if ax & IO_SEARCHCUR
		or es:[bx][ID_CURSOR],dl
	    .else
		or es:[bx][ID_GLOBAL],dl
	    .endif
	    invoke dlinit,DLG_Replace
	    .if rsevent(IDD_Replace,DLG_Replace)
		mov ax,sflag
		and ax,not (IO_SEARCHMASK or _T_PROMPTONREP)
		mov dl,_O_FLAGB
		.if es:[bx][ID_USECASE] & dl
		    or ax,IO_SEARCHCASE
		.endif
		.if es:[bx][ID_PROMPT] & dl
		    or ax,_T_PROMPTONREP
		.endif
		.if BYTE PTR es:[bx][ID_CURSOR] & _O_RADIO
		    or ax,IO_SEARCHCUR
		.else
		    or ax,IO_SEARCHSET
		.endif
		mov dx,ax
		xor ax,ax
		.if searchstring != al
		    .if replacestring != al
			inc ax
		    .endif
		.endif
	    .endif
	    push dx
	    invoke dlclose,DLG_Replace
	    mov ax,dx
	    pop dx
	.endif
	test ax,ax
	ret
iddreplace ENDP

tireplace PROC PRIVATE USES si di bx
	mov si,tinfo
	mov ax,_T_PROMPTONREP
	or  [si].S_TINFO.ti_flag,ax
	mov ax,fsflag
	and al,IO_SEARCHMASK
	.if iddreplace(ax)
	    and fsflag,not IO_SEARCHMASK
	    or	BYTE PTR fsflag,dl
	    .if ax == ID_CHANGEALL || !(dx & _T_PROMPTONREP)
		and [si].S_TINFO.ti_flag,not _T_PROMPTONREP
	    .endif
	    .if !ticontinuesearch()
		jmp @F
		.repeat
		    call titostdi
		    and STDI.ios_flag,not (IO_SEARCHSET or IO_SEARCHCUR)
		    .break .if !continuesearch()
		    call tisearchfound
		    @@:
		    mov di,cx
		    .break .if !iddreplaceprompt()
		    .if ax != ID_NO
			add  [si].S_TINFO.ti_cleo,di	; select text
			call ticlipdel			; delete text
			mov  di,offset replacestring	; add new text
			.repeat
			    mov al,[di]
			    inc di
			    .break .if !al
			    call tiputc
			.until 0
		    .else
			call ticontinuesearch
		    .endif
		.until 0
	    .endif
	.endif
	call tiputs
	xor ax,ax
	ret
tireplace ENDP

idtestal:
	push	es
	push	di
	push	cx
	push	ax
	cmp	al,'A'
	jb	@F
	cmp	al,'Z'
	ja	@F
	or	al,20h
      @@:
	push	ds
	pop	es
	mov	di,offset idchars
	mov	cx,sizeof idchars
	cld
	repne	scasb
	cmp	BYTE PTR [di-1],0
	pop	ax
	pop	cx
	pop	di
	pop	es
	ret

tisearchxy PROC pascal PRIVATE USES si di bx
local	linebuf[128]:BYTE
	call	cursorx		; get cursor x,y pos
	mov	di,ax
	mov	bx,dx
	inc	di		; to start of line..
      @@:
	dec	di		; moving left seeking a valid character
	jz	@F
	invoke	getxyc,di,bx
	call	idtestal
	jz	@B
	mov	ax,di
	dec	ax
	invoke	getxyc,ax,bx
	call	idtestal
	jnz	@B
      @@:
	lea	si,linebuf
	mov	cx,32
	xor	ax,ax
      @@:
	invoke	getxyc,di,bx
	inc	di
	call	idtestal
	jz	@F
	mov	[si],al
	inc	si
	dec	cx
	jnz	@B
      @@:
	sub	ax,ax
	mov	[si],al
	mov	al,linebuf
	test	al,al
	jz	@F
	invoke	strcpy,addr searchstring,addr linebuf
	call	tisearch
      @@:
	ret
tisearchxy ENDP

;-----------------------------------------------------------------------------
; Event handler
;-----------------------------------------------------------------------------

	.data

te_keytable label size_t
	dw KEY_F1,	__F1		; Help
	dw KEY_F2,	__F2		; Save file
	dw KEY_F3,	tisearch	; Search
	dw KEY_F4,	tireplace	; Replace
	dw KEY_F6,	__F6
  ifdef __DZ__
	dw KEY_F8,	__F8
	dw KEY_F9,	__F9
	dw KEY_ESC,	__Esc		; Exit - leave files open
	dw KEY_ALTX,	__AltX		; Exit - Close all files
	dw KEY_CTRLX,	__CtrlX		; Close current file
  else
	dw KEY_F9,	__AltX
	dw KEY_ESC,	__AltX
	dw KEY_ALTX,	__AltX
	dw KEY_CTRLX,	__AltX
  endif
	dw KEY_F11,	titogglemenus	; Zoom (Ctrl-M)
	dw KEY_CTRLF2,	__CtrlF2	; Save as
	dw KEY_CTRLF6,	__CtrlF9	; Options
	dw KEY_CTRLF9,	__CtrlF9	; Options

	dw KEY_CTRLA,	__CtrlA		; Select All
	dw KEY_CTRLB,	__CtrlB		; User screen
	dw KEY_CTRLF,	__CtrlF		; Optimal fill on/off
	dw KEY_CTRLG,	tilseek		; Goto line
	dw KEY_CTRLI,	__CtrlI		; Autoindent on/off
	dw KEY_CTRLL,	__CtrlL		; Search again
	dw KEY_CTRLM,	titogglemenus	; Toggle menus on/off
	dw KEY_CTRLO,	__CtrlB		;
	dw KEY_ALTR,	__CtrlR		; Reload file
	dw KEY_CTRLS,	__CtrlS		; Toggle style on/off
	dw KEY_CTRLT,	__CtrlT		; Tabs mode on/off
	dw KEY_ALTL,	tilseek		;
	dw KEY_ALTS,	tisearchxy	; Word search
	dw KEY_ALT0,	__Alt0		; Window List
	tekeycount equ (($ - offset te_keytable) / (size_l * 2))

.code

tioption:
	call teoption
	mov bx,tinfo
	mov ax,[bx].S_TINFO.ti_flag
	mov cx,teflag
	mov dx,ax
	and ax,not _T_TECFGMASK
	or  ax,cx
	mov [bx].S_TINFO.ti_flag,ax
	mov ax,dx
	and ax,_T_USETABS
	and cx,_T_USETABS
	.if ax != cx
	    mov ax,1
	    .if dx & _T_MODIFIED
		.if tisavechanges()
		    mov ax,tinfo
		    call tiflush
		.endif
	    .endif
	    .if ax
		call __CtrlR
	    .endif
	.endif
	retx

__CtrlF9:
	pushl	cs
	call	tioption
	jmp	ticontinue

__F1:
  ifdef __DZ__
	mov  ax,HELPID_05
	call view_readme
  else
	invoke rsmodal,IDD_TEHelp
  endif
	jmp ticontinue

__F2:
	mov  ax,tinfo
	call tisave
	jmp  ticontinue

__F6:
	.if tigetfile()
	    mov bx,tinfo
	    .if [bx].S_TEDIT.ti_next
		mov ax,[bx].S_TEDIT.ti_next
	    .endif
	    jmp titogglefile
	.endif
	ret

titogglefile:
	push si
	push di
	mov di,ax
	mov si,tinfo
	.if di != si
	    .if [di].S_TINFO.ti_flag & _T_MALLOC or _T_EMMBUF
		invoke tihide,si
		mov tinfo,di
		invoke tishow,di
	    .endif
	.endif
	pop di
	pop si
	jmp ticontinue

ifdef DEBUG
SHOWTINFO equ 1
endif
ifdef SHOWTINFO

	.data
	extrn _dsstack:WORD
	tformat label BYTE
	db "%8u line count",10
	db "%8u EMM handle",10
	db "%8u EMM page  ",10
	db "%08lX file name ",10
	db "%8X Stack top  ",10
	db "%8X SP         ",10
	db "%8lu file size ",10
	db "%8X next file ",10
	db "%8X prev file ",10
	db "%08lX style ptr ",10
	db 0
	.code

__Alt0:
	.if tdlgopen()
	    push si
	    mov si,ax
	    mov ax,sp
	    invoke ermsg,0,addr tformat,
		[si].S_TEDIT.ti_lcnt,
		[si].S_TEDIT.ti_emmh,
		[si].S_TEDIT.ti_emmp,
		[si].S_TEDIT.ti_file,
		offset _dsstack,
		ax,
		[si].S_TEDIT.ti_size,
		[si].S_TEDIT.ti_next,
		[si].S_TEDIT.ti_prev,
		[si].S_TEDIT.ti_style
	    mov ax,si
	    pop si
	    jmp titogglefile
	.endif
	ret
else
__Alt0:
	.if tdlgopen()
	    jmp titogglefile
	.endif
	ret
endif

__CtrlF2:
	mov bx,tinfo
	invoke strcpy,addr _bufin,[bx].S_TEDIT.ti_file
	invoke strfn,dx::ax
	.if ax != offset _bufin
	    mov bx,ax
	    mov BYTE PTR [bx-1],0
	.endif
	.if wdlgopen(addr _bufin,dx::ax,0)
	    mov bx,tinfo
	    invoke strcpy,[bx].S_TEDIT.ti_file,dx::ax
	    mov ax,tinfo
	    call tiflush
	    mov bx,tinfo
	    xor [bx].S_TINFO.ti_flag,_T_USEMENUS
	    call titogglemenus
	.endif
	sub ax,ax
	ret

__CtrlA:
	call tiselectall
	call tiseto
	jmp  titoggleupdate

__CtrlB:
	call consuser
	sub  ax,ax
	ret

__CtrlI:
	mov ax,_T_USEINDENT
	jmp @F
__CtrlF:
	mov ax,_T_OPTIMALFILL
	jmp @F
__CtrlS:
	mov ax,_T_USESTYLE
	jmp @F
__CtrlT:
	mov ax,_T_SHOWTABS
      @@:
	mov bx,tinfo
	xor [bx].S_TINFO.ti_flag,ax
	jmp titoggleupdate

__CtrlL:
	call	ticontinuesearch
	jmp	ticontinue

titoggleupdate:
	call	tiputs
	jmp	ticontinue

__CtrlR:
	push	bx
	mov	bx,tinfo
	test	[bx].S_TINFO.ti_flag,_T_MODIFIED
	pop	bx
	jz	@F
	invoke	rsmodal,IDD_TEReload2
	jnz	@F
	jmp	ticontinue
      @@:
	mov	ax,tinfo
	call	timemzero
	mov	curh,-1		; v2.47 - update page on read
	mov	ax,tinfo
	call	tiread
	jz	@F
	call	tiseto
	call	tiputs
	jmp	ticontinue
      @@:
	mov	di,KEY_ESC
	dec	ax
	ret

ifdef __DZ__

tisavefiles	PROTO _CType
tiloadfiles	PROTO _CType

__F8:
	call	tisavefiles
	ret

__F9:
	call	tiloadfiles
	ret

	;------------------------------------------
	; Close window and exit -- leave files open
	;------------------------------------------
__Esc:
	mov ax,tinfo
	.if ax
	    xchg ax,bx
	    test [bx].S_TINFO.ti_flag,_T_EMMBUF
	    xchg ax,bx
	    .if !ZERO?
		invoke tihide,ax
		mov ax,_TI_RETEVENT
		ret
	    .endif
	.endif

	;----------------------------------------
	; Close current file -- exit if last file
	;----------------------------------------
__CtrlX:
	call	tclose
	mov	ax,_TI_RETEVENT
	jz	@F
	mov	ax,tinfo
	test	ax,ax
	jz	@F
	invoke	tishow,ax
	mov	ax,_TI_CONTINUE
      @@:
	ret
endif
	;-----------------------------
	; Close all open files -- exit
	;-----------------------------
__AltX:
	call tcloseall
	mov  ax,_TI_RETEVENT
	ret


	.data
	cp_tionfo	db ' col %-3u ln %-5u',0
	tiupdate_line	dw -1
	tiupdate_offs	dw -1

	.code

timenus PROC PRIVATE
	push si
	mov si,tinfo
	mov ax,si
	.if tistate()
	    .if dl & _D_ONSCR && cx & _T_USEMENUS
		mov  bx,ax
		mov  ax,[si].S_TINFO.ti_loff
		add  ax,[si].S_TINFO.ti_yoff
		inc  ax
		push ax
		mov  ax,[si].S_TINFO.ti_xoff
		add  ax,[si].S_TINFO.ti_boff
		push ax
		mov  ax,es:[bx][4]
		add  al,es:[bx].S_DOBJ.dl_rect.rc_col
		sub  al,18
		mov  cl,ah
		invoke scputf,ax,cx,0,0,addr cp_tionfo
		add sp,size_l*2
		mov ax,' '
		.if [si].S_TINFO.ti_flag & _T_MODIFIED
		    mov al,'*'
		.endif
		invoke scputw,0,cx,1,ax
	    .endif
	.endif
	pop si
	xor ax,ax
	ret
timenus ENDP

tiftime PROC PRIVATE USES si
	local ft:S_FTIME
	push di
	mov si,ax
	sub ax,ax
	mov ft.ft_time,ax
	mov ft.ft_date,ax
	.if osopen([si].S_TEDIT.ti_file,0,M_RDONLY,A_OPEN) != -1
	    mov di,ax
	    invoke getftime,di,addr ft
	    invoke close,di
	.else
	    or [si].S_TINFO.ti_flag,_T_MODIFIED
	.endif
	lodm ft
	test ax,ax
	pop di
	ret
tiftime ENDP

teevent PROC PRIVATE USES si di bx
	call tiseto
	call tiputs
	.repeat
	    mov ax,tinfo
	    mov si,ax
	    .if [si].S_TINFO.ti_flag & _T_MODIFIED
		.if tiftime()
		    .if ax != WORD PTR [si].S_TEDIT.ti_time
			.if rsmodal(IDD_TEReload)
			    mov	 ax,si
			    call timemzero
			    mov	 curh,-1	; v2.48 - update page on read
			    mov	 ax,si
			    call tiread
			    mov	 di,KEY_ESC
			    .break .if ZERO?
			    call tiseto
			    call tiputs
			.endif
		    .endif
		.endif
	    .endif
	    call timenus
	    call tgetevent
	    mov	 di,ax
	    xor	 bx,bx
	    mov	 cx,tekeycount
	    .repeat
		.if ax == te_keytable[bx]
		    xor ax,ax
		    .break
		.endif
		add bx,size_l*2
	    .untilcxz
	    .if ax
	      ifdef __CLIP__
		call ticlipevent
	      endif
		call tievent
		mov  si,ax
	    .else
		call te_keytable[bx+size_l]
		.continue .if ax == _TI_CONTINUE
		.break
	    .endif
	    call tiseto
	    call tiputs
	.until 0
	mov ax,di
	ret
teevent ENDP

tiupdate:
	push si
	mov si,tinfo
	mov ax,si
	.if tistate()
	    .if dl & _D_ONSCR && cx & _T_USEMENUS
		mov ax,[si].S_TINFO.ti_loff
		add ax,[si].S_TINFO.ti_yoff
		mov dx,[si].S_TINFO.ti_xoff
		add dx,[si].S_TINFO.ti_boff
		.if ax != tiupdate_line || dx != tiupdate_offs
		    mov tiupdate_offs,dx
		    mov tiupdate_line,ax
		    call timenus
		.endif
	    .endif
	.endif
	pop si
	xor ax,ax
	retx

tmodal PROC _CType PUBLIC USES si di bx
local cursor:S_CURSOR
local update:DWORD
local ftime:DWORD
	.repeat
	    call mousep
	.until ZERO?
	mov ax,tinfo
	mov si,ax
	.if tistate()
	    movmx update,tupdate
	    movp tupdate,tiupdate
	    invoke cursorget,addr cursor
	    invoke tishow,si
	    mov ax,si
	    call tiftime
	    stom ftime
	    call teevent
	    mov di,ax
	    mov ax,tinfo
	    .if si == ax
		call tiftime
		mov si,WORD PTR ftime
		sub si,ax
	    .else
		mov si,0
	    .endif
	    mov ax,WORD PTR update
	    mov WORD PTR tupdate,ax
	    movl ax,WORD PTR update+2
	    movl WORD PTR tupdate+2,ax
	    invoke cursorset,addr cursor
	    mov dx,si		; zero if not modified
	    mov ax,di		; returned key value
	    test ax,ax
	.endif
	ret
tmodal ENDP

tedit PROC _CType PUBLIC fname:DWORD, line:size_t
	.if topen(fname)
	    mov ax,line
	    call tialigny
	    call tmodal
	.endif
	ret
tedit ENDP
endif
	END
