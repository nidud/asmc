include consx.inc
include string.inc
include alloc.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

rcmoveup PROC USES rsi rdi rbx rbp rc, wp:PVOID, flag
	local	x,l,lp:PVOID
	movzx	eax,rc.S_RECT.rc_y
	.if	eax > 1
		movzx	esi,rc.S_RECT.rc_row
		dec	eax
		add	esi,eax
		mov	edi,eax
		mov	al,rc.S_RECT.rc_x
		mov	x,eax
		mov	al,rc.S_RECT.rc_col
		mov	l,eax
		.if	rcalloc( ecx, 0 )
			mov	rbx,rax
			rcread( rc, rax )
			scgetws( x, edi, l )
			mov	lp,rax
			dec	rc.S_RECT.rc_y
			rcwrite( rc, rbx )
			free  ( rbx )
			mov	ebx,l
			add	ebx,ebx
			movzx	rax,rc.S_RECT.rc_row
			dec	rax
			mov	rbp,rax
			mul	ebx
			mov	rdi,wp
			add	rdi,rax
			memxchg( lp, rdi, ebx )
			scputws( x, esi, l, rax )
			mov	rdx,rdi
			sub	rdx,rbx
			mov	esi,ebp
			.while	esi
				memxchg( rdx, rdi, ebx )
				sub	edi,ebx
				sub	edx,ebx
				dec	esi
			.endw
		.endif
	.endif
	mov	eax,rc
	ret
rcmoveup ENDP

rcmovedn PROC USES rsi rdi rbx rc, wp:PVOID, flag
	local	x,l,lp:PVOID
	movzx	eax,rc.S_RECT.rc_y
	movzx	edx,rc.S_RECT.rc_row
	mov	esi,eax
	add	eax,edx
	.if	_scrrow >= eax
		mov	edi,eax
		mov	al,rc.S_RECT.rc_x
		mov	x,eax
		mov	al,rc.S_RECT.rc_col
		mov	l,eax
		.if	rcalloc( rc, 0 )
			mov	rbx,rax
			rcread( rc, rax )
			scgetws( x, edi, l )
			mov	lp,rax
			inc	rc.S_RECT.rc_y
			rcwrite( rc, rbx )
			free( rbx )
			mov	ebx,l
			add	ebx,ebx
			memxchg( lp, wp, ebx )
			scputws( x, esi, l, rax )
			movzx	esi,rc.S_RECT.rc_row
			dec	esi
			mov	rdi,wp
			.while	esi
				memxchg( rdi, addr [rdi+rbx], ebx )
				add	rdi,rbx
				dec	esi
			.endw
		.endif
	.endif
	mov	eax,rc
	ret
rcmovedn ENDP

rcmoveright PROC USES rsi rdi rbx rc, wp:PVOID, flag
	local	x,y,l,lp:PVOID
	movzx	eax,rc.S_RECT.rc_x
	movzx	edx,rc.S_RECT.rc_col
	mov	esi,eax
	add	eax,edx
	.if	_scrcol > eax
		mov	edi,eax
		mov	al,rc.S_RECT.rc_x
		mov	x,eax
		mov	al,rc.S_RECT.rc_y
		mov	y,eax
		mov	al,rc.S_RECT.rc_row
		not	eax
		mov	l,eax
		.if	rcalloc( rc, 0 )
			mov	rbx,rax
			rcread( rc, rax )
			scgetws( edi, y, l )
			mov	lp,rax
			inc	rc.S_RECT.rc_x
			rcwrite( rc, rbx )
			free  ( rbx )
			movzx	ebx,rc.S_RECT.rc_col
			dec	ebx
			movzx	edx,rc.S_RECT.rc_row
			mov	rsi,wp
			mov	rdi,lp
			.repeat
				mov	ax,[rsi]
				push	[rdi]
				mov	[rdi],ax
				mov	ecx,ebx
				push	rdi
				mov	rdi,rsi
				add	rsi,2
				rep	movsw
				pop	rdi
				pop	rax
				mov	[rsi-2],ax
				add	rdi,2
				dec	edx
			.until !edx
			scputws( x, y, l, lp )
		.endif
	.endif
	mov	eax,rc
	ret
rcmoveright ENDP

rcmoveleft PROC USES rsi rdi rbx rc, wp:PVOID, flag
	local	x,y,l,lw:PVOID,lp:PVOID
	.if	rc.S_RECT.rc_x
		movzx	eax,rc.S_RECT.rc_x
		mov	edi,eax
		dec	edi
		mov	x,eax
		mov	al,rc.S_RECT.rc_y
		mov	y,eax
		mov	al,rc.S_RECT.rc_row
		mov	esi,eax
		not	eax
		mov	l,eax
		.if	rcalloc( rc, 0 )
			mov	rbx,rax
			rcread( rc, rax )
			scgetws( edi, y, l )
			mov	lp,rax
			dec	rc.S_RECT.rc_x
			rcwrite( rc, rbx )
			free( rbx )
			movzx	eax,rc.S_RECT.rc_col
			mov	edx,eax
			dec	eax
			mov	ebx,eax
			shl	edx,2
			mov	lw,rdx
			mov	edx,esi
			add	eax,eax
			mov	rsi,wp
			add	rsi,rax
			mov	rdi,lp
			std
			.repeat
				mov	ax,[rsi]
				push	[rdi]
				mov	[rdi],ax
				mov	ecx,ebx
				push	rdi
				mov	rdi,rsi
				sub	rsi,2
				rep	movsw
				pop	rdi
				pop	rax
				mov	[rsi+2],ax
				add	rsi,lw
				add	rdi,2
				dec	edx
			.until !edx
			cld
			movzx	eax,rc.S_RECT.rc_col
			add	eax,x
			dec	eax
			scputws( eax, y, l, lp )
		.endif
	.endif
	mov	eax,rc
	ret
rcmoveleft ENDP

	END
