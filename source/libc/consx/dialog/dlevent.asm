include consx.inc
include io.inc
include time.inc
include crtl.inc

scroll_delay	PROTO

.data
tdialog PVOID 0
tdllist PVOID 0
thelp	PVOID 0
tdoffss dd 0
ocurs	S_CURSOR <0,0,0,0>
tobjp	dd 0
oflag	dd 0
orect	dd 0
oxpos	dd 0
oypos	dd 0
oxlen	dd 0
event	dd 0
result	dd 0
dlexit	dd 0
xlbuf	dw 256 dup(0)

_scancodes label BYTE	;  A - Z
	db 1Eh,30h,2Eh,20h,12h,21h,22h,23h,17h,24h,25h,26h,32h
	db 31h,18h,19h,10h,13h,1Fh,14h,16h,2Fh,11h,2Dh,15h,2Ch

ALIGN	4
proctab label DWORD
	dd case_ESC,case_ESC
  ifndef SKIP_ALTMOVE
	dd case_ALTUP,case_ALTDN,case_ALTLEFT,case_ALTRIGHT
  endif
	dd case_ENTER,case_ENTER,cmdmouse,case_LEFT,case_UP
	dd case_RIGHT,case_DOWN,case_HOME,case_END,case_TAB
	dd case_PGUP,case_PGDN

keytable label DWORD
	dd KEY_ESC,KEY_ALTX
  ifndef SKIP_ALTMOVE
	dd KEY_ALTUP,KEY_ALTDN,KEY_ALTLEFT,KEY_ALTRIGHT
  endif
	dd KEY_ENTER,KEY_KPENTER,MOUSECMD,KEY_LEFT,KEY_UP
	dd KEY_RIGHT,KEY_DOWN,KEY_HOME,KEY_END,KEY_TAB
	dd KEY_PGUP,KEY_PGDN
	key_count = ($ - offset keytable) / 4

eventproc label DWORD
	dd dlpbuttevent
	dd dlradioevent
	dd dlcheckevent
	dd dlxcellevent
	dd dlteditevent
	dd dlmenusevent
	dd dlxcellevent

	.code

	OPTION PROC:PRIVATE

handle_event PROC USES esi edi ebx

	.if eax
		mov edx,tdialog
		movzx ecx,[edx].S_DOBJ.dl_count
		mov edx,[edx].S_DOBJ.dl_object
		.if eax == KEY_F1
			xor eax,eax
			mov edx,tdialog
			.if [edx].S_DOBJ.dl_flag & _D_DHELP
				.if thelp != eax
					call thelp
					mov eax,_C_NORMAL
				.endif
			.endif
		.elseif !ecx
			xor eax,eax
		.else
			xor ebx,ebx
			xor esi,esi

			.repeat
				.if [edx].S_TOBJ.to_flag & _O_GLCMD
					mov ebx,[edx].S_TOBJ.to_data
				.endif
				push eax
				.if [edx].S_TOBJ.to_flag & _O_DEACT || [edx].S_TOBJ.to_ascii == 0
					xor eax,eax
				.else
					and al,0DFh
					.if [edx].S_TOBJ.to_ascii == al
						or al,1
					.else
						mov al,[edx].S_TOBJ.to_ascii
						and al,0DFh
						sub al,'A'
						push edx
						movzx edx,al
						cmp ah,_scancodes[edx]
						pop edx
						setz al
						test al,al
					.endif
				.endif
				pop eax
				.if !ZERO?
					test [edx].S_TOBJ.to_flag,_O_PBKEY
					mov eax,esi
					mov edx,tdialog
					mov [edx].S_DOBJ.dl_index,al
					mov eax,_C_RETURN
					jnz toend
					mov eax,_C_NORMAL
					jmp toend
				.endif
				add edx,16
				inc esi
			.untilcxz

			.if ebx
				mov edx,ebx
				.while	[edx].S_GLCMD.gl_key
					.if [edx].S_GLCMD.gl_key == eax
						call [edx].S_GLCMD.gl_proc
						jmp toend
					.endif
					add edx,SIZE S_GLCMD
				.endw
			.endif
			xor eax,eax
		.endif
	.endif
toend:
	mov result,eax
	ret
handle_event ENDP

test_event PROC
	xor edx,edx
	.repeat
		.if eax == keytable[edx]
			call proctab[edx]
			ret
		.endif
		add edx,4
	.untilcxz
	call handle_event
	ret
