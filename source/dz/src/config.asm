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
include ini.inc
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
incbin	<dzini.bin>
	db 0
if ($ - _bufin) le 1000h
	db 1000h - ($ - _bufin) dup('x')
endif

DZ_INIFILE	db DOSZIP_INIFILE,0 ; config file
DZ_CFGFILE	db DOSZIP_CFGFILE,0 ; history file

cp_Config	db "config",0
cp_Doskey	db "Doskey",0
cp_Directory	db "Directory",0
cp_OpenFiles	db ".",0
cp_format_s	db "[%s]",10,0
cp_format_x	db "%d=%X",10,0
cp_format_e	db "%d=%s",10,0

		ALIGN	4

cid_table_x	dd  1, offset config.c_cflag
		dd  2, offset config.c_console
		dd  3, offset config.c_fsflag
		dd  4, offset config.c_tvflag
		dd  5, offset config.c_teflag
		dd  6, offset config.c_titabsize
		dd  7, offset config.c_ffflag
		dd  8, offset config.c_comprlevel
		dd  9, offset config.c_panelsize
		dd 10, offset config.c_fcb_indexa
		dd 11, offset config.c_cel_indexa
		dd 12, offset config.c_fcb_indexb
		dd 13, offset config.c_cel_indexb
		dd 14, offset config.c_apath
		dd 15, offset config.c_bpath
		dd 16, offset at_foreground
		dd 17, offset at_foreground[4]
		dd 18, offset at_foreground[8]
		dd 19, offset at_foreground[12]
		dd 20, offset at_background
		dd 21, offset at_background[4]
		dd 22, offset at_background[8]
		dd 23, offset at_background[12]
		dd 24, offset config.c_list.mkl_flag
		dd 25, offset config.c_list.mkl_offspath
		dd 26, offset config.c_list.mkl_offset
		dd 27, offset config.c_list.mkl_handle
		dd 28, offset config.c_list.mkl_count
		dd 29, offset config.c_filter.of_flag
		dd 30, offset config.c_filter.of_max_date
		dd 31, offset config.c_filter.of_min_date
		dd 32, offset config.c_filter.of_max_size
		dd 33, offset config.c_filter.of_min_size
		dd 0

cid_table_p	dd 40, config.c_apath.ws_mask
		dd 41, config.c_apath.ws_file
		dd 42, config.c_apath.ws_arch
		dd 43, config.c_apath.ws_path
		dd 44, config.c_bpath.ws_mask
		dd 45, config.c_bpath.ws_file
		dd 46, config.c_bpath.ws_arch
		dd 47, config.c_bpath.ws_path
		dd 0

cid_table_s	dd 50, offset config.c_filter.of_include
		dd 51, offset config.c_filter.of_exclude
		dd 52, offset searchstring
		dd 53, offset replacestring
		dd 54, offset cp_selectmask
		dd 55, offset filelist_bat
		dd 56, offset format_lst
		dd 57, offset findfilemask
		dd 58, offset findfilepath
		dd 59, offset comparemask
		dd 60, offset default_arc
		dd 61, offset default_zip
		dd 0

	.code

config_create PROC USES esi
	mov	config.c_cel_indexa,5
	.if	osopen( __srcfile, 0, M_WRONLY, A_CREATETRUNC ) != -1
		mov	esi,eax
		or	_osfile[eax],FH_TEXT
		_write( esi, addr default_ini, strlen( addr default_ini ) )
		_close( esi )
	.endif
	ret
config_create ENDP

historyremove PROC
	setfattr( strfcat( __srcfile, _pgmpath, addr DZ_CFGFILE ), 0 )
	remove( __srcfile )
	ret
historyremove ENDP

