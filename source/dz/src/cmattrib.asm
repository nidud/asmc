; CMATTRIB.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include string.inc
include time.inc
include io.inc
include zip.inc

	.data

externdef	IDD_UnzipCRCError:DWORD
externdef	IDD_DZZipAttributes:DWORD
externdef	scan_fblock:DWORD

format_zx	db '%08X',10
		db '%04X',10
		db '%04X',10
		db '%04X',10
		db '%04X',10
		db '%04X',10
		db '%08X',10
		db '%08X',10
		db '%08X',10
		db '%04X',10
		db '%04X',10,10,10
		db '%04X',10
		db '%08X',10
		db '%08X',10
		db '%08X',10
		db 0
format_zu	db '%16u',10
		db '%16u',10
		db '%16u',10
		db '%16u',10
		db 0

	.code

ID_RDONLY	equ 1*16
ID_HIDDEN	equ 2*16
ID_SYSTEM	equ 3*16
ID_ARCHIVE	equ 4*16
ID_CREATEDATE	equ 5*16
ID_CREATETIME	equ 6*16
ID_MODDATE	equ 7*16
ID_MODTIME	equ 8*16
ID_ACCESSDATE	equ 9*16
ID_ACCESSTIME	equ 10*16
ID_SET		equ 11*16
ID_CANCEL	equ 12*16


cmfileattrib PROC PRIVATE USES esi edi ebx

	local	fblk:	PTR S_FBLK,
		flag:	DWORD,
		fname:	PTR SBYTE,
		ft:	FILETIME

	mov	fname,eax
	mov	fblk,edx
	mov	flag,ecx
	mov	edi,scan_fblock

	.if	rsopen( IDD_DZFileAttributes )
		mov	ebx,eax

		mov	al,_O_FLAGB
		mov	edx,flag
		.if	dl & _A_RDONLY
			or [ebx+ID_RDONLY],al
		.endif
		.if	dl & _A_HIDDEN
			or [ebx+ID_HIDDEN],al
		.endif
		.if	dl & _A_SYSTEM
			or [ebx+ID_SYSTEM],al
		.endif
		.if	dl & _A_ARCH
			or [ebx+ID_ARCHIVE],al
		.endif

		.if	wfindfirst( fname, edi, 00FFh ) != -1
			wcloseff( eax )

			ftimetostr( [ebx].S_TOBJ.to_data[ID_ACCESSTIME],
				addr [edi].S_WFBLK.wf_timeaccess )
			fdatetostr( [ebx].S_TOBJ.to_data[ID_ACCESSDATE],
				addr [edi].S_WFBLK.wf_timeaccess )
			ftimetostr( [ebx].S_TOBJ.to_data[ID_CREATETIME],
				addr [edi].S_WFBLK.wf_timecreate )
			fdatetostr( [ebx].S_TOBJ.to_data[ID_CREATEDATE],
				addr [edi].S_WFBLK.wf_timecreate )
			ftimetostr( [ebx].S_TOBJ.to_data[ID_MODTIME],
				addr [edi].S_WFBLK.wf_time )
			fdatetostr( [ebx].S_TOBJ.to_data[ID_MODDATE],
				addr [edi].S_WFBLK.wf_time )

			dlinit( ebx )
			dlshow( ebx )

			mov	eax,[ebx].S_DOBJ.dl_rect
			add	eax,0213h
			mov	dl,ah
			scpath( eax, edx, 21, fname )

			.if	dlevent( ebx )

				mov	al,_O_FLAGB
				xor	edx,edx
				.if	[ebx+ID_RDONLY] & al
					or dl,_A_RDONLY
				.endif
				.if	[ebx+ID_SYSTEM] & al
					or dl,_A_SYSTEM
				.endif
				.if	[ebx+ID_ARCHIVE] & al
					or dl,_A_ARCH
				.endif
				.if	[ebx+ID_HIDDEN] & al
					or dl,_A_HIDDEN
				.endif

				mov	al,BYTE PTR flag
				and	al,_A_ARCH or _A_SYSTEM or _A_HIDDEN or _A_RDONLY
				.if	al != dl
					.if	BYTE PTR flag & _A_SUBDIR
						mov	flag,edx
						setfattr( fname, 0 )
						mov	edx,flag
					.endif
					setfattr( fname, edx )
				.endif

				.if	osopen( fname, _A_NORMAL, M_WRONLY, A_OPEN ) != -1
					mov	esi,eax

					GetTime MACRO t
						atodate( [ebx].S_TOBJ.to_data[ID_&t&DATE] )
						mov    edx,eax
						atotime( [ebx].S_TOBJ.to_data[ID_&t&TIME] )
						or     eax,edx
						ENDM

					GetTime MOD
					setftime( esi, eax )

					GetTime CREATE
					setftime_create( esi, eax )

					GetTime ACCESS
					setftime_access( esi, eax )

					_close( esi )
				.endif
			.endif
		.endif
		dlclose( ebx )
	.endif
	ret
