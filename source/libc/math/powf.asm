; POWF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

powf proc x:float, y:float
ifdef _WIN64
    cvtss2sd xmm0,xmm0
    cvtss2sd xmm1,xmm1
    pow(xmm0, xmm1)
    cvtsd2ss xmm0,xmm0
else
   .new a:double
   .new b:double
    fld  x
    fstp a
    fld  y
    fstp b
    pow(a, b)
endif
    ret

powf endp

    end
