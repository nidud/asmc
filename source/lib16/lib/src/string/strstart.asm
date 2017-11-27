; STRSTART.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

strstart PROC _CType PUBLIC USES di string:PTR BYTE
	les	di,string
	mov	dx,es
      @@:
	mov	al,es:[di]
	inc	di
	test	al,al
	jz	@F
	cmp	al,' '
	je	@B
	cmp	al,9
	je	@B
      @@:
	mov	ax,di
	dec	ax
	ret
strstart ENDP

	END
