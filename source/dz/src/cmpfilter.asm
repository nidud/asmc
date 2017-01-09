; CMFILTER.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include stdio.inc
include stdlib.inc
include string.inc

externdef	IDD_DZPanelFilter:DWORD

ID_READCOUNT	equ 1*16
ID_READMASK	equ 2*16
ID_DIRECTORY	equ 3*16
ID_OK		equ 4*16
ID_LOADPATH	equ 5*16
ID_CANCEL	equ 6*16

	.data

path_dd		dd 0
cp_directory	db "Directory",0
format_d	db "%d",0

	.code

event_loadpath PROC PRIVATE
	local	path[_MAX_PATH]:BYTE
	mov	path,0
	tools_idd( _MAX_PATH, addr path, addr cp_directory )
	push	eax
	call	msloop
	pop	eax
	mov	dl,path
	.if !dl || !eax || eax == MOUSECMD
		mov	eax,_C_NORMAL
	.else
		expenviron( addr path )
		strcpy( path_dd, eax )
		mov	eax,_C_REOPEN
	.endif
	ret
event_loadpath ENDP

PanelFilter PROC PRIVATE USES esi edi ebx panel, xpos

	mov	edi,IDD_DZPanelFilter
	mov	eax,xpos
	mov	[edi+6],al
	.if rsopen( edi )
		mov	ebx,panel
		mov	esi,[ebx].S_PANEL.pn_wsub
		mov	edi,eax
		mov	[edi].S_TOBJ.to_proc[ID_LOADPATH],event_loadpath
		mov	eax,[edi].S_TOBJ.to_data[ID_DIRECTORY]
		mov	path_dd,eax

		strcpy( eax, [esi].S_WSUB.ws_path )
		strcpy( [edi].S_TOBJ.to_data[ID_READMASK], [esi].S_WSUB.ws_mask )
		sprintf( [edi].S_TOBJ.to_data[ID_READCOUNT], addr format_d, [esi].S_WSUB.ws_maxfb )
		dlinit( edi )

		.if dlevent( edi )

			push	[edi].S_TOBJ.to_data[ID_READMASK]
			push	[esi].S_WSUB.ws_mask
			push	[edi].S_TOBJ.to_data[ID_DIRECTORY]
			push	[esi].S_WSUB.ws_path
			atol  ( [edi].S_TOBJ.to_data[ID_READCOUNT] )
			mov	ebx,eax
			call	strcpy
			call	strcpy
			dlclose( edi )

			.if ebx != [esi].S_WSUB.ws_maxfb && ebx > 10 && \
				ebx < WMAXFBLOCK && [esi].S_WSUB.ws_fcb

				push	[esi].S_WSUB.ws_maxfb
				mov	[esi].S_WSUB.ws_maxfb,ebx
				wsopen( esi )
				pop	edx
				.if eax
					mov	eax,1
				.else
					mov	[esi].S_WSUB.ws_maxfb,edx
					wsopen( esi )
					xor	eax,eax
				.endif
			.endif
			push	eax
			mov	eax,panel
			call	panel_reread
			mov	eax,panel
			.if eax == cpanel
				cominit( esi )
			.endif
			pop	eax
		.else
			dlclose( edi )
			xor	eax,eax
		.endif
	.endif
	ret
PanelFilter ENDP

cmafilter PROC
	PanelFilter( panela, 3 )
	ret
cmafilter ENDP

cmbfilter PROC
	PanelFilter( panelb, 42 )
	ret
cmbfilter ENDP

cmloadpath PROC
	sub	esp,_MAX_PATH
	mov	eax,esp
	mov	path_dd,eax
	push	eax
	call	event_loadpath
	cmp	eax,_C_REOPEN
	pop	eax
	jne	@F
	call	cpanel_setpath
@@:
	add	esp,_MAX_PATH
	ret
cmloadpath ENDP

	END
