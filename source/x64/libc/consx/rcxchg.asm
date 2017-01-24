include consx.inc
include alloc.inc
include errno.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

rcxchg	PROC USES rsi rdi rbx rbp r12 r13 r14 r15 rc, wc:PVOID
local	bz:	COORD,
	rect:	SMALL_RECT,
	lbuf[TIMAXSCRLINE]:CHAR_INFO

	mov	eax,ecx
	mov	r12,rdx
	shr	eax,16
	movzx	ebp,al
	movzx	eax,ah
	mov	bz.x,bp
	mov	r13d,eax
	mov	bz.y,ax
	mov	al,cl
	mov	rect.Left,ax
	add	eax,ebp
	dec	eax
	mov	rect.Right,ax
	movzx	eax,ch
	mov	r15d,eax
	mov	rect.Top,ax
	add	eax,r13d
	dec	eax
	mov	rect.Bottom,ax
	mov	eax,r13d
	mul	ebp
	shl	eax,2
	malloc( rax )
	mov	r14,rax

	.if	rax

		.if	rcreadc( rax, bz, addr rect )

			lea	rdi,lbuf
			xor	eax,eax
			mov	ecx,ebp
			rep	stosd
			mov	rsi,r12
			mov	ebx,r13d
			mov	bz.y,1

			.repeat
				lea	rdi,lbuf
				mov	ecx,ebp
				.repeat
					mov	ax,[rsi]
					mov	[rdi],al
					mov	[rdi+2],ah
					add	rsi,2
					add	rdi,SIZE CHAR_INFO
				.untilcxz
				mov	eax,r15d
				add	eax,r13d
				sub	eax,ebx
				mov	rect.Top,ax
				mov	rect.Bottom,ax
				WriteConsoleOutput( hStdOutput, addr lbuf, bz, 0, addr rect )
				test	eax,eax
				jz	toend
				dec	ebx
			.until	ZERO?

			mov	rsi,r14
			mov	rdi,r12
			mov	ebx,r13d

			.repeat
				mov	ecx,ebp
				.repeat
					mov	al,[rsi]
					mov	ah,[rsi+2]
					mov	[rdi],ax
					add	rdi,2
					add	rsi,4
				.untilcxz
				dec	ebx
			.until	ZERO?
			mov	eax,ebx
			inc	eax
		.endif

		free( r14 )
	.endif
toend:
	ret
rcxchg	ENDP

	END
