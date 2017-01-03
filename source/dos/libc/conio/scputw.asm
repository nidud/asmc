; SCPUTW.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include mouse.inc

	.code

ifdef	__scputw__
__scputw PROC PUBLIC
	push	bx
	push	dx
	push	ax
	mov	bx,ax
	mov	ax,dx
	call	__getxypm
	invoke	wcputw,dx::ax,cx,bx
	ShowMouseCursor
	pop	ax
	pop	dx
	pop	bx
	ret
__scputw ENDP
endif

scputw	PROC _CType PUBLIC USES ax x,y,l,w:size_t
	push	dx
	mov	al,BYTE PTR x
	mov	ah,BYTE PTR y
	call	__getxypm
	invoke	wcputw,dx::ax,l,w
	ShowMouseCursor
	pop	dx
	ret
scputw	ENDP

	END
