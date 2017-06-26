; EMMFREE.ASM--
; Copyright (C) 2015 Doszip Developers
include alloc.inc

	.code

emmfree PROC _CType PUBLIC handle
	mov	dx,handle	; DX EMM handle
	mov	ah,45h	; RELEASE HANDLE AND MEMORY
	int	67h
	test	ah,ah
	mov	ax,0
	jz	@F
	dec	ax
@@:
	ret
emmfree ENDP

	END
