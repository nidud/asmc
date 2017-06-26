; ALLOC.ASM--
; Copyright (C) 2015 Doszip Developers
include alloc.inc
include errno.inc

mb	STRUC
mb_size dw ?
mb_used dw ?
mb	ENDS

extrn	_psp:WORD
extrn	heapbase:WORD
extrn	brklvl:WORD
extrn	heaptop:WORD
extrn	heapfree:WORD

.code

resize_block:
	mov	bx,ax
	mov	ax,ss:_psp
	sub	bx,ax
	mov	es,ax
	mov	ah,4Ah
	int	21h
	ret

create_heap:
	mov	ax,ss:heapbase
	inc	ax
	cmp	ax,ss:heaptop
	ja	create_heap_failed
	call	resize_block
	jc	create_heap_failed
	mov	ax,ss:heapbase
	mov	ss:brklvl,ax
	mov	ss:heapfree,ax
	mov	es,ax
	xor	ax,ax
	mov	bx,ax
	mov	es:[bx].mb.mb_size,ax
	inc	ax
	mov	es:[bx].mb.mb_used,ax
	ret
    create_heap_failed:
	xor	ax,ax
	ret

extend_heap:
	mov	ax,ss:brklvl
	inc	ax
	add	ax,cx
	cmp	ax,ss:heaptop
	ja	extend_heap_failed
	call	resize_block
	jc	extend_heap_failed
	mov	ax,ss:brklvl
	mov	es,ax
	xor	bx,bx
	mov	es:[bx].mb.mb_size,cx
	mov	dx,ax
	add	ax,cx
	mov	ss:brklvl,ax
	mov	es,ax
	xor	ax,ax
	mov	es:[bx].mb.mb_size,ax
	inc	ax
	mov	es:[bx].mb.mb_used,ax
	ret
    extend_heap_failed:
	xor	ax,ax
	ret

getmaxblock:
	push	si
	push	di
	push	bx
	xor	cx,cx		; max size of block
	mov	ax,ss:heapbase	; segment of block
	mov	dx,ax
	mov	bx,cx
	mov	si,ax		; segment of last block
    getmaxblock_loop:
	mov	es,ax
	mov	di,es:[bx].mb.mb_size
	test	di,di
	jz	getmaxblock_exit
	mov	si,ax
	cmp	es:[bx].mb.mb_used,bx
	jne	getmaxblock_next
	add	ax,di
	mov	es,ax
	cmp	es:[bx].mb.mb_used,bx
	jne	getmaxblock_set
	mov	ax,es:[bx].mb.mb_size
	test	ax,ax
	jz	getmaxblock_set
	add	di,ax
	mov	ax,si
	mov	es,ax
	mov	es:[bx].mb.mb_size,di
	jmp	getmaxblock_loop
    getmaxblock_set:
	mov	ax,si
	cmp	di,cx
	jb	getmaxblock_next
	mov	cx,di
	mov	dx,ax
    getmaxblock_next:
	add	ax,di
	jmp	getmaxblock_loop
    getmaxblock_exit:
	mov	ax,si		; last block
	test	cx,cx
	jz	getmaxblock_end
	mov	ss:heapfree,dx
    getmaxblock_end:
	pop	bx
	pop	di
	pop	si
	ret

free	PROC _CType PUBLIC USES bx maddr:DWORD
	mov ax,WORD PTR maddr+2
	mov cx,ss:brklvl
	.if ax >= ss:heapbase && ax < cx
	    mov es,ax
	    xor bx,bx
	    add ax,es:[bx]
	    mov es:[bx+2],bx
	    .if ax == cx
		call getmaxblock
		mov es,ax
		mov es:[bx],bx
		inc bx
		mov es:[bx+1],bx
		mov ss:brklvl,ax
		inc ax
		call resize_block
	    .else
		mov ax,es
		mov ss:heapfree,ax
	    .endif
	.else
	    xor ax,ax
	.endif
	ret
free	ENDP

palloc	PROC _CType PUBLIC USES bx
	test	ax,ax
	jz	palloc_failed
	mov	cx,ax
	mov	ax,ss:heapfree
	test	ax,ax
	jz	palloc_create
	mov	es,ax
	mov	dx,ax
	xor	bx,bx
	cmp	es:[bx+2],bl
	mov	ax,es:[bx]
	je	palloc_found
    palloc_find:
	push	cx
	call	getmaxblock
	mov	ax,cx
	pop	cx
	jz	palloc_extend
	cmp	ax,cx
	jb	palloc_extend
	mov	es,dx
    palloc_found:
	cmp	ax,cx
	jb	palloc_find
	mov	WORD PTR es:[bx+2],1
	je	palloc_set
	mov	es:[bx],cx
	sub	ax,cx
	add	cx,dx
	mov	es,cx
	mov	es:[bx],ax
	mov	es:[bx+2],bx
	mov	es,dx
    palloc_set:
	mov	ax,es:[bx]
	add	ax,dx
	mov	ss:heapfree,ax
    palloc_seto:
	mov	ax,4
    palloc_end:
	test	ax,ax
	ret
    palloc_create:
	call	create_heap
	jz	palloc_failed
    palloc_extend:
	call	extend_heap
	jnz	palloc_seto
    palloc_failed:
	mov	ss:errno,ENOMEM
	xor	ax,ax
	cwd
	jmp	palloc_end
palloc	ENDP

malloc	PROC _CType PUBLIC msize:WORD
	mov ax,msize
	add ax,4
	.if CARRY?
	    mov ax,1001h
	.else
	    mov dl,al
	    shr ax,4
	    .if dl & 15
		inc ax
	    .endif
	.endif
	call palloc
	or ax,ax
	ret
malloc	ENDP

	END
