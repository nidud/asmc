include tinfo.inc

	.code

tsplitscreen PROC USES esi edi ebx ebp

	.if	tigetfile( tinfo )

		mov	esi,eax
		mov	edi,edx

		ASSUME	esi:PTR S_TINFO

		mov	edx,_scrrow
		inc	edx
		mov	ebx,_scrcol
		.if	ebx == [esi].ti_cols && ecx > 1
			shr	ebx,1
		.endif

		mov	ebp,ebx
		mov	bh,dl
		shl	ebx,16

		.while	esi

			push	edx
			tihide( esi )
			pop	edx
			movzx	ecx,bl
			and	[esi].ti_flag,NOT _T_WINDOWS
			mov	[esi].ti_cols,ebp
			mov	[esi].ti_rows,edx
			mov	[esi].ti_DOBJ.dl_rect,ebx
			mov	[esi].ti_xpos,ecx

			.if	ebp != _scrcol
				mov	eax,ebp
				.if	[esi].ti_xoff >= eax
					dec	eax
					mov	[esi].ti_xoff,eax
					mov	[esi].ti_cursor.x,ax
					inc	eax
				.endif

				.if	ecx
					or	[esi].ti_flag,_T_WINDOWB
					xor	bl,bl
				.else
					or	[esi].ti_flag,_T_WINDOWA
					mov	bl,al
				.endif
			.endif

			.break .if esi == edi
			mov	esi,[esi].ti_next
		.endw

		mov	esi,tinfo
		mov	eax,_scrcol
		.if	eax != [esi].ti_cols
			mov	eax,[esi].ti_next
			mov	ecx,[esi].ti_prev
			.if	eax
				tishow( eax )
			.elseif ecx
				tishow( ecx )
			.endif
		.endif
		tishow( esi )
		mov	eax,_TI_CONTINUE

		ASSUME	esi:NOTHING

	.endif
	ret

tsplitscreen ENDP

	END
