; WCPATH.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include string.inc

	.code

wcpath	PROC _CType PUBLIC USES bx b:DWORD, l:size_t, p:DWORD
	push	ds
	push	si
	lds	si,b
	invoke	strlen,p
	mov	cx,ax
	mov	dx,WORD PTR p
	mov	ax,WORD PTR b
	cmp	cx,l
	jbe	wcpath_end
	mov	bx,dx
	add	dx,cx
	mov	cx,l
	sub	dx,cx
	add	dx,4
	cmp	BYTE PTR es:[bx][1],':'
	jne	@F
	mov	ax,es:[bx]
	mov	[si],al
	mov	[si+2],ah
	mov	ax,si
	add	si,4
	mov	bh,es:[bx+2]
	mov	bl,'.'
	add	ax,4
	add	dx,2
	sub	cx,2
	jmp	wcpath_set
      @@:
	mov	bx,'/.'
    wcpath_set:
	mov	[si],bh
	mov	[si+2],bl
	mov	[si+4],bl
	mov	[si+6],bh
	add	ax,8
	sub	cx,4
    wcpath_end:
	pop	si
	pop	ds
	ret
wcpath	ENDP

	END
