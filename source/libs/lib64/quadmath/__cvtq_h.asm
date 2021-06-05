; __CVTQ_H.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cvtq_h() - Quad to half
;

include quadmath.inc

    .code

__cvtq_h proc h:ptr, q:ptr

    movups xmm0,[rdx]
    cvtq_h(xmm0)
    mov ecx,eax
    mov rax,h
    mov [rax],cx
    ret

__cvtq_h endp

    end
