; STRNCPY.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

strncpy PROC _CType PUBLIC USES si di s1:PTR BYTE, s2:PTR BYTE, count:size_t
	push	ds
	lds	si,s2
	les	di,s1
	sub	ax,ax
	mov	cx,count
	cld?
      @@:
	movsb
	dec	cx
	jz	@F
	cmp	[si-1],al
	jne	@B
      @@:
	lodm	s1
	pop	ds
	ret
strncpy ENDP

	END
