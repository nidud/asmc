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
tobjp	dq 0
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

ALIGN	8
keytable label S_GLCMD
	S_GLCMD <KEY_ESC,	case_ESC>
	S_GLCMD <KEY_ALTX,	case_ESC>
  ifndef SKIP_ALTMOVE
	S_GLCMD <KEY_ALTUP,	case_ALTUP>
	S_GLCMD <KEY_ALTDN,	case_ALTDN>
	S_GLCMD <KEY_ALTLEFT,	case_ALTLEFT>
	S_GLCMD <KEY_ALTRIGHT,	case_ALTRIGHT>
  endif
	S_GLCMD <KEY_ENTER,	case_ENTER>
	S_GLCMD <KEY_KPENTER,	case_ENTER>
	S_GLCMD <MOUSECMD,	cmdmouse>
	S_GLCMD <KEY_LEFT,	case_LEFT>
	S_GLCMD <KEY_UP,	case_UP>
	S_GLCMD <KEY_RIGHT,	case_RIGHT>
	S_GLCMD <KEY_DOWN,	case_DOWN>
	S_GLCMD <KEY_HOME,	case_HOME>
	S_GLCMD <KEY_END,	case_END>
	S_GLCMD <KEY_TAB,	case_TAB>
	S_GLCMD <KEY_PGUP,	case_PGUP>
	S_GLCMD <KEY_PGDN,	case_PGDN>

	key_count = ($ - offset keytable) / sizeof(S_GLCMD)

eventproc label QWORD
	dq dlpbuttevent
	dq dlradioevent
	dq dlcheckevent
	dq dlxcellevent
	dq dlteditevent
	dq dlmenusevent
	dq dlxcellevent

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE, PROC:PRIVATE
;	OPTION WIN64:0, STACKBASE:rsp, PROC:PRIVATE

test_event PROC event_count:qword, levent:qword

	mov	eax,edx
	lea	r10,keytable

	.repeat
		cmp	eax,[r10].S_GLCMD.gl_key
		je	glcmd
		add	r10,sizeof(S_GLCMD)
	.untilcxz

	.if	eax

		mov	r8,tdialog
		movzx	ecx,[r8].S_DOBJ.dl_count
		mov	rdx,[r8].S_DOBJ.dl_object

		.if	eax == KEY_F1

			xor	eax,eax

			.if	[r8].S_DOBJ.dl_flag & _D_DHELP

				.if	thelp != rax

					call	thelp
					mov	eax,_C_NORMAL
				.endif
			.endif

		.elseif !ecx

			xor	eax,eax
		.else
			xor	r10,r10
			xor	r11,r11

			.repeat
				.if	[rdx].S_TOBJ.to_flag & _O_GLCMD

					mov	r10,[rdx].S_TOBJ.to_data
				.endif

				push	rax
				.if	[rdx].S_TOBJ.to_flag & _O_DEACT || \
					[rdx].S_TOBJ.to_ascii == 0

					xor	eax,eax
				.else

					and	al,0DFh
					.if	[rdx].S_TOBJ.to_ascii == al

						or	al,1
					.else

						mov	al,[rdx].S_TOBJ.to_ascii
						and	al,0DFh
						sub	al,'A'

						push	rcx
						movzx	rcx,al
						lea	r9,_scancodes
						add	r9,rcx
						pop	rcx
						mov	al,ah
						cmp	al,[r9]
						setz	al
						test	al,al
					.endif
				.endif
				pop	rax

				.if	!ZERO?
					test	[rdx].S_TOBJ.to_flag,_O_PBKEY
					mov	[r8].S_DOBJ.dl_index,r11b
					mov	eax,_C_RETURN
					jnz	toend
					mov	eax,_C_NORMAL
					jmp	toend
				.endif

				add	rdx,sizeof(S_TOBJ)
				inc	r11
			.untilcxz

			.if	r10

				.while	[r10].S_GLCMD.gl_key

					cmp	eax,[r10].S_GLCMD.gl_key
					je	glcmd
					add	r10,SIZE S_GLCMD
				.endw
			.endif
			xor	eax,eax
		.endif
	.endif
toend:
	mov	result,eax
	ret
glcmd:
	mov	r10,[r10].S_GLCMD.gl_proc
	call	r10
	jmp	toend
test_event ENDP

save_cursor:
	push	rax
	GetCursor( addr ocurs )
	pop	rax

