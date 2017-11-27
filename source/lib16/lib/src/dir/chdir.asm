; CHDIR.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc
include dos.inc

	.code

chdir PROC _CType PUBLIC directory:DWORD
    ifdef __LFN__
	cmp	_ifsmgr,0
    endif
	push	ds
	lds	dx,directory
	mov	ah,3Bh
    ifdef __LFN__
	je	@F
	stc
	mov	ax,713Bh
      @@:
    endif
	int	21h
	pop	ds
	jc	chdir_err
	xor	ax,ax
    chdir_end:
	ret
    chdir_err:
	call	osmaperr
	jmp	chdir_end
chdir ENDP

	END
