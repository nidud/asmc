; ACOS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

    option win64:rsp nosave noauto

acos proc x:double

    movq   xmm1,xmm0
    movq   xmm2,xmm0
    mov    rax,1.0
    movq   xmm0,rax
    mulsd  xmm2,xmm2
    subsd  xmm0,xmm2
    sqrtpd xmm0,xmm0
    jmp    atan2

acos endp

    end
