; COSH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
include intrin.inc

.code

cosh proc x:double
ifdef _WIN64
    exp(_mm_and_pd(xmm0, { 0x7FFFFFFFFFFFFFFF, 0 }))
    _mm_div_sd(_mm_move_sd(xmm1, 1.0), xmm0)
    _mm_div_sd(_mm_add_sd(xmm0, xmm1), 2.0)
else
    and byte ptr x[7],0x7F
    exp(x)
    fld1
    fdiv st(0),st(1)
    faddp
    fld1
    fld1
    faddp
    fdivp
endif
    ret
    endp

    end
