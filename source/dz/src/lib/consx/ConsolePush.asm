include consx.inc
include alloc.inc

PUBLIC	console_dl	; init screen
PUBLIC	console_cu	; init cursor

	.data

console_dl S_DOBJ <?>
console_cu S_CURSOR <?>

	.code

ConsolePush PROC USES ebx

	local	ci:CONSOLE_SCREEN_BUFFER_INFO

	.if	GetConsoleScreenBufferInfo( hStdOutput, addr ci )

		mov	eax,ci.dwSize
		movzx	ecx,ax
		mov	_scrcol,ecx
		shr	eax,16
		dec	eax
		mov	_scrrow,eax
		CursorGet( addr console_cu )
		lea	ebx,console_dl
		free( [ebx].S_DOBJ.dl_wp )
		mov	eax,_scrrow
		mov	ah,BYTE PTR _scrcol
		inc	al
		rcpush( eax )
		mov	[ebx].S_DOBJ.dl_wp,eax
		mov	[ebx].S_DOBJ.dl_flag,_D_DOPEN
		mov	eax,_scrrow
		inc	eax
		mov	[ebx].S_DOBJ.dl_rect.rc_row,al
		mov	eax,_scrcol
		mov	[ebx].S_DOBJ.dl_rect.rc_col,al
	.endif
	ret

ConsolePush ENDP

	END
