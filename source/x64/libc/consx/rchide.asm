include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

rchide	PROC USES rsi rdi rbx rect, fl, wp:PVOID

	mov	esi,ecx
	mov	edi,edx
	mov	rbx,r8

	xor	eax,eax
	.if	edx & _D_DOPEN or _D_ONSCR

		.if	edx & _D_ONSCR

			.if	rcxchg( ecx, r8 )

				.if	edi & _D_SHADE

					rcclrshade( esi, rbx )
				.endif
				xor	eax,eax
				inc	eax
			.endif
		.endif
	.endif
	ret

rchide	ENDP

	END
