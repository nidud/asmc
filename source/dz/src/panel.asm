; PANEL.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include string.inc
include alloc.inc
include progress.inc
include io.inc
include errno.inc
include stdlib.inc
include process.inc
include time.inc
include crtl.inc
include cfini.inc
include winbase.inc

PUBLIC	cp_copyselected
EXTRN	cp_quote:BYTE

	.data

pcellwb		dw 256 dup(0720h)
pcell_a		S_XCEL <_D_BACKG or _D_MYBUF,1,1,<2,2,12,1>,pcellwb,<2,2,12,1>>
pcell_b		S_XCEL <_D_BACKG or _D_MYBUF,1,1,<2,2,12,1>,pcellwb,<2,2,12,1>>
prect_a		S_DOBJ <_D_CLEAR or _D_COLOR,0,0,<0,1,40,20>,0,0>
prect_b		S_DOBJ <_D_CLEAR or _D_COLOR,0,0,<40,1,40,20>,0,0>
spanela		S_PANEL <path_a,0,0,0,0,pcell_a,prect_a,0>
spanelb		S_PANEL <path_b,0,0,0,0,pcell_b,prect_b,0>

cp_emaxfb	db "This subdirectory contains more",10
		db "than %d files/directories.",10
		db "Only %d of the files is read.",0

cp_disk		db "C:\",0
cp_rot		db "home",0
cp_byte		db "byte",0
formats		db "%20s",0

format_10lu	db "%10lu",0
format_02lX	db 16," VOL-%02u ",17,0
cp_subdir	db 16," SUBDIR ",17,0
cp_updir	db 16," UP-DIR ",17,0

cp_copyselected db "%d file(s) to",0

cp_name		db 'Name',0
cp_date		db 'Date',0
cp_time		db 'Time',0
cp_size		db 'Size',0

S_PRECT		STRUC
p_name		dd ?
p_type		dd ?	; 0+Name,1+Size,2+Date,3+Time
p_putfile	dd ?
p_rect		S_RECT <>
S_PRECT		ENDS

	ALIGN	4

PTABLE	S_PRECT < 0,0,fbputsl,<1,2,12,1>>  ; Vertical Short List
	S_PRECT <26,3,fbputsd,<1,2,38,1>>  ; Vertical Short Detail
	S_PRECT < 0,0,fbputsl,<1,2,12,1>>  ; Horizontal Short List
	S_PRECT <26,3,fbputld,<1,2,78,1>>  ; Horizontal Short Detail
	S_PRECT < 0,0,fbputll,<1,2,18,1>>  ; Vertical Long List
	S_PRECT <16,2,fbputld,<1,2,38,1>>  ; Vertical Long Detail
	S_PRECT < 0,0,fbputll,<1,2,18,1>>  ; Horizontal Long List
	S_PRECT <26,3,fbputld,<1,2,78,1>>  ; Horizontal Long Detail
	S_PRECT < 0,0,fbputll,<1,2,38,1>>  ; Vertical Wide
	S_PRECT < 0,0,fbputll,<1,2,78,1>>  ; Horizontal Wide

	.code

prect_open PROC PRIVATE USES esi edi ebx pn:LPPANEL

  local panel, rect:S_RECT, xcell, xlrc:S_RECT, prect:S_RECT, dlwp

	mov	esi,pn
	mov	panel,esi
	call	comhide
	mov	edi,[esi].S_PANEL.pn_wsub
	mov	edi,[edi].S_WSUB.ws_flag
	xor	edx,edx			; x,y
	mov	eax,_scrcol		; cols
	shr	eax,1
	mov	ah,BYTE PTR _scrrow	; rows
	mov	ecx,cflag
	mov	bh,9			; panel size (rows)

	.if !( ecx & _C_COMMANDLINE )
		inc ah		; rows++
	.endif
	.if ecx & _C_MENUSLINE
		inc dh		; y++
		dec ah		; rows--
	.endif
	.if ecx & _C_STATUSLINE
		dec ah		; rows--
	.endif
	.if ecx & _C_HORIZONTAL && !( ecx & _C_WIDEVIEW )
		shr ah,1	; rows / 2
		dec bh
	.endif
	mov bl,ah
	sub bl,bh		; rows - bh (size)
	.if bl < BYTE PTR config.c_panelsize

		mov BYTE PTR config.c_panelsize,bl
	.endif

	sub ah,BYTE PTR config.c_panelsize
	.if ecx & _C_HORIZONTAL

		mov al,BYTE PTR _scrcol ; cols = 80
		.if edi & _W_PANELID && !( ecx & _C_WIDEVIEW )

			add dh,ah	; y += rows
		.endif
	.elseif edi & _W_PANELID && !( ecx & _C_WIDEVIEW )

		mov dl,BYTE PTR _scrcol ; x = 40
		shr dl,1
	.endif

	mov	WORD PTR rect,dx
	mov	WORD PTR rect+2,ax
	xor	ebx,ebx

	.if ecx & _C_HORIZONTAL
		mov bl,2
	.endif
	.if edi & _W_DETAIL
		inc bl
	.endif
	.if edi & _W_LONGNAME
		add bl,4
	.endif
	.if edi & _W_WIDEVIEW
		mov bl,8
		.if ecx & _C_HORIZONTAL
			inc bl
		.endif
	.endif

	shl	ebx,4
	add	ebx,offset PTABLE
	mov	xcell,ebx

	mov	dl,[ebx].S_PRECT.p_rect.rc_col
	push	eax
	mov	eax,[ebx].S_PRECT.p_rect
	mov	prect,eax
	mov	eax,_scrcol
	.if	dl != 78
		shr eax,1
		.if dl != 38
			.if dl == 18
				shr eax,1
			.else
				mov eax,14
			.endif
		.endif
	.endif
	sub	eax,2
	pop	ecx
	mov	prect.rc_col,al

	mov	eax,prect
	add	ax,WORD PTR rect
	mov	xlrc,eax

	mov	ebx,[esi].S_PANEL.pn_xl
	mov	[ebx].S_XCEL.xl_cpos,eax
	sub	ch,3
	mov	[ebx].S_XCEL.xl_rows,ch

	movzx	eax,cl
	dec	al
	mov	cl,xlrc.rc_col
	inc	cl
	div	cl
	mov	[ebx].S_XCEL.xl_cols,al

	mov	ebx,[esi].S_PANEL.pn_dialog
	.if	[ebx].S_DOBJ.dl_flag & _D_DOPEN

		dlclose( [esi].S_PANEL.pn_xl )
		dlclose( ebx )
	.endif

	mov	eax,rect
	mov	[ebx].S_DOBJ.dl_rect,eax
	mov	al,at_background[B_Panel]
	or	al,at_foreground[F_Frame]

	.if	dlopen( ebx, eax, 0 )

		xor	eax,eax
		mov	WORD PTR rect,ax

		mov	edx,[esi].S_PANEL.pn_dialog
		mov	edx,[edx].S_DOBJ.dl_wp
		mov	dlwp,edx
		movzx	ecx,rect.rc_col
		add	edx,ecx
		add	edx,ecx
		mov	ah,at_background[B_Panel]
		or	ah,at_foreground[F_Panel]
		mov	al,' '
		wcputw( edx, ecx, eax )

		.if	edi & _W_MINISTATUS

			mov	al,2
			sub	rect.rc_row,al
			mov	edx,[esi].S_PANEL.pn_xl
			sub	[edx].S_XCEL.xl_rows,al
			.if	edi & _W_DRVINFO

				sub rect.rc_row,al
				sub [edx].S_XCEL.xl_rows,al
				.if !( cflag & _C_HORIZONTAL )

					dec rect.rc_row
					dec [edx].S_XCEL.xl_rows
				.endif
			.endif
			xor	eax,eax
			mov	ah,at_background[B_Panel]
			or	ah,at_foreground[F_Frame]
			movzx	edx,rect.rc_col
			rcframe(rect, dlwp, edx, eax)
		.endif

		mov	ebx,xcell
		mov	eax,[ebx].S_PRECT.p_putfile
		mov	[esi].S_PANEL.pn_putfcb,eax

		mov	eax,rect
		mov	xlrc,eax
		mov	al,prect.rc_col
		add	al,2
		mov	xlrc.rc_col,al
		mov	dl,12
		mov	dh,at_background[B_Panel]
		or	dh,at_foreground[F_Frame]
		movzx	ecx,rect.rc_col

		push	edi
		lea	edi,[ecx*2]
		add	edi,dlwp

		movzx	eax,prect.rc_col
		mov	esi,eax
		inc	esi
		add	esi,esi
		and	al,-2
		sub	al,2

		.switch [ebx].S_PRECT.p_type
		  .case 0
			add	edi,eax
			.repeat
				wcputs( edi, ecx, ecx, addr cp_name )
				add	edi,esi
				rcframe( xlrc, dlwp, ecx, edx )
				movzx	eax,prect.rc_col
				inc	eax
				movzx	ebx,xlrc.rc_x
				add	ebx,eax
				.break .if bh
				add	xlrc.rc_x,al
				add	eax,ebx
				.break .if ah
				movzx	ebx,xlrc.rc_col
				add	eax,ebx
				.break .if ah
			.until	al > rect.rc_col
			mov	al,prect.rc_col
			add	al,2
			.if	al != rect.rc_col
				wcputs( edi, ecx, ecx, addr cp_name )
			.endif
			.endc
		  .case 2
			sub	eax,[ebx].S_PRECT.p_name
			add	eax,edi
			wcputs( eax, ecx, ecx, addr cp_name )
			lea	eax,[edi+ecx*2-14]
			wcputs( eax, ecx, ecx, addr cp_date )
			lea	eax,[edi+ecx*2-34]
			wcputs( eax, ecx, ecx, addr cp_size )
			sub	xlrc.rc_col,9
			rcframe( xlrc, dlwp, ecx, edx )
			sub	xlrc.rc_col,11
			rcframe( xlrc, dlwp, ecx, edx )
			.endc
		  .case 3
			sub	eax,[ebx].S_PRECT.p_name
			add	eax,edi
			wcputs( eax, ecx, ecx, addr cp_name )
			lea	eax,[edi+ecx*2-10]
			wcputs( eax, ecx, ecx, addr cp_time )
			lea	eax,[edi+ecx*2-26]
			wcputs( eax, ecx, ecx, addr cp_date )
			lea	eax,[edi+ecx*2-46]
			wcputs( eax, ecx, ecx, addr cp_size )
			sub	xlrc.rc_col,6
			rcframe( xlrc, dlwp, ecx, edx )
			sub	xlrc.rc_col,9
			rcframe( xlrc, dlwp, ecx, edx )
			sub	xlrc.rc_col,11
			rcframe( xlrc, dlwp, ecx, edx )
		.endsw

		pop	edi
		mov	ebx,dlwp
		xor	eax,eax
		mov	edx,eax
		mov	al,rect.rc_col
		add	al,2
		lea	eax,[ebx+eax*2]
		mov	BYTE PTR [eax],':'
		mov	cl,ASCII_ARROWD
		mov	[eax+2],cl
		mov	eax,panel
		mov	ecx,[eax].S_PANEL.pn_dialog
		mov	dl,[ecx].S_DOBJ.dl_rect.rc_col
		mov	ecx,[ecx].S_DOBJ.dl_rect
		xor	cx,cx
		mov	eax,6
		mov	ah,at_background[B_Panel]
		or	ah,at_foreground[F_Frame]
		rcframe( ecx, ebx, edx, eax )
		xor	eax,eax
		mov	al,rect.rc_row
		mov	ah,rect.rc_col

		.if	!( edi & _W_MINISTATUS )
			mul	ah
			mov	cl,ASCII_UP
			mov	[ebx+eax*2-6],cl
		.else
			dec	al
			mul	ah
			.if	edi & _W_DRVINFO
				mov	cl,ASCII_DOWN
				mov	[ebx+eax*2+4],cl
			.else
				mov	cl,ASCII_DOT
				mov	[ebx+eax*2+4],cl
				movzx	edx,rect.rc_col
				add	eax,edx
				mov	cl,ASCII_DOWN
				mov	[ebx+eax*2-6],cl
			.endif
		.endif
		mov	esi,panel
		mov	eax,cflag
		and	eax,_C_WIDEVIEW
		.if	ZERO? || esi == cpanel
			dlshow( [esi].S_PANEL.pn_dialog )
			or	edi,_W_VISIBLE
			and	edi,not _W_WHIDDEN
		.else
			or	edi,_W_WHIDDEN
		.endif
		mov	edx,[esi].S_PANEL.pn_wsub
		mov	[edx].S_WSUB.ws_flag,edi
	.endif
	push	eax
	call	comshow
	pop	eax
	ret
