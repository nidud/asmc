; LOG10.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

    .code

log10 proc x:double

  local d:double

    movsd   d,xmm0
    fld     d
    fldlg2
    fxch    st(1)
    fyl2x
    fstp    d
    movsd   xmm0,d
    ret

log10 endp

    end
