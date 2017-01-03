; WSETACDT.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc

	.code

wsetacdate PROC _CType PUBLIC USES di bx path:DWORD, acdate:WORD
	push	ds
	lds	dx,path
	mov	di,acdate
	stc
	mov	ax,7143h
	mov	bl,5
	int	21h
	pop	ds
	jc	wsetacdate_error
	xor	ax,ax
    wsetacdate_toend:
	ret
    wsetacdate_error:
	call	osmaperr
	jmp	wsetacdate_toend
wsetacdate ENDP

	END
