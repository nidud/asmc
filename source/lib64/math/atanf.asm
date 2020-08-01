; ATANF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

    option win64:rsp nosave noauto

atanf proc x:float

  local a:float

    movss   a,xmm0
    fld     a
    fld1
    fpatan
    fstp    a
    movss   xmm0,a
    ret

atanf endp

    end
