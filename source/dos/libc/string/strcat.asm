; STRCAT.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

strcat PROC _CType PUBLIC USES si di s1:PTR BYTE, s2:PTR BYTE
	push	ds
	cld?
	mov	al,0
	les	di,s1
	lds	si,s2
	mov	cx,-1
	repne	scasb
	dec	di
      @@:
	mov	al,[si]
	mov	es:[di],al
	inc	di
	inc	si
	test	al,al
	jnz	@B
	lodm	s1
	pop	ds
	ret
strcat ENDP

	END
