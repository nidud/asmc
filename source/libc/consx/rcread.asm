include consx.inc
include alloc.inc

	.code

	option	cstack:on

rcreadc PROC USES ebx esi edi buf:PVOID, bsize, pRrect:PVOID
	local	bz:COORD
	local	rc:SMALL_RECT
	mov	eax,bsize
	mov	bz,eax
	mov	edx,pRrect
	mov	eax,DWORD PTR [edx]
	mov	DWORD PTR rc,eax
	mov	eax,DWORD PTR [edx+4]
	mov	DWORD PTR rc+4,eax
	.if	!ReadConsoleOutput( hStdOutput, buf, bz, 0, addr rc )
		mov	ax,rc.Top
		mov	rc.Bottom,ax
		mov	edi,buf
		movzx	ebx,bz.y
		mov	bz.y,1
		movzx	esi,bz.x
		shl	esi,2
		.repeat
			.break .if !ReadConsoleOutput( hStdOutput, edi, bz, 0, addr rc )
			inc	rc.Bottom
			inc	rc.Top
			add	edi,esi
			dec	ebx
		.until !ebx
		xor	eax,eax
		.if	!ebx
			inc eax
		.endif
	.endif
	ret
rcreadc ENDP

rcread	PROC USES ebx esi edi rc, wc:PVOID
	local	col:DWORD
	local	bz:COORD
	local	buf:DWORD
	local	rect:SMALL_RECT
	movzx	eax,rc.S_RECT.rc_col
	mov	col,eax
	mov	bz.x,ax
	movzx	eax,rc.S_RECT.rc_row
	mov	bz.y,ax
	mov	ebx,eax
	movzx	eax,rc.S_RECT.rc_y
	mov	rect.Top,ax
	mov	al,rc.S_RECT.rc_x
	mov	rect.Left,ax
	mov	eax,ebx
	add	ax,rect.Top
	dec	eax
	mov	rect.Bottom,ax
	mov	eax,col
	add	ax,rect.Left
	dec	eax
	mov	rect.Right,ax
	mov	eax,ebx
	mul	col
	shl	eax,2
	alloca( eax )
	mov	buf,eax
	.if	rcreadc( buf, bz, addr rect )
		mov	esi,buf
		mov	edi,wc
		.repeat
			mov ecx,col
			.repeat
				lodsw
				stosb
				lodsw
				stosb
			.untilcxz
			dec	ebx
		.until !ebx
		inc	ebx
		mov	eax,ebx
	.endif
	ret
rcread	ENDP

	END
