; FILELENG.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc

	.code

filelength PROC _CType PUBLIC handle:size_t
local	fpos:DWORD
	mov	ax,4201h
	mov	bx,handle
	xor	cx,cx
	mov	dx,cx
	int	21h
	jc	filelength_error
	mov	[bp-4],ax
	mov	[bp-2],dx
	mov	ax,4202h
	mov	bx,handle
	xor	cx,cx
	mov	dx,cx
	int	21h
	jc	filelength_error
	push	dx
	push	ax
	mov	dx,[bp-2]
	mov	cx,[bp-4]
	mov	ax,4200h
	mov	bx,handle
	int	21h
	pop	ax
	pop	dx
    filelength_end:
	ret
    filelength_error:
	call	osmaperr
	mov	dx,ax
	jmp	filelength_end
filelength ENDP

	END