test_event ENDP

LoadCurrentObjectSaveCursor PROC
	push eax
	CursorGet(addr ocurs)
	pop eax
LoadCurrentObjectSaveCursor ENDP

LoadCurrentObject PROC
	mov edx,tdialog
	.if [edx].S_DOBJ.dl_count
		.if !eax
			movzx eax,[edx].S_DOBJ.dl_index
			inc eax
		.endif
		mov ecx,[edx+4]
		mov edx,[edx].S_DOBJ.dl_object
		dec eax
		shl eax,4
		add eax,edx
		mov tobjp,eax
		mov edx,eax
		movzx eax,[edx].S_DOBJ.dl_flag
		mov oflag,eax
		mov eax,[edx].S_TOBJ.to_rect
		mov orect,eax
		add WORD PTR orect,cx
		and eax,0FFh
		add al,cl
		mov oxpos,eax
		mov al,orect.S_RECT.rc_y
		mov oypos,eax
		mov al,orect.S_RECT.rc_col
		mov oxlen,eax
		movzx eax,[edx].S_TOBJ.to_flag
	.else
		xor eax,eax
	.endif
	ret
LoadCurrentObject ENDP

omousecmd PROC
	mousex()
	mov edx,eax
	mousey()
	.if eax == oypos
		mov eax,oxpos
		dec eax
		.if edx >= eax
			add eax,2
			.if edx <= eax
				or al,1
				ret
			.endif
		.endif
	.endif
	xor eax,eax
	mov eax,MOUSECMD
	ret
omousecmd ENDP

ExecuteChild PROC
	inc eax
	LoadCurrentObject()
	mov eax,[edx].S_TOBJ.to_proc
	.if eax
		call eax
		mov result,eax
		.if eax == _C_REOPEN
			mov edx,tdialog
			mov al,[edx].S_DOBJ.dl_index
			push eax
			dlinit(tdialog)
			pop eax
			mov edx,tdialog
			mov [edx].S_DOBJ.dl_index,al
		.endif
	.endif
	ret
ExecuteChild ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

item_init PROC
	mov	edx,tdialog
	movzx	eax,[edx].S_DOBJ.dl_count
	movzx	ecx,[edx].S_DOBJ.dl_index
	mov	edx,[edx].S_DOBJ.dl_object
	push	eax
	mov	eax,ecx
	shl	eax,4
	add	edx,eax
	pop	eax
	test	ecx,ecx
	ret
item_init ENDP

cl_to_index PROC
	dec	ecx
	mov	edx,tdialog
	mov	[edx].S_DOBJ.dl_index,cl
	xor	eax,eax
	inc	eax
	ret
cl_to_index ENDP

cl_to_index_if_act PROC
	test	[edx].S_TOBJ.to_flag,_O_DEACT
	jz	cl_to_index
	test	ch,ch
	ret
cl_to_index_if_act ENDP

previtem PROC
	call item_init

	.if !ZERO?
		sub edx,SIZE S_TOBJ		; prev object
		.repeat
			call cl_to_index_if_act
			.break .if !ZERO?
			sub edx,SIZE S_TOBJ
		.untilcxz
		jnz toend
		xor ecx,ecx
	.endif

	mov edx,tdialog
	add cl,[edx].S_DOBJ.dl_count
	.if !ZERO?
		movzx eax,[edx].S_DOBJ.dl_index
		mov edx,[edx].S_DOBJ.dl_object
		push eax
		mov eax,ecx
		dec eax
		shl eax,4
		add edx,eax
		pop eax
		.repeat
			.break .if al > cl
			test [edx].S_TOBJ.to_flag,_O_DEACT
			jz  cl_to_index
			sub edx,SIZE S_TOBJ
		.untilcxz
	.endif
	xor eax,eax
toend:
	mov result,eax
	ret
previtem ENDP

itemleft PROC
	call item_init
	jz  error
	sub edx,SIZE S_TOBJ		; prev object
	mov eax,[edx+20]		; RECT next object
	.repeat
		.if ah == [edx+5] && al > [edx+4]
			call cl_to_index_if_act
			jnz toend
		.endif
		sub edx,SIZE S_TOBJ
	.untilcxz
error:
	xor eax,eax
toend:
	mov result,eax
	ret
itemleft ENDP

