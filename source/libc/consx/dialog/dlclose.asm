include consx.inc
include alloc.inc

	.code
	assume	esi: ptr S_DOBJ

dlclose proc uses esi edi ebx dobj:PTR S_DOBJ

	push	eax
	mov	esi,dobj
	movzx	eax,[esi].dl_flag
	mov	edi,eax
	mov	ecx,eax
	and	ecx,_D_ONSCR
	and	eax,_D_DOPEN
	push	ecx
	push	eax

	.if !ZERO?

		.if ecx

			rcwrite([esi].dl_rect, [esi].dl_wp)

			.if edi & _D_SHADE

				mov eax,[esi].dl_rect
				mov dl,ah
				lea ebx,[eax+2]
				shr eax,16
				movzx ecx,al
				add dl,ah
				push eax
				mul ah
				add eax,eax
				add eax,[esi].dl_wp
				scputal(ebx, edx, ecx, eax)
				add eax,ecx
				pop ecx
				lea ebx,[ebx+ecx-2]
				shr ecx,8
				dec ecx
				.if !ZERO?
					sub edx,ecx
					.repeat
						scputal(ebx, edx, 2, eax)
						add eax,2
						inc edx
					.untilcxz
				.endif
			.endif
		.endif

		and edi,not (_D_DOPEN or _D_ONSCR)
		mov [esi].dl_flag,di

		.if !( edi & _D_MYBUF )
			free([esi].dl_wp)
			xor eax,eax
			mov [esi].dl_wp,eax
		.endif

		.if edi & _D_RCNEW
			free(esi)
		.endif
	.endif
	pop eax ; if open
	pop ecx ; if visible
	pop edx ; EAX on call
	ret
dlclose endp

	END
