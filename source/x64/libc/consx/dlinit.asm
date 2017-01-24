include alloc.inc
include consx.inc

externdef tclrascii:byte

	.code

	OPTION	WIN64:2, STACKBASE:rsp
	OPTION	PROC:PRIVATE

dlinitobj proc uses rsi rdi rbx rbp r12 dobj:PTR S_DOBJ, tobj:PTR S_TOBJ

	mov	rbp,rcx
	mov	rbx,rdx

	xor	eax,eax
	mov	ch,[rbx].S_TOBJ.to_rect.rc_col
	mov	edx,[rbx+4]	; .to_rect.rc_x,y

	mov	cl,[rbp+6]	; .dl_rect.rc_col
	mov	edi,[rbp]	; .dl_flag
	add	edx,edx
	mov	al,dh
	mul	cl
	mov	cl,ch
	and	ecx,00FFh
	and	edx,00FFh
	add	eax,edx
	add	rax,[rbp].S_DOBJ.dl_wp
	mov	r12,rax
	mov	ax,[rbx].S_TOBJ.to_flag
	and	eax,000Fh

	.switch al

	  .case _O_PBUTT
		mov	eax,[rbx];.S_TOBJ.to_flag
		and	eax,_O_DEACT
		mov	edx,eax
		.repeat
			mov	eax,[r12]
			inc	r12
			mov	al,ah
			and	al,0Fh
			.if	edx
				.if	!al
					mov	al,ah
					and	al,070h
					or	al,008h
					mov	[r12],al
				.endif
			.elseif al == 8
				mov	al,ah
				and	al,070h
				mov	[r12],al
			.endif
			inc	r12
		.untilcxz
		.endc

	  .case _O_RBUTT
		and	al,_O_RADIO
		mov	al,' '
		.if	!ZERO?
			mov	al,ASCII_RADIO
		.endif
		mov	[r12+2],al
		.endc

	  .case _O_CHBOX
		and	eax,_O_FLAGB
		mov	al,' '
		.if	!ZERO?
			mov	al,'x'
		.endif
		mov	[r12+2],al
		.endc

	  .case _O_XCELL
	  .case _O_TEDIT

		mov	dl,tclrascii
		mov	rsi,[ebx].S_TOBJ.to_data
		mov	ebx,eax
		mov	rdi,r12
		mov	eax,[rdi]
		mov	al,dl
		mov	edx,ecx
		.if	bl != _O_TEDIT
			mov	al,' '
			.repeat
				stosb
				inc rdi
			.untilcxz
		.else
			rep	stosw
		.endif
		.if	rsi
			mov	rdi,r12
			.if	bl == _O_XCELL
				add	rdi,2
				sub	edx,2
				wcpath( rdi, edx, rsi )
			.else
				.repeat
					lodsb
					.break .if !al
					stosb
					inc	rdi
					dec	edx
				.until	ZERO?
			.endif
		.endif
		.endc

	  .case _O_MENUS
		mov	eax,[rbx]
		.if	al & _O_FLAGB
			mov byte ptr [r12-2],175
		.elseif eax & _O_RADIO
			mov al,ASCII_RADIO
			mov [r12-2],al
		.endif
		.endc

	.endsw

	ret
dlinitobj endp

	OPTION	PROC:PUBLIC

dlinit	proc uses rsi rdi rbx r12 r13 td:PTR S_DOBJ

	mov	rbx,rcx
	mov	edi,[rbx]
	.if	edi & _D_ONSCR
		mov	r13,[rbx].S_DOBJ.dl_wp
		.if	!rcalloc( [rbx].S_DOBJ.dl_rect, 0 )
			jmp	toend
		.endif
		mov	[rbx].S_DOBJ.dl_wp,rax
		rcread( [rbx].S_DOBJ.dl_rect, rax )
	.endif
	movzx	esi,[rbx].S_DOBJ.dl_count
	mov	r12,[rbx].S_DOBJ.dl_object
	.while	esi
		dlinitobj(rbx, r12)
		add	r12,SIZE S_TOBJ
		dec	esi
	.endw
	.if	!(edi & _D_ONSCR)
		rcwrite([ebx].S_DOBJ.dl_rect, [ebx].S_DOBJ.dl_wp )
		free  ( [ebx].S_DOBJ.dl_wp )
		mov	[ebx].S_DOBJ.dl_wp,r13
	.endif
toend:
	ret
dlinit	endp

	END
