; MEMCMP.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

memcmp	PROC _CType PUBLIC USES si di s1:PTR BYTE, s2:PTR BYTE, len:size_t
	push	ds
	les	di,s1
	lds	si,s2
	mov	cx,len
	cld?
	repe	cmpsb
	mov	ax,cx
	pop	ds
	ret
memcmp	ENDP

	END