cmfileattrib ENDP

cmzipattrib PROC USES esi edi ebx	; wsub, fblk

	mov	edi,edx			; EDX fblk
	mov	ecx,[edi].S_FBLK.fb_flag

	.if	!( cl & _A_SUBDIR )	; ECX attrib
		mov	ebx,ecx

		.if	wsopenarch( eax ) != -1
			mov	esi,eax
			;
			; CRC, compressed size and local offset stored at end of FBLK
			;
			strlen( addr [edi].S_FBLK.fb_name )
			add	eax,SIZE S_FBLK
			add	edi,eax
			mov	eax,[edi+4]
			mov	zip_central.cz_crc,eax
			mov	eax,[edi+8]
			mov	zip_central.cz_csize,eax
			mov	eax,[edi]
			mov	zip_central.cz_off_local,eax
			;
			; seek to and read local offset
			;
			_lseek( esi, eax, SEEK_SET )
			osread( esi, addr zip_local, SIZE S_LZIP )
			mov	edi,ebx ; FBLK.flag

			.if	eax == SIZE S_LZIP && \
				WORD PTR zip_local.lz_zipid == ZIPLOCALID && \
				WORD PTR zip_local.lz_pkzip == ZIPHEADERID

				osread( esi, entryname, zip_local.lz_fnsize )
				push	eax
				_close( esi )
				pop	eax

				.if	ax == zip_local.lz_fnsize

					add	eax,entryname
					mov	BYTE PTR [eax],0

					.if	rsopen( IDD_DZZipAttributes )

						mov	esi,eax
						mov	ebx,[eax+4]
						dlshow( eax )

						add	ebx,0104h
						mov	dl,bh
						scpath( ebx, edx, 54, entryname )

						and	edi,_A_FATTRIB
						add	dl,3
						add	bl,23
						scputf( ebx, edx, 0, 0, addr format_zx,
							DWORD PTR zip_local,
							zip_local.lz_version,	; version needed to extract
							zip_local.lz_flag,	; general purpose bit flag
							zip_local.lz_method,	; compression method
							zip_local.lz_time,	; last mod file time
							zip_local.lz_date,	; last mod file date
							zip_local.lz_crc,	; crc-32
							zip_local.lz_csize,	; compressed size
							zip_local.lz_fsize,	; uncompressed size
							zip_local.lz_fnsize,	; file name length
							zip_local.lz_extsize,	; extra field length
							edi,
							zip_central.cz_off_local,
							zip_central.cz_csize,
							zip_central.cz_crc )

						add	dl,7
						add	bl,8
						scputf( ebx, edx, 0, 0, addr format_zu,
							zip_local.lz_csize,	; compressed size
							zip_local.lz_fsize,	; uncompressed size
							zip_local.lz_fnsize,	; file name length
							zip_local.lz_extsize )	; extra field length

						add	dl,6
						add	bl,18
						.if	edi & _A_RDONLY
							scputc( ebx, edx, 1, 'x' )
						.endif
						inc	dl
						.if	edi & _A_HIDDEN
							scputc( ebx, edx, 1, 'x' )
						.endif
						inc	dl
						.if	edi & _A_SYSTEM
							scputc( ebx, edx, 1, 'x' )
						.endif
						inc	dl
						.if	edi & _A_ARCH
							scputc( ebx, edx, 1, 'x' )
						.endif
						dlevent( esi )
						dlclose( esi )
					.endif
				.else
					xor	eax,eax
				.endif
			.else
				_close( esi )
			.endif
		.endif
	.endif
	ret
cmzipattrib ENDP

cmattrib PROC
	mov	eax,cpanel

	.switch
	  .case !panel_curobj(eax)
	  .case ecx & _FB_ROOTDIR
		.endc
	  .case ecx & _FB_ARCHIVE
		mov eax,cpanel
		mov eax,[eax].S_PANEL.pn_wsub
		cmzipattrib()
		.endc
	.default
		cmfileattrib()
		.endc
	.endsw

	ret
cmattrib ENDP

	END

