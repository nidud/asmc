; STRNICMP.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

strnicmp PROC _CType PUBLIC USES si di s1:PTR BYTE, s2:PTR BYTE, count:size_t
	push	ds
	lds	si,s1
	les	di,s2
	mov	cx,count
	inc	cx
      @@:
	dec	cx
	jz	@F
	mov	al,[si]
	mov	ah,es:[di]
	inc	si
	inc	di
	test	al,al
	jz	@F
	cmp	ah,al
	je	@B
	cmpaxi
	je	@B
      @@:
	sub	al,ah
	cbw
	pop	ds
	ret
strnicmp ENDP

	END
