; STRCHR.ASM--
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

strchr proc uses di s1:string_t, char:int_t

    xor     ax,ax
    movl    dx,ax
    lesl    di,s1
.0:
    mov     al,esl[di]
    test    al,al
    jz      .1
    inc     di
    cmp     al,BYTE PTR char
    jne     .0
    movl    dx,es
    mov     ax,di
    dec     ax
.1:
    ret

strchr endp

    end
