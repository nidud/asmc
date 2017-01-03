; STRSTR.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

strstr	PROC _CType PUBLIC USES bx si di s1:PTR BYTE, s2:PTR BYTE
	push	ds
	les	di,s1
	mov	dx,es
	lds	si,s2
	cmp	BYTE PTR [si],0
	je	strstr_nul
    strstr_lup:
	mov	ah,[si]
      @@:
	mov	al,es:[di]
	test	al,al
	jz	strstr_nul
	inc	di
	cmp	al,ah
	jne	@B
	mov	bx,di
	inc	si
      @@:
	mov	al,[si]
	test	al,al
	jz	@F
	cmp	es:[bx],al
	jne	@F
	inc	si
	inc	bx
	jmp	@B
	dec	si
      @@:
	cmp	BYTE PTR [si],0
	mov	si,WORD PTR s2
	jne	strstr_lup
	mov	ax,di
	dec	ax
    strstr_end:
	pop	ds
	ret
    strstr_nul:
	sub	ax,ax
	mov	dx,ax
	jmp	strstr_end
strstr	ENDP

	END
