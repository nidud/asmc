; CMTOGGLE.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc

	.code

cmatoggle PROC
	panel_toggle(panela)
	ret
cmatoggle ENDP

cmbtoggle PROC
	panel_toggle(panelb)
	ret
cmbtoggle ENDP

cmtoggleon PROC USES esi edi

	mov esi,panel_state(panela)
	mov edi,panel_state(panelb)
	.if !edi && esi
		cmatoggle()
	.elseif edi && !esi
		cmbtoggle()
	.elseif edi
		mov esi,cpanel
		mov edi,panela
		.if esi == edi
			mov edi,panelb
		.endif
		panel_hide(esi)
		panel_hide(edi)
	.else
		comhide()
		mov esi,cpanel
		mov edi,panela
		.if esi == edi
			mov edi,panelb
		.endif
		panel_show(edi)
		panel_show(esi)
		panel_setactive(esi)
	.endif
	xor	eax,eax
	ret
cmtoggleon ENDP

cmtogglehz PROC
	mov eax,config.c_panelsize
	mov ecx,cflag
	.if ecx & _C_WIDEVIEW && ecx & _C_HORIZONTAL
		and ecx,not _C_WIDEVIEW
		shl al,1
	.elseif ecx & _C_HORIZONTAL
		and ecx,not _C_HORIZONTAL
		shl al,1
	.else
		or  ecx,_C_WIDEVIEW or _C_HORIZONTAL
	.endif
	mov	cflag,ecx
	mov	config.c_panelsize,eax
	redraw_panels()
	ret
cmtogglehz ENDP

cmtogglesz PROC
	xor eax,eax
	.if eax == config.c_panelsize
		mov eax,_scrrow
		shr eax,1
		dec eax
	.endif
	mov config.c_panelsize,eax
	redraw_panels()
	ret
cmtogglesz ENDP

cmxorcmdline PROC
	xor cflag,_C_COMMANDLINE
	apiupdate()
	ret
cmxorcmdline ENDP

cmxorkeybar PROC
	xor cflag,_C_STATUSLINE
	apiupdate()
	ret
cmxorkeybar ENDP

cmxormenubar PROC
	xor cflag,_C_MENUSLINE
	apiupdate()
	ret
cmxormenubar ENDP

	END
