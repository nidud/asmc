; CMCOMPSUB.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include alloc.inc
include io.inc
include iost.inc
include progress.inc
include string.inc
include syserrls.inc
include time.inc
include cfini.inc
include stdlib.inc

ifdef __WIN95__
MAXHIT		equ 100000
else
MAXHIT		equ 500000
endif

externdef	IDD_DZCompareDirectories:DWORD
externdef	IDD_DZRecursiveCompare:DWORD
externdef	cp_emaxfb:BYTE
externdef	cp_formatID:BYTE
;
; from cmsearch.asm
;
externdef	ff_basedir:DWORD
externdef	DLG_FindFile:DWORD

ff_close	PROTO
ff_close_dlg	PROTO
ff_rsevent	PROTO :DWORD, :DWORD
ff_getcurobj	PROTO
ff_getcurfile	PROTO
ff_putcelid	PROTO :DWORD
ff_searchpath	PROTO :DWORD
ff_event_xcell	PROTO
ff_event_edit	PROTO
ff_event_view	PROTO
ff_event_exit	PROTO
ff_event_filter PROTO
ff_deleteobj	PROTO
ff_update_cellid PROTO

ID_FILE		equ 13
ID_GOTO		equ 22

OF_MASK		equ 14*16
OF_SOURCE	equ 15*16
OF_TARGET	equ 16*16
OF_SUBD		equ 17*16
OF_EQUAL	equ 18*16
OF_DIFFER	equ 19*16
OF_FIND		equ 20*16
OF_FILT		equ 21*16
OF_SAVE		equ 22*16
OF_GOTO		equ 23*16
OF_QUIT		equ 24*16
OF_MSUP		equ 25*16
OF_MSDN		equ 26*16
OF_GCMD		equ OF_MSUP

	.data

GCMD_search	dd KEY_F2,	event_mklist
		dd KEY_F3,	ff_event_view
		dd KEY_F4,	ff_event_edit
		dd KEY_F5,	ff_event_filter
		dd KEY_F6,	event_path
		dd KEY_F7,	event_find
		dd KEY_F8,	event_delete
		dd KEY_F9,	cmfilter_load
		dd KEY_F10,	event_advanced
		dd KEY_DEL,	event_delete
		dd KEY_ALTX,	ff_event_exit
		dd KEY_CTRLW,	event_flip
		dd 0
ff_table	dd 0
ff_count	dd 0
ff_recursive	dd 0
source		dd 0
target		dd 0

_COMP_NAME	equ 0x01 ; Compare File names
_COMP_CREATE	equ 0x02 ; Compare File creation time
_COMP_ACCESS	equ 0x04 ; Compare Last access time
_COMP_WRITE	equ 0x08 ; Compare Last modification time
_COMP_DATA	equ 0x10 ; Compare File content
_COMP_ATTRIB	equ 0x20 ; Compare File Attributes
_COMP_EQUAL	equ 0x40 ; Find equal/differ
_COMP_SUBDIR	equ 0x80 ; Scan subdirectories

flags		dd _COMP_NAME or _COMP_WRITE or _COMP_SUBDIR

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	.code

	OPTION PROC: PRIVATE

ff_alloc PROC USES esi edi ebx path, fb
	strlen( path )
	add	eax,BLOCKSIZE
	mov	edi,eax
	.if	malloc( eax )
		mov	esi,eax
		add	eax,S_FBLK.fb_name
		strcpy( eax, path )
		mov	ebx,tdllist
		sub	edx,edx
		mov	eax,[ebx].S_LOBJ.ll_count
		progress_update( edx::eax )
		mov	ecx,eax
		mov	eax,[ebx].S_LOBJ.ll_count
		inc	[ebx].S_LOBJ.ll_count
		mov	edx,[ebx].S_LOBJ.ll_count
		.if	edx >= ID_FILE
			mov edx,ID_FILE
		.endif
		mov	[ebx].S_LOBJ.ll_numcel,edx
		mov	ebx,[ebx].S_LOBJ.ll_list
		mov	[ebx+eax*4],esi
		mov	edi,fb
		xchg	edi,esi
		mov	eax,ecx
		mov	ecx,4
		rep	movsd
		mov	DWORD PTR [edi-8],0
		dec	eax
	.endif
	test	eax,eax
	ret
ff_alloc ENDP

