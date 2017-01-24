include alloc.inc
include consx.inc

externdef tclrascii:byte

	.code

	OPTION PROC:PRIVATE

init_pushbutton proc
	mov	esi,[ebp-4]
	and	eax,_O_DEACT
	mov	edx,eax
	.repeat
		mov	eax,[esi]
		inc	esi
		mov	al,ah
		and	al,0Fh
		.if	edx
			.if	!al
				and ah,070h
				or  ah,008h
				mov [esi],ah
			.endif
		.elseif al == 8
			and	ah,070h
			mov	[esi],ah
		.endif
		inc	esi
	.untilcxz
	ret
init_pushbutton endp

init_radiobutton proc
	and	al,_O_RADIO
	mov	al,' '
	jz	init_button
	mov	al,ASCII_RADIO
init_radiobutton endp

init_button proc
	mov	edx,[ebp-4]
	mov	[edx+2],al
	ret
init_button endp

init_chechbox proc
	and	eax,_O_FLAGB
	mov	al,' '
	jz	init_button
	mov	al,'x'
	jmp	init_button
init_chechbox endp

init_textedit proc
	mov	dl,tclrascii
	mov	eax,esi
	mov	esi,[ebx].S_TOBJ.to_data
	mov	ebx,eax
	mov	edi,[ebp-4]
	mov	eax,[edi]
	mov	al,dl
	mov	edx,ecx
	.if	bl != _O_TEDIT
		mov	al,' '
		.repeat
			stosb
			inc edi
		.untilcxz
	.else
		rep	stosw
	.endif
	.if	esi
		mov	edi,[ebp-4]
		.if	bl == _O_XCELL
			add	edi,2
			sub	edx,2
			wcpath( edi, edx, esi )
		.else
			.repeat
				lodsb
				.break .if !al
				stosb
				inc	edi
				dec	edx
			.until	ZERO?
		.endif
	.endif
	ret
init_textedit endp

init_menus proc
	mov	edx,[ebp-4]
	.if	al & _O_FLAGB
		mov byte ptr [edx-2],175
	.elseif eax & _O_RADIO
		mov al,ASCII_RADIO
		mov [edx-2],al
	.endif
	ret
init_menus endp

	.data

init_procs label dword
	dd init_pushbutton
	dd init_radiobutton
	dd init_chechbox
	dd init_textedit
	dd init_textedit
	dd init_menus

	.code

dlinitobj proc uses ebx esi edi dobj:PTR S_DOBJ, tobj:PTR S_TOBJ
  local window
	xor	eax,eax
	mov	ebx,tobj
	mov	ch,[ebx].S_TOBJ.to_rect.rc_col
	mov	edx,[ebx+4]	; .to_rect.rc_x,y
	mov	ebx,dobj
	mov	cl,[ebx+6]	; .dl_rect.rc_col
	mov	edi,[ebx]	; .dl_flag
	add	edx,edx
	mov	al,dh
	mul	cl
	mov	cl,ch
	and	ecx,00FFh
	and	edx,00FFh
	add	eax,edx
	add	eax,[ebx].S_DOBJ.dl_wp
	mov	window,eax
	mov	ebx,tobj
	mov	ax,[ebx].S_TOBJ.to_flag
	and	eax,000Fh
	mov	esi,eax
	cmp	al,_O_MENUS
	ja	@F
	mov	edx,init_procs[eax*4]
	mov	eax,[ebx]
	push	edi
	call	edx
	pop	edi
@@:
	mov	eax,edi
	ret
dlinitobj endp

	OPTION	PROC:PUBLIC

dlinit	proc uses esi edi ebx td:PTR S_DOBJ
  local object, wp
	mov	ebx,td
	mov	edi,[ebx]
	test	edi,_D_ONSCR
	jz	@F
	mov	eax,[ebx].S_DOBJ.dl_wp
	mov	wp,eax
	rcalloc( [ebx].S_DOBJ.dl_rect, 0 )
	jz	toend
	mov	[ebx].S_DOBJ.dl_wp,eax
	rcread( [ebx].S_DOBJ.dl_rect, eax )
@@:
	movzx	eax,[ebx].S_DOBJ.dl_count
	mov	esi,eax
	mov	eax,[ebx].S_DOBJ.dl_object
	mov	object,eax
	test	esi,esi
	jz	done
@@:
	dlinitobj( td, object )
	add	object,SIZE S_TOBJ
	dec	esi
	jnz	@B
done:
	test	edi,_D_ONSCR
	jz	toend
	rcwrite( [ebx].S_DOBJ.dl_rect, [ebx].S_DOBJ.dl_wp )
	free( [ebx].S_DOBJ.dl_wp )
	mov	eax,wp
	mov	[ebx].S_DOBJ.dl_wp,eax
toend:
	ret
dlinit	endp

	END
