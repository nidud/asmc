include consx.inc

	.code

wczip	PROC USES rsi rdi rbx dest:PVOID, src:PVOID, count, dflag
	mov	rdi,rcx;dest
	mov	rsi,rdx;src
	mov	ecx,r8d;count
	mov	edx,r9d;dflag
	add	rdi,3
	lea	rbx,[rdi+rcx]
	.repeat
		mov	ax,[rsi]
		.if	!al
			mov al,' '
		.endif
		mov	[rbx],al
		mov	al,ah
		mov	[rdi],al
		.if	edx & _D_RESAT
			and	ax,0FF0h
			.if	edx & _D_MENUS
				mov	al,B_Menus shl 4
				.if	ah == at_foreground[F_MenusKey]
					mov ah,F_MenusKey
				.elseif ah != 8
					mov ah,F_Menus
				.endif
			.elseif al == at_background[B_Dialog]
				.if	ah == at_foreground[F_DialogKey]
					mov ah,F_DialogKey
				.elseif ah == at_foreground[F_Dialog]
					mov ah,F_Dialog
				.endif
				mov	al,[rsi]
				.if	al == 'Ü' || al == 'ß'
					mov ah,F_PBShade
				.endif
				mov	al,B_Dialog shl 4
			.elseif al == at_background[B_Title]
				mov	al,B_Title shl 4
				.if	ah == at_foreground[F_TitleKey]
					mov ah,F_TitleKey
				.elseif ah != 8
					mov ah,F_Title
				.endif
			.elseif al == at_background[B_PushButt]
				mov	al,B_PushButt shl 4
				.if	ah == at_foreground[F_TitleKey]
					mov ah,F_TitleKey
				.elseif ah != 8
					mov ah,F_Title
				.endif
			.endif
			or	al,ah
			mov	[rdi],al
		.endif
		inc	rbx
		inc	rdi
		add	rsi,2
	.untilcxz
	mov	rsi,dest
	mov	rdi,rsi
	add	rsi,3
	mov	ecx,count
	call	compress
	mov	ecx,count
	call	compress
	mov	rax,rdi
	sub	rax,dest
	shr	rax,1
	inc	rax
	ret
compress:
	lodsb
	mov	dl,al
	mov	dh,al
	and	dh,0F0h
	cmp	al,[rsi]
	jnz	@F
	mov	ebx,0F001h
	jmp	@04
@@:
	cmp	dh,0F0h
	jnz	@08
	mov	eax,01F0h
	jmp	@07
@03:
	inc	ebx
	lodsb
	cmp	al,[rsi]
	jne	@05
@04:
	dec	ecx
	jnz	@03
@05:
	mov	eax,ebx
	cmp	ebx,0F002h
	jnz	@F
	cmp	dh,0F0h
	jz	@F
	mov	al,dl
	stosb
	jmp	@08
@@:
	xchg	ah,al
@07:
	stosw
	mov	al,dl
@08:
	stosb
	test	ecx,ecx
	jz	@F
	dec	ecx
	jnz	compress
@@:
	retn
wczip	ENDP

	END
