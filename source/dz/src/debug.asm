; DEBUG.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include stdlib.inc

cmplugins proto

.data

ifdef DEBUG
;externdef	string_lengths:dword
externdef	comspex:dword
format_files	db 'panelA.path = %-30s',10
		db 'panelB.path = %-30s',10
		db 'panelB.mask = %-30s',10
		db 'programpath = %-30s',10
		db 'configpath  = %-30s',10
		db 'console	= %030b',10
		db '_scrcol	= %30d',10
		db '_scrrow	= %30d',10
		db 'keyshift	= %30b',10
		db 0
endif

.code

ifdef DEBUG

cmdebug proc uses esi edi ebx
if 0
	mov ebx,cpanel
	mov ebx,[ebx].S_PANEL.pn_wsub
	invoke	ermsg,"Debug",addr format_files,
		addr path_a.wp_path,
		addr path_b.wp_path,
		addr path_a.wp_mask,
		addr programpath,
		addr configpath,
		console,
		_scrcol,
		_scrrow,
		keyshift
	invoke	ermsg,"Debug","%s\n%s",comspec,comspex
endif
if 0
	mov	ecx,1023
	xor	ebx,ebx ; total length
	xor	esi,esi ; total used
@@:
	mov	edx,string_lengths[ecx*4]
	xor	eax,eax
	mov	string_lengths[ecx*4],eax
	add	esi,edx
	mov	eax,edx
	mul	ecx
	add	ebx,eax
	dec	ecx
	jge	@B
	mov	eax,ebx
	xor	edx,edx
	div	esi
	invoke	ermsg,"Debug","Avarage string lengths: %d (%d)\n",eax,esi
endif
if 0
	invoke	ermsg,"Debug","PanelA: %08X\nPanelB: %08X",
		path_a.ws_flag,
		path_b.ws_flag
endif
	ret
cmdebug endp
endif

	END
