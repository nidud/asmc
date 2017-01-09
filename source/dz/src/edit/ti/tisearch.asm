include tinfo.inc
include string.inc
include iost.inc

notfoundmsg	PROTO
cmsearchidd	PROTO :DWORD

	.data

externdef	IDD_Replace:DWORD
externdef	IDD_ReplacePrompt:DWORD
externdef	searchstring:BYTE
externdef	replacestring:BYTE
externdef	fsflag:DWORD

tisearch_off	dd 0
tisearch_line	dd 0
sflag		dd 0

	.code

tisearchsetoff PROC PRIVATE ti:PTINFO

	.if	sflag & IO_SEARCHSET
		xor	eax,eax
		mov	tisearch_off,eax
		mov	tisearch_line,eax
	.else
		mov	edx,ti
		mov	eax,[edx].S_TINFO.ti_boff
		add	eax,[edx].S_TINFO.ti_xoff
		mov	tisearch_off,eax
		mov	eax,[edx].S_TINFO.ti_loff
		add	eax,[edx].S_TINFO.ti_yoff
		mov	tisearch_line,eax
	.endif
	ret

tisearchsetoff ENDP

tisearchcontinue PROC PRIVATE USES esi edi ebx clear_selection, ti:PTINFO

	local offs:DWORD

	.if	!strlen( addr searchstring )
		dec	eax
	.else
		mov	edx,ti
		mov	esi,eax

		tisearchsetoff( edx )
		and	sflag,not IO_SEARCHSET
		mov	eax,tisearch_line
		mov	ebx,eax

		.if	!tigetline( edx, eax )
			dec	eax
		.else
			mov	eax,tisearch_off

			.if	eax <= [edx].S_TINFO.ti_bcnt

				mov	edi,[edx].S_TINFO.ti_lp
				lea	edi,[edi+eax+1]
			.else

				nextline:

				inc	ebx
				mov	eax,ebx

				tigetnextl( edx )

				.if	ZERO?
					call	notfoundmsg
					xor	eax,eax
					dec	eax
					jmp	toend
				.endif

				mov	edi,eax
			 .endif

			.if	!( fsflag & IO_SEARCHCASE )

				.repeat

					mov	al,searchstring
					strchri( edi, eax )
					jz	nextline

					lea	edi,[eax+1]
					_strnicmp( addr searchstring, eax, esi )

				.until	ZERO?
			.else
				.repeat
					mov	al,searchstring
					strchr( edi, eax )
					jz	nextline
					lea	edi,[eax+1]
					strncmp( addr searchstring, eax, esi )
				.until	ZERO?
			.endif

			dec	edi
			sub	edi,[edx].S_TINFO.ti_lp
			mov	tisearch_line,ebx
			mov	tisearch_off,edi

			tialigny( edx, ebx )
			mov	eax,tisearch_off
			inc	tisearch_off
			tialignx( edx, eax )

			ticlipset( edx )

			add	[edx].S_TINFO.ti_cleo,esi
			tiputs( edx )

			xor	eax,eax
			.if	eax != clear_selection
				ticlipset( edx )
				xor	eax,eax
			.endif
		.endif
	.endif
toend:
	ret
tisearchcontinue ENDP

ticontsearch PROC ti:PTINFO
	push	fsflag
	tisearchcontinue( 1, ti )
	pop	eax
	mov	fsflag,eax
	xor	eax,eax
	ret
ticontsearch ENDP

tisearch PROC ti:PTINFO

	.if	cmsearchidd( fsflag )

		mov	eax,fsflag
		and	eax,not IO_SEARCHMASK
		and	edx,IO_SEARCHMASK
		or	eax,edx
		mov	fsflag,eax
		mov	sflag,eax

		ticontsearch( ti )
	.endif
	ret
tisearch ENDP

tisearchxy PROC ti:PTINFO

	local	linebuf[128]:BYTE

	.if	scgetword( addr linebuf )

		strcpy( addr searchstring, eax )
		tisearch( ti )
	.endif
	ret
tisearchxy ENDP

;-----------------------------------------------------------------------------
; Replace
;-----------------------------------------------------------------------------

