; CMSETUP.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include io.inc
include iost.inc
include string.inc
include stdlib.inc
include crtl.inc
include errno.inc
include stdio.inc
include alloc.inc

command		PROTO :DWORD
__AT__		equ 1

	.data

cf_panel	db 0
cf_panel_upd	db 0
cf_screen_upd	db 0
cp_cmdreload	db 'ECHO.',0
cp_pal		db '*.pal',0

color_Blue	db 00h,0Fh,0Fh,07h,08h,00h,00h,07h
		db 08h,00h,0Ah,0Bh,00h,0Fh,0Fh,0Fh
		db 00h,10h,70h,70h,40h,30h,30h,70h
		db 30h,30h,30h,00h,10h,10h,07h,06h
color_Black	db 07h,07h,0Fh,07h,08h,08h,07h,07h
		db 08h,07h,0Ah,0Bh,0Fh,0Bh,0Bh,0Bh
		db 00h,00h,00h,10h,30h,10h,10h,00h
		db 10h,10h,00h,00h,00h,00h,07h,07h
color_Mono	db 0Fh,0Fh,0Fh,0Fh,0Fh,0Fh,0Fh,0Fh
		db 0Fh,0Fh,0Fh,0Fh,0Fh,0Fh,0Fh,0Fh
		db 00h,00h,00h,00h,00h,70h,70h,00h
		db 70h,70h,70h,00h,00h,00h,0Fh,0Fh
color_White	db 00h,07h,0Fh,07h,08h,07h,00h,07h
		db 08h,00h,0Ah,0Bh,00h,07h,08h,08h
		db 00h,10h,0F0h,0F0h,40h,70h,70h,70h
		db 80h,30h,70h,70h,00h,00h,07h,07h
color_Norton	db 07h,0Bh,0Bh,0Bh,0Bh,00h,00h,07h
		db 08h,0Fh,0Eh,0Bh,0Fh,00h,0Eh,0Eh
		db 00h,10h,30h,30h,40h,0F0h,20h,70h
		db 0F0h,30h,00h,00h,30h,30h,0Fh,0Fh

color_Table	dd color_Blue
		dd offset color_Black
		dd offset color_Mono
		dd offset color_White
		dd offset color_Norton

	.code

ID_UBEEP	equ 1*16 ; Use Beep
ID_MOUSE	equ 2*16 ; Use Mouse
ID_IOSFN	equ 3*16 ; Use Long File Names
ID_CLIPB	equ 4*16 ; Use System Clipboard
ID_ASCII	equ 5*16 ; Use Ascii symbol
ID_NTCMD	equ 6*16 ; Use NT Prompt
ID_CMDENV	equ 7*16 ; CMD Compatible Mode
ID_IMODE	equ 8*16 ; Init screen mode on startup
ID_DELHISTORY	equ 9*16
ID_ESCUSERSCR	equ 10*16

cmsystem PROC USES esi edi ebx

	.if rsopen( IDD_DZSystemOptions )

		push	thelp
		mov	thelp,event_help
		mov	ebx,eax
		mov	eax,cflag
		.if eax & _C_DELHISTORY
			or	[ebx].S_TOBJ.to_flag[ID_DELHISTORY],_O_FLAGB
		.endif
		.if eax & _C_ESCUSERSCR
			or	[ebx].S_TOBJ.to_flag[ID_ESCUSERSCR],_O_FLAGB
		.endif
		tosetbitflag( [ebx].S_DOBJ.dl_object, 8, _O_FLAGB, console )
		dlinit( ebx )
		rsevent( IDD_DZSystemOptions, ebx )
		mov	esi,eax
		togetbitflag( [ebx].S_DOBJ.dl_object, 10, _O_FLAGB )
		dlclose( ebx )
		pop	eax
		mov	thelp,eax
		mov	eax,esi
		.if	eax
			mov	eax,edx
			mov	edx,cflag
			and	edx,not (_C_DELHISTORY or _C_ESCUSERSCR)
			.if	eax & 100h ; Auto Delete History
				or	edx,_C_DELHISTORY
			.endif
			.if	eax & 200h ; Use Esc for user screen
				or	edx,_C_ESCUSERSCR
			.endif
			mov	cflag,edx
			mov	ecx,console
			mov	BYTE PTR console,al
			and	eax,CON_MOUSE or CON_IOSFN or CON_CMDENV
			and	ecx,CON_MOUSE or CON_IOSFN or CON_CMDENV
			.if	ecx != eax
				mov	ecx,ENABLE_WINDOW_INPUT
				.if	eax & CON_MOUSE
					or	ecx,ENABLE_MOUSE_INPUT
				.endif
				SetConsoleMode( hStdInput, ecx )
				.if	cf_panel == 1
					mov	cf_panel_upd,1
				.else
					call	redraw_panels
				.endif
			.endif
			call	setasymbol
			mov	eax,1
		.endif
	.endif
	ret
