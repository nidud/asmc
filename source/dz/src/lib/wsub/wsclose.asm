include alloc.inc
include wsub.inc

	.code

	ASSUME	esi: ptr S_WSUB

wsclose PROC USES esi wsub:PTR S_WSUB

	mov	esi,wsub
	wsfree( esi )
	push	eax
	free  ( [esi].ws_fcb )
	.if	[esi].ws_flag & _W_MALLOC

		free([esi].ws_path)
	.endif
	xor	eax,eax
	mov	[esi].ws_flag,eax
	mov	[esi].ws_fcb,eax
	pop	eax
	ret

wsclose ENDP

	END