CompareFileData proc uses esi edi ebx A:LPSTR, B:LPSTR

local	h1,h2,b1,b2

	mov	b1,alloca(0x8000)
	add	eax,0x4000
	mov	b2,eax

	.repeat
		mov	h1,osopen(A, 0, M_RDONLY, A_OPEN)
		.break	.if eax == -1
		mov	h2,osopen(B, 0, M_RDONLY, A_OPEN)
		.if	eax == -1

			_close(h1)
			mov eax,-1
			.break
		.endif

		.while	osread(h1, b1, 0x4000)

			mov	ebx,eax
			.if	osread(h2, b2, 0x4000) != ebx

				mov eax,-1
				.break
			.endif

			mov	eax,-1
			mov	ecx,ebx
			mov	esi,b1
			mov	edi,b2
			repz	cmpsb

			.break .ifnz
		.endw

		mov ebx,eax
		_close(h1)
		_close(h2)
		mov eax,ebx
	.until	1
	ret

CompareFileData endp

ff_fileblock PROC USES esi edi ebx directory, wfblk

local	path[_MAX_PATH*2]:SBYTE,
	result:DWORD,
	found[4]:BYTE

	xor	eax,eax
	mov	result,eax

	.repeat

		.break	.if eax == ff_count

		mov	found,al
		mov	edi,wfblk
		mov	edx,MAXHIT
		mov	result,edx
		mov	ebx,tdllist

		.if	[ebx].S_LOBJ.ll_count >= edx

			stdmsg( addr cp_warning, addr cp_emaxfb, edx, edx )
			mov	result,2
			.break
		.endif

		mov	result,eax
		.break	.if !filter_wblk(edi)

		add	edi,S_WFBLK.wf_name
		strfcat(addr path, directory, edi)
		.break	.if !cmpwarg(edi, fp_maskp)

		mov	result,test_userabort()
		.break .ifnz

		.for	ebx = wfblk, edi = ff_count, esi = ff_table : edi : edi--, esi += 4

			mov	edx,[esi]
			mov	eax,DWORD PTR [edx].S_FBLK.fb_size
			.continue .if eax != DWORD PTR [ebx].S_WFBLK.wf_size
			mov	eax,DWORD PTR [edx].S_FBLK.fb_size[4]
			.continue .if eax != DWORD PTR [ebx].S_WFBLK.wf_size[4]

			.if	flags & _COMP_ATTRIB	; Compare File Attributes

				mov	eax,[edx].S_FBLK.fb_flag
				.continue .if eax != [ebx].S_WFBLK.wf_attrib
			.endif

			.if	flags & _COMP_WRITE	; Compare Last modification time

				__FTToTime( addr [ebx].S_WFBLK.wf_time )
				mov	edx,[esi]
				.continue .if eax != [edx].S_FBLK.fb_time
			.endif

			.if	flags & _COMP_CREATE	; Compare File creation time

				.if	osopen( addr [edx].S_FBLK.fb_name, 0, M_RDONLY, A_OPEN ) != -1

					push	eax
					getftime_create(eax)
					pop	ecx
					push	eax
					_close( ecx )
					__FTToTime(addr [ebx].S_WFBLK.wf_timecreate)
					pop	ecx
					.continue .if eax != ecx
				.endif
				mov	edx,[esi]
			.endif

			.if	flags & _COMP_ACCESS	; Compare Last access time

				.if	osopen( addr [edx].S_FBLK.fb_name, 0, M_RDONLY, A_OPEN ) != -1

					push	eax
					getftime_access(eax)
					pop	ecx
					push	eax
					_close( ecx )
					__FTToTime( addr [ebx].S_WFBLK.wf_timeaccess )
					pop	ecx
					.continue .if eax != ecx
				.endif
				mov	edx,[esi]
			.endif

			.if	flags & _COMP_NAME	; Compare File names

				mov	ecx,strfn( addr [edx].S_FBLK.fb_name )
				.continue .if _stricmp( addr [ebx].S_WFBLK.wf_name, ecx )
			.endif

			.if	flags & _COMP_DATA	; Compare File content

				.continue .if CompareFileData(addr [edx].S_FBLK.fb_name, addr path)
				mov	edx,[esi]
			.endif

			mov	found,1
			.break
		.endf

		mov	eax,DLG_FindFile
		movzx	eax,[eax].S_TOBJ.to_flag[OF_EQUAL]
		and	eax,_O_RADIO

		.break	.if eax && !found
		.break	.if !eax && found

		.if	!ff_alloc(addr path, edx)

			clear_table()
			ermsg(0, addr CP_ENOMEM)
			mov result,-1
		.endif

	.until	1
	mov	eax,result
	ret

