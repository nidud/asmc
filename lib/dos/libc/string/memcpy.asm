; MEMCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

memcpy proc uses si di s1:ptr, s2:ptr, count:size_t

    pushl   ds
    lesl    di,s1
    ldsl    si,s2
    mov     cx,count
    mov     ax,di
    movl    dx,es
    rep     movsb
    popl    ds
    ret

memcpy endp

    end
