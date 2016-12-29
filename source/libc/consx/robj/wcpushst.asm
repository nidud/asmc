include consx.inc

	.data
	wcvisible db 0

	.code

wcstline PROC PRIVATE
	mov	ecx,_scrcol
	mov	ch,1
	shl	ecx,16
	mov	ch,BYTE PTR _scrrow
	rcxchg( ecx, eax )
	ret
wcstline ENDP

wcpushst PROC USES ebx wc:PVOID, cp:LPSTR
	.if	wcvisible == 1
		mov	eax,wc
		call	wcstline
	.endif
	mov	al,' '
	mov	ah,at_background[B_Menus]
	or	ah,at_foreground[F_KeyBar]
	wcputw( wc, _scrcol, eax )
	mov	ebx,wc
	mov	BYTE PTR [ebx+36],179
	add	ebx,2
	wcputs( ebx, _scrcol, _scrcol, cp )
	mov	eax,wc
	call	wcstline
	mov	wcvisible,1
	ret
wcpushst ENDP

wcpopst PROC wp:PVOID
	mov	eax,wp
	call	wcstline
	xor	wcvisible,1
	ret
wcpopst ENDP

	END