ff_fileblock ENDP

clear_table PROC
	mov	eax,ff_count
	mov	edx,ff_table
	.while	eax
		free ( [edx] )
		add	edx,4
		dec	eax
	.endw
	mov	ff_count,eax
	ret
clear_table ENDP

clear_list PROC
	mov	eax,tdllist
	mov	edx,[eax].S_LOBJ.ll_list
	mov	eax,[eax].S_LOBJ.ll_count
	.while	eax
		free ( [edx] )
		add	edx,4
		dec	eax
	.endw
	mov	edx,tdllist
	mov	[edx].S_LOBJ.ll_celoff,eax
	mov	[edx].S_LOBJ.ll_index,eax
	mov	[edx].S_LOBJ.ll_numcel,eax
	mov	[edx].S_LOBJ.ll_count,eax
	ret
clear_list ENDP

ff_addfileblock PROC USES esi edi ebx directory, wfblk

	local	path[512]:BYTE
	mov	edi,wfblk

	.if	filter_wblk( edi )
		strfcat( addr path, directory, addr [edi].S_WFBLK.wf_name )
		mov	eax,ff_count
		.if	eax < MAXHIT
			__FTToTime( addr [edi].S_WFBLK.wf_time )
			mov	ecx,eax
			.if	fballoc( addr path, ecx, [edi].S_WFBLK.wf_size, [edi].S_WFBLK.wf_attrib )
				mov	ecx,ff_count
				inc	ff_count
				shl	ecx,2
				add	ecx,ff_table
				mov	[ecx],eax
				xor	ecx,ecx
				mov	eax,ff_count
				progress_update( ecx::eax )
			.else
				call	clear_table
				ermsg( 0, addr CP_ENOMEM )
				mov	eax,1
			.endif
		.else
			stdmsg( addr cp_warning, addr cp_emaxfb, eax, eax )
			mov	eax,2
		.endif
	.endif
	ret
ff_addfileblock ENDP

clear_slash PROC string
	mov	eax,string
	mov	ecx,[eax+1]
	and	ecx,00FFFFFFh
	.if	ecx == 00005C3Ah ; ":\"
		mov BYTE PTR [eax+2],0
	.endif
	ret
clear_slash ENDP

ff_directory PROC directory
	mov	eax,1
	.if	ff_recursive != eax
		mov	edx,source
		strlen( edx )
		push	eax
		strlen( directory )
		pop	ecx
		.if	eax >= ecx
			mov eax,ecx
		.endif
		.if	!_strnicmp( directory, edx, eax )
			rsmodal( IDD_DZRecursiveCompare )
		.endif
	.endif
	.if	eax
		mov	ff_recursive,1
		.if	!progress_set( 0, directory, 0 )
			scan_files( directory )
		.endif
	.endif
	ret
ff_directory ENDP

event_find PROC USES esi edi ebx
  local cursor:S_CURSOR
	CursorGet( addr cursor )
	call	CursorOff
	call	clear_table
	call	clear_list
	mov	ebx,DLG_FindFile
	dlinit( ebx )
	clear_slash( source )
	mov	esi,eax
	clear_slash( target )
	mov	fp_directory,ff_directory
	mov	fp_fileblock,ff_addfileblock
	mov	ff_recursive,1
	progress_open( "Read Source", 0 )
	progress_set( esi, 0, MAXHIT )
	mov	fp_maskp,offset cp_stdmask
	mov	al,[ebx+OF_SUBD]
	.if	al & _O_FLAGB
		scan_directory( 1, esi )
	.else
		ff_directory( esi )
	.endif
	call	progress_close
	xor	eax,eax
	mov	ff_recursive,eax
	mov	fp_fileblock,ff_fileblock
	.if	ff_count != eax && !( [ebx].S_TOBJ.to_flag[OF_GOTO] & _O_STATE )
		mov	ax,[ebx+4]
		add	ax,0F03h
		mov	dl,ah
		scputw( eax, edx, 15, 00C4h )
		progress_open( "Compare", 0 )
		mov	eax,target
		push	eax
		progress_set( eax, 0, MAXHIT+2 )
		call	ff_searchpath
		call	progress_close
		call	clear_table
		mov	edx,tdllist
		mov	eax,[edx].S_LOBJ.ll_count
		.if	eax >= ID_FILE
			mov eax,ID_FILE
		.endif
		mov	[edx].S_LOBJ.ll_numcel,eax
		call	update_cellid
	.endif
	CursorSet( addr cursor )
	ret
