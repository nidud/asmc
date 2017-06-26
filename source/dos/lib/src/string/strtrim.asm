; STRTRIM.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

strtrim PROC _CType PUBLIC USES di string:PTR BYTE
	les	di,string
	mov	dx,es
	sub	ax,ax
	cld?
	mov	cx,-1
	repne	scasb
	not	cx
	dec	di
	mov	al,' '
      @@:
	dec	di
	dec	cx
	jz	@F
	cmp	es:[di],al
	ja	@F
	mov	es:[di],ah
	jmp	@B
      @@:
	mov	ax,di
	sub	ax,WORD PTR string
	inc	ax
	ret
strtrim ENDP

	END
