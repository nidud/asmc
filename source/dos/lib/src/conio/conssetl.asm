; CONSSETL.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include keyb.inc
include mouse.inc

extrn	_egafastswitch: BYTE

.code

conssetl PROC _CType PUBLIC l:size_t	; line: 0..max
local	cursor:S_CURSOR
local	rc:DWORD
local	wp:DWORD
	mov	ax,l
	cmp	al,_scrrow
	jne	@F
	cmp	_scrcol,80
	je	conssetl_end
      @@:
	HideMouseCursor
	cmp	_egafastswitch,0
	jne	@F
	mov	al,_scrcol
	mov	ah,50
	mov	WORD PTR rc,0
	mov	WORD PTR rc+2,ax	; save screen (args rcclose)
	invoke	rcpush,49
	stom	wp
      @@:
	invoke	cursorget,addr cursor
	mov	ax,0003h	; this clears the screen
	cmp	_scrseg,0B000h
	jne	@F
	mov	al,07h
      @@:
	or	al,_egafastswitch
	int	10h
	invoke	cursorset,addr cursor
	cmp	_egafastswitch,0
	jne	@F
	call	consinit
	invoke	rcclose,rc,_D_DOPEN or _D_ONSCR,wp
      @@:
	cmp	l,49
	jne	@F
	mov	ax,1202h	; set scanline to 400
	mov	bx,0030h
	int	10h
	mov	ax,1112h	; load 8x8 font
	xor	bx,bx
	int	10h
      @@:
	test	console,CON_COLOR
	jz	@F
	invoke	loadpal,addr at_palett
      @@:
	ShowMouseCursor
    conssetl_end:
	call	consinit
	ret
conssetl ENDP

	END
