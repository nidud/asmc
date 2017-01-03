; SCPUTS.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include mouse.inc

	.code

scputs	PROC _CType PUBLIC USES si di x:size_t, y:size_t, a:size_t,
	l:size_t, string:DWORD
	push	es
	push	ds
	push	bx
	push	cx
	push	dx
	mov	al,BYTE PTR x
	mov	ah,BYTE PTR y
	call	__getxypm
	mov	es,dx
	mov	di,ax
	lds	si,string
	mov	ch,0
	mov	dh,0
	mov	cl,BYTE PTR l
	mov	dl,_scrcol
	add	dx,dx
	mov	ah,BYTE PTR a
	call	__wputs
	ShowMouseCursor
	pop	dx
	pop	cx
	pop	bx
	pop	ds
	pop	es
	ret
scputs	ENDP

	END
