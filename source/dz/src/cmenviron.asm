; CMENVIRON.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include alloc.inc
include io.inc
include string.inc
include stdio.inc
include errno.inc
include stdlib.inc
include syserrls.inc

MAXHIT		equ 128
CELLCOUNT	equ 18

	.data

externdef	IDD_DZEnviron:DWORD

DLG_Environ	dd 0
FCB_Environ	dd 0
event_keys	dd KEY_F2,  event_add
		dd KEY_F3,  event_load
		dd KEY_F4,  event_edit
		dd KEY_F5,  event_save
		dd KEY_F8,  event_delete
		dd 0
cp_env		db '*.env',0

	.code

	OPTION	PROC: PRIVATE

getcurobj PROC
	xor	eax,eax
	mov	edx,FCB_Environ
	.if	[edx].S_LOBJ.ll_count != eax
		mov	eax,[edx].S_LOBJ.ll_index
		add	eax,[edx].S_LOBJ.ll_celoff
		mov	edx,[edx].S_LOBJ.ll_list
		lea	edx,[edx+eax*4]
		mov	eax,[edx]
		test	eax,eax
	.endif
	ret
getcurobj ENDP

putcelid PROC USES ebx
	mov	ebx,DLG_Environ
	movzx	eax,[ebx].S_DOBJ.dl_index
	.if	eax >= CELLCOUNT
		xor eax,eax
	.endif
	inc	eax
	mov	edx,FCB_Environ
	add	eax,[edx].S_LOBJ.ll_index
	mov	ecx,[edx].S_LOBJ.ll_count
	mov	bx,[ebx+4]
	add	bx,1403h
	mov	dl,bh
	scputf( ebx, edx, 0, 0, "<%02d:%02d>", eax, ecx )
	ret
putcelid ENDP

read_environ PROC USES esi edi ebx

	mov	ebx,FCB_Environ
	mov	eax,[ebx].S_LOBJ.ll_list
	.if	eax
		xor	edx,edx
		mov	edi,eax
		.while	edx < [ebx].S_LOBJ.ll_count
			free  ( [edi+edx*4] )
			inc	edx
		.endw
		xor	eax,eax
		mov	[ebx].S_LOBJ.ll_count,eax
		mov	[ebx].S_LOBJ.ll_numcel,eax
		.if	GetEnvironmentStrings()
			push	eax
			mov	esi,eax
			.repeat
				mov	al,[esi]
				.break .if !al
				.if	al != '='
					salloc( esi )
					stosd
					inc	[ebx].S_LOBJ.ll_count
					mov	eax,[ebx].S_LOBJ.ll_count
					.if	eax <= CELLCOUNT
						inc [ebx].S_LOBJ.ll_numcel
					.endif
				.endif
				.break .if !strlen( esi )
				lea	esi,[esi+eax+1]
			.until	0
			call	FreeEnvironmentStrings
			mov	eax,[ebx].S_LOBJ.ll_count
		.endif
	.endif
	ret
read_environ ENDP

event_list PROC USES esi edi ebx
	dlinit( DLG_Environ )
	mov	ebx,DLG_Environ
	movzx	esi,[ebx].S_DOBJ.dl_rect.rc_x
	add	esi,3
	movzx	edi,[ebx].S_DOBJ.dl_rect.rc_y
	add	edi,2
	xor	ebx,ebx
	.repeat
		mov	edx,FCB_Environ
		.break .if ebx >= [edx].S_LOBJ.ll_numcel
		mov	eax,ebx
		add	eax,[edx].S_LOBJ.ll_index
		shl	eax,2
		mov	edx,[edx].S_LOBJ.ll_list
		add	edx,eax
		mov	ecx,[edx]
		strchr( ecx,'=' )
		mov	ecx,[edx]
		mov	edx,eax
		.if	!ZERO?
			mov BYTE PTR [eax],0
		.endif
		scputs( esi, edi, 0, 25, ecx )
		.if	edx
			mov	BYTE PTR [edx],'='
			inc	edx
			mov	eax,esi
			add	eax,25
			scputs( eax, edi, 0, 45, edx )
		.endif
		inc	edi
		inc	ebx
	.until	0
	mov	eax,1
	ret
event_list ENDP

update_cellid PROC USES edi ebx
	call	putcelid
	call	event_list
	mov	ebx,DLG_Environ
	mov	edi,FCB_Environ
	mov	ecx,CELLCOUNT
	mov	eax,_O_STATE
	.repeat
		add	ebx,16
		or	[ebx],ax
	.untilcxz
	mov	ebx,DLG_Environ
	not	eax
	mov	ecx,[edi].S_LOBJ.ll_numcel
	.while	ecx
		add	ebx,16
		and	[ebx],ax
		dec	ecx
	.endw
	mov	eax,_C_NORMAL
	ret
update_cellid ENDP

event_xcell PROC
	call	putcelid
	mov	edx,DLG_Environ
	movzx	eax,[edx].S_DOBJ.dl_index
	mov	edx,FCB_Environ
	mov	[edx].S_LOBJ.ll_celoff,eax
	call	dlxcellevent
	ret
event_xcell ENDP

     ;--------------------------------------

event_edit PROC USES esi edi ebx
	local	variable[256]:BYTE
	local	value[2048]:BYTE
	.if	getcurobj()
		mov	esi,eax
		lea	ebx,value
		lea	edi,variable
		xor	edx,edx
		mov	[ebx],dl
		.if	strchr( esi, '=' )
			mov	BYTE PTR [eax],0
			mov	edx,eax
			inc	eax
			strcpy( ebx, eax )
		.endif
		strcpy( edi, esi )
		.if	edx
			mov BYTE PTR [edx],'='
		.endif
		mov	esi,edx
		.if	tgetline( edi, ebx, 60, 2048 )
			.if	BYTE PTR [ebx]
				.if	esi
					inc	esi
					strcmp( esi, ebx )
					jz	toend
				.endif
				.if	SetEnvironmentVariable( edi, ebx )
					call	read_environ
					call	update_cellid
				.endif
			.endif
		.endif
	.endif
