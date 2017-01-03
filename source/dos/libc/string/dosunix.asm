; DOSUNIX.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

dostounix PROC _CType PUBLIC USES di string:PTR BYTE
	les	di,string
	mov	ah,'/'
      @@:
	mov	al,es:[di]
	inc	di
	test	al,al
	jz	@F
	cmp	al,'\'
	jne	@B
	mov	es:[di-1],ah
	jmp	@B
      @@:
	lodm	string
	ret
dostounix ENDP

	END
