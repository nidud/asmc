include consx.inc
include alloc.inc

	.code

scputws PROC USES esi edi ecx edx x, y, l, wp:PVOID
local	rect:SMALL_RECT
local	lbuf[TIMAXSCRLINE]:CHAR_INFO
	mov esi,wp
	lea edi,lbuf
	mov ecx,l
	.ifs ecx < 0
		not ecx
	.endif
	xor eax,eax
	.repeat
		lodsb
		stosw
		lodsb
		stosw
	.untilcxz
	free( wp )
	movzx eax,BYTE PTR x
	movzx edx,BYTE PTR y
	mov rect.Top,dx
	mov rect.Left,ax
	mov ecx,l
	.ifs ecx < 0
		not ecx
		mov l,ecx
		add edx,ecx
		dec edx
		shl ecx,16
		mov cx,1
	.else
		add eax,ecx
		add ecx,10000h
	.endif
	mov rect.Right,ax
	mov rect.Bottom,dx
	WriteConsoleOutput( hStdOutput, addr lbuf, ecx, 0, addr rect )
	ret
scputws ENDP

	END
