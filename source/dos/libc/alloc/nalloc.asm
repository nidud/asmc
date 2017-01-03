; NALLOC.ASM--
; Copyright (C) 2015 Doszip Developers

include alloc.inc

extrn _dsstack:WORD
extrn errno:WORD

ENOMEM	   equ 12
MAXHEAPLEN equ 9004

mb	STRUC
mb_size dw ?
mb_used dw ?
mb	ENDS

	.data
	ss_brkl dw 0
	ss_free dw 0
	ss_base equ <offset _dsstack>

	.code

create_heap:
	mov	ax,ss_base
	mov	bx,ax
	mov	ss_brkl,ax
	mov	ss_free,ax
	jmp	extend_heap_set

extend_heap:
	mov	ax,ss_brkl
	add	ax,SIZE mb
	add	ax,cx
	sub	ax,ss_base
	cmp	ax,MAXHEAPLEN
	ja	extend_heap_failed
	mov	ax,ss_brkl
	mov	bx,ax
	mov	[bx].mb.mb_size,cx
	mov	dx,ax
	add	ax,cx
	mov	ss_brkl,ax
	mov	bx,ax
    extend_heap_set:
	sub	ax,ax
	mov	[bx].mb.mb_size,ax
	inc	ax
	mov	[bx].mb.mb_used,ax
	ret
    extend_heap_failed:
	xor	ax,ax
	ret

getmaxblock:
	push	cx
	push	si
	push	di
	mov	si,ss_base
	mov	dx,si		; largest free block
	xor	cx,cx		; size of largest free block
    getmaxblock_do:
	cmp	[si].mb.mb_used,0
	jne	getmaxblock_next
	mov	di,si		; merge free block's
    getmaxblock_add:
	add	si,[si].mb.mb_size
	mov	bx,[si].mb.mb_size
	cmp	[si].mb.mb_used,0	; if next block is free
	jne	getmaxblock_test
	add	[di].mb.mb_size,bx
	jmp	getmaxblock_add
    getmaxblock_test:
	mov	si,di		; update result
	cmp	cx,[si].mb.mb_size
	ja	getmaxblock_next
	mov	cx,[si].mb.mb_size
	mov	dx,si
    getmaxblock_next:
	add	si,[si].mb.mb_size
	cmp	si,ss_brkl
	jb	getmaxblock_do
	mov	ax,cx		; return size in ax
	test	ax,ax
	jz	getmaxblock_end
	mov	ss_free,dx
    getmaxblock_end:
	pop	di
	pop	si
	pop	cx
	ret

nalloc	PROC _CType PUBLIC USES bx dx cx msize:WORD
	mov	ax,msize
	test	ax,ax
	jz	nalloc_failed
	add	ax,SIZE mb
	mov	cx,ax
	mov	ax,ss_free
	test	ax,ax
	jz	nalloc_create
	mov	dx,ax
	mov	bx,ax
	cmp	[bx].mb.mb_used,0
	mov	ax,[bx].mb.mb_size
	je	nalloc_found
    nalloc_find:
	call	getmaxblock
	jz	nalloc_extend
	cmp	ax,cx
	jb	nalloc_extend
    nalloc_found:
	cmp	ax,cx
	jb	nalloc_find
	mov	bx,dx
	mov	[bx].mb.mb_used,1
	je	nalloc_set
	mov	[bx].mb.mb_size,cx
	sub	ax,cx
	add	bx,cx
	mov	[bx].mb.mb_size,ax
	mov	[bx].mb.mb_used,0
	mov	bx,dx
    nalloc_set:
	mov	ax,[bx].mb.mb_size
	add	ax,dx
	mov	ss_free,ax
    nalloc_seto:
	mov	ax,dx
	add	ax,SIZE mb
    nalloc_end:
	test	ax,ax
	ret
    nalloc_create:
	call	create_heap
	jz	nalloc_failed
    nalloc_extend:
	call	extend_heap
	jnz	nalloc_seto
    nalloc_failed:
	mov	errno,ENOMEM
	xor	ax,ax
	jmp	nalloc_end
nalloc	ENDP

nfree	PROC _CType PUBLIC USES ax bx maddr:WORD
	mov ax,maddr
	sub ax,SIZE mb
	.if ax >= ss_base && ax < ss_brkl
	    mov bx,ax
	    add ax,[bx].mb.mb_size
	    mov [bx].mb.mb_used,0
	    .if ax == ss_brkl
		mov [bx].mb.mb_size,0
		mov [bx].mb.mb_used,1
		mov ss_brkl,bx
		mov ss_free,bx
	    .else
		mov ss_free,bx
	    .endif
	.endif
	ret
nfree	ENDP

	END
