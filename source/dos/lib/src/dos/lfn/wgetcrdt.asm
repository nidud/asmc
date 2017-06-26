; WGETCRDT.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc

	.code

wgetcrdate PROC _CType PUBLIC USES si di bx path:DWORD
	push	ds
	lds	dx,path
	stc
	mov	ax,7143h
	mov	bl,8
	int	21h
	pop	ds
	jc	wgetcrdate_error
	mov	ax,cx
	mov	dx,di
    wgetcrdate_toend:
	ret
    wgetcrdate_error:
	call	osmaperr
	jmp	wgetcrdate_toend
wgetcrdate ENDP

	END
