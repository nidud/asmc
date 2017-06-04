include consx.inc
include string.inc
include ltype.inc

ticontinue	PROTO
tiretevent	PROTO
tinocando	PROTO
tidecx		PROTO :DWORD
tiincx		PROTO :DWORD
tistripend	PROTO :DWORD
tiisword	PROTO

	.data

TI	dd 0

	.code

	OPTION PROC: PRIVATE
	ASSUME	edx: PTR S_TEDIT

getline PROC USES esi edi
	mov	edx,TI
	mov	eax,[edx].ti_bp
	.if	eax
		mov	esi,eax
		mov	edi,eax
		mov	ecx,[edx].ti_bcol	; terminate line
		xor	eax,eax			; set length of line
		mov	[edi+ecx-1],al
		mov	ecx,-1
		repne	scasb
		not	ecx
		dec	ecx
		dec	edi
		mov	[edx].ti_bcnt,ecx
		sub	ecx,[edx].ti_bcol	; clear rest of line
		neg	ecx
		rep	stosb
		mov	ecx,[edx].ti_bcnt
		mov	eax,[edx].ti_bp
		test	eax,eax
	.endif
	ret
getline ENDP

curlptr PROC
	getline()
	.if	!ZERO?
		add	eax,[edx].ti_boff
		add	eax,[edx].ti_xoff
	.endif
	ret
curlptr ENDP

needline PROC
	getline()
	.if	ZERO?
		pop	eax		 ; pop caller off the stack
		mov	eax,_TE_CMFAILED ; operation fail (end of line/buffer)
	.endif
	ret
needline ENDP

event_home PROC
	call	needline
	xor	eax,eax
	mov	[edx].ti_boff,eax
	mov	[edx].ti_xoff,eax
	ret
event_home ENDP

event_toend PROC
	call	event_home
	call	needline
	tistripend( eax )
	.if	ecx
		mov	eax,[edx].ti_cols
		dec	eax
		.if	SDWORD PTR ecx <= eax
			mov eax,ecx
		.endif
		mov	[edx].ti_xoff,eax
		mov	ecx,[edx].ti_bcnt
		sub	ecx,[edx].ti_cols
		inc	ecx
		xor	eax,eax
		.if	SDWORD PTR eax <= ecx
			mov eax,ecx
		.endif
		mov	[edx].ti_boff,eax
		add	eax,[edx].ti_xoff
		.if	eax > [edx].ti_bcnt
			dec [edx].ti_boff
		.endif
	.endif
	xor	eax,eax
	ret
event_toend ENDP

event_left PROC
	xor	eax,eax
	.if	eax != [edx].ti_xoff
		dec [edx].ti_xoff
	.elseif eax != [edx].ti_boff
		dec [edx].ti_boff
	.else
		mov	eax,_TE_CMFAILED
		.if	[edx].ti_flag & _TE_DLEDIT
			mov eax,_TE_RETEVENT
		.endif
	.endif
	ret
event_left ENDP

event_right PROC

	call	curlptr
	mov	ecx,eax
	mov	al,[eax]
	sub	ecx,[edx].ti_xoff

	.if	al
		mov	eax,[edx].ti_cols
		dec	eax
		.if	eax > [edx].ti_xoff
			inc	[edx].ti_xoff
			xor	eax,eax
			ret
		.endif
	.endif

	.if	strlen( ecx ) >= [edx].ti_cols
		inc	[edx].ti_boff
		xor	eax,eax
		ret
	.endif

	mov	eax,_TE_CMFAILED
	.if	[edx].ti_flag & _TE_DLEDIT
		mov	eax,_TE_RETEVENT
	.endif
	ret
event_right ENDP

event_delete PROC
	call	curlptr
	.if	!ZERO?
		tistripend( eax )
		call	curlptr
		.if	ecx && BYTE PTR [eax]
			dec	[edx].ti_bcnt
			mov	ecx,eax
			inc	eax
			strcpy( ecx, eax )
			or	[edx].ti_flag,_TE_MODIFIED
			mov	eax,_TE_CONTINUE
			ret
		.endif
	.endif
	call	tinocando
	ret
event_delete ENDP

event_backsp PROC
	call	getline
	jz	@F
	mov	eax,[edx].ti_xoff
	add	eax,[edx].ti_boff
	jz	error
	test	ecx,ecx
	jz	error
	call	event_left
	call	curlptr
	tistripend( eax )
	test	eax,eax
	jnz	event_delete
