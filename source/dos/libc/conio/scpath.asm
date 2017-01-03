; SCPATH.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include mouse.inc

	.code

scpath	PROC _CType PUBLIC USES si di x,y,l:size_t, string:DWORD
	push	ds
	push	es
	push	dx
	push	cx
	mov	al,BYTE PTR x
	mov	ah,BYTE PTR y
	call	__getxypm
	push	ax
	mov	di,ax
	mov	si,dx
	invoke	wcpath,dx::ax,l,string
	xchg	si,dx
	test	cx,cx
	jz	scpath_end
	mov	es,dx
	mov	di,ax
	lds	ax,string
	cld?
      @@:
	movsb
	inc	di
	dec	cx
	jnz	@B
    scpath_end:
	ShowMouseCursor
	pop	dx
	mov	ax,di
	sub	ax,dx
	shr	ax,1
	pop	cx
	pop	dx
	pop	es
	pop	ds
	ret
scpath	ENDP

	END
