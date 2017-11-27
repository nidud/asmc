; UNIXDOS.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

unixtodos PROC _CType PUBLIC USES si string:PTR BYTE
	push	ds
	lds	si,string
	mov	ah,'\'
      @@:
	mov	al,[si]
	inc	si
	test	al,al
	jz	@F
	cmp	al,'/'
	jne	@B
	mov	[si-1],ah
	jmp	@B
      @@:
	lodm	string
	pop	ds
	ret
unixtodos ENDP

	END
