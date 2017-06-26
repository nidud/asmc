; CONSUSER.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include keyb.inc

	.code

consuser PROC _CType PUBLIC
local	cursor:S_CURSOR
local	dialog:S_DOBJ
	invoke	cursorget,addr cursor
	mov	al,_scrrow
	push	ax
	mov	al,console_dl.dl_rect.rc_row
	dec	al
	invoke	conssetl,ax
	call	cursoroff
	sub	ax,ax
	mov	dialog.dl_flag,_D_DOPEN
	mov	WORD PTR dialog.dl_rect,ax
	mov	dialog.dl_rect.rc_col,80
	mov	al,console_dl.dl_rect.rc_row
	mov	dialog.dl_rect.rc_row,al
	movmx	dialog.dl_wp,console_dl.dl_wp
	invoke	dlshow,addr dialog
      @@:
	call	getkey
	test	ax,ax
	jz	@B
	pop	ax
	invoke	conssetl,ax
	invoke	dlhide,addr dialog
	invoke	cursorset,addr cursor
	sub	ax,ax
	ret
consuser ENDP

	END
