include tinfo.inc
include direct.inc
include errno.inc
include alloc.inc
include string.inc
include ltype.inc
include dzlib.inc

	.code

;
; Validate tinfo
; return CX .ti_flag, DX .dl_flag, AX dialog
;
tistate PROC ti:PTINFO

	mov edx,ti
	xor eax,eax

	.if edx

		mov ecx,[edx].S_TINFO.ti_flag
		lea edx,[edx].S_TINFO.ti_DOBJ

		.if ecx & _T_TEDIT

			mov eax,edx
			movzx edx,[edx].S_DOBJ.dl_flag
		.endif
	.endif
	ret

tistate ENDP

;-----------------------------------------------------------------------------
; Alloc file buffer
;-----------------------------------------------------------------------------

	ASSUME esi: PTR S_TINFO

tialloc PROC USES esi ti:PTINFO

	mov	esi,ti

	mov	eax,[esi].ti_blen
	add	eax,TIMAXLINE*2+_MAX_PATH*2+STYLESIZE

	.if	malloc( eax )

		or	[esi].ti_flag,_T_MALLOC or _T_TEDIT
		mov	[esi].ti_bp,eax
		add	eax,[esi].ti_blen
		mov	[esi].ti_lp,eax
		add	eax,TIMAXLINE*2
		mov	[esi].ti_style,eax
		add	eax,STYLESIZE
		mov	[esi].ti_file,eax
		mov	eax,1
	.else

		ermsg ( 0, addr CP_ENOMEM )
		xor	eax,eax
	.endif
	ret
tialloc ENDP

tifree	PROC USES esi ti:PTINFO

	mov	esi,ti

	mov	eax,[esi].ti_flag
	.if	eax & _T_MALLOC

		xor	eax,_T_MALLOC
		mov	[esi].ti_flag,eax
		free  ( [esi].ti_bp )
	.endif
	ret
tifree	ENDP

tirealloc PROC USES esi edi ebx edx ti:PTINFO

	mov	esi,ti
	mov	edi,[esi].ti_bp
	mov	ebx,[esi].ti_blen
	add	[esi].ti_blen,TIMAXFILE

	.if	!tialloc( esi )
		mov	[esi].ti_blen,ebx
	.else
		memcpy( [esi].ti_bp, edi, ebx )
		add	ebx,edi
		memcpy( [esi].ti_lp, ebx, TIMAXLINE * 2 + _MAX_PATH * 2 + STYLESIZE )
		free  ( edi )
		sub	[esi].ti_flp,edi
		mov	eax,[esi].ti_bp
		add	[esi].ti_flp,eax
		mov	eax,edi
		test	eax,eax
	.endif

	ret
tirealloc ENDP

	ASSUME esi: NOTHING

timemzero PROC USES edi ti:PTINFO

	mov	eax,ti
	mov	ecx,[eax].S_TINFO.ti_blen
	mov	edx,[eax].S_TINFO.ti_bp
	mov	edi,edx
	add	ecx,TIMAXLINE*2
	xor	eax,eax
	rep	stosb
	mov	eax,edx
	ret

timemzero ENDP

	ASSUME	edx: PTR S_TINFO

;------------------------------------------------------------------------------
; Get line from buffer
;------------------------------------------------------------------------------

tigetline PROC USES esi edi ebx ti:PTINFO, line_id:UINT

	mov	eax,line_id			; ARG: line id
	mov	ebx,eax
	mov	edx,ti
	mov	edi,[edx].ti_bp			; file is string[MAXFILESIZE]
	.if	eax				; first line ?
		mov	ecx,[edx].ti_curl	; current line ?
		.if	eax == ecx		; save time on repeated calls..
			mov edi,[edx].ti_flp	; pointer to current line in buffer
		.else
			mov esi,eax		; loop from EDI to line id in EAX
			.repeat
				strchr( edi, 10 )
				jz	error
				lea	edi,[eax+1]
				dec	esi
			.until	ZERO?
		.endif
	.endif

	mov	[edx].ti_flp,edi		; set current line pointer
	.if	strchr( edi, 10 )		; get length of line
		.if	BYTE PTR [eax-1] == 0Dh
			dec	eax
		.endif
		sub	eax,edi
	.else
		strlen( edi )
	.endif

	mov	[edx].ti_fbcnt,eax
	mov	[edx].ti_curl,ebx
	mov	ecx,eax
	mov	esi,edi
	mov	edi,[edx].ti_lp
	xor	eax,eax

	.if	ecx < [edx].ti_blen
		mov	[edi],eax
		mov	ebx,[edx].ti_tabz	; create mask for tabs in EBX
		dec	ebx
		and	ebx,TIMAXTABSIZE-1
		.while	ecx
			lodsb
			.if	eax == 9
				.repeat
					mov [edi],ax
					inc edi
					mov eax,TITABCHAR
				.until !( edi & ebx )
			.else

				mov	[edi],ax
				inc	edi
			.endif
			dec	ecx
		.endw

		mov	eax,[edx].ti_lp		; set expanded line size
		mov	ecx,edi
		sub	ecx,eax
		mov	[edx].ti_bcnt,ecx
	.endif