config_read PROC USES esi edi ebx

  local historyfile[_MAX_PATH]:BYTE, entry, boff, xoff, loff, cfile

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
	mov	eax,cinifile
	mov	cfile,eax

	.if	iniopen( strfcat( addr historyfile, _pgmpath, addr DZ_CFGFILE ) )
		.if	inientryid( addr cp_Config, 0 )
			xtol  ( eax )
			.if	eax <= DOSZIP_VERSION && eax >= DOSZIP_MINVERS
				lea	esi,cid_table_x
				.repeat
					lodsd
					.break .if !eax
					inientryid( addr cp_Config, eax )
					mov	ecx,eax
					lodsd
					mov	ebx,eax
					.continue .if ZERO?
					xtol( ecx )
					mov	[ebx],eax
				.until	0
				lea	esi,cid_table_p
				.repeat
					lodsd
					.break .if !eax
					inientryid( addr cp_Config, eax )
					mov	ecx,eax
					lodsd
					.continue .if ZERO?
					mov	eax,[eax]
					strcpy( eax, ecx )
				.until	0
				lea	esi,cid_table_s
				.repeat
					lodsd
					.break .if !eax
					inientryid( addr cp_Config, eax )
					mov	ecx,eax
					lodsd
					.continue .if ZERO?
					strcpy( eax, ecx )
				.until	0

				mov	edi,history
				.if	edi
					mov	entry,0
					.while	inientryid( addr cp_Directory, entry )
						mov	esi,eax
						xtol( esi )
						mov	loff,eax
						topenh_atol()
						.break .if ZERO?
						mov	ebx,edx
						topenh_atol()
						.break .if ZERO?
						mov	boff,edx
						strchr( esi, ',' )
						.break .if ZERO?
						inc	eax
						mov	esi,eax
						.if	filexist( esi ) == 2
							salloc( esi )
							mov	[edi].S_DIRECTORY.path,eax
							mov	eax,loff
							mov	[edi].S_DIRECTORY.flag,eax
							mov	[edi].S_DIRECTORY.fcb_index,ebx
							mov	eax,boff
							mov	[edi].S_DIRECTORY.cel_index,eax
						.endif
						add	edi,SIZE S_DIRECTORY
						inc	entry
					.endw

					mov	eax,history
					lea	edi,[eax].S_HISTORY.h_doskey
					mov	esi,MAXDOSKEYS
					xor	ebx,ebx

					.while	inientryid( addr cp_Doskey, ebx )

						salloc( eax )
						stosd
						inc	ebx
						dec	esi
						.break .if ZERO?
					.endw
				.endif

				iniclose()
				mov	eax,cfile
				mov	cinifile,eax
				jmp	toend
			.endif
		.endif
		iniclose()
		and	cflag,not _C_DELHISTORY
	.endif
toend:
ifdef __W95__
	pop	eax
	and	eax,CON_WIN95
	or	console,eax
endif
	mov	eax,cfile
	mov	cinifile,eax
	ret
config_read ENDP

config_save PROC USES esi edi ebx

  local section[2]:BYTE, boff, xoff, loff

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
	strfcat( __srcfile, _pgmpath, addr DZ_CFGFILE )
	.if	osopen( eax, _A_NORMAL, M_WRONLY, A_CREATETRUNC ) == -1
		xor eax,eax
	.else
		mov STDO.ios_file,eax
		.if	!ioinit( addr STDO, OO_MEM64K )
			_close( STDO.ios_file )
			xor eax,eax
		.else
			oprintf( addr cp_format_s, addr cp_Config )
			oprintf( addr cp_format_x, 0, DOSZIP_VERSION )
			lea	esi,cid_table_x
			.repeat
				lodsd
				.break .if !eax
				mov	ecx,eax
				lodsd
				mov	eax,[eax]
				oprintf( addr cp_format_x, ecx, eax )
			.until	0
			lea	esi,cid_table_p
			.repeat
				lodsd
				.break .if !eax
				mov	ecx,eax
				lodsd
				mov	eax,[eax]
				oprintf( addr cp_format_e, ecx, eax )
			.until	0
			lea	esi,cid_table_s
			.repeat
				lodsd
				.break .if !eax
				mov	ecx,eax
				lodsd
				oprintf( addr cp_format_e, ecx, eax )
			.until	0

			mov	edi,history
			.if	edi
				oprintf( addr cp_format_s, addr cp_Directory )
				xor esi,esi
				.while	[edi].S_DIRECTORY.path
					oprintf( "%d=%X,%d,%d,%s\n",
						esi,
						[edi].S_DIRECTORY.flag,
						[edi].S_DIRECTORY.fcb_index,
						[edi].S_DIRECTORY.cel_index,
						[edi].S_DIRECTORY.path )
					add	edi,SIZE S_DIRECTORY
					inc	esi
					.break .if esi >= MAXHISTORY
				.endw
				oprintf( addr cp_format_s, addr cp_Doskey )
				mov	eax,history
				lea	esi,[eax].S_HISTORY.h_doskey
				xor	edi,edi
				.repeat
					lodsd
					.break .if !eax
					.break .if BYTE PTR [eax] == 0
					oprintf( addr cp_format_e, edi, eax )
					inc	edi
					.break .if edi >= MAXDOSKEYS
				.until	0
			.endif

			ioflush( addr STDO )
			iofree( addr STDO )
			tsaveh( STDO.ios_file )
			_close( STDO.ios_file )
			mov	eax,1
		.endif
	.endif
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