prect_open ENDP

prect_hide PROC panel:LPPANEL

	mov	ecx,panel
	mov	edx,[ecx].S_PANEL.pn_wsub
	mov	eax,[edx].S_WSUB.ws_flag

	.if	eax & _W_WHIDDEN

		xor	eax,_W_WHIDDEN
		mov	[edx].S_WSUB.ws_flag,eax
		mov	eax,1

	.elseif eax & _W_VISIBLE

		xor	eax,_W_VISIBLE
		mov	[edx].S_WSUB.ws_flag,eax
		push	[ecx].S_PANEL.pn_dialog
		push	[ecx].S_PANEL.pn_xl
		call	dlclose
		call	dlhide
		mov	eax,1
	.else
		xor	eax,eax
	.endif
	ret

prect_hide ENDP

prect_close proc private panel

	mov	ecx,panel
	mov	eax,[ecx].S_PANEL.pn_wsub
	mov	eax,[eax].S_WSUB.ws_flag
	and	eax,_W_VISIBLE
	.ifnz
		push	[ecx].S_PANEL.pn_dialog
		prect_hide(ecx)
		call	dlclose
		mov	eax,1
	.endif
	ret

prect_close endp

prect_open_ab PROC

	mov	eax,cflag
	and	eax,_C_PANELID
	lea	eax,spanela
	.ifnz
		lea eax,spanelb
	.endif
	mov	cpanel,eax

	xor	eax,eax
	.if	flaga & _W_VISIBLE

		prect_open(addr spanela)
	.endif
	.if	flagb & _W_VISIBLE

		prect_open(addr spanelb)
	.endif
	ret

prect_open_ab ENDP

panel_getb PROC

	mov	eax,panela
	.if	eax == cpanel

		mov eax,panelb
	.endif
	ret

panel_getb ENDP

panel_state PROC panel:LPPANEL

	mov	ecx,panel
	mov	eax,[ecx].S_PANEL.pn_dialog
	mov	eax,[eax].S_DOBJ.dl_wp
	.if	eax

		mov	eax,[ecx].S_PANEL.pn_wsub
		mov	eax,[eax].S_WSUB.ws_fcb
		.if	eax

			mov eax,ecx
		.endif
	.endif
	ret

panel_state ENDP

cpanel_state PROC
	panel_state(cpanel)
	ret
cpanel_state ENDP

panel_stateab PROC

	.if	panel_state(panela)

		panel_state(panelb)
	.endif
	ret

panel_stateab ENDP

panel_curobj PROC panel:LPPANEL

	mov	ecx,panel
	mov	eax,[ecx].S_PANEL.pn_wsub
	.if	eax

		mov	eax,[ecx].S_PANEL.pn_fcb_index
		add	eax,[ecx].S_PANEL.pn_cel_index

		.if	wsfblk( [ecx].S_PANEL.pn_wsub, eax )

			mov	edx,eax
			add	eax,S_FBLK.fb_name
		.endif
	.endif
	ret

panel_curobj ENDP

panel_findnext PROC panel:LPPANEL

	mov	ecx,panel
	.if	wsffirst([ecx].S_PANEL.pn_wsub)

		mov	edx,eax
		add	eax,S_FBLK.fb_name
	.endif
	ret

panel_findnext ENDP

cpanel_findfirst PROC

	.if	panel_state(cpanel)

		.if	!panel_findnext(eax)

			panel_curobj(cpanel)
		.endif

		.if	!ZERO? && ecx & _FB_UPDIR

			xor	eax,eax
		.endif
	.endif

	test	eax,eax
	ret

cpanel_findfirst ENDP

cpanel_gettarget PROC

	.if	panel_stateab()

		mov	eax,path_a.ws_path
		.if	cpanel == offset spanela

			mov eax,path_b.ws_path
		.endif
	.endif
	test eax,eax
	ret

cpanel_gettarget ENDP

panel_hide PROC USES ebx panel:LPPANEL

	mov	ebx,panel
	prect_close(ebx)
	wsfree([ebx].S_PANEL.pn_wsub)
	mov	eax,ebx
	ret

panel_hide ENDP

panel_show PROC panel:LPPANEL

	mov	ecx,panel
	mov	edx,[ecx].S_PANEL.pn_wsub
	or	[edx].S_WSUB.ws_flag,_W_VISIBLE

	panel_update(ecx)
	ret

panel_show ENDP

panel_selected PROC PRIVATE USES esi panel:LPPANEL

	xor  eax,eax
	mov  ecx,panel

	.for edx = [ecx].S_PANEL.pn_fcb_count,
	     ecx = [ecx].S_PANEL.pn_wsub,
	     esi = [ecx].S_WSUB.ws_fcb : esi && edx : esi += 4, edx--

		mov ecx,[esi]
		.if [ecx].S_FBLK.fb_flag & _FB_SELECTED

			add eax,1
		.endif
	.endf
	ret

panel_selected ENDP

pcell_set PROC PRIVATE USES esi edi ebx panel

	mov	esi,panel
	mov	edi,[esi].S_PANEL.pn_xl
	movzx	eax,[edi].S_XCEL.xl_cols
	movzx	edx,[edi].S_XCEL.xl_rows
	mul	edx
	mov	edx,[esi].S_PANEL.pn_fcb_count
	sub	edx,[esi].S_PANEL.pn_fcb_index
	.if	eax >= edx
		mov	eax,edx
	.endif
	mov	[esi].S_PANEL.pn_cel_count,eax
	mov	edx,[esi].S_PANEL.pn_cel_index
	.if	edx < eax
		mov	eax,edx
	.else
		dec	eax
	.endif
	mov	[esi].S_PANEL.pn_cel_index,eax
	sub	edx,edx
	movzx	ebx,[edi].S_XCEL.xl_rows
	div	ebx
	mov	ecx,eax
	mul	ebx
	mov	ebx,[esi].S_PANEL.pn_cel_index
	sub	ebx,eax
	movzx	eax,[edi].S_XCEL.xl_cpos.rc_col
	inc	eax
	mul	ecx
	mov	ecx,eax
	mov	eax,[edi].S_XCEL.xl_cpos
	add	al,cl
	add	ah,bl
	mov	[edi].S_XCEL.xl_rect,eax
	mov	eax,[esi].S_PANEL.pn_cel_index
	ret
pcell_set ENDP

panel_setid PROC panel:LPPANEL, index:UINT

	mov	edx,panel
	xor	eax,eax
	mov	[edx].S_PANEL.pn_cel_index,eax
	mov	[edx].S_PANEL.pn_fcb_index,eax
	pcell_set(edx)

	mov	eax,index
	mov	edx,panel

	.if	eax < [edx].S_PANEL.pn_cel_count

		mov	[edx].S_PANEL.pn_cel_index,eax
	.else
		sub	eax,[edx].S_PANEL.pn_cel_count
		inc	eax
		mov	[edx].S_PANEL.pn_fcb_index,eax
		mov	eax,[edx].S_PANEL.pn_cel_count
		dec	eax
		mov	[edx].S_PANEL.pn_cel_index,eax
	.endif
	ret
panel_setid ENDP

pcell_open PROC PRIVATE
	mov	edx,eax
	mov	al,at_background[B_InvPanel]
	dlopen( [edx].S_PANEL.pn_xl, eax, 0 )
	ret
pcell_open ENDP

pcell_show PROC USES esi edi panel:LPPANEL
	mov	esi,panel
	mov	edi,[esi].S_PANEL.pn_xl
	xor	eax,eax
	.if	!([edi].S_XCEL.xl_flag & _D_DOPEN or _D_ONSCR)

		pcell_set(esi)
		xor	eax,eax
		.if	[esi].S_PANEL.pn_cel_count != eax
			mov	eax,esi
			call	pcell_open
			dlshow( edi )
			mov	eax,1
		.endif
	.endif
	ret
pcell_show ENDP