toend:
	test	eax,eax
	ret
error:
	mov	[edx].ti_curl,eax
	mov	edi,[edx].ti_bp
	mov	[edx].ti_flp,edi
	jmp	toend
tigetline ENDP

tigetnextl PROC USES esi edi ebx ti:PTINFO

	xor	eax,eax
	mov	edx,ti
	mov	[edx].ti_curl,eax
	mov	edi,[edx].ti_flp	; next = current + size + 0D 0A
	add	edi,[edx].ti_fbcnt
	mov	al,[edi]

	.if	eax
		.if	al == 0Dh
			inc	edi
			mov	al,[edi]
		.endif
		.if	al != 0Ah
			xor	eax,eax
		.else
			inc	edi
			mov	[edx].ti_flp,edi
			strchr( edi,10 )
			.if	ZERO?
				strlen( edi )
			.else
				.if	BYTE PTR [eax-1] == 0Dh
					dec	eax
				.endif
				sub	eax,edi
			.endif

			mov	[edx].ti_fbcnt,eax
			mov	ecx,eax
			mov	esi,edi
			mov	edi,[edx].ti_lp
			xor	eax,eax
			mov	[edi],eax

			.if	ecx < [edx].ti_blen

				mov	ebx,[edx].ti_tabz
				dec	ebx
				and	ebx,TIMAXTABSIZE-1

				.while	ecx
					lodsb
					stosb
					.if	al == 9
						mov	eax,TITABCHAR
						.while	edi & ebx
							stosb
						.endw
					.endif
					dec	ecx
				.endw

				mov	[edi],ah
				mov	eax,[edx].ti_lp
				mov	ecx,edi
				sub	ecx,eax
				mov	[edx].ti_bcnt,ecx
			.else
				xor	eax,eax
			.endif
		.endif
	.endif
	test	eax,eax
	ret
tigetnextl ENDP

ticurlp PROC USES esi edi ti:PTINFO

	mov	edx,ti			; current line =
	mov	eax,[edx].ti_loff	; line offset -- first line on screen
	add	eax,[edx].ti_yoff	; + y offset -- cursory()

	.if	tigetline( edx, eax )

		mov	esi,eax
		xor	ecx,ecx			; just in case..
		add	eax,[edx].ti_bcol	; terminate line
		mov	[eax-1],cl
		;
		; cursor->x may be above lenght of line
		; so space is added up to current x-pos
		;
		.repeat
			mov	eax,[edx].ti_boff	; current line offset =
			add	eax,[edx].ti_xoff	; buffer offset -- start of screen line
			.break .if eax < [edx].ti_bcol	; + x offset -- cursorx()
			.if	[edx].ti_xoff != ecx
				dec	[edx].ti_xoff
			.else
				.break .if [edx].ti_boff == ecx
				dec	[edx].ti_boff
			.endif
		.until	0
		mov	edi,eax
		.if	strlen( esi ) < edi
			mov	ecx,' '
			.repeat
				mov	[esi+eax],cx
				inc	eax
			.until	eax >= edi
			mov	ecx,eax
		.endif
		mov	[edx].ti_bcnt,eax	; byte count in line
		mov	eax,esi
	.endif
	test	eax,eax
	ret
ticurlp ENDP

ticurcp PROC ti:PTINFO
	;
	; current pointer = current line + line offset
	;
	.if	ticurlp( ti )
		add eax,[edx].ti_boff
		add eax,[edx].ti_xoff
	.endif
	ret

ticurcp ENDP

