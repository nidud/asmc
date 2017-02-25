include tinfo.inc
include ctype.inc
include ltype.inc
include stdlib.inc
include string.inc

	.code

	ASSUME	edx: PTR S_TINFO

tiselected PROC ti:PTINFO
	mov	edx,ti
	mov	eax,[edx].ti_clel	; CX line count
	sub	eax,[edx].ti_clsl
	mov	ecx,eax
	jnz	@F
	mov	eax,[edx].ti_cleo	; AX byte count
	sub	eax,[edx].ti_clso
@@:
	ret
tiselected ENDP
	;
	; set clipboard to current position
	;
ticlipset PROC ti:PTINFO
	mov	edx,ti
	mov	eax,[edx].ti_xoff
	add	eax,[edx].ti_boff
	mov	[edx].ti_clso,eax
	mov	[edx].ti_cleo,eax
	mov	eax,[edx].ti_loff
	add	eax,[edx].ti_yoff
	mov	[edx].ti_clsl,eax
	mov	[edx].ti_clel,eax
	ret
ticlipset ENDP

ticliptostart PROC USES edi ti:PTINFO
	mov	edx,ti

	mov	edi,[edx].ti_loff
	mov	eax,[edx].ti_yoff
	mov	ecx,edi
	add	ecx,eax
	sub	ecx,[edx].ti_clsl
	.ifnz
		.if	eax >= ecx
			sub	eax,ecx ; move cursor up
		.else
			sub	ecx,eax ; scroll up..
			xor	eax,eax ; screen line to 0
			sub	edi,ecx ; new line offset
		.endif
	.endif
	mov	[edx].ti_loff,edi
	mov	[edx].ti_yoff,eax
	tialignx( edx, [edx].ti_clso )
	ret
ticliptostart ENDP

tigeto	PROC USES esi edi ti:PTINFO, line:UINT, offs:UINT

	xor	edi,edi
	.if	tigetline( ti, line )	; expanded line

		mov	esi,eax
		mov	edi,[edx].ti_flp	; line from file buffer
		mov	ecx,offs

		.if	[edx].ti_flag & _T_USETABS

			.while	ecx

				mov	al,[esi]
				add	esi,1
				.break .if !al

				.if	al != TITABCHAR ; skip expanded tabs
					add	edi,1
				.endif
				sub	ecx,1
			.endw
		.else
			add	edi,ecx		; if no tabs then equal
		.endif
	.endif
	mov	eax,edi
	ret
tigeto	ENDP

ticlipdel PROC USES ebx ti:PTINFO

	mov	edx,ti

	.if	tiselected( edx )

		ticliptostart( edx )

		.if	tigeto( edx, [edx].ti_clsl, [edx].ti_clso )
			mov	ebx,eax

			.if	tigeto( edx, [edx].ti_clel, [edx].ti_cleo )
				.if	eax <= ebx
					xor	eax,eax
				.else
					strcpy( ebx, eax )
					or	[edx].ti_flag,_T_MODIFIED
					mov	eax,[edx].ti_clel
					sub	eax,[edx].ti_clsl
					.ifnz
						.if	eax <= [edx].ti_lcnt
							sub [edx].ti_lcnt,eax
						.else
							mov [edx].ti_lcnt,0
						.endif
					.endif
					ticlipset( edx )
					xor	eax,eax
					inc	eax
				.endif
			.endif
		.endif
	.endif
	ret
ticlipdel ENDP

	ASSUME	esi: PTR S_TINFO

