; DLEVENT.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include keyb.inc
include mouse.inc
include dos.inc

scroll_delay	PROTO _CType

	PUBLIC	tdialog
	PUBLIC	tdllist

	.data
	tdialog dd ?
	tdllist dd ?
	tdoffss dw ?
	ocurs	S_CURSOR <?>
	tobjp	dd ?
	oflag	dw ?
	orect	dd ?
	oxpos	dw ?
	oypos	dw ?
	oxlen	dw ?
	event	dw ?
	result	dw ?
	dlexit	dw ?
	xlbuf	dw 80 dup(?)

	_scancodes label BYTE	;  A - Z
	db 1Eh,30h,2Eh,20h,12h,21h,22h,23h,17h,24h,25h,26h,32h
	db 31h,18h,19h,10h,13h,1Fh,14h,16h,2Fh,11h,2Dh,15h,2Ch

	proctab label size_t
	dw case_ESC
	dw case_ESC
  ifndef SKIP_ALTMOVE
	dw case_ALTUP
	dw case_ALTDN
	dw case_ALTLEFT
	dw case_ALTRIGHT
  endif
	dw case_ENTER
	dw case_ENTER
  ifdef __MOUSE__
	dw cmdmouse
  endif
	dw case_LEFT
	dw case_UP
	dw case_RIGHT
	dw case_DOWN
	dw case_HOME
	dw case_END
	dw case_TAB
	dw case_PGUP
	dw case_PGDN

	keytable label size_t
	dw KEY_ESC
	dw KEY_ALTX
  ifndef SKIP_ALTMOVE
	dw KEY_ALTUP
	dw KEY_ALTDN
	dw KEY_ALTLEFT
	dw KEY_ALTRIGHT
  endif
	dw KEY_ENTER
	dw KEY_KPENTER
  ifdef __MOUSE__
	dw MOUSECMD
  endif
	dw KEY_LEFT
	dw KEY_UP
	dw KEY_RIGHT
	dw KEY_DOWN
	dw KEY_HOME
	dw KEY_END
	dw KEY_TAB
	dw KEY_PGUP
	dw KEY_PGDN
	key_count = ($ - offset keytable) / size_l

	eventproc label size_t
	dw dlpbuttevent
	dw dlradioevent
	dw dlcheckevent
	dw dlxcellevent
	dw dlteditevent
	dw dlmenusevent
	dw dlxcellevent

	.code

dummy_update:
	xor ax,ax
	ret

tdshortkey:
	push ax
	.if es:[bx].S_TOBJ.to_flag & _O_DEACT || !es:[bx].S_TOBJ.to_ascii
	    sub ax,ax
	.else
	    and al,0DFh
	    .if es:[bx].S_TOBJ.to_ascii == al
		or al,1
	    .else
		mov al,es:[bx].S_TOBJ.to_ascii
		and al,0DFh
		sub al,'A'
		push bx
		sub bx,bx
		mov bl,al
		cmp ah,[bx+_scancodes]
		pop bx
		.if ZERO?
		    or al,1
		.else
		    sub ax,ax
		.endif
	    .endif
	.endif
	pop ax
	ret

handle_event:
	test	ax,ax
	jnz	handle_event_do
	ret
    handle_event_do:
	push	si
	push	di
	xor	dx,dx
	mov	si,dx
	mov	cx,dx
	les	bx,tdialog
	mov	cl,es:[bx].S_DOBJ.dl_count
	les	bx,es:[bx].S_DOBJ.dl_object
	cmp	ax,KEY_F1
	je	handle_event_help
	test	cl,cl
	jz	handle_event_null
    handle_event_loop:
	test	es:[bx].S_TOBJ.to_flag,_O_GLCMD
	jz	handle_event_shkey
	mov	dx,WORD PTR es:[bx].S_TOBJ.to_data
	mov	di,WORD PTR es:[bx].S_TOBJ.to_data+2
    handle_event_shkey:
	call	tdshortkey
	jnz	handle_event_si_to_index
	add	bx,16
	inc	si
	dec	cx
	jnz	handle_event_loop
	test	dx,dx
	jz	handle_event_null
	mov	bx,dx
	mov	es,di
    handle_event_gloop:
	cmp	es:[bx].S_GLCMD.gl_key,0
	jz	handle_event_null
	cmp	es:[bx].S_GLCMD.gl_key,ax
	je	handle_event_found
	add	bx,SIZE S_GLCMD
	jmp	handle_event_gloop
    handle_event_found:
	call	es:[bx].S_GLCMD.gl_proc
	jmp	handle_event_end
    handle_event_null:
	sub	ax,ax
	jmp	handle_event_end
    handle_event_si_to_index:
	test	es:[bx].S_TOBJ.to_flag,_O_PBKEY
	mov	ax,si
	les	bx,tdialog
	mov	es:[bx].S_DOBJ.dl_index,al
	mov	ax,_C_RETURN
	jnz	handle_event_end
    handle_event_one:
	mov	ax,_C_NORMAL
    handle_event_end:
	mov	result,ax
	pop	di
	pop	si
	ret
    handle_event_help:
	xor	ax,ax
	les	bx,tdialog
	test	es:[bx].S_DOBJ.dl_flag,_D_DHELP
	jz	handle_event_end
	cmp	WORD PTR thelp,ax
	jz	handle_event_end
	call	thelp
	mov	ax,_C_NORMAL
	jmp	handle_event_end

