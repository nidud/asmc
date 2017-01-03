; CMEXIT.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include conio.inc

_DZIP	segment

cmexit	PROC _CType PUBLIC
	test BYTE PTR config.c_confirm,_C_CONFEXIT
	jz cmquit
	invoke rsmodal,IDD_DZExit
	test ax,ax
	jnz cmquit
	ret
cmexit	ENDP

cmquit	PROC _CType PUBLIC
	mov ax,1
	mov mainswitch,ax
	ret
cmquit	ENDP

_DZIP	ENDS

	END
