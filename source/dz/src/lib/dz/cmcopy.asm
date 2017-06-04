; CMCOPY.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include io.inc
include iost.inc
include errno.inc
include time.inc
include string.inc
include alloc.inc
include syserrls.inc

PUBLIC	copy_jump
PUBLIC	copy_flag
PUBLIC	copy_fast

_COPY_SELECTED	equ 01h ; copy selected files
_COPY_IARCHIVE	equ 02h ; source is archive
_COPY_OARCHIVE	equ 04h ; target is archive
_COPY_IEXTFILE	equ 08h ; source is .??? archive -- 7ZA.EXE
_COPY_IZIPFILE	equ 10h ; source is .ZIP archive
_COPY_OZIPFILE	equ 20h ; target is .ZIP archive
_COPY_OEXTFILE	equ 40h ; target is .??? archive -- 7ZA.EXE
_COPY_RECURSIV	equ 80h ; recursive error

	.data

copy_jump	dd 0
copy_flag	db 0
copy_fast	db 0
ALIGN	4
copy_filecount	dd 0
copy_subdcount	dd 0

cp_ercopy	db 'There was an error while copying',0

format_s	db '%s',0
format_sL_s_	db '%s',10
format_iSi	db "'%s'",0
cp_unixslash	db '/',0
cp_copyto	db "' to",0

	.code

error_copy:
	cmp	errno,ENOSPC
	je	error_diskfull
	ermsg( 0, "%s\n%s", addr cp_ercopy, __outfile )
	ret

error_diskfull:
	ermsg( 0, "%s\n%s\n\n%s", addr cp_ercopy, __outfile, sys_errlist[ENOSPC*4] )
	ret

getcopycount PROC PRIVATE USES edi ebx
	mov	ebx,cpanel
	mov	ebx,[ebx].S_PANEL.pn_wsub
	mov	ecx,[ebx].S_WSUB.ws_count
	mov	edi,[ebx].S_WSUB.ws_fcb
	.while	ecx
		mov	ebx,[edi]
		add	edi,4
		mov	eax,[ebx]
		.if	eax & _FB_SELECTED
			.if	eax & _A_SUBDIR
				inc	copy_subdcount
				push	ecx
				add	ebx,S_FBLK.fb_name
				recursive( ebx, __srcpath, __outpath )
				pop	ecx
				.if	!ZERO?
					mov	copy_flag,_COPY_RECURSIV
					.break
				.endif
			.else
				inc	copy_filecount
			.endif
		.endif
		dec	ecx
	.endw
	mov	eax,copy_filecount
	add	eax,copy_subdcount
	ret
getcopycount ENDP

cpyevent_filter PROC
	call	cmfilter
	mov	ecx,tdialog
	mov	ecx,[ecx+4]
	add	ecx,0510h
	mov	dl,ch
	mov	eax,' '
	.if	filter
		mov	al,7
	.endif
	scputw( ecx, edx, 1, eax )
	mov	eax,_C_NORMAL
	ret
cpyevent_filter ENDP