event_find ENDP

event_help PROC
	mov	eax,HELPID_14
	call	view_readme
	ret
event_help ENDP

event_mklist PROC USES esi edi
	mov	esi,tdllist
	xor	eax,eax
	.if	[esi].S_LOBJ.ll_count != eax
		.if	mklistidd()
			xor	edi,edi
			.while	edi < [esi].S_LOBJ.ll_count
				mov	edx,[esi].S_LOBJ.ll_list
				mov	edx,[edx+edi*4]
				strfn ( addr [edx].S_FBLK.fb_name )
				lea	ecx,[edx].S_FBLK.fb_name
				sub	eax,ecx
				mov	mklist.mkl_offspath,eax
				mov	mklist.mkl_offset,0
				lea	eax,[edx].S_FBLK.fb_name
				call	mklistadd
				inc	edi
			.endw
			_close( mklist.mkl_handle )
			mov	eax,_C_NORMAL
		.endif
	.endif
	ret
event_mklist ENDP

event_list proc USES esi edi
	dlinit( DLG_FindFile )
	mov	eax,DLG_FindFile
	movzx	esi,[eax].S_DOBJ.dl_rect.rc_x
	add	esi,4
	movzx	edi,[eax].S_DOBJ.dl_rect.rc_y
	add	edi,2
	mov	eax,tdllist
	mov	edx,[eax].S_LOBJ.ll_index
	shl	edx,2
	add	edx,[eax].S_LOBJ.ll_list
	mov	ecx,[eax].S_LOBJ.ll_numcel
	.while	ecx
		mov	eax,[edx]
		add	eax,S_FBLK.fb_name
		scpath( esi, edi, 68, eax )
		inc	edi
		add	edx,4
		dec	ecx
	.endw
	mov	eax,1
	ret
event_list ENDP

update_cellid PROC
	ff_putcelid( addr cp_formatID )
	call	event_list
	jmp	ff_update_cellid
update_cellid ENDP

event_delete PROC
	call	ff_deleteobj
	call	update_cellid
	mov	eax,_C_NORMAL
	ret
event_delete ENDP

event_path proc
	mov	eax,panela ; Source - Panel-A
	mov	ecx,[eax].S_PANEL.pn_wsub
	strcpy(source, [ecx].S_WSUB.ws_path)
	mov	eax,panelb ; Target - Panel-B
	mov	ecx,[eax].S_PANEL.pn_wsub
	strcpy(target, [ecx].S_WSUB.ws_path)
	mov	eax,DLG_FindFile
	.if	eax
		dlinit( eax )
	.endif
	mov	eax,_C_NORMAL
	ret
event_path endp

event_advanced proc uses esi edi

	.if rsopen( IDD_CompareOptions )

		mov esi,eax
		tosetbitflag([esi].S_DOBJ.dl_object, 6, _O_FLAGB, flags)
		dlinit(esi)
		rsevent(IDD_CompareOptions, esi)
		mov edi,eax
		togetbitflag([esi].S_DOBJ.dl_object, 6, _O_FLAGB)
		xchg eax,esi
		dlclose(eax)

		.if	edi

			and flags,11000000B
			or  flags,esi
		.endif
	.endif
	mov	eax,_C_NORMAL
	ret

event_advanced endp

event_flip proc

	PushEvent(KEY_ENTER)
	PushEvent(KEY_F6)
	PushEvent(KEY_SHIFTF5)
	PushEvent(KEY_CTRLW)
	mov	eax,_C_ESCAPE
	ret

event_flip endp

cmcompsub PROC PUBLIC USES esi edi ebx

