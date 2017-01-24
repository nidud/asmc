include consx.inc
include string.inc
include alloc.inc
include stdio.inc
include limits.inc

	.code

	OPTION WIN64:3, STACKBASE:rsp

cliprintf PROC USES rsi rdi rbx format:LPSTR, args:VARARG

	local	o:S_FILE

	mov	o.iob_flag,_IOWRT or _IOSTRG
	mov	o.iob_cnt,INT_MAX
	lea	rax,_bufin
	mov	o.iob_ptr,rax
	mov	o.iob_base,rax
	_output( addr o, format, addr args )
	mov	rcx,o.iob_ptr
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