@@:
	ret
error:
	call	tinocando
	ret
event_backsp ENDP

event_tab PROC
	test	ecx,_TE_USECONTROL
	jnz	@F
	mov	eax,_TE_RETEVENT ; return current event (keystroke)
	ret
@@:
	mov	al,9
event_tab ENDP

event_add PROC USES ebx
	mov	ebx,eax
	call	getline
	jz	nocando
	movzx	eax,bl
	test	byte ptr _ltype[eax+1],_CONTROL
	jnz	control
add_char:
	mov	eax,[edx].ti_bcnt
	inc	eax
	cmp	eax,[edx].ti_bcol
	jae	endoffline
	tiincx( edx )
	jz	endoffline
	inc	[edx].ti_bcnt
	call	getline
	jz	endoffline
	or	[edx].ti_flag,_TE_MODIFIED
	mov	eax,[edx].ti_bp
	add	eax,[edx].ti_boff
	add	eax,[edx].ti_xoff
	dec	eax
	strshr( eax, ebx )
done:
	sub	eax,eax
toend:
	ret
endoffline:
	mov	eax,[edx].ti_bcol
	dec	eax
	mov	[edx].ti_bcnt,eax
nocando:
	call	tinocando
	jmp	toend
control:
	test	bl,bl
	jz	@F
	test	[edx].ti_flag,_TE_USECONTROL
	jnz	add_char
@@:
	mov	eax,_TE_RETEVENT
	jmp	toend
event_add ENDP

_setcursor PROC
  local cursor:S_CURSOR
	mov	edx,TI
	mov	eax,[edx].ti_xpos
	add	eax,[edx].ti_xoff
	mov	ecx,[edx].ti_ypos
	mov	cursor.x,ax
	mov	cursor.y,cx
	mov	cursor.bVisible,1
	mov	cursor.dwSize,CURSOR_NORMAL
	CursorSet( addr cursor )
	ret
_setcursor ENDP

event_nextword PROC USES esi
	call	curlptr
	jz	toend
	mov	esi,eax		; to end of word
	mov	ecx,eax
     @@:
	lodsb
	call	tiisword
	jnz	@B
	test	al,al
	jz	toend
     @@:
	lodsb			; to start of word
	test	al,al
	jz	toend
	call	tiisword
	jz	@B
	dec	esi
	sub	esi,ecx
	mov	eax,[edx].ti_boff
	add	eax,[edx].ti_xoff
	add	eax,esi
	cmp	eax,[edx].ti_bcnt
	ja	toend
	sub	eax,[edx].ti_boff
	mov	ecx,[edx].ti_cols
	cmp	eax,ecx
	jb	@F
	dec	ecx
	sub	eax,ecx
	add	[edx].ti_boff,eax
	mov	[edx].ti_xoff,ecx
	jmp	continue
@@:
	mov	[edx].ti_xoff,eax
continue:
	mov	eax,_TE_CONTINUE
toend:
	ret
event_nextword ENDP

event_prevword PROC
	push	esi
	call	getline
	test	eax,eax
	jz	toend
	mov	ecx,eax
	mov	eax,[edx].ti_boff
	add	eax,[edx].ti_xoff
	jz	toend
	mov	esi,eax
	add	esi,ecx
	mov	al,[esi]
	call	tiisword
	jz	@F
	mov	al,[esi-1]
	call	tiisword
	jnz	lup2
	dec	esi
	jmp	lup
@@:
	test	al,al
	jnz	lup
	dec	esi
lup:
	cmp	esi,ecx
	je	set
	jb	home
	mov	al,[esi]
	dec	esi
	cmp	esi,ecx
	jbe	home
	test	al,al
	jz	home
	call	tiisword
	jz	lup
lup2:
	mov	al,[esi]
	dec	esi
	cmp	esi,ecx
	jb	home
	je	set
	test	al,al
	jz	home
	call	tiisword
	jnz	lup2
	add	esi,2
set:
	mov	eax,esi
	sub	eax,ecx
	cmp	eax,[edx].ti_cols
	jnb	@F
	mov	[edx].ti_xoff,eax
	mov	[edx].ti_boff,0
	jmp	done
@@:
	sub	eax,[edx].ti_xoff
	mov	[edx].ti_boff,eax
done:
	mov	eax,_TE_CONTINUE
toend:
	pop	esi
	ret