load_object:
	mov	r8,tdialog
	.if	[r8].S_DOBJ.dl_count
		.if	!eax
			movzx	eax,[r8].S_DOBJ.dl_index
			inc	eax
		.endif
		dec	eax
		imul	rax,rax,sizeof(S_TOBJ)
		mov	ecx,[r8+4]
		add	rax,[r8].S_DOBJ.dl_object
		mov	tobjp,rax
		mov	rdx,rax
		movzx	eax,[rdx].S_TOBJ.to_flag
		mov	oflag,eax
		mov	eax,[rdx].S_TOBJ.to_rect
		mov	orect,eax
		add	WORD PTR orect,cx
		and	eax,0FFh
		add	al,cl
		mov	oxpos,eax
		mov	al,orect.S_RECT.rc_y
		mov	oypos,eax
		mov	al,orect.S_RECT.rc_col
		mov	oxlen,eax
		movzx	eax,[rdx].S_TOBJ.to_flag
	.else
		xor	eax,eax
	.endif
	ret

omousecmd:
	call	mousex
	mov	edx,eax
	call	mousey
	.if	eax == oypos
		mov	eax,oxpos
		dec	eax
		.if	edx >= eax
			add	eax,2
			.if	edx <= eax
				or al,1
				ret
			.endif
		.endif
	.endif
	xor	eax,eax
	mov	eax,MOUSECMD
	ret

ExecuteChild:
	push	rbx
	inc	eax
	call	load_object
	mov	rax,[rdx].S_TOBJ.to_proc
	.if	rax
		call	rax
		mov	result,eax
		.if	eax == _C_REOPEN
			mov	rdx,tdialog
			mov	bl,[rdx].S_DOBJ.dl_index
			dlinit( tdialog )
			mov	rdx,tdialog
			mov	[rdx].S_DOBJ.dl_index,bl
		.endif
	.endif
	pop	rbx
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

item_init:
	mov	rdx,tdialog
	movzx	rax,[rdx].S_DOBJ.dl_count
	movzx	rcx,[rdx].S_DOBJ.dl_index
	mov	rdx,[rdx].S_DOBJ.dl_object
	push	rax
	imul	rax,rcx,sizeof(S_TOBJ)
	add	rdx,rax
	pop	rax
	test	rcx,rcx
	ret

cl_to_index:
	dec	ecx
	mov	rdx,tdialog
	mov	[rdx].S_DOBJ.dl_index,cl
	xor	eax,eax
	inc	eax
	ret

cl_to_index_if_act:
	test	[rdx].S_TOBJ.to_flag,_O_DEACT
	jz	cl_to_index
	test	ch,ch
	ret

previtem:
	call	item_init

	.if	!ZERO?
		sub	rdx,SIZE S_TOBJ		; prev object
		.repeat
			call	cl_to_index_if_act
			.break .if !ZERO?
			sub	rdx,SIZE S_TOBJ
		.untilcxz
		jnz	@F
		xor	ecx,ecx
	.endif

	mov	rdx,tdialog
	add	cl,[rdx].S_DOBJ.dl_count
	.if	!ZERO?
		movzx	rax,[rdx].S_DOBJ.dl_index
		mov	rdx,[rdx].S_DOBJ.dl_object
		push	rax
		mov	rax,rcx
		dec	rax
		imul	rax,rax,sizeof(S_TOBJ)
		add	rdx,rax
		pop	rax
		.repeat
			.break .if al > cl
			test	[rdx].S_TOBJ.to_flag,_O_DEACT
			jz	cl_to_index
			sub	rdx,SIZE S_TOBJ
		.untilcxz
	.endif
	xor	eax,eax
@@:
	mov	result,eax
	ret

itemleft:
	call	item_init
	jz	@F

	sub	rdx,SIZE S_TOBJ		; prev object
	mov	eax,[rdx+SIZE S_TOBJ+4] ; RECT next object

	.repeat
		.if	ah == [rdx+5] && al > [rdx+4]
			call	cl_to_index_if_act
			jnz	@B
		.endif
		sub	rdx,SIZE S_TOBJ
	.untilcxz
@@:
	xor	eax,eax
	mov	result,eax
	ret

