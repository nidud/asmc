include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

rcwrite proc uses rsi rdi rbx rbp r12 r13 rc, wc:PVOID

	local	bz:COORD
	local	rect:SMALL_RECT
	local	lbuf[TIMAXSCRLINE]:CHAR_INFO

	mov	rsi,rdx
	mov	eax,ecx
	shr	eax,16
	movzx	ebp,al
	mov	bz.x,bp
	mov	bz.y,1
	movzx	eax,ah
	mov	r12d,eax
	movzx	eax,cl
	mov	rect.Left,ax
	add	eax,ebp
	dec	eax
	mov	rect.Right,ax
	movzx	eax,ch
	mov	r13d,eax
	lea	rdi,lbuf
	xor	eax,eax
	mov	ecx,ebp
	rep	stosd
	mov	ebx,r12d
	.repeat
		lea	rdi,lbuf
		mov	ecx,ebp
		.repeat
			mov	ax,[rsi]
			add	rsi,2
			mov	[rdi],al
			mov	[rdi+2],ah
			add	rdi,SIZE CHAR_INFO
		.untilcxz
		mov	eax,r13d
		add	eax,r12d
		sub	eax,ebx
		mov	rect.Top,ax
		mov	rect.Bottom,ax
		.break .if !WriteConsoleOutput( hStdOutput, addr lbuf, bz, 0, addr rect )
		dec	ebx
	.until	ZERO?
	ret
rcwrite endp

	END
