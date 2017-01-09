include tinfo.inc
include string.inc
include alloc.inc
include errno.inc

	.code

	ASSUME esi: PTR S_TINFO
	ASSUME edx: PTR S_TINFO

tiopen	PROC USES esi ti:PTINFO, tabsize:UINT, flags:UINT

	malloc( SIZE S_TINFO )
	jz	nomem

	mov	edx,edi
	mov	esi,eax
	mov	edi,eax
	mov	ecx,SIZE S_TINFO
	xor	eax,eax
	rep	stosb
	mov	edi,edx
	mov	eax,tabsize
	mov	[esi].ti_tabz,eax

	mov	ah,at_background[B_TextEdit]
	or	ah,at_foreground[F_TextEdit]
	mov	al,' '
	mov	[esi].ti_clat,eax
	mov	[esi].ti_stat,eax
	inc	[esi].ti_cursor.bVisible
	mov	[esi].ti_cursor.dwSize,CURSOR_NORMAL

	;
	; adapt to current screen
	;
	mov	eax,_scrrow
	inc	eax
	mov	[esi].ti_rows,eax
	mov	[esi].ti_DOBJ.dl_rect.rc_row,al
	mov	edx,ti
	mov	eax,_scrcol

	.if	edx && [edx].ti_flag & _T_WINDOWS
		shr	eax,1
		.if	[edx].ti_flag & _T_WINDOWA
			or	[esi].ti_flag,_T_WINDOWB
			mov	[esi].ti_xpos,eax
			mov	[esi].ti_DOBJ.dl_rect.rc_x,al
		.else
			or	[esi].ti_flag,_T_WINDOWA
		.endif
	.endif

	mov	[esi].ti_cols,eax
	mov	[esi].ti_DOBJ.dl_rect.rc_col,al
	mov	[esi].ti_bcol,TIMAXLINE
	mov	[esi].ti_blen,TIMAXFILE

	.if	tialloc( esi )

		.if tigetfile( ti )
			;
			; link to last file
			;
			mov [esi].ti_prev,edx
			mov [edx].ti_next,esi
		.endif

		mov	eax,flags
		or	[esi].ti_flag,eax

		.if	[esi].ti_flag & _T_USEMENUS

			inc [esi].ti_ypos
			inc [esi].ti_cursor.y
			dec [esi].ti_rows
		.endif

		mov	eax,esi
		test	eax,eax
	.else
		free  ( esi )
		jmp	nomem
	.endif
toend:
	ret
nomem:
	ermsg ( 0, addr CP_ENOMEM )
	xor	eax,eax
	jmp	toend
tiopen	ENDP

	ASSUME ebx: PTR S_TINFO
	ASSUME edi: PTR S_TINFO

ticlose PROC USES esi edi ebx ti:PTINFO

	mov	esi,ti
	xor	edi,edi

	.if	[esi].ti_flag & _T_MALLOC

		tifree( esi )
		dlclose( addr [esi].ti_DOBJ )
	.endif

	.if	tigetfile( esi )

		mov	edi,[esi].ti_prev
		mov	ebx,[esi].ti_next
		mov	[esi].ti_prev,0
		mov	[esi].ti_next,0

		.if	ebx && [ebx].ti_prev == esi
			mov [ebx].ti_prev,edi
		.endif

		.if	edi
			.if [edi].ti_next == esi
				mov [edi].ti_next,ebx
			.endif
		.else
			mov edi,ebx
		.endif
	.endif

	free  ( esi )
	mov	eax,edi
	ret
ticlose ENDP

	ASSUME ebx: NOTHING
	ASSUME edi: NOTHING

tihide	PROC ti:PTINFO

	mov	ecx,ti
	.if	ecx
		mov	[ecx].S_TINFO.ti_scrc,0
		dlclose( addr [ecx].S_TINFO.ti_DOBJ )
	.endif
	ret
tihide	ENDP

	ASSUME esi: PTR S_TINFO

tihideall PROC USES esi edi ebx ti:PTINFO

	.if	tigetfile( ti )

		push	ecx
		push	eax
		mov	esi,eax
		mov	edi,edx

		tihide( ti )

		.if	[esi].ti_flag & _T_WINDOWS

			mov	edx,_scrrow
			inc	edx
			mov	eax,_scrcol
			mov	ebx,eax
			mov	bh,dl
			shl	ebx,16
			xor	ecx,ecx

			.while	esi

				push	eax
				push	edx
				tihide( esi )
				pop	edx
				pop	eax

				and	[esi].ti_flag,NOT _T_WINDOWS
				mov	[esi].ti_cols,eax
				mov	[esi].ti_rows,edx
				mov	[esi].ti_DOBJ.dl_rect,ebx
				mov	[esi].ti_xpos,0

				.break .if esi == edi
				mov	esi,[esi].ti_next
			.endw
		.endif

		pop	eax
		pop	ecx
	.endif
	mov	edx,edi
	ret

tihideall ENDP