tiexpandline PROC USES esi edi ebx eax ti:PTINFO, line:LPSTR

	mov	edx,ti
	mov	eax,line
	mov	ebx,[edx].ti_tabz

	.if	[edx].ti_flag & _T_USETABS

		dec	bl
		and	ebx,TIMAXTABSIZE-1
		mov	esi,eax
		mov	edi,eax
		mov	ecx,[edx].ti_bcol
		add	ecx,esi
		dec	ecx
		.while	1
			lodsb
			.break .if al < 1

			.if	al == 9
				stosb	; insert TAB char
					; insert "spaces" to next Tab offset
				.break .if edi >= ecx
				.while	esi & ebx
					strshr( esi, TITABCHAR )
					.break .if edi >= ecx
					inc	esi
					mov	edi,esi
				.endw
				.continue
			.endif

			.break .if edi == ecx
			stosb
		.endw
		mov	BYTE PTR [edi],0
	.endif
	ret
tiexpandline ENDP

	ASSUME edx: NOTHING

tioptimalfill PROC USES esi edi ebx ecx ti:PTINFO, line_offset:LPSTR

	mov	esi,line_offset
	strlen( esi )
	mov	ecx,eax

	mov	edx,ti
	mov	eax,[edx].S_TINFO.ti_flag
	and	eax,_T_OPTIMALFILL or _T_USETABS
	cmp	eax,_T_OPTIMALFILL or _T_USETABS
	mov	eax,esi
	jne	toend
	cmp	ecx,5
	jb	toend

	push	esi
	xor	eax,eax
do:
	mov	ebx,esi
	mov	al,[esi]
	inc	esi
	test	al,al
	jz	break
	cmp	al,39
	je	quote
	cmp	al,'"'
	je	quote
	cmp	al,10
	je	break
	cmp	al,13
	je	break
	test	BYTE PTR _ltype[eax+1],_SPACE
	jz	do
@@:
	lodsb
	cmp	al,10
	je	break
	cmp	al,13
	je	break
	test	BYTE PTR _ltype[eax+1],_SPACE
	jnz	@B
@@:
	dec	esi
next:
	mov	edi,ebx
	sub	edi,[esp]
	mov	ecx,edi
	add	edi,8
	and	edi,-8
	sub	edi,ecx
	lea	ecx,[esi+1]
	sub	ecx,ebx
	cmp	ecx,3;4
	jb	done
	cmp	ecx,edi
	jbe	done
	mov	BYTE PTR [ebx],9
	inc	ebx
	mov	ecx,edi
	dec	ecx
	jz	next
	mov	edi,ebx
	add	ebx,ecx
	mov	al,TITABCHAR
	rep	stosb
	jmp	next
done:
	test	ecx,ecx
	jz	do
	dec	ecx
	jz	do
	mov	al,' '
	mov	edi,ebx
	rep	stosb
	jmp	do
break:
	pop	eax
toend:
	ret
quote:
	mov	bl,al
@@:
	mov	al,[esi]
	inc	esi
	test	al,al
	jz	break
	cmp	al,bl
	jne	@B
	jmp	do
tioptimalfill ENDP

	ASSUME	edx: PTR S_TINFO
	ASSUME	ecx: PTR S_TIOST

__st_open PROC ti:PTINFO, ts:PTIOST, char:UINT

	.if	ticurcp( ti )

		mov	ecx,ts
		mov	[ecx].ts_line_ptr,eax
		mov	[ecx].ts_index,0

		mov	eax,char
		mov	[ecx].ts_char,al

		mov	eax,[edx].ti_flp
		mov	[ecx].ts_file_ptr,eax
		add	eax,[edx].ti_fbcnt
		mov	[ecx].ts_file_end,eax

		mov	eax,[edx].ti_lp
		add	eax,[edx].ti_bcol
		mov	[ecx].ts_buffer,eax
	.endif
	ret

__st_open ENDP

__st_putc PROC USES ecx ts:PTIOST, char:UINT

	mov	eax,ts
	mov	ecx,[eax].S_TIOST.ts_index

	.if	ecx < TIMAXLINE

		add	ecx,[eax].S_TIOST.ts_buffer
		inc	[eax].S_TIOST.ts_index
		movzx	eax,BYTE PTR char
		mov	[ecx],ax
		clc
	.else
		xor	eax,eax
		stc
	.endif
	ret

__st_putc ENDP

	ASSUME	ecx: NOTHING
	ASSUME	esi: PTR S_TIOST

