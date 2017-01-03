; WCPUTS.ASM--
; Copyright (C) 2015 Doszip Developers
include conio.inc

	.code

wcputs	PROC _CType PUBLIC USES cx dx si di p:DWORD,
	l:size_t, max:size_t, string:DWORD
	push	ds
	les	di,p
	mov	dl,BYTE PTR l
	mov	dh,0
	add	dx,dx
	mov	cl,BYTE PTR max
	mov	ch,es:[di]+1
	and	ch,0F0h
	.if ch == at_background[B_Menus]
	    or ch,at_foreground[F_MenusKey]
	.elseif ch == at_background[B_Dialog]
	    or ch,at_foreground[F_DialogKey]
	.else
	    sub ch,ch
	.endif
	lds	si,string
	mov	ah,0
	call	__wputs
	pop	ds
	ret
wcputs	ENDP

	END
