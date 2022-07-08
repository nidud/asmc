; NANQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

nanq proc
ifdef _WIN64
    mov     rax,0x7FFF000000000001
    movq    xmm0,rax
    shufps  xmm0,xmm0,01101000B
endif
    ret
nanq endp

    end
