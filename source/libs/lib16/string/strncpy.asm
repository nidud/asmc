; STRNCPY.ASM--
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

strncpy proc __ctype uses si di s1:ptr sbyte, s2:ptr sbyte, count:word

    pushl   ds
    ldsl    si,s2
    lesl    di,s1
    xor     ax,ax
    mov     cx,count
.0:
    movsb
    dec     cx
    jz      .1
    cmp     [si-1],al
    jne     .0
.1:
    movl    dx,es
    mov     ax,word ptr s1
    popl    ds
    ret

strncpy endp

    end
