include tinfo.inc

extern	IDD_TEReload:DWORD

	.code

	ASSUME esi: PTR S_TINFO

tevent	PROC USES esi edi

	mov	esi,tinfo

	.while	1

		tiseto( esi )
		tiputs( esi )

		.while	1

			.if	tiftime( esi )

				.if	eax != [esi].ti_time

					.if	rsmodal( IDD_TEReload )

						timemzero( esi )
						tiread( esi )

						mov	edi,KEY_ESC
						jz	toend

						tiseto( esi )
						tiputs( esi )
					.endif
				.endif
			.endif

			timenus( esi )
			tgetevent()
			mov	edi,eax
			tihandler()
			mov	esi,tinfo

			.break .if eax == _TI_NOTEVENT

			cmp	eax,_TI_RETEVENT
			je	toend
		.endw

		tievent( esi, edi )
	.endw

toend:
	mov	edx,esi
	mov	eax,edi
	ret

tevent	ENDP

	END