nextitem PROC
	mov	edx,tdialog
	movzx	eax,[edx].S_DOBJ.dl_count
	movzx	ecx,[edx].S_DOBJ.dl_index
	inc	ecx
	mov	edx,[edx].S_DOBJ.dl_object
	push	eax
	mov	eax,ecx
	shl	eax,4
	add	edx,eax
	inc	ecx
	pop	eax
	.while	ecx <= eax
		call cl_to_index_if_act
		jnz toend
		inc ecx
		add edx,SIZE S_TOBJ
	.endw
	mov	eax,tdialog
	mov	edx,[eax].S_DOBJ.dl_object
	movzx	eax,[eax].S_DOBJ.dl_index
	inc	eax
	mov	ecx,1
	.while	ecx <= eax
		call cl_to_index_if_act
		jnz toend
		inc ecx
		add edx,SIZE S_TOBJ
	.endw
	xor eax,eax
toend:
	mov result,eax
	ret
nextitem ENDP

itemright PROC USES ebx
	mov	edx,tdialog
	movzx	ebx,[edx].S_DOBJ.dl_count
	movzx	ecx,[edx].S_DOBJ.dl_index
	inc	ecx
	mov	edx,[edx].S_DOBJ.dl_object
	mov	eax,ecx
	shl	eax,4
	add	edx,eax
	inc	ecx
	mov	ax,[edx-12]
	.while	ecx <= ebx
		.if ah == [edx+5] && al < [edx+4]
			call cl_to_index_if_act
			jnz  toend
		.endif
		inc ecx
		add edx,16
	.endw
	xor eax,eax
toend:
	mov result,eax
	ret
itemright ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

xbuttxchg PROC
	getxyc( oxpos, oypos )
	xchg	esi,eax
	scputc( oxpos, oypos, 1, eax )
	mov	eax,oxpos
	add	eax,oxlen
	dec	eax
	push	eax
	getxyc( eax, oypos )
	xchg	edi,eax
	pop	ebx
	scputc( ebx, oypos, 1, eax )
	ret
xbuttxchg ENDP

xbuttms PROC USES esi edi ebx
	mov	esi,' '
	mov	edi,esi
	call	xbuttxchg
	inc	ebx
	getxyc( ebx, oypos )
	push	eax
	sub	ebx,oxlen
	mov	eax,oypos
	inc	eax
	inc	ebx
	getxyc( ebx, eax )
	push	eax
	mov	eax,oflag
	and	eax,000Fh
	push	eax
	.if ZERO?
		mov eax,oypos
		inc eax
		scputc( ebx, eax, oxlen, ' ' )
		add ebx,oxlen
		dec ebx
		scputc( ebx, oypos, 1, ' ' )
	.endif
	call msloop
	call xbuttxchg
	pop edx
	pop eax
	pop edi
	.if !edx
		mov ebx,oxpos
		inc ebx
		mov edx,oypos
		inc edx
		scputc( ebx, edx, oxlen, eax )
		add ebx,oxlen
		dec ebx
		scputc( ebx, oypos, 1, edi )
	.endif
	ret
xbuttms ENDP

cmdmouse PROC USES esi edi ebp
	mov  edx,tdialog
	call mousex
	mov  ecx,eax
	call mousey
	mov ebp,eax
	mov result,_C_NORMAL
	.if rcxyrow( DWORD PTR [edx].S_DOBJ.dl_rect, ecx, eax )
		push eax
		mov edi,[edx].S_DOBJ.dl_rect
		mov al,[edx].S_DOBJ.dl_count
		mov esi,eax
		mov edx,[edx].S_DOBJ.dl_object
		.while	esi
			mov eax,[edx].S_TOBJ.to_rect
			add ax,di
			.if rcxyrow( eax, ecx, ebp )
				mov edx,tdialog
				pop eax
				sub eax,eax
				push eax
				mov al,[edx].S_DOBJ.dl_count
				sub eax,esi
				mov esi,eax
				inc eax
				call LoadCurrentObject
				.if !( eax & _O_DEACT )
					mov edx,tdialog
					mov eax,esi
					mov [edx].S_DOBJ.dl_index,al
					mov eax,oflag
					and al,0Fh
					.if al == _O_TBUTT || al == _O_PBUTT
						call xbuttms
					.endif
					mov eax,oflag
					.if eax & _O_DEXIT
						mov result,_C_ESCAPE
					.endif
					.if eax & _O_CHILD
					@@:
						mov  eax,esi
						call ExecuteChild
					.else
						and eax,000Fh
						.if al == _O_TBUTT || al == _O_PBUTT || \
							al == _O_MENUS || al == _O_XHTML
							mov result,_C_RETURN
						.endif
					.endif
				.else
					and eax,0Fh
					.if al == _O_LLMSU
						TDLListMouseUP()
					.elseif al == _O_LLMSD
						TDLListMouseDN()
					.elseif al == _O_MOUSE
						.if ecx & _O_CHILD
							mov eax,esi
							ExecuteChild()
						.endif
					.endif
				.endif
				.break
			.endif
			add edx,SIZE S_TOBJ
			dec esi
		.endw

		pop eax
		.if eax == 1
			dlmove(tdialog)
		.elseif eax
			msloop()
		.endif
	.else
		mov result,_C_ESCAPE
	.endif
	ret
