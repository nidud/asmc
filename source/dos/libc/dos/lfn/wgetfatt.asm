; WGETFATT.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc

	.code

wgetfattr PROC _CType PUBLIC USES bx path:DWORD
	push	ds
	lds	dx,path
	stc
	mov	ax,7143h
	mov	bl,0
	int	21h
	pop	ds
	jc	wgetfattr_error
	mov	ax,cx
    wgetfattr_toend:
	ret
    wgetfattr_error:
	call	osmaperr
	jmp	wgetfattr_toend
wgetfattr ENDP

	END
