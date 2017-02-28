; ASCII.ASM--
;
; Test SetConsoleSize( cols, rows )
;
; Mouse-Left copies the hex value of current ascii to the clipboard.
; 0 to 0x30, or 48 using Mouse-Rigth
;
include consx.inc
include stdio.inc

extern	IDD_DMain:DWORD
extern	IDD_DHelp:DWORD

	.data

	x	dd 0
	y	dd 0
	d	dd 0
	oscrcol dd 0
	oscrrow dd 0
	ascii	db "Ascii"
	format	db 16 dup(0)

	.code
	;
	; Get Ascii char at mouse position
	;
getmchar:
	mov	eax,d
	mov	eax,[eax].S_DOBJ.dl_rect
	add	eax,00000207h	; y + 2, x + 7
	and	eax,0000FFFFh	; set cols and rows to 16
	or	eax,10100000h	; inside ?
	.if	rcxyrow(eax, keybmouse_x, keybmouse_y)
		mov	ecx,d
		movzx	edx,[ecx].S_DOBJ.dl_rect.rc_y
		movzx	ecx,[ecx].S_DOBJ.dl_rect.rc_x
		dec	eax
		shl	eax,4	; line * 16 + mouse_x - dialog-x
		add	eax,keybmouse_x
		sub	eax,edx ; clear ZERO flag
		lea	eax,[eax-7]
	.endif
	ret
	;
	; case F1
	;
event_F1:
	rsmodal( IDD_DHelp )
mswait:
	call	msloop
event:
	call	getkey
	test	eax,eax
	jnz	key_event
	mov	eax,edx
	shr	eax,16
	and	eax,3
	jnz	event_mouse
	mov	eax,y
	cmp	eax,keybmouse_y
	jne	@F
	mov	eax,x
	cmp	eax,keybmouse_x
	jne	@F
	call	tdidle
	jmp	event
     @@:
	mov	eax,keybmouse_x
	mov	x,eax
	mov	eax,keybmouse_y
	mov	y,eax
	scputc( 13, 1, 10, 196 )
	call	getmchar
	jz	event
	add	edx,13
	add	ecx,1
	scputf( edx, ecx, 0, 10, "[0x%02X %3d]", eax, eax )
	jmp	event
event_mouse:
	push	eax
	call	getmchar
	pop	ecx
	jz	event
	.if	!(ecx & 1)
		sprintf( addr format, " %d", eax )
	.else
		sprintf( addr format, " 0x%02X", eax )
	.endif
	cliprintf( addr format[1] )
	SetConsoleTitle( addr ascii )
	jmp	mswait
key_event:
	cmp	eax,KEY_F1
	je	event_F1
	cmp	eax,KEY_SPACE
	je	event
	ret

main	PROC c
	mov	tdidle,ConsoleIdle
	or	console,CON_SLEEP
	SetConsoleTitle( addr ascii )
	.if	rsopen( IDD_DMain )
		mov	d,eax
		mov	[eax+16].S_TOBJ.to_proc,event
		mov	ecx,_scrcol
		mov	edx,_scrrow
		inc	edx
		mov	oscrcol,ecx
		mov	oscrrow,edx
		push	eax
		movzx	edx,[eax].S_DOBJ.dl_rect.rc_row
		movzx	eax,[eax].S_DOBJ.dl_rect.rc_col
		SetConsoleSize( eax, edx )
		call	dlmodal
		SetConsoleSize( oscrcol, oscrrow )
	.endif
	xor	eax,eax
	ret
main	ENDP

	END