cmdmouse ENDP

MouseDelay PROC
	.if mousep()
		scroll_delay()
		scroll_delay()
		or eax,1
	.endif
	ret
MouseDelay ENDP

TDLListMouseUP PROC
	mov edx,tdllist
	sub eax,eax
	cmp eax,[edx].S_LOBJ.ll_count
	jz  TDReturnNormal
	mov [edx].S_LOBJ.ll_celoff,eax
	mov eax,[edx].S_LOBJ.ll_dlgoff
	mov edx,tdialog
	cmp al,[edx].S_DOBJ.dl_index
	mov [edx].S_DOBJ.dl_index,al
	je  @F
	ret
      @@:
	call case_UP
	test eax,eax
	jz   TDReturnNormal
	call MouseDelay
	jnz @B
	jmp TDReturnNormal
TDLListMouseUP ENDP

TDLListMouseDN PROC
	mov edx,tdllist
	sub eax,eax
	cmp eax,[edx].S_LOBJ.ll_count
	jz  TDReturnNormal
	mov eax,[edx].S_LOBJ.ll_numcel
	dec eax
	mov [edx].S_LOBJ.ll_celoff,eax
	add eax,[edx]
	mov edx,tdialog
	cmp al,[edx].S_DOBJ.dl_index
	mov [edx].S_DOBJ.dl_index,al
	jz  @F
	sub eax,eax
	ret
      @@:
	call case_DOWN
	test eax,eax
	jz   TDReturnNormal
	call MouseDelay
	jnz  @B
TDLListMouseDN ENDP

TDReturnNormal PROC
	call	msloop
	mov	eax,_C_NORMAL
	ret
TDReturnNormal ENDP

TDListItem? PROC
	sub	eax,eax
	call	LoadCurrentObject
	test	eax,_O_LLIST
	jnz	@F
	and	eax,0Fh
	cmp	al,_O_MENUS
	je	@F
	mov	result,_C_NORMAL
	pop	eax
      @@:
	ret
TDListItem? ENDP

case_HOME PROC
	call	TDListItem?
	mov	eax,0
	jz	@F
	mov	edx,tdllist
	mov	[edx].S_LOBJ.ll_index,eax
	mov	[edx].S_LOBJ.ll_celoff,eax
	push	[edx].S_LOBJ.ll_dlgoff
	mov	eax,tdialog
	call	[edx].S_LOBJ.ll_proc
	pop	eax
      @@:
	mov	edx,tdialog
	mov	[edx].S_DOBJ.dl_index,al
	call	nextitem
	call	previtem
	ret
case_HOME ENDP

case_LEFT PROC
	sub eax,eax
	.if LoadCurrentObject() & _O_LLIST
		jmp case_PGUP
	.endif
	and eax,000Fh
	.if al == _O_MENUS
		jmp case_EXIT
	.endif
	call itemleft
	jz   case_UP
	ret
case_LEFT ENDP

case_RIGHT PROC
	xor eax,eax
	.if LoadCurrentObject() & _O_LLIST
		jmp case_PGDN
	.endif
	and eax,000Fh
	.if al == _O_MENUS
		jmp case_EXIT
	.endif
	itemright()
	jz case_DOWN
	ret
case_RIGHT ENDP

