include consx.inc

	.code

wczip	PROC USES esi edi ebx dest:PVOID, src:PVOID, count, dflag
	mov edx,dflag
	mov ecx,count
	mov edi,dest
	mov esi,src
	add edi,3
	lea ebx,[edi+ecx]
	.repeat
		mov ax,[esi]
		.if !al
			mov al,' '
		.endif
		mov [ebx],al
		mov al,ah
		mov [edi],al
		.if edx & _D_RESAT
			and ax,0FF0h
			.if edx & _D_MENUS
				mov al,B_Menus shl 4
				.if ah == at_foreground[F_MenusKey]
					mov ah,F_MenusKey
				.elseif ah != 8
					mov ah,F_Menus
				.endif
			.elseif al == at_background[B_Dialog]
				.if ah == at_foreground[F_DialogKey]
					mov ah,F_DialogKey
				.elseif ah == at_foreground[F_Dialog]
					mov ah,F_Dialog
				.endif
				mov al,[esi]
				.if al == 'Ü' || al == 'ß'
					mov ah,F_PBShade
				.endif
				mov al,B_Dialog shl 4
			.elseif al == at_background[B_Title]
				mov al,B_Title shl 4
				.if ah == at_foreground[F_TitleKey]
					mov ah,F_TitleKey
				.elseif ah != 8
					mov ah,F_Title
				.endif
			.elseif al == at_background[B_PushButt]
				mov al,B_PushButt shl 4
				.if ah == at_foreground[F_TitleKey]
					mov ah,F_TitleKey
				.elseif ah != 8
					mov ah,F_Title
				.endif
			.endif
			or  al,ah
			mov [edi],al
		.endif
		inc ebx
		inc edi
		add esi,2
	.untilcxz
	mov esi,dest
	mov edi,esi
	add esi,3
	mov ecx,count
	call compress
	mov ecx,count
	call compress
	mov eax,edi
	sub eax,dest
	shr eax,1
	inc eax
	ret
compress:
	lodsb
	mov dl,al
	mov dh,al
	and dh,0F0h
	cmp al,[esi]
	jnz @F
	mov ebx,0F001h
	jmp @04
@@:
	cmp dh,0F0h
	jnz @08
	mov eax,01F0h
	jmp @07
@03:
	inc ebx
	lodsb
	cmp al,[esi]
	jne @05
@04:
	dec ecx
	jnz @03
@05:
	mov eax,ebx
	cmp ebx,0F002h
	jnz @F
	cmp dh,0F0h
	jz  @F
	mov al,dl
	stosb
	jmp @08
@@:
	xchg ah,al
@07:
	stosw
	mov al,dl
@08:
	stosb
	test ecx,ecx
	jz @F
	dec ecx
	jnz compress
@@:
	retn
wczip	ENDP

	END