ticlippaste PROC USES esi edi ebx ti:PTINFO

	mov	esi,ti
	mov	eax,[esi].ti_flag

	.if	eax & _T_OVERWRITE
		ticlipdel( esi )
	.else
		ticlipset( esi )
	.endif

	.if	ClipboardPaste()

		push	[esi].ti_flag
		push	[esi].ti_yoff
		push	[esi].ti_loff
		push	[esi].ti_xoff
		push	[esi].ti_boff

		and	[esi].ti_flag,not (_T_USEINDENT or _T_OPTIMALFILL)
		mov	edx,esi
		mov	esi,clipbsize
		mov	edi,eax

		.while	1

			@@:

			movzx	eax,byte ptr [edi]
			.break	.if !eax

			inc	edi
			push	eax
			tiputc( ti, eax )
			cmp	eax,_TI_CONTINUE
			pop	eax
			.breaknz
			dec	esi
			.breakz
			test	BYTE PTR _ctype[eax*2+2],_SPACE
			jnz	@B

			.if	esi >= 128

				@@:

				mov	eax,[edx].ti_yoff
				add	eax,[edx].ti_loff
				mov	ecx,[edx].ti_xoff
				add	ecx,[edx].ti_boff
				.break	.if !tigeto( edx, eax, ecx )

				mov	ebx,eax
				strlen( eax )
				add	eax,esi
				add	eax,ebx
				mov	ecx,[edx].ti_bp
				add	ecx,[edx].ti_blen
				sub	ecx,128
				.if	eax < ecx

					strins( ebx, edi )
					mov	[edx].ti_lcnt,1
					mov	eax,[edx].ti_bp

					.while	strchr( eax, 10 )
						inc	[edx].ti_lcnt
						inc	eax
					.endw
					.break
				.endif
				.break	.if !tirealloc( edx )
				jmp	@B
			.endif

			.while	esi

				movzx	eax,BYTE PTR [edi]
				.break	.if !eax

				add	edi,1
				tiputc( edx, eax )
				.break	.if eax != _TI_CONTINUE
				sub	esi,1
			.endw
			.break
		.endw

		ClipboardFree()

		mov	esi,ti
		pop	eax
		pop	ecx
		mov	[esi].ti_boff,eax
		mov	[esi].ti_xoff,ecx
		pop	ecx
		pop	eax
		mov	[esi].ti_yoff,eax
		mov	[esi].ti_loff,ecx
		pop	eax
		or	eax,_T_MODIFIED
		mov	[esi].ti_flag,eax
	.endif
	ticlipset( esi )
	xor	eax,eax
	ret
ticlippaste ENDP
	;
	; copy start to end pointer of selected text
	;
ticopyselection PROC USES esi edi ti:PTINFO

	mov	esi,ti

	.if	tigeto( esi, [esi].ti_clsl, [esi].ti_clso )
		mov	edi,eax
		.if	tigeto( esi, [esi].ti_clel, [esi].ti_cleo )
			sub	eax,edi		; = byte size of selected text
			ClipboardCopy( edi, eax )
			mov	eax,1
		.endif
	.endif
	ret
ticopyselection ENDP

ticlipcut PROC USES esi ti:PTINFO, delete:UINT
	mov	esi,ti
	.if	tiselected( esi )
		ticopyselection( esi )
		jz	toend
		dec	eax
		jnz	toend
	.endif
	.if	delete
		ticlipdel( esi )
	.endif
	ticlipset( esi )
toend:
	xor	eax,eax
	ret
ticlipcut ENDP

tiselectall PROC ti:PTINFO
	xor	eax,eax
	mov	edx,ti
	mov	[edx].ti_clsl,eax
	mov	[edx].ti_clso,eax
	mov	[edx].ti_clel,eax
	mov	eax,[edx].ti_bcol
	mov	[edx].ti_cleo,eax
	.if	[edx].ti_lcnt != eax
		mov	eax,[edx].ti_lcnt
		dec	eax
		mov	[edx].ti_clel,eax
		tiputs( edx )
	.endif
	xor	eax,eax
	ret
tiselectall ENDP

tiincy	PROC USES eax ecx ebx ti:PTINFO
	mov	edx,ti
	mov	ebx,[edx].ti_rows
	mov	eax,[edx].ti_loff
	mov	ecx,eax
	add	eax,[edx].ti_yoff
	inc	eax
	.if	eax >= [edx].ti_lcnt
		xor	eax,eax
	.else
		mov	eax,[edx].ti_yoff
		inc	eax
		.if	eax >= ebx
			mov	eax,ebx
			dec	eax
			inc	ecx
		.endif
		mov	[edx].ti_yoff,eax
		mov	[edx].ti_loff,ecx
	.endif
	ret
tiincy	ENDP

tialignx PROC USES ecx ti:PTINFO, x:UINT
	;
	; align xoff and boff to EAX
	;
	mov	eax,x
	mov	edx,ti

	mov	ecx,[edx].ti_xoff
	add	ecx,[edx].ti_boff
	cmp	ecx,eax			; left or right ?
	jb	incx
	je	toend
