; WSFREE.ASM--
; Copyright (C) 2015 Doszip Developers

include wsub.inc
include alloc.inc

	.code

wsfree	PROC _CType PUBLIC USES si di bx wsub:DWORD
	les	bx,wsub
	mov	si,es:[bx].S_WSUB.ws_count
	sub	ax,ax
	cmp	ax,WORD PTR es:[bx].S_WSUB.ws_fcb
	mov	es:[bx].S_WSUB.ws_count,ax
	je	wsfree_end
	mov	di,ax
	jmp	wsfree_next
    wsfree_loop:
	dec	si
	les	dx,[bx].S_WSUB.ws_fcb
	mov	ax,si
	shl	ax,2
	add	dx,ax
	sub	ax,ax
	xchg	bx,dx
	mov	cx,es:[bx+2]
	mov	es:[bx+2],ax
	xchg	ax,es:[bx]
	xchg	bx,dx
	test	ax,ax
	je	wsfree_next
	invoke	free,cx::ax
	inc	di
    wsfree_next:
	test	si,si
	jnz	wsfree_loop
	mov	ax,di
    wsfree_end:
	ret
wsfree	ENDP

	END
