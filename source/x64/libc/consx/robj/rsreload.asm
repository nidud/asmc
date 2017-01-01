include consx.inc

	.code

rsreload PROC USES rsi rdi rbx robj:PTR S_ROBJ, dobj:PTR S_DOBJ
	mov	rsi,rcx
	mov	rbx,rdx
	mov	eax,[rbx]
	and	eax,_D_DOPEN
	.if	!ZERO?
		dlhide( rbx )
		mov	edi,eax
		movzx	rax,[rbx].S_DOBJ.dl_count
		inc	rax
		lea	rax,[rax*8+2]
		add	rax,rsi
		mov	r8,rax
		mov	al,[rbx].S_DOBJ.dl_rect.rc_col
		mul	[rbx].S_DOBJ.dl_rect.rc_row
		.if	[rbx].S_DOBJ.dl_flag & _D_RESAT
			or eax,8000h
		.endif
		xchg	r8,rax
		wcunzip( [rbx].S_DOBJ.dl_wp, rax, r8d )
		dlinit( rbx )
		.if	esi
			dlshow( rbx )
		.endif
	.endif
	ret
rsreload ENDP

	END
