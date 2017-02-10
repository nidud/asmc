include io.inc
include consx.inc
include string.inc
include wsub.inc

ID_CNT		equ 13
ID_OK		equ ID_CNT
ID_EXIT		equ ID_CNT+1
ID_FILE		equ ID_CNT+2
ID_PATH		equ ID_CNT+3
ID_L_UP		equ ID_CNT+4
ID_L_DN		equ ID_CNT+5
O_PATH		equ ID_PATH*16+16
O_FILE		equ ID_FILE*16+16

	.data

extrn	IDD_WOpenFile:dword

	o_list	dd 0
	o_wsub	dd 0
	dialog	dd 0
	a_open	db 0


	.code

wdlgopen PROC USES esi edi ebx apath:LPSTR, amask:LPSTR, asave

	local	wsub:S_WSUB
	local	list:S_LOBJ

	mov	eax,asave
	mov	a_open,al
	lea	eax,wsub
	mov	o_wsub,eax
	lea	eax,list
	mov	o_list,eax
	mov	edi,eax
	mov	ecx,sizeof( S_LOBJ )
	xor	eax,eax
	rep	stosb

	mov	wsub.ws_flag,eax
	mov	wsub.ws_maxfb,5000

	.if	wsopen( o_wsub )

		strcpy( wsub.ws_mask, amask )
		strcpy( wsub.ws_path, apath )
		xor	edi,edi

		.if	rsopen( IDD_WOpenFile )

			mov	ebx,eax
			mov	dialog,eax
			dlshow( eax )
			mov	eax,wsub.ws_path
			mov	[ebx].S_TOBJ.to_data[O_PATH],eax
			mov	[ebx].S_TOBJ.to_count[O_PATH],16
			strcpy( [ebx].S_TOBJ.to_data[O_FILE], wsub.ws_mask )
			mov	[ebx].S_TOBJ.to_proc[O_FILE],offset event_file
			mov	[ebx].S_TOBJ.to_proc[O_PATH],offset event_path
			mov	list.ll_proc,offset event_list
			mov	list.ll_dcount,ID_CNT
			mov	list.ll_celoff,ID_CNT
			mov	eax,wsub.ws_fcb
			mov	list.ll_list,eax

			.if	a_open & _WSAVE

				mov	dl,[ebx+5]
				mov	al,[ebx+4]
				add	al,21
				scputs( eax, edx, 0, 0, "Save" )
			.endif

			read_wsub()
			init_list()
			dlinit( ebx )

			.while	dllevent( ebx, addr list )

				.if	eax <= ID_CNT

					case_files()
				.else
					strfcat( wsub.ws_path, 0, [ebx].S_TOBJ.to_data[O_FILE] )
					mov	edi,eax
					.if	a_open & _WSAVE && !(a_open & _WNEWFILE)

						.if	!strext( eax )

							mov	eax,amask
							inc	eax
							strcat( edi, eax )
						.endif
					.endif
					.break
				.endif
			.endw
			dlclose( ebx )
		.endif

		wsclose( addr wsub )
		mov	eax,edi
		test	eax,eax
	.endif

	ret

init_list:
	push	esi
	push	edi
	push	ebx

	mov	ecx,ID_CNT
	mov	ebx,o_list
	mov	[ebx].S_LOBJ.ll_numcel,0
	mov	eax,[ebx].S_LOBJ.ll_index
	shl	eax,2
	add	eax,[ebx].S_LOBJ.ll_list
	mov	edi,dialog
	mov	bx,[edi+4]  ; dialog x,y
	add	bx,[edi+20] ; object x,y
	mov	edi,[edi].S_DOBJ.dl_object
	mov	esi,eax

	.repeat
		lodsd
		or	[edi].S_TOBJ.to_flag,_O_STATE
		.if	eax

			push	eax
			mov	al,[eax]
			and	al,_A_SUBDIR
			mov	al,at_foreground[F_Dialog]
			.ifnz
				mov al,at_foreground[F_Inactive];F_Subdir]
			.endif
			mov	dl,bh
			scputfg( ebx, edx, 28, eax )
			inc	bh
			pop	eax

			add	eax,S_FBLK.fb_name
			and	[edi].S_TOBJ.to_flag,not _O_STATE
			mov	edx,o_list
			inc	[edx].S_LOBJ.ll_numcel
		.endif
		mov	[edi].S_TOBJ.to_data,eax
		add	edi,SIZE S_TOBJ
	.untilcxz

	pop	ebx
	pop	edi
	pop	esi
	retn