nextitem:
	mov	rdx,tdialog
	movzx	rax,[rdx].S_DOBJ.dl_count
	movzx	rcx,[rdx].S_DOBJ.dl_index
	inc	rcx
	mov	rdx,[rdx].S_DOBJ.dl_object
	push	rax
	mov	rax,rcx
	imul	rax,rax,sizeof(S_TOBJ)
	add	rdx,rax
	inc	rcx
	pop	rax
	.while	ecx <= eax
		call	cl_to_index_if_act
		jnz	@F
		inc	ecx
		add	rdx,SIZE S_TOBJ
	.endw

	mov	rax,tdialog
	mov	rdx,[rax].S_DOBJ.dl_object
	movzx	rax,[rax].S_DOBJ.dl_index
	inc	rax

	mov	ecx,1
	.while	ecx <= eax
		call	cl_to_index_if_act
		jnz	@F
		inc	ecx
		add	rdx,SIZE S_TOBJ
	.endw
	xor	eax,eax
@@:
	mov	result,eax
	ret

itemright:
	push	rbx

	mov	rdx,tdialog
	movzx	rbx,[rdx].S_DOBJ.dl_count
	movzx	rcx,[rdx].S_DOBJ.dl_index
	inc	rcx
	mov	rdx,[rdx].S_DOBJ.dl_object
	mov	rax,rcx
	imul	rax,rax,sizeof(S_TOBJ)
	add	rdx,rax
	inc	rcx
	mov	ax,[rdx-sizeof(S_TOBJ)+4]

	.while	ecx <= ebx
		.if	ah == [rdx+5] && al < [rdx+4]
			call cl_to_index_if_act
			jnz  @F
		.endif
		inc	ecx
		add	rdx,sizeof(S_TOBJ)
	.endw
	xor	eax,eax
@@:
	mov	result,eax
	pop	rbx
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

xbuttxchg:
	push	rbx
	getxyc( oxpos, oypos )
	xchg	esi,eax
	scputc( oxpos, oypos, 1, eax )
	mov	eax,oxpos
	add	eax,oxlen
	dec	eax
	mov	ebx,eax
	getxyc( eax, oypos )
	xchg	edi,eax
	scputc( ebx, oypos, 1, eax )
	pop	rbx
	ret

xbuttms:
	push	rsi
	push	rdi
	push	rbx
	push	r12
	push	r13
	push	r14
	mov	esi,' '
	mov	edi,esi
	call	xbuttxchg
	inc	ebx
	getxyc( ebx, oypos )
	mov	r12d,eax
	sub	ebx,oxlen
	mov	eax,oypos
	inc	eax
	inc	ebx
	getxyc( ebx, eax )
	mov	r13d,eax
	mov	eax,oflag
	and	eax,000Fh
	mov	r14d,eax
	.if	ZERO?
		mov	eax,oypos
		inc	eax
		scputc( ebx, eax, oxlen, ' ' )
		add	ebx,oxlen
		dec	ebx
		scputc( ebx, oypos, 1, ' ' )
	.endif
	call	msloop
	call	xbuttxchg
	mov	edx,r14d
	mov	eax,r13d
	mov	edi,r12d
	.if	!edx
		mov	ebx,oxpos
		inc	ebx
		mov	edx,oypos
		inc	edx
		scputc( ebx, edx, oxlen, eax )
		add	ebx,oxlen
		dec	ebx
		scputc( ebx, oypos, 1, edi )
	.endif
	pop	r14
	pop	r13
	pop	r12
	pop	rbx
	pop	rdi
	pop	rsi
	ret