confirm_copy PROC PRIVATE USES esi edi ebx fblk, docopy
	mov	esi,docopy
	mov	eax,config.c_cflag
	mov	ecx,_C_CONFCOPY
	mov	edi,IDD_DZCopy
	.if	!esi
		mov	ecx,_C_CONFMOVE
		mov	edi,IDD_DZMove
	.endif
	and	eax,ecx
	.if	ZERO?
		inc	eax
	.elseif rsopen( edi )
		mov	ebx,eax
		.if	esi
			mov	filter,0
			mov	[ebx+3*16].S_TOBJ.to_proc,cpyevent_filter
		.endif
		dlshow( ebx )
		mov	edx,[ebx].S_DOBJ.dl_rect
		add	edx,0209h
		mov	esi,__outpath
		mov	BYTE PTR [ebx+1*16+2],WMAXPATH/16
		mov	eax,fblk
		mov	eax,[eax].S_FBLK.fb_flag
		.if	eax & _FB_SELECTED
			mov	eax,copy_filecount
			add	eax,copy_subdcount
			mov	cl,dh
			scputf( edx, ecx, 0, 0, addr cp_copyselected, eax )
		.else
			mov	cl,dh
			scputw( edx, ecx, 1, 0027h )
			inc	dl
			mov	eax,fblk
			add	eax,S_FBLK.fb_name
			scpath( edx, ecx, 38, eax )
			add	dl,al
			scputs( edx, ecx, 0, 0, addr cp_copyto )
			mov	eax,fblk
			.if	!( BYTE PTR [eax].S_FBLK.fb_flag & _A_SUBDIR )
				mov	esi,__outfile
			.endif
		.endif
		.if	copy_flag & _COPY_OARCHIVE
			mov	esi,__outfile
		.endif
		mov	eax,[ebx].S_DOBJ.dl_object
		mov	[eax].S_TOBJ.to_data,esi
		.if	copy_flag & _COPY_IARCHIVE or _COPY_OARCHIVE
			dlinit( ebx )
			mov	eax,[ebx].S_DOBJ.dl_object
			or	[eax].S_TOBJ.to_flag,_O_STATE
		.endif
		rsevent( edi, ebx )
		dlclose( ebx )
		xor	eax,eax
		.if	edx
			inc	eax
		.endif
	.endif
	ret
confirm_copy ENDP

init_copy PROC USES esi edi ebx fblk, docopy

	xor	eax,eax
	mov	copy_fast,al
	mov	copy_jump,eax		; set if skip file (jump)
	mov	copy_flag,al		; type of copy
	mov	copy_filecount,eax	; selected files
	mov	copy_subdcount,eax

	.if	!cpanel_gettarget()	; get __outpath
		ermsg( 0, "You need two file panels to use this command" )
		jmp	toend
	.endif

	mov	esi,eax			; ESI = target path
	call	panel_getb
	mov	edi,[eax].S_PANEL.pn_wsub ; EDI = target directory
	mov	eax,cpanel
	mov	eax,[eax].S_PANEL.pn_wsub

	.if	[eax].S_WSUB.ws_flag & _W_ROOTDIR
		call	notsup
		jmp	toend
	.endif

	mov	eax,[edi].S_WSUB.ws_flag
	and	eax,_W_ARCHIVE
	.if	!ZERO?
		.if	[edi].S_WSUB.ws_count == 1
			inc	copy_fast
		.endif
		and	eax,_W_ARCHEXT
		mov	eax,_COPY_OARCHIVE or _COPY_OEXTFILE
		.if	ZERO?
			mov	eax,_COPY_OARCHIVE or _COPY_OZIPFILE
			.if	BYTE PTR docopy == 0
				;
				; moving files to archive..
				;
				call	notsup
				jmp	toend
			.endif
		.endif
	.endif

	mov	copy_flag,al
	mov	edx,__srcpath
	mov	ebx,__outpath
	strcpy( ebx, esi )
	mov	eax,cpanel
	mov	eax,[eax].S_PANEL.pn_wsub
	strcpy( edx, [eax].S_WSUB.ws_path )
	mov	eax,fblk
	add	eax,S_FBLK.fb_name
	strfcat( __srcfile, edx, eax )
	.if	copy_flag & _COPY_OARCHIVE
		strfcat( __outfile, ebx, [edi].S_WSUB.ws_file )
		strcpy( ebx, [edi].S_WSUB.ws_arch )
		dostounix( eax )
	.else
		strfcat( __outfile, ebx, strfn( __srcfile ) )
	.endif
	mov	eax,fblk
	mov	esi,[eax].S_FBLK.fb_flag
	.if	esi & _FB_SELECTED
		call	getcopycount		; copy/move selected files
		test	eax,eax
		mov	al,copy_flag
		jz	toend
		or	copy_flag,_COPY_SELECTED
	.elseif esi & _A_SUBDIR
		add	eax,S_FBLK.fb_name
		recursive( eax, __srcpath, ebx )
		mov	copy_subdcount,1	; copy/move one directory
		.if	!ZERO?
			or copy_flag,_COPY_RECURSIV
		.endif
	.else
		mov	copy_filecount,1	; copy/move one file
	.endif
	mov	eax,copy_filecount
	add	eax,copy_subdcount
	jz	toend
	mov	eax,fblk
	mov	eax,[eax].S_FBLK.fb_flag
	and	eax,_FB_ARCHIVE
	.if	!ZERO?
		.if	eax & _FB_ARCHEXT
			mov eax,_COPY_IARCHIVE or _COPY_IEXTFILE
		.else
			mov eax,_COPY_IARCHIVE or _COPY_IZIPFILE
		.endif
	.endif
	or	copy_flag,al
	confirm_copy( fblk, docopy )
	jz	toend

	.if	copy_flag & _COPY_IARCHIVE
		and	copy_flag,not _COPY_RECURSIV
	.else
		.if	!strcmp( __outfile, __srcfile )
			ermsg( 0, "You can't copy a file to itself" )
			jmp	toend
		.endif
	.endif

	.if	copy_flag & _COPY_RECURSIV
		ermsg( 0, "You tried to recursively copy or move a directory" )
		jmp	toend
	.endif

	.if	!( copy_flag & _COPY_OARCHIVE )
		.if	getfattr( ebx ) == -1
			.if	_mkdir( ebx )
				ermkdir( ebx )
				inc	eax
				jmp	toend
			.endif
		.endif
	.endif

	call	setconfirmflag
	mov	eax,1
