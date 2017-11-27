; RCALLOC.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include alloc.inc

	.code

rcalloc PROC _CType PUBLIC rc:DWORD, shade:size_t
	invoke rcmemsize,rc,shade
	invoke malloc,ax
	ret
rcalloc ENDP

	END
