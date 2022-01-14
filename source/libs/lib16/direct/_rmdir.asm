; _RMDIR.ASM--
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include direct.inc
include io.inc

    .code

_rmdir proc __ctype directory:ptr sbyte

ifdef __LFN__
    cmp     _ifsmgr,0
endif
    pushl   ds
    ldsl    dx,directory
    mov     ah,3Ah
ifdef __LFN__
    jz      .0
    stc
    mov     ax,713Ah
.0:
endif
    int     21h
    popl    ds
    jc      .2
    xor     ax,ax
.1:
    ret
.2:
    call    osmaperr
    jmp     .1

_rmdir endp

    end
