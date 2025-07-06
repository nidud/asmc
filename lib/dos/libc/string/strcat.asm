; STRCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

strcat proc uses si di s1:string_t, s2:string_t

    pushl   ds
    ldr     di,s1
    ldr     si,s2
    mov     dx,di
    xor     ax,ax
    mov     cx,-1
    repne   scasb
    dec     di
    mov     ax,dx
    movl    dx,es
.0:
    mov     cl,[si]
    mov     esl[di],cl
    inc     di
    inc     si
    test    cl,cl
    jnz     .0
    popl    ds
    ret

strcat endp

    end
