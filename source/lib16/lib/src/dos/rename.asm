; RENAME.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc

	.code

rename	PROC _CType PUBLIC Oldname:DWORD, Newname:DWORD
ifdef __LFN__
	mov	dx,_osversion
	mov	ax,5600h	; DOS 2+ - RENAME FILE
	cmp	_ifsmgr,0
	je	@F
	mov	ax,43FFh	; MS-DOS 7.20 (Win98)
	mov	cl,56h
	cmp	dx,0207h
	je	@F
	mov	ax,7156h	; Windows95 - RENAME FILE
	cmp	dl,7
	je	@F
	cmp	dl,5
	je	@F
	mov	ax,5600h	; DOS 2+ - RENAME FILE
@@:
	stc
endif
	push	ds
	push	di
	lds	dx,Oldname
	les	di,Newname
	int	21h
	pop	di
	pop	ds
	jc	error
	xor	ax,ax
toend:
	ret
error:
	call	osmaperr
	jmp	toend
rename	ENDP

	END