@@:
	tidecx( edx )			; go left
	jz	toend
	dec	ecx
	cmp	eax,ecx
	jne	@B
	jmp	done
incx:
	tiincx( edx )			; go right
	jz	toend
	inc	ecx
	cmp	eax,ecx
	jne	incx
done:
	inc	ecx
toend:
	ret
tialignx ENDP

tialigny PROC USES ecx ti:PTINFO, y:UINT
	;
	; align yoff and loff to EAX
	;
	mov	eax,y
	mov	edx,ti

	mov	ecx,[edx].ti_yoff
	add	ecx,[edx].ti_loff

	.while	ecx > eax
		.if	[edx].ti_yoff
			dec [edx].ti_yoff
		.else
			dec [edx].ti_loff
		.endif
		dec ecx
	.endw

	.while	ecx < eax
		tiincy( edx )
		.break .if ZERO?
		inc ecx
	.endw
	ret

tialigny ENDP

tihome	PROC ti:PTINFO
	mov	edx,ti
	xor	eax,eax
	mov	[edx].ti_boff,eax
	mov	[edx].ti_xoff,eax
	ret
tihome	ENDP

titoend PROC USES esi edi ti:PTINFO
	mov	edx,ti
	ticurlp(edx )
	.ifnz
		tistripend( eax )
		.ifnz
			mov	[edx].ti_bcnt,ecx
			mov	eax,ecx
			sub	eax,[edx].ti_boff
			.if	eax < [edx].ti_cols

				mov	[edx].ti_xoff,eax
			.else
				mov	eax,[edx].ti_cols
				dec	eax
				.if	ecx <= eax

					mov	eax,ecx
				.endif
				mov	[edx].ti_xoff,eax
				sub	ecx,eax
				mov	[edx].ti_boff,ecx
			.endif
		.else
			tihome( edx )
		.endif
		xor	eax,eax
	.else
		mov	eax,_TI_CMFAILED
	.endif
	ret
titoend ENDP

tileft	PROC ti:PTINFO
	tidecx( ti )
	mov	eax,_TI_CMFAILED
	jz	@F
	xor	eax,eax
@@:
	ret
tileft	ENDP

tiup	PROC ti:PTINFO
	mov	edx,ti
	xor	eax,eax
	.if	eax != [edx].ti_yoff
		dec [edx].ti_yoff
	.elseif eax != [edx].ti_loff
		dec [edx].ti_loff
	.else
		mov eax,_TI_CMFAILED
	.endif
	ret
tiup	ENDP

