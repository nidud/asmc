; STRCMP.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

strcmp	PROC _CType PUBLIC USES si di s1:PTR BYTE, s2:PTR BYTE
	push	ds
	lds	si,s2
	les	di,s1
	mov	al,-1
      @@:
	test	al,al
	jz	@F
	mov	al,[si]
	inc	si
	mov	ah,es:[di]
	inc	di
	cmp	ah,al
	je	@B
	sbb	al,al
	sbb	al,-1
      @@:
	cbw
	pop	ds
	ret
strcmp ENDP

	END
