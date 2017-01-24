; CONFIG.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include iost.inc
include tview.inc
include tinfo.inc
include io.inc
include stdio.inc
include string.inc
include alloc.inc
include confirm.inc
include cfini.inc
include stdlib.inc

topenh_atol	PROTO

PUBLIC	console
PUBLIC	searchstring
PUBLIC	replacestring
PUBLIC	findfilemask
PUBLIC	findfilepath
PUBLIC	comparemask
PUBLIC	filelist_bat
PUBLIC	format_lst
PUBLIC	mklist
PUBLIC	cp_selectmask

.data

__srcfile	dd 0
__srcpath	dd 0
__outfile	dd 0
__outpath	dd 0
entryname	dd 0
mainswitch	dd 0			; program switch
dzexitcode	dd 0			; return code (23 if exec)
numfblock	dd MAXFBLOCK		; number of file pointers allocated

;;;;;;;;;-------------------------------
	; Configuration file (DZCONFIG)
	;-------------------------------
config		label S_CONFIG
version		dd DOSZIP_VERSION
cflag		dd _C_DEFAULT
console		dd CON_DEFAULT
fsflag		dd IO_SEARCHSUB
tvflag		dd _TV_HEXOFFSET or _TV_USEMLINE
tiflags		dd _T_TEDEFAULT
titabsize	dd 8
ffflag		dd 2
compresslevel	dd 9
panelsize	dd 0	; Alt-Up/Down
fcb_indexa	dd 0
cel_indexa	dd 0
fcb_indexb	dd 0
cel_indexb	dd 0
path_a		S_WSUB	<_W_DEFAULT,0,MAXFBLOCK>
path_b		S_WSUB	<_W_DEFAULT or _W_PANELID,0,MAXFBLOCK>
opfilter	S_FILT	<-1,0,0,0,0,'*.*'>
at_foreground	db 00h,0Fh,0Fh,07h,08h,00h,00h,07h
		db 08h,00h,0Ah,0Bh,00h,0Fh,0Fh,0Fh
at_background	db 00h,10h,70h,70h,40h,30h,30h,70h
		db 30h,30h,00h,00h,10h,10h,07h,06h
mklist		S_MKLST <0,0,0,-1,0>


history		dd 0
searchstring	db 128 dup(0)
replacestring	db 128 dup(0)
cp_selectmask	db 128 dup(0)
filelist_bat	db "filelist.bat"
		db _MAX_PATH-12 dup(0)
format_lst	db "%f\n"
		db 256-4 dup(0)
findfilemask	db "*.*"
		db _MAX_PATH-3 dup(0)
findfilepath	db _MAX_PATH dup(0)
comparemask	db "*.*"
		db _MAX_PATH-3 dup(0)

cpanel		dd spanela
panela		dd spanela
panelb		dd spanelb

;-S_DZDATA-END--------------------------------------------------

_bufin		label BYTE
;;;;;;;;;;;;;;;;;-----------------------------------------------
		; _bufin 4096 byte. Includes a default .INI file
		;-----------------------------------------------
	db 128 dup(0)
default_ini label BYTE
incbin	<dzini.txt>
	db 0
if ($ - _bufin) le 1000h
	db 1000h - ($ - _bufin) dup('x')
endif

DZ_INIFILE	db DOSZIP_INIFILE,0 ; config file

		ALIGN	4

config_table_x	dd config.c_cflag
		dd config.c_console
		dd config.c_fsflag
		dd config.c_tvflag
		dd config.c_teflag
		dd config.c_titabsize
		dd config.c_ffflag
		dd config.c_comprlevel
		dd config.c_panelsize
		dd config.c_fcb_indexa
		dd config.c_cel_indexa
		dd config.c_fcb_indexb
		dd config.c_cel_indexb
		dd config.c_apath
		dd config.c_bpath
		dd config.c_color
		dd config.c_color[0x04]
		dd config.c_color[0x08]
		dd config.c_color[0x0C]
		dd config.c_color[0x10]
		dd config.c_color[0x14]
		dd config.c_color[0x18]
		dd config.c_color[0x1C]
		dd config.c_list.mkl_flag
		dd config.c_list.mkl_offspath
		dd config.c_list.mkl_offset
		dd config.c_list.mkl_handle
		dd config.c_list.mkl_count
		dd config.c_filter.of_flag
		dd config.c_filter.of_max_date
		dd config.c_filter.of_min_date
		dd config.c_filter.of_max_size
		dd config.c_filter.of_min_size
		dd 0

