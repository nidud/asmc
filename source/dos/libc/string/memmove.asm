; MEMMOVE.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

memmove PROC _CType PUBLIC USES si di s1:PTR BYTE, s2:PTR BYTE, cnt:size_t
	push	ds
	les	di,s1
	lds	si,s2
	mov	cx,cnt
	mov	dx,WORD PTR s1+2
	mov	ax,di
	cld?
	cmp	ax,si
	jbe	@F
	std
	add	si,cx
	add	di,cx
	sub	si,1
	sub	di,1
      @@:
	rep	movsb
	cld
	pop	ds
	ret
memmove ENDP

	END
