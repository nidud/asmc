; CEILF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code

ceilf proc x:float
ifdef _WIN64
    roundps xmm0,xmm0,2
else
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
endif
    ret
    endp

    end
