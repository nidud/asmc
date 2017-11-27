; THELP.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.data
	thelp p? ?
	thelp_stack p? 10 dup(?)
	stack_index dw ?

	.code

thelpinit PROC _CType PUBLIC hproc:size_p
	mov	ax,WORD PTR hproc
	mov	WORD PTR thelp,ax
	mov	WORD PTR thelp_stack,ax
ifdef __l__
	mov	dx,WORD PTR hproc+2
	mov	WORD PTR thelp+2,dx
	mov	WORD PTR thelp_stack+2,dx
endif
	ret
thelpinit ENDP

thelp_set PROC _CType PUBLIC hproc:size_p
	inc	stack_index
	push	bx
	mov	bx,stack_index
ifdef __l__
	shl	bx,2
else
	add	bx,bx
endif
	mov	ax,WORD PTR hproc
	mov	WORD PTR thelp,ax
ifdef __l__
	mov	dx,WORD PTR hproc+2
	mov	WORD PTR thelp+2,dx
	mov	WORD PTR thelp_stack[bx+2],dx
endif
	mov	WORD PTR thelp_stack[bx],ax
	pop	bx
	ret
thelp_set ENDP

thelp_pop PROC _CType PUBLIC
	push	ax
	push	bx
	dec	stack_index
	mov	bx,stack_index
ifdef __l__
	shl	bx,2
	mov	ax,WORD PTR thelp_stack[bx+2]
	mov	WORD PTR thelp+2,ax
else
	add	bx,bx
endif
	mov	ax,WORD PTR thelp_stack[bx]
	mov	WORD PTR thelp,ax
	pop	bx
	pop	ax
	ret
thelp_pop ENDP

	END
