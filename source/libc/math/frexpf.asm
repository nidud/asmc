; FREXPF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; float frexp(float x, int *exp);
;
include math.inc

.code

frexpf proc x:float, y:ptr int_t
ifdef _WIN64
    cvtss2sd xmm0,xmm0
    frexp(xmm0, ldr(y))
    cvtsd2ss xmm0,xmm0
else
   .new d:double
    fld x
    fstp d
    frexp(d, y)
endif
    ret
    endp

    end
