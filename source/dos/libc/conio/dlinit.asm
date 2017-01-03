; DLINIT.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include mouse.inc

extrn	tclrascii:BYTE

	.data

init_procs label size_t
	dw init_pushbutton
	dw init_radiobutton
	dw init_chechbox
	dw init_textedit
	dw init_textedit
	dw init_menus

	.code

init_pushbutton:
	lds si,[bp-4]
	and ax,_O_DEACT
	mov di,ax
	.repeat
	    mov ax,[si]
	    inc si
	    mov al,ah
	    and al,0Fh
	    .if di
		.if !al
		    and ah,070h
		    or	ah,008h
		    mov [si],ah
		.endif
	    .else
		.if al == 8
		    and ah,070h
		    mov [si],ah
		.endif
	    .endif
	    inc si
	.untilcxz
	ret

init_radiobutton:
	and	al,_O_RADIO
	mov	al,' '
	jz	@F
	mov	al,7
      @@:
	les	bx,[bp-4]
	mov	es:[bx][2],al
	ret

init_chechbox:
	and	ax,_O_FLAGB
	mov	al,' '
	jz	@B
	mov	al,'x'
	jmp	@B

init_textedit:
	mov dl,tclrascii
	mov ax,si
	lds si,es:[bx].S_TOBJ.to_data
	mov bx,ax
	les di,[bp-4]
	mov ax,es:[di]
	mov al,dl
	mov dx,cx
	.if bl != _O_TEDIT
	    mov al,' '
	    .repeat
		stosb
		inc di
	    .untilcxz
	.else
	    cld?
	    rep stosw
	.endif
	mov cx,dx
	.if si
	    mov di,[bp-4]
	    .repeat
		lodsb
		.break .if !al
		stosb
		inc di
	    .untilcxz
	.endif
	ret

init_menus:
	les bx,[bp-4]
	.if al & _O_FLAGB
	    mov BYTE PTR es:[bx][-2],175
	.elseif ax & _O_RADIO
	    mov BYTE PTR es:[bx][-2],7
	.endif
	ret

dlinitobj PROC _CType PUBLIC USES bx si di dobj:DWORD, tobj:DWORD
local	window:DWORD
	push ds
	les bx,tobj
	mov  ch,es:[bx][6]	; .to_rect.rc_col
	mov  dx,es:[bx][4]	; .to_rect.rc_x,y
	les bx,dobj
	mov  cl,es:[bx][6]	; .dl_rect.rc_col
	mov  di,es:[bx] ; .dl_flag
	.if di & _D_ONSCR
	    HideMouseCursor
	    add dx,es:[bx+4]
	    mov cl,_scrcol
	.endif
	add dx,dx
	mov al,dh
	mul cl
	mov cl,ch
	and cx,00FFh
	and dx,00FFh
	add ax,dx
	mov dx,_scrseg
	.if !(di & _D_ONSCR)
	    add ax,WORD PTR es:[bx].S_DOBJ.dl_wp
	    mov dx,WORD PTR es:[bx].S_DOBJ.dl_wp+2
	.endif
	stom window
	les bx,tobj
	mov ax,es:[bx]
	and ax,000Fh
	mov si,ax
	cmp al,_O_MENUS
	ja  @F
	shl ax,size_l/2
	xchg ax,si
	mov si,init_procs[si]
	xchg ax,si
	mov dx,ax
	mov ax,es:[bx]
	push di
	call dx
	pop di
      @@:
	.if di & _D_ONSCR
	    ShowMouseCursor
	.endif
	mov ax,di
	pop ds
	ret
dlinitobj ENDP

dlinit	PROC _CType PUBLIC USES si di bx td:DWORD
local	object:DWORD
	les	bx,td
	mov	di,es:[bx]
	sub	ax,ax
	mov	al,es:[bx].S_DOBJ.dl_count
	mov	si,ax
	lodm	es:[bx].S_DOBJ.dl_object
	stom	object
	assert	ax,0,jne,"dlinit"
	.while si
	    invoke dlinitobj,td,object
	    add WORD PTR object,SIZE S_TOBJ
	    dec si
	.endw
	ret
dlinit	ENDP

	END
