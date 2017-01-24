include consx.inc
include alloc.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

rcclose PROC USES rsi rbx rect:S_RECT, fl, wp:PVOID

	mov	rbx,r8
	mov	esi,edx

	.if	edx & _D_DOPEN

		.if	edx & _D_ONSCR
			rchide( ecx, edx, r8 )
		.endif

		.if	!( esi & _D_MYBUF )
			free( rbx )
		.endif
	.endif
	mov	eax,esi
	and	eax,_D_DOPEN
	ret

rcclose ENDP

	END
