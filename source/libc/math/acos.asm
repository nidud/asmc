; ACOS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

acos proc _x:double
ifdef _WIN64
   .new x:double = xmm0
else
    define x _x
endif
    fld     x
    fmul    st(0),st(0)
    fld1
    fsubrp  st(1),st(0)
    fsqrt
    fld     x
    fpatan
ifdef _WIN64
    fstp    x
    movsd   xmm0,x
endif
    ret

acos endp

    end
