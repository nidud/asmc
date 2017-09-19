; CMEXIT.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include consx.inc

    .code

cmexit proc
    .if config.c_cflag & _C_CONFEXIT
	.if !rsmodal(IDD_DZExit)
	    ret
	.endif
    .endif
cmexit endp

cmquit proc
    xor eax,eax
    mov mainswitch,eax
    inc eax
    mov dzexitcode,eax
    ret
cmquit endp

    END
