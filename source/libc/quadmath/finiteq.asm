; FINITEQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

finiteq proc q:real16
ifdef _WIN64
    shufpd  xmm0,xmm0,1
    movq    rax,xmm0
    shufpd  xmm0,xmm0,1
    mov     rcx,0x7fff000000000000
    and     rax,rcx
    sub     rax,rcx
    shr     rax,63
endif
    ret
finiteq endp

    end
