include consx.inc
include alloc.inc
include errno.inc

	.code

	option	cstack:on

rcxchg	PROC USES esi edi ebx ecx rc, wc:PVOID
	local	y:DWORD
	local	col:DWORD
	local	row:DWORD
	local	bz:COORD
	local	tmp:DWORD
	local	rect:SMALL_RECT
	local	lbuf[TIMAXSCRLINE]:CHAR_INFO
	movzx	eax,rc.S_RECT.rc_col
	mov	col,eax
	mov	bz.x,ax
	mov	al,rc.S_RECT.rc_row
	mov	row,eax
	mov	bz.y,ax
	mov	al,rc.S_RECT.rc_x
	mov	rect.Left,ax
	add	eax,col
	dec	eax
	mov	rect.Right,ax
	movzx	eax,rc.S_RECT.rc_y
	mov	y,eax
	mov	rect.Top,ax
	add	eax,row
	dec	eax
	mov	rect.Bottom,ax
	mov	eax,row
	mul	col
	shl	eax,2
	alloca( eax )
	mov	tmp,eax
	rcreadc( tmp, bz, addr rect )
;	test	eax,eax
	jz	toend
	lea	edi,lbuf
	xor	eax,eax
	mov	ecx,col
	rep	stosd
	mov	esi,wc
	mov	ebx,row
	mov	bz.y,1
	.repeat
		lea	edi,lbuf
		mov	ecx,col
		.repeat
			mov	ax,[esi]
			mov	[edi],al
			mov	[edi+2],ah
			add	esi,2
			add	edi,SIZE CHAR_INFO
		.untilcxz
		mov	eax,y
		add	eax,row
		sub	eax,ebx
		mov	rect.Top,ax
		mov	rect.Bottom,ax
		WriteConsoleOutput( hStdOutput, addr lbuf, bz, 0, addr rect )
		test	eax,eax
		jz	toend
		dec	ebx
	.until	ZERO?
	mov	esi,tmp
	mov	edi,wc
	mov	ebx,row
	.repeat
		mov	ecx,col
		.repeat
			mov	al,[esi]
			mov	ah,[esi+2]
			mov	[edi],ax
			add	edi,2
			add	esi,4
		.untilcxz
		dec	ebx
	.until	ZERO?
	mov	eax,ebx
	inc	eax
toend:
	ret
rcxchg	ENDP

	END
