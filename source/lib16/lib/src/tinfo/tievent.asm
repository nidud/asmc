; TIEVENT.ASM--
; Copyright (C) 2015 Doszip Developers

include clip.inc
include conio.inc
include tinfo.inc
include keyb.inc
include mouse.inc
include string.inc
include dos.inc
include ctype.inc

tiselected  PROTO
ticlipevent PROTO

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

ti_proctab label size_t
	dw ticontinue
	dw tiesc
	dw tileft
	dw tiright
	dw tihome
	dw titoend
	dw tibacksp
	dw tiretevent
	dw tidelete
	dw timouse
	dw tinextword
	dw tiprevword
	dw tiesc
	dw tiesc
	dw tiesc
	dw tiesc

ti_key_count = (($ - offset ti_proctab) / size_l)

	.code

tinocando PROC PUBLIC
	invoke	beep,9,1
	mov	ax,_TI_CMFAILED ; end of line/buffer
	ret
tinocando ENDP

ticurlp PROC PUBLIC USES bx
	mov	bx,tinfo
	lodm	[bx].S_TINFO.ti_bp
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

tiesc PROC PUBLIC
	jmp tiretevent
tiesc ENDP

tileft PROC USES bx
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

tiincvalue PROC pascal USES si di dx boff:DWORD, soff:DWORD,
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

tiincx PROC USES bx ax
	mov bx,tinfo
	invoke tiincvalue,addr [bx].S_TINFO.ti_boff,addr [bx].S_TINFO.ti_xoff,
		[bx].S_TINFO.ti_bcol,[bx].S_TINFO.ti_cols
	ret
tiincx ENDP

tiright PROC USES di bx
	mov	bx,tinfo
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

tihome PROC PUBLIC USES bx
	mov	bx,tinfo
	sub	ax,ax
	mov	[bx].S_TINFO.ti_xoff,ax
	mov	[bx].S_TINFO.ti_boff,ax
	ret
tihome ENDP

titoend PROC PUBLIC USES bx
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

tistrlen PROC USES si di bx
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

tidecvalue PROC pascal USES si di dx boff:DWORD, soff:DWORD,
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

tidecx PROC USES ax bx
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

tiseto PROC PUBLIC USES si di bx
	call	ticurlp
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

tibacksp PROC
	mov cx,bx
	mov bx,tinfo
	mov ax,[bx].S_TINFO.ti_boff
	add ax,[bx].S_TINFO.ti_xoff
	mov bx,cx
	.if ax
	    call tileft
	    call tidelete
	    ret
	.endif
	call tinocando
	ret
tibacksp ENDP

tiputc_add:
	mov	ax,[bx].S_TINFO.ti_bcnt
	inc	ax
	cmp	ax,[bx].S_TINFO.ti_bcol
	jae	tiputc_eof
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
    tiputc_CONTINUE:
	mov	ax,_TI_CONTINUE
	ret
    tiputc_CONTROL:
	test	al,al
	jz	tiputc_ret
	test	[bx].S_TINFO.ti_flag,_T_USECONTROL
	jnz	tiputc_add
    tiputc_ret:
	mov	ax,_TI_RETEVENT
	ret
    tiputc_eof:
	jmp	tinocando

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

tidelete PROC PUBLIC USES di bx
	mov  bx,tinfo
	call ticurcp
	mov  es,dx
	mov  di,ax
	or   [bx].S_TINFO.ti_flag,_T_MODIFIED
	.if  BYTE PTR es:[di] != 0
	    dec [bx].S_TINFO.ti_bcnt
	    mov cx,ax
	    inc cx
	    invoke strcpy,dx::ax,dx::cx
	.endif
	call ticontinue
	ret
tidelete ENDP

tiisword PROC
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

tinextword PROC PUBLIC USES si bp
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

tiprevword PROC PUBLIC USES si di bp bx
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

tisetcursor PROC PUBLIC USES bx
	mov	bx,tinfo
	mov	ax,[bx].S_TINFO.ti_xpos
	add	ax,[bx].S_TINFO.ti_xoff
	mov	ah,BYTE PTR [bx].S_TINFO.ti_ypos
	mov	[bx].S_TINFO.ti_cursor.cr_xy,ax
	mov	[bx].S_TINFO.ti_cursor.cr_type,CURSOR_NORMAL
	invoke	cursorset,addr [bx].S_TINFO.ti_cursor
	ret
tisetcursor ENDP

timouse PROC USES bx
  ifdef __MOUSE__
	mov	bx,tinfo
	call	mousey
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

tiputl	PROC USES si di bx
local	lb[2+TIMAXSCRLINE]:BYTE
local	wc[2*TIMAXSCRLINE]:BYTE
local	line:size_t	; current line 0..max
local	loff:size_t	; adress of line
local	lseg:size_t
local	llen:size_t	; length of line
local	clst:size_t	; clip start
local	clen:size_t	; clip end
	mov si,tinfo
	mov	ah,[si].S_TINFO.ti_clat
	mov	al,[si].S_TINFO.ti_clch
	push	ss
	pop	es
	lea	dx,wc
	mov	di,dx
	mov	cx,TIMAXSCRLINE
	cld?
	rep	stosw
	mov	di,dx
	lodm	[si].S_TINFO.ti_bp
	mov	loff,ax
	mov	lseg,dx
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
    tiputl_color:
  ifdef __CLIP__
	xor	ax,ax
	mov	clen,ax ; clip end to	0000
	dec	ax		; clip start to FFFF
	mov	clst,ax
	call	tiselected
	jz	tiputl_screen
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
	sub	ax,ax
	call	tiputl
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

	END
