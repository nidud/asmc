; COMMAND.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include tview.inc
include process.inc
include string.inc
include alloc.inc
include stdio.inc
include stdlib.inc
include io.inc
include crtl.inc
include cfini.inc

	.data

com_wsub  dd path_a
com_base  db WMAXPATH dup(0)
com_info  S_TEDIT <com_base,_TE_OVERWRITE,0,24,80,WMAXPATH,0720h,0,0,0,0,0>

	.code

comhndlevent PROC PRIVATE
	.if	cflag & _C_COMMANDLINE
		CursorOn() ; preserve EAX
		dledite( addr com_info, eax )
		ret
	.endif
	xor	eax,eax
	ret
comhndlevent ENDP

cominit PROC wsub
	mov	eax,wsub
	mov	com_wsub,eax
	invoke	wsinit,eax
	call	cominitline
	mov	eax,1
	ret
cominit ENDP

cominitline PROC PRIVATE USES ebx
	mov	ebx,DLG_Commandline
	.if	ebx && [ebx].S_DOBJ.dl_flag & _D_DOPEN
		movzx	eax,[ebx].S_DOBJ.dl_rect.rc_x
		movzx	edx,[ebx].S_DOBJ.dl_rect.rc_y
		mov	com_info.ti_ypos,edx
		mov	com_info.ti_xpos,eax
		mov	eax,com_wsub
		strlen([eax].S_WSUB.ws_path)
		inc	eax
		.if	eax > 51
			mov	eax,51
		.endif
		mov	com_info.ti_xpos,eax
		mov	edx,_scrcol
		sub	edx,eax
		mov	com_info.ti_cols,edx
		_gotoxy( eax, com_info.ti_ypos )
		.if	[ebx].S_DOBJ.dl_flag & _D_ONSCR
			mov	edx,com_info.ti_ypos
			scputw( 0, edx, _scrcol, ' ' )
			mov	eax,com_wsub
			scpath( 0, edx, 50, [eax].S_WSUB.ws_path )
			mov	al,BYTE PTR com_info.ti_xpos
			dec	al
			scputw( eax, edx, 1, 62 ) ; '>'
			mov	eax,KEY_PGUP
			comhndlevent()
		.else
			mov	eax,[ebx].S_DOBJ.dl_wp
			wcputw( eax, _scrcol, ' ' )
			add	eax,com_info.ti_xpos
			add	eax,com_info.ti_xpos
			sub	eax,2
			wcputw( eax, 1, 62 )
			mov	eax,com_wsub
			wcpath( [ebx].S_DOBJ.dl_wp, 50, [eax].S_WSUB.ws_path )
		.endif
	.endif
	ret
cominitline ENDP

comshow PROC
	mov	eax,com_info.ti_ypos
	lea	ecx,prect_b
	.if	!( BYTE PTR [ecx] & _D_ONSCR )
		lea	ecx,prect_a
	.endif
	.if	( BYTE PTR [ecx] & _D_ONSCR )
		mov dl,[ecx].S_DOBJ.dl_rect.rc_y
		add dl,[ecx].S_DOBJ.dl_rect.rc_row
		.if dl > al
			mov al,dl
		.endif
	.endif
	.if	!eax && cflag & _C_MENUSLINE
		inc eax
	.endif
	.if	eax >= _scrrow && cflag & _C_STATUSLINE
		dec eax
	.endif
	.if	eax > _scrrow
		mov eax,_scrrow
	.endif
	mov	BYTE PTR com_info.ti_ypos,al
	mov	edx,DLG_Commandline
	mov	[edx+5],al

	.if	cflag & _C_COMMANDLINE
		_gotoxy( 0, eax )
		CursorOn()
		dlshow( DLG_Commandline )
		cominitline()
	.endif
	ret
comshow ENDP

comhide PROC
	dlhide( DLG_Commandline )
	CursorOff()
	ret
comhide ENDP

comevent PROC event
	mov	eax,event
	.switch eax
	  .case KEY_UP
		.if	cpanel_state()
			xor eax,eax
		.else
			cmdoskeyup()
			mov eax,1
		.endif
		.endc
	  .case KEY_DOWN
		.if	cpanel_state()
			xor eax,eax
		.else
			cmdoskeydown()
			mov eax,1
		.endif
		.endc
	  .case KEY_ALTRIGHT
		cmpathright()
		mov	eax,1
		.endc
	  .case KEY_ALTLEFT
		cmpathleft()
		mov	eax,1
		.endc
	  .case 0
	  .case KEY_CTRLX
		xor	eax,eax
		.endc
	  .default
		.if	comhndlevent()
			xor eax,eax
		.else
			mov eax,1
		.endif
	.endsw
	ret
comevent ENDP

clrcmdl PROC
	.if	cflag & _C_COMMANDLINE
		mov	com_base,0
		comevent( KEY_HOME )
		cominitline()
	.endif
	ret