case_UP PROC
	xor eax,eax
	LoadCurrentObject()
	and eax,_O_LLIST
	.if !ZERO?
		xor eax,eax
		mov edx,tdllist
		.if eax == [edx].S_LOBJ.ll_celoff
			.if eax != [edx].S_LOBJ.ll_index
				mov ecx,[edx].S_LOBJ.ll_dlgoff
				mov edx,tdialog
				.if [edx].S_DOBJ.dl_index == cl
					mov edx,tdllist
					dec [edx].S_LOBJ.ll_index
					jmp case_LLPROC
				.endif
				mov [edx].S_DOBJ.dl_index,cl
				inc eax
			.endif
			ret
		.endif
	.endif
	previtem()
	ret
case_UP ENDP

case_DOWN PROC
	xor eax,eax
	LoadCurrentObject()
	and eax,_O_LLIST
	jz  case_NEXT
	mov edx,tdllist
	mov eax,[edx].S_LOBJ.ll_dcount
	mov ecx,[edx].S_LOBJ.ll_celoff
	dec eax
	.if eax != ecx
		mov eax,ecx
		add eax,[edx].S_LOBJ.ll_index
		inc eax
		cmp eax,[edx].S_LOBJ.ll_count
		jb  case_NEXT
	.endif
	mov eax,[edx].S_LOBJ.ll_dlgoff
	add eax,ecx
	mov edx,tdialog
	mov ah,[edx].S_DOBJ.dl_index
	mov [edx].S_DOBJ.dl_index,al
	cmp al,ah
	jne case_NORMAL
	mov edx,tdllist
	mov eax,[edx].S_LOBJ.ll_count
	sub eax,[edx].S_LOBJ.ll_index
	sub eax,[edx].S_LOBJ.ll_dcount
	jle return_NULL
	inc [edx].S_LOBJ.ll_index
case_DOWN ENDP

case_LLPROC PROC
	mov eax,tdialog
	call [edx].S_LOBJ.ll_proc
	jmp return_AX
case_LLPROC ENDP

case_EXIT PROC
	inc edi
case_EXIT ENDP

return_NULL PROC
	xor eax,eax
return_NULL ENDP

return_AX PROC
	mov result,eax
	ret
return_AX ENDP

case_NORMAL PROC
	mov result,_C_NORMAL
	ret
case_NORMAL ENDP

case_TAB PROC
	xor eax,eax
	call LoadCurrentObject
	and eax,_O_LLIST
	jz  case_NEXT
	mov edx,tdllist
	mov eax,[edx].S_LOBJ.ll_dlgoff
	add eax,[edx].S_LOBJ.ll_dcount
	mov edx,tdialog
	mov [edx].S_DOBJ.dl_index,al
	jmp case_NORMAL
case_TAB ENDP

case_NEXT PROC
	jmp nextitem
case_NEXT ENDP

case_ESC PROC
	mov result,_C_ESCAPE
	ret
case_ESC ENDP

case_PGUP PROC
	call TDListItem?
	jz  case_HOME
	mov edx,tdllist
	xor eax,eax
	.if eax == [edx].S_LOBJ.ll_celoff
		.if eax != [edx].S_LOBJ.ll_index
			mov eax,[edx].S_LOBJ.ll_dcount
			.if eax > [edx].S_LOBJ.ll_index
				jmp case_HOME
			.endif
			sub [edx].S_LOBJ.ll_index,eax
			jmp case_LLPROC
		.endif
	.else
		mov [edx].S_LOBJ.ll_celoff,eax
		mov eax,[edx].S_LOBJ.ll_dlgoff
		mov edx,tdialog
		mov [edx].S_DOBJ.dl_index,al
	.endif
	mov result,_C_NORMAL
	ret
case_PGUP ENDP

case_PGDN PROC
	call TDListItem?
	jz  case_END
	mov edx,tdllist
	mov eax,[edx].S_LOBJ.ll_dcount
	dec eax
	cmp eax,[edx].S_LOBJ.ll_celoff
	jz  case_PGDN_00
	mov eax,[edx].S_LOBJ.ll_numcel
	add eax,[edx].S_LOBJ.ll_dlgoff
	dec eax
	mov edx,tdialog
	mov [edx].S_DOBJ.dl_index,al
	mov result,_C_NORMAL
	ret
    case_PGDN_00:
	add eax,[edx].S_LOBJ.ll_celoff
	add eax,[edx].S_LOBJ.ll_index
	inc eax
	cmp eax,[edx].S_LOBJ.ll_count
	jnb case_END
	mov eax,[edx].S_LOBJ.ll_dcount
	add [edx].S_LOBJ.ll_index,eax
	jmp case_LLPROC
