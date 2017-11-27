; FBFFIRST.ASM--
; Copyright (C) 2015 Doszip Developers

include fblk.inc
include wsub.inc

	.code

fbffirst PROC _CType PUBLIC fcb:DWORD, count:size_t
	xor	dx,dx
	jmp	fbffirst_init
    fbffirst_loop:
	mov	ax,dx
	shl	ax,2
	push	bx
	les	bx,fcb
	add	bx,ax
	les	bx,es:[bx]
	mov	cx,es:[bx]
	mov	ax,bx
	pop	bx
	test	cx,_A_SELECTED
	jz	fbffirst_next
	mov	dx,es
	jmp	fbffirst_end
    fbffirst_next:
	inc	dx
    fbffirst_init:
	cmp	count,dx
	jg	fbffirst_loop
	xor	ax,ax
	mov	dx,ax
    fbffirst_end:
	ret
fbffirst ENDP

	END
