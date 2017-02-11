; DZMAIN.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include stdio.inc
include stdlib.inc
include string.inc
include alloc.inc
include io.inc
include iost.inc
include progress.inc
include process.inc
include cfini.inc

config_create	PROTO

	.data

	panel_A		dd 0
	panel_B		dd 0

	.code

	OPTION	PROC: PRIVATE

ioupdate PROC stream
	;
	; This is called on each flush (copy)
	;
	mov	eax,DWORD PTR STDO.ios_total
	mov	edx,DWORD PTR STDO.ios_total[4]
	.if	BYTE PTR stream == 0
		mov	eax,DWORD PTR STDI.ios_total
		mov	edx,DWORD PTR STDI.ios_total[4]
	.endif
	.if	progress_update( edx::eax )
		xor	eax,eax ; User break (ESC)
	.else
		xor	eax,eax
		inc	eax
	.endif
	ret
ioupdate ENDP

test_path PROC

	xor	eax,eax ; validate path in ESI
	mov	cx,[esi]	; path in EDI used if fail
	.if	cl
		.if	cx == '\\'

			inc	eax
		.elseif ch == ':'

			movzx	eax,cl
			or	al,' '
			sub	al,'a' - 1

			.if	_disk_exist( eax )

				.if	filexist( esi ) == 2
					;
					; disk and path exist
					;
					; if exist, remove trailing slash from path
					;
					.if	strrchr( esi, '\' )

						mov	ecx,'\'
						.if	[eax] == cx && BYTE PTR [eax-1] != ':'

							mov	[eax],ch
						.endif
					.endif
					mov	eax,1
				.else

					xor	eax,eax
				.endif
			.endif
		.endif
	.endif
	.if	!eax

		strcpy( esi,edi )
		xor	eax,eax
	.endif
	ret
test_path ENDP

	OPTION	PROC: PUBLIC

doszip_init PROC USES esi edi ebx argv

	malloc( 5*WMAXPATH )	; directory buffers
	mov	__srcfile,eax	; source
	add	eax,WMAXPATH
	mov	__srcpath,eax
	add	eax,WMAXPATH
	mov	__outfile,eax	; target
	add	eax,WMAXPATH
	mov	__outpath,eax
	add	eax,WMAXPATH
	mov	entryname,eax	; archive->name

	wsopen( addr path_a )	; panels
	wsopen( addr path_b )

	mov	edi,_pgmpath	; %DZ%
	SetEnvironmentVariable( "DZ", edi )

	mov	bl,[edi+2]
	mov	BYTE PTR [edi+2],0
	SetEnvironmentVariable( "DZDRIVE", edi )
	mov	[edi+2],bl

	mov	ebx,edi
	;
	; Create and read the DZ.INI file
	;
	.if	!filexist( strfcat( __srcfile, ebx, addr DZ_INIFILE ) )
		;
		; virgin call..
		;
		config_create()
		and	cflag,not _C_DELHISTORY
	.endif

	CFRead( __srcfile )

	;
	; Read section [Environ]
	;
	xor	edi,edi
	mov	esi,__srcfile
	.if	CFGetSection( "Environ" )

		mov	ebx,eax

		.while	CFGetEntryID( ebx, edi )

			strcpy( esi, eax )
			inc	edi
			expenviron( esi )
			.break .if !strchr( esi, '=' )
			mov	BYTE PTR [eax],0
			inc	eax
			push	eax
			strtrim( esi )
			call	strstart
			SetEnvironmentVariable( esi, eax )
		.endw
	.endif

	;
	; Read section [Path]
	;
	xor	edi,edi
	mov	[esi],edi

	.if	CFGetSection( "Path" )

		mov	ebx,eax

		.while	CFGetEntryID( ebx, edi )

			mov	edx,eax
			strcat( strcat( esi, ";" ), edx )
			inc	edi
		.endw

		.if	[esi] != al

			inc	esi
			expenviron( esi )
			SetEnvironmentVariable( "PATH", esi )
		.endif
	.endif

	call	config_read
	call	setasymbol

	mov	eax,console
	and	eax,CON_NTCMD
	CFGetComspec( eax )

	and	config.c_apath.ws_flag,not _W_ARCHEXT
	and	config.c_bpath.ws_flag,not _W_ARCHEXT
	;
	; argv is .ZIP file or directory
	;
	mov	ebx,argv

	.if	ebx

		.if	filexist( ebx ) == 1

			strfn ( ebx )
			lea	edi,[eax-S_FBLK.fb_name]
			readword( ebx )

			.if	ax == 4B50h

				mov	eax,_W_ARCHZIP
			.elseif warctest( edi, eax ) == 1

				mov	eax,_W_ARCHEXT
			.else

				xor	eax,eax
			.endif

			.if	eax

				and	config.c_apath.ws_flag,not (_W_ARCHIVE or _W_ROOTDIR)
				and	config.c_bpath.ws_flag,not (_W_ARCHIVE or _W_ROOTDIR)
				or	eax,_W_VISIBLE
				or	config.c_apath.ws_flag,eax
				mov	eax,config.c_apath.ws_arch
				mov	BYTE PTR [eax],0
				add	edi,S_FBLK.fb_name
				strcpy( config.c_apath.ws_file, edi )

				.if	edi != ebx

					mov	BYTE PTR [edi-1],0
					jmp	chdir_arg
				.endif
				and	cflag,not _C_PANELID
				_getcwd( config.c_apath.ws_path, WMAXPATH )
			.endif

		.elseif eax
		 chdir_arg:

			and	cflag,not _C_PANELID
			mov	eax,':'

			.if	[ebx+1] == al

				mov	al,[ebx]
				or	al,20h
				sub	al,'a' - 1

				_chdrive( eax )
			.endif
			_chdir( ebx )
		.endif
	.endif

	;
	; Read section [Load]
	;
	.if	CFGetSection( "Load" )

		CFExecute( eax )
	.endif

	mov	thelp,cmhelp
	mov	oupdate,ioupdate
	mov	eax,numfblock
	mov	wsmaxfbb,eax
	mov	wsmaxfba,eax

	call	ConsolePush
	mov	eax,ConsoleIdle
	mov	tdidle,eax
ifdef __CI__
	call	CodeInfo
endif
ifdef __BMP__
	call	CaptureScreen
endif
	xor	eax,eax
	ret

doszip_init ENDP

doszip_open PROC USES esi edi ebx

	local	path[_MAX_PATH]:SBYTE

	xor	eax,eax
	mov	dzexitcode,eax
	mov	mainswitch,eax

	setconfirmflag()

	.if	cflag & _C_DELTEMP

		removetemp( addr cp_ziplst )
		and	cflag,not _C_DELTEMP
	.endif
	;
	; Init panels
	;
	mov	eax,config.c_fcb_indexa
	mov	spanela.pn_fcb_index,eax
	mov	eax,config.c_fcb_indexb
	mov	spanelb.pn_fcb_index,eax
	mov	eax,config.c_cel_indexa
	mov	spanela.pn_cel_index,eax
	mov	eax,config.c_cel_indexb
	mov	spanelb.pn_cel_index,eax

	xor	eax,eax
	lea	edx,cp_stdmask
	mov	ecx,config.c_apath.ws_mask
	.if	[ecx] == al

		strcpy( config.c_apath.ws_mask, edx )
	.endif
	mov	ecx,config.c_bpath.ws_mask
	.if	BYTE PTR [ecx] == 0

		strcpy( config.c_bpath.ws_mask, edx )
	.endif
	;
	; Init Desktop
	;
	.if	console & CON_IMODE || _scrcol < 80

		apimode()
	.endif

	call	apiopen
	mov	tupdate,apiidle
	call	apiidle
	or	console,CON_SLEEP
	call	CursorOff
	call	prect_open_ab
	lea	eax,spanelb
	.if	cpanel == eax

		lea eax,spanela
	.endif
	call	panel_openmsg
	mov	edi,_pgmpath
	mov	esi,path_a.ws_path
	.if	!test_path()

		and path_a.ws_flag,not _W_ARCHIVE
	.endif
	mov	esi,path_b.ws_path
	.if	!test_path()

		and path_b.ws_flag,not _W_ARCHIVE
	.endif
	.if	cflag & _C_COMMANDLINE

		CursorOn()
	.endif

	panel_open_ab()
	config_open()
	ret

doszip_open ENDP

doszip_hide PROC
	.if	cflag & _C_AUTOSAVE
		config_save()
	.endif
	call	apiclose
	mov	eax,panelb
	call	prect_hide
	mov	panel_B,eax
	mov	eax,panela
	call	prect_hide
	mov	panel_A,eax
	ret
doszip_hide ENDP

doszip_show PROC
	apiopen()
	.if	panel_A
		mov	eax,panela
		redraw_panel()
	.endif
	.if	panel_B
		mov	eax,panelb
		redraw_panel()
	.endif
	ret
doszip_show ENDP

doszip_close PROC
	mov	tupdate,tdummy
	.if	cflag & _C_AUTOSAVE
		config_save()
	.endif
	mov	eax,panela
	call	panel_close
	mov	eax,panelb
	call	panel_close
	call	apiclose
	_gotoxy( 0, com_info.ti_ypos )
tdummy:
	xor	eax,eax
	ret
doszip_close ENDP

	END