home:
	call	event_home
	jmp	toend
event_prevword ENDP

event_mouse PROC USES ebx
	mov	ebx,keybmouse_y
	mov	ecx,keybmouse_x
	mov	eax,[edx].ti_xpos
	cmp	ecx,eax
	jb	event
	add	eax,[edx].ti_cols
	cmp	ecx,eax
	jae	event
	mov	eax,[edx].ti_ypos
	cmp	ebx,eax
	jne	event
	push	ecx
	call	getline
	jz	@F
	strlen( eax )
@@:
	pop	ecx
	sub	ecx,[edx].ti_xpos
	cmp	ecx,eax
	jg	@F
	mov	eax,ecx
@@:
	mov	[edx].ti_xoff,eax
	call	_setcursor
	call	msloop
	sub	eax,eax
toend:
	ret
event:
	call	tiretevent
	jmp	toend
event_mouse ENDP

	.data

keytable label DWORD
	dd _TE_CONTINUE,	ticontinue
	dd KEY_CTRLRIGHT,	event_nextword
	dd KEY_CTRLLEFT,	event_prevword
	dd KEY_LEFT,		event_left
	dd KEY_RIGHT,		event_right
	dd KEY_HOME,		event_home
	dd KEY_END,		event_toend
	dd KEY_BKSP,		event_backsp
	dd KEY_TAB,		event_tab
	dd KEY_DEL,		event_delete
	dd MOUSECMD,		event_mouse
	dd KEY_UP,		tiretevent
	dd KEY_DOWN,		tiretevent
	dd KEY_PGUP,		tiretevent
	dd KEY_PGDN,		tiretevent
	dd KEY_CTRLPGUP,	tiretevent
	dd KEY_CTRLPGDN,	tiretevent
	dd KEY_CTRLHOME,	tiretevent
	dd KEY_CTRLEND,		tiretevent
	dd KEY_CTRLUP,		tiretevent
	dd KEY_CTRLDN,		tiretevent
	dd KEY_MOUSEUP,		tiretevent
	dd KEY_MOUSEDN,		tiretevent
	dd KEY_ENTER,		tiretevent
	dd KEY_KPENTER,		tiretevent
	dd KEY_ESC,		tiretevent

keycount equ (($ - offset keytable) / 8)

	.code

tievent PROC
	mov	ecx,keycount
	lea	edx,keytable
	.repeat
		.if	eax == [edx]
			mov	eax,[edx+4]
			mov	edx,TI
			mov	ecx,[edx].ti_flag
			call	eax
			ret
		.endif
		add	edx,8
	.untilcxz
	call	event_add
	ret
tievent ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

ClipIsSelected PROC
	mov	edx,TI
	mov	eax,[edx].ti_cleo
	sub	eax,[edx].ti_clso
	ret
ClipIsSelected ENDP

ClipSet PROC
	mov	edx,TI
	mov	eax,[edx].ti_xoff
	add	eax,[edx].ti_boff
	mov	[edx].ti_clso,eax
	mov	[edx].ti_cleo,eax
	ret
ClipSet ENDP

ClipDelete PROC
	.if	ClipIsSelected()
		mov	eax,[edx].ti_clso
		mov	ecx,[edx].ti_xoff
		add	ecx,[edx].ti_boff
		.if	ecx < eax
			.repeat
				tiincx( edx )
				.break .if ZERO?
				inc	ecx
			.until	eax == ecx
			inc	ecx
		.elseif ecx > eax
			.repeat
				tidecx( edx )
				.break .if ZERO?
				dec	ecx
			.until	eax == ecx
			inc	ecx
		.endif
		mov	eax,[edx].ti_bp
		or	[edx].ti_flag,_TE_MODIFIED
		mov	ecx,eax
		add	eax,[edx].ti_clso
		add	ecx,[edx].ti_cleo
		strcpy( eax, ecx )
		call	getline
		call	ClipSet
		xor	eax,eax
		inc	eax
	.endif
	ret
ClipDelete ENDP

ClipCopy PROC
	xor	eax,eax
	jmp	ClipCC
ClipCopy ENDP

ClipCut PROC
	mov	eax,1
ClipCut ENDP

