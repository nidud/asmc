; CMSORT.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include string.inc

	.code

cmsort PROC PRIVATE USES esi edi ebx	; AX: OFFSET panel, DX: sort flag
	local	path[_MAX_PATH]:BYTE
	mov	esi,edx
	.if	panel_state()
		mov	ecx,esi
		mov	edi,eax
		mov	esi,[eax].S_PANEL.pn_wsub
		mov	eax,[esi].S_WSUB.ws_flag
		and	eax,not ( _W_SORTSIZE or _W_NOSORT )
		or	eax,ecx
		mov	[esi].S_WSUB.ws_flag,eax
		mov	eax,edi
		.if	panel_curobj()
			lea	ecx,path
			strcpy( ecx, eax )
			wssort( esi )
			.if	wsearch( esi, addr path ) != -1
				push	eax
				push	edi
				dlclose([edi].S_PANEL.pn_xl)
				pop	eax
				pop	edx
				call	panel_setid
				.if	edi == cpanel
					mov	eax,edi
					call	pcell_show
				.endif
			.endif
		.endif
		panel_putitem( edi, 0 )
		mov	eax,1
	.endif
	ret
cmsort	ENDP

cmnosort:
	.if	panel_state()
		push	eax
		mov	edx,[eax].S_PANEL.pn_wsub
		or	[edx].S_WSUB.ws_flag,_W_NOSORT
		call	panel_read
		pop	eax
		panel_putitem( eax, 0 )
		mov	eax,1
	.endif
	ret

cmanosort PROC
	mov	eax,panela
	jmp	cmnosort
cmanosort ENDP

cmbnosort PROC
	mov	eax,panelb
	jmp	cmnosort
cmbnosort ENDP

cmcnosort PROC
	mov	eax,cpanel
	jmp	cmnosort
cmcnosort ENDP

cmadate PROC
	mov	eax,panela
	mov	edx,_W_SORTDATE
	jmp	cmsort
cmadate ENDP

cmbdate PROC
	mov	eax,panelb
	mov	edx,_W_SORTDATE
	jmp	cmsort
cmbdate ENDP

cmcdate PROC
	mov	eax,cpanel
	mov	edx,_W_SORTDATE
	jmp	cmsort
cmcdate ENDP

cmatype PROC
	mov	eax,panela
	mov	edx,_W_SORTTYPE
	jmp	cmsort
cmatype ENDP

cmbtype PROC
	mov	eax,panelb
	mov	edx,_W_SORTTYPE
	jmp	cmsort
cmbtype ENDP

cmctype PROC
	mov	eax,cpanel
	mov	edx,_W_SORTTYPE
	jmp	cmsort
cmctype ENDP

cmasize PROC
	mov	eax,panela
	mov	edx,_W_SORTSIZE
	jmp	cmsort
cmasize ENDP

cmbsize PROC
	mov	eax,panelb
	mov	edx,_W_SORTSIZE
	jmp	cmsort
cmbsize ENDP

cmcsize PROC
	mov	eax,cpanel
	mov	edx,_W_SORTSIZE
	jmp	cmsort
cmcsize ENDP

cmaname PROC
	mov	eax,panela
	mov	edx,_W_SORTNAME
	jmp	cmsort
cmaname ENDP

cmbname PROC
	mov	eax,panelb
	mov	edx,_W_SORTNAME
	jmp	cmsort
cmbname ENDP

cmcname PROC
	mov	eax,cpanel
	mov	edx,_W_SORTNAME
	jmp	cmsort
cmcname ENDP

	END
