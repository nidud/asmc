include tinfo.inc
include alloc.inc
include string.inc

	.data
	externdef crctab:DWORD
	old_boff dd 0
	old_loff dd 0

	.code

	ASSUME	edx: PTR S_TINFO
	ASSUME	esi: PTR S_TINFO

tiputl PROC PRIVATE USES esi edi ebx wc, line, ti:PTR S_TINFO

  local loff,	; adress of line
	llen,	; length of line
	clst,	; clip start
	clen	; clip end

	mov	edx,ti
	mov	eax,[edx].ti_clat
	.if	[edx].ti_flag & _T_USESTYLE
		mov	eax,[edx].ti_stat
	.endif

	mov	ebx,wc
	mov	edi,ebx
	mov	ecx,[edx].ti_cols
	rep	stosw

	mov	edi,ebx
	mov	eax,line

	.if	eax
		tigetnextl( edx )
	.else
		tigetline( edx, eax )
	.endif

	.ifnz
		mov	esi,eax
		mov	llen,ecx

		.if	ecx > [edx].ti_boff

			mov	loff,esi
			add	esi,[edx].ti_boff
			mov	ecx,[edx].ti_cols

			.repeat
				mov	al,[esi]
				add	esi,1

				.break .if !al

				.if	al == TITABCHAR
					mov	al,' '
				.endif

				.if	al == 9 && !( [edx].ti_flag & _T_SHOWTABS )
					mov	al,' '
				.endif

				mov	[edi],al
				add	edi,2
			.untilcxz

			.if	[edx].ti_flag & _T_USESTYLE

				mov	eax,loff

				.if	BYTE PTR [eax]

					tistyle(edx, line, eax, llen, wc)
				.endif
			.endif
		.endif

		xor	eax,eax
		mov	clen,eax	; clip end to	0000
		dec	eax		; clip start to FFFF
		mov	clst,eax


		.if	tiselected( ti )

			xor	edx,edx
			mov	esi,ti
			mov	eax,line

			.if	eax >= [esi].ti_clsl && eax <= [esi].ti_clel

				.if	eax == [esi].ti_clsl

					dec	edx
					mov	clen,edx
					push	eax
					mov	eax,[esi].ti_clso
					mov	edx,[esi].ti_boff
					.if	eax >= edx

						sub	eax,edx
					.else
						xor	eax,eax
					.endif
					mov	clst,eax
					pop	eax

					.if	eax == [esi].ti_clel

						mov	eax,[esi].ti_cleo
						sub	eax,[esi].ti_boff
						mov	clen,eax
					.endif
				.else
					mov	clst,edx

					.if	eax == [esi].ti_clel

						mov	eax,[esi].ti_cleo
						sub	eax,[esi].ti_boff
						mov	clen,eax
					.else

						dec	edx
						mov	clen,edx
					.endif
				.endif

				mov	ecx,[esi].ti_cols
				mov	edi,wc
				inc	edi
				mov	al,at_background[B_Inverse]

				xor	ebx,ebx
				mov	edx,clst

				.repeat
					.if	ebx < edx

						add	edi,1
					.else
						.break .if ebx >= clen

						mov	[edi],al
						add	edi,1
					.endif
					add	ebx,1
					add	edi,1
				.untilcxz
			.endif
		.endif
	.endif
	mov	eax,1
	ret
tiputl	ENDP

tiputs	PROC USES esi edi ebx ti:PTR S_TINFO

  local wc, ci, wcols, bz:COORD, rc:SMALL_RECT, cursor:S_CURSOR

	mov	esi,ti

	mov	eax,[esi].ti_xpos
	add	eax,[esi].ti_xoff
	mov	ecx,[esi].ti_ypos
	add	ecx,[esi].ti_yoff

	mov	cursor.x,ax
	mov	cursor.y,cx
	mov	cursor.bVisible,1
	mov	cursor.dwSize,CURSOR_NORMAL
	SetCursor( addr cursor )

	mov	eax,[esi].ti_cols
	mul	[esi].ti_rows
	shl	eax,1
	mov	ebx,eax

	lea	eax,[eax+ebx*2]
	alloca( eax )
	mov	wc,eax
	mov	esi,eax

	add	eax,ebx
	mov	ci,eax

	lea	ecx,[ebx+ebx*2]
	mov	edi,esi
	xor	eax,eax
	rep	stosb
	mov	edx,ti
	mov	eax,[edx].ti_cols
	add	eax,eax
	mov	wcols,eax

	mov	edi,[edx].ti_rows
	mov	ebx,[edx].ti_loff

	.if	ebx
		lea	eax,[ebx-1]
		tigetline( edx, eax )
		jz	toend
	.endif

	.repeat

		tiputl( esi, ebx, ti )
		test	eax,eax
		jz	toend

		add	esi,wcols
		add	ebx,1
		sub	edi,1

	.until	ZERO?

	mov	esi,ti
	mov	ecx,[esi].ti_cols
	mov	bz.x,cx
	mov	eax,[esi].ti_xpos
	mov	rc.Left,ax
	add	eax,ecx
	dec	eax
	mov	rc.Right,ax
	mov	eax,[esi].ti_ypos
	mov	rc.Top,ax
	add	eax,[esi].ti_rows
	dec	eax
	mov	rc.Bottom,ax

	mov	eax,[esi].ti_rows
	mov	bz.y,ax
	mul	ecx
	mov	ecx,eax
	mov	edx,wc
	mov	edi,ci

	.repeat
		mov	ax,[edx]
		mov	[edi],al
		mov	[edi+2],ah
		add	edi,4		; SIZE CHAR_INFO
		add	edx,2
	.untilcxz

	mov	edx,ti
	mov	eax,[edx].ti_boff
	mov	ebx,old_boff
	mov	old_boff,eax
	sub	eax,ebx
	mov	ecx,[edx].ti_loff
	mov	ebx,old_loff
	mov	old_loff,ecx
	sub	ecx,ebx
	sub	eax,ecx

	push	eax
	movzx	eax,WORD PTR bz
	movzx	ecx,WORD PTR bz+2
	mul	ecx
	add	eax,eax
	mov	edx,wc
	mov	ecx,eax

	xor	eax,eax
	xor	ebx,ebx
	.while	ecx
		mov	bl,al
		xor	bl,[edx]
		shr	eax,8
		xor	eax,crctab[ebx*4]
		add	edx,1
		sub	ecx,1
	.endw

	mov	edx,ti
	mov	ebx,[edx].ti_scrc
	mov	[edx].ti_scrc,eax
	sub	eax,ebx
	pop	ecx
	add	eax,ecx

	.if	!ZERO?

		WriteConsoleOutput( hStdOutput, ci, bz, 0, addr rc )
	.endif
toend:
	mov	edx,ti
	ret
tiputs	ENDP

	END
