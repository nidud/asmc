; RSUNZIPA.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

externdef at_background:BYTE
externdef at_foreground:BYTE

	.code

rcunzipat_04:
	mov	ah,al
	and	ax,0FF0h
	shr	al,4
	mov	bh,0
	mov	bl,al
	mov	al,ss:[bx+at_background]
	mov	bl,ah
	or	al,ss:[bx+at_foreground]
	ret

rsunzipat PROC PUBLIC
	push	bx
    rcunzipat_00:
	lodsb
	mov	dl,al
	and	dl,0F0h
	cmp	dl,0F0h
	jne	rcunzipat_01
	mov	ah,al
	lodsb
	and	ax,0FFFh
	mov	dx,ax
	lodsb
	call	rcunzipat_04
      @@:
	stosb
	inc	di
	dec	dx
	jz	rcunzipat_02
	dec	cx
	jnz	@B
	jmp	rcunzipat_end
    rcunzipat_01:
	call	rcunzipat_04
	stosb
	inc	di
    rcunzipat_02:
	dec	cx
	jnz	rcunzipat_00
    rcunzipat_end:
	pop	bx
	ret
rsunzipat ENDP

	END
