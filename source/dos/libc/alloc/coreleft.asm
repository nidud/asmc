; CORELEFT.ASM--
; Copyright (C) 2015 Doszip Developers
include alloc.inc

extrn	brklvl:WORD
extrn	heaptop:WORD

	.code

coreleft PROC _CType PUBLIC
	mov	ax,heaptop
	sub	ax,brklvl
	mov	cl,4
	mov	dh,00h
	mov	dl,ah
	shr	dx,cl
	shl	ax,cl
	ret
coreleft ENDP

	END
