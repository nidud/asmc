include consx.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

rcmsmove PROC USES rsi rdi rbx pRECT:ptr S_RECT, wp:PVOID, fl

	local	xpos,ypos
	local	relx,rely
	local	cursor:S_CURSOR

	mov	rdi,rcx
	mov	ebx,[rdi]
	.if	r8d & _D_SHADE
		rcclrshade( ebx, rdx )
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
	CursorGet( addr cursor )
	CursorOff()

	.while	mousep() == 1

		xor	esi,esi
		mousex()
		.if	eax > xpos
			mov rsi,rcmoveright
		.elseif CARRY?
			.if	bl
				mov rsi,rcmoveleft
			.endif
		.endif
		.if	!rsi
			mousey()
			.if	eax > ypos
				mov rsi,rcmovedn
			.elseif CARRY?
				.if	bh != 1
					mov rsi,rcmoveup
				.endif
			.endif
		.endif
		.if	rsi
			mov	r8d,fl
			and	r8d,not _D_SHADE
			mov	rdx,wp
			mov	ecx,ebx
			call	rsi
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
	CursorSet( addr cursor )
	.if	fl & _D_SHADE
		rcsetshade( ebx, wp )
	.endif
	mov	[rdi],ebx
	ret
rcmsmove ENDP

	END