tiputc	PROC USES esi edi ebx ti:PTINFO, char:UINT

	local	ts:S_TIOST

	mov	edx,ti
	lea	esi,ts
	movzx	eax,BYTE PTR char

	.if	BYTE PTR _ctype[eax*2+2] & _CONTROL

		.if	eax != 9 && eax != 10
			.if	eax == 13
				xor	eax,eax ; skip
			.else
				mov	eax,_TI_RETEVENT
			.endif
			jmp	toend
		.endif
	.endif

	__st_open( edx, esi, eax )
	jz	error

	mov	ecx,ts.ts_line_ptr
	sub	ecx,[edx].ti_lp

	.if	!ZERO?
		__st_copy( edx, esi )
		jc	error
	.endif


	.if	ts.ts_char == 10

		mov	ecx,ts.ts_index
		mov	eax,ts.ts_buffer

		.while	ecx
			sub	ecx,1
			.break .if BYTE PTR [eax+ecx] > ' '
			.break .if BYTE PTR [eax+ecx] == 10
			mov	BYTE PTR [eax+ecx],0
			mov	ts.ts_index,ecx
		.endw

		.if	[edx].ti_flag & _T_USECRLF

			__st_putc( esi, 13 )
			jc	error
		.endif

		__st_putc( esi, 10 )
		jc	error

		inc	[edx].ti_lcnt		; inc line count
		tihome( edx )			; to start of line
		tiincy( edx )			; one down

		.if	[edx].ti_flag & _T_USEINDENT

			mov	ecx,[edx].ti_lp			; get indent size
			mov	eax,' '
			.while	[ecx] != ah && \
				[ecx] <= al && \
				ecx < ts.ts_line_ptr
				add	ecx,1
			.endw
			sub	ecx,[edx].ti_lp			; add indent
			.ifnz
				.repeat

					tiincx( edx )
					.breakz

					__st_putc( esi, eax )
					jc	error
				.untilcxz
			.endif
		.endif
	.else

		tiincx( edx )
		jz	error

		mov	al,ts.ts_char
		.if	al == 9 && !( [edx].ti_flag & _T_USETABS )
			mov	al,' '
		.endif

		__st_putc( esi, eax )
		jc	error

		.if	ts.ts_char == 9

			mov	eax,[edx].ti_xoff	; Align xoff and boff to next TAB
			add	eax,[edx].ti_boff
			mov	ecx,eax

			mov	ebx,[edx].ti_tabz
			dec	bl
			and	bl,TIMAXTABSIZE-1

			.if	al & bl

				not	bl
				and	al,bl
				add	eax,[edx].ti_tabz

				.if	ecx > eax		; Align xoff and boff to AX

					.while	1

						tidecx( edx )
						.breakz

						sub	ecx,1
						.break	.if eax == ecx
					.endw

				.elseif CARRY?

					.while	1

						.if !( [edx].ti_flag & _T_USETABS )

							push	eax
							__st_putc( esi, ' ' )
							pop	eax
							jc	error
						.endif

						tiincx( edx )
						.breakz

						add	ecx,1
						.break	.if eax == ecx
					.endw
				.endif
			.endif
		.endif
	.endif

	__st_tail( edx, esi, ts.ts_line_ptr )
toend:
	ret
error:
	mov	eax,_TI_CMFAILED
	jmp	toend
tiputc	ENDP

tibacksp PROC USES esi edi ebx ti:PTINFO

	local	ts:S_TIOST

	mov	edx,ti
	lea	esi,ts

	mov	eax,[edx].ti_xoff
	add	eax,[edx].ti_boff

	.ifz
		mov	eax,[edx].ti_loff
		add	eax,[edx].ti_yoff
		.ifz
			mov	eax,_TI_CMFAILED
			jmp	toend
		.endif
		tiup	( edx )
		titoend ( edx )
		tidelete( edx )
		jmp	toend
	.endif

	__st_open( edx, esi, 0 )
	jz	error

	mov	eax,ts.ts_line_ptr
	xor	ebx,ebx
	.if	WORD PTR [eax-1] != ' '
		inc ebx
	.endif

	test	[edx].ti_flag,_T_USEINDENT
	jz	done

	mov	eax,[edx].ti_lp
	cmp	eax,ts.ts_line_ptr
	je	done

	.while	eax != ts.ts_line_ptr
		cmp	BYTE PTR [eax],' '
		ja	done
		add	eax,1
	.endw
	sub	eax,[edx].ti_lp
	;
	; get indent from line(s) above
	;
	mov	esi,eax
	mov	edi,[edx].ti_loff
	add	edi,[edx].ti_yoff
	xor	eax,eax

	.while	edi

		sub	edi,1

		tigetline( edx, edi )
		.breakz

		.if	BYTE PTR [eax]	; get indent

			mov	ecx,eax
			xor	eax,eax

			@@:

			.continue .if BYTE PTR [ecx+eax] == 0

			.if	BYTE PTR [ecx+eax] <= ' '

				add	eax,1
				cmp	eax,[edx].ti_bcol
				jb	@B

				xor	eax,eax
				.break
			.endif

			.break .if eax < esi
		.endif
	.endw

	mov	ecx,ts.ts_line_ptr
	sub	ecx,[edx].ti_lp
	cmp	ecx,eax
	jbe	done

	sub	ecx,eax
	mov	edi,ecx

	mov	ebx,[edx].ti_loff
	add	ebx,[edx].ti_yoff
	mov	ecx,[edx].ti_xoff
	add	ecx,[edx].ti_boff
	push	ecx
	push	edi
	tigeto( edx, ebx, ecx )
	mov	esi,eax

	.repeat
		.break .if tileft( edx )
		sub	edi,1
	.until	ZERO?
	pop	eax
	sub	eax,edi
	pop	ecx
	sub	ecx,eax
	tigeto( edx, ebx, ecx )
	.if	esi && eax && eax < esi
		strcpy( eax, esi )
	.endif
	xor	eax,eax
