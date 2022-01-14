; _CHDRIVE.ASM--
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include direct.inc

    .code

_chdrive proc __ctype drv:sword

    mov     dx,drv
    mov     ah,0Eh
    int     21h
    ret

_chdrive endp

    end
