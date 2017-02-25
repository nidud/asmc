include alloc.inc
include consx.inc
include string.inc
include cfini.inc
include stdlib.inc

MAXLINES	equ 12		; visible lines on screen
MAXNAMES	equ 0x2000	; name buffer
_CMPCASE	equ 1

externdef	IDD_FindSection:PVOID

	.code

compare PROC PRIVATE a, b

	mov	eax,a
	mov	edx,b

	mov	eax,[eax]
	mov	edx,[edx]
IFDEF _CMPCASE
	strcmp( eax, edx )
ELSE
	_stricmp( eax, edx )
ENDIF
	ret

compare ENDP

CFFindSection PROC USES esi edi ebx cfini:PCFINI, __section:LPSTR, __entry:LPSTR

local	cursor:		S_CURSOR,
	dialog:		PTR S_DOBJ,
	dlg_x:		UINT,
	dlg_y:		UINT,
	dlg_c:		UINT,
	cur_x:		UINT,
	x, y:		UINT,
	name_table:	PVOID,
	name_count:	UINT,
	index:		SINT,
	result:		UINT,
	section[64]:	SBYTE

	CursorGet( addr cursor )
	CursorOn()

	mov	result,0

	.if	rsopen( IDD_FindSection )

		mov	dialog,eax
		mov	dlg_x,eax
		mov	cur_x,eax

		.if	malloc( MAXNAMES*4 )

			mov	name_table,eax
			mov	name_count,0
			mov	esi,cfini

			.while	esi

				.if	[esi].S_CFINI.cf_flag & _CFSECTION

					mov	eax,[esi].S_CFINI.cf_name

					.if	eax

						.if	byte ptr [eax]

							mov	ecx,name_count
							.break .if ecx >= MAXNAMES

							inc	name_count
							shl	ecx,2
							add	ecx,name_table
							mov	[ecx],eax
						.endif
					.endif
				.endif
				mov	esi,[esi].S_CFINI.cf_next
			.endw

			mov	eax,name_count
			.if	eax

				qsort ( name_table, eax, 4, compare )
				strcpy( addr section, __section )
				mov	eax,1
			.else

				free( name_table )
				xor	eax,eax
			.endif
		.endif

		mov	result,eax
	.endif

	.if	result

		dlshow( dialog )

		xor	ebx,ebx
		mov	index,ebx
		mov	result,ebx

		strcat( addr section, "?" )
		PushEvent( KEY_BKSP )

		.while	1

			mov	esi,dialog
			movzx	edx,[esi].S_DOBJ.dl_rect.rc_y
			inc	edx
			mov	dlg_y,edx
			movzx	edi,[esi].S_DOBJ.dl_rect.rc_col
			sub	edi,4
			mov	dlg_c,edi
			movzx	ebx,[esi].S_DOBJ.dl_rect.rc_x
			add	ebx,2
			mov	dlg_x,ebx
			mov	cur_x,ebx
			add	cur_x,strlen(addr section)
			movzx	ecx,[esi].S_DOBJ.dl_rect.rc_row
			sub	ecx,3

			lea	eax,[ebx+32]
			sub	edi,32
			scputc( eax, edx, edi,' ' )
			add	edi,32
			scputc( ebx, edx, 32, 0FAh )

			inc	edx
			.repeat

				scputc( ebx, edx, edi, ' ' )
				inc	edx
			.untilcxz

			mov	edx,dlg_y
			scputs( ebx, edx, 0, 31, addr section )

			mov	esi,index
			mov	edi,name_count
			.if	edi

				sub	edi,esi
				.if	edi >= MAXLINES

					mov	edi,MAXLINES
				.endif
				add	edx,2
				mov	y,edx
				shl	esi,2
				add	esi,name_table

				.repeat

					scputs( ebx, y, 0, 28, [esi] )

					.if	CFGetEntry( __CFGetSection( cfini, [esi] ), __entry )

						mov	ecx,ebx
						add	ecx,30
						scputs( ecx, y, 0, 35, eax )
					.endif

					inc	y
					add	esi,4
					dec	edi
				.untilz

				add	ebx,45
				mov	edx,dlg_y
				scputf( ebx, edx, 0, 5, "%d", index )
				add	ebx,8
				scputf( ebx, edx, 0, 5, "%d", name_count )
				add	ebx,8
				scputf( ebx, edx, 0, 5, "%d", MAXNAMES )
			.endif

			event_loop:

			_gotoxy( cur_x, dlg_y )

			.switch tgetevent()

			  .case MOUSECMD

				mov	esi,mousey()
				mov	edi,mousex()
				mov	ebx,dialog
				mov	edx,[ebx].S_DOBJ.dl_rect
				.if	rcxyrow( edx, edi, esi ) ;== 1

					rcmsmove(
						addr [ebx].S_DOBJ.dl_rect,
						[ebx].S_DOBJ.dl_wp,
						[ebx].S_DOBJ.dl_flag )
				.endif
				msloop()
				.endc

			  .case KEY_ESC
				.break

			  .case KEY_ENTER
			  .case KEY_KPENTER

				mov	edx,name_table
				mov	ebx,index