ClipCC	PROC USES esi edi
	mov	esi,TI
	mov	edi,eax		; AX: Copy == 0, Cut == 1
	call	ClipIsSelected	; get size of selection
	jz	@F
	mov	edx,TI
	mov	eax,[edx].ti_bp
	add	eax,[edx].ti_clso
	mov	ecx,[edx].ti_cleo
	sub	ecx,[edx].ti_clso
	ClipboardCopy( eax, ecx )
	test	eax,eax
	jz	toend
	test	edi,edi
	jz	@F
	call	ClipDelete
@@:
	call	ClipSet
toend:
	xor	eax,eax
	ret
ClipCC	ENDP

ClipPaste PROC USES esi edi ebx
	mov	edx,TI
	mov	eax,[edx].ti_flag
	.if	eax & _TE_OVERWRITE
		call	ClipDelete
	.else
		call	ClipSet
	.endif
	call	ClipboardPaste
	.if	!ZERO?
		mov	edx,TI
		push	[edx].ti_xoff
		push	[edx].ti_boff
		mov	edi,eax
		mov	esi,ecx ; clipbsize
		.repeat
			mov	al,[edi]
			.break .if !al
			inc	edi
			.break .if event_add() != _TE_CONTINUE
			dec	esi
		.until	ZERO?
		call	ClipboardFree
		mov	edx,TI
		pop	eax
		mov	[edx].ti_boff,eax
		pop	eax
		mov	[edx].ti_xoff,eax
	.endif
	call	ClipSet
	xor	eax,eax
	ret
ClipPaste ENDP

ClipEvent PROC USES esi edi ebx
	mov	esi,eax
	call	ClipIsSelected
	jnz	@F
	call	ClipSet			; reset clipboard if not selected
@@:
	cmp	esi,KEY_CTRLINS		; test clipboard shortkeys
	je	@Copy
	cmp	esi,KEY_CTRLC
	je	@Copy
	cmp	esi,KEY_CTRLV
	je	@Paste
	cmp	esi,KEY_CTRLDEL
	je	@Cut
	mov	eax,keyshift
	mov	eax,[eax]
	test	eax,SHIFT_KEYSPRESSED
	jnz	@ShiftDown
	cmp	esi,KEY_DEL		; Delete selected text ?
	jne	delete?
	call	ClipDelete
	jz	reset
	xor	eax,eax
	jmp	toend
@Copy:
	call	ClipCopy
	jmp	toend
@Cut:
	call	ClipCut
	jmp	toend
@Paste:
	call	ClipPaste
	jmp	toend
@ShiftDown:
	cmp	esi,KEY_INS		; Shift-Insert -- Paste()
	je	@Paste
	cmp	esi,KEY_DEL		; Shift-Del -- Cut()
	je	@Cut
	cmp	esi,KEY_HOME
	je	@move
	cmp	esi,KEY_LEFT
	je	@move
	cmp	esi,KEY_RIGHT
	je	@move
	cmp	esi,KEY_END
	je	@move
delete?:
	cmp	esi,KEY_ESC
	je	reset
	cmp	esi,MOUSECMD
	je	reset
	cmp	esi,KEY_BKSP
	je	reset
	cmp	esi,KEY_ENTER
	je	reset
	cmp	esi,KEY_KPENTER
	je	reset
	cmp	esi,KEY_TAB
	je	reset
	mov	eax,esi
	test	al,al
	jz	reset
	call	ClipDelete
reset:
	call	ClipSet			; set clipboard to cursor
	mov	eax,esi			; return event
toend:
	ret
@null:
	xor	eax,eax
	jmp	toend
@move:
	mov	eax,esi			; consume event, return null
	call	tievent
	cmp	eax,_TE_CMFAILED
	je	@null
	cmp	eax,_TE_RETEVENT
	je	@null
	mov	ebx,TI
	mov	eax,[ebx].S_TEDIT.ti_boff
	add	eax,[ebx].S_TEDIT.ti_xoff
	cmp	eax,[ebx].S_TEDIT.ti_clso
	jb	@back
	cmp	esi,KEY_RIGHT
	jne	@F
	mov	edx,eax
	dec	edx
	cmp	edx,[ebx].S_TEDIT.ti_clso
	jne	@F
	cmp	edx,[ebx].S_TEDIT.ti_cleo
	jne	@back
@@:
	mov	[ebx].S_TEDIT.ti_cleo,eax
	jmp	@null
@back:
	mov	[ebx].S_TEDIT.ti_clso,eax
	jmp	@null
ClipEvent ENDP

putline PROC USES esi edi ebx

