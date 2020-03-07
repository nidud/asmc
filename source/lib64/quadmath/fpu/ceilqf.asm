; CEILQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

ceilqf proc vectorcall Q:real16

    fldq()
    fstcw   [rsp]
    fclex
    mov     word ptr [rsp+4],0x0B63
    fldcw   [rsp+4]
    frndint
    fclex
    fldcw   [rsp]
    fstq()
    ret

ceilqf endp

    end
