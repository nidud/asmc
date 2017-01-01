include consx.inc
include alloc.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

scgetws PROC USES rsi rdi rbx rbp r12 x, y, l
local	rect:SMALL_RECT,
	lbuf[TIMAXSCRLINE]:CHAR_INFO

	mov	r12,r8
	movzx	eax,cl
	movzx	edx,dl
	mov	rect.Left,ax
	mov	rect.Top,dx
	mov	ebx,r8d

	.if	sdword PTR ebx < 0
		not	ebx
		mov	r12d,ebx
		add	edx,ebx
		dec	edx
		shl	ebx,16
		mov	bx,1
	.else
		add	eax,ebx
		add	ebx,10000h
	.endif

	mov	rect.Right,ax
	mov	rect.Bottom,dx
	mov	eax,r8d
	shl	rax,1
	.if	malloc( rax )
		mov	rbp,rax
		.if	ReadConsoleOutput( hStdOutput, addr lbuf, ebx, 0, addr rect )
			lea	rsi,lbuf
			mov	rdi,rbp
			mov	ecx,r12d
			.repeat
				lodsw
				stosb
				lodsw
				stosb
			.untilcxz
			inc	ecx
			mov	eax,1
		.endif
		mov	rax,rbp
	.endif
	ret
scgetws ENDP

	END
