; MKDIR.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc
include dos.inc

	.code

mkdir	PROC _CType PUBLIC directory:DWORD
    ifdef __LFN__
	cmp	_ifsmgr,0
    endif
	push	ds
	lds	dx,directory
	mov	ah,39h
    ifdef __LFN__
	je	@F
	stc
	mov	ax,7139h
      @@:
    endif
	int	21h
	pop	ds
	jc	mkdir_err
	xor	ax,ax
    mkdir_end:
	ret
    mkdir_err:
	call	osmaperr
	jmp	mkdir_end
mkdir	ENDP

	END
