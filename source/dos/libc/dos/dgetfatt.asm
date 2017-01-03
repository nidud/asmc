; DGETFATT.ASM--
; Copyright (C) 2015 Doszip Developers
;
; int _dos_getfileattr(char *path, unsigned *attrib);
;
; Return 0 on success, else DOS error code
;
include dos.inc

	.code

_dos_getfileattr PROC _CType PUBLIC file:DWORD, attrib:DWORD
      ifdef __LFN__
	cmp	_ifsmgr,0
      endif
	push	bx
	push	ds
	lds	dx,file
	mov	ax,4300h
      ifdef __LFN__
	jz	@F
	stc
	mov	ax,7143h
	mov	bl,0
      @@:
      endif
	int	21h
	pop	ds
	jc	error
	les	bx,attrib
	mov	es:[bx],cx
	xor	ax,ax
    toend:
	pop	bx
	ret
    error:
	call	osmaperr
	mov	ax,doserrno
	jmp	toend
_dos_getfileattr ENDP

	END
