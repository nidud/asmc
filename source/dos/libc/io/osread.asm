; OSREAD.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc
include errno.inc

	.code

osread	PROC _CType PUBLIC h:size_t, b:DWORD, z:size_t
	stc
	push	ds
	mov	ax,3F00h
	mov	bx,h
	mov	cx,z
	lds	dx,b
	int	21h
	pop	ds
	jc	osread_error
    osread_end:
	ret
    osread_error:
	call	osmaperr
	sub	ax,ax
	jmp	osread_end
	ret
osread	ENDP

	END