test_event:
	sub	bx,bx
    test_event_loop:
	cmp	ax,keytable[bx]
	je	test_event_found
	add	bx,size_l
	dec	cx
	jnz	test_event_loop
	call	handle_event
	ret
    test_event_found:
	call	proctab[bx]
	ret

LoadCurrentObjectSaveCursor:
	push	ax
	invoke	cursorget,addr ocurs
	pop	ax

LoadCurrentObject:
	les	bx,tdialog
	cmp	es:[bx].S_DOBJ.dl_count,0
	jne	@F
	sub	ax,ax
	ret
      @@:
	test	ax,ax
	jnz	@F
	mov	al,es:[bx].S_DOBJ.dl_index
	inc	ax
      @@:
	mov	dx,es:[bx]+4
	les	bx,es:[bx].S_DOBJ.dl_object
	dec	ax
	shl	ax,4
	add	ax,bx
	mov	WORD PTR tobjp,ax
	mov	WORD PTR tobjp+2,es
	mov	bx,ax
	mov	ax,es:[bx].S_DOBJ.dl_flag
	mov	oflag,ax
	movmx	orect,es:[bx].S_TOBJ.to_rect
	add	WORD PTR orect,dx
	and	ax,0FFh
	add	al,dl
	mov	oxpos,ax
	mov	al,orect.S_RECT.rc_y
	mov	oypos,ax
	mov	al,orect.S_RECT.rc_col
	mov	oxlen,ax
	mov	ax,es:[bx].S_TOBJ.to_flag
	ret

ifdef __MOUSE__
omousecmd:
	call	mousex
	push	ax
	call	mousey
	pop	dx
	cmp	ax,oypos
	jne	omousecmd_nil
	mov	ax,oxpos
	dec	ax
	cmp	dx,ax
	jb	omousecmd_nil
	add	ax,2
	cmp	dx,ax
	jbe	omousecmd_one
    omousecmd_nil:
	sub	al,al
	mov	ax,MOUSECMD
	ret
    omousecmd_one:
	or	al,1
	ret
endif

ExecuteChild:
	inc ax
	call LoadCurrentObject
	.if WORD PTR es:[bx].S_TOBJ.to_proc != 0
	    call es:[bx].S_TOBJ.to_proc
	    mov result,ax
	    .if ax == _C_REOPEN
		les bx,tdialog
		mov al,es:[bx].S_DOBJ.dl_index
		push ax
		invoke dlinit,tdialog
		pop ax
		les bx,tdialog
		mov es:[bx].S_DOBJ.dl_index,al
	    .endif
	.endif
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

?item_init:
	pop	ax
	push	ds
	push	si
	push	di
	push	bx
	lds	si,tdialog
	les	di,[si].S_DOBJ.dl_object
	sub	cx,cx
	sub	dx,dx
	mov	dl,[si].S_DOBJ.dl_count
	add	cl,[si].S_DOBJ.dl_index
	jmp	ax

item_SetIndex?:
	mov ax,es:[di]	;.S_TOBJ.to_flag
	.if ax & _O_DEACT
	    sub ax,ax
	    ret
	.endif
	;
item_SetIndex:
	dec cx
	mov [si].S_DOBJ.dl_index,cl
	sub ax,ax
	inc ax
	ret

item_DoIfIndex:
	call item_SetIndex?
	.if ZERO?
	    ret
	.endif
	pop bx
	jmp ?item_exit

