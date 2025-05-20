; CEILF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

ceilf proc _x:float
ifdef _WIN64
   .new x:float = xmm0
else
    define x _x
endif
   .new w:word
   .new n:word
    fld     x
    fstcw   w
    fclex               ; clear exceptions
    mov     n,0x0B63    ; set new rounding
    fldcw   n
    frndint             ; round to integer
    fclex
    fldcw   w
ifdef _WIN64
    fstp    x
    movss   xmm0,x
endif
    ret

ceilf endp

    end
