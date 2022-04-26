; __CVTQ_SD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cvtq_sd() - Quad to double
;

include quadmath.inc

    .code

__cvtq_sd proc uses rbx d:ptr, q:ptr

    mov rbx,d
    movups xmm0,[q]
    cvtq_sd(xmm0)
    mov rax,rbx
    movsd [rax],xmm0
    ret

__cvtq_sd endp

    end
