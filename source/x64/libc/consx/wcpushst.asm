include consx.inc

	.data
	wcvisible db 0

	.code

	OPTION	WIN64:2, STACKBASE:rsp

wcstline:
	mov	ecx,_scrcol
	mov	ch,1
	shl	ecx,16
	mov	ch,BYTE PTR _scrrow
	rcxchg( ecx, rax )
	ret

wcpushst PROC USES rsi rbx wc:PVOID, cp:LPSTR

	mov	rsi,rdx
	mov	rbx,rcx

	.if	wcvisible == 1
		mov	rax,rcx
		call	wcstline
	.endif
	mov	al,' '
	mov	ah,at_background[B_Menus]
	or	ah,at_foreground[F_KeyBar]
	wcputw( rbx, _scrcol, eax )
	mov	BYTE PTR [rbx+36],179
	add	rbx,2
	wcputs( rbx, _scrcol, _scrcol, rsi )
	lea	rax,[rbx-2]
	call	wcstline
	mov	wcvisible,1
	ret
wcpushst ENDP

wcpopst PROC wp:PVOID
	mov	rax,rcx
	call	wcstline
	xor	wcvisible,1
	ret
wcpopst ENDP

	END
