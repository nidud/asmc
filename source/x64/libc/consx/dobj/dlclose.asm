include consx.inc
include alloc.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp
	assume	rsi: ptr S_DOBJ

dlclose proc uses rsi rdi rbx rbp r12 r13 r14 r15 dobj:PTR S_DOBJ

	mov	r14,rax

	mov	rsi,rcx
	movzx	eax,[rsi].dl_flag
	mov	edi,eax
	mov	ecx,eax
	and	ecx,_D_ONSCR
	and	eax,_D_DOPEN
	mov	r12,rax

	.if	!ZERO?

		.if	ecx

			rcwrite( [rsi].dl_rect, [rsi].dl_wp )

			.if	edi & _D_SHADE

				mov	eax,[rsi].dl_rect
				mov	dl,ah
				lea	rbx,[rax+2]
				shr	eax,16
				movzx	ebp,al
				add	dl,ah

				mov	r15,rax
				mul	ah
				add	eax,eax
				add	rax,[rsi].dl_wp
				mov	r13,rdx
				scputal(ebx, edx, ebp, rax)

				mov	rdx,r13
				add	rax,rbp
				mov	rcx,r15

				lea	ebx,[ebx+ecx-2]
				shr	ecx,8
				dec	ecx
				.if	!ZERO?
					mov	ebp,edx
					sub	ebp,ecx
					mov	r15d,ecx
					.repeat
						scputal(ebx, ebp, 2, rax)
						add	rax,2
						inc	ebp
						dec	r15d
					.until	ZERO?
				.endif
			.endif
		.endif

		and	edi,not (_D_DOPEN or _D_ONSCR)
		mov	[rsi].dl_flag,di

		.if	!( edi & _D_MYBUF )
			free( [rsi].dl_wp )
			xor	rax,rax
			mov	[rsi].dl_wp,rax
		.endif

		.if	edi & _D_RCNEW
			free( rsi )
		.endif
	.endif
	mov	rax,r12		; if open
	mov	rdx,r14		; EAX on call
	ret
dlclose endp

	END