previtem:
	call ?item_init
	.if !ZERO?
	    mov ax,cx
	    dec ax
	    shl ax,4
	    add di,ax
	    .repeat
		call item_SetIndex?
		.break .if !ZERO?
		sub di,SIZE S_TOBJ
	    .untilcxz
	    .if !ax
	     @@:
		.if dl
		    mov cx,dx
		    mov bl,[si].S_DOBJ.dl_index
		    mov di,WORD PTR [si].S_DOBJ.dl_object
		    mov ax,cx
		    dec ax
		    shl ax,4
		    add di,ax
		    sub ax,ax
		    .repeat
			.break .if bl > cl
			mov ax,es:[di].S_TOBJ.to_flag
			.if !(ax & _O_DEACT)
			    call item_SetIndex
			    jmp ?item_exit
			.endif
			sub di,SIZE S_TOBJ
		    .untilcxz
		.endif
		jmp ?item_null
	    .endif
	    jmp ?item_exit
	.else
	    jmp @B
	.endif
	jmp ?item_null

itemleft:
	call ?item_init
	.if !ZERO?
	    mov ax,cx
	    dec ax
	    shl ax,4
	    add di,ax
	    mov bx,es:[di][20]
	    .repeat
		.if bl > es:[di][4] && bh != es:[di][5]
		    call item_DoIfIndex
		.endif
		sub di,16
	    .untilcxz
	.endif

?item_null:
	sub	ax,ax
?item_exit:
	pop	bx
	pop	di
	pop	si
	pop	ds
	ret

nextitem:
	call	?item_init
	inc	cx
	mov	ax,cx
	shl	ax,4
	add	di,ax
	inc	cx
      @@:
	cmp	cx,dx
	ja	@F
	call	item_DoIfIndex
	inc	cx
	add	di,16
	jmp	@B
      @@:
	sub	dx,dx
	mov	dl,[si].S_DOBJ.dl_index
	inc	dx
	mov	cx,1
	mov	di,WORD PTR [si].S_DOBJ.dl_object
      @@:
	cmp	cx,dx
	ja	?item_null
	call	item_DoIfIndex
	inc	cx
	add	di,16
	jmp	@B

itemright:
	call	?item_init
	inc	cx
	mov	ax,cx
	shl	ax,4
	add	di,ax
	mov	bx,es:[di-12]
	inc	cx
    itemright_loop:
	cmp	cx,dx
	ja	?item_null
	cmp	bh,es:[di][5]
	jne	@F
	cmp	bl,es:[di][4]
	jnb	@F
	call	item_DoIfIndex
      @@:
	inc	cx
	add	di,16
	jmp	itemright_loop

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

xbuttxchg:
	invoke	getxyc,oxpos,oypos
	xchg	si,ax
	invoke	scputc,oxpos,oypos,1,ax
	mov	ax,oxpos
	add	ax,oxlen
	dec	ax
	push	ax
	invoke	getxyc,ax,oypos
	xchg	di,ax
	pop	bx
	invoke	scputc,bx,oypos,1,ax
	ret

ifdef __MOUSE__

xbuttms:
	push	si
	push	di
	mov	si,' '
	mov	di,si
	call	xbuttxchg
	inc	bx
	invoke	getxyc,bx,oypos
	push	ax
	sub	bx,oxlen
	mov	ax,oypos
	inc	ax
	inc	bx
	invoke	getxyc,bx,ax
	push	ax
	mov	ax,oflag
	and	ax,000Fh
	push	ax
	jnz	xbuttms_00
	mov	ax,oypos
	inc	ax
	invoke	scputc,bx,ax,oxlen,' '
	add	bx,oxlen
	dec	bx
	invoke	scputc,bx,oypos,1,' '
    xbuttms_00:
	call	msloop
	call	xbuttxchg
	pop	dx
	pop	ax
	pop	di
	test	dx,dx
	jnz	xbuttms_end
	mov	bx,oxpos
	inc	bx
	mov	dx,oypos
	inc	dx
	invoke	scputc,bx,dx,oxlen,ax
	add	bx,oxlen
	dec	bx
	invoke	scputc,bx,oypos,1,di
    xbuttms_end:
	pop	di
	pop	si
	ret

