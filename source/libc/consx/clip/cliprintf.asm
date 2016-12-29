include consx.inc
include string.inc
include alloc.inc
include stdio.inc
include limits.inc

	.code

cliprintf PROC C USES esi edi ebx,
	format: LPSTR,
	args:	VARARG
local	o:	S_FILE
	mov	o.iob_flag,_IOWRT or _IOSTRG
	mov	o.iob_cnt,INT_MAX
	lea	eax,_bufin
	mov	o.iob_ptr,eax
	mov	o.iob_base,eax
	_output( addr o, format, addr args )
	mov	ecx,o.iob_ptr
	mov	BYTE PTR [ecx],0
	.if	eax
		mov	edi,eax
		.if	OpenClipboard( 0 )
			call	EmptyClipboard
			inc	edi
			.if	GlobalAlloc( GMEM_MOVEABLE or GMEM_DDESHARE, edi )
				dec	edi
				mov	esi,eax
				GlobalLock( eax )
				mov	ebx,eax
				strcpy( ebx, addr _bufin )
				GlobalUnlock( esi )
				SetClipboardData( CF_TEXT, ebx )
				mov	eax,edi
			.endif
			push	eax
			call	CloseClipboard
			pop	eax
		.endif
	.endif
	ret
cliprintf ENDP

	END
