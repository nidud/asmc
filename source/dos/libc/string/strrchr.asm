; STRRCHR.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

strrchr PROC _CType PUBLIC USES di s1:PTR BYTE, char:size_t
	les	di,s1
	sub	ax,ax
	mov	dx,ax
	cld?
	mov	cx,-1
	repne	scasb
	not	cx
	dec	di
	std
	mov	al,BYTE PTR char
	repne	scasb
	mov	al,0
	jne	@F
	mov	dx,es
	mov	ax,di
	inc	ax
      @@:
	cld
	test	ax,ax
	ret
strrchr ENDP

	END