toend:
	mov	eax,_C_NORMAL
	ret
event_edit ENDP

event_add PROC USES esi edi ebx
	local	environ[2048]:BYTE
	lea	ebx,environ
	mov	BYTE PTR [ebx],0
	.if	tgetline( "Format: <variable>=<value>", ebx, 60, 2048 )
		.if	BYTE PTR [ebx]
			.if	strchr( ebx, '=' )
				mov	BYTE PTR [eax],0
				inc	eax
				.if	SetEnvironmentVariable( ebx, eax )
					read_environ()
					update_cellid()
				.endif
			.endif
		.endif
	.endif
	mov	eax,_C_NORMAL
	ret
event_add ENDP

event_delete PROC USES esi ebx

	.if	getcurobj()
		mov	esi,eax
		.if	strchr( eax, '=' )
			mov	BYTE PTR [eax],0
			mov	ebx,eax
			SetEnvironmentVariable( esi, 0 )
			mov	BYTE PTR [ebx],'='
			.if	eax
				mov	ebx,FCB_Environ
				.if	!read_environ()
					mov	[ebx].S_LOBJ.ll_index,eax
					mov	[ebx].S_LOBJ.ll_celoff,eax
				.else
					mov	edx,[ebx].S_LOBJ.ll_index
					mov	ecx,[ebx].S_LOBJ.ll_celoff
					.if	edx
						mov	esi,eax
						sub	esi,edx
						.if esi < CELLCOUNT
							dec	edx
							inc	ecx
						.endif
					.endif
					sub	eax,edx
					.if	eax >= CELLCOUNT
						mov	eax,CELLCOUNT
					.endif
					.if	ecx >= eax
						dec	ecx
					.endif

					mov	[ebx].S_LOBJ.ll_index,edx
					mov	[ebx].S_LOBJ.ll_celoff,ecx
					mov	[ebx].S_LOBJ.ll_numcel,eax
					mov	ebx,DLG_Environ
					test	eax,eax
					mov	al,cl
					.if	ZERO?
						mov	al,CELLCOUNT-1
					.endif
					mov	[ebx].S_DOBJ.dl_index,al
					call	update_cellid
				.endif
			.endif
		.endif
	.endif
	mov	eax,_C_NORMAL
	ret
event_delete ENDP

event_load PROC
	local	path[_MAX_PATH]:SBYTE
	.if	wgetfile( addr path, addr cp_env, 3 )
		_close( eax )
		ReadEnvironment( addr path )
		read_environ()
		update_cellid()
	.endif
	mov	eax,_C_NORMAL
	ret
event_load ENDP

event_save PROC
	local	path[_MAX_PATH]:SBYTE
	.if	wgetfile( addr path, addr cp_env, 2 )
		_close( eax )
		SaveEnvironment( addr path )
	.endif
	mov	eax,_C_NORMAL
	ret
event_save ENDP

	OPTION	PROC: PUBLIC

cmenviron PROC USES esi edi ebx
	local	cursor:S_CURSOR
	local	ll:S_LOBJ
	lea	edx,ll
	mov	FCB_Environ,edx
	mov	edi,edx
	xor	eax,eax
	mov	ecx,SIZE S_LOBJ
	rep	stosb
	mov	[edx].S_LOBJ.ll_dcount,CELLCOUNT
	mov	[edx].S_LOBJ.ll_proc,event_list
	.if	malloc( ( MAXHIT * 4 ) + 4 )
		lea	edx,ll
		mov	[edx].S_LOBJ.ll_list,eax
		call	clrcmdl
		GetCursor( addr cursor )
		.if	rsopen( IDD_DZEnviron )
			mov	DLG_Environ,eax
			mov	ebx,eax
			mov	edi,[ebx].S_DOBJ.dl_object
			mov	[edi].S_TOBJ.to_data[24*16],offset event_keys
			lea	edx,[edi].S_TOBJ.to_proc
			mov	ecx,CELLCOUNT
			mov	eax,event_xcell
			.repeat
				mov	[edx],eax
				add	edx,SIZE S_TOBJ
			.untilcxz
			dlshow( ebx )
			mov	eax,FCB_Environ
			mov	tdllist,eax
			call	read_environ
			call	update_cellid
			.while	rsevent( IDD_DZEnviron, ebx )
				.switch eax
				  .case 1..19
					.break .if event_edit() != _C_NORMAL
					.endc
				  .case 20
					call	event_add
					.endc
				  .case 21
					call	event_delete
					.endc
				  .case 22
					call	event_load
					.endc
				  .case 23
					call	event_save
					.endc
				.endsw

			.endw
			dlclose( ebx )
		.endif
		mov	ebx,FCB_Environ
		mov	eax,[ebx].S_LOBJ.ll_list
		.if	eax
			xor	edx,edx
			mov	eax,[ebx].S_LOBJ.ll_list
			.while	edx < [ebx].S_LOBJ.ll_count
				free( [eax+edx*4] )
				inc	edx
			.endw
			free( [ebx].S_LOBJ.ll_list )
		.endif
	.else
		ermsg( 0, addr CP_ENOMEM )
	.endif
	GetEnvironmentTEMP()
	GetEnvironmentPATH()
	SetCursor( addr cursor )
	xor	eax,eax
	ret
cmenviron ENDP

	END