cmdmouse:
	push	rsi
	push	rdi
	push	rbx
	push	r12
	push	r13
	push	r14

	mov	rbx,tdialog
	mov	r13,mousex()
	mov	r14,mousey()
	mov	result,_C_NORMAL

	.if	rcxyrow( [rbx].S_DOBJ.dl_rect, r13d, eax )

		mov	r12d,eax
		mov	edi,[rbx].S_DOBJ.dl_rect
		mov	al,[rbx].S_DOBJ.dl_count
		mov	esi,eax
		mov	rbx,[rbx].S_DOBJ.dl_object

		.while	esi

			mov	eax,[rbx].S_TOBJ.to_rect
			add	ax,di

			.if	rcxyrow( eax, r13d, r14d )

				mov	rdx,tdialog
				xor	r12,r12
				movzx	eax,[rdx].S_DOBJ.dl_count
				sub	eax,esi
				mov	esi,eax
				inc	eax
				call	load_object

				.if	!( eax & _O_DEACT )

					mov	rdx,tdialog
					mov	eax,esi
					mov	[rdx].S_DOBJ.dl_index,al
					mov	eax,oflag
					and	al,0Fh

					.if	al == _O_TBUTT || al == _O_PBUTT
						call	xbuttms
					.endif

					mov	eax,oflag
					.if	eax & _O_DEXIT
						mov	result,_C_ESCAPE
					.endif

					.if	eax & _O_CHILD
						mov	eax,esi
						call	ExecuteChild
					.else
						and	eax,000Fh
						.if	al == _O_TBUTT || al == _O_PBUTT || \
							al == _O_MENUS || al == _O_XHTML
							mov result,_C_RETURN
						.endif
					.endif
				.else
					and	eax,0Fh
					.if	al == _O_LLMSU
						call	TDLListMouseUP
					.elseif al == _O_LLMSD
						call	TDLListMouseDN
					.elseif al == _O_MOUSE
						.if	ecx & _O_CHILD
							mov  eax,esi
							call ExecuteChild
						.endif
					.endif
				.endif
				.break
			.endif
			add	rbx,SIZE S_TOBJ
			dec	esi
		.endw

		mov	eax,r12d
		.if	eax == 1
			dlmove( tdialog )
		.elseif eax
			call	msloop
		.endif
	.else
		mov	result,_C_ESCAPE
	.endif

	pop	r14
	pop	r13
	pop	r12
	pop	rbx
	pop	rdi
	pop	rsi
	ret

MouseDelay:
	.if	mousep()
		scroll_delay()
		scroll_delay()
		or eax,1
	.endif
	ret

TDLListMouseUP:
	mov	rdx,tdllist
	sub	eax,eax
	cmp	eax,[rdx].S_LOBJ.ll_count
	jz	TDReturnNormal
	mov	[rdx].S_LOBJ.ll_celoff,eax
	mov	eax,[rdx].S_LOBJ.ll_dlgoff
	mov	rdx,tdialog
	cmp	al,[rdx].S_DOBJ.dl_index
	mov	[rdx].S_DOBJ.dl_index,al
	je	@F
	ret
@@:
	call	case_UP
	test	eax,eax
	jz	TDReturnNormal
	call	MouseDelay
	jnz	@B
	jmp	TDReturnNormal

TDLListMouseDN:
	mov	rdx,tdllist
	sub	eax,eax
	cmp	eax,[rdx].S_LOBJ.ll_count
	jz	TDReturnNormal
	mov	eax,[rdx].S_LOBJ.ll_numcel
	dec	eax
	mov	[rdx].S_LOBJ.ll_celoff,eax
	add	eax,[rdx]
	mov	rdx,tdialog
	cmp	al,[rdx].S_DOBJ.dl_index
	mov	[rdx].S_DOBJ.dl_index,al
	jz	@F
	sub	eax,eax
	ret
@@:
	call	case_DOWN
	test	eax,eax
	jz	TDReturnNormal
	call	MouseDelay
	jnz	@B

TDReturnNormal:
	call	msloop
	mov	eax,_C_NORMAL
	ret

is_listitem:
	xor	eax,eax
	call	load_object
	test	eax,_O_LLIST
	jnz	@F
	and	eax,0Fh
	cmp	al,_O_MENUS
	je	@F
	mov	result,_C_NORMAL
	xor	eax,eax
@@:
	ret

case_HOME:
	.if	is_listitem()

		and	eax,_O_LLIST
		.if	!ZERO?

			xor	eax,eax
			mov	r10,tdllist
			mov	[r10].S_LOBJ.ll_index,eax
			mov	[r10].S_LOBJ.ll_celoff,eax

			mov	rdx,[r10].S_LOBJ.ll_proc
			mov	eax,[r10].S_LOBJ.ll_dlgoff
			push	rax
			mov	rax,tdialog
			call	rdx
			pop	rax
		.endif
		mov	rdx,tdialog
		mov	[rdx].S_DOBJ.dl_index,al
		call	nextitem
		call	previtem
	.endif
	ret

case_LEFT:
	xor	eax,eax
	call	load_object
	test	eax,_O_LLIST
	jnz	case_PGUP
	and	eax,000Fh
	cmp	al,_O_MENUS
	je	case_EXIT
	call	itemleft
	jz	case_UP
	ret

case_RIGHT:
	xor	eax,eax
	call	load_object
	test	eax,_O_LLIST
	jnz	case_PGDN
	and	eax,000Fh
	cmp	al,_O_MENUS
	je	case_EXIT
	call	itemright
	jz	case_DOWN
	ret

