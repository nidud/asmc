include consx.inc
include string.inc
include ctype.inc

tinocando	PROTO
tidecx		PROTO :PTR S_TEDIT
tiincx		PROTO :PTR S_TEDIT
tistripend	PROTO :LPSTR
tiisword	PROTO

	.code

	OPTION	WIN64:3, STACKBASE:rsp
	OPTION	PROC: PRIVATE
	ASSUME	r12: PTR S_TEDIT

getline PROC USES rsi rdi

	mov	rax,[r12].ti_bp
	.if	rax
		mov	rsi,rax
		mov	rdi,rax
		mov	ecx,[r12].ti_bcol	; terminate line
		xor	eax,eax			; set length of line
		mov	[rdi+rcx-1],al
		mov	ecx,-1
		repne	scasb
		not	ecx
		dec	ecx
		dec	rdi
		mov	[r12].ti_bcnt,ecx
		sub	ecx,[r12].ti_bcol	; clear rest of line
		neg	ecx
		rep	stosb
		mov	ecx,[r12].ti_bcnt
		mov	rax,[r12].ti_bp
		test	rax,rax
	.endif
	ret
getline ENDP

curlptr PROC
	getline()
	.if	!ZERO?
		add eax,[r12].ti_boff
		add eax,[r12].ti_xoff
	.endif
	ret
curlptr ENDP

needline PROC
	getline()
	.if	ZERO?
		pop rax			; pop caller off the stack
		mov rax,_TE_CMFAILED	; operation fail (end of line/buffer)
	.endif
	ret
needline ENDP

event_home PROC
	call	needline
	xor	eax,eax
	mov	[r12].ti_boff,eax
	mov	[r12].ti_xoff,eax
	ret
event_home ENDP

event_toend PROC
	call	event_home
	call	needline
	tistripend( rax )
	.if	ecx
		mov	eax,[r12].ti_cols
		dec	eax
		.if	SDWORD PTR ecx <= eax
			mov eax,ecx
		.endif
		mov	[r12].ti_xoff,eax
		mov	ecx,[r12].ti_bcnt
		sub	ecx,[r12].ti_cols
		inc	ecx
		xor	eax,eax
		.if	SDWORD PTR eax <= ecx
			mov eax,ecx
		.endif
		mov	[r12].ti_boff,eax
		add	eax,[r12].ti_xoff
		.if	eax > [r12].ti_bcnt
			dec [r12].ti_boff
		.endif
	.endif
	xor	eax,eax
	ret
event_toend ENDP

event_left PROC
	xor	eax,eax
	.if	eax != [r12].ti_xoff
		dec [r12].ti_xoff
	.elseif eax != [r12].ti_boff
		dec [r12].ti_boff
	.else
		mov	eax,_TE_CMFAILED
		.if	[r12].ti_flag & _TE_DLEDIT
			mov eax,_TE_RETEVENT
		.endif
	.endif
	ret
event_left ENDP

event_right PROC
	call	curlptr
	mov	rcx,rax
	mov	al,[rax]
	sub	ecx,[r12].ti_xoff

	.if	al
		mov	eax,[r12].ti_cols
		dec	eax
		.if	eax > [r12].ti_xoff
			inc	[r12].ti_xoff
			xor	eax,eax
			ret
		.endif
	.endif

	strlen( rcx )
	.if	eax >= [r12].ti_cols
		inc	[r12].ti_boff
		xor	eax,eax
		ret
	.endif

	mov	eax,_TE_CMFAILED
	.if	[r12].ti_flag & _TE_DLEDIT
		mov	eax,_TE_RETEVENT
	.endif
	ret
event_right ENDP

event_delete PROC
	call	curlptr
	.if	!ZERO?
		tistripend( rax )
		call	curlptr
		.if	ecx && BYTE PTR [rax]
			dec	[r12].ti_bcnt
			mov	rcx,rax
			inc	rax
			strcpy( rcx, rax )
			or	[r12].ti_flag,_TE_MODIFIED
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
	mov	eax,[r12].ti_xoff
	add	eax,[r12].ti_boff
	jz	error
	test	ecx,ecx
	jz	error
	call	event_left
	call	curlptr
	tistripend( rax )
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

