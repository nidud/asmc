include tinfo.inc

extern	IDD_TEReload2:DWORD

	.code

	ASSUME	edx: PTR S_TINFO

tiseto	PROC USES edi ti:PTINFO

	mov	edx,ti

	mov	eax,[edx].ti_loff		; test current line
	add	eax,[edx].ti_yoff

	.if	eax > [edx].ti_lcnt
		xor	eax,eax
		mov	[edx].ti_loff,eax
		mov	[edx].ti_yoff,eax
	.endif

	.if	ticurlp( edx )			; get pointer to current line
		mov	edi,eax

		add	eax,[edx].ti_boff	; strip space from end
		add	eax,[edx].ti_xoff
		push	ecx
		tistripend( eax )
		pop	ecx

		mov	eax,[edx].ti_boff	; test if char is visible
		add	eax,[edx].ti_xoff

		.if	eax > ecx

			add	edi,ecx		; length of line
			sub	eax,ecx
			mov	ecx,eax		; ECX to pad count
			mov	eax,' '
			rep	stosb
			mov	[edi],ah
			mov	eax,1
		.else
			xor	eax,eax
		.endif
	.endif
	ret
tiseto	ENDP

tireload PROC USES esi ti:PTINFO

	mov	esi,ti
	.if	[esi].S_TINFO.ti_flag & _T_MODIFIED

		.if	!rsmodal( IDD_TEReload2 )
			xor	eax,eax
			jmp	toend
		.endif
	.endif

	timemzero( esi )
	.if	tiread( esi )
		tiseto( esi )
		tiputs( esi )
		mov	eax,1
	.endif

toend:
	ret
tireload ENDP

	END