case_PGDN ENDP

case_END PROC
	call TDListItem?
	jnz @F
	mov edx,tdialog
	mov al,[edx].S_DOBJ.dl_count
	dec al
	mov [edx].S_DOBJ.dl_index,al
	call previtem
	call nextitem
	ret
@@:
	mov edx,tdllist
	mov eax,[edx].S_LOBJ.ll_count
	cmp eax,[edx].S_LOBJ.ll_dcount
	jnb @F
	mov eax,[edx].S_LOBJ.ll_numcel
	dec eax
	mov [edx].S_LOBJ.ll_celoff,eax
	add eax,[edx].S_LOBJ.ll_dlgoff
	mov edx,tdialog
	mov [edx].S_DOBJ.dl_index,al
	mov result,_C_NORMAL
	ret
@@:
	sub eax,[edx].S_LOBJ.ll_dcount
	cmp eax,[edx].S_LOBJ.ll_index
	jz  @F
	mov [edx].S_LOBJ.ll_index,eax
	mov eax,[edx].S_LOBJ.ll_dcount
	dec eax
	mov [edx].S_LOBJ.ll_celoff,eax
	add eax,[edx].S_LOBJ.ll_dlgoff
	mov edx,tdialog
	mov [edx].S_DOBJ.dl_index,al
	mov edx,tdllist
	jmp case_LLPROC
@@:
	jmp return_NULL
case_END ENDP

case_ENTER PROC
	xor eax,eax
	call LoadCurrentObject
	and eax,_O_CHILD
	mov eax,_C_RETURN
	jnz @F
	mov result,eax
	ret
@@:
	mov edx,tdialog
	movzx eax,[edx].S_DOBJ.dl_index
	call ExecuteChild
	ret
case_ENTER ENDP

OGOTOXY PROC
	xor eax,eax
	call LoadCurrentObjectSaveCursor
	call CursorOn
	inc oxpos
	_gotoxy(oxpos, oypos)
	ret
OGOTOXY ENDP

TDXORRADIO PROC USES edx ecx
	test BYTE PTR [edx].S_TOBJ.to_flag,_O_RADIO
	mov eax,' '
	jz  @F
	mov al,ASCII_RADIO
      @@:
	mov cx,[edx+4]
	mov edx,tdialog
	add cx,[edx+4]
	mov dl,ch
	inc ecx
	scputc(ecx, edx, 1, eax)
	ret
TDXORRADIO ENDP

xorradioflag PROC
	xor eax,eax
	LoadCurrentObject()
	and eax,_O_RADIO
	jnz break
	mov edx,tdialog
	sub ecx,ecx
	add cl,[edx].S_DOBJ.dl_count
	jz  toend
	mov edx,[edx].S_DOBJ.dl_object
@@:
	test BYTE PTR [edx].S_TOBJ.to_flag,_O_RADIO
	jnz @F
	add edx,16
	dec ecx
	jnz @B
	jmp toend
@@:
	and BYTE PTR [edx].S_TOBJ.to_flag,not _O_RADIO
	call TDXORRADIO
	xor  eax,eax
	call LoadCurrentObject
	or BYTE PTR [edx].S_TOBJ.to_flag,_O_RADIO
	call TDXORRADIO
break:
	call msloop
	mov eax,_C_NORMAL
toend:
	ret
xorradioflag ENDP

ORETURN PROC
	CursorSet(addr ocurs)
	ret
ORETURN ENDP

TDXORSWITCH PROC
	xor eax,eax
	call LoadCurrentObject
	xor eax,_O_FLAGB
	mov [edx],ax
	test eax,_O_FLAGB
	mov eax,' '
	jz  @F
	mov eax,'x'
@@:
	mov edx,orect
	mov cl,dh
	inc edx
	scputc(edx, ecx, 1, eax)
	call msloop
	xor eax,eax
	ret
TDXORSWITCH ENDP

TDTestXYRow PROC
	call mousey
	mov  edx,eax
	call mousex
	rcxyrow(orect, eax, edx)
	mov eax,MOUSECMD
	ret
TDTestXYRow ENDP

TDSelectObject PROC
	rcread( orect, addr xlbuf )
	mov eax,oflag
	and eax,0000000Fh
	.if eax == _O_MENUS
		mov al,at_background[B_InvMenus]
	.else
		mov al,at_background[B_Inverse]
	.endif
	wcputbg( addr xlbuf, oxlen, eax )
	rcxchg( orect, addr xlbuf )
	ret