timenus PROC USES esi ebx ti:PTINFO

	mov	esi,ti

	.if	tistate( esi )

		.if	edx & _D_ONSCR && ecx & _T_USEMENUS

			mov	ebx,eax

			mov	eax,[esi].ti_loff
			add	eax,[esi].ti_yoff
			inc	eax
			push	eax

			mov	eax,[esi].ti_xoff
			add	eax,[esi].ti_boff
			push	eax

			mov	eax,[ebx][4]
			add	al,[ebx].S_DOBJ.dl_rect.rc_col
			sub	al,18
			mov	cl,ah

			scputf( eax, ecx, 0, 0, " col %-3u ln %-6u" )
			add	esp,4*2

			mov	eax,' '
			.if	[esi].ti_flag & _T_MODIFIED
				mov	al,'*'
			.endif
			scputw( 0, ecx, 1, eax )
		.endif
	.endif
	xor	eax,eax
	ret
timenus ENDP

	ASSUME edi: PTR S_DOBJ

tishow	PROC USES esi edi ebx ti:PTINFO

	mov	esi,ti

	.if	esi
		lea	edi,[esi].S_TINFO.ti_DOBJ

		.if	!( [edi].dl_flag & _D_DOPEN )
			mov	edx,[esi].ti_clat

			.if	[esi].ti_flag & _T_USESTYLE

				mov	edx,[esi].ti_stat
			.endif

			shr	edx,8
			.if	rcopen( [edi].dl_rect, _D_CLEAR or _D_BACKG, edx, 0, 0 )

				mov	[edi].dl_wp,eax
				mov	[edi].dl_flag,_D_DOPEN
			.endif
		.endif

		.if	[edi].dl_flag & _D_DOPEN

			dlshow( edi )
			SetCursor( addr [esi].ti_cursor )

			xor	eax,eax
			mov	[esi].ti_scrc,eax

			mov	al,[edi].dl_rect.rc_col
			mov	[esi].ti_cols,eax

			mov	al,[edi].dl_rect.rc_row
			movzx	ebx,[edi].dl_rect.rc_y

			.if	[esi].ti_flag & _T_USEMENUS

				lea	ebx,[ebx+1]
				lea	eax,[eax-1]
			.endif

			mov	[esi].ti_ypos,ebx
			mov	[esi].ti_rows,eax

			.if	!ZERO?

				dec	ebx
				movzx	edx,[edi].dl_rect.rc_x
				mov	ecx,[esi].ti_cols
				mov	ah,at_background[B_Menus]
				or	ah,at_foreground[F_Menus]
				mov	al,' '

				scputw( edx, ebx, ecx, eax )

				inc	edx
				sub	ecx,19
				scpath( edx, ebx, ecx, [esi].ti_file )
			.endif
			tiputs( esi )
		.endif
	.endif
	ret
tishow	ENDP

titogglemenus PROC USES esi ti:PTINFO

	mov	esi,ti

	.if	tistate( esi )

		tihide( esi )

		movzx	edx,[esi].ti_DOBJ.dl_rect.rc_y
		movzx	ecx,[esi].ti_DOBJ.dl_rect.rc_row
		mov	eax,[esi].ti_flag
		xor	eax,_T_USEMENUS
		mov	[esi].ti_flag,eax

		and	eax,_T_USEMENUS
		.if	!ZERO?
			inc	edx
			dec	ecx
		.endif
		mov	[esi].ti_ypos,edx
		mov	[esi].ti_rows,ecx

		tishow( esi )
	.endif
	xor	eax,eax
	ret
titogglemenus ENDP

	ASSUME esi: PTR S_TINFO
	ASSUME edi: PTR S_TINFO

titogglefile PROC USES esi edi ebx old:PTINFO, new:PTINFO

	mov	edi,old
	mov	eax,new
	mov	ebx,edi
	mov	esi,eax

	.if	esi != edi && [esi].ti_flag & _T_TEDIT

		mov	ebx,esi

		.if	!( [edi].ti_flag & _T_WINDOWS )

			flip_buffer:
			tishow( esi )

			.if	[esi].ti_DOBJ.dl_flag & _D_DOPEN

				and	[edi].ti_DOBJ.dl_flag,NOT (_D_DOPEN OR _D_ONSCR)
				free  ( [esi].ti_DOBJ.dl_wp )
				mov	eax,[edi].ti_DOBJ.dl_wp
				mov	[esi].ti_DOBJ.dl_wp,eax
			.else
				mov	ebx,edi
			.endif
		.else

			mov	eax,[esi].ti_DOBJ.dl_rect
			.while	[edi].ti_prev
				mov	edi,[edi].ti_prev
			.endw
			.while	edi
				.if	eax == [edi].ti_DOBJ.dl_rect && \
					[edi].ti_DOBJ.dl_flag & _D_DOPEN && \
					edi != esi

					jmp	flip_buffer
				.endif
				mov	edi,[edi].ti_next
			.endw

			tishow( esi )
		.endif
	.endif
	mov	eax,ebx
	ret
titogglefile ENDP

	END
