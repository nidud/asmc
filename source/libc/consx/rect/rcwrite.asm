include consx.inc

	.code

rcwrite proc uses esi edi ebx rc, wc:PVOID
local	y,col,row:dword
local	bz:COORD
local	rect:SMALL_RECT
local	lbuf[TIMAXSCRLINE]:CHAR_INFO
	movzx	eax,rc.S_RECT.rc_col
	mov	col,eax
	mov	bz.x,ax
	mov	bz.y,1
	movzx	eax,rc.S_RECT.rc_row
	mov	row,eax
	movzx	eax,rc.S_RECT.rc_x
	mov	rect.Left,ax
	add	eax,col
	dec	eax
	mov	rect.Right,ax
	movzx	eax,rc.S_RECT.rc_y
	mov	y,eax
	lea	edi,lbuf
	xor	eax,eax
	mov	ecx,col
	rep	stosd
	mov	esi,wc
	mov	ebx,row
	.repeat
		lea edi,lbuf
		mov ecx,col
		.repeat
			mov ax,[esi]
			add esi,2
			mov [edi],al
			mov [edi+2],ah
			add edi,SIZE CHAR_INFO
		.untilcxz
		mov eax,y
		add eax,row
		sub eax,ebx
		mov rect.Top,ax
		mov rect.Bottom,ax
		.break .if !WriteConsoleOutput( hStdOutput, addr lbuf, bz, 0, addr rect )
		dec ebx
	.until	ZERO?
	ret
rcwrite endp

	END