cmdmouse:
	push si
	push di
	push bp
	les bx,tdialog
	call mousex
	mov  cx,ax
	call mousey
	mov  bp,ax
	mov  result,_C_NORMAL
	.if rcxyrow(DWORD PTR es:[bx].S_DOBJ.dl_rect,cx,ax)
	    push ax
	    mov	 di,WORD PTR es:[bx].S_DOBJ.dl_rect
	    mov	 al,es:[bx].S_DOBJ.dl_count
	    mov	 si,ax
	    les bx,es:[bx].S_DOBJ.dl_object
	    .while si
		lodm es:[bx].S_TOBJ.to_rect
		add ax,di
		.if rcxyrow(dx::ax,cx,bp)
		    les bx,tdialog
		    pop ax
		    sub ax,ax
		    push ax
		    mov al,es:[bx].S_DOBJ.dl_count
		    sub ax,si
		    mov si,ax
		    inc ax
		    call LoadCurrentObject
		    .if !(ax & _O_DEACT)
			les bx,tdialog
			mov ax,si
			mov es:[bx].S_DOBJ.dl_index,al
			mov ax,oflag
			and al,0Fh
			.if al == _O_TBUTT || al == _O_PBUTT
			    call xbuttms
			.endif
			mov ax,oflag
			.if ax & _O_DEXIT
			    mov result,_C_ESCAPE
			.endif
			.if ax & _O_CHILD
			@@:
			    mov ax,si
			    call ExecuteChild
			.else
			    and ax,000Fh
			    .if al == _O_TBUTT || al == _O_PBUTT || \
				al == _O_MENUS || al == _O_XHTML
				mov result,_C_RETURN
			    .endif
			.endif
		    .else
			and ax,0Fh
			.if al == _O_LLMSU
			    call TDLListMouseUP
			.elseif al == _O_LLMSD
			    call TDLListMouseDN
			.elseif al == _O_MOUSE
			    .if cx & _O_CHILD
				jnz  @B
			    .endif
			.endif
		    .endif
		    .break
		.endif
		add bx,SIZE S_TOBJ
		dec si
	    .endw
	    pop ax
	    .if ax == 1
		invoke dlmove,tdialog
	    .elseif ax
		call msloop
	    .endif
	.else
	    mov result,_C_ESCAPE
	.endif
	pop bp
	pop di
	pop si
	ret

MouseDelay:
	call	mousep
	jnz	@F
	ret
      @@:
	call	scroll_delay
	call	scroll_delay
	or	al,1
	ret

TDLListMouseUP:
	les	bx,tdllist
	sub	ax,ax
	cmp	ax,es:[bx].S_LOBJ.ll_count
	jz	TDReturnNormal
	mov	dx,es:[bx]
	mov	es:[bx].S_LOBJ.ll_celoff,ax
	les	bx,tdialog
	cmp	dl,es:[bx].S_DOBJ.dl_index
	mov	es:[bx].S_DOBJ.dl_index,dl
	je	@F
	ret
      @@:
	call	case_UP
	test	ax,ax
	jz	TDReturnNormal
	call	MouseDelay
	jnz	@B
	jmp	TDReturnNormal

TDLListMouseDN:
	les	bx,tdllist
	sub	ax,ax
	cmp	ax,es:[bx].S_LOBJ.ll_count
	jz	TDReturnNormal
	mov	ax,es:[bx].S_LOBJ.ll_numcel
	dec	ax
	mov	es:[bx].S_LOBJ.ll_celoff,ax
	add	ax,es:[bx]
	les	bx,tdialog
	cmp	al,es:[bx].S_DOBJ.dl_index
	mov	es:[bx].S_DOBJ.dl_index,al
	jz	@F
	sub	ax,ax
	ret
      @@:
	call	case_DOWN
	test	ax,ax
	jz	TDReturnNormal
	call	MouseDelay
	jnz	@B
else
case_MOUSE:
	mov	result,_C_NORMAL
	ret
endif ; __MOUSE__


TDReturnNormal:
      ifdef __MOUSE__
	call	msloop
	inc	ax	; _C_NORMAL
      else
	mov	ax,_C_NORMAL
      endif
	ret

TDListItem?:
	sub	ax,ax
	call	LoadCurrentObject
	test	ax,_O_LLIST
	jnz	@F
	and	ax,0Fh
	cmp	al,_O_MENUS
	je	@F
	mov	result,_C_NORMAL
	pop	ax
      @@:
	ret

case_HOME:
	call	TDListItem?
	mov	ax,0
	jz	@F
	les	bx,tdllist
	mov	es:[bx].S_LOBJ.ll_index,ax
	mov	es:[bx].S_LOBJ.ll_celoff,ax
	push	es:[bx].S_LOBJ.ll_dlgoff
	call	es:[bx].S_LOBJ.ll_proc
	pop	ax
      @@:
	les	bx,tdialog
	mov	es:[bx].S_DOBJ.dl_index,al
	call	nextitem
	call	previtem
	ret

case_LEFT:
	sub	ax,ax
	call	LoadCurrentObject
	test	ax,_O_LLIST
	jz	@F
	jmp	case_PGUP
      @@:
	and	ax,000Fh
	cmp	al,_O_MENUS
	jz	@F
	call	itemleft
	jz	case_UP
	ret
      @@:
	jmp	case_EXIT

case_RIGHT:
	sub	ax,ax
	call	LoadCurrentObject
	test	ax,_O_LLIST
	jz	@F
	jmp	case_PGDN
      @@:
	and	ax,000Fh
	cmp	al,_O_MENUS
	jz	@F
	call	itemright
	jz	case_DOWN
	ret
      @@:
	jmp	case_EXIT

