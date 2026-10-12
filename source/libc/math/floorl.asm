; FLOORL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code

floorl proc x:real10
    fld     x
    fstcw   word ptr x
    fclex
    mov     word ptr x[2],0x0763
    fldcw   word ptr x[2]
    frndint
    fclex
    fldcw   word ptr x
ifdef _WIN64
    fstp    x
    movaps  xmm0,xmmword ptr x
endif
    ret
    endp

    end
