; RMDIR.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc
include dos.inc

	.code

rmdir	PROC _CType PUBLIC directory:DWORD
    ifdef __LFN__
	cmp	_ifsmgr,0
    endif
	push	ds
	lds	dx,directory
	mov	ah,3Ah
    ifdef __LFN__
	jz	@F
	stc
	mov	ax,713Ah
      @@:
    endif
	int	21h
	pop	ds
	jc	rmdir_err
	xor	ax,ax
    rmdir_end:
	ret
    rmdir_err:
	call	osmaperr
	jmp	rmdir_end
rmdir	ENDP

	END
