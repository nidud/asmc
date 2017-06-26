; DSETFTCR.ASM--
; Copyright (C) 2015 Doszip Developers
;
; int _dos_setftime_create(int __handle, int __date, int __time);
;
; Win+DosLFN - return OS error code on error
;
include dos.inc
include io.inc

	.code

_dos_setftime_create PROC _CType PUBLIC h:size_t, d:size_t, t:size_t
	push	si
	push	bx
	stc
	mov	ax,5707h	; MS-DOS 7/Win95 - SET CREATION DATE AND TIME
	mov	bx,h		; BX = file handle
	mov	cx,t		; CX = new creation time
	mov	dx,d		; DX = new creation date
	mov	si,0		; SI = new creation time:
	int	21h		;  10-millisecond units past time in CX (0-199)
	jc	error
	xor	ax,ax
    toend:
	pop	si
	pop	bx
	ret
    error:
	call	osmaperr
	mov	ax,doserrno
	jmp	toend
_dos_setftime_create ENDP

	END
