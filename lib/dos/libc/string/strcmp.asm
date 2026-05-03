; STRCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

strcmp proc <usesds> uses si di s1:string_t, s2:string_t

    ldr     si,s2
    ldr     di,s1
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
    ret

strcmp endp

    end
