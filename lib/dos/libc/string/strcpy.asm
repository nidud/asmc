; STRCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

strcpy proc uses si di s1:string_t, s2:string_t

    pushl   ds
    ldr     di,s2
    mov     si,di
    movl    ax,es
    movl    ds,ax
    xor     ax,ax
    mov     cx,-1
    repne   scasb
    lesl    di,s1
    mov     ax,di
    not     cx
    rep     movsb
    movl    dx,es
    popl    ds
    ret

strcpy endp

    end
