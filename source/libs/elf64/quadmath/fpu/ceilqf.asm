; CEILQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

ceilqf proc Q:real16

  local w1:word, w2:word

    fldq()
    fstcw   w1
    fclex
    mov     w2,0x0B63
    fldcw   w2
    frndint
    fclex
    fldcw   w1
    fstq()
    ret

ceilqf endp

    end
