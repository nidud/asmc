; COSHF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
include intrin.inc

.code

coshf proc x:float
ifdef _WIN64
    expf(_mm_and_ps(xmm0, { 0x7FFFFFFF, 0, 0, 0 }))
    _mm_move_ss(xmm1, 1.0)
    _mm_div_ss(xmm1, xmm0)
    _mm_add_ss(xmm0, xmm1)
    _mm_div_ss(xmm0, 2.0)
else
    and byte ptr x[4],0x7F
    expf(x)
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
