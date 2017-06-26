; EMMALLOC.ASM--
; Copyright (C) 2015 Doszip Developers
include alloc.inc

	.code

emmalloc PROC _CType PUBLIC pages:word
	push	bx
	mov	bx,pages
	mov	ah,43h
	int	67h
	pop	bx
	test	ah,ah
	jz	@F
	mov	dx,-1
@@:
	mov	ax,dx
	ret
emmalloc ENDP

	END