event_add PROC USES rbx
	mov	rbx,rax
	call	getline
	jz	nocando
	movzx	rax,bl
	lea	r8,_ctype
	test	BYTE PTR [r8+rax*2+2],_CONTROL
	jnz	control
add_char:
	mov	eax,[r12].ti_bcnt
	inc	eax
	cmp	eax,[r12].ti_bcol
	jae	endoffline
	tiincx( r12 )
	jz	endoffline
	inc	[r12].ti_bcnt
	call	getline
	jz	endoffline
	or	[r12].ti_flag,_TE_MODIFIED
	mov	rax,[r12].ti_bp
	add	eax,[r12].ti_boff
	add	eax,[r12].ti_xoff
	dec	rax
	strshr( rax, ebx )
done:
	sub	eax,eax
toend:
	ret
endoffline:
	mov	eax,[r12].ti_bcol
	dec	eax
	mov	[r12].ti_bcnt,eax
nocando:
	call	tinocando
	jmp	toend
control:
	test	bl,bl
	jz	@F
	test	[r12].ti_flag,_TE_USECONTROL
	jnz	add_char
@@:
	mov	eax,_TE_RETEVENT
	jmp	toend
event_add ENDP

tsetcursor PROC
  local cursor:S_CURSOR
	mov	eax,[r12].S_TEDIT.ti_xpos
	add	eax,[r12].S_TEDIT.ti_xoff
	mov	ecx,[r12].S_TEDIT.ti_ypos
	mov	cursor.x,ax
	mov	cursor.y,cx
	mov	cursor.bVisible,1
	mov	cursor.dwSize,CURSOR_NORMAL
	CursorSet( addr cursor )
	ret
tsetcursor ENDP

event_nextword PROC USES rsi
	call	curlptr
	jz	toend
	mov	rsi,rax		; to end of word
	mov	rcx,rax
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
	dec	rsi
	sub	rsi,rcx
	mov	eax,[r12].ti_boff
	add	eax,[r12].ti_xoff
	add	eax,esi
	cmp	eax,[r12].ti_bcnt
	ja	toend
	sub	eax,[r12].ti_boff
	mov	ecx,[r12].ti_cols
	cmp	eax,ecx
	jb	@F
	dec	ecx
	sub	eax,ecx
	add	[r12].ti_boff,eax
	mov	[r12].ti_xoff,ecx
	jmp	continue
@@:
	mov	[r12].ti_xoff,eax
continue:
	mov	eax,_TE_CONTINUE
toend:
	ret
event_nextword ENDP

event_prevword PROC USES rsi
	call	getline
	test	rax,rax
	jz	toend
	mov	rcx,rax
	mov	eax,[r12].ti_boff
	add	eax,[r12].ti_xoff
	jz	toend
	mov	rsi,rax
	add	rsi,rcx
	mov	al,[rsi]
	call	tiisword
	jz	@F
	mov	al,[rsi-1]
	call	tiisword
	jnz	lup2
	dec	rsi
	jmp	lup
@@:
	test	al,al
	jnz	lup
	dec	rsi
lup:
	cmp	rsi,rcx
	je	set
	jb	home
	mov	al,[rsi]
	dec	rsi
	cmp	rsi,rcx
	jbe	home
	test	al,al
	jz	home
	call	tiisword
	jz	lup
lup2:
	mov	al,[rsi]
	dec	rsi
	cmp	rsi,rcx
	jb	home
	je	set
	test	al,al
	jz	home
	call	tiisword
	jnz	lup2
	add	rsi,2
set:
	mov	rax,rsi
	sub	rax,rcx
	cmp	eax,[r12].ti_cols
	jnb	@F
	mov	[r12].ti_xoff,eax
	mov	[r12].ti_boff,0
	jmp	done
@@:
	sub	eax,[r12].ti_xoff
	mov	[r12].ti_boff,eax
done:
	mov	eax,_TE_CONTINUE
toend:
	ret
home:
	call	event_home
	jmp	toend
event_prevword ENDP

event_mouse PROC USES rbx
	mov	ebx,keybmouse_y
	mov	ecx,keybmouse_x
	mov	eax,[r12].ti_xpos
	cmp	ecx,eax
	jb	event
	add	eax,[r12].ti_cols
	cmp	ecx,eax
	jae	event
	mov	eax,[r12].ti_ypos
	cmp	ebx,eax
	jne	event
	mov	ebx,ecx
	call	getline
	jz	@F
	strlen( rax )