event_help:
	mov	eax,HELPID_15
	call	view_readme
	retn
cmsystem ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	OPTION	PROC: PRIVATE

ID_MEUSLINE	equ 1*16
ID_USEDATE	equ 2*16
ID_USETIME	equ 3*16
ID_USELDATE	equ 4*16
ID_USELTIME	equ 5*16
ID_COMMANDLINE	equ 6*16
ID_STAUSLINE	equ 7*16
ID_ATTRIB	equ 8*16
ID_STANDARD	equ 9*16
ID_LOAD		equ 10*16
ID_SAVE		equ 11*16

event_reload PROC
	.if cf_panel == 0
		dlhide( tdialog )
		call	apiupdate
		dlshow( tdialog )
		call	msloop
		mov	eax,_C_NORMAL
	.else
		call	msloop
		mov	cf_screen_upd,1
		mov	eax,_C_ESCAPE
	.endif
	ret
event_reload ENDP

event_loadcolor PROC USES esi
  local path[_MAX_PATH]:BYTE
	.if wgetfile( addr path, addr cp_pal, 3 )
		push	eax
		osread( eax, addr at_foreground, SIZE S_COLOR )
		mov	esi,eax
		call	_close
		mov	eax,_C_NORMAL
		.if esi == SIZE S_COLOR
			event_reload()
		.endif
	.endif
	ret
event_loadcolor ENDP

event_savecolor PROC
  local path[_MAX_PATH]:BYTE
	.if wgetfile( addr path, addr cp_pal, 2 )
		push	eax
		oswrite( eax, addr at_foreground, SIZE S_COLOR )
		call	_close
	.endif
	mov	eax,_C_NORMAL
	ret
event_savecolor ENDP

ifdef __AT__

event_editat PROC
	call	editattrib
	test	eax,eax
	jnz	event_reload
	mov	eax,_C_NORMAL
	ret
event_editat ENDP

endif

event_standard PROC
	mov	eax,tdialog
	mov	ax,[eax+4]
	add	ax,0B0Ch
	mov	ecx,IDD_DZDefaultColor
	mov	[ecx+6],ax

	.if rsmodal( ecx )
		.if eax < 6
			dec	eax
			mov	eax,color_Table[eax*4]
			memcpy( addr at_foreground, eax, sizeof( S_COLOR ) )
			call	event_reload
		.else
			xor	eax,eax
		.endif
	.else
		inc	eax
	.endif
	ret
event_standard ENDP

	OPTION	PROC: PUBLIC

cmscreen PROC USES esi edi

	mov	cf_screen_upd,0

	.if rsopen( IDD_DZScreenOptions )
		mov	edi,eax
		mov	dl,_O_FLAGB
		mov	eax,cflag
		.if eax & _C_MENUSLINE
			or [edi][ID_MEUSLINE],dl
		.endif
		.if eax & _C_COMMANDLINE
			or [edi][ID_COMMANDLINE],dl
		.endif
		.if eax & _C_STATUSLINE
			or [edi][ID_STAUSLINE],dl
		.endif
		mov eax,console
		.if eax & CON_UDATE
			or [edi][ID_USEDATE],dl
		.endif
		.if eax & CON_LDATE
			or [edi][ID_USELDATE],dl
		.endif
		.if eax & CON_UTIME
			or [edi][ID_USETIME],dl
		.endif
		.if eax & CON_LTIME
			or [edi][ID_USELTIME],dl
		.endif
