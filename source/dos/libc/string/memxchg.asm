; MEMXCHG.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

memxchg PROC _CType PUBLIC USES si di s1:PTR BYTE, s2:PTR BYTE, count:size_t
	push	ds
	les	di,s1
	lds	si,s2
	mov	cx,count
	cld?
      @@:
	mov	al,es:[di]
	movsb
	mov	[si-1],al
	dec	cx
	jnz	@B
	lodm	s1
	pop	ds
	ret
memxchg ENDP

	END
