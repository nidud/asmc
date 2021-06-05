; __CVTQ_SD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cvtq_sd() - Quad to double
;

include quadmath.inc

    .code

__cvtq_sd proc d:ptr, q:ptr

    movups xmm0,[rdx]
    cvtq_sd(xmm0)
    mov rax,d
    movsd [rax],xmm0
    ret

__cvtq_sd endp

    end