case_UP:
	xor	eax,eax
	call	load_object
	and	eax,_O_LLIST
	.if	!ZERO?
		xor	eax,eax
		mov	rdx,tdllist
		.if	eax == [rdx].S_LOBJ.ll_celoff
			.if	eax != [rdx].S_LOBJ.ll_index
				mov	ecx,[rdx].S_LOBJ.ll_dlgoff
				mov	rdx,tdialog
				.if	[rdx].S_DOBJ.dl_index == cl
					mov rdx,tdllist
					dec [rdx].S_LOBJ.ll_index
					jmp case_LLPROC
				.endif
				mov	[rdx].S_DOBJ.dl_index,cl
				inc	eax
			.endif
			ret
		.endif
	.endif
	jmp	previtem

case_DOWN:

	xor	eax,eax
	call	load_object
	and	eax,_O_LLIST
	jz	nextitem

	mov	rdx,tdllist
	mov	eax,[rdx].S_LOBJ.ll_dcount
	mov	ecx,[rdx].S_LOBJ.ll_celoff
	dec	eax

	.if	eax != ecx

		mov	eax,ecx
		add	eax,[rdx].S_LOBJ.ll_index
		inc	eax
		cmp	eax,[rdx].S_LOBJ.ll_count
		jb	nextitem
	.endif

	mov	eax,[rdx].S_LOBJ.ll_dlgoff
	add	eax,ecx
	mov	rdx,tdialog
	mov	ah,[rdx].S_DOBJ.dl_index
	mov	[rdx].S_DOBJ.dl_index,al
	cmp	al,ah
	jne	case_NORMAL

	mov	rdx,tdllist
	mov	eax,[rdx].S_LOBJ.ll_count
	sub	eax,[rdx].S_LOBJ.ll_index
	sub	eax,[rdx].S_LOBJ.ll_dcount
	jle	return_NULL
	inc	[rdx].S_LOBJ.ll_index

case_LLPROC:
	mov	rax,tdialog
	call	[rdx].S_LOBJ.ll_proc
	jmp	return_AX

case_EXIT:
	inc	edi
return_NULL:
	xor	eax,eax
return_AX:
	mov	result,eax
	ret
case_NORMAL:
	mov	result,_C_NORMAL
	ret

case_TAB:
	xor	eax,eax
	call	load_object
	and	eax,_O_LLIST
	jz	nextitem
	mov	rdx,tdllist
	mov	eax,[rdx].S_LOBJ.ll_dlgoff
	add	eax,[rdx].S_LOBJ.ll_dcount
	mov	rdx,tdialog
	mov	[rdx].S_DOBJ.dl_index,al
	jmp	case_NORMAL

case_ESC:
	mov	result,_C_ESCAPE
	ret

case_PGUP:
	.if	is_listitem()
		.if	eax & _O_LLIST
			mov	rdx,tdllist
			xor	eax,eax
			.if	eax == [rdx].S_LOBJ.ll_celoff
				.if	eax != [rdx].S_LOBJ.ll_index
					mov	eax,[rdx].S_LOBJ.ll_dcount
					.if	eax > [rdx].S_LOBJ.ll_index
						call	case_HOME
					.else
						sub	[rdx].S_LOBJ.ll_index,eax
						call	case_LLPROC
					.endif
				.endif
			.else
				mov	[rdx].S_LOBJ.ll_celoff,eax
				mov	eax,[rdx].S_LOBJ.ll_dlgoff
				mov	rdx,tdialog
				mov	[rdx].S_DOBJ.dl_index,al
			.endif
			mov	result,_C_NORMAL
		.else
			call	case_HOME
		.endif
	.endif
	ret

case_PGDN:
	.if	is_listitem()
		.if	eax & _O_LLIST
			mov	rdx,tdllist
			mov	eax,[rdx].S_LOBJ.ll_dcount
			dec	eax
			.if	eax != [rdx].S_LOBJ.ll_celoff
				mov	eax,[rdx].S_LOBJ.ll_numcel
				add	eax,[rdx].S_LOBJ.ll_dlgoff
				dec	eax
				mov	rdx,tdialog
				mov	[rdx].S_DOBJ.dl_index,al
				mov	result,_C_NORMAL
			.else
				add	eax,[rdx].S_LOBJ.ll_celoff
				add	eax,[rdx].S_LOBJ.ll_index
				inc	eax
				.if	eax < [rdx].S_LOBJ.ll_count
					mov	eax,[rdx].S_LOBJ.ll_dcount
					add	[rdx].S_LOBJ.ll_index,eax
					call	case_LLPROC
				.else
					call	case_END
				.endif
			.endif
		.else
			call	case_END
		.endif
	.endif
	ret

