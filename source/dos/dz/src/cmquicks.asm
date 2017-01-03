; CMQUICKS.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include dos.inc
include keyb.inc
include conio.inc
include string.inc

; (PG)UP,DOWN:	Move
; ESC,TAB,ALTX: Quit
; ENTER:	Quit
; BKSP:		Search from start
; insert char:	Search from current pos.

;SKIPSUBDIR = 1 ; Exclude directories in search

.data

cp_quicksearch	db '&Quick Search: ',1Ah,'   ',0

cmquicksearch_keys label WORD
	dw 0,KEY_ESC,KEY_TAB,KEY_ALTX,KEY_ENTER,KEY_KPENTER
	dw KEY_LEFT,KEY_RIGHT,KEY_UP,KEY_PGUP,KEY_DOWN,KEY_PGDN
	dw KEY_HOME,KEY_END,KEY_BKSP
cmquicksearch_label label WORD
	dw event_loop,event_exit,event_exit,event_exit,event_enter
	dw event_enter,event_pevent,event_pevent,event_pevent,event_pevent
	dw event_pevent,event_pevent,event_pevent,event_pevent,event_bksp
cmquicksearch_count = ($ - cmquicksearch_label) / 2

.code _DZIP

psearch PROC pascal PRIVATE USES si di bx cname:DWORD, l:WORD, direction:WORD
local fcb:DWORD
local cindex:WORD
local lindex:WORD
	mov	bx,cpanel		; current index
	mov	si,[bx].S_PANEL.pn_fcb_index
	add	si,[bx].S_PANEL.pn_cel_index
	mov	lindex,si
	mov	cindex,si
	mov	di,[bx].S_PANEL.pn_fcb_count
	mov	bx,WORD PTR [bx].S_PANEL.pn_wsub
	or	ax,ax			; if (AX == 0) search from start
	movmx	fcb,[bx].S_WSUB.ws_fcb
	jz	psearch_all		; (case BKSP)
    psearch_loop:
	cmp	si,di			; search from current to end
	jnb	psearch_start
	les	bx,fcb
	mov	ax,si
	shl	ax,2
	add	bx,ax
	les	bx,es:[bx]
  ifdef SKIPSUBDIR
	test	BYTE PTR es:[bx],_A_SUBDIR
	jnz	psearch_next
  endif
	invoke	strnicmp,cname,addr es:[bx].S_FBLK.fb_name,l
	test	ax,ax
	jz	psearch_match
    psearch_next:
	inc	si
	jmp	psearch_loop
    psearch_all:
	mov	lindex,di
    psearch_start:
	xor	si,si
	mov	di,lindex
	mov	lindex,si
	cmp	si,di
	jne	psearch_loop
	xor	ax,ax
	jmp	psearch_end
    psearch_match:
	mov	bx,cpanel
	push	bx
	push	0
	invoke	dlclose,[bx].S_PANEL.pn_xl
	mov	ax,cpanel
	mov	dx,si
	call	panel_setid
	call	panel_putitem
	mov	ax,cpanel
	call	pcell_show
	mov	ax,1
    psearch_end:
	mov	dx,cindex
	ret
psearch ENDP

event_pevent:
	invoke	panel_event,cpanel,ax
event_loop:
	sub	ax,ax
	ret
event_bksp:			; delete char and search from start
	cmp	si,15
	jle	event_loop
	dec	si
	mov	dx,di
	invoke	scputw,si,di,2,' '
	invoke	gotoxy,si,di
	xor	ax,ax
	mov	cx,15
event_back:
	push	ax
	mov	dx,si
	sub	dx,cx
	invoke	psearch,ss::bx,dx,ax
	test	ax,ax
	pop	ax
	jz	event_loop
	test	ax,ax
	jz	event_loop
	invoke	scputw,si,di,1,ax
	cmp	si,78
	jge	event_loop
	inc	si
	invoke	gotoxy,si,di
	jmp	event_loop
event_enter:
	mov	ax,si
	sub	ax,15
	invoke	psearch,ss::bx,ax,1
  ifdef SKIPSUBDIR
	jmp	event_loop
  else
	test	ax,ax
	jz	event_loop
	mov	bx,cpanel
	mov	ax,[bx].S_PANEL.pn_fcb_index
	add	ax,[bx].S_PANEL.pn_cel_index
	cmp	ax,dx
	jne	event_loop
  endif
event_exit:
	mov ax,1
	ret

cmquicksearch PROC _CType PUBLIC USES si di
local cursor:S_CURSOR
local stline[128]:WORD
local fname[256]:BYTE
	.if cpanel_state()
	    invoke cursorget,addr cursor
	    invoke cursoron
	    invoke wcpushst,addr stline,addr cp_quicksearch
	    mov	   si,15		; SI = x
	    sub	   ax,ax
	    mov	   al,_scrrow		; DI = y
	    mov	   di,ax
	    invoke gotoxy,si,di		; cursor to (x,y)
	    .repeat
		call tupdate
		call getkey		; get key
		.continue .if !ax
		mov cx,cmquicksearch_count	; test key
		xor bx,bx
		.repeat
		    .break .if ax == cmquicksearch_keys[bx]
		    add bx,2
		.untilcxz
		.if cx
		    mov dx,cmquicksearch_label[bx]
		    lea bx,fname
		    call dx
		.else
		    lea bx,fname
		    mov ah,0
		    mov [bx+si-15],al
		    mov cx,14
		    call event_back
		.endif
	    .until ax
	    invoke wcpopst,addr stline
	    invoke cursorset,addr cursor
	.endif
	sub ax,ax
	ret
cmquicksearch ENDP

	END
