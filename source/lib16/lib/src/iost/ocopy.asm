; OCOPY.ASM--
; Copyright (C) 2015 Doszip Developers

include iost.inc

	.code

ocopy	PROC _CType PUBLIC len:DWORD
ifdef __3__
	push	esi
	mov	eax,len
	test	eax,eax
	jnz	@F
    ocopy_success:
	sub	ax,ax
	inc	ax
    ocopy_end:
	pop	esi
	ret
      @@:
	mov	esi,eax
      @@:
	mov	ax,STDI.ios_c
	sub	ax,STDI.ios_i
	jz	@F
	call	ogetc
	jz	ocopy_end
	call	oputc
	jz	ocopy_end
	dec	esi
	jz	ocopy_success
	jmp	@B
      @@:
	call	oflush		; flush STDO
	jz	ocopy_end	; do block copy of bytes left
	push	STDO.ios_size
	push	STDO.ios_bp
	mov	eax,STDI.ios_bp
	mov	STDO.ios_bp,eax
	mov	ax,STDI.ios_size
	mov	STDO.ios_size,ax
      @@:
	call	ofread
	jz	ocopy_eof
	movzx	eax,STDI.ios_c	; count
	cmp	eax,esi
	jae	ocopy_last
	sub	esi,eax
	mov	STDO.ios_i,ax
	mov	STDI.ios_i,ax
	call	oflush
	jnz	@B
    ocopy_exit:
	mov	dx,ax
	pop	eax
	mov	STDO.ios_bp,eax
	pop	ax
	mov	STDO.ios_size,ax
	mov	ax,dx
	jmp	ocopy_end
    ocopy_last:
	mov	STDI.ios_i,si
	mov	STDO.ios_i,si
	call	oflush
	jmp	ocopy_exit
    ocopy_eof:
	mov	eax,esi
	test	eax,eax
	jnz	ocopy_exit
	inc	ax
	jmp	ocopy_exit
else
	push	si
	push	di
	mov	di,WORD PTR len
	mov	si,WORD PTR len+2
	test	si,si
	jnz	ocopy_start
	test	di,di
	jnz	ocopy_start	; copy zero byte -- ok
    ocopy_success:
	xor	ax,ax
	inc	ax
	jmp	ocopy_end
    ocopy_start:
	mov	ax,STDI.ios_c	; flush inbuf
	sub	ax,STDI.ios_i
	or	si,si
	jnz	ocopy_bigbuf
	cmp	ax,di
	jae	ocopy_inbuf
    ocopy_bigbuf:
	test	ax,ax
	jz	ocopy_block
    ocopy_inbuf:
	call	ogetc
	jz	ocopy_end
	call	oputc
	jz	ocopy_end
	sub	di,ax
	sbb	si,0
	mov	ax,si
	or	ax,di
	jz	ocopy_success	; success if zero (inbuf > len)
	mov	ax,STDI.ios_i
	cmp	ax,STDI.ios_c
	jne	ocopy_inbuf	; do byte copy from STDI to STDO
    ocopy_block:
	call	oflush		; flush STDO
	jz	ocopy_end	; do block copy of bytes left
	push	STDO.ios_size
	pushm	STDO.ios_bp
	movmx	STDO.ios_bp,STDI.ios_bp
	mov	ax,STDI.ios_size
	mov	STDO.ios_size,ax
    ocopy_next:
	call	ofread
	jz	ocopy_eof
	mov	ax,STDI.ios_c	; count
	test	si,si
	jnz	ocopy_more
	cmp	ax,di
	jae	ocopy_last
    ocopy_more:
	sub	di,ax
	sbb	si,0
	mov	STDO.ios_i,ax	; fill STDO
	mov	STDI.ios_i,ax	; flush STDI
	call	oflush		; flush STDO
	jnz	ocopy_next	; copy next block
    ocopy_exit:
	mov	dx,ax
	pop	ax
	mov	WORD PTR STDO.ios_bp,ax
	pop	ax
	mov	WORD PTR STDO.ios_bp+2,ax
	pop	ax
	mov	STDO.ios_size,ax
	mov	ax,dx
    ocopy_end:
	pop	di
	pop	si
	ret
    ocopy_last:
	mov	STDI.ios_i,di
	mov	STDO.ios_i,di
	call	oflush
	jmp	ocopy_exit
    ocopy_eof:
	xor	ax,ax
	test	si,si
	jnz	ocopy_exit
	test	di,di
	jnz	ocopy_exit
	inc	ax
	jmp	ocopy_exit
endif
ocopy	ENDP

	END
