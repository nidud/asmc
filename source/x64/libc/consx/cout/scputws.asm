include consx.inc
include alloc.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

scputws PROC USES rsi rdi x, y, l, wp:PVOID
local	rect:SMALL_RECT,
	lbuf[TIMAXSCRLINE]:CHAR_INFO

	mov	rsi,r9
	lea	rdi,lbuf
	mov	ecx,r8d
	.if	sdword PTR ecx < 0
		not	ecx
	.endif
	xor	eax,eax
	.repeat
		lodsb
		stosw
		lodsb
		stosw
	.untilcxz
	free( r9 )
	movzx	eax,BYTE PTR x
	movzx	edx,BYTE PTR y
	mov	rect.Top,dx
	mov	rect.Left,ax
	mov	ecx,l
	.if	sdword PTR ecx < 0
		not	ecx
		;mov	l,ecx
		add	edx,ecx
		dec	edx
		shl	ecx,16
		mov	cx,1
	.else
		add	eax,ecx
		add	ecx,10000h
	.endif
	mov	rect.Right,ax
	mov	rect.Bottom,dx
	mov	r8d,ecx
	WriteConsoleOutput( hStdOutput, addr lbuf, r8d, 0, addr rect )
	ret
scputws ENDP

	END
