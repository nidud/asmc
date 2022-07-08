; ISINFQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

isinfq proc q:real16
ifdef _WIN64
    xor     eax,eax
    movq    rcx,xmm0
    test    rcx,rcx
    jnz     @F
    shufpd  xmm0,xmm0,1
    movq    rcx,xmm0
    shufpd  xmm0,xmm0,1
    test    rcx,rcx
    jnz     @F
    shr     rcx,32
    and     ecx,0x7FFFFFFF
    cmp     ecx,0x7FFF0000
    setz    al
@@:
endif
    ret
isinfq endp

    end
