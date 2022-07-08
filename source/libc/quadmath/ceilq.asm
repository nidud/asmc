; CEILQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

ceilq proc q:real16
ifdef _WIN64
  local w1:word, w2:word
    qtofpu( xmm0 )
    fstcw   w1
    fclex
    mov     w2,0x0B63
    fldcw   w2
    frndint
    fclex
    fldcw   w1
    fputoq()
else
    int 3
endif
    ret
ceilq endp

    end
