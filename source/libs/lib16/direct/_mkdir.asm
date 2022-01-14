; _MKDIR.ASM--
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include direct.inc
include io.inc

    .code

_mkdir proc __ctype directory:ptr sbyte

ifdef __LFN__
    cmp     _ifsmgr,0
endif
    pushl   ds
    ldsl    dx,directory
    mov     ah,39h
ifdef __LFN__
    je      .0
    stc
    mov     ax,7139h
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

_mkdir endp

    end