case_UP:
	sub	ax,ax
	call	LoadCurrentObject
	and	ax,_O_LLIST
	jz	case_UP_01
	sub	ax,ax
	les	bx,tdllist
	cmp	ax,es:[bx].S_LOBJ.ll_celoff
	jne	case_UP_01
	cmp	ax,es:[bx].S_LOBJ.ll_index
	je	@F
	mov	dx,es:[bx].S_LOBJ.ll_dlgoff
	les	bx,tdialog
	cmp	es:[bx].S_DOBJ.dl_index,dl
	je	case_UP_02
	mov	es:[bx].S_DOBJ.dl_index,dl
	inc	ax
      @@:
	ret
    case_UP_01:
	call	previtem
	ret
    case_UP_02:
	les	bx,tdllist
	dec	es:[bx].S_LOBJ.ll_index
	jmp	case_LLPROC

case_DOWN:
	sub	ax,ax
	call	LoadCurrentObject
	and	ax,_O_LLIST
	jz	case_NEXT
	les	bx,tdllist
	mov	cx,es:[bx].S_LOBJ.ll_dcount
	mov	dx,es:[bx].S_LOBJ.ll_celoff
	mov	ax,cx
	dec	ax
	cmp	ax,dx
	jz	@F
	mov	ax,dx
	add	ax,es:[bx].S_LOBJ.ll_index
	inc	ax
	cmp	ax,es:[bx].S_LOBJ.ll_count
	jb	case_NEXT
      @@:
	mov	ax,es:[bx].S_LOBJ.ll_dlgoff
	add	ax,dx
	les	bx,tdialog
	mov	ah,es:[bx].S_DOBJ.dl_index
	mov	es:[bx].S_DOBJ.dl_index,al
	cmp	al,ah
	jne	case_NORMAL
	les	bx,tdllist
	mov	ax,es:[bx].S_LOBJ.ll_count
	sub	ax,es:[bx].S_LOBJ.ll_index
	sub	ax,cx
	jle	return_NULL
	inc	es:[bx].S_LOBJ.ll_index

case_LLPROC:
	call	es:[bx].S_LOBJ.ll_proc
	jmp	return_AX

case_EXIT:
	inc	di
return_NULL:
	sub	ax,ax
return_AX:
	mov	result,ax
	ret
case_NORMAL:
	mov	result,_C_NORMAL
	ret

case_TAB:
	sub	ax,ax
	call	LoadCurrentObject
	and	ax,_O_LLIST
	jz	case_NEXT
	les	bx,tdllist
	mov	ax,es:[bx].S_LOBJ.ll_dlgoff
	add	ax,es:[bx].S_LOBJ.ll_dcount
	les	bx,tdialog
	mov	es:[bx].S_DOBJ.dl_index,al
	jmp	case_NORMAL
case_NEXT:
	jmp	nextitem

case_ESC:
	mov	result,_C_ESCAPE
	ret

case_PGUP:
	call	TDListItem?
	jz	case_PGUP_02
	les	bx,tdllist
	sub	ax,ax
	cmp	ax,es:[bx].S_LOBJ.ll_celoff
	jz	case_PGUP_01
	mov	es:[bx].S_LOBJ.ll_celoff,ax
	mov	ax,es:[bx].S_LOBJ.ll_dlgoff
	les	bx,tdialog
	mov	es:[bx].S_DOBJ.dl_index,al
    case_PGUP_00:
	mov	result,_C_NORMAL
	ret
    case_PGUP_01:
	cmp	ax,es:[bx].S_LOBJ.ll_index
	jz	case_PGUP_00
	mov	ax,es:[bx].S_LOBJ.ll_dcount
	cmp	ax,es:[bx].S_LOBJ.ll_index
	jbe	case_PGUP_03
    case_PGUP_02:
	jmp	case_HOME
    case_PGUP_03:
	sub	es:[bx].S_LOBJ.ll_index,ax
	jmp	case_LLPROC

case_PGDN:
	call	TDListItem?
	jz	case_END
	les	bx,tdllist
	mov	ax,es:[bx].S_LOBJ.ll_dcount
	dec	ax
	cmp	ax,es:[bx].S_LOBJ.ll_celoff
	jz	case_PGDN_00
	mov	ax,es:[bx].S_LOBJ.ll_numcel
	add	ax,es:[bx].S_LOBJ.ll_dlgoff
	dec	ax
	les	bx,tdialog
	mov	es:[bx].S_DOBJ.dl_index,al
	mov	result,_C_NORMAL
	ret
    case_PGDN_00:
	add	ax,es:[bx].S_LOBJ.ll_celoff
	add	ax,es:[bx].S_LOBJ.ll_index
	inc	ax
	cmp	ax,es:[bx].S_LOBJ.ll_count
	jnb	case_END
	mov	ax,es:[bx].S_LOBJ.ll_dcount
	add	es:[bx].S_LOBJ.ll_index,ax
	jmp	case_LLPROC

