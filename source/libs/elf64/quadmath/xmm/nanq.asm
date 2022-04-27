; NANQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:noauto

nanq proc

    mov     rax,0x7FFF000000000001
    movq    xmm0,rax
    shufps  xmm0,xmm0,01101000B
    ret

nanq endp

    end