config_table_p	dd config.c_apath.ws_mask
		dd config.c_apath.ws_file
		dd config.c_apath.ws_arch
		dd config.c_apath.ws_path
		dd config.c_bpath.ws_mask
		dd config.c_bpath.ws_file
		dd config.c_bpath.ws_arch
		dd config.c_bpath.ws_path
		dd 0

config_table_s	dd config.c_filter.of_include
		dd config.c_filter.of_exclude
		dd searchstring
		dd replacestring
		dd cp_selectmask
		dd filelist_bat
		dd format_lst
		dd findfilemask
		dd findfilepath
		dd comparemask
		dd default_arc
		dd default_zip
		dd 0

	.code

config_create PROC USES esi edi

	xor	edi,edi
	mov	config.c_cel_indexa,5

	.if	osopen( __srcfile, 0, M_WRONLY, A_CREATETRUNC ) != -1

		mov	esi,eax
		or	_osfile[eax],FH_TEXT
		_write( esi, addr default_ini, strlen( addr default_ini ) )
		mov	edi,eax
		_close( esi )
	.endif

	mov	eax,edi
	ret

config_create ENDP

config_read PROC USES esi edi ebx

  local xoff, boff, yoff, loff, entry

ifdef __W95__
	push	console
endif
	mov	history,malloc( SIZE S_HISTORY )
	.if	eax

		mov	edi,eax
		xor	eax,eax
		mov	ecx,SIZE S_HISTORY
		rep	stosb
	.endif

	.if	CFGetSection( ".config" )

		mov	ebx,eax

		.if	CFGetEntryID( ebx, 0 )

			.if	xtol(eax) <= DOSZIP_VERSION && eax >= DOSZIP_MINVERS

				mov	edi,1
				lea	esi,config_table_x
				.repeat
					.if	CFGetEntryID( ebx, edi )

						xtol  ( eax )
						mov	ecx,[esi]
						mov	[ecx],eax
					.endif
					add	edi,1
					add	esi,4
					mov	eax,[esi]
				.until	!eax

				lea	esi,config_table_p
				mov	eax,[esi]
				.while	eax
					.if	CFGetEntryID( ebx, edi )

						mov	ecx,[esi]
						mov	ecx,[ecx]
						strcpy( ecx, eax )
					.endif
					add	edi,1
					add	esi,4
					mov	eax,[esi]
				.endw

				lea	esi,config_table_s
				mov	eax,[esi]
				.while	eax
					.if	CFGetEntryID( ebx, edi )

						mov	ecx,[esi]
						strcpy( ecx, eax )
					.endif
					add	edi,1
					add	esi,4
					mov	eax,[esi]
				.endw
			.endif
		.endif
	.endif

	.if	CFGetSection( ".directory" )

		mov	edi,history
		.if	edi

			mov	entry,0
			mov	ebx,eax

			.while	CFReadFileName( ebx, addr entry, 2 )

				mov	[edi].S_DIRECTORY.path,eax
				mov	eax,loff
				mov	[edi].S_DIRECTORY.flag,eax
				mov	eax,yoff
				mov	[edi].S_DIRECTORY.fcb_index,eax
				mov	eax,boff
				mov	[edi].S_DIRECTORY.cel_index,eax
				add	edi,SIZE S_DIRECTORY
			.endw
		.endif
	.endif

	.if	CFGetSection( ".doskey" )

		mov	eax,history
		.if	eax

			lea	edi,[eax].S_HISTORY.h_doskey
			mov	esi,MAXDOSKEYS
			xor	ebx,ebx

			mov	entry,0
			mov	ebx,eax

			.while	CFGetEntryID( ebx, entry )

				salloc( eax )
				stosd
				inc	entry
				dec	esi
				.break .if ZERO?
			.endw
		.endif
	.endif

