; CEILL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code

ceill proc x:real10
    fld     x
    fstcw   word ptr x[2]
    fclex
    mov     word ptr x,0x0B63
    fldcw   word ptr x
    frndint
    fclex
    fldcw   word ptr x[2]
ifdef _WIN64
    fstp    x
    movaps  xmm0,xmmword ptr x
endif
    ret
    endp

    end