case_END:
	call	TDListItem?
	jnz	@F
	les	bx,tdialog
	mov	al,es:[bx].S_DOBJ.dl_count
	dec	al
	mov	es:[bx].S_DOBJ.dl_index,al
	call	previtem
	call	nextitem
	ret
      @@:
	les	bx,tdllist
	mov	ax,es:[bx].S_LOBJ.ll_count
	cmp	ax,es:[bx].S_LOBJ.ll_dcount
	jnb	@F
	mov	ax,es:[bx].S_LOBJ.ll_numcel
	dec	ax
	mov	es:[bx].S_LOBJ.ll_celoff,ax
	add	ax,es:[bx].S_LOBJ.ll_dlgoff
	les	bx,tdialog
	mov	es:[bx].S_DOBJ.dl_index,al
	mov	result,_C_NORMAL
	ret
      @@:
	sub	ax,es:[bx].S_LOBJ.ll_dcount
	cmp	ax,es:[bx].S_LOBJ.ll_index
	jz	@F
	mov	es:[bx].S_LOBJ.ll_index,ax
	mov	ax,es:[bx].S_LOBJ.ll_dcount
	dec	ax
	mov	es:[bx].S_LOBJ.ll_celoff,ax
	add	ax,es:[bx].S_LOBJ.ll_dlgoff
	les	bx,tdialog
	mov	es:[bx].S_DOBJ.dl_index,al
	les	bx,tdllist
	jmp	case_LLPROC
      @@:
	jmp	return_NULL

case_ENTER:
	sub	ax,ax
	call	LoadCurrentObject
	and	ax,_O_CHILD
	mov	ax,_C_RETURN
	jnz	@F
	mov	result,ax
	ret
      @@:
	les	bx,tdialog
	sub	ax,ax
	mov	al,es:[bx].S_DOBJ.dl_index
	call	ExecuteChild
	ret

OGOTOXY:
	sub	ax,ax
	call	LoadCurrentObjectSaveCursor
	call	cursoron
	inc	oxpos
	invoke	gotoxy,oxpos,oypos
	ret

xorradioflag:
	sub	ax,ax
	call	LoadCurrentObject
	and	ax,_O_RADIO
	jz	@F
  ifdef __MOUSE__
	call	msloop
  else
	xor	ax,ax
  endif
	ret
      @@:
	les	bx,tdialog
	sub	cx,cx
	add	cl,es:[bx].S_DOBJ.dl_count
	jz	XORRADIOFLAG_03
	les	bx,es:[bx].S_DOBJ.dl_object
    xorradioflag_loop:
	test	BYTE PTR es:[bx].S_TOBJ.to_flag,_O_RADIO
	jz	@F
	and	BYTE PTR es:[bx].S_TOBJ.to_flag,not _O_RADIO
	push	bx
	push	cx
	invoke	dlinitobj,tdialog,es::bx
	pop	cx
	pop	bx
      @@:
	add	bx,16
	dec	cx
	jnz	xorradioflag_loop
	xor	ax,ax
	call	LoadCurrentObject
	or	BYTE PTR es:[bx].S_TOBJ.to_flag,_O_RADIO
	invoke	dlinitobj,tdialog,es::bx
      ifdef __MOUSE__
	call	msloop
      endif
	mov	ax,_C_NORMAL
    XORRADIOFLAG_03:
	ret

ORETURN:
	invoke	cursorset,addr ocurs
	ret

TDXORSWITCH:
	sub	ax,ax
	call	LoadCurrentObject
	xor	ax,_O_FLAGB
	mov	es:[bx],ax
	test	ax,_O_FLAGB
	mov	ax,' '
	jz	@F
	mov	ax,'x'
      @@:
	mov	bx,WORD PTR orect
	mov	cl,bh
	inc	bx
	invoke	scputc,bx,cx,1,ax
  ifdef __MOUSE__
	call	msloop
  endif
	sub	ax,ax
	ret

ifdef __MOUSE__
TDTestXYRow:
	call	mousey
	mov	dx,ax
	call	mousex
	invoke	rcxyrow,orect,ax,dx
	mov	ax,MOUSECMD
	ret
endif

TDSelectObject:
	invoke	rcread,orect,addr xlbuf
	mov	al,at_background[B_Inverse]
	invoke	wcputbg,addr xlbuf,oxlen,ax
	invoke	rcxchg,orect,addr xlbuf
	ret