toend:
ifdef __W95__
	pop	eax
	and	eax,CON_WIN95
	or	console,eax
endif
	ret
config_read ENDP

config_save PROC USES esi edi ebx

  local boff, xoff, loff

	mov	eax,spanela.pn_fcb_index
	mov	config.c_fcb_indexa,eax
	mov	eax,spanela.pn_cel_index
	mov	config.c_cel_indexa,eax
	mov	eax,spanelb.pn_fcb_index
	mov	config.c_fcb_indexb,eax
	mov	eax,spanelb.pn_cel_index
	mov	config.c_cel_indexb,eax

	and	config.c_apath.ws_flag,not _W_VISIBLE
	.if	prect_a.xl_flag & _D_DOPEN

		or config.c_apath.ws_flag,_W_VISIBLE
	.endif

	and	config.c_bpath.ws_flag,not _W_VISIBLE
	.if	prect_b.xl_flag & _D_DOPEN

		or config.c_bpath.ws_flag,_W_VISIBLE
	.endif

	.if	CFAddSection( ".config" )

		mov	ebx,eax
		xor	edi,edi
		CFAddEntryX( ebx, "%d=%X", edi, DOSZIP_VERSION )

		inc	edi
		lea	esi,config_table_x
		.while	1
			lodsd
			.break .if !eax
			mov	eax,[eax]
			CFAddEntryX( ebx, "%d=%X", edi, eax )
			add	edi,1
		.endw
		lea	esi,config_table_p
		.while	1
			lodsd
			.break .if !eax
			mov	eax,[eax]
			CFAddEntryX( ebx, "%d=%s", edi, eax )
			add	edi,1
		.endw
		lea	esi,config_table_s
		.while	1
			lodsd
			.break .if !eax
			CFAddEntryX( ebx, "%d=%s", edi, eax )
			add	edi,1
		.endw
	.endif

	.if	CFAddSection( ".directory" )

		mov	ebx,eax
		mov	edi,history
		.if	edi

			xor	esi,esi
			.while	[edi].S_DIRECTORY.path

				CFAddEntryX( ebx, "%d=%X,%X,%X,%s", esi,
					[edi].S_DIRECTORY.flag,
					[edi].S_DIRECTORY.fcb_index,
					[edi].S_DIRECTORY.cel_index,
					[edi].S_DIRECTORY.path )

				add	edi,SIZE S_DIRECTORY
				inc	esi
				.break .if esi == MAXHISTORY
			.endw
		.endif
	.endif

	.if	CFAddSection( ".doskey" )

		mov	ebx,eax
		mov	eax,history
		.if	eax

			lea	esi,[eax].S_HISTORY.h_doskey
			xor	edi,edi

			.while	edi < MAXDOSKEYS

				lodsd

				.break .if !eax
				.break .if BYTE PTR [eax] == 0

				CFAddEntryX(ebx, "%d=%s", edi, eax)

				inc	edi
			.endw
		.endif
	.endif

	tsaveh( __CFBase, ".openfiles" )

	CFWrite( strfcat( __srcfile, _pgmpath, addr DZ_INIFILE ) )

	mov	eax,1
	ret
config_save ENDP

setconfirmflag PROC

	mov	edx,CFSELECTED
	mov	eax,config.c_cflag

	.if	eax & _C_CONFDELETE

		or edx,CFDELETEALL
	.endif
	.if	eax & _C_CONFDELSUB

		or edx,CFDIRECTORY
	.endif
	.if	eax & _C_CONFSYSTEM

		or edx,CFSYSTEM
	.endif
	.if	eax & _C_CONFRDONLY

		or edx,CFREADONY
	.endif
	mov	confirmflag,edx
	ret

setconfirmflag ENDP

	END