case_END:
	.if	is_listitem()
		.if	!(eax & _O_LLIST)
			mov	rdx,tdialog
			mov	al,[rdx].S_DOBJ.dl_count
			dec	al
			mov	[rdx].S_DOBJ.dl_index,al
			call	previtem
			call	nextitem
		.else
			mov	rdx,tdllist
			mov	eax,[rdx].S_LOBJ.ll_count
			.if	eax < [rdx].S_LOBJ.ll_dcount
				mov	eax,[rdx].S_LOBJ.ll_numcel
				dec	eax
				mov	[rdx].S_LOBJ.ll_celoff,eax
				add	eax,[rdx].S_LOBJ.ll_dlgoff
				mov	rdx,tdialog
				mov	[rdx].S_DOBJ.dl_index,al
				mov	result,_C_NORMAL
			.else
				sub	eax,[rdx].S_LOBJ.ll_dcount
				.if	eax != [rdx].S_LOBJ.ll_index
					mov	[rdx].S_LOBJ.ll_index,eax
					mov	eax,[rdx].S_LOBJ.ll_dcount
					dec	eax
					mov	[rdx].S_LOBJ.ll_celoff,eax
					add	eax,[rdx].S_LOBJ.ll_dlgoff
					mov	rdx,tdialog
					mov	[rdx].S_DOBJ.dl_index,al
					mov	rdx,tdllist
					call	case_LLPROC
				.else
					xor	eax,eax
					mov	result,eax
				.endif
			.endif
		.endif
	.endif
	ret

case_ENTER:
	xor	eax,eax
	call	load_object
	and	eax,_O_CHILD
	mov	eax,_C_RETURN
	jnz	@F
	mov	result,eax
	ret
@@:
	mov	rdx,tdialog
	movzx	eax,[rdx].S_DOBJ.dl_index
	jmp	ExecuteChild

OGOTOXY:
	xor	eax,eax
	call	save_cursor
	call	CursorOn
	inc	oxpos
	_gotoxy( oxpos, oypos )
	ret

TDXORRADIO:
	push	rcx
	push	rdx
	test	BYTE PTR [rdx].S_TOBJ.to_flag,_O_RADIO
	mov	eax,' '
	jz	@F
	mov	al,ASCII_RADIO
@@:
	mov	cx,[rdx+4]
	mov	rdx,tdialog
	add	cx,[rdx+4]
	mov	dl,ch
	inc	ecx
	scputc( ecx, edx, 1, eax )
	pop	rdx
	pop	rcx
	ret

xorradioflag PROC
	xor	eax,eax
	call	load_object
	and	eax,_O_RADIO
	jnz	break
	mov	rdx,tdialog
	sub	ecx,ecx
	add	cl,[rdx].S_DOBJ.dl_count
	jz	toend
	mov	rdx,[rdx].S_DOBJ.dl_object
@@:
	test	BYTE PTR [rdx].S_TOBJ.to_flag,_O_RADIO
	jnz	@F
	add	rdx,sizeof(S_TOBJ)
	dec	ecx
	jnz	@B
	jmp	toend
@@:
	and	BYTE PTR [rdx].S_TOBJ.to_flag,not _O_RADIO
	call	TDXORRADIO
	xor	eax,eax
	call	load_object
	or	BYTE PTR [rdx].S_TOBJ.to_flag,_O_RADIO
	call	TDXORRADIO
break:
	call	msloop
	mov	eax,_C_NORMAL
toend:
	ret
xorradioflag ENDP

TDXORSWITCH:
	xor	eax,eax
	call	load_object
	xor	eax,_O_FLAGB
	mov	[rdx],ax
	test	eax,_O_FLAGB
	mov	eax,' '
	jz	@F
	mov	eax,'x'
@@:
	mov	ecx,orect
	mov	dl,ch
	inc	ecx
	scputc( ecx, edx, 1, eax )
	call	msloop
	xor	eax,eax
	ret

TDTestXYRow:
	call	mousey
	mov	r8d,eax
	call	mousex
	rcxyrow( orect, eax, r8d )
	mov	eax,MOUSECMD
	ret