if 0
				mov	ecx,cur_x
				sub	ecx,dlg_x
				mov	esi,[edx+ebx*4]
				lea	edi,section

				.ifnz
IFDEF _CMPCASE
					repz	cmpsb
ELSE
					.repeat
						mov	al,[esi]
						mov	ah,[edi]
						add	esi,1
						add	edi,1
						.continue .if al == ah
						or	ax,0x2020
						.break .if al != ah
					.untilcxz
ENDIF
					jnz	event_loop
				.endif
endif
				mov	eax,[edx+ebx*4]
				mov	result,eax
				.break

			  .case KEY_BKSP

				.while	1

					mov	eax,dlg_x
					.break .if eax == cur_x

					dec	cur_x
					xor	ebx,ebx
					mov	index,ebx
					search_count()

					mov	ecx,cur_x
					sub	ecx,dlg_x
					mov	section[ecx],0

					.break .if !eax
				.endw
				.endc

			  .case KEY_HOME
				mov	eax,index
				.if	eax

					mov	index,0
					.endc
				.endif
				jmp	event_loop

			  .case KEY_END
				mov	eax,name_count
				dec	eax
				.if	eax != index

					mov	index,eax
					.endc
				.endif
				jmp	event_loop

			  .case KEY_UP
				.if	index

					dec	index
					.endc
				.endif
				jmp	event_loop

			  .case KEY_DOWN
				mov	eax,name_count
				dec	eax
				.if	index < eax

					inc	index
					.endc
				.endif
				jmp	event_loop

			  .case KEY_PGUP
				mov	eax,index
				.if	eax < MAXLINES

					xor	eax,eax
				.else
					sub	eax,MAXLINES
				.endif
				.if	eax != index

					mov	index,eax
					.endc
				.endif
				jmp	event_loop

			  .case KEY_PGDN
				mov	edx,name_count
				dec	edx
				mov	eax,index
				.if	eax < edx

					add	eax,MAXLINES
					.if	eax <= edx

						mov	index,eax
					.else
						mov	index,edx
					.endif
					.endc
				.endif
				jmp	event_loop

			  .case KEY_LEFT
				xor	ebx,ebx
				.endc	.if !search_count()
				jmp	event_loop

			  .case KEY_RIGHT

				mov	ecx,cur_x
				sub	ecx,dlg_x
				jz	event_loop

				mov	edx,name_table
				mov	eax,index
				mov	esi,[edx+eax*4]
				lea	edi,section
				mov	ebx,ecx
				repz	cmpsb
				jnz	event_loop

				mov	esi,[edx+eax*4]
				movzx	eax,BYTE PTR [esi+ebx]

			  .default

				mov	ecx,cur_x
				sub	ecx,dlg_x

				.if	al && ecx < 32

					movzx	eax,al
					mov	WORD PTR section[ecx],ax
					inc	cur_x

					mov	ebx,index
					.if	search_count()

						.if	search_index()

							dec	cur_x
							mov	ecx,cur_x
							sub	ecx,dlg_x
							xor	eax,eax
							mov	section[ecx],al
							jmp	event_loop
						.endif
					.endif
					.endc
				.endif
				jmp	event_loop
			.endsw
		.endw

		dlclose( dialog )

	.endif

	CursorSet( addr cursor )

	mov	eax,result
	ret

search_index:	; from start to index

	xor	ebx,ebx
	mov	edx,index
	jmp	search_edx

search_count:	; from index to end

	mov	edx,name_count

search_edx:

	mov	eax,name_table

	.while	ebx < edx

		mov	ecx,cur_x
		sub	ecx,dlg_x

		.if	!ZERO?

			mov	esi,[eax+ebx*4]
			lea	edi,section
IFDEF _CMPCASE
			repz	cmpsb
ELSE
			push	eax
			.repeat
				mov	al,[esi]
				mov	ah,[edi]
				add	esi,1
				add	edi,1
				.continue .if al == ah
				or	ax,0x2020
				.break .if al != ah
			.untilcxz
			pop	eax
ENDIF
			.if	ZERO?

				mov	index,ebx
				xor	eax,eax
				.break
			.endif
		.endif
		add	ebx,1
	.endw
	retn

CFFindSection ENDP

	end
