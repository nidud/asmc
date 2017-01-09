; CMTOGGLE.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

	.code

cmatoggle PROC
	mov	eax,panela
	jmp	panel_toggle
cmatoggle ENDP

cmbtoggle PROC
	mov	eax,panelb
	jmp	panel_toggle
cmbtoggle ENDP

cmtoggleon PROC USES esi edi
	sub	esi,esi
	sub	edi,edi
	mov	eax,panela
	.if panel_state()
		inc esi
	.endif
	mov	eax,panelb
	.if panel_state()
		inc edi
	.endif
	.if edi != esi
		.if esi
			call cmatoggle
		.else
			call cmbtoggle
		.endif
	.elseif edi
		mov eax,cpanel
		.if eax != panelb
			push panelb
		.else
			push panela
		.endif
		call	panel_hide
		pop	eax
		call	panel_hide
	.else
		call	comhide
		mov	eax,cpanel
		push	eax
		push	eax
		.if eax == panelb
			mov eax,panela
		.else
			mov eax,panelb
		.endif
		call	panel_show
		pop	eax
		call	panel_show
		pop	eax
		call	panel_setactive
	.endif
	xor	eax,eax
	ret
cmtoggleon ENDP

cmtogglehz PROC
	mov	eax,config.c_panelsize
	mov	ecx,cflag
	.if ecx & _C_WIDEVIEW && ecx & _C_HORIZONTAL
		and	ecx,not _C_WIDEVIEW
		shl	al,1
	.elseif ecx & _C_HORIZONTAL
		and	ecx,not _C_HORIZONTAL
		shl	al,1
	.else
		or	ecx,_C_WIDEVIEW or _C_HORIZONTAL
	.endif
	mov	cflag,ecx
	mov	config.c_panelsize,eax
	jmp	redraw_panels
cmtogglehz ENDP

cmtogglesz PROC
	xor	eax,eax
	.if eax == config.c_panelsize
		mov	eax,_scrrow
		shr	eax,1
		dec	eax
	.endif
	mov	config.c_panelsize,eax
	jmp	redraw_panels
cmtogglesz ENDP

cmxorcmdline PROC
	xor	cflag,_C_COMMANDLINE
	jmp	apiupdate
cmxorcmdline ENDP

cmxorkeybar PROC
	xor	cflag,_C_STATUSLINE
	jmp	apiupdate
cmxorkeybar ENDP

cmxormenubar PROC
	xor	cflag,_C_MENUSLINE
	jmp	apiupdate
cmxormenubar ENDP

	END