TDSelectObject:
	sub	rsp,20h
	rcread( orect, addr xlbuf )
	mov	eax,oflag
	and	eax,0000000Fh
	.if	eax == _O_MENUS
		mov al,at_background[B_InvMenus]
	.else
		mov al,at_background[B_Inverse]
	.endif
	wcputbg( addr xlbuf, oxlen, eax )
	rcxchg( orect, addr xlbuf )
	add	rsp,20h
	ret

TDDeselectObject:
	push	rax
	sub	rsp,20h
	rcwrite( orect, addr xlbuf )
	add	rsp,20h
	pop	rax
	ret

ifndef SKIP_ALTMOVE

case_ALTUP:
	mov	rax,rcmoveup
	jmp	case_ALTMOVE

case_ALTDN:
	mov	rax,rcmovedn
	jmp	case_ALTMOVE

case_ALTLEFT:
	mov	rax,rcmoveleft
	jmp	case_ALTMOVE

case_ALTRIGHT:
	mov	rax,rcmoveright

case_ALTMOVE:
	push	rsi
	push	rdi
	push	rbx
	sub	rsp,20h

	mov	rsi,rax
	mov	rdi,tdialog
	movzx	ebx,[rdi].S_DOBJ.dl_flag

	.if	ebx & _D_DMOVE

		.if	ebx & _D_SHADE

			rcclrshade( [rdi].S_DOBJ.dl_rect, [rdi].S_DOBJ.dl_wp )
		.endif

		mov	ecx,[rdi].S_DOBJ.dl_rect
		mov	rdx,[rdi].S_DOBJ.dl_wp
		movzx	r8d,[rdi].S_DOBJ.dl_flag
		call	rsi
		mov	WORD PTR [rdi].S_DOBJ.dl_rect,ax

		.if	ebx & _D_SHADE

			rcsetshade( [rdi].S_DOBJ.dl_rect, [rdi].S_DOBJ.dl_wp )
		.endif
	.endif
	add	rsp,20h
	pop	rbx
	pop	rdi
	pop	rsi
	ret

endif

;-------------------------------------------------------------------------------

	OPTION	PROLOGUE:PROLOGUEDEF,
		EPILOGUE:EPILOGUEDEF,
		PROC:PUBLIC,
		CSTACK:ON

;-------------------------------------------------------------------------------

dlpbuttevent PROC USES rsi rdi rbx
	xor	eax,eax
	call	save_cursor
	call	CursorOn
	mov	eax,oxpos
	inc	eax
	_gotoxy( eax, oypos )
	mov	al,BYTE PTR oflag
	and	al,0Fh
	.if	al != _O_TBUTT
		call	CursorOff
	.endif
	movzx	esi,ASCII_RIGHT
	movzx	edi,ASCII_LEFT
	call	xbuttxchg
	call	tgetevent
	mov	ebx,eax
	call	xbuttxchg
	SetCursor( addr ocurs )
	mov	eax,ebx
	ret
dlpbuttevent ENDP

dlradioevent PROC
	call	OGOTOXY
	.repeat
		call	tgetevent
		.if	eax == MOUSECMD
			call	omousecmd
			jz	toend
		.elseif eax != KEY_SPACE
			jmp	toend
		.endif
		call	xorradioflag
	.until oflag & _O_EVENT
	mov	eax,KEY_SPACE
toend:
	SetCursor( addr ocurs )
	ret
dlradioevent ENDP

dlcheckevent PROC
	call	OGOTOXY
	.repeat
		call	tgetevent
		.if	eax == MOUSECMD
			call	omousecmd
			jz	toend
			call	TDXORSWITCH
		.elseif eax == KEY_SPACE
			call	TDXORSWITCH
		.else
			jmp	toend
		.endif
	.until	oflag & _O_EVENT
	mov	eax,KEY_SPACE
toend:
	SetCursor( addr ocurs )
	ret
dlcheckevent ENDP

dlxcellevent PROC USES rsi
	xor	eax,eax
	call	load_object
	.if	!ZERO?
		call	CursorOff
	.endif
	.if	oflag & _O_LLIST
		mov	rdx,tdialog
		movzx	eax,[rdx].S_DOBJ.dl_index
		mov	rdx,tdllist
		.if	eax >= [rdx].S_LOBJ.ll_dlgoff
			sub	eax,[rdx].S_LOBJ.ll_dlgoff
			.if	eax < [rdx].S_LOBJ.ll_numcel
				mov [rdx].S_LOBJ.ll_celoff,eax
			.endif
		.endif
	.endif
	call	TDSelectObject
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
		delay ( 16 )
		call	mousep
		.break .if !ZERO?
		dec	esi
	.endw
	call	mousep
	jz	lupe
	call	TDTestXYRow
	jz	lupe
	mov	eax,KEY_ENTER
