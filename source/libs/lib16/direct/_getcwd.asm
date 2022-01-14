; GETCWD.ASM--
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include direct.inc
include io.inc

    .code

_getcwd proc __ctype uses si buffer:ptr sbyte, maxlen:word

    pushl   ds
ifdef __LFN__
    cmp     _ifsmgr,0
endif
    ldsl    si,buffer
    mov     dx,0   ; drive number (DL, 0 = default)
    mov     ah,47h
ifdef __LFN__
    je      .0
    stc
    mov     ax,7147h
.0:
endif
    int     21h
    jnc     .1
    call    osmaperr
    inc     ax
    cwd
    jmp     .2
.1:
    movl    dx,ds
    mov     ax,si
.2:
    popl    ds
    ret

_getcwd endp

    end
