; WFULLPAT.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc
include dir.inc

	.code

wfullpath PROC _CType PUBLIC buf:DWORD, drv:WORD
	push	WORD PTR buf+2
	mov	ax,WORD PTR buf
	add	ax,3
	push	ax
	push	drv
	call	wgetcwd
	or	ax,dx
	jz	wfullpath_02
	mov	ax,drv
	test	ax,ax
	jz	wfullpath_00
	add	al,'@'
	jmp	wfullpath_01
    wfullpath_00:
	call	getdrv
	add	al,'A'
    wfullpath_01:
	les	bx,buf
	mov	ah,':'
	mov	es:[bx],ax
	mov	al,'\'
	mov	es:[bx+2],al
	mov	dx,es
	mov	ax,bx
    wfullpath_02:
	ret
wfullpath ENDP

	END
