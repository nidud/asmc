; MEMMOVW.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

memmovw PROC _CType PUBLIC USES si di s1:PTR BYTE, s2:PTR BYTE, cnt:size_t
	push	ds
	les	di,s1
	lds	si,s2
	mov	cx,cnt
	mov	ax,di
	mov	dx,WORD PTR s1+2
	std
	add	si,cx
	add	di,cx
	sub	si,2
	sub	di,2
	shr	cx,1
	rep	movsw
	cld
	pop	ds
	ret
memmovw ENDP

	END