TDSelectObject ENDP

TDDeselectObject PROC
	push eax
	rcwrite( orect, addr xlbuf )
	pop eax
	ret
TDDeselectObject ENDP

ifndef SKIP_ALTMOVE

case_ALTUP PROC
	mov eax,rcmoveup
	jmp case_ALTMOVE
case_ALTUP ENDP

case_ALTDN PROC
	mov eax,rcmovedn
	jmp case_ALTMOVE
case_ALTDN ENDP

case_ALTLEFT PROC
	mov eax,rcmoveleft
	jmp case_ALTMOVE
case_ALTLEFT ENDP

case_ALTRIGHT PROC
	mov eax,rcmoveright
case_ALTRIGHT ENDP

case_ALTMOVE PROC USES esi edi ebx
	mov	edi,tdialog
	movzx	ecx,[edi].S_DOBJ.dl_flag
	test	ecx,_D_DMOVE
	jz	toend
	mov	esi,[edi].S_DOBJ.dl_wp
	mov	ebx,[edi].S_DOBJ.dl_rect
	push	ecx
	push	esi
	push	ebx
	test	ecx,_D_SHADE
	jz	@F
	push	eax
	rcclrshade( ebx, esi )
	pop	eax
@@:
	call eax
	add esp,16
	mov bx,ax
	mov WORD PTR [edi].S_DOBJ.dl_rect,ax
	test [edi].S_DOBJ.dl_flag,_D_SHADE
	jz toend
	rcsetshade( ebx, esi )
toend:
	ret
case_ALTMOVE ENDP
endif

;-------------------------------------------------------------------------------

	OPTION PROC:PUBLIC

;-------------------------------------------------------------------------------

dlpbuttevent PROC USES esi edi
	xor eax,eax
	call LoadCurrentObjectSaveCursor
	call CursorOn
	mov eax,oxpos
	inc eax
	_gotoxy( eax, oypos )
	mov al,BYTE PTR oflag
	and al,0Fh
	.if al != _O_TBUTT
		call	CursorOff
	.endif
	movzx esi,ASCII_RIGHT
	movzx edi,ASCII_LEFT
	call xbuttxchg
	call tgetevent
	push eax
	call xbuttxchg
	CursorSet( addr ocurs )
	pop eax
	ret
dlpbuttevent ENDP

dlradioevent PROC
	OGOTOXY()
	.repeat
		tgetevent()
		.if eax == MOUSECMD
			omousecmd()
			jz toend
		.elseif eax != KEY_SPACE
			jmp toend
		.endif
		xorradioflag()
	.until oflag & _O_EVENT
	mov eax,KEY_SPACE
toend:
	ORETURN()
	ret
dlradioevent ENDP

dlcheckevent PROC
	OGOTOXY()
	.repeat
		tgetevent()
		.if eax == MOUSECMD
			omousecmd()
			jz toend
			TDXORSWITCH()
		.elseif eax == KEY_SPACE
			TDXORSWITCH()
		.else
			jmp toend
		.endif
	.until	oflag & _O_EVENT
	mov eax,KEY_SPACE
toend:
	ORETURN()
	ret
dlcheckevent ENDP

dlxcellevent PROC USES esi

	xor eax,eax
	LoadCurrentObject()

	.if !ZERO?

		CursorOff()
	.endif

	.if oflag & _O_LLIST

		mov edx,tdialog
		movzx eax,[edx].S_DOBJ.dl_index
		mov edx,tdllist

		.if eax >= [edx].S_LOBJ.ll_dlgoff
			sub eax,[edx].S_LOBJ.ll_dlgoff
			.if eax < [edx].S_LOBJ.ll_numcel
				mov [edx].S_LOBJ.ll_celoff,eax
			.endif
		.endif
	.endif
	TDSelectObject()
lupe:
	call	tgetevent
	cmp	eax,KEY_MOUSEUP
	je	mouseup
	cmp	eax,KEY_MOUSEDN
	je	mousedn
	cmp	eax,MOUSECMD
	jne	done
	call	TDTestXYRow
	jz	done
	mousewait( oxpos, oypos, oxlen )
	mov	eax,oflag
	and	eax,000Fh
	cmp	eax,_O_XHTML
	mov	eax,KEY_ENTER
	jz	done
	mov	esi,10
	.while	!ZERO?
		Sleep ( 16 )
		call	mousep
		.break .if !ZERO?
		dec	esi
	.endw
	mousep()
	jz lupe
	TDTestXYRow()
	jz lupe
	mov eax,KEY_ENTER