toend:
	test	eax,eax
	ret
init_copy ENDP

copyfile PROC USES esi edi file_size:QWORD, t:DWORD, attrib:DWORD
	xor	esi,esi
	;----------------
	; open the files
	;----------------
	.ifs wscopyopen(__srcfile, __outfile) > 0
		;---------------
		; copy the file
		;---------------
		or STDI.ios_flag,IO_USECRC
		or STDO.ios_flag,IO_USECRC or IO_UPDTOTAL or IO_USEUPD
		iocopy( addr STDO, addr STDI, file_size )
		mov esi,eax
		.if eax
			ioflush( addr STDO )	; flush the stream
		.endif
		ioclose( addr STDI )		; test CRC value

		mov eax,STDO.ios_crc
		.if eax != STDI.ios_crc
			ioclose( addr STDO )
			lea eax,CP_EIO
			mov edx,errno
			.if edx
				mov eax,sys_errlist[edx*4]
			.endif
			ermsg( 0, addr format_sL_s_, addr cp_ercopy, eax )
		.elseif !esi
			ioclose( addr STDO )
			call	error_copy
			wscopyremove(__outfile) ; -1
		.else
			progress_update( file_size )
			;--------------------------------
			; return user break (ESC) in ESI
			;--------------------------------
			mov	esi,eax
			setftime( STDO.ios_file, time )
			ioclose( addr STDO )
			mov	eax,attrib
			;-----------------------------------
			; remove RDONLY if CD-ROOM - @v2.18
			;-----------------------------------
			.if al & _A_RDONLY && cflag & _C_CDCLRDONLY
				mov edx,cpanel
				mov edx,[edx].S_PANEL.pn_wsub
				mov edx,[edx].S_WSUB.ws_flag
				.if edx & _W_CDROOM
					xor al,_A_RDONLY
				.endif
			.endif
			and	eax,_A_FATTRIB
			setfattr( __outfile, eax )
			mov	eax,esi
		.endif
	.endif
	;---------------------------------------------
	; return 1: ok, -1: error, 0: jump (if exist)
	;---------------------------------------------
	ret