TDDeselectObject:
	push	ax
	invoke	rcwrite,orect,addr xlbuf
	pop	ax
	ret

ifndef SKIP_ALTMOVE
case_ALTUP:
	mov	ax,rcmoveup
	jmp	case_ALTMOVE
case_ALTDN:
	mov	ax,rcmovedn
	jmp	case_ALTMOVE
case_ALTLEFT:
	mov	ax,rcmoveleft
	jmp	case_ALTMOVE
case_ALTRIGHT:
	mov	ax,rcmoveright
case_ALTMOVE:
	les	bx,tdialog
	test	es:[bx].S_DOBJ.dl_flag,_D_DMOVE
	jz	@F
  ifdef __CDECL__
	push	es:[bx].S_DOBJ.dl_flag
	pushm	es:[bx].S_DOBJ.dl_wp
	pushm	es:[bx].S_DOBJ.dl_rect
  else
	pushm	es:[bx].S_DOBJ.dl_rect
	pushm	es:[bx].S_DOBJ.dl_wp
	push	es:[bx].S_DOBJ.dl_flag
  endif
	pushl	cs
	call	ax
	les	bx,tdialog
	mov	WORD PTR es:[bx].S_DOBJ.dl_rect,ax
      @@:
	ret
endif

;************** Public

dlpbuttevent PROC _CType PUBLIC
	push	si
	push	di
	sub	ax,ax
	call	LoadCurrentObjectSaveCursor
	call	cursoron
	mov	ax,oxpos
	inc	ax
	invoke	gotoxy,ax,oypos
	mov	al,BYTE PTR oflag
	and	al,0Fh
	cmp	al,_O_TBUTT
	je	@F
	call	cursoroff
      @@:
	mov	si,16
	mov	di,17
	call	xbuttxchg
	call	tgetevent
	push	ax
	call	xbuttxchg
	invoke	cursorset,addr ocurs
	pop	ax
	pop	di
	pop	si
	ret
dlpbuttevent ENDP

dlradioevent PROC _CType PUBLIC
	call OGOTOXY
	.repeat
	    call tgetevent
	  ifdef __MOUSE__
	    .if ax == MOUSECMD
		call omousecmd
		jz @F
	    .elseif ax != KEY_SPACE
	  else
	    .if ax != KEY_SPACE
	  endif
		jmp @F
	    .endif
	    call xorradioflag
	.until oflag & _O_EVENT
	mov ax,KEY_SPACE
      @@:
	call ORETURN
	ret
dlradioevent ENDP

dlcheckevent PROC _CType PUBLIC
	call	OGOTOXY
    tdcheckevent_00:
	call	tgetevent
  ifdef __MOUSE__
	cmp	ax,MOUSECMD
	je	@F
  endif
	cmp	ax,KEY_SPACE
	je	tdcheckevent_02
	jmp	tdcheckevent_03
  ifdef __MOUSE__
      @@:
	call	omousecmd
	jz	tdcheckevent_03
  endif
    tdcheckevent_02:
	call	TDXORSWITCH
	test	oflag,_O_EVENT
	jz	tdcheckevent_00
	mov	ax,KEY_SPACE
    tdcheckevent_03:
	call	ORETURN
	ret
dlcheckevent ENDP

dlxcellevent PROC _CType PUBLIC
	sub	ax,ax
	call	LoadCurrentObject
	jz	@F
	call	cursoroff
      @@:
	test	oflag,_O_LLIST
	jz	@F
	les	bx,tdialog
	mov	ah,0
	mov	al,es:[bx].S_DOBJ.dl_index
	les	bx,tdllist
	cmp	ax,es:[bx].S_LOBJ.ll_dlgoff
	jb	@F
	sub	ax,es:[bx].S_LOBJ.ll_dlgoff
	cmp	ax,es:[bx].S_LOBJ.ll_numcel
	jnb	@F
	mov	es:[bx].S_LOBJ.ll_celoff,ax
      @@:
	call	TDSelectObject
    tdxcellevent_loop:
	call	tgetevent
  ifdef __MOUSE__
	cmp	ax,MOUSECMD
	jne	tdxcellevent_07
	call	TDTestXYRow
	jz	tdxcellevent_07
	invoke	mousewait,oxpos,oypos,oxlen
	mov	ax,oflag
	and	ax,000Fh
	cmp	ax,_O_XHTML
	mov	ax,KEY_ENTER
	jz	tdxcellevent_07
	push	si
	mov	si,10
      @@:
	invoke	delay,16
	call	mousep
	jnz	@F
	dec	si
	jnz	@B
      @@:
	call	mousep
	jz	@F
	call	TDTestXYRow
	jz	@F
	mov	ax,KEY_ENTER
	jmp	tdxcellevent_06
      @@:
	sub	ax,ax
    tdxcellevent_06:
	pop	si
  endif
    tdxcellevent_07:
	test	ax,ax
	jz	tdxcellevent_loop
	call	TDDeselectObject
	ret
