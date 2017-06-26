; GETFATTR.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc

	.code

getfattr PROC _CType PUBLIC file:DWORD
ifdef __LFN__
	cmp	_ifsmgr,0
endif
	push	ds
	push	bx
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
	pop	bx
	pop	ds
	jc	error
	mov	ax,cx
      @@:
	ret
error:
	call	osmaperr
	jmp	@B
getfattr ENDP

	END

