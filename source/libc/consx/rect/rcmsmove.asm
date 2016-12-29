include consx.inc

	.code

rcmsmove PROC USES esi edi ebx rc:PRECT, wp:PVOID, fl:DWORD

	local	xpos,ypos
	local	relx,rely
	local	cursor:S_CURSOR

	mov	edi,rc
	mov	ebx,[edi]
	.if	fl & _D_SHADE
		rcclrshade( ebx, wp )
	.endif
	call	mousey
	mov	ypos,eax
	mov	edx,eax
	call	mousex
	mov	xpos,eax
	sub	al,bl
	mov	relx,eax
	sub	dl,bh
	mov	rely,edx
	GetCursor( addr cursor )
	CursorOff()

	.while	mousep() == 1

		xor	esi,esi
		.if	mousex() > xpos
			mov esi,rcmoveright
		.elseif CARRY?
			.if	bl
				mov esi,rcmoveleft
			.endif
		.endif
		.if	!esi
			.if	mousey() > ypos
				mov esi,rcmovedn
			.elseif CARRY?
				.if	bh != 1
					mov esi,rcmoveup
				.endif
			.endif
		.endif
		.if	esi
			mov	ecx,fl
			and	ecx,not _D_SHADE
			push	ecx
			push	wp
			push	ebx
			call	esi
			mov	ebx,eax
			mov	edx,eax
			mov	eax,rely
			add	al,dh
			mov	ypos,eax
			mov	eax,relx
			add	al,dl
			mov	xpos,eax
		.endif
	.endw
	SetCursor( addr cursor )
	.if	fl & _D_SHADE
		rcsetshade( ebx, wp )
	.endif
	mov	[edi],ebx
	ret
rcmsmove ENDP

	END
