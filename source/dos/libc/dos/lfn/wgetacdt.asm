; WGETACDT.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc

	.code

wgetacdate PROC _CType PUBLIC USES di bx path:DWORD
	push	ds
	lds	dx,path
	stc
	mov	ax,7143h
	mov	bl,6
	int	21h
	pop	ds
	jc	wgetacdate_error
	mov	ax,di
    wgetacdate_toend:
	ret
    wgetacdate_error:
	call	osmaperr
	jmp	wgetacdate_toend
wgetacdate ENDP

	END