toend:
	ret
error:
	mov	eax,_TI_CMFAILED
	jmp	toend
done:
	.if !tileft( edx ) && ebx

		tidelete( edx )
	.endif
	jmp	toend

tibacksp ENDP

tidelete PROC USES esi edi ebx ti:PTINFO

	local	ts:S_TIOST

	mov	edx,ti
	lea	esi,ts

	__st_open( edx, esi, 0 )
	jz	failed

	mov	eax,ts.ts_file_ptr
	cmp	eax,ts.ts_file_end
	je	zero_lenght

	mov	ecx,ts.ts_line_ptr
	xor	eax,eax
	xor	ebx,ebx
@@:
	mov	bl,[ecx]
	add	ecx,1
	test	ebx,ebx
	jz	@F
	or	al,BYTE PTR _ctype[ebx*2+2]
	jmp	@B
@@:
	sub	ecx,ts.ts_line_ptr
	dec	ecx
	jz	end_of_line

	.if !( eax & NOT ( _SPACE or _CONTROL or _BLANK ) )
		;
		; the line is blank..
		;
		mov	eax,ts.ts_line_ptr
		mov	BYTE PTR [eax+1],0
		sub	eax,[edx].ti_lp
		jz	start
	.endif

	test	[edx].ti_flag,_T_USETABS
	jz	no_tabs

	mov	ecx,ts.ts_line_ptr
	sub	ecx,[edx].ti_lp
	jz	start

	__st_copy( edx, esi )
	jc	failed

start:
	mov	ecx,ts.ts_line_ptr
	inc	ecx

	mov	eax,[edx].ti_flag
	push	eax
	and	eax,not _T_OPTIMALFILL
	mov	[edx].ti_flag,eax

	__st_tail( edx, esi, ecx )

	pop	ecx
	and	ecx,_T_OPTIMALFILL
	or	[edx].ti_flag,ecx
	jmp	toend

no_tabs:
	mov	eax,ts.ts_file_ptr
	add	eax,[edx].ti_xpos
	add	eax,[edx].ti_xoff
	mov	ecx,eax
	inc	ecx
	cmp	ecx,ts.ts_file_end
	ja	failed
	jmp	copy

end_of_line:
	mov	ecx,ts.ts_line_ptr
	sub	ecx,[edx].ti_lp
	jz	failed

	__st_copy2( edx, esi )
	jc	failed

	mov	eax,ts.ts_file_end
	.if	BYTE PTR [eax] == 0Dh
		inc	eax
	.endif
	.if	BYTE PTR [eax] == 0Ah
		inc	eax
		dec	[edx].ti_lcnt
	.endif

	mov	ts.ts_file_end,eax
	__st_flush( edx, esi )
	jmp	toend

zero_lenght:
	.if	BYTE PTR [eax] == 0Dh
		lea	ecx,[eax+2]
		dec	[edx].ti_lcnt
	.elseif BYTE PTR [eax] == 0Ah
		lea	ecx,[eax+1]
		dec	[edx].ti_lcnt
	.else
		jmp	failed
	.endif
copy:
	strcpy( eax, ecx )
	or	[edx].ti_flag,_T_MODIFIED
	xor	eax,eax

toend:
	ret
failed:
	mov	eax,_TI_CMFAILED
	jmp	toend
tidelete ENDP

