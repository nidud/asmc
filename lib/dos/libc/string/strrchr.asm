; STRRCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

strrchr proc uses di s1:string_t, char:int_t

    ldr     di,s1
    xor     ax,ax
    movl    dx,ax
    mov     cx,-1
    repne   scasb
    not     cx
    dec     di
    std
    mov     al,byte ptr char
    repne   scasb
    mov     al,0
    jne     .0
    movl    dx,es
    mov     ax,di
    inc     ax
.0:
    cld
    ret

strrchr endp

    end