panel_putinfo PROC PRIVATE USES esi edi ebx panel:LPPANEL

  local path[WMAXPATH]:BYTE, xy:WORD, len:DWORD

	.if	panel_state(panel)

		mov	edi,eax
		mov	eax,[edi].S_PANEL.pn_dialog
		.if	[eax].S_DOBJ.dl_flag & _D_ONSCR

			mov	esi,[edi].S_PANEL.pn_wsub
			mov	eax,[eax+4]
			mov	xy,ax
			shr	eax,16
			and	eax,0FFh
			sub	eax,2
			mov	len,eax

			strcpy( addr path, [esi].S_WSUB.ws_path )
			.if	[esi].S_WSUB.ws_flag & _W_ARCHIVE or _W_ROOTDIR

				strfcat( eax, [esi].S_WSUB.ws_file, [esi].S_WSUB.ws_arch )
			.endif

			mov	edx,eax
			mov	bx,xy
			add	bx,0101h
			mov	cl,bh
			mov	ah,at_background[B_Panel]
			or	ah,at_foreground[F_Panel]
			mov	esi,[esi].S_WSUB.ws_path
			mov	al,[esi]
			scputw( ebx, ecx, 1, eax )

			mov	ecx,len
			push	ecx
			push	edx
			dec	bh
			mov	ah,at_background[B_Panel]
			or	ah,at_foreground[F_Frame]
			mov	al,205
			mov	dl,bh
			scputw( ebx, edx, ecx, eax )

			pop	edx
			strlen( edx )
			xchg	edx,eax
			pop	ebx
			mov	cl,at_background[B_Panel]

			.if	edi == cpanel

				mov cl,at_background[B_InvPanel]
			.endif
			or	cl,at_foreground[F_Frame]
			dec	ebx
			.if	edx >= ebx

				push	eax
				mov	ah,cl
				mov	al,' '
				movzx	ecx,bl
				inc	ecx
				mov	bx,xy
				inc	bl
				mov	dl,bh
				scputw( ebx, edx, ecx, eax )
				inc	bl
				sub	cl,2
				pop	eax
				scpath( ebx, edx, ecx, eax )
			.else
				mov	esi,eax
				mov	al,bl
				shr	dl,1
				adc	dl,0
				shr	al,1
				adc	al,0
				mov	bx,xy
				add	bl,al
				sub	bl,dl
				mov	dl,bh
				scputf( ebx, edx, ecx, 0, " %s ", esi )
			.endif
		.endif
	.endif
	ret
panel_putinfo ENDP

panel_setactive PROC USES esi edi panel:LPPANEL

	mov	esi,panel
	mov	edi,cpanel
	and	cflag,not _C_PANELID

	mov	eax,[esi].S_PANEL.pn_wsub
	.if	[eax].S_WSUB.ws_flag & _W_PANELID

		or cflag,_C_PANELID
	.endif

	cominit( [esi].S_PANEL.pn_wsub )
	dlclose( [edi].S_PANEL.pn_xl )

	mov	cpanel,esi
	panel_putinfo(edi)
	.if	cflag & _C_WIDEVIEW

		.if	esi != edi

			.if panel_state(esi)

				prect_hide(edi)
				mov	eax,[edi].S_PANEL.pn_wsub
				or	[eax].S_WSUB.ws_flag,_W_WHIDDEN
				mov	eax,[esi].S_PANEL.pn_wsub
				and	[eax].S_WSUB.ws_flag,not _W_WHIDDEN
				panel_show(esi)
			.endif
			jmp	toend
		.endif
	.endif
	pcell_show(esi)
	panel_putinfo(esi)
toend:
	ret
panel_setactive ENDP

panel_sethdd PROC USES esi edi panel:LPPANEL, hdd:UINT

	push	_getdrive()
	mov	esi,panel
	mov	edi,_disk_init(hdd)

	historysave()
	wschdrv([esi].S_PANEL.pn_wsub, edi)
	panel_read(esi)
	pop	eax
	.if	esi == cpanel

		cominit( [esi].S_PANEL.pn_wsub )
	.endif
	panel_putinfozx()
	ret

panel_sethdd ENDP

panel_toggle PROC USES esi edi panel:LPPANEL

	mov	esi,panel
	mov	edi,panel_getb()
	mov	ecx,panel_state(edi)
	mov	edx,[esi].S_PANEL.pn_dialog
	mov	eax,[edx]

	.if	eax & _D_ONSCR

		xchg	edi,edx
		.if	ecx && esi == cpanel

			panel_setactive(edx)
		.endif
		mov	eax,[edi]
		.if	eax & _D_ONSCR

			panel_hide(esi)
		.endif
	.else
		panel_show(esi)

		mov edi,cpanel
		mov edi,[edi].S_PANEL.pn_dialog
		mov eax,[edi]
		.if !( eax & _D_ONSCR )

			panel_setactive(esi)
		.endif
	.endif
	xor	eax,eax
	ret
panel_toggle ENDP

panel_toggleact PROC

	.if panel_stateab()

		historysave()
		panel_setactive(panel_getb())
		mov eax,1
	.endif
	test eax,eax
	ret

panel_toggleact ENDP

panel_update PROC USES esi panel:LPPANEL
	mov	esi,panel
	mov	eax,[esi].S_PANEL.pn_wsub
	mov	eax,[eax].S_WSUB.ws_flag
	and	eax,_W_VISIBLE
	.ifnz
		panel_read(esi)
		panel_redraw(esi)
	.endif
	ret
panel_update ENDP

panel_xorinfo PROC panel:LPPANEL
	mov	ecx,panel
	mov	edx,[ecx].S_PANEL.pn_wsub
	mov	eax,[edx].S_WSUB.ws_flag
	xor	eax,_W_DRVINFO
	.if	eax & _W_DRVINFO
		or eax,_W_MINISTATUS
	.endif
	mov	[edx].S_WSUB.ws_flag,eax
	panel_redraw(ecx)
	ret
panel_xorinfo ENDP

panel_xormini PROC panel:LPPANEL

	mov	ecx,panel
	mov	eax,[ecx].S_PANEL.pn_wsub
	xor	[eax].S_WSUB.ws_flag,_W_MINISTATUS
	.if	[eax].S_WSUB.ws_flag & _W_VISIBLE

		panel_redraw(ecx)
	.endif
	msloop()
	xor	eax,eax
	ret

panel_xormini ENDP

pcell_getrect PROC PRIVATE USES esi edi ebx xcell, index

	mov	ecx,index
	mov	ebx,xcell
	movzx	edi,[ebx].S_XCEL.xl_rows

	mov	eax,ecx
	xor	edx,edx
	div	edi

	mov	esi,eax
	mul	edi
	sub	ecx,eax

	movzx	eax,[ebx].S_XCEL.xl_cpos.rc_col
	inc	eax
	mul	esi
	add	eax,[ebx].S_XCEL.xl_cpos
	add	ah,cl
	ret

pcell_getrect ENDP

panel_xycmd PROC USES esi ebx panel:LPPANEL, xpos:UINT, ypos:UINT

	.if panel_state(panel)

		mov	esi,eax
		xor	eax,eax
		mov	edx,[esi].S_PANEL.pn_dialog

		.if	[edx].S_DOBJ.dl_flag & _D_ONSCR

			mov	ebx,[edx].S_DOBJ.dl_rect
			.switch rcxyrow( ebx, xpos, ypos )

			  .case 1
				mov	eax,_XY_MOVEUP
			  .case 0
				.endc

			  .case 2
				movzx	edx,bl
				mov	ecx,xpos
				mov	eax,_XY_INSIDE
				.endc	.if ecx == edx
				add	edx,2
				mov	eax,_XY_NEWDISK
				.endc	.if ecx <= edx
				inc	edx
				mov	eax,_XY_CONFIG
				.endc	.if ecx == edx
				mov	eax,_XY_MOVEUP
				.endc

			  .default

				mov	edx,eax
				mov	ecx,ebx
				shr	ecx,24
				mov	eax,[esi].S_PANEL.pn_wsub

				.if	[eax].S_WSUB.ws_flag & _W_MINISTATUS

					sub	ecx,2
					.if	[eax].S_WSUB.ws_flag & _W_DRVINFO
						sub	ecx,2
						.if	!( cflag & _C_HORIZONTAL )
							dec	ecx
						.endif
					.endif
					mov	eax,_XY_MOVEDOWN
					.endc	.if edx > ecx

					.ifz
						movzx	eax,bl
						add	eax,2
						.if	eax == xpos
							mov eax,_XY_DRVINFO
							.endc
						.endif
					.endif
				.endif

				.if	edx == ecx
					movzx	eax,bl
					shr	ebx,16
					add	al,bl
					sub	eax,3
					cmp	eax,xpos
					mov	eax,_XY_MINISTATUS
					.endc	.if ZERO?
					mov	eax,_XY_MOVEDOWN
					.endc
				.endif

				xor	ebx,ebx
				.while	ebx < [esi].S_PANEL.pn_cel_count
					pcell_getrect( [esi].S_PANEL.pn_xl, ebx )
					inc	ebx
					push	eax
					rcxyrow(eax,xpos,ypos)
					pop	edx
					mov	eax,_XY_INSIDE
					.ifnz
						lea	ecx,[ebx-1]
						mov	eax,_XY_FILE
						.break
					.endif
				.endw
			.endsw
		.endif
	.endif
toend:
	ret
panel_xycmd ENDP

redraw_panels PROC

	prect_hide(panelb)
	push	eax
	.if	prect_hide(panela)

		redraw_panel(panela)
	.endif
	pop	eax
	.if	eax
		redraw_panel(panelb)
	.endif
	ret
redraw_panels ENDP

panel_openmsg PROC USES esi ebx panel:LPPANEL

	mov	esi,panel
	mov	ebx,[esi].S_PANEL.pn_dialog
	xor	eax,eax

	.if	[ebx].S_DOBJ.dl_flag & _D_ONSCR && [ebx].S_DOBJ.dl_wp != eax

		mov	eax,[esi].S_PANEL.pn_wsub
		mov	eax,[eax].S_WSUB.ws_flag
		and	eax,_W_MINISTATUS
		.ifnz
			movzx	ecx,[ebx].S_DOBJ.dl_rect.rc_col
			sub	cl,2
			movzx	eax,[ebx].S_DOBJ.dl_rect.rc_y
			add	al,[ebx].S_DOBJ.dl_rect.rc_row
			sub	al,2
			movzx	ebx,[ebx].S_DOBJ.dl_rect.rc_x
			inc	ebx
			mov	edx,eax
			mov	ah,at_background[B_Panel]
			or	ah,at_foreground[F_System]
			mov	al,' '
			scputw( ebx, edx, ecx, eax )
			scputs( ebx, edx, 0, 5, "open:" )

			mov	esi,[esi].S_PANEL.pn_wsub
			mov	eax,[esi].S_WSUB.ws_path
			.if	[esi].S_WSUB.ws_flag & _W_ARCHIVE

				mov eax,[esi].S_WSUB.ws_file
			.endif
			sub	cl,6
			add	bl,6
			scpath( ebx, edx, ecx, eax )
		.endif
	.endif
	ret
panel_openmsg ENDP