__st_copy2 PROC USES esi ebx ti:PTINFO, ts:PTIOST

	mov	esi,ts
	mov	edx,ti

	mov	ecx,[esi].ts_line_ptr
	mov	ebx,[edx].ti_lp
	sub	ecx,ebx
	.repeat
		mov	al,[ebx]
		.if	al != TITABCHAR
			__st_putc( esi, eax )
			jc	toend
		.endif
		inc	ebx
	.untilcxz
	clc
toend:
	ret
__st_copy2 ENDP

__st_copy PROC USES esi ti:PTINFO, ts:PTIOST

	mov	esi,ts
	mov	edx,ti
	mov	ecx,[esi].ts_line_ptr

	.if	BYTE PTR [ecx] == TITABCHAR

		mov	eax,2000h + TITABCHAR
		mov	[ecx],ah

		.if	[ecx+1] == al
			mov	BYTE PTR [ecx],9
		.endif

		.if	ecx > [edx].ti_lp

			.repeat
				dec	ecx
				.break .if [ecx] != al
				mov	[ecx],ah
			.until	ecx == [edx].ti_lp

			.if	BYTE PTR [ecx] == 9
				mov	[ecx],ah
			.endif
		.endif
	.endif

	__st_copy2( edx, esi )

	ret
__st_copy ENDP

	ASSUME	edx: PTR S_TIOST

__st_trim PROC USES edx ecx ts:PTIOST

	mov	edx,ts
	mov	ecx,[edx].ts_index
	mov	eax,[edx].ts_buffer

	.while	ecx
		sub	ecx,1

		.break .if BYTE PTR [eax+ecx] != ' '

		mov	BYTE PTR [eax+ecx],0
		mov	[edx].ts_index,ecx
	.endw
	ret

__st_trim ENDP

	ASSUME	edx: PTR S_TINFO

__st_flush PROC USES esi edi ebx ti:PTINFO, ts:PTIOST

	mov	esi,ts
	mov	edx,ti

	.if	[edx].ti_flag & _T_OPTIMALFILL && [esi].ts_index

		tiexpandline ( edx, [esi].ts_buffer )
		tioptimalfill( edx, [esi].ts_buffer )

		mov	ecx,eax
		mov	ebx,eax
		mov	[esi].ts_index,0

		.while	1
			mov	al,[ecx]
			.break .if !al
			.if	al != TITABCHAR
				mov	[ebx],al
				inc	ebx
				inc	[esi].ts_index
			.endif
			inc	ecx
		.endw

	.endif

	mov	eax,[esi].ts_file_ptr
	add	eax,[esi].ts_index
	mov	ecx,[esi].ts_file_end
	cmp	eax,ecx
	je	done
	jb	shrink

	strlen( ecx )
	inc	eax
	add	eax,[esi].ts_file_end
	mov	ecx,[edx].ti_bp
	add	ecx,[edx].ti_blen
	sub	ecx,256
	cmp	eax,ecx
	jb	extend

	mov	eax,edx
	tirealloc( edx )
	jz	error

	sub	[esi].ts_file_end,eax
	sub	[esi].ts_file_ptr,eax
	mov	eax,[edx].ti_bp
	add	[esi].ts_file_end,eax
	add	[esi].ts_file_ptr,eax
	mov	eax,[edx].ti_lp
	add	eax,[edx].ti_bcol
	mov	[esi].ts_buffer,eax

shrink:
	mov	eax,[esi].ts_file_ptr
	add	eax,[esi].ts_index
	strmove(eax,[esi].ts_file_end)
done:
	memcpy( [esi].ts_file_ptr, [esi].ts_buffer, [esi].ts_index )
	or	[edx].ti_flag,_T_MODIFIED
	xor	eax,eax
toend:
	ret
extend:
	sub	eax,[esi].ts_file_end
	mov	ecx,[esi].ts_file_ptr
	add	ecx,[esi].ts_index
	memmove(ecx,[esi].ts_file_end,eax)
	jmp	done
error:
	mov	eax,_TI_CMFAILED
	jmp	toend

__st_flush ENDP

__st_tail PROC USES esi edi ti:PTINFO, ts:PTIOST, tail:LPSTR

	mov	esi,ts
	mov	edi,tail

	movzx	eax,BYTE PTR [edi]
	.while	eax

		.if	eax != TITABCHAR
			__st_putc( esi, eax )
			jc	error
		.endif
		add	edi,1
		movzx	eax,BYTE PTR [edi]
	.endw

	__st_trim( esi )
	__st_flush( ti, esi )
toend:
	ret
error:
	mov	eax,_TI_CMFAILED
	jmp	toend

__st_tail ENDP

	END