done:
	test eax,eax
	jz lupe
toend:
	TDDeselectObject()
	ret
mouseup:
	mov eax,KEY_UP
	test oflag,_O_LLIST
	jz toend
	PushEvent(eax)
	jmp	@F
mousedn:
	mov eax,KEY_DOWN
	test oflag,_O_LLIST
	jz	toend
	PushEvent(eax)
@@:
	PushEvent(eax)
	jmp toend
dlxcellevent ENDP

dlteditevent PROC
	push	esi
	mov	edx,tdialog
	mov	si,[edx+4]
	sub	eax,eax
	call	LoadCurrentObject
	mov	eax,[edx].S_TOBJ.to_rect
	add	ax,si
	movzx	ecx,[edx].S_TOBJ.to_count
	shl	ecx,4
	dledit( [edx].S_TOBJ.to_data, eax, ecx, oflag )
	pop	esi
	ret
dlteditevent ENDP

dlmenusevent PROC

	CursorOff()

	xor eax,eax
	LoadCurrentObjectSaveCursor()

	.if [edx].S_TOBJ.to_data
		mov al,' '
		mov ah,at_background[B_Menus]
		or  ah,at_foreground[F_KeyBar]
		mov ecx,_scrrow
		scputw( 20, ecx, 60, eax )
		scputs( 20, ecx, 0, 60, [edx].S_TOBJ.to_data )
	.endif
	TDSelectObject()
	tgetevent()
	.if eax == KEY_MOUSEUP
		mov eax,KEY_UP
	.elseif eax == KEY_MOUSEDN
		mov eax,KEY_DOWN
	.endif
	TDDeselectObject()
	CursorSet( addr ocurs )
	ret
dlmenusevent ENDP

dlevent PROC USES esi edi ebx dialog:PTR S_DOBJ

	local	prevdlg:DWORD	; init tdialog
	local	cursor:S_CURSOR ; init cursor

	mov eax,tdialog
	mov prevdlg,eax
	mov eax,dialog
	mov tdialog,eax
	mov ebx,tdialog
	movzx esi,[ebx].S_DOBJ.dl_flag

	.if !( esi & _D_ONSCR )
		dlshow( dialog )
		jz toend
	.endif

	CursorGet( addr cursor )
	CursorOff()
	movzx eax,[ebx].S_DOBJ.dl_count
	.if eax
		xor eax,eax
		.if LoadCurrentObject() & _O_DEACT
			nextitem()
		.endif
		mov eax,1
	.endif
	.if !eax
		.while	1
			tgetevent()
			mov ecx,9
			test_event()
			mov eax,result
			.break .if eax == _C_ESCAPE
			.break .if eax == _C_RETURN
		.endw
	.else

		msloop()
		xor edi,edi

		.repeat
			xor eax,eax
			mov result,eax

			.if LoadCurrentObject() & _O_EVENT
				call [edx].S_TOBJ.to_proc
			.else
				mov al,[edx]
				and eax,0Fh
				.if al > 6
					.if al == _O_TBUTT
						dlpbuttevent()
					.else
						mov eax,KEY_ESC
					.endif
				.else
					call eventproc[eax*4]
				.endif
			.endif

			mov dlexit,eax
			mov event,eax
			mov ecx,key_count
			test_event()
			mov eax,result
			.if eax == _C_ESCAPE
				mov event,0
				.break
			.elseif eax == _C_RETURN
				xor eax,eax
				.if LoadCurrentObject() & _O_DEXIT
					mov event,0
				.else
					mov edx,tdialog
					movzx eax,[edx].S_DOBJ.dl_index
					inc eax
					mov event,eax
				.endif
				.break
			.endif
		.until	edi
	.endif
	CursorSet( addr cursor )
	mov eax,event
toend:
	mov edx,eax
	mov eax,prevdlg
	mov tdialog,eax
	mov eax,edx
	mov ecx,dlexit
	test eax,eax
	ret
dlevent ENDP

Install:
	mov eax,getevent
	mov tgetevent,eax
	ret

pragma_init	Install,32

	END
