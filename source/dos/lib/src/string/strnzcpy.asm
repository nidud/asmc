; STRNZCPY.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

strnzcpy PROC _CType PUBLIC USES si di s1:PTR BYTE, s2:PTR BYTE, count:size_t
	push	ds
	lds	si,s2
	les	di,s1
	sub	ax,ax
	mov	cx,count
	cmp	cx,2
	jb	toend
	dec	cx
	cld?
      @@:
	movsb
	dec	cx
	jz	@F
	cmp	[si-1],al
	jne	@B
      @@:
	mov	es:[di],al
toend:
	lodm	s1
	pop	ds
	ret
strnzcpy ENDP

	END