wsreadroot PROC PRIVATE USES esi edi ebx wsub, panel

  local disk, index, VolumeID[32]:BYTE

	mov	ebx,wsub
	wsfree( ebx )
	xor	eax,eax
	mov	index,eax
	mov	eax,[ebx].S_WSUB.ws_flag
	and	eax,not (_W_ARCHIVE or _W_NETWORK)
	or	eax,_W_ROOTDIR
	mov	[ebx].S_WSUB.ws_flag,eax
	_disk_read()
	mov	disk,_getdrive()

	.if	_disk_exist( eax )

		mov	edi,eax
		mov	eax,[ebx].S_WSUB.ws_path
		mov	eax,[eax]
		.if	al && ah == ':'

			and	al,not 20h
			mov	cp_disk,al
			.if	GetVolumeID( addr cp_disk, addr VolumeID )

				add	edi,S_DISK.di_name[3]
				mov	BYTE PTR [edi-1],' '
				strnzcpy( edi, addr VolumeID, 27 )
			.endif
		.endif
	.endif

	mov	eax,[ebx].S_WSUB.ws_arch
	mov	BYTE PTR [eax],0
	strcpy( [ebx].S_WSUB.ws_file, addr cp_rot )
	xor	edi,edi
	xor	esi,esi
	mov	ebx,[ebx].S_WSUB.ws_fcb
	.while	esi < MAXDRIVES

		inc	esi
		.continue .if !_disk_exist( esi )
		lea	ecx,[eax].S_DISK.di_name
		.break .if !fballoc( ecx, [eax].S_DISK.di_time,
			[eax].S_DISK.di_size, [eax].S_DISK.di_flag )
		mov	[ebx+edi*4],eax
		inc	edi
		.if	esi == disk
			lea	eax,[edi-1]
			mov	index,eax
		.endif
	.endw
	mov	ebx,wsub
	mov	[ebx].S_WSUB.ws_count,edi
	mov	eax,edi
	mov	edx,index
	ret
wsreadroot ENDP

wsub_read PROC USES esi edi wsub

	xor	esi,esi
	mov	edi,wsub

	mov	eax,[edi].S_WSUB.ws_flag
	and	eax,_W_ARCHIVE
	.if	eax
		mov	esi,esp
		strfcat( alloca( WMAXPATH ), [edi].S_WSUB.ws_path, [edi].S_WSUB.ws_file )
		filexist( eax )
		mov	esp,esi
		xor	esi,esi
		.if	eax == 1
			.if	[edi].S_WSUB.ws_flag & _W_ARCHZIP
				wzipread( edi )
			.else
				warcread( edi )
			.endif
			.if	eax != ER_READARCH
				inc	esi
			.endif
		.endif
	.endif

	.if	!esi
		and	[edi].S_WSUB.ws_flag,not (_W_ARCHIVE or _W_ROOTDIR)
		wsread( edi )
	.endif

	mov	esi,eax
	.if	eax > 1 && !( [edi].S_WSUB.ws_flag & _W_NOSORT )
		wssort( edi )
	.endif
	.if	esi == [edi].S_WSUB.ws_maxfb
		stdmsg( addr cp_warning, addr cp_emaxfb, esi, esi )
	.endif
	mov	eax,esi
	ret
wsub_read ENDP

panel_read PROC USES esi edi panel:LPPANEL

	mov	esi,panel
	mov	edi,[esi].S_PANEL.pn_wsub
	panel_openmsg(esi)

	mov	eax,[edi].S_WSUB.ws_path
	.if	BYTE PTR [eax] && [edi].S_WSUB.ws_flag & _W_ROOTDIR
		wsreadroot( edi, esi )
		mov [esi].S_PANEL.pn_cel_index,edx
	.else
		wsub_read( edi )
	.endif
	mov	[esi].S_PANEL.pn_fcb_count,eax
	.if	eax <= [esi].S_PANEL.pn_fcb_index
		.if	eax
			dec	eax
			mov	[esi].S_PANEL.pn_fcb_index,eax
			inc	eax
		.else
			mov	[esi].S_PANEL.pn_fcb_index,eax
		.endif
	.endif
	ret
panel_read ENDP

panel_open PROC PRIVATE USES esi edi panel:LPPANEL

  local path[WMAXPATH]:BYTE, wsub:DWORD

	mov	esi,panel
	mov	edi,[esi].S_PANEL.pn_wsub
	mov	wsub,edi

	.if	wsopen(edi)

		mov	[esi].S_PANEL.pn_cel_count,0

		.if	esi == cpanel

			push	[edi].S_WSUB.ws_flag
			strcpy(addr path, [edi].S_WSUB.ws_path)
			mov	eax,[edi].S_WSUB.ws_path
			mov	BYTE PTR [eax],0
			cominit(wsub)
			pop	eax

			.if	eax & _W_ARCHIVE

				push	eax
				_stricmp(addr path, [edi].S_WSUB.ws_path)
				pop	edx
				.if	!eax
					mov [edi].S_WSUB.ws_flag,edx
				.endif
			.endif
		.endif

		.if	[edi].S_WSUB.ws_flag & _W_VISIBLE

			panel_reread(esi)
			.if	esi == cpanel

				panel_setactive(esi)
			.endif
		.endif
		mov	eax,1
	.endif
	ret
panel_open ENDP

panel_open_ab PROC

	.if panel_open(cpanel)

		lea eax,spanelb
		.if cpanel == eax

			lea eax,spanela
		.endif
	.endif

	panel_open(eax)
	mov	eax,1
	ret

panel_open_ab ENDP

panel_close PROC panel:LPPANEL

	.if panel_state(panel)

		push	eax
		prect_close(eax)
		pop	eax
		wsclose([eax].S_PANEL.pn_wsub)
	.endif
	ret

panel_close ENDP

cpanel_setpath PROC path:LPSTR

	mov	eax,path
	mov	eax,[eax]

	.if	ah == ':'

		or	al,20h
		sub	eax,'a' - 1

		_disk_ready(eax)
	.endif

	.if	eax
		mov	eax,cpanel
		mov	eax,[eax].S_PANEL.pn_wsub
		and	[eax].S_WSUB.ws_flag,not (_W_NETWORK or _W_ARCHIVE or _W_ROOTDIR)
		strcpy([eax].S_WSUB.ws_path, path)
		mov	eax,cpanel
		cominit([eax].S_PANEL.pn_wsub)
		panel_reread(cpanel)
	.endif
	ret

cpanel_setpath ENDP

cpanel_deselect PROC USES esi edi fp:LPFBLK

	mov edx,fp
	and [edx].S_FBLK.fb_flag,not _FB_SELECTED

	.if cflag & _C_VISUALUPDATE

		mov di,progress_dobj.S_DOBJ.dl_flag
		and edi,_D_ONSCR
		.ifnz
			dlhide(addr progress_dobj)
		.endif

		panel_putitem(cpanel,0)

		lea esi,spanela
		.if esi == cpanel

			lea esi,spanelb
		.endif

		mov edx,[esi].S_PANEL.pn_wsub
		mov eax,[edx].S_WSUB.ws_maxfb
		sub eax,2

		.if eax > [edx].S_WSUB.ws_count

			mov	eax,fp
			add	eax,S_FBLK.fb_name
			strlen( eax )
			add	eax,SIZE S_FBLK
			push	eax
			malloc( eax )
			pop	edx

			.ifnz
				mov	edx,memcpy(eax, fp, edx)
				inc	[esi].S_PANEL.pn_fcb_count
				inc	[esi].S_PANEL.pn_cel_count
				mov	eax,[esi].S_PANEL.pn_wsub
				mov	ecx,[eax].S_WSUB.ws_count
				inc	[eax].S_WSUB.ws_count
				mov	eax,[eax].S_WSUB.ws_fcb
				mov	[eax+ecx*4],edx

				panel_event(esi, KEY_END)
			.endif
		.endif

		.if edi

			dlshow(addr progress_dobj)
		.endif
	.endif
	ret
cpanel_deselect ENDP

fblk_selectable proc private fp:LPFBLK

	mov ecx,fp
	xor eax,eax

	.if !( BYTE PTR [ecx] & _A_VOLID )

		inc eax
		.if BYTE PTR [ecx] & _A_SUBDIR && !( cflag & _C_SELECTDIR )

			dec eax
		.endif
	.endif
	ret

fblk_selectable endp

fblk_invert PROC fp:LPFBLK

	.if fblk_selectable(fp)

		fbinvert(ecx)
	.endif
	ret

fblk_invert ENDP

fblk_select PROC fp:LPFBLK

	.if fblk_selectable(fp)

		fbselect(ecx)
	.endif
	ret

fblk_select ENDP

fbputfile PROC USES esi edi ebx fb, x, y, l
	mov	eax,fb
	mov	ebx,eax
	add	eax,S_FBLK.fb_name
	mov	edi,eax
	strlen( eax )
	mov	esi,eax
	fbcolor(ebx)
	mov	ecx,l
	sub	ecx,25
	scputs( x, y, eax, ecx, edi )
	.if	esi > ecx
		mov	al,BYTE PTR x
		add	al,cl
		dec	al
		mov	cl,al
		mov	al,'¯'
		mov	ah,at_foreground[F_Panel]
		or	ah,at_background[B_Panel]
		scputw( ecx, y, 1, eax )
	.endif
	mov	dl,BYTE PTR x
	add	dl,cl
	mov	eax,[ebx].S_FBLK.fb_flag
	.if	al & _A_HIDDEN or _A_SYSTEM
		fbcolor(ebx)
		mov	ah,al
		mov	al,'°'
		scputw( edx, y, 1, eax )
	.endif

	mov	eax,[ebx].S_FBLK.fb_flag
	mov	esi,eax
	fbcolor(ebx)
	mov	ecx,eax
	mov	eax,DWORD PTR [ebx].S_FBLK.fb_size
	mov	edx,DWORD PTR [ebx].S_FBLK.fb_size[4]
	mov	bl,BYTE PTR x
	add	bl,BYTE PTR l
	sub	bl,25
	.if	esi & _A_SUBDIR
		inc	bl
		and	esi,_FB_UPDIR
		mov	eax,offset cp_subdir+1
		.ifnz
			mov eax,offset cp_updir+1
		.endif
		scputs( ebx, y, ecx, 7, eax )
	.else
		mov	esi,ecx
		xor	ecx,ecx
		.while	edx
			shrd	eax,edx,10
			inc	ecx
			shr	edx,10
		.endw
		.while	eax >= 000F0000h
			shr	eax,10
			inc	ecx
		.endw
		.data
		strmega db 0,"KMGT"
		.code
		mov	cl,strmega[ecx]
		scputf( ebx, y, esi, 0, "%7u%c", eax, ecx )
	.endif
