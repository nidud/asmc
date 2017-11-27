; OPENFILE.ASM--
; Copyright (C) 2015 Doszip Developers

include iost.inc
include io.inc
include errno.inc

	.code

openfile PROC _CType PUBLIC fname:DWORD, mode:size_t, action:size_t
	invoke	osopen,fname,_A_NORMAL,mode,action
	cmp	ax,-1
	je	openfile_err
    openfile_end:
	ret
    openfile_err:
	invoke	eropen,fname
	jmp	openfile_end
openfile ENDP

	END
