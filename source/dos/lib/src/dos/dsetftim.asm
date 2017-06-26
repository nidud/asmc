; DSETFTIM.ASM--
; Copyright (C) 2015 Doszip Developers
;
; unsigned _dos_setftime(int handle, unsigned date, unsigned time);
;
; Return 0 on success, else DOS error code
;
include dos.inc
include io.inc

	.code

_dos_setftime PROC _CType PUBLIC handle:size_t, datew:size_t, timew:size_t
	stc
	push	bx
	push	cx
	push	dx
	mov	ax,5701h
	mov	bx,handle
	mov	dx,datew
	mov	cx,timew
	int	21h
	pop	dx
	pop	cx
	pop	bx
	jc	error
	xor	ax,ax
    toend:
	ret
    error:
	call	osmaperr
	mov	ax,doserrno
	jmp	toend
_dos_setftime ENDP

	END