@2:
	mov	eax,x
	add	eax,l
	sub	eax,14
	push	eax
	add	eax,9
	puttime()
	pop	eax
	putdate()
	ret

putdate:
	mov	x,eax
	mov	ebx,fb
	mov	edi,[ebx].S_FBLK.fb_flag
	movzx	eax,WORD PTR [ebx].S_FBLK.fb_time+2
	mov	esi,eax
	.if	edi & _FB_ROOTDIR
		or edi,_A_SYSTEM
	.endif
	shr	eax,9
	.if	eax >= 20
		sub eax,20
	.else
		add eax,80
	.endif
	push	eax
	mov	eax,esi
	shr	eax,5
	and	eax,000Fh
	push	eax
	mov	eax,esi
	and	eax,001Fh
	push	eax
	fbcolor(ebx)
	scputf( x, y, eax, 0, addr cp_datefrm )
	add	esp,12
	retn

puttime:
	mov	x,eax
	mov	ebx,fb
	mov	eax,[ebx].S_FBLK.fb_time
	shr	eax,5
	and	eax,003Fh
	push	eax
	mov	eax,[ebx].S_FBLK.fb_time
	shr	eax,11
	and	eax,001Fh
	push	eax
	mov	eax,[ebx].S_FBLK.fb_flag
	.if	eax & _FB_ROOTDIR
		or eax,_A_SYSTEM
	.endif
	fbcolor(ebx)
	scputf( x, y, eax, 0, addr cp_timefrm )
	add	esp,8
	retn
fbputfile ENDP

panel_putmini PROC USES esi edi ebx panel:LPPANEL

  local l, x, y, fb,
	VolumeID[32]:BYTE, DiskID,
	FreeBytesAvailable:QWORD,
	TotalNumberOfBytes:QWORD,
	TotalNumberOfFreeBytes:QWORD,
	cFreeBytesAvailable[32]:BYTE,
	cTotalNumberOfBytes[32]:BYTE,
	bstring[64]:BYTE,
	FileSystemName[32]:BYTE

	mov esi,panel
	.if panel_state(esi)

		mov	edi,[esi].S_PANEL.pn_dialog
		.if	[edi].S_DOBJ.dl_flag & _D_ONSCR

			movzx	eax,[edi].S_DOBJ.dl_rect.rc_col
			sub	eax,2
			mov	l,eax
			movzx	eax,[edi].S_DOBJ.dl_rect.rc_x
			inc	eax
			mov	x,eax
			movzx	eax,[edi].S_DOBJ.dl_rect.rc_y
			add	al,[edi].S_DOBJ.dl_rect.rc_row
			sub	al,2
			mov	y,eax
			mov	eax,[esi].S_PANEL.pn_wsub
			mov	eax,[eax].S_WSUB.ws_flag

			.if eax & _W_MINISTATUS

				.if eax & _W_DRVINFO

					mov	edx,x
					mov	ecx,y
					sub	ecx,2
					inc	edx
					.if	cflag & _C_HORIZONTAL

						add edx,40
					.endif
					clear()
					inc	ecx
					clear()
					inc	ecx
					.if	cflag & _C_HORIZONTAL

						sub edx,40
						clear()
					.endif
					mov	edx,x
					add	edx,1
					.if	cflag & _C_HORIZONTAL

						add edx,40
					.endif
					mov	ecx,y
					sub	ecx,2
					scputs( edx, ecx, 0, 0, "Size:\nFree:" )
					add	edx,31
					scputs( edx, ecx, 0, 0, addr cp_byte )
					inc	ecx
					scputs( edx, ecx, 0, 0, addr cp_byte )
					mov	eax,[esi].S_PANEL.pn_wsub
					mov	eax,[eax].S_WSUB.ws_path
					mov	eax,[eax]
					mov	cp_disk,al
					.if	al && ah == ':'

						and	al,not 20h
						mov	cp_disk,al
						sub	al,'A' - 1
						movzx	eax,al
						mov	DiskID,eax

						.if	GetVolumeID( addr cp_disk, addr VolumeID )

							.if _disk_exist( DiskID )

								add	eax,S_DISK.di_name[3]
								mov	edx,eax
								mov	BYTE PTR [eax-1],' '
								strnzcpy( edx, addr VolumeID, 27 )
							.endif

							mov	cl,at_background[B_Panel]
							or	cl,at_foreground[F_Files]
							mov	edx,y
							sub	edx,2
							mov	ebx,x
							inc	ebx

							.if	!(cflag & _C_HORIZONTAL)

								dec edx
							.endif
							scputs( ebx, edx, ecx, 30, addr VolumeID )
						.endif
					.endif

					.if	GetFileSystemName( addr cp_disk, addr FileSystemName )

						mov	cl,at_background[B_Panel]
						or	cl,at_foreground[F_Subdir]
						mov	ebx,y
						sub	ebx,2
						mov	edx,x
						add	edx,12
						.if	!(cflag & _C_HORIZONTAL)

							dec ebx
						.endif
						scputf( edx, ebx, ecx, 24, "%24s", addr FileSystemName )
					.endif

					GetDiskFreeSpaceEx(
						addr cp_disk,
						addr FreeBytesAvailable,
						addr TotalNumberOfBytes,
						addr TotalNumberOfFreeBytes )

					mkbstring( addr cFreeBytesAvailable, FreeBytesAvailable )
					mkbstring( addr cTotalNumberOfBytes, TotalNumberOfBytes )

					mov	cl,at_background[B_Panel]
					or	cl,at_foreground[F_Files]
					mov	edx,x
					mov	ebx,y
					sub	ebx,2
					add	edx,11
					.if	cflag & _C_HORIZONTAL

						add edx,40
					.endif
					scputf( edx, ebx, ecx, 20, addr formats, addr cTotalNumberOfBytes )
					inc	ebx
					scputf( edx, ebx, ecx, 20, addr formats, addr cFreeBytesAvailable )
				.endif

				mov	ah,at_background[B_Panel]
				or	ah,at_foreground[F_Hidden]
				mov	al,' '
				scputw( x, y, l, eax )
				movzx	ecx,ah
				.if	![esi].S_PANEL.pn_fcb_count

					mov	eax,[esi].S_PANEL.pn_wsub
					mov	eax,[eax].S_WSUB.ws_path
					mov	al,[eax]
					scputf( x, y, 0, 0, "[%c:] Empty disk", eax )
				.else
					mov	eax,[esi].S_PANEL.pn_fcb_index
					add	eax,[esi].S_PANEL.pn_cel_index
					wsfblk( [esi].S_PANEL.pn_wsub, eax )
					mov	fb,eax

					.if	panel_selected(esi)

						xor	eax,eax
						xor	edx,edx
						mov	ecx,[esi].S_PANEL.pn_fcb_count
						.if	ecx

							mov	ebx,[esi].S_PANEL.pn_wsub
							.if	[ebx].S_WSUB.ws_fcb != eax

								xor edi,edi
								mov esi,[ebx].S_WSUB.ws_fcb
								.repeat

									mov ebx,[esi]
									.if [ebx].S_FBLK.fb_flag & _FB_SELECTED

										inc edi
										.if !( [ebx].S_FBLK.fb_flag & _A_SUBDIR )

											add eax,DWORD PTR [ebx].S_FBLK.fb_size
											adc edx,DWORD PTR [ebx].S_FBLK.fb_size[4]
										.endif
									.endif
									add esi,4
								.untilcxz
								push	edx
								push	eax
								lea	ebx,bstring
								push	ebx
								call	mkbstring
								mov	cl,at_background[B_Panel]
								or	cl,at_foreground[F_Panel]
								mov	edx,x
								inc	edx
								scputc( edx, y, 37, ' ' )
								scputf( edx, y, ecx, 0, "%s byte in %d file(s)", ebx, edi )
							.endif
						.endif
					.else
						fbputfile( fb, x, y, l )
						mov	eax,fb
						.if	[eax].S_FBLK.fb_flag & _FB_UPDIR

							scputw( x, y, 2, ' ' )
							mov esi,[esi].S_PANEL.pn_wsub
							strfn( [esi].S_WSUB.ws_path )
							mov cl,at_background[B_Panel]
							or  cl,at_foreground[F_System]
							scputs( x, y, ecx, 12, eax )
						.endif
					.endif
				.endif
			.endif
		.endif
	.endif
	ret
clear:
	mov	ah,at_background[B_Panel]
	or	ah,at_foreground[F_Panel]
	mov	al,' '
	scputw( edx, ecx, 37, eax )
	retn

panel_putmini ENDP

	OPTION	PROC: PRIVATE

fbputsize PROC USES ebx edx

	mov	ebx,[ebp+20]
	fbcolor(ebx)
	shl	eax,8
	mov	ecx,eax
	lea	eax,format_10lu

	.if	[ebx].S_FBLK.fb_flag & _A_VOLID

		mov	ch,at_foreground[F_Subdir]
		or	ch,at_background[B_Panel]
		lea	eax,format_02lX
	.endif
	wcputf(edx, [ebp+28], ecx, eax, [ebx].S_FBLK.fb_size)
	ret

fbputsize ENDP

fbputsystem PROC USES ebx

	mov	edx,eax
	mov	ebx,[ebp+20]
	mov	eax,[ebx].S_FBLK.fb_flag

	.if	al & _A_HIDDEN or _A_SYSTEM

		fbcolor(ebx)
		mov	ah,al
		mov	al,'°'
		wcputw( edx, 1, eax )
	.endif
	ret

fbputsystem ENDP

fbputmax PROC USES ebx

	mov	ebx,eax
	mov	al,'¯'
	mov	ah,at_foreground[F_Panel]
	or	ah,at_background[B_Panel]
	wcputw( ebx, 1, eax )
	ret

fbputmax ENDP

fbputtime PROC USES ebx fb, wp

	mov	ebx,fb
	mov	eax,[ebx].S_FBLK.fb_time
	shr	eax,5
	and	eax,003Fh
	push	eax
	mov	eax,[ebx].S_FBLK.fb_time
	shr	eax,11
	and	eax,001Fh
	push	eax
	fbcolor(ebx)
	shl	eax,8
	wcputf( wp, 0, eax, addr cp_timefrm )
	add	esp,8
	ret

fbputtime ENDP

