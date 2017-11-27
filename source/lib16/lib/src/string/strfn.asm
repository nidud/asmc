; STRFN.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

strfn	PROC _CType PUBLIC USES di s1:PTR BYTE
	les	di,s1
	sub	ax,ax
	mov	cx,ax
	dec	cx
	cld?
	repne	scasb
	not	cx
      @@:
	dec	di
	mov	al,es:[di]
	cmp	al,'/'
	je	@F
	cmp	al,'\'
	je	@F
	dec	cx
	jnz	@B
      @@:
	lodm	s1
	cmp	di,ax
	je	@F
	cmp	BYTE PTR es:[di],0
	je	@F
	mov	ax,di
	inc	ax
      @@:
	ret
strfn ENDP

	END
