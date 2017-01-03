; RSUNZIPC.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include alloc.inc

	.code

rsunzipch PROC PUBLIC
	push	bx
    rsunzipch_00:
	lodsb
	mov	dl,al
	and	dl,0F0h
	cmp	dl,0F0h
	jnz	rsunzipch_01
	mov	ah,al
	lodsb
	and	ax,0FFFh
	mov	bx,ax
	lodsb
      @@:
	stosb
	inc	di
	dec	bx
	jz	rsunzipch_02
	dec	cx
	jnz	@B
	jmp	rsunzipch_end
    rsunzipch_01:
	stosb
	inc	di
    rsunzipch_02:
	dec	cx
	jnz	rsunzipch_00
    rsunzipch_end:
	pop	bx
	ret
rsunzipch ENDP

	END
