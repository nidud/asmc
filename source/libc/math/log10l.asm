; LOG10L.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code

log10l proc x:real10
    fld     x
    fldlg2
    fxch    st(1)
    fyl2x
ifdef _WIN64
    fstp    x
    movaps  xmm0,xmmword ptr x
endif
    ret
    endp

    end