copyfile ENDP

fblk_copyfile PROC PRIVATE fblk, skip_outfile
	.if	filter_fblk( fblk )
		mov	eax,fblk
		add	eax,S_FBLK.fb_name
		strfcat( __srcfile, __srcpath, eax )
		.if	!skip_outfile && !( copy_flag & _COPY_OARCHIVE )
			mov	eax,fblk
			add	eax,S_FBLK.fb_name
			strfcat( __outfile, __outpath, eax )
		.endif
		mov	ecx,fblk
		.if	!progress_set( addr [ecx].S_FBLK.fb_name, __outpath, [ecx].S_FBLK.fb_size )
			mov	ecx,fblk
			mov	edx,[ecx].S_FBLK.fb_flag
			.if	edx & _FB_ARCHIVE
				mov eax,cpanel
				wsdecomp( [eax].S_PANEL.pn_wsub, ecx, __outpath )
			.elseif copy_flag & _COPY_OARCHIVE
				wzipadd( [ecx].S_FBLK.fb_size, [ecx].S_FBLK.fb_time, edx )
			.else
				copyfile( [ecx].S_FBLK.fb_size, [ecx].S_FBLK.fb_time, edx )
			.endif
		.endif
	.endif
	ret
fblk_copyfile ENDP

fp_copyfile PROC USES esi edi ebx directory, wblk

	.if filter_wblk(wblk)

		mov ebx,wblk
		strfcat(__srcfile, directory, addr [ebx].WIN32_FIND_DATA.cFileName)
		.if !(copy_flag & _COPY_OARCHIVE)

			strfcat(__outfile, __outpath, addr [ebx].WIN32_FIND_DATA.cFileName)
		.endif
		mov esi,[ebx].WIN32_FIND_DATA.nFileSizeHigh
		mov edi,[ebx].WIN32_FIND_DATA.nFileSizeLow
		.if !progress_set(addr [ebx].WIN32_FIND_DATA.cFileName, __outpath, esi::edi)

			__FTToTime(addr [ebx].WIN32_FIND_DATA.ftLastWriteTime)
			mov edx,[ebx].WIN32_FIND_DATA.dwFileAttributes
			and edx,_A_FATTRIB
			.if copy_flag & _COPY_OARCHIVE
				wzipadd(esi::edi, eax, edx )
			.else
				copyfile(esi::edi, eax, edx )
			.endif
		.endif
	.endif
	ret
fp_copyfile ENDP

fp_copydirectory PROC USES esi edi ebx directory
	alloca( WMAXPATH )
	mov	ebx,eax
	strlen( __srcpath )
	mov	esi,directory
	add	esi,eax
	.if	BYTE PTR [esi] == '\'
		inc	esi
	.endif
	strcpy( ebx, __outpath )
	.if	copy_flag & _COPY_OARCHIVE
		mov	eax,__outpath
		.if	BYTE PTR [eax]
			strcat( eax, addr cp_unixslash )
		.endif
		dostounix( strcat( strcat( __outpath, esi ), addr cp_unixslash ) )
		mov	eax,__srcfile
		mov	BYTE PTR [eax],0
		.if	cflag & _C_ZINCSUBDIR
			call	clock
			push	eax
			getfattr( directory )
			pop	edx
			wzipadd( 0, edx, eax )
		.endif
	.elseif !_mkdir( strfcat( __outpath, 0, esi ) )
		.if	!setfattr( __outpath, 0 )
			getfattr( directory )
			and	eax,not _A_SUBDIR
			setfattr( __outpath, eax )
		.endif
	.endif
	scan_files( directory )
	mov	esi,eax
	strcpy( __outpath, ebx )
	mov	eax,esi
	mov	esp,ebp			; free EBX..
	ret
fp_copydirectory ENDP