@@:
	sub	ebx,[r12].ti_xpos
	cmp	ebx,eax
	jg	@F
	mov	eax,ebx
@@:
	mov	[r12].ti_xoff,eax
	call	tsetcursor
	call	msloop
	sub	eax,eax
toend:
	ret
event:
	mov	eax,_TE_RETEVENT
	jmp	toend
event_mouse ENDP

tievent PROC
	mov	ecx,[r12].ti_flag
	.switch eax
	  .case _TE_CONTINUE
		ret
	  .case KEY_CTRLRIGHT
		event_nextword()
		ret
	  .case KEY_CTRLLEFT
		event_prevword()
		ret
	  .case KEY_LEFT
		event_left()
		ret
	  .case KEY_RIGHT
		event_right()
		ret
	  .case KEY_HOME
		event_home()
		ret
	  .case KEY_END
		event_toend()
		ret
	  .case KEY_BKSP
		event_backsp()
		ret
	  .case KEY_TAB
		event_tab()
	  .case KEY_DEL
		event_delete()
		ret
	  .case MOUSECMD
		event_mouse()
		ret
	  .case KEY_UP
	  .case KEY_DOWN
	  .case KEY_PGUP
	  .case KEY_PGDN
	  .case KEY_CTRLPGUP
	  .case KEY_CTRLPGDN
	  .case KEY_CTRLHOME
	  .case KEY_CTRLEND
	  .case KEY_CTRLUP
	  .case KEY_CTRLDN
	  .case KEY_MOUSEUP
	  .case KEY_MOUSEDN
	  .case KEY_ENTER
	  .case KEY_KPENTER
	  .case KEY_ESC
		mov	eax,_TE_RETEVENT
		ret
	.endsw
	call	event_add
	ret
tievent ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

ClipIsSelected PROC
	mov	eax,[r12].ti_cleo
	sub	eax,[r12].ti_clso
	ret
ClipIsSelected ENDP

ClipSet PROC
	mov	eax,[r12].ti_xoff
	add	eax,[r12].ti_boff
	mov	[r12].ti_clso,eax
	mov	[r12].ti_cleo,eax
	ret
ClipSet ENDP

ClipDelete PROC
	.if	ClipIsSelected()
		mov	eax,[r12].ti_clso
		mov	ecx,[r12].ti_xoff
		add	ecx,[r12].ti_boff
		.if	ecx < eax
			.repeat
				tiincx( r12 )
				.break .if ZERO?
				inc	ecx
			.until	eax == ecx
			inc	ecx
		.elseif ecx > eax
			.repeat
				tidecx( r12 )
				.break .if ZERO?
				dec	ecx
			.until	eax == ecx
			inc	ecx
		.endif
		mov	rcx,[r12].ti_bp
		or	[r12].ti_flag,_TE_MODIFIED
		mov	rdx,rcx
		add	ecx,[r12].ti_clso
		add	edx,[r12].ti_cleo
		strcpy( rcx, rdx )
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

ClipCC	PROC USES rdi
	mov	edi,eax		; AX: Copy == 0, Cut == 1
	call	ClipIsSelected	; get size of selection
	jz	@F
	mov	rax,[r12].ti_bp
	add	eax,[r12].ti_clso
	mov	edx,[r12].ti_cleo
	sub	edx,[r12].ti_clso
	ClipboardCopy( rax, edx )
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

ClipPaste PROC USES rsi rdi rbx rbp

	mov	eax,[r12].ti_flag
	.if	eax & _TE_OVERWRITE
		call	ClipDelete
	.else
		call	ClipSet
	.endif
	call	ClipboardPaste
	.if	!ZERO?

		mov	ebx,[r12].ti_xoff
		mov	ebp,[r12].ti_boff
		mov	rdi,rax
		mov	esi,ecx ; clipbsize
		.repeat
			mov	al,[rdi]
			.break .if !al
			inc	rdi
			.break .if event_add() != _TE_CONTINUE
			dec	esi
		.until	ZERO?
		call	ClipboardFree
		mov	[r12].ti_boff,ebp
		mov	[r12].ti_xoff,ebx
	.endif
	call	ClipSet
	xor	eax,eax
	ret
