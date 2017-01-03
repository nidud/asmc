; DSETFATT.ASM--
; Copyright (C) 2015 Doszip Developers
;
; int _dos_setfileattr(char *path, unsigned attrib);
;
; Return 0 on success, else DOS error code
;
include dos.inc

	.code

_dos_setfileattr PROC _CType PUBLIC file:DWORD, attrib:size_t
	push	ds
ifdef __LFN__
	cmp	_ifsmgr,0
endif
	lds	dx,file
	mov	cx,attrib
	mov	ax,4301h
ifdef __LFN__
	jz	@F
	stc
	mov	ax,7143h
	mov	bl,1
@@:
endif
	int	21h
	pop	ds
	jc	error
	xor	ax,ax
toend:
	ret
error:
	call	osmaperr
	mov	ax,doserrno
	jmp	toend
_dos_setfileattr ENDP

	END
