include consx.inc
include string.inc
include alloc.inc
include stdio.inc
include limits.inc

	.code

	OPTION WIN64:3, STACKBASE:rsp

cliprintf PROC USES rsi rdi rbx format:LPSTR, args:VARARG

	local	o:_iobuf

	mov	o._flag,_IOWRT or _IOSTRG
	mov	o._cnt,INT_MAX
	lea	rax,_bufin
	mov	o._ptr,rax
	mov	o._base,rax
	_output( addr o, format, addr args )
	mov	rcx,o._ptr
	mov	BYTE PTR [rcx],0
	.if	rax
		mov	rdi,rax
		.if	OpenClipboard( 0 )
			call	EmptyClipboard
			inc	rdi
			.if	GlobalAlloc( GMEM_MOVEABLE or GMEM_DDESHARE, rdi )
				dec	rdi
				mov	rsi,rax
				GlobalLock( rax )
				mov	rbx,rax
				strcpy( rbx, addr _bufin )
				GlobalUnlock( rsi )
				SetClipboardData( CF_TEXT, rbx )
				mov	rax,rdi
			.endif
			mov	rbx,rax
			call	CloseClipboard
			mov	rax,rbx
		.endif
	.endif
	ret
cliprintf ENDP

	END