fbputdate PROC USES esi edi ebx fb, wp

	mov	ebx,fb
	mov	edi,[ebx].S_FBLK.fb_flag
	movzx	eax,WORD PTR [ebx].S_FBLK.fb_time+2
	mov	esi,eax

	.if	edi & _FB_ROOTDIR

		or edi,_A_SYSTEM
	.endif

	shr	eax,9
	.if	eax >= 20

		sub eax,20
	.else

		add eax,80
	.endif

	push	eax
	mov	eax,esi
	shr	eax,5
	and	eax,000Fh
	push	eax
	mov	eax,esi
	and	eax,001Fh
	push	eax
	fbcolor(ebx)
	shl	eax,8
	wcputf( wp, 0, eax, addr cp_datefrm )
	add	esp,12
	ret
fbputdate ENDP

fbputdatetime PROC

	push	eax
	add	eax,18
	fbputtime( [ebp+20], eax )
	pop	eax
	fbputdate( [ebp+20], eax )
	ret

fbputdatetime ENDP

fbloadbock PROC

	mov	eax,[ebp+20]
	mov	ebx,eax
	add	eax,S_FBLK.fb_name
	mov	edi,eax
	strlen( eax )
	mov	esi,eax
	mov	ecx,[ebx].S_FBLK.fb_flag
	fbcolor(ebx)
	shl	eax,8
	ret

fbloadbock ENDP

fbput83 PROC USES edx xl, wp, at, fname

	mov	eax,fname
	.if	WORD PTR [eax] == '..'

		xor eax,eax
	.else
		strext( eax )
	.endif

	push	eax
	mov	ecx,xl
	.ifnz
		sub	eax,fname
		.if	al <= cl

			mov cl,al
		.endif
	.endif

	mov	ch,BYTE PTR at
	wcputs( wp, xl, ecx, fname )

	pop	eax
	.if	eax

		inc	eax
		mov	edx,wp
		add	edx,xl
		add	edx,xl
		add	edx,2
		mov	cl,3
		wcputs( edx, 0, ecx, eax )
	.endif
	ret
fbput83 ENDP

putupdir PROC

	.if	ecx & _FB_UPDIR

		wcputs( edx, 0, ebx, addr cp_updir )
	.elseif ecx & _A_SUBDIR

		wcputs( edx, 0, ebx, addr cp_subdir )
	.else
		fbputsize()
	.endif
	ret

putupdir ENDP

	OPTION	PROC: PUBLIC

fbputsl PROC USES esi edi ebx fb, wp, l

	fbloadbock()
	shr	eax,8
	mov	ebx,eax
	mov	eax,l
	.if	eax > 30

		sub eax,30
	.else
		mov eax,8
	.endif

	fbput83( eax, wp, ebx, edi )
	mov	edx,wp
	mov	eax,l
	add	edx,eax
	add	edx,eax

	.if	esi > eax

		mov	eax,edx
		sub	eax,10
		fbputmax()
	.endif

	mov	eax,edx
	sub	eax,8
	fbputsystem()
	ret

fbputsl ENDP

fbputsd PROC USES esi edi ebx fb, wp, l

	fbloadbock()
	mov	ebx,eax
	mov	edx,wp
	add	edx,l
	add	edx,l
	sub	edx,50
	putupdir()
	mov	eax,l
	sub	eax,30
	shr	ebx,8
	fbput83( eax, wp, ebx, edi )
	sub	edx,10
	mov	eax,edx
	fbputsystem()
	mov	eax,l
	sub	eax,26

	.if	esi > eax

		mov eax,edx
		sub eax,2
		fbputmax()
	.endif

	mov	eax,edx
	add	eax,32
	fbputdatetime()
	ret

fbputsd ENDP

fbputll PROC USES esi edi ebx fb, wp, l:DWORD

	fbloadbock()
	mov	ecx,l
	dec	ecx
	mov	ch,ah
	wcputs( wp, l, ecx, edi )
	mov	ch,0
	mov	ebx,wp
	add	ebx,ecx
	add	ebx,ecx

	.if	esi > ecx

		mov	eax,ebx
		sub	eax,2
		fbputmax()
	.endif
	mov	eax,ebx
	fbputsystem()
	ret

fbputll ENDP

fbputld PROC USES esi edi ebx fb, wp, l

  local dist

	xor	eax,eax
	.if	cflag & _C_HORIZONTAL	; Long Horizontal Detail

		mov eax,12
	.endif
	mov	dist,eax
	fbloadbock()
	mov	ebx,eax
	mov	edx,wp
	add	edx,l
	add	edx,l
	sub	edx,38			; Long Vertical Detail
	sub	edx,dist
	putupdir()
	sub	edx,10
	mov	eax,edx
	fbputsystem()
	shr	dist,1
	mov	eax,l
	sub	eax,24
	sub	eax,dist
	shr	ebx,8
	fbput83( eax, wp, ebx, edi )
	mov	eax,l
	sub	eax,21
	sub	eax,dist
	.if	esi > eax
		mov eax,edx
		sub eax,2
		fbputmax()
	.endif
	mov	eax,wp
	add	eax,l
	add	eax,l
	.if	cflag & _C_HORIZONTAL

		sub eax,28
		fbputdatetime()
	.else
		sub eax,16
		fbputdate(fb, eax)
	.endif
	ret
fbputld ENDP

;
; 0. Clear panel
; 1. moving down: all lines moved up 1	 -- last line cleared
; 2. moving up:	  all lines moved down 1 -- first line cleared
;

prect_clear PROC PRIVATE USES esi edi ebx dialog, rc:S_RECT, ptype

  local wl, l

	mov	ebx,dialog
	movzx	eax,rc.rc_col
	mov	l,eax
	add	eax,eax
	mov	wl,eax
	movzx	edi,rc.rc_row
	mov	eax,ptype
	.switch al
	  .case 1	; move one line up
		mov	ecx,l
		lea	eax,[edi-1]
		mov	edi,ebx
		lea	esi,[edi+ecx*2]
		mul	ecx
		mov	ecx,eax
		rep	movsw
		mov	ebx,edi
		mov	edi,1
		.endc
	  .case 2	; move one line down
		mov	ecx,l
		lea	eax,[edi-1]
		mov	esi,ebx
		lea	edi,[esi+ecx*2]
		mul	ecx
		mov	ecx,eax
		dec	eax
		add	eax,eax
		add	edi,eax
		add	esi,eax
		std
		rep	movsw
		cld
		mov	edi,1
	.endsw
	.repeat
		mov	edx,ebx
		mov	ecx,l
		mov	ah,at_foreground[F_Panel]
		or	ah,at_background[B_Panel]
		.repeat
			mov al,[edx]
			.if al != 179

				mov al,' '
				mov [edx],ax
			.endif
			add edx,2
		.untilcxz
		add	ebx,wl
		dec	edi
	.untilz
	ret
prect_clear ENDP

panel_putitem PROC USES esi edi ebx panel:LPPANEL, index:UINT

  local rc:S_RECT, rcxc:S_RECT, dlrc, result, count, dlwp

	mov	al,ASCII_RIGHT
	mov	format_02lX,al
	mov	cp_subdir,al
	mov	cp_updir,al
	mov	al,ASCII_LEFT
	mov	format_02lX[11],al
	mov	cp_subdir[9],al
	mov	cp_updir[9],al
	mov	esi,panel
	mov	edi,[esi].S_PANEL.pn_dialog

	.if	[edi].S_DOBJ.dl_flag & _D_ONSCR

		mov	eax,[edi].S_DOBJ.dl_rect
		mov	rc,eax
		movzx	eax,ax
		mov	dlrc,eax
		add	rc.rc_y,2
		inc	rc.rc_x
		sub	rc.rc_col,2
		sub	rc.rc_row,3
		mov	eax,[esi].S_PANEL.pn_wsub
		mov	eax,[eax].S_WSUB.ws_flag

		.if eax & _W_MINISTATUS

			sub rc.rc_row,2
			.if eax & _W_DRVINFO

				sub rc.rc_row,3
				.if cflag & _C_HORIZONTAL

					inc rc.rc_row
				.endif
			.endif
		.endif

		.if rcalloc( rc, 0 )

			mov	dlwp,eax
			mov	ebx,eax
			mov	eax,[esi].S_PANEL.pn_fcb_count

			.if	eax

				dlclose( [esi].S_PANEL.pn_xl )
				mov	result,eax
				pcell_set(esi)
				rcread(rc, ebx)
				prect_clear(ebx, rc, index)

				xor	edi,edi
				mov	count,-1

				.while	1

					inc	count
					mov	eax,count
					.if	eax >= [esi].S_PANEL.pn_cel_count

						rcwrite( rc, ebx )
						free( ebx )
						.if result

							pcell_show(esi)
						.endif
						panel_putmini(esi)
						.break
					.endif

					pcell_getrect( [esi].S_PANEL.pn_xl, eax )
					sub	eax,dlrc
					sub	eax,00000201h
					mov	rcxc,eax
					movzx	ecx,rc.rc_col
					rcbprc( eax, dlwp, ecx )
					mov	edx,eax

					mov	eax,index
					.if	eax == 1

						mov ecx,[esi].S_PANEL.pn_xl
						mov eax,edi
						add al,[ecx].S_XCEL.xl_rows
						dec al
					.elseif eax == 2

						mov eax,edi
					.else
						mov al,rcxc.rc_y
					.endif
					.continue .if rcxc.rc_y != al

					mov	eax,[esi].S_PANEL.pn_xl
					movzx	eax,[eax].S_XCEL.xl_cpos.rc_col
					push	eax
					mov	eax,[esi].S_PANEL.pn_wsub
					mov	ecx,[eax].S_WSUB.ws_fcb
					mov	eax,[esi].S_PANEL.pn_fcb_index
					add	eax,count
					mov	ecx,[ecx+eax*4]
					push	edx
					push	ecx
					call	[esi].S_PANEL.pn_putfcb
				.endw
			.else
				dlclose( [esi].S_PANEL.pn_xl )
				pcell_set( esi )
				rcread( rc, ebx )
				prect_clear( edi, rc, 0 )
				free( ebx )
			.endif
		.endif
	.endif
	ret
panel_putitem ENDP

panel_putitemax PROC PRIVATE index:UINT

	panel_putitem( esi, index )
	mov	eax,1
	ret

panel_putitemax ENDP

panel_putinfoax PROC PRIVATE index:UINT
	panel_putinfo(esi)
	panel_putitemax(index)
	ret
panel_putinfoax ENDP

panel_putinfozx PROC PRIVATE
	xor	ecx,ecx
	mov	[esi].S_PANEL.pn_cel_index,ecx
	mov	[esi].S_PANEL.pn_fcb_index,ecx
	panel_putinfoax(ecx)
	ret
panel_putinfozx ENDP

panel_reread PROC USES esi panel:LPPANEL

	xor	eax,eax
	mov	esi,panel
	mov	ecx,[esi].S_PANEL.pn_wsub
	.if	[ecx].S_WSUB.ws_flag & _W_VISIBLE

		panel_read(esi)
		panel_putinfoax(0)
		mov	eax,1
	.endif
	ret

