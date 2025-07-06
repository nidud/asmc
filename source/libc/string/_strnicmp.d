; _STRNICMP.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

_strnicmp proc uses si di s1:string_t, s2:string_t, count:uint_t

    pushl   ds
    ldsl    si,s1
    lesl    di,s2
    mov     cx,count
.0:
    mov     al,[si]
    test    cx,cx
    jz      .1
    dec     cx
    test    al,al
    jz      .1
    mov     ah,esl[di]
    inc     si
    inc     di
    or      ax,0x2020
    cmp     al,ah
    je      .0
    sbb     al,al
    sbb     al,-1
.1:
    cbw
    popl    ds
    ret

_strnicmp endp

    end
