; NOTSUP.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include syserrls.inc

	.code

notsup	PROC _CType PUBLIC
	invoke ermsg,0,addr CP_ENOSYS
	test ax,ax
	ret
notsup	ENDP

	END