clrcmdl ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; command
;
command PROC USES esi edi ebx cmd ; BOOL

	local	cursor:S_CURSOR, batch, path, temp
	local	UpdateEnviron, CallBatch

	mov	eax,console
	and	eax,CON_NTCMD
	CFGetComspec( eax )

	alloca( 8000h + _MAX_PATH*2 + 32 )
	mov	edi,eax
	add	eax,8000h
	mov	batch,eax
	mov	byte ptr [eax],0
	add	eax,_MAX_PATH
	mov	path,eax
	add	eax,_MAX_PATH
	mov	temp,eax

	mov	edx,cmd
	.while	BYTE PTR [edx] == ' '
		add edx,1
	.endw

	strtrim( strnzcpy( edi, edx, 8000h-1 ) )
	test	eax,eax
	jz	toend
	expenviron( edi )

	.if BYTE PTR [edi] == '%'
		;
		; %view% <filename>
		; %edit% <filename>
		; %find% [<directory>] [<file_mask(s)>] [<text_to_find_in_files>]
		;
		.switch
		  .case !_strnicmp( edi, "%view%", 6 )
			load_tview( addr [edi+7], 0 )
			mov	eax,1
			.endc
		  .case !_strnicmp( edi, "%edit%", 6 )
			load_tedit( addr [edi+7], 4 )
			mov	eax,1
			.endc
		  .case !_strnicmp( edi, "%find%", 6 )
			.if BYTE PTR [edi+6] == ' '
				add	edi,7
				strchr( edi, ' ' )
				mov	ecx,edi
				mov	edi,eax
				.if strrchr( ecx, ' ' )
					mov BYTE PTR [edi],0	; end of first arg
					mov BYTE PTR [eax],0	; start of last arg - 1
					.if BYTE PTR [eax+1] != '?' && eax != edi
						inc	eax
						strcpy( addr searchstring, eax )
					.endif
					.if BYTE PTR [edi+1] != '?'
						strcpy( addr findfilemask, addr [edi+1] )
					.endif
				.endif
				FindFile( addr [edi+7] )
			.else
				call	cmsearch
				mov	eax,1
			.endif
			.endc
		  .default
			xor	eax,eax
		.endsw
		jmp	toend
	.endif

	clrcmdl()

	xor	eax,eax
	mov	CallBatch,eax
	mov	UpdateEnviron,eax
	;
	; use batch for old .EXE files, \r\n, > and <
	;
	.switch
	  .case strchr( edi, '>' )
	  .case strchr( edi, '<' )
	  .case strchr( edi, 10 )
		jmp	create_batch
	.endsw

	;
	; Inline CD and C: commands
	;
	mov	edx,edi
	mov	ecx,1
	.if	WORD PTR [edi+1] != ':'
		mov	eax,[edi]
		or	ax,2020h
		.if	ax != 'dc'
			xor	ecx,ecx
		.else
			add	edx,2
			mov	al,[edx]
			.if	al != ' ' && al != '.' && al != '\'
				xor	ecx,ecx
			.endif
		.endif
	.endif
	.if	ecx
		mov	esi,edx
		.while	BYTE PTR [esi] == ' '
			add esi,1
		.endw
		.if SetCurrentDirectory( esi )
			.if GetCurrentDirectory( _MAX_PATH, esi )
				mov	eax,esi
				call	cpanel_setpath
				mov	_diskflag,3
			.endif
		.endif
		jmp	toend
	.endif

	;
	; Parse the first token
	;
	strnzcpy( path, edi, _MAX_PATH-1 )
	mov	ebx,eax
	strtrim( eax )
	jz	execute_command

	.if	BYTE PTR [ebx] == '"'
		.if strchr( strcpy( ebx, addr [ebx+1] ), '"' )
			mov BYTE PTR [eax],0
		.elseif strchr( ebx, ' ' )
			mov BYTE PTR [eax],0
		.endif
	.elseif strchr( ebx, ' ' )
		mov BYTE PTR [eax],0
	.endif

	.if	!searchp( ebx )
		;
		; Not an executable file
		;
		; SET and FOR may change the environment
		;
		__isexec( ebx )
		test	eax,eax
		jnz	execute_command
		mov	eax,[ebx]
		and	eax,00FFFFFFh
		or	eax,00202020h
		.switch eax
		  ;
		  ; Change or set environment variable
		  ;
		  .case 'tes'	; SET
		  .case 'rof'	; FOR
			mov	al,[edi+3]
			.switch al
			  .case ' '
			  .case 9
				inc	UpdateEnviron
				jmp	create_batch
			.endsw
		.endsw
		jmp	execute_command
	.endif

	.switch __isexec( strcpy( ebx, eax ) )
	  .case _EXEC_EXE
		.if comspec_type == 0
			.if osopen( ebx, 0, M_RDONLY, A_OPEN ) != -1
				mov	esi,eax
				osread( esi, temp, 32 )
				push	eax
				_close( esi )
				pop	eax
				.if	eax == 32
					mov	esi,temp
					mov	ax,[esi+24]
					.if	ax == 0040h
						xor	eax,eax
						.if	eax != [esi+20]
							jmp create_batch
						.endif
					.endif
				.endif
			.endif
		.endif
		jmp	execute_command
	  .case _EXEC_CMD
	  .case _EXEC_BAT
		mov	CallBatch,eax
		mov	UpdateEnviron,eax
	  .case _EXEC_COM
		jmp	create_batch
	.endsw

create_batch:

	mov	eax,console
	and	eax,CON_CMDENV
	.if	!eax
		mov	CallBatch,eax
		mov	UpdateEnviron,eax
	.endif

	.if	CreateBatch( edi, CallBatch, UpdateEnviron ) != -1
		strcpy( batch, eax )
	.endif


execute_command:

	doszip_hide()
	_gotoxy( 0, com_info.ti_ypos )
	CursorOn()
	system( edi )
	push	eax

	.if	UpdateEnviron

		strfcat( edi, envtemp, "dzcmd.env" )
		ReadEnvironment( edi )
		removefile( edi )
		GetEnvironmentTEMP()
		GetEnvironmentPATH()
		.if	!GetCurrentDirectory( WMAXPATH, edi )
			xor	edi,edi
		.endif
	.endif

	doszip_show()
	SetKeyState()

	mov	eax,batch
	.if	BYTE PTR [eax]
		removefile( eax )
	.endif

	.if	UpdateEnviron && edi
		mov	eax,edi
		cpanel_setpath()
	.endif
	pop	eax
toend:
	ret
command ENDP

	END

