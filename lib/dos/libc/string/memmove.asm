; MEMMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

memmove proc <usesds> uses si di s1:ptr, s2:ptr, cnt:size_t

    ldr     di,s1
    ldr     si,s2

    mov     cx,cnt
    mov     ax,di
    cmp     ax,si
    ja      .0
    rep     movsb
    jmp     .1
.0:
    std
    add     si,cx
    add     di,cx
    sub     si,1
    sub     di,1
    rep     movsb
    cld
.1:
    movl    dx,es
    ret

memmove endp

    end
