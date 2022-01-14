; STRCPY.ASM--
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

strcpy proc __ctype uses si di s1:ptr sbyte, s2:ptr sbyte

    pushl   ds
    xor     ax,ax
    mov     cx,-1
    lesl    di,s2
    repne   scasb
    lesl    di,s1
    ldsl    si,s2
    mov     ax,di
    not     cx
    rep     movsb
    movl    dx,es
    popl    ds
    ret

strcpy endp

    end