ID_YES	equ	1
ID_ALL	equ	2
ID_NO	equ	3

iddreplaceprompt PROC PRIVATE USES ebx ti:PTINFO

	mov	eax,1
	mov	ebx,ti

	.if	[ebx].S_TINFO.ti_flag & _T_PROMPTONREP

		.if	rsmodal( IDD_ReplacePrompt )

			lea	edx,[eax-1]
			mov	ebx,IDD_ReplacePrompt
			mov	[ebx].S_ROBJ.rs_index,dl
			mov	ebx,ti

			.if	eax == ID_ALL
				xor [ebx].S_TINFO.ti_flag,_T_PROMPTONREP
			.endif
		.endif
	.endif
	test	eax,eax
	ret
iddreplaceprompt ENDP

ID_OLDSTRING	equ 1*16
ID_NEWSTRING	equ 2*16
ID_USECASE	equ 3*16
ID_PROMPT	equ 4*16
ID_CURSOR	equ 5*16
ID_GLOBAL	equ 6*16
ID_OK		equ 7
ID_CHANGEALL	equ 8

iddreplace PROC PRIVATE USES ebx

	.if	rsopen( IDD_Replace )
		mov	ebx,eax
		mov	[ebx].S_TOBJ.to_count[ID_OLDSTRING],128 shr 4
		mov	[ebx].S_TOBJ.to_count[ID_NEWSTRING],128 shr 4
		mov	eax,offset searchstring
		mov	[ebx].S_TOBJ.to_data[ID_OLDSTRING],eax
		mov	eax,offset replacestring
		mov	[ebx].S_TOBJ.to_data[ID_NEWSTRING],eax
		mov	eax,fsflag
		mov	dl,_O_FLAGB
		.if	eax & IO_SEARCHCASE
			or	[ebx][ID_USECASE],dl
		.endif
		.if	eax & _T_PROMPTONREP
			or	[ebx][ID_PROMPT],dl
		.endif
		mov	edx,_O_RADIO
		.if	eax & IO_SEARCHCUR
			or	[ebx][ID_CURSOR],dl
			xor	edx,edx
		.endif
		or	[ebx][ID_GLOBAL],dl
		dlinit( ebx )
		.if	rsevent( IDD_Replace, ebx )
			mov	eax,fsflag
			and	eax,not (IO_SEARCHMASK or _T_PROMPTONREP)
			mov	dl,_O_FLAGB
			.if	[ebx][ID_USECASE] & dl
				or	eax,IO_SEARCHCASE
			.endif
			.if	[ebx][ID_PROMPT] & dl
				or	eax,_T_PROMPTONREP
			.endif
			mov	edx,IO_SEARCHSET
			.if	BYTE PTR [ebx][ID_CURSOR] & _O_RADIO
				mov	edx,IO_SEARCHCUR
			.endif
			or	edx,eax
			xor	eax,eax
			.if	searchstring != al
				inc	eax
			.endif
		.endif
		push	edx
		dlclose( ebx )
		mov	eax,edx
		pop	edx
	.endif
	test	eax,eax
	ret
iddreplace ENDP

tireplace PROC USES esi edi ebx ti:PTINFO

	mov	esi,ti
	mov	eax,_T_PROMPTONREP
	or	[esi].S_TINFO.ti_flag,eax
	call	iddreplace

	.if	!ZERO?
		mov	fsflag,edx
		mov	sflag,edx
		.if	eax == ID_CHANGEALL || !( edx & _T_PROMPTONREP )
			and	[esi].S_TINFO.ti_flag,not _T_PROMPTONREP
		.endif
		.while	!tisearchcontinue( 0, esi )

			.break .if !iddreplaceprompt( esi )
			.continue .if eax == ID_NO

			ticlipdel( esi )		; delete text
			lea	edi,replacestring	; add new text
			mov	al,[edi]
			.while	al
				tiputc( esi, eax )
				inc	edi
				mov	al,[edi]
			.endw
		.endw
	.endif
	tiputs( esi )
	ticlipset( esi )
	xor	eax,eax
	ret
tireplace ENDP

	END
