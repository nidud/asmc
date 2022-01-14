; STRCMP.ASM--
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

strcmp proc __ctype uses si di s1:ptr sbyte, s2:ptr sbyte

    pushl   ds
    ldsl    si,s2
    lesl    di,s1
    mov     al,-1
.0:
    test    al,al
    jz      .1
    mov     al,esl[di]
    mov     ah,[si]
    inc     si
    inc     di
    cmp     al,ah
    je      .0
    sbb     al,al
    sbb     al,-1
.1:
    cbw
    popl    ds
    ret

strcmp endp

    end
