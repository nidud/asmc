; __CVTA_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__cvta_q proc number:ptr, string:string_t, endptr:ptr string_t

    mov rcx,rdx
    cvta_q(rcx, r9)
    mov rax,number
    movups [rax],xmm0
    ret

__cvta_q endp

    end
