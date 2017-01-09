; DZMODAL.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include string.inc
include io.inc
include alloc.inc

menus_getevent	PROTO
scroll_delay	PROTO

	.data

MSOBJ	macro	x,l,cmd
	S_RECT	<x,24,l,1>
	dd	cmd
	endm

MOBJ_Statusline label S_MSOBJ
	MSOBJ	 1,7, cmhelp
	MSOBJ	10,6, cmrename
	MSOBJ	18,7, cmview
	MSOBJ	27,7, cmedit
	MSOBJ	36,7, cmcopy
	MSOBJ	45,7, cmmove
	MSOBJ	54,7, cmmkdir
	MSOBJ	64,7, cmdelete
	MSOBJ	72,7, cmexit

	.code

comaddstring PROC string
	xor	eax,eax
	mov	edx,DLG_Commandline
	.if	BYTE PTR [edx] & _D_ONSCR
		mov	edx,string
		mov	eax,com_info.ti_bp
		.if	BYTE PTR [eax]
			strtrim( com_info.ti_bp )
			strcat( com_info.ti_bp, addr cp_space )
		.endif
		strcat( strcat( com_info.ti_bp, edx ), addr cp_space )
		comevent( KEY_END )
	.endif
	ret
comaddstring ENDP

cmcfblktocmd PROC
	mov	eax,cpanel
	.if	panel_curobj()
		comaddstring( eax )
	.endif
	ret
cmcfblktocmd ENDP

cmpathatocmd PROC
	mov	eax,panela
	mov	eax,[eax].S_PANEL.pn_wsub
	mov	eax,[eax].S_WSUB.ws_path
	comaddstring( eax )
	ret
cmpathatocmd ENDP

cmpathbtocmd PROC
	mov	eax,panelb ; @v3.35 - Ctrl-9
	mov	eax,[eax].S_PANEL.pn_wsub
	mov	eax,[eax].S_WSUB.ws_path
	comaddstring( eax )
	ret
cmpathbtocmd ENDP

statusline_xy PROC USES esi x, y, q, mo

	mov	ecx,q
	mov	edx,y
	mov	eax,cflag
	and	eax,_C_STATUSLINE

	.if	!ZERO?
		xor	eax,eax
		.if	edx == _scrrow
			mov	esi,mo
			.repeat
				mov	[esi+1],dl
				rcxyrow( [esi], x, edx )
				.break .if !ZERO?
				add	esi,8
			.untilcxz
			.if	eax
				mov	eax,esi
			.endif
		.endif
	.endif

	ret
statusline_xy ENDP

history_event_list	PROTO
DirectoryToCurrentPanel PROTO :DWORD

SetPathFromHistory PROC PRIVATE USES esi edi ebx panel

	local	ll:S_LOBJ, rc

	mov	ebx,IDD_DZHistory
	mov	eax,[ebx+6]
	mov	rc,eax
	mov	eax,panel
	mov	eax,[eax].S_PANEL.pn_dialog
	mov	cx,[eax+4] ; .S_DOBJ.dl_rect
	add	cl,3
	mov	[ebx+6],cl
	mov	eax,_scrrow
	mov	cl,al
	sub	al,ch

	.if	al >= [ebx+6].S_RECT.rc_row
		mov al,ch
		add al,2
	.else
		mov al,cl
		sub al,[ebx+6].S_RECT.rc_row
	.endif

	mov	[ebx+7],al
	mov	eax,history
	.if	eax
		mov	esi,eax
		.if	rsopen( ebx )
			mov	ebx,eax
			lea	edi,ll
			xor	eax,eax
			mov	ecx,SIZE S_LOBJ
			rep	stosb
			mov	ll.ll_proc,history_event_list
			mov	ll.ll_dcount,16
			mov	ll.ll_list,alloca( MAXHISTORY*4 )
			mov	ecx,MAXHISTORY
			mov	edi,eax
			xor	edx,edx
			.repeat
				mov	eax,[esi].S_DIRECTORY.path
				.break .if !eax
				stosd
				add	esi,SIZE S_DIRECTORY
				inc	edx
			.untilcxz
			mov	ll.ll_count,edx
			.if	edx > 16
				mov	edx,16
			.endif
			mov	ll.ll_numcel,edx
			lea	edx,ll
			mov	tdllist,edx
			mov	eax,ebx

			history_event_list()
			dlevent( ebx )
			dlclose( ebx )

			mov	eax,edx
			.if	eax
				dec	eax
				add	eax,ll.ll_index
				shl	eax,4
				add	eax,history
			.endif
		.endif
	.endif

	mov	ecx,rc
	mov	ebx,IDD_DZHistory
	mov	[ebx+6],cx

	.if	eax
		mov	ebx,eax
		mov	eax,panel
		panel_setactive()
		DirectoryToCurrentPanel( ebx )
	.endif
	ret
SetPathFromHistory ENDP

cmahistory PROC
	SetPathFromHistory( panela )
	ret
cmahistory ENDP

cmbhistory PROC
	SetPathFromHistory( panelb )
	ret
cmbhistory ENDP

panel_scrolldn PROC PRIVATE panel
	mov	eax,panel
	.if	eax == cpanel
		.repeat
			mov	edx,panel
			mov	eax,[edx].S_PANEL.pn_cel_count
			dec	eax
			.if	SDWORD PTR [edx].S_PANEL.pn_cel_index < eax
				mov	[edx].S_PANEL.pn_cel_index,eax
				mov	eax,edx
				call	pcell_update
				call	scroll_delay
			.else
				panel_event( panel, KEY_DOWN )
			.endif
			call	scroll_delay
			call	mousep
		.until	eax != 1
		mov	eax,1
	.else
		call	panel_setactive
		xor	eax,eax
	.endif
	ret
