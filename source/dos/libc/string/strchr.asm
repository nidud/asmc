; STRCHR.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

strchr	PROC _CType PUBLIC USES di s1:PTR BYTE, char:size_t
	sub	ax,ax
	mov	dx,ax
	les	di,s1
      @@:
	mov	al,es:[di]
	test	al,al
	jz	@F
	inc	di
	cmp	al,BYTE PTR char
	jne	@B
	mov	dx,es
	mov	ax,di
	dec	ax
      @@:
	ret
strchr	ENDP

	END
