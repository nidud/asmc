; TICLIPB.ASM--
; Copyright (C) 2015 Doszip Developers

include libc.inc
ifdef __CLIP__
include clip.inc
include keyb.inc
include string.inc
include iost.inc
include mouse.inc
include conio.inc
include tinfo.inc
include alloc.inc

externdef	IDD_ClipboardWarning:DWORD

tigetline	PROTO
tiremline	PROTO
tidelete	PROTO
tiseto		PROTO
ticontinue	PROTO
tiflushl	PROTO
tiputc		PROTO
tievent		PROTO
;
; Cut		Shift-Del	Ctrl-X
; Copy		Ctrl-Ins	Ctrl-C
; Paste		Shift-Ins	Ctrl-V
; Clear		Del		Ctrl-Del
;

	.code

tiselected PROC PUBLIC USES bx
	mov	bx,tinfo
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

ticlipdel PROC PUBLIC USES si di bx
	invoke	tiselected
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
    ticlipdel_set:
	call	tiseto
	call	ticlipset
	sub	ax,ax
	inc	ax
    ticlipdel_end:
	ret
ticlipdel ENDP

ticlipcut PROC PUBLIC USES si di
	mov	si,tinfo
	mov	di,ax			; AX: Copy == 0, Cut == 1
	call	tiselected		; get size of selection
	jz	ticlipcut_set
	mov	cx,ax
	lodm	[si].S_TINFO.ti_bp
	add	ax,[si].S_TINFO.ti_clso
	invoke	ClipboardCopy,dx::ax,cx
	test	di,di
	jz	ticlipcut_set
	call	ticlipdel
    ticlipcut_set:
	call	ticlipset
    ticlipcut_eof:
	sub	ax,ax
	ret
ticlipcut ENDP

ticlipget PROC PUBLIC USES si di bx
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
	push	[si].S_TINFO.ti_xoff
	push	[si].S_TINFO.ti_boff
	mov	si,clipbsize
	mov	di,ax
	mov	es,dx
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
	jmp	ticlipevent_nul
    ticlipevent_MOVEBACK:
	mov	[bx].S_TINFO.ti_clso,ax
    ticlipevent_nul:
	xor	ax,ax
	jmp	ticlipevent_end
ticlipevent ENDP

endif ; __CLIP__

	END