copydirectory PROC PRIVATE USES esi edi ebx fblk
	alloca( WMAXPATH )
	mov	esi,eax
	mov	edi,fblk
	lea	edi,[edi].S_FBLK.fb_name
	mov	ebx,__outpath
	.if	!progress_set( edi, ebx, 0 )
		.if	!( copy_flag & _COPY_OARCHIVE )
			_mkdir( ebx )
		.endif
		strfcat( esi, __srcpath, edi )
		.if	copy_flag & _COPY_OARCHIVE
			.if	copy_fast != 1
				mov	eax,panela
				.if	eax == cpanel
					mov eax,panelb
				.endif
				;-------------------------------------------
				; if panel name is not found: use fast copy
				;-------------------------------------------
				.if	wsearch( [eax].S_PANEL.pn_wsub, edi ) == -1
					inc	copy_fast
					.if	wzipopen()
						scansub( esi, addr cp_stdmask, 1 )
						dec	copy_fast
						call	wzipclose
					.else
						dec	copy_fast
						dec	eax
					.endif
					jmp	toend
				.endif
			.endif
		.endif
		scansub( esi, addr cp_stdmask, 1 )
	.endif
toend:
	mov	esp,ebp
	ret
copydirectory ENDP

copyselected PROC PRIVATE
	call	panel_getb
	push	[eax].S_PANEL.pn_fcb_index
	push	[eax].S_PANEL.pn_cel_index
	mov	ecx,esi
	.repeat
		.if	ecx & _FB_ARCHIVE
			mov eax,cpanel
			wsdecomp( [eax].S_PANEL.pn_wsub, edi, __outpath )
		.elseif cl & _A_SUBDIR
			copydirectory( edi )
		.else
			fblk_copyfile( edi, 0 )
		.endif
		.break .if eax
		cpanel_deselect( edi )
		panel_findnext(cpanel)
		mov	edi,edx
	.until	ZERO?
	mov	edx,eax
	call	panel_getb
	mov	ecx,eax
	pop	eax
	mov	[ecx].S_PANEL.pn_cel_index,eax
	pop	eax
	mov	[ecx].S_PANEL.pn_fcb_index,eax
	mov	eax,edx
	ret
copyselected ENDP

cmcopy	PROC USES esi edi ebx

	.if	cpanel_findfirst()

		mov	edi,edx
		mov	esi,ecx

		.if	init_copy( edx, 1 )

			mov	al,copy_flag
			.if	al & _COPY_IEXTFILE
				mov	ebx,cpanel
				mov	ebx,[ebx].S_PANEL.pn_wsub
				warccopy( ebx, edi, __outpath, copy_subdcount )
			.elseif al & _COPY_OEXTFILE
				call	panel_getb
				mov	ebx,eax
				mov	edx,[ebx].S_PANEL.pn_wsub
				mov	ebx,cpanel
				mov	ebx,[ebx].S_PANEL.pn_wsub
				warcadd( edx, ebx, edi )
			.else
				progress_open( addr cp_copy, addr cp_copy )
				mov	fp_fileblock,fp_copyfile
				mov	fp_directory,fp_copydirectory
				.if	copy_flag & _COPY_OARCHIVE
					dostounix( __outpath )
					.if	copy_flag & _COPY_OZIPFILE && copy_fast
						call	wzipopen
						jz	done
					.endif
				.endif
				.if	esi & _FB_SELECTED
					call	copyselected
				.elseif esi & _A_SUBDIR
					.if	esi & _FB_ARCHIVE
						mov	eax,cpanel
						wsdecomp( [eax].S_PANEL.pn_wsub, edi, __outpath )
					.else
						copydirectory( edi )
					.endif
				.else
					fblk_copyfile( edi, 1 )
				.endif
				.if	copy_flag & _COPY_OZIPFILE && copy_fast
					call wzipclose
				.endif
				done:
				call	progress_close
			.endif
		.endif
	.endif
	mov	copy_fast,0
	ret
cmcopy	ENDP

	END