tievent PROC USES esi edi ebx ti:PTINFO, event:UINT


	.if !tiselected( ti )

		ticlipset( edx )
	.endif

	mov	eax,keyshift
	mov	ecx,[eax]
	mov	eax,event

	.switch

	  .case eax == MOUSECMD

		;--------------------------------------------------------------
		; Mouse Event
		;--------------------------------------------------------------

		call	mousep
		mov	ebx,keybmouse_y
		mov	ecx,keybmouse_x

		.if	eax == KEY_MSRIGTH

			.data

			externdef IDD_TEQuickMenu:DWORD

			QuickMenuKeys	dd KEY_CTRLDEL
					dd KEY_CTRLINS ; KEY_CTRLC
					dd KEY_CTRLV
					dd KEY_CTRLA
					dd KEY_ALT0
					dd KEY_F5
					dd KEY_ESC
					dd KEY_CTRLX
					dd KEY_F7

			qkeycount equ (($ - offset QuickMenuKeys) / 4)

			.code

			mov	ebx,IDD_TEQuickMenu
			mov	eax,keybmouse_x
			mov	[ebx+6],al
			mov	eax,keybmouse_y
			mov	[ebx+7],al

			.if	rsmodal( ebx )

				PushEvent( QuickMenuKeys[eax*4-4] )
				msloop()
			.endif
			jmp	continue

		.elseif eax == KEY_MSLEFT

			.if	msvalidate()

				sub	ebx,[edx].ti_ypos
				sub	ecx,[edx].ti_xpos
				mov	[edx].ti_yoff,ebx
				mov	[edx].ti_xoff,ecx

				ticlipset( edx )
				mov	esi,[edx].ti_clsl
				mov	edi,[edx].ti_clso

				.while	1

					tiputs( edx )
					push	edx
					Sleep ( CON_SLEEP_TIME )
					pop	edx

					call	mousep
					mov	ebx,keybmouse_y
					mov	ecx,keybmouse_x
					cmp	eax,KEY_MSLEFT
					jne	return_event

					msvalidate()
					.contz

					sub	ebx,[edx].ti_ypos
					sub	ecx,[edx].ti_xpos
					mov	[edx].ti_yoff,ebx
					mov	[edx].ti_xoff,ecx
					add	ecx,[edx].ti_boff
					add	ebx,[edx].ti_loff

					.if	edi > ecx
						mov [edx].ti_clso,ecx
					.else
						mov [edx].ti_cleo,ecx
						.ifz
							mov [edx].ti_clso,ecx
						.endif
					.endif
					.if	esi > ebx
						mov	[edx].ti_clsl,ebx
					.else
						mov	[edx].ti_clel,ebx
						.ifz
							mov [edx].ti_clsl,ebx
						.endif
					.endif

					mov	eax,[edx].ti_yoff
					.if	!eax
						tiscrollup()
					.else
						inc	eax
						.if	eax == [edx].ti_rows
							tiscrolldn()
						.endif
					.endif
				.endw
			.endif
		.endif
		jmp	return_event

	  .case eax == KEY_CTRLINS
	  .case eax == KEY_CTRLC

		ticlipcut( edx, 0 )
		.endc

	  .case eax == KEY_CTRLV
		ticlippaste( edx )
		.endc

	  .case eax == KEY_CTRLDEL

		ticlipcut( edx, 1 )
		.endc

	  .case ecx & SHIFT_KEYSPRESSED

		.switch eax

		  .case KEY_INS
			ticlippaste( edx )
			jmp	continue

		  .case KEY_DEL
			ticlipcut( edx, 1 )
			jmp	continue

		  .case KEY_HOME
		  .case KEY_LEFT
		  .case KEY_RIGHT
		  .case KEY_END
		  .case KEY_UP
		  .case KEY_DOWN
		  .case KEY_PGUP
		  .case KEY_PGDN

			push	eax
			call	handle_event
			pop	ecx

			cmp	eax,_TI_CMFAILED
			je	continue
			cmp	eax,_TI_RETEVENT
			je	continue

			mov	edx,ti
			mov	ebx,[edx].ti_loff
			add	ebx,[edx].ti_yoff
			mov	eax,[edx].ti_boff
			add	eax,[edx].ti_xoff
			cmp	ebx,[edx].ti_clsl
			jb	case_tostart

			cmp	eax,[edx].ti_clso
			jb	case_tostart
			cmp	ecx,KEY_RIGHT
			jne	@F
			lea	ecx,[eax-1]
			cmp	ecx,[edx].ti_clso
			jne	@F
			cmp	ecx,[edx].ti_cleo
			jne	case_tostart
		     @@:
			mov	[edx].ti_cleo,eax
			mov	[edx].ti_clel,ebx
			jmp	continue

		.endsw
		.endc

	  .case eax == KEY_DEL

		ticlipdel( edx )
		mov	eax,KEY_DEL
		jz	clipset
		jmp	continue

	.endsw

	.switch
	  .case eax == KEY_ESC
	  .case eax == MOUSECMD
	  .case eax == KEY_BKSP
	  .case eax == KEY_ENTER
	  .case eax == KEY_KPENTER
	  .case !al
		jmp	clipset
	.endsw

	push	eax
	ticlipdel( edx )
	pop	eax

