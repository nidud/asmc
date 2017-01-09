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
		dd KEY_F7,	event_find
		dd KEY_F8,	event_delete
		dd KEY_F9,	cmfilter_load
		dd KEY_DEL,	event_delete
		dd KEY_ALTX,	ff_event_exit
		dd 0
ff_table	dd 0
ff_count	dd 0
ff_recursive	dd 0
source		dd 0
target		dd 0

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

ff_fileblock PROC USES esi edi ebx directory, wfblk

	local	path[_MAX_PATH*2]:BYTE
	local	ioflag:BYTE
	local	result:DWORD
	local	ftime:DWORD
	local	found:BYTE

	xor eax,eax
	xor esi,esi
	mov result,eax

	.if eax != ff_count

		mov found,al
		mov edi,wfblk
		mov edx,MAXHIT
		mov result,edx
		mov ebx,tdllist

		.if [ebx].S_LOBJ.ll_count < edx

			mov result,eax
			.if filter_wblk( edi )

				add edi,S_WFBLK.wf_name
				strfcat( addr path, directory, edi )
				.if cmpwarg( edi, fp_maskp )

					test_userabort()
					mov result,eax
					.if ZERO?
						inc esi
					.endif
				.endif
			.endif
		.else
			stdmsg( addr cp_warning, addr cp_emaxfb, edx, edx )
			mov result,2
		.endif
	.endif

	.if esi

		mov ebx,wfblk
		__FTToTime( addr [ebx].S_WFBLK.wf_time )

		mov ftime,eax
		mov eax,DLG_FindFile
		mov al,[eax+OF_EQUAL]
		and al,_O_RADIO
		mov ioflag,al
		mov edi,ff_count
		mov esi,ff_table

		.repeat
			mov edx,[esi]
			add esi,4
			mov eax,ftime
			.if eax == [edx].S_FBLK.fb_time

				mov eax,DWORD PTR [edx].S_FBLK.fb_size[4]
				.if eax == DWORD PTR [ebx].S_WFBLK.wf_size[4]

					mov eax,DWORD PTR [edx].S_FBLK.fb_size
					.if eax == DWORD PTR [ebx].S_WFBLK.wf_size


						mov ecx,strfn( addr [edx].S_FBLK.fb_name )
						.if !_stricmp( addr [ebx].S_WFBLK.wf_name, ecx )

							mov found,1
							cmp ioflag,_O_RADIO
							je  addblock
						.endif
					.endif
				.endif
			.endif
			dec edi
		.until	ZERO?

		.if !found && ioflag != _O_RADIO

		addblock:

			ff_alloc( addr path, edx )

			.if ZERO?

				clear_table()
				ermsg( 0, addr CP_ENOMEM )
				mov result,-1
			.endif
		.endif
	.endif
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
	GetCursor( addr cursor )
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
	SetCursor( addr cursor )
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

	OPTION PROC: PUBLIC

cmcompsub PROC USES esi edi ebx

local	cursor:		S_CURSOR,
	ll:		S_LOBJ,
	old_thelp:	DWORD

	mov	ff_count,0
	mov	eax,thelp
	mov	old_thelp,eax
	mov	thelp,event_help
	call	clrcmdl
	GetCursor( addr cursor )
	lea	edx,ll
	mov	tdllist,edx
	mov	edi,edx
	mov	ecx,SIZE S_LOBJ
	xor	eax,eax
	rep	stosb
	mov	[edx].S_LOBJ.ll_dcount,ID_FILE
	mov	[edx].S_LOBJ.ll_proc,event_list

	.if	malloc( ( MAXHIT * 8 ) + 4 )
		mov	ll.ll_list,eax
		add	eax,(MAXHIT*4)+4
		mov	ff_table,eax
		.if	rsopen( IDD_DZCompareDirectories )
			mov	DLG_FindFile,eax
			mov	ebx,eax
			mov	[ebx].S_TOBJ.to_data[OF_GCMD],offset GCMD_search
			lea	eax,comparemask
			mov	[ebx].S_TOBJ.to_data[OF_MASK],eax
			.if	BYTE PTR [eax] == 0
				strcpy( eax, addr cp_stdmask )
			.endif
			mov	edx,panela	; The default Source is Panel-A
			mov	edi,panelb	; The default Target is Panel-B
			mov	edx,[edx].S_PANEL.pn_wsub
			mov	edi,[edi].S_PANEL.pn_wsub
			strcpy( [ebx].S_TOBJ.to_data[OF_SOURCE], [edx].S_WSUB.ws_path )
			mov	source,eax
			strcpy( [ebx].S_TOBJ.to_data[OF_TARGET], [edi].S_WSUB.ws_path )
			mov	target,eax
			mov	[ebx].S_TOBJ.to_proc[OF_FIND],event_find
			mov	[ebx].S_TOBJ.to_proc[OF_FILT],ff_event_filter
			mov	[ebx].S_TOBJ.to_proc[OF_SAVE],event_mklist
			mov	ah,BYTE PTR fsflag
			mov	al,_O_RADIO
			or	[ebx+OF_EQUAL],al
			.if	ah & IO_SEARCHSUB
				or BYTE PTR [ebx+OF_SUBD],_O_FLAGB
			.endif
			lea	edx,[ebx].S_TOBJ.to_proc[SIZE S_TOBJ]
			mov	ecx,ID_FILE
			mov	eax,ff_event_xcell
			ff_rsevent( IDD_DZCompareDirectories, event_find )
			and	ah,not IO_SEARCHSUB
			mov	al,_O_FLAGB
			.if	[ebx+OF_SUBD] & al
				or ah,IO_SEARCHSUB
			.endif
			call	ff_close_dlg
			call	clear_list
			call	clear_table
		.else
			ermsg( 0, addr CP_ENOMEM )
		.endif
		free( ll.ll_list )
		__purgeheap()
	.endif
	SetCursor( addr cursor )
	mov	eax,old_thelp
	mov	thelp,eax
	xor	eax,eax
	ret
cmcompsub ENDP

	END
