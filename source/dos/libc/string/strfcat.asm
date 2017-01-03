; STRFCAT.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

strfcat PROC _CType PUBLIC USES si di s1:PTR BYTE, s2:PTR BYTE, s3:PTR BYTE
	push	ds
	sub	ax,ax
	les	di,s1
	mov	dx,di
	mov	cx,-1
	cld?
	cmp	WORD PTR s2,ax
	je	@F
	les	di,s2
	repne	scasb
	les	di,s1
	lds	si,s2
	not	cx
	rep	movsb
	jmp	strfcat_test
      @@:
	repne	scasb
    strfcat_test:
	dec	di
	cmp	di,dx
	je	strfcat_loop
	mov	BYTE PTR es:[di],'\'
	dec	di
	mov	al,es:[di]
	cmp	al,'\'
	je	@F
	cmp	al,'/'
	je	@F
	inc	di
      @@:
	inc	di
    strfcat_loop:
	lds	si,s3
      @@:
	mov	al,[si]
	mov	es:[di],al
	inc	di
	inc	si
	test	al,al
	jnz	@B
	mov	es:[di],al
	lodm	s1
	pop	ds
	ret
strfcat ENDP

	END