clipset:
	push	eax
	ticlipset( edx )
	pop	eax

	call	handle_event
toend:
	ret

case_tostart:
	mov	[edx].ti_clso,eax
	mov	[edx].ti_clsl,ebx

continue:
	xor	eax,eax
	jmp	toend

return_event:
	mov	eax,_TI_RETEVENT
	jmp	toend

handle_event:

	.switch eax

	  .case KEY_ESC
		mov	eax,_TI_RETEVENT
	  .case _TI_CONTINUE
		.endc

	  .case KEY_CTRLRIGHT
		;--------------------------------------------------------------
		; Move to Next/Prev word (Ctrl-Right, Ctrl-Left)
		;--------------------------------------------------------------

		.if	ticurcp( edx )

			mov	ecx,eax
			mov	edx,eax

			movzx	eax,BYTE PTR [ecx]
			.while	__ltype[eax+1] & _LABEL or _DIGIT
				add	ecx,1
				mov	al,[ecx]
			.endw
			.while	eax && !( __ltype[eax+1] & _LABEL or _DIGIT )
				add	ecx,1
				mov	al,[ecx]
			.endw

			.if	eax

				sub	ecx,edx
				mov	edx,ti
				mov	eax,[edx].ti_boff
				add	eax,[edx].ti_xoff
				add	eax,ecx

				.if	eax <= [edx].ti_bcnt

					mov	eax,ecx
					add	eax,[edx].ti_xoff
					mov	ecx,[edx].ti_cols

					.if	eax >= ecx

						dec	ecx
						sub	eax,ecx
						add	[edx].ti_boff,eax
						mov	[edx].ti_xoff,ecx
						xor	eax,eax
						.endc
					.endif
				.endif

				mov	[edx].ti_xoff,eax
				xor	eax,eax
				.endc
			.endif

			mov	edx,ti
			mov	eax,KEY_DOWN
			call	handle_event
			mov	eax,KEY_HOME
			jmp	handle_event
		.endif
		xor	eax,eax
		.endc

	  .case KEY_CTRLLEFT
		.repeat
			.if	ticurlp( edx )

				mov	ecx,eax
				mov	eax,[edx].ti_boff
				add	eax,[edx].ti_xoff
				.ifz
					.if	!tiup( edx )

						titoend( edx )
						.continue
					.endif
					.endc
				.endif
				lea	edx,[ecx+eax]
				.if	eax

					sub	edx,1
				.endif
				movzx	eax,BYTE PTR [edx]
				.while	ecx < edx && !( __ltype[eax+1] & _LABEL or _DIGIT )

					sub	edx,1
					mov	al,[edx]
				.endw
				.while	ecx < edx && __ltype[eax+1] & _LABEL or _DIGIT

					sub	edx,1
					mov	al,[edx]
				.endw
				.if	!( __ltype[eax+1] & _LABEL or _DIGIT )

					mov	al,[edx+1]
					.if	__ltype[eax+1] & _LABEL or _DIGIT

						add	edx,1
					.endif
				.endif
				mov	eax,edx
				mov	edx,ti
				add	ecx,[edx].ti_boff
				add	ecx,[edx].ti_xoff
				sub	ecx,eax
				.if	ecx > [edx].ti_xoff

					sub	ecx,[edx].ti_xoff
					mov	[edx].ti_xoff,0
					sub	[edx].ti_boff,ecx
				.else
					sub	[edx].ti_xoff,ecx
				.endif
			.endif
		.until	1
		xor	eax,eax
		.endc

	  .case KEY_LEFT
		tileft( edx )
		.endc

	  .case KEY_RIGHT
		tiincx( edx )
		mov	eax,_TI_CMFAILED
		.endcz
		xor	eax,eax
		.endc

	  .case KEY_HOME
		tihome( edx )
		.endc

	  .case KEY_END
		titoend( edx )
		.endc

	  .case KEY_BKSP
		tibacksp( edx )
		.endc

	  .case KEY_DEL
		tidelete( edx )
		.endc

	  .case KEY_UP
		tiup( edx )
		.endc

	  .case KEY_DOWN
		mov	eax,[edx].ti_loff
		mov	ecx,[edx].ti_yoff
		add	eax,ecx
		inc	eax
		.if	eax >= [edx].ti_lcnt
			mov	eax,_TI_CMFAILED
			.endc
		.endif
		mov	eax,[edx].ti_rows
		dec	eax
		.if	ecx < eax
			inc	[edx].ti_yoff
			xor	eax,eax
			.endc
		.endif
		mov	eax,[edx].ti_lcnt
		sub	eax,[edx].ti_loff
		sub	eax,ecx
		.if	eax < 2
			mov	eax,_TI_CMFAILED
			.endc
		.endif
		inc	[edx].ti_loff
		xor	eax,eax
		.endc

	  .case KEY_PGUP
		mov	eax,[edx].ti_rows
		.if	[edx].ti_loff >= eax
			sub	[edx].ti_loff,eax
			xor	eax,eax
			.endc
		.endif

	  .case KEY_CTRLHOME
		xor	eax,eax
		mov	[edx].ti_boff,eax
		mov	[edx].ti_xoff,eax

	  .case KEY_CTRLPGUP
		xor	eax,eax
		mov	[edx].ti_loff,eax
		mov	[edx].ti_yoff,eax
		.endc

	  .case KEY_PGDN
		mov	eax,[edx].ti_rows
		add	eax,eax
		add	eax,[edx].ti_loff
		.if	eax < [edx].ti_lcnt
			mov	eax,[edx].ti_loff
			add	eax,[edx].ti_rows
			mov	[edx].ti_loff,eax
			xor	eax,eax
			.endc
		.endif

	  .case KEY_CTRLEND
		tictrlend:
		mov	eax,[edx].ti_lcnt
		.if	eax
			dec	eax
			tialigny( edx, eax )
			xor	eax,eax
			.endc
		.endif
		mov	eax,_TI_CMFAILED
		.endc

	  .case KEY_CTRLPGDN
		mov	eax,[edx].ti_rows
		dec	eax
		mov	[edx].ti_yoff,eax
		add	eax,[edx].ti_loff
		.if	eax >= [edx].ti_lcnt
			xor	eax,eax
			.endc
		.endif
		jmp	tictrlend

	  .case KEY_CTRLUP
		tiscrollup:
		xor	eax,eax
		.if	eax != [edx].ti_loff
			dec [edx].ti_loff
			.endc
		.endif
		mov	eax,_TI_CMFAILED
		.endc

	  .case KEY_CTRLDN
		tiscrolldn:
		mov	eax,[edx].ti_loff
		add	eax,[edx].ti_yoff
		inc	eax
		cmp	eax,[edx].ti_lcnt
		mov	eax,_TI_CMFAILED
		.endcnb
		inc	[edx].ti_loff
		xor	eax,eax
		.endc

	  .case KEY_MOUSEUP
		mov	eax,_TI_CMFAILED
		mov	ecx,3
		.endc  .if ecx > [edx].ti_loff
		sub	[edx].ti_loff,ecx
		xor	eax,eax
		.endc

	  .case KEY_MOUSEDN
		mov	eax,[edx].ti_loff
		add	eax,[edx].ti_yoff
		add	eax,3
		.if	eax < [edx].ti_lcnt

			add	[edx].ti_loff,3
			xor	eax,eax
			.endc
		.endif
		mov	eax,_TI_CMFAILED
		.endc

	  .case KEY_ENTER
	  .case KEY_KPENTER
		mov	eax,10
	  .default
		tiputc( edx, eax )
		.endc
	.endsw
	retn

msvalidate:

	mov	eax,[edx].ti_xpos

	.if	ecx >= eax

		add	eax,[edx].ti_cols
		.if	ecx < eax

			mov	eax,[edx].ti_ypos
			.if	ebx >= eax

				add	eax,[edx].ti_rows
				.if	ebx < eax

					xor eax,eax
					inc eax
					retn
				.endif
			.endif
		.endif
	.endif
	xor	eax,eax
	retn

tievent ENDP

	END