panel_scrolldn ENDP

panel_scrollup PROC PRIVATE panel
	mov	eax,panel
	.if	eax == cpanel
		.repeat
			xor	eax,eax
			mov	edx,panel
			.if	[edx].S_PANEL.pn_cel_index != eax
				mov	[edx].S_PANEL.pn_cel_index,eax
				mov	eax,edx
				call	pcell_update
				call	scroll_delay
			.else
				panel_event( panel, KEY_UP )
			.endif
			call	scroll_delay
			call	mousep
		.until	eax != 1
		mov	eax,1
	.else
		call	panel_setactive
		xor	eax,eax
	.endif
	ret
panel_scrollup ENDP

mouseevent PROC PRIVATE USES esi edi ebx

	.while	mousep()

		mov	edi,keybmouse_x
		mov	esi,keybmouse_y

		.if	cflag & _C_MENUSLINE && !esi

			mov	eax,_scrcol
			sub	eax,5
			.if	edi >= eax
				cmscreen()
				.break
			.endif
			sub	eax,13
			.if	edi > eax
				cmcalendar()
			.endif
			.break
		.endif

		.if	!( cflag & _C_MENUSLINE ) && !esi && edi <= 56
			cmxormenubar()
			menus_getevent()
			cmxormenubar()
			.break
		.endif

		.if	statusline_xy( edi, esi, 9, addr MOBJ_Statusline )

			push	eax
			msloop()
			pop	eax
			call	[eax].S_MSOBJ.mo_proc
			.break
		.endif

		mov	ebx,panela
		.if	!panel_xycmd( ebx, edi, esi )
			mov	ebx,panelb
			panel_xycmd( ebx, edi, esi )
		.endif
		.switch eax
		  .case 1
		  .case 2
			mov	eax,ebx
			panel_setactive()
			pcell_setxy( ebx, edi, esi )
			.endc
		  .case 3
			panel_scrolldn( ebx )
			.endc
		  .case 4
			panel_scrollup( ebx )
			.endc
		  .case 5
			.if	ebx == panela
				cmachdrv()
			.else
				cmbchdrv()
			.endif
			.endc
		  .case 6
			mov	eax,ebx
			panel_xormini()
			.endc
		  .case 7
			SetPathFromHistory( ebx )
			.endc
		  .case 8
			mov	eax,ebx
			panel_xorinfo()
		.endsw
		xor	eax,eax
		.break
	.endw
	ret
mouseevent ENDP

doszip_modal PROC USES esi
	;
	; _diskflag set on disk change
	;
	; mkdir():	1
	; rmdir():	1
	; osopen(WR):	1
	; remove():	1
	; rename():	1
	; setfattr():	2
	; setftime():	2
	; process():	3
	;
	xor	eax,eax
	mov	_diskflag,eax
	inc	eax
	mov	mainswitch,eax

	.while	mainswitch

		mov	eax,_diskflag
		.if	eax
			.if	eax == 3
				;
				; Update after extern command
				;
				SetConsoleTitle( DZ_Title )
				.if	cflag & _C_DELTEMP
					removetemp( addr cp_ziplst )
					and	cflag,not _C_DELTEMP
				.endif
				mov	eax,cpanel
				mov	esi,[eax].S_PANEL.pn_wsub
				.if	filexist( [esi].S_WSUB.ws_path ) != 2
					mov	eax,[esi].S_WSUB.ws_path
					mov	BYTE PTR [eax],0
					and	[esi].S_WSUB.ws_flag,not _W_ROOTDIR
				.endif
				.if	[esi].S_WSUB.ws_flag & _W_ARCHIVE
					.if	filexist( [esi].S_WSUB.ws_file ) != 1
						and	[esi].S_WSUB.ws_flag,not _W_ARCHIVE
					.endif
				.endif
				cominit( esi )
			.endif
			;
			; Clear flag and update panels
			;
			mov	BYTE PTR _diskflag,0
			reread_panels()
		.endif

		menus_getevent()
		mov	esi,eax
		.if	(eax == KEY_ENTER || eax == KEY_KPENTER) \
			&& com_base && cflag & _C_COMMANDLINE

			.if	doskeysave()
				command( addr com_base )
			.endif
			.continue .if eax
			comevent( KEY_END )
			.continue
		.elseif com_base && cflag & _C_COMMANDLINE

			.continue .if comevent( esi )
		.endif
		cpanel_state()
		.if	!ZERO?
			.continue .if panel_event( cpanel, esi )
		.endif

		.break .if mainswitch == 0
		.if	esi == MOUSECMD
			mouseevent()
			msloop()
			.continue
		.endif
		.if	esi == KEY_TAB
			panel_toggleact()
			.continue
		.endif

		lea	edx,global_key
		mov	eax,[edx].S_GLCMD.gl_key
		.while	eax
			.if	eax == esi
				call	[edx].S_GLCMD.gl_proc
				mov	eax,1
				.break
			.endif
			add	edx,SIZE S_GLCMD
			mov	eax,[edx].S_GLCMD.gl_key
		.endw
		.if	eax
			msloop()
			.continue
		.endif

		comevent( esi )
	.endw
toend:
	ret

doszip_modal ENDP

	END