ClipPaste ENDP

ClipEvent PROC USES rsi rdi rbx
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
	mov	rax,keyshift
	mov	eax,[rax]
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
	mov	eax,[r12].ti_boff
	add	eax,[r12].ti_xoff
	cmp	eax,[r12].ti_clso
	jb	@back
	cmp	esi,KEY_RIGHT
	jne	@F
	mov	edx,eax
	dec	edx
	cmp	edx,[r12].ti_clso
	jne	@F
	cmp	edx,[r12].ti_cleo
	jne	@back
@@:
	mov	[r12].ti_cleo,eax
	jmp	@null
@back:
	mov	[r12].ti_clso,eax
	jmp	@null
ClipEvent ENDP

putline PROC USES rsi rdi rbx
  local ci[256]:DWORD
  local bz:COORD
  local rc:SMALL_RECT
	call	tsetcursor
	lea	rdi,ci
	mov	ebx,[r12].ti_cols
	mov	eax,[r12].ti_clat
	mov	cl,al
	mov	al,0
	shl	eax,8
	mov	al,cl
	mov	ecx,ebx
	rep	stosd
	mov	rsi,[r12].ti_bp
	strlen( rsi )
	.if	eax > [r12].ti_boff
		add	esi,[r12].ti_boff
		mov	ecx,ebx
		lea	rdi,ci
		.repeat
			mov	al,[rsi]
			.break .if !al
			mov	[rdi],al
			inc	rsi
			add	rdi,4
		.untilcxz
	.endif
	mov	edi,[r12].ti_boff
	mov	ecx,[r12].ti_cleo
	.if	edi < ecx
		sub	ecx,edi
		.if	!ZERO?
			mov	eax,[r12].ti_clso
			sub	eax,edi
			sub	ecx,eax
			.if	!ZERO?
				.if	ecx >= ebx
					mov ecx,ebx
				.endif
				lea	rdi,ci
				lea	rdi,[rdi+rax*4+2]
				mov	al,at_background[B_Inverse]
				.repeat
					mov [rdi],al
					add rdi,4
				.untilcxz
			.endif
		.endif
	.endif
	mov	ecx,ebx
	mov	bz.x,cx
	mov	eax,[r12].ti_xpos
	mov	rc.Left,ax
	add	eax,ecx
	dec	eax
	mov	rc.Right,ax
	mov	eax,[r12].ti_ypos
	mov	rc.Top,ax
	mov	rc.Bottom,ax
	mov	bz.y,1
	WriteConsoleOutput( hStdOutput, addr ci, bz, 0, addr rc )
	ret
putline ENDP

modal	PROC USES rsi rdi
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

dledit	PROC USES rsi rdi r12 b:LPSTR, rc, bz, oflag

  local t:S_TEDIT
  local cursor:S_CURSOR

	CursorGet( addr cursor )

	lea	r12,t
	xor	eax,eax
	mov	rdi,r12
	mov	rcx,SIZE S_TEDIT
	rep	stosb

	movzx	eax,rc.S_RECT.rc_x
	mov	t.ti_xpos,eax
	mov	al,rc.S_RECT.rc_y
	mov	t.ti_ypos,eax
	mov	al,rc.S_RECT.rc_col
	mov	t.ti_cols,eax
	mov	eax,bz
	mov	t.ti_bcol,eax
	mov	rax,b
	mov	t.ti_bp,rax
	mov	eax,oflag
	and	eax,_O_CONTR or _O_DLGED
	or	eax,_TE_OVERWRITE
	mov	t.ti_flag,eax
	call	tsetcursor

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
	mov	esi,eax
	call	putline
	CursorSet( addr cursor )
	mov	eax,esi
	ret
dledit	ENDP

dledite PROC USES rsi r12 t:PVOID, event:DWORD

	mov	r12,rcx
	call	getline
	call	putline
	mov	eax,event
	.if	!eax
		call	tgetevent
		mov	event,eax
	.endif
	call	ClipEvent
	call	tievent
	mov	esi,eax
	call	getline
	call	putline
	mov	edx,esi
	xor	eax,eax
	.if	edx == _TE_RETEVENT
		mov	eax,event
	.endif
	ret
dledite ENDP

	END