panel_reread ENDP

reread_panels PROC

	.if panel_state(panela)

		panel_reread(eax)
	.endif

	.if panel_state(panelb)

		panel_reread(eax)
	.endif
	ret
reread_panels ENDP

panel_redraw PROC USES esi panel:LPPANEL

	xor	eax,eax
	mov	esi,panel
	mov	ecx,[esi].S_PANEL.pn_wsub
	.if	[ecx].S_WSUB.ws_flag & _W_VISIBLE

		prect_open(esi)
		panel_putinfoax(0)

		mov	eax,1
		.if	esi == cpanel

			pcell_show(esi)
		.endif
	.endif
	ret

panel_redraw ENDP

redraw_panel PROC panel:LPPANEL

	mov	ecx,panel
	mov	edx,[ecx].S_PANEL.pn_wsub
	or	[edx].S_WSUB.ws_flag,_W_VISIBLE

	panel_redraw(ecx)
	ret

redraw_panel ENDP

pcell_update PROC USES esi edi ebx panel:LPPANEL

	mov	esi,panel
	.if	dlclose( [esi].S_PANEL.pn_xl )

		pcell_set(esi)
		.if panel_curobj(esi)

			mov	ebx,[esi].S_PANEL.pn_xl
			mov	ebx,[ebx].S_XCEL.xl_rect
			mov	edi,edx

			.if	rcalloc( ebx, 0 )

				push	eax
				rcread( ebx, eax )
				pop	eax
				mov	edx,edi
				mov	edi,eax
				mov	eax,[esi].S_PANEL.pn_xl
				movzx	eax,[eax].S_XCEL.xl_cpos.rc_col
				push	eax
				push	edi
				push	edx
				call	[esi].S_PANEL.pn_putfcb
				rcwrite( ebx, edi )
				free( edi )
			.endif

			mov	eax,esi
			call	pcell_open
			dlshow( [esi].S_PANEL.pn_xl )
			panel_putmini(esi)
			mov eax,1
		.endif
	.endif
	ret

pcell_update ENDP

pcell_select PROC PRIVATE USES esi panel

	.if panel_curobj(panel)

		.if fblk_invert(edx)

			pcell_update(panel)
			mov	eax,1
		.endif
	.endif
	ret

pcell_select ENDP

;----------------------------------------------------------------------------
; Panel Event
;----------------------------------------------------------------------------

S_PEVENT	STRUC
pe_fblk		dd ?
pe_name		dd ?
pe_flag		dd ?
pe_file		db _MAX_PATH dup(?)
pe_path		db _MAX_PATH dup(?)
S_PEVENT	ENDS

	ASSUME	esi: PTR S_PANEL
	ASSUME	edi: PTR S_WSUB

