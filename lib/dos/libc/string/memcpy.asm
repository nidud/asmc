; MEMCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

memcpy proc <usesds> uses si di s1:ptr, s2:ptr, count:size_t

    ldr     di,s1
    ldr     si,s2

    mov     cx,count
    mov     ax,di
    rep     movsb
    movl    dx,es
    ret

memcpy endp

    end
