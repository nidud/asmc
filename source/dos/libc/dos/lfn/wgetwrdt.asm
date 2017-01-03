; WGETWRDT.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc

	.code

wgetwrdate PROC _CType PUBLIC USES di bx path:DWORD
	push	ds
	lds	dx,path
	stc
	mov	ax,7143h
	mov	bl,4
	int	21h
	pop	ds
	jc	wgetwrdate_error
	mov	ax,cx
	mov	dx,di
    wgetwrdate_toend:
	ret
    wgetwrdate_error:
	call	osmaperr
	cwd
	jmp	wgetwrdate_toend
wgetwrdate ENDP

	END
