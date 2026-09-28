; LOG2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code

log2 proc x:double
    fld1
    fld     x
    fyl2x
ifdef _WIN64
    fstp    x
    movsd   xmm0,x
endif
    ret
    endp

    end