done:
	test	eax,eax
	jz	lupe
toend:
	call	TDDeselectObject
	ret
mouseup:
	mov	eax,KEY_UP
	test	oflag,_O_LLIST
	jz	toend
	PushEvent( eax )
	jmp	@F
mousedn:
	mov	eax,KEY_DOWN
	test	oflag,_O_LLIST
	jz	toend
	PushEvent( eax )
@@:
	PushEvent( eax )
	jmp	toend
dlxcellevent ENDP

dlteditevent PROC USES rsi
	mov	rdx,tdialog
	mov	si,[rdx+4]
	sub	eax,eax
	call	load_object
	mov	eax,[rdx].S_TOBJ.to_rect
	add	ax,si
	movzx	r8d,[rdx].S_TOBJ.to_count
	shl	r8d,4
	mov	rcx,[rdx].S_TOBJ.to_data
	dledit( rcx, eax, r8d, oflag )
	ret
dlteditevent ENDP

dlmenusevent PROC USES rbx
	call	CursorOff
	xor	eax,eax
	call	save_cursor
	mov	rbx,rdx
	.if	[rdx].S_TOBJ.to_data
		mov	al,' '
		mov	ah,at_background[B_Menus]
		or	ah,at_foreground[F_KeyBar]
		scputw( 20, _scrrow, 60, eax )
		scputs( 20, _scrrow, 0, 60, [rbx].S_TOBJ.to_data )
	.endif
	call	TDSelectObject
	call	tgetevent
	.if	eax == KEY_MOUSEUP
		mov eax,KEY_UP
	.elseif eax == KEY_MOUSEDN
		mov eax,KEY_DOWN
	.endif
	call	TDDeselectObject
	SetCursor( addr ocurs )
	ret
dlmenusevent ENDP

dlevent PROC USES rsi rdi rbx dialog:PTR S_DOBJ

	local	prevdlg:QWORD	; init tdialog
	local	cursor:S_CURSOR ; init cursor

	mov	rax,tdialog
	mov	prevdlg,rax
	mov	rax,rcx;dialog
	mov	tdialog,rax
	mov	rbx,rax
	movzx	esi,[rbx].S_DOBJ.dl_flag

	.if	!( esi & _D_ONSCR )
		dlshow( rbx )
		jz	toend
	.endif

	GetCursor( addr cursor )
	call	CursorOff
	movzx	rax,[rbx].S_DOBJ.dl_count
	.if	eax
		xor	eax,eax
		.if	load_object() & _O_DEACT
			call	nextitem
		.endif
		mov	eax,1
	.endif
	.if	!eax
		.while	1

			test_event( 9, tgetevent() )
			mov	eax,result
			.break .if eax == _C_ESCAPE
			.break .if eax == _C_RETURN
		.endw
	.else

		call	msloop
		xor	edi,edi

		.repeat
			xor	eax,eax
			mov	result,eax

			.if	load_object() & _O_EVENT
				call	[rdx].S_TOBJ.to_proc
			.else
				movzx	rax,BYTE PTR [rdx]
				and	al,0Fh
				.if	al > 6
					.if	al == _O_TBUTT
						dlpbuttevent()
					.else
						mov eax,KEY_ESC
					.endif
				.else
					lea	r8,eventproc
					mov	rax,[r8+rax*8]
					call	rax
				.endif
			.endif

			mov	dlexit,eax
			mov	event,eax
			test_event( key_count, eax )
			mov	eax,result
			.if	eax == _C_ESCAPE
				mov	event,0
				.break
			.elseif eax == _C_RETURN
				xor	eax,eax
				.if	load_object() & _O_DEXIT
					mov	event,0
				.else
					mov	rdx,tdialog
					movzx	eax,[rdx].S_DOBJ.dl_index
					inc	eax
					mov	event,eax
				.endif
				.break
			.endif
		.until	edi
	.endif
	SetCursor( addr cursor )
	mov	eax,event
toend:
	mov	edx,eax
	mov	rax,prevdlg
	mov	tdialog,rax
	mov	eax,edx
	mov	ecx,dlexit
	test	eax,eax
	ret
dlevent ENDP

Install:
	lea	rax,getevent
	mov	tgetevent,rax
	ret

pragma_init	Install,32

	END
