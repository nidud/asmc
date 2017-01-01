include consx.inc
include string.inc
include alloc.inc

	OPTION WIN64:2, STACKBASE:rsp

	.data

externdef IDD_ClipboardWarning:QWORD

clipbsize dq 0
clipboard dq 0

	.code

ClipboardFree PROC
	free( clipboard )
	xor	eax,eax
	mov	clipbsize,rax
	mov	clipboard,rax
	ret
ClipboardFree ENDP

ClipboardCopy PROC USES rsi rdi rbx string:LPSTR, len:QWORD
	mov	rbx,rcx
	mov	rdi,rdx
	call	ClipboardFree
	mov	eax,console
ifdef __W95__
	and	eax,CON_WIN95 or CON_CLIPB
	.if	eax == CON_CLIPB
else
	and	eax,CON_CLIPB
	.if	eax
endif
		.if	OpenClipboard( 0 )
			call	EmptyClipboard
			inc	rdi
			.if	GlobalAlloc( GMEM_MOVEABLE or GMEM_DDESHARE, rdi )
				dec	rdi
				mov	rsi,rax
				GlobalLock( rax )
				memcpy( rax, rbx, rdi )
				mov	rbx,rax
				mov	BYTE PTR [rbx+rdi],0
				GlobalUnlock( rsi )
				SetClipboardData( CF_TEXT, rbx )
				mov	rax,rdi
			.endif
			mov	rbx,rax
			call	CloseClipboard
			mov	rax,rbx
		.endif
	.else
		inc	rdi
		.if	malloc( rdi )
			dec	rdi
			memcpy( rax, rbx, rdi )
			mov	BYTE PTR [rax+rdi],0
			mov	clipboard,rax
			mov	clipbsize,rdi
		.endif
	.endif
	ret
ClipboardCopy ENDP

ClipboardPaste PROC USES rbx
	mov	eax,console
ifdef __W95__
	and	eax,CON_WIN95 or CON_CLIPB
	.if	eax == CON_CLIPB
else
	and	eax,CON_CLIPB
	.if	eax
endif
		.if	IsClipboardFormatAvailable( CF_TEXT )
			.if	OpenClipboard( 0 )
				.if	GetClipboardData( CF_TEXT )
					mov	rbx,rax
					.if	strlen( rax )
						mov	clipbsize,rax
						inc	rax
						.if	malloc( rax )
							strcpy( rax, rbx )
							mov	clipboard,rax
						.else
							rsmodal( IDD_ClipboardWarning )
							xor	eax,eax
						.endif
					.endif
				.endif
				mov	rbx,rax
				call	CloseClipboard
				mov	rax,rbx
			.endif
		.endif
	.else
		.if	clipbsize
			mov rax,clipboard
		.else
			xor rax,rax
		.endif
	.endif
	mov	rcx,clipbsize
	test	rax,rax
	ret
ClipboardPaste ENDP

	END