ifdef __AT__
		mov	[edi].S_TOBJ.to_proc[ID_ATTRIB],event_editat
else
		or	[edi].S_TOBJ.to_flag[ID_ATTRIB],_O_STATE
endif
		mov	[edi].S_TOBJ.to_proc[ID_STANDARD],event_standard
		mov	[edi].S_TOBJ.to_proc[ID_LOAD],event_loadcolor
		mov	[edi].S_TOBJ.to_proc[ID_SAVE],event_savecolor
		dlinit( edi )
		rsevent( IDD_DZScreenOptions, edi )
		mov	esi,eax
		lea	eax,[edi+16]
		togetbitflag( eax, 7, _O_FLAGB )
		dlclose( edi )	; return bit-flag in DX
		mov	eax,esi
		mov	esi,cflag
		.if eax
			mov	eax,edx
			mov	edx,console
			and	edx,not ( CON_UTIME or CON_UDATE or CON_LTIME or CON_LDATE )

			.if al & 02h
				or	edx,CON_UDATE
			.endif
			.if al & 08h
				or	edx,CON_LDATE
			.endif
			.if al & 04h
				or	edx,CON_UTIME
			.endif
			.if al & 10h
				or	edx,CON_LTIME
			.endif
			and	esi,not ( _C_MENUSLINE or _C_STATUSLINE or _C_COMMANDLINE )
			.if al & 01h
				or	esi,_C_MENUSLINE
			.endif
			.if al & 20h
				or	esi,_C_COMMANDLINE
			.endif
			.if al & 40h
				or	esi,_C_STATUSLINE
			.endif
			.if console != edx
				mov	console,edx
				.if cflag & _C_MENUSLINE
					scputw( 60, 0, 20, ' ' )
				.endif
			.endif
			.if cflag != esi || cf_screen_upd
				mov	cf_screen_upd,0
				mov	cflag,esi
				.if cf_panel == 1
					dlhide( tdialog )
				.endif
				call	apiupdate
				.if cf_panel == 1
					dlshow( tdialog )
				.endif
			.endif
		.endif
		mov	eax,_C_NORMAL
	.endif
	ret
cmscreen ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

cmpanel PROC USES ebx
	.if rsopen( IDD_DZPanelOptions )
		mov	ebx,eax
		mov	edx,_O_FLAGB
		mov	eax,cflag
		.if eax & _C_INSMOVDN
			or	[ebx+1*16],dl
		.endif
		.if eax & _C_SELECTDIR
			or	[ebx+2*16],dl
		.endif
		.if eax & _C_SORTDIR
			or	[ebx+3*16],dl
		.endif
		.if eax & _C_CDCLRDONLY
			or	[ebx+4*16],dl
		.endif
		.if eax & _C_VISUALUPDATE
			or	[ebx+5*16],dl
		.endif
		dlinit( ebx )
		rsevent( IDD_DZPanelOptions, ebx )
		push	eax
		mov	eax,ebx
		add	eax,SIZE S_DOBJ
		togetbitflag( eax, 4, _O_FLAGB )
		dlclose( ebx )
		pop	eax

		.if eax
			mov	eax,edx
			and	path_a.ws_flag,not _W_SORTSUB
			and	path_b.ws_flag,not _W_SORTSUB
			mov	edx,cflag
			and	edx,not (_C_INSMOVDN or _C_SELECTDIR or _C_SORTDIR or _C_CDCLRDONLY or _C_VISUALUPDATE)
			.if al & 1
				or	edx,_C_INSMOVDN
			.endif
			.if al & 2
				or	edx,_C_SELECTDIR
			.endif
			.if al & 4
				or	edx,_C_SORTDIR
				or	path_a.ws_flag,_W_SORTSUB
				or	path_b.ws_flag,_W_SORTSUB
			.endif
			.if al & 8
				or	edx,_C_CDCLRDONLY
			.endif
			.if al & 16
				or	edx,_C_VISUALUPDATE
			.endif
			.if cflag != edx
				mov	cflag,edx
				mov	BYTE PTR _diskflag,1
			.endif
			mov	eax,1
		.endif
	.endif
	ret