local	cursor:S_CURSOR,
	ll:S_LOBJ,
	old_thelp:DWORD,
	fmask[_MAX_PATH]:SBYTE,
	tpath[_MAX_PATH]:SBYTE,
	spath[_MAX_PATH]:SBYTE

	lea	eax,tpath
	mov	target,eax
	lea	eax,spath
	mov	source,eax
	mov	DLG_FindFile,0
	strcpy(addr fmask, addr cp_stdmask)
	event_path()

	.if CFGetSection(".compsubdir")
		mov ebx,eax
		.if CFGetEntryID(ebx, 0)
			mov flags,xtol(eax)
		.endif
		.if CFGetEntryID(ebx, 1)
			strcpy(addr fmask, eax)
		.endif
		.if CFGetEntryID(ebx, 2)
			strcpy(source, eax)
		.endif
		.if CFGetEntryID(ebx, 3)
			strcpy(target, eax)
		.endif
	.endif

	mov	ff_count,0
	mov	eax,thelp
	mov	old_thelp,eax
	mov	thelp,event_help
	call	clrcmdl
	CursorGet(addr cursor)
	lea	edx,ll
	mov	tdllist,edx
	mov	edi,edx
	mov	ecx,SIZE S_LOBJ
	xor	eax,eax
	rep	stosb
	mov	[edx].S_LOBJ.ll_dcount,ID_FILE
	mov	[edx].S_LOBJ.ll_proc,event_list

	.if	malloc((MAXHIT * 8) + 4)

		mov	ll.ll_list,eax
		add	eax,(MAXHIT*4)+4
		mov	ff_table,eax

		.if	rsopen(IDD_DZCompareDirectories)

			mov	DLG_FindFile,eax
			mov	ebx,eax
			mov	[ebx].S_TOBJ.to_data[OF_GCMD],offset GCMD_search
			mov	[ebx].S_TOBJ.to_count[OF_MASK],256/16
			mov	[ebx].S_TOBJ.to_count[OF_SOURCE],256/16
			mov	[ebx].S_TOBJ.to_count[OF_TARGET],256/16
			lea	eax,fmask
			mov	[ebx].S_TOBJ.to_data[OF_MASK],eax
			mov	eax,source
			mov	[ebx].S_TOBJ.to_data[OF_SOURCE],eax
			mov	eax,target
			mov	[ebx].S_TOBJ.to_data[OF_TARGET],eax
			mov	[ebx].S_TOBJ.to_proc[OF_FIND],event_find
			mov	[ebx].S_TOBJ.to_proc[OF_FILT],ff_event_filter
			mov	[ebx].S_TOBJ.to_proc[OF_SAVE],event_mklist

			mov	ecx,flags
			mov	al,_O_RADIO
			.if	cl & _COMP_EQUAL
				or [ebx+OF_EQUAL],al
			.else
				or [ebx+OF_DIFFER],al
			.endif

			and	fsflag,not IO_SEARCHSUB
			.if	cl & _COMP_SUBDIR

				or BYTE PTR [ebx+OF_SUBD],_O_FLAGB
				or fsflag,IO_SEARCHSUB
			.endif

			lea	edx,[ebx].S_TOBJ.to_proc[SIZE S_TOBJ]
			mov	ecx,ID_FILE
			mov	eax,ff_event_xcell

			ff_rsevent( IDD_DZCompareDirectories, event_find )

			and	ah,not IO_SEARCHSUB
			and	flags,NOT (_COMP_EQUAL or _COMP_SUBDIR)
			.if	BYTE PTR [ebx+OF_EQUAL] & _O_RADIO

				or flags,_COMP_EQUAL
			.endif
			.if	BYTE PTR [ebx+OF_SUBD] & _O_FLAGB

				or flags,_COMP_SUBDIR
				or ah,IO_SEARCHSUB
			.endif

			ff_close_dlg()
			clear_list()
			clear_table()
		.else
			ermsg( 0, addr CP_ENOMEM )
		.endif
		free( ll.ll_list )
		__purgeheap()
	.endif

	.if CFAddSection(".compsubdir")

		mov ebx,eax
		CFAddEntryX(ebx, "0=%X", flags)
		CFAddEntryX(ebx, "1=%s", addr fmask)
		CFAddEntryX(ebx, "2=%s", addr spath)
		CFAddEntryX(ebx, "3=%s", addr tpath)
	.endif

	CursorSet( addr cursor )
	mov	eax,old_thelp
	mov	thelp,eax

	xor	eax,eax
	ret

cmcompsub ENDP

	END
