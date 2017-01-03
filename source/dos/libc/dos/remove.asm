; REMOVE.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc

	.code

remove	PROC _CType PUBLIC file:DWORD
ifdef __LFN__
	push	si
	mov	al,_ifsmgr
	test	al,al
endif
	push	ds
	lds	dx,file
	mov	ah,41h
ifdef __LFN__
	jz	@F
	xor	si,si
	stc
	mov	ax,7141h
@@:
endif
	int	21h
	pop	ds
	jc	error
	xor	ax,ax
toend:
ifdef __LFN__
	pop	si
endif
	ret
error:
	call	osmaperr
	jmp	toend
remove	ENDP

	END