local	ci[256]:DWORD,
	bz:	COORD,
	rc:	SMALL_RECT

	_setcursor()

	lea	edi,ci
	mov	edx,TI
	mov	ebx,[edx].ti_cols
	mov	eax,[edx].ti_clat
	mov	cl,al
	mov	al,0
	shl	eax,8
	mov	al,cl
	mov	ecx,ebx
	rep	stosd

	mov	esi,[edx].ti_bp
	.if	strlen( esi ) > [edx].ti_boff

		add	esi,[edx].ti_boff
		mov	ecx,ebx
		lea	edi,ci

		.repeat
			mov	al,[esi]
			.break .if !al
			mov	[edi],al
			inc	esi
			add	edi,4
		.untilcxz
	.endif

	mov edi,[edx].ti_boff
	mov ecx,[edx].ti_cleo

	.if edi < ecx

		sub ecx,edi
		xor eax,eax
		.if ecx >= ebx

			mov ecx,ebx
		.endif
		.if [edx].ti_clso >= edi

			mov eax,[edx].ti_clso
			sub eax,edi
			.if eax <= ecx
				sub ecx,eax
			.else
				xor ecx,ecx
			.endif
		.endif
		.if ecx

			lea edi,ci
			lea edi,[edi+eax*4+2]
			mov al,at_background[B_Inverse]
			.repeat
				mov [edi],al
				add edi,4
			.untilcxz
		.endif
	.endif

	mov	ecx,ebx
	mov	bz.x,cx
	mov	eax,[edx].ti_xpos
	mov	rc.Left,ax
	add	eax,ecx
	dec	eax
	mov	rc.Right,ax
	mov	eax,[edx].ti_ypos
	mov	rc.Top,ax
	mov	rc.Bottom,ax
	mov	bz.y,1

	WriteConsoleOutput( hStdOutput, addr ci, bz, 0, addr rc )
	ret
putline ENDP

modal	PROC USES esi edi
	xor	esi,esi
	.repeat
		.if	!esi
			call getline
			call putline
		.endif
		call	tgetevent
		call	ClipEvent
		mov	edi,eax
		call	tievent
		mov	esi,eax
	.until	eax == _TE_RETEVENT
	call	getline
	mov	eax,edi		; return current event (keystroke)
	ret
modal	ENDP

;-------------------------------------------------------------------------------
	OPTION PROC: PUBLIC
;-------------------------------------------------------------------------------

dledit	PROC USES edi b:LPSTR, rc, bz, oflag
  local t:S_TEDIT
  local cursor:S_CURSOR

	CursorGet( addr cursor )

	lea	edi,t
	xor	eax,eax
	mov	ecx,SIZE S_TEDIT
	rep	stosb
	mov	edi,TI
	lea	eax,t
	mov	TI,eax

	movzx	eax,rc.S_RECT.rc_x
	mov	t.ti_xpos,eax
	mov	al,rc.S_RECT.rc_y
	mov	t.ti_ypos,eax
	mov	al,rc.S_RECT.rc_col
	mov	t.ti_cols,eax
	mov	eax,bz
	mov	t.ti_bcol,eax
	mov	eax,b
	mov	t.ti_bp,eax
	mov	eax,oflag
	and	eax,_O_CONTR or _O_DLGED
	or	eax,_TE_OVERWRITE
	mov	t.ti_flag,eax
	call	_setcursor
	getxya( t.ti_xpos, t.ti_ypos )
	shl	eax,8
	mov	al,tclrascii
	mov	t.ti_clat,eax  ; save text color
	.if	oflag & _O_DTEXT
		call	event_toend
		mov	eax,t.ti_xoff
		add	eax,t.ti_boff
		mov	t.ti_cleo,eax
	.endif
	call	modal
	push	eax
	call	putline
	CursorSet( addr cursor )
	pop	eax
	mov	TI,edi
	ret
dledit	ENDP

dledite PROC USES edi t:PVOID, event
	mov	edi,TI
	mov	eax,t
	mov	TI,eax
	call	getline
	call	putline
	mov	eax,event
	.if	!eax
		call	tgetevent
		mov	event,eax
	.endif
	call	ClipEvent
	call	tievent
	push	eax
	call	getline
	call	putline
	pop	edx
	xor	eax,eax
	.if	edx == _TE_RETEVENT
		mov	eax,event
	.endif
	mov	TI,edi
	ret
dledite ENDP

	END
