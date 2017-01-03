; WSETFATT.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc

	.code

wsetfattr PROC _CType PUBLIC USES bx path:DWORD, attrib:WORD
	push	ds
	lds	dx,path
	mov	cx,attrib
	stc
	mov	ax,7143h
	mov	bl,1
	int	21h
	pop	ds
	jc	wsetfattr_error
	xor	ax,ax
    wsetfattr_toend:
	ret
    wsetfattr_error:
	call	osmaperr
	jmp	wsetfattr_toend
wsetfattr ENDP

	END
