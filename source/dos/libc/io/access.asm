; ACCESS.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc
include dos.inc

	.code

access	PROC _CType PUBLIC fname:DWORD, amode:size_t
	.if getfattr(fname) != -1
	    .if amode == 2 && ax & _A_RDONLY
		mov ax,-1
	    .else
		sub ax,ax
	    .endif
	.endif
	ret
access	ENDP

	END