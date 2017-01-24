include consx.inc
include alloc.inc

	.code

scgetws PROC USES esi edi ebx ecx edx x, y, l
	local	rect:SMALL_RECT
	local	lbuf[TIMAXSCRLINE]:CHAR_INFO
	local	buf:DWORD
	movzx	eax,BYTE PTR x
	movzx	edx,BYTE PTR y
	mov	rect.Left,ax
	mov	rect.Top,dx
	mov	ebx,l
	.if	sdword PTR ebx < 0
		not	ebx
		mov	l,ebx
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
	mov	eax,l
	shl	eax,1
	.if	malloc( eax )
		mov	buf,eax
		.if	ReadConsoleOutput( hStdOutput, addr lbuf, ebx, 0, addr rect )
			lea	esi,lbuf
			mov	edi,buf
			mov	ecx,l
			.repeat
				lodsw
				stosb
				lodsw
				stosb
			.untilcxz
			inc	ecx
			mov	eax,1
		.endif
		mov	eax,buf
	.endif
	ret
scgetws ENDP

	END
