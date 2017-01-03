; STRCMPI.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

strcmpi PROC PUBLIC
	push	si
	push	di
      @@:
	mov	ah,[si]
	mov	al,es:[di]
	test	ah,ah
	jz	@F
	cmpaxi
	jne	@F
	inc	si
	inc	di
	jmp	@B
      @@:
	mov	cx,di
	pop	di
	pop	dx
	ret
strcmpi ENDP

	END