panel_event PROC USES esi edi ebx panel:LPPANEL, event:UINT

  local pe:S_PEVENT

	mov	esi,panel_state(panel)
	mov	eax,event

	.switch eax

	  .case KEY_LEFT

		mov	ecx,[esi].pn_xl
		xor	edx,edx
		movzx	eax,[ecx].S_XCEL.xl_rows ; number of lines in panel
		mov	ecx,[esi].pn_cel_index

		.switch
		  .case eax <= ecx
			sub ecx,eax
			mov edx,ecx
		  .case ecx
			mov [esi].pn_cel_index,edx
			pcell_update(esi)
		  .case [esi].pn_fcb_index == edx
			xor eax,eax
			.endc
		  .case eax <= [esi].pn_fcb_index
			sub [esi].pn_fcb_index,eax
			mov edx,[esi].pn_fcb_index
		  .default
			mov [esi].pn_fcb_index,edx
			panel_putitemax(0)
		.endsw
		.endc

	  .case KEY_RIGHT

		mov	eax,[esi].pn_xl
		movzx	ecx,[eax].S_XCEL.xl_rows
		mov	eax,[esi].pn_cel_index
		add	eax,ecx
		mov	edx,[esi].pn_cel_count
		dec	edx
		.if	eax <= edx

			add [esi].pn_cel_index,ecx
			pcell_update(esi)
		.else
			mov	eax,[esi].pn_cel_index
			add	eax,[esi].pn_fcb_index
			add	eax,ecx
			.if	eax < [esi].pn_fcb_count

				add [esi].pn_fcb_index,ecx
				panel_putitemax(0)
			.elseif [esi].pn_cel_index < edx

				mov [esi].pn_cel_index,edx
				pcell_update(esi)
			.else
				xor eax,eax
			.endif
		.endif
		.endc

	  .case KEY_UP
		xor	eax,eax
		.if	[esi].pn_cel_index != eax

			dec [esi].pn_cel_index
			pcell_update(esi)
		.elseif [esi].pn_fcb_index != eax

			dec [esi].pn_fcb_index
			panel_putitemax(2)
		.endif
		.endc

	  .case KEY_INS
		mov	eax,keyshift
		.if	BYTE PTR [eax] & 3

			xor	eax,eax
			.endc
		.endif
		pcell_select(esi)

		.endcz
		.endc .if !(cflag & _C_INSMOVDN)

	  .case KEY_DOWN
		mov	ecx,[esi].pn_cel_count
		dec	ecx
		xor	eax,eax
		.if	ecx > [esi].pn_cel_index

			inc [esi].pn_cel_index
			pcell_update(esi)
		.elseif ZERO?

			mov	ecx,[esi].pn_fcb_count
			sub	ecx,[esi].pn_fcb_index
			sub	ecx,[esi].pn_cel_index
			.ifs	ecx > 1

				inc [esi].pn_fcb_index
				panel_putitemax(1)
			.endif
		.endif
		.endc

	  .case KEY_END
		mov	edx,[esi].pn_cel_count
		mov	eax,[esi].pn_fcb_count
		.if	edx < eax

			sub	eax,edx
			mov	[esi].pn_fcb_index,eax
			dec	edx
			mov	[esi].pn_cel_index,edx
			panel_putitemax(0)
		.else
			xor	eax,eax
			dec	edx
			.if	edx > [esi].pn_cel_index

				mov [esi].pn_cel_index,edx
				mov [esi].pn_fcb_index,eax
				panel_putitemax(eax)
			.endif
		.endif
		.endc

	  .case KEY_HOME
		xor	eax,eax
		mov	edx,[esi].pn_cel_index
		or	edx,[esi].pn_fcb_index
		.ifnz
			mov [esi].pn_cel_index,eax
			mov [esi].pn_fcb_index,eax
			panel_putitemax(eax)
		.endif
		.endc

	  .case KEY_PGUP
		xor	eax,eax
		mov	edx,[esi].pn_cel_index
		or	edx,[esi].pn_fcb_index
		.ifnz
			.if [esi].pn_cel_index != eax

				mov [esi].pn_cel_index,eax
				pcell_update(esi)
			.else
				mov	ecx,eax
				mov	edx,[esi].pn_xl
				mov	al,[edx+2]
				mov	cl,[edx+3]
				imul	ecx

				.if	eax <= [esi].pn_fcb_index

					sub [esi].pn_fcb_index,eax
				.else
					mov [esi].pn_fcb_index,0
				.endif
				panel_putitemax(0)
			.endif
		.endif
		.endc

	  .case KEY_PGDN
		mov	eax,[esi].pn_cel_count
		dec	eax
		.if	eax != [esi].pn_cel_index

			mov [esi].pn_cel_index,eax
			pcell_update(esi)
		.else

			xor	ecx,ecx
			add	eax,[esi].pn_fcb_index
			inc	eax
			.if	eax != [esi].pn_fcb_count

				mov	eax,[esi].pn_fcb_index
				add	eax,[esi].pn_cel_count
				.if	eax < [esi].pn_fcb_count

					mov eax,[esi].pn_cel_count
					dec eax
					add [esi].pn_fcb_index,eax
					xor eax,eax
					mov [esi].pn_cel_index,eax
					panel_putitemax(eax)
					mov ecx,eax
				.endif
			.endif
			mov	eax,ecx
		.endif
		.endc

	  .case KEY_MOUSEDN
		mov	eax,[esi].pn_xl
		movzx	ecx,BYTE PTR [eax+3]
		mov	eax,[esi].pn_cel_index
		add	eax,[esi].pn_fcb_index
		add	eax,ecx
		.if	eax >= [esi].pn_fcb_count

			.gotosw(KEY_DOWN)
		.endif
		add	[esi].pn_fcb_index,ecx
		panel_putitemax(0)
		.endc

	  .case KEY_MOUSEUP
		mov	eax,[esi].pn_xl
		movzx	eax,BYTE PTR [eax+3]
		.if	eax > [esi].pn_fcb_index

			.gotosw(KEY_UP)
		.endif
		sub	[esi].pn_fcb_index,eax
		panel_putitemax(0)
		.endc

	  .case KEY_ENTER
	  .case KEY_KPENTER

		mov	edi,[esi].pn_wsub
		.endc	.if !panel_curobj(esi)

		mov	pe.pe_name,eax
		mov	pe.pe_fblk,edx
		mov	pe.pe_flag,ecx

		.switch

		  .case ecx & _A_SUBDIR
			mov	eax,[edi].ws_path
			mov	al,[eax+1]
			.if	!(al == ':' || al == '\')

				error_directory()
				.endc
			.endif

			.if	!(ecx & _FB_ARCHIVE)

				historysave()
			.endif
			mov	pe.pe_file,0

			.if	ecx & _FB_UPDIR

				mov	eax,[edi].ws_path
				.if	[edi].ws_flag & _W_ARCHIVE or _W_ROOTDIR

					mov	eax,[edi].ws_arch
					.if	BYTE PTR [eax] == 0

						mov eax,[edi].ws_file
					.endif
				.endif
				push	ecx
				strfn(eax)
				lea	ecx,pe.pe_file
				strcpy(ecx, eax)
				pop	ecx
			.endif

			.if	ecx & _FB_ARCHIVE

				mov	eax,[edi].ws_arch
				.if	ecx & _FB_UPDIR

					.if	BYTE PTR [eax] == 0

						and [edi].ws_flag,not (_W_ARCHIVE or _W_ROOTDIR)
					.else

						mov edi,eax
						reduce_path()
					.endif
				.else

					mov	edi,eax
					add_to_path()
				.endif
			.else

				mov	eax,[edi].ws_path
				.if	byte ptr [eax+1] == ':'

					.if !(pe.pe_flag & _FB_ROOTDIR)

						strfcat( addr pe.pe_path, [edi].ws_path, pe.pe_name )
						.if SetCurrentDirectory( eax )

							GetCurrentDirectory( WMAXPATH, [edi].ws_path )
						.endif
						.if	!eax

							osmaperr()
							error_directory()
							.endc
						.endif
					.else

						mov	eax,[edi].ws_arch
						mov	BYTE PTR [eax],0
						.if	!(ecx & _FB_UPDIR)

							strcpy( [edi].ws_arch, pe.pe_name )
						.endif
						or	[edi].ws_flag,_W_ROOTDIR
					.endif
				.else

					mov	edi,[edi].ws_path
					.if	ecx & _FB_UPDIR

						.if	strrchr( addr [edi+2], '\' )

							reduce_path()
						.endif
					.else
						add_to_path()
					.endif
				.endif
			.endif

			cominit([esi].pn_wsub)
			panel_read(esi)

			.if !( pe.pe_flag & _FB_ROOTDIR )

				xor	eax,eax
				mov	[esi].pn_cel_index,eax
				mov	[esi].pn_fcb_index,eax

				.if	pe.pe_file != al

					.if wsearch([esi].pn_wsub, addr pe.pe_file) != -1

						panel_setid(esi, eax)
					.endif
				.endif
			.endif
			panel_putinfoax(0)
			mov	eax,1
			.endc

		    .case ecx & _FB_ROOTDIR && ecx & _A_VOLID
			;
			; Root directory - change disk
			;
			mov	eax,cpanel
			mov	eax,[eax].S_PANEL.pn_wsub
			and	[eax].S_WSUB.ws_flag,not _W_ROOTDIR
			mov	eax,pe.pe_name
			movzx	eax,BYTE PTR [eax]
			sub	al,'A' - 1
			panel_sethdd( cpanel, eax )
			mov	eax,1
			.endc

		    .case ecx & _FB_ARCHIVE
			;
			; File inside archive
			;
			xor	eax,eax
			.endc

		  .default
			;
			; case file
			;
			lea	ebx,pe.pe_file
			.if	__isexec( strfcat( ebx, [edi].ws_path, pe.pe_name ) )
				;
				; case .EXE, .COM, .BAT, .CMD
				;
				.if	strchr( ebx, ' ' )

					strcpy( addr pe.pe_path, addr cp_quote )
					strcat( strcat( eax, ebx ), addr cp_quote )
					mov ebx,eax
				.endif
				command( ebx )
				mov	eax,1
				.endc
			.endif

			.if CFExpandCmd( ebx, pe.pe_name, "Filetype" )
				;
				; case DZ.INI type
				;
				command( ebx )
				mov eax,1
				.endc
			.endif

			.if strext( ebx )
				;
				; case EDit Info file (.EDI) ?
				;
				.if !_stricmp( eax, ".edi" )

					topenedi( ebx )
					mov eax,1
					.endc
				.endif
			.endif

			;
			; Read 4 byte from file
			;
			.if readword( ebx )

				.if ax == 4B50h ; 'PK'
					;
					; case .ZIP file
					;
					mov eax,_W_ARCHZIP
				.elseif warctest( pe.pe_fblk, eax ) == 1
					;
					; case 7za archive
					;
					mov eax,_W_ARCHEXT
				.else
					xor eax,eax
				.endif
			.endif

			.if	!eax
				;
				; case System OS type
				;
				.if	console & CON_NTCMD

					CreateConsole( ebx, _P_NOWAIT )
					mov eax,1
				.endif
			.else

				mov	ecx,path_a.ws_flag
				or	ecx,path_b.ws_flag
				and	ecx,_W_ARCHIVE
				.ifz
					mov	edi,[esi].pn_wsub
					mov	ecx,[edi].ws_arch
					mov	BYTE PTR [ecx],0
					or	[edi].ws_flag,eax
					mov	edi,[edi].ws_file
					strcpy(edi, pe.pe_name)
					panel_read(esi)
					panel_putinfozx()
					mov	eax,1
				.else
					xor	eax,eax
				.endif
			.endif

		.endsw
		.endc

	  .default
		xor	eax,eax
	.endsw
	ret

add_to_path:
	add	edx,S_FBLK.fb_name
	xor	eax,eax
	.if	[edi] == al

		strcpy( edi, edx )
	.else

		strfcat( edi, eax, edx )
	.endif
	retn

reduce_path:
	mov	edx,edi
	.if	strrchr( edi, '\' )

		mov	edx,eax
		xor	eax,eax
	.endif
	mov	[edx],al
	retn

error_directory:
	errnomsg("Error open directory", "Can't open the directory:\n%s\n\n%s", addr pe.pe_path)
	xor	eax,eax
	retn

panel_event ENDP

	ASSUME	esi: NOTHING
	ASSUME	edi: NOTHING

getmouse PROC PRIVATE
	mousep()
	mov	esi,keybmouse_y
	mov	edi,keybmouse_x
	test	eax,eax
	ret
getmouse ENDP

pcell_move PROC PRIVATE USES esi edi ebx panel

  local fblk, rect:S_RECT, dialog, mouse, dlflag, selected

	mov	ebx,panel
	.if	cpanel_findfirst()

		mov	fblk,edx
		mov	edi,[ebx].S_PANEL.pn_xl
		mov	eax,[edi].S_XCEL.xl_rect
		mov	rect,eax
		mov	selected,panel_selected(ebx)

		.if	mousep() == 1
			;
			; Create a movable object
			;
			mov	eax,keyshift
			mov	eax,[eax]
			and	eax,3		; Shift + Mouse = Move
			mov	mouse,eax	; else Copy

			.if	selected

				mov	rect.rc_col,15
			.else

				mov	eax,[ebx].S_PANEL.pn_wsub
				mov	eax,[eax].S_WSUB.ws_flag
				.if	eax & _W_DETAIL

					sub rect.rc_col,26
				.endif
				.repeat
					mov al,rect.rc_x
					add al,rect.rc_col
					dec al
					mov dl,rect.rc_y
					.break .if getxyc(eax, edx) != ' '
					dec rect.rc_col
				.untilz
				inc	rect.rc_col
			.endif

			inc	rect.rc_col
			dec	rect.rc_x
			movzx	eax,at_background[B_Inverse]
			rcopen(rect, _D_DMOVE or _D_CLEAR or _D_COLOR, eax, 0, 0)
			mov	dialog,eax
			lea	edx,[eax+2]
			mov	ecx,selected

			.if	ecx
				wcputf( edx, 0, 0, addr cp_copyselected, ecx )
			.else
				mov	cl,rect.rc_col
				dec	cl
				mov	eax,fblk
				add	eax,S_FBLK.fb_name
				wcputs( edx, 0, ecx, eax )
			.endif

			mov	dlflag,_D_DMOVE or _D_CLEAR or _D_COLOR or _D_DOPEN
			rcshow( DWORD PTR rect, dlflag, dialog )
			or	dlflag,_D_ONSCR
			mov	ecx,rect
			mov	dl,ch
			scputw( ecx, edx, 1, ' ' )
			add	cl,rect.rc_col
			dec	cl
			mov	eax,'+'
			.if	BYTE PTR mouse

				mov al,' '
			.endif
			scputw( ecx, edx, 1, eax )
			;
			; Move the object
			;
			.while	getmouse() == 1

				mov	eax,edi
				mov	ecx,esi
				.if	al != rect.rc_x || cl != rect.rc_y

					rcmove( addr rect, dialog, dlflag, edi, esi )
				.endif
				mov	eax,keyshift
				mov	eax,[eax]
				and	eax,3
				.if	eax != mouse

					mov	mouse,eax
					mov	ecx,'+'
					.if	eax

						mov ecx,' '
					.endif
					mov	eax,rect
					add	al,rect.rc_col
					dec	al
					mov	dl,ah
					scputw( eax, edx, 1, ecx )
				.endif
			.endw
			rcclose( rect, dlflag, dialog )
			;
			; Find out where the object is
			;
			mov	eax,[ebx].S_PANEL.pn_wsub
			mov	eax,[eax].S_WSUB.ws_flag
			mov	edx,panela

			.if	!(eax & _W_PANELID)

				mov edx,panelb
			.endif
			.if	panel_xycmd( edx, edi, esi )
				.if	mouse
					cmmove()
				.else
					cmcopy()
				.endif
				mov	eax,1
			.else
				.if	statusline_xy( edi, esi, 9, addr MOBJ_Statusline )

					.switch ecx	;
							; 9 cmhelp
							; 8 cmrename
					  .case 7	; 7 cmview
					  .case 6	; 6 cmedit
					  .case 5	; 5 cmcopy
					  .case 4	; 4 cmmove
							; 3 cmmkdir
					  .case 2	; 2 cmdelete
							; 1 cmexit
						mov	eax,[eax+4]
						call	eax
						mov	eax,1
						.endc
					  .default
						xor	eax,eax
					.endsw

				.elseif cflag & _C_COMMANDLINE

					mov	ecx,DLG_Commandline
					movzx	ecx,[ecx].S_DOBJ.dl_rect.rc_y

					.if	ecx == esi

						cmmklist()
						mov eax,1
					.endif
				.endif
			.endif
		.else
			xor	eax,eax
		.endif
	.endif
	ret
pcell_move ENDP

pcell_setxy PROC USES esi edi ebx panel:LPPANEL, xpos:UINT, ypos:UINT

local	rect:S_RECT

	mov	ebx,panel
	mov	esi,ypos
	mov	edi,xpos

	.if	panel_state(ebx)

		.while	1

			mov	xpos,edi
			mov	ypos,esi
			.if	panel_xycmd(ebx, edi, esi) != _XY_FILE

				.continue .if getmouse() == 2

				xor	eax,eax
				.break
			.endif

			mov	rect,edx
			.if	ecx != [ebx].S_PANEL.pn_cel_index

				mov [ebx].S_PANEL.pn_cel_index,ecx
				pcell_update(ebx)
			.endif

			.if	getmouse() != 2

				mousewait(edi, esi, 1)

				.if	!pcell_move(ebx)

					mov	edi,10
					.repeat

						Sleep(16)
						.break .if mousep()

						dec edi
					.untilz

					.if getmouse()

						.if edi == xpos && esi == ypos

							panel_event(ebx, KEY_ENTER)
						.endif
					.endif
				.endif
				.break
			.endif

			pcell_select(ebx)

			movzx	eax,rect.rc_x
			movzx	edx,rect.rc_y
			movzx	ecx,rect.rc_col
			mousewait(eax, edx, ecx)

			mov	esi,keybmouse_y
			mov	edi,keybmouse_x
		.endw
	.endif
	ret

pcell_setxy ENDP

	END
