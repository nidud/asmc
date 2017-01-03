; STRICMP.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

stricmp PROC _CType PUBLIC USES si di s1:PTR BYTE, s2:PTR BYTE
	push	ds
	les	di,s1
	lds	si,s2
	mov	al,-1
      @@:
	test	al,al
	jz	@F
	mov	al,[si]
	mov	ah,es:[di]
	inc	si
	inc	di
	cmp	ah,al
	je	@B
	cmpaxi
	je	@B
	sbb	al,al
	sbb	al,-1
      @@:
	cbw
	pop	ds
	ret
stricmp ENDP

	END
