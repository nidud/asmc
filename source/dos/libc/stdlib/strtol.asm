; STRTOL.ASM--
; Copyright (C) 2015 Doszip Developers

include stdlib.inc

	.code

strtol	PROC _CType PUBLIC USES bx string:PTR BYTE
	push	es
	les	bx,string	; '128'		- long
	mov	ah,'9'		; '128 C:\file' - long
      @@:			; '100h'	- hex
	mov	al,es:[bx]	; 'f3 22'	- hex
	inc	bx
	test	al,al
	jz	strtol_long
	cmp	al,' '
	je	strtol_long
	cmp	al,ah
	jbe	@B
	invoke	xtol,string
    strtol_end:
	pop	es
	ret
    strtol_long:
	invoke	atol,string
	jmp	strtol_end
strtol	ENDP

	END
