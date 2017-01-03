; WCPUSHST.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.data
	wcvisible db 0

	.code

wcstline:
	push	bx
	mov	bx,0150h
	mov	ch,_scrrow
	mov	cl,0
	invoke	rcxchg,bx::cx,dx::ax
	pop	bx
	ret

wcpushst PROC _CType PUBLIC USES bx wc:DWORD, cp:DWORD
	cmp	wcvisible,1
	jne	wcpushst_00
	lodm	wc
	call	wcstline
    wcpushst_00:
	mov	al,' '
	mov	ah,at_background[B_Menus]
	or	ah,at_foreground[F_Menus]
	invoke	wcputw,wc,80,ax
	les	bx,wc
	mov	BYTE PTR es:[bx][36],179
	add	bx,2
	invoke	wcputs,es::bx,80,80,cp
	lodm	wc
	call	wcstline
	mov	wcvisible,1
	ret
wcpushst ENDP

wcpopst PROC _CType PUBLIC wp:DWORD
	lodm	wp
	call	wcstline
	xor	wcvisible,1
	ret
wcpopst ENDP

	END