event_list:
	call	init_list
	dlinit( dialog )
	mov	eax,_C_NORMAL
	retn

read_wsub:
	xor	eax,eax
	mov	edx,o_list
	mov	[edx].S_LOBJ.ll_index,eax
	mov	[edx].S_LOBJ.ll_count,eax
	mov	[edx].S_LOBJ.ll_numcel,eax
	wsread( o_wsub )
	mov	edx,o_list
	mov	[edx].S_LOBJ.ll_count,eax
	.if	eax > 1

		wssort( o_wsub )
	.endif
	retn

event_file:

	mov	eax,dialog
	mov	eax,[eax].S_TOBJ.to_data[O_FILE]

	.if	a_open & _WSAVE

		push	eax
		strrchr(eax, '*')
		pop	eax
		.ifz
			push	eax
			strrchr( eax, '?' )
			pop	eax
			jz	return
		.endif
		test	a_open,_WLOCK
		jnz	normal
	.endif

	mov	ecx,o_wsub
	push	eax
	push	ecx
	strnzcpy( [ecx].S_WSUB.ws_mask, eax, 32-1 )
	call	read_wsub
	call	event_list
	call	wsearch
	inc	eax
	jz	normal
return:
	mov	eax,_C_RETURN
	retn

event_path:
	call	read_wsub
	call	event_list

normal:
	mov	eax,_C_NORMAL
	retn

case_files:
	push	esi
	push	edi
	push	ebx

	mov	ebx,o_list
	mov	eax,[ebx].S_LOBJ.ll_index
	add	eax,[ebx].S_LOBJ.ll_celoff
	shl	eax,2
	add	eax,[ebx].S_LOBJ.ll_list
	mov	edi,[eax]
	mov	eax,[edi]

	.if	!( al & _A_SUBDIR )

		mov	ebx,dialog
		mov	[ebx].S_DOBJ.dl_index,ID_FILE
		lea	eax,[edi].S_FBLK.fb_name
		strcpy( [ebx].S_TOBJ.to_data[O_FILE], eax )
		.if	event_file() == _C_RETURN

			inc	eax
		.else
			xor	eax,eax
		.endif
	.else
		mov	ebx,o_wsub
		and	eax,_FB_UPDIR
		.ifnz
			.if	strfn( [ebx].S_WSUB.ws_path )

				mov	esi,eax
				xor	eax,eax
				mov	[esi-1],al
				mov	ebx,o_list
				mov	[ebx].S_LOBJ.ll_celoff,eax

				event_path()

				.if	wsearch( o_wsub, esi ) != -1

					.if	eax < ID_CNT

						mov	ecx,dialog
						mov	[ecx].S_DOBJ.dl_index,al
					.else
						mov	[ebx].S_LOBJ.ll_index,eax
					.endif
					event_list()
					xor	eax,eax
				.endif
			.endif
		.else
			mov	ecx,dialog
			mov	[ecx].S_DOBJ.dl_index,al
			lea	eax,[edi].S_FBLK.fb_name
			strfcat( [ebx].S_WSUB.ws_path, 0, eax )

			event_path()
			xor	eax,eax
		.endif
	.endif

	pop	ebx
	pop	edi
	pop	esi
	retn

wdlgopen ENDP

	END
