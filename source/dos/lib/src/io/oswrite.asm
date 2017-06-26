; OSWRITE.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc
include errno.inc

	.code

oswrite PROC _CType PUBLIC h:size_t, b:DWORD, z:size_t
	push	ds
	push	bx
	lds	dx,b
	mov	bx,h
	mov	cx,z
	mov	ax,4000h
	int	21h
	pop	bx
	pop	ds
	jc	oswrite_error
	cmp	ax,cx
	jne	oswrite_ersize
    oswrite_end:
	ret
    oswrite_ersize:
	mov	ax,ER_DISK_FULL
    oswrite_error:
	call	osmaperr
	xor	ax,ax
	jmp	oswrite_end
	ret
oswrite ENDP

	END