cmpanel ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

cmconfirm PROC USES ebx
	.if rsopen( IDD_DZConfirmations )
		mov	ebx,eax
		mov	eax,config.c_cflag
		shr	eax,16
		tosetbitflag( [ebx].S_DOBJ.dl_object, 7, _O_FLAGB, eax )
		dlinit( ebx )
		rsevent( IDD_DZConfirmations, ebx )
		push	eax
		togetbitflag( [ebx].S_DOBJ.dl_object, 7, _O_FLAGB )
		dlclose( ebx )
		pop	eax

		.if eax
			mov	eax,config.c_cflag
			and	eax,not 007F0000h
			shl	edx,16
			or	eax,edx
			mov	config.c_cflag,eax
		.endif
	.endif
	ret
cmconfirm ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

cmcompression PROC USES ebx
	.if rsopen( IDD_DZCompression )
		mov	ebx,eax
		mov	eax,compresslevel
		.if al > 9
			mov al,6
			mov compresslevel,eax
		.endif
		inc	eax
		shl	eax,4
		add	eax,ebx
		or	[eax].S_DOBJ.dl_flag,_O_RADIO
		.if cflag & _C_ZINCSUBDIR
			or	[ebx].S_DOBJ.dl_flag[11*16],_O_FLAGB
		.endif
		dlinit( ebx )
		.if rsevent( IDD_DZCompression, ebx )
			mov	eax,cflag
			and	eax,not _C_ZINCSUBDIR
			.if [ebx].S_DOBJ.dl_flag[11*16] & _O_FLAGB
				or eax,_C_ZINCSUBDIR
			.endif
			mov	cflag,eax
			xor	eax,eax
			mov	edx,ebx
			.repeat
				add	edx,SIZE S_TOBJ
				.break .if [edx].S_DOBJ.dl_flag & _O_RADIO
				inc	eax
			.until eax == 10
			.if eax == 10
				mov	eax,6
			.endif
			mov	compresslevel,eax
		.endif
		dlclose( ebx )
	.endif
	ret
cmcompression ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

cmoptions PROC USES esi ebx

	mov	cf_panel,1
	mov	cf_panel_upd,0

	.if rsopen( IDD_DZConfiguration )

		mov	ebx,eax
		mov	[ebx].S_TOBJ.to_proc[4*16],toption
		mov	[ebx].S_TOBJ.to_proc[5*16],cmconfirm
		mov	[ebx].S_TOBJ.to_proc[6*16],cmcompression
		mov	[ebx].S_TOBJ.to_proc[1*16],cmsystem
		mov	[ebx].S_TOBJ.to_proc[2*16],cmscreen
		mov	[ebx].S_TOBJ.to_proc[3*16],cmpanel

		.if cflag & _C_AUTOSAVE
			or	BYTE PTR [ebx+7*16],_O_FLAGB
		.endif
		dlinit( ebx )
		rsevent( IDD_DZConfiguration, ebx )
		push	[ebx+7*16]
		dlclose( ebx )
		mov	cf_panel_upd,0
		pop	eax

		.if edx
			and cflag,not _C_AUTOSAVE
			.if al & _O_FLAGB
				or cflag,_C_AUTOSAVE
			.endif
		.endif
		call	redraw_panels
	.endif
	mov	cf_panel,0
	ret
cmoptions ENDP

	END