dlxcellevent ENDP

dlteditevent PROC _CType PUBLIC
	push	si
	les	bx,tdialog
	mov	si,es:[bx][4]
	sub	ax,ax
	call	LoadCurrentObject
	mov	dx,WORD PTR es:[bx].S_TOBJ.to_rect+2
	mov	ax,WORD PTR es:[bx].S_TOBJ.to_rect
	add	ax,si
	sub	cx,cx
	mov	cl,es:[bx].S_TOBJ.to_count
	shl	cx,4
	invoke	dledit,es:[bx].S_TOBJ.to_data,dx::ax,cx,oflag
	pop	si
	ret
dlteditevent ENDP

dlmenusevent PROC _CType PUBLIC
	sub  ax,ax
	call LoadCurrentObjectSaveCursor
	call cursoroff
	.if WORD PTR es:[bx].S_TOBJ.to_data
	    mov al,' '
	    mov ah,at_background[B_Menus]
	    or	ah,at_foreground[F_Menus]
	    mov cl,_scrrow
	    invoke scputw,20,cx,60,ax
	    invoke scputs,20,cx,0,60,es:[bx].S_TOBJ.to_data
	.endif
	call TDSelectObject
	call tgetevent
	call TDDeselectObject
	invoke cursorset,addr ocurs
	ret
dlmenusevent ENDP

dlevent PROC _CType PUBLIC USES si di bx dialog:DWORD
local	prevdlg:DWORD	; init tdialog
local	cursor:S_CURSOR ; init cursor
	movmx	prevdlg,tdialog
	movmx	tdialog,dialog
	les	bx,tdialog
	mov	si,es:[bx]
	test	si,_D_ONSCR
	jnz	@F
	invoke	dlshow,dialog
	jz	tdevent_end
      @@:
	invoke	cursorget,addr cursor
	call	cursoroff
	sub	ax,ax
	les	bx,tdialog
	cmp	es:[bx].S_DOBJ.dl_count,al
	je	@F
	call	LoadCurrentObject
	test	ax,_O_DEACT
	jz	tdevent_modal
	call	nextitem
	jnz	tdevent_modal
      @@:
	call	tgetevent
	mov	cx,9
	call	test_event
	mov	ax,result
	cmp	ax,_C_ESCAPE
	je	tdevent_cancel
	cmp	ax,_C_RETURN
	je	tdevent_cancel
	jmp	@B
    tdevent_modal:
  ifdef __MOUSE__
	call	msloop
  endif
	sub	di,di
    tdevent_continue:
	sub	ax,ax
	mov	result,ax
	call	LoadCurrentObject
	and	ax,_O_EVENT
	jz	@F
	call	es:[bx].S_TOBJ.to_proc
	jmp	tdevent_test
      @@:
	mov	al,es:[bx]
	and	ax,0Fh
	cmp	al,6
	jbe	tdevent_event
	cmp	al,_O_TBUTT
	jne	@F
	call	dlpbuttevent
	jmp	tdevent_test
      @@:
	mov	ax,KEY_ESC
	jmp	tdevent_test
    tdevent_event:
	shl	ax,size_l/2
	xchg	bx,ax
	pushl	cs
	call	eventproc[bx]
    tdevent_test:
	mov	dlexit,ax
	mov	event,ax
	mov	cx,key_count
	call	test_event
	mov	ax,result
	cmp	ax,_C_ESCAPE
	je	tdevent_cancel
	cmp	ax,_C_RETURN
	je	tdevent_return
	test	di,di
	jz	tdevent_continue
    tdevent_exit:
	invoke	cursorset,addr cursor
	mov	ax,event
	test	ax,ax
	jmp	tdevent_end
    tdevent_return:
	sub	ax,ax
	call	LoadCurrentObject
	and	ax,_O_DEXIT
	jnz	tdevent_cancel
    tdevent_index:
	les	bx,tdialog
	sub	ax,ax
	mov	al,es:[bx].S_DOBJ.dl_index
	inc	ax
	mov	event,ax
	jmp	tdevent_exit
    tdevent_cancel:
	mov	event,0
	jmp	tdevent_exit
    tdevent_end:
	les	bx,dialog
	mov	dx,ax
	movmx	tdialog,prevdlg
	mov	ax,dx
	mov	cx,dlexit
	test	ax,ax
	ret
dlevent ENDP

	END
