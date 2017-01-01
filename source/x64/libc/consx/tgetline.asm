include consx.inc

	.code

tgetline PROC USES rsi rdi dlgtitle:LPSTR, buffer:LPSTR, line_size, buffer_size
	local	dobj:S_DOBJ
	local	rc:S_RECT
	mov	dobj.dl_flag,_D_STDDLG
	mov	dobj.dl_rect.rc_row,5
	mov	dobj.dl_rect.rc_y,5
	mov	al,BYTE PTR line_size
	mov	rc.rc_col,al
	add	al,8
	mov	dobj.dl_rect.rc_col,al
	shr	al,1
	mov	ah,40
	sub	ah,al
	mov	dobj.dl_rect.rc_x,ah
	mov	rc.rc_row,1
	mov	rc.rc_x,4
	mov	rc.rc_y,2
	mov	dl,at_background[B_Dialog]
	or	dl,at_foreground[F_Dialog]
	.if	dlopen( addr dobj, edx, dlgtitle )
		mov	rcx,dobj.dl_wp
		movzx	rdx,rc.rc_col
		lea	rax,[rdx+8]
		lea	eax,[rax*4+8]
		add	rcx,rax
		mov	al,07h
		wcputa( rcx, edx, eax )
		dlshow( addr dobj )
		call	msloop
		sub	eax,eax
		mov	esi,eax
		mov	edi,eax
		.while	esi != KEY_ESC
			mov	eax,rc
			add	ax,WORD PTR dobj.dl_rect
			mov	ecx,buffer_size
			xor	r9d,r9d
			.if	ch & 80h
				mov r9d,_O_DTEXT
				and ecx,7FFFh
			.endif
			mov	r8d,ecx
			dledit( buffer, eax, r8d, r9d )
			mov	esi,eax
			.if	eax == KEY_ENTER || eax == KEY_KPENTER
				inc edi
				.break
			.endif
			.if	eax == MOUSECMD
				.break .if !rcxyrow( dobj.dl_rect, keybmouse_x, keybmouse_y )
				.if	eax == 1
					dlmove( addr dobj )
				.endif
			.endif
		.endw
		dlclose( addr dobj )
	.endif
	mov	eax,edi
	ret
tgetline ENDP

	END
