; ISNANQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    option dotname

    .code

isnanq proc q:real16
ifdef _WIN64
    shufpd  xmm0,xmm0,1
    movq    rcx,xmm0
    shufpd  xmm0,xmm0,1
    rol     rcx,16
    and     cx,Q_EXPMASK
    xor     eax,eax
    cmp     cx,Q_EXPMASK
    jne     .1
    shr     rcx,16
    jnz     .0
    movq    rcx,xmm0
.0:
    test    rcx,rcx
    setnz   al
.1:
endif
    ret
isnanq endp

    end
