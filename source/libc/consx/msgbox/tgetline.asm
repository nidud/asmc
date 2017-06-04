include consx.inc

	.code

tgetline PROC USES esi edi dlgtitle:LPSTR, buffer:LPSTR, line_size, buffer_size
local	dobj:S_DOBJ
local	rc:S_RECT
	mov dobj.dl_flag,_D_STDDLG
	mov dobj.dl_rect.rc_row,5
	mov dobj.dl_rect.rc_y,5
	mov al,BYTE PTR line_size
	mov rc.rc_col,al
	add al,8
	mov dobj.dl_rect.rc_col,al
	shr al,1
	mov ah,40
	sub ah,al
	mov dobj.dl_rect.rc_x,ah
	mov rc.rc_row,1
	mov rc.rc_x,4
	mov rc.rc_y,2
	mov dl,at_background[B_Dialog]
	or  dl,at_foreground[F_Dialog]
	.if dlopen( addr dobj, edx, dlgtitle )
		mov edx,dobj.dl_wp
		movzx ecx,rc.rc_col
		lea eax,[ecx+8]
		lea eax,[eax*4+8]
		add edx,eax
		mov al,07h
		wcputa( edx, ecx, eax )
		dlshow( addr dobj )
		msloop()
		sub eax,eax
		mov esi,eax
		mov edi,eax
		.while	esi != KEY_ESC
			mov eax,rc
			add ax,WORD PTR dobj.dl_rect
			mov ecx,buffer_size
			xor edx,edx
			.if ch & 80h
				mov edx,_O_DTEXT
				and ecx,7FFFh
			.endif
			dledit( buffer, eax, ecx, edx )
			mov esi,eax
			.if eax == KEY_ENTER || eax == KEY_KPENTER
				inc edi
				.break
			.endif
			.if eax == MOUSECMD
				.break .if !rcxyrow( dobj.dl_rect, keybmouse_x, keybmouse_y )
				.if eax == 1
					dlmove( addr dobj )
				.endif
			.endif
		.endw
		dlclose( addr dobj )
	.endif
	mov eax,edi
	ret
tgetline ENDP

	END
