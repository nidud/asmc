; EXP2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
ifdef _WIN64
include intrin.inc
option float: double
endif

.code

exp2 proc x:double
ifdef _WIN64
    _mm_move_pd(xmm1, xmm0)
    _mm_and_pd(xmm1, { 0x7FFFFFFFFFFFFFFF, 0 })
    .if ( xmm1 < 0x1.0p-1020 )
        _mm_move_sd(xmm0, 0x1.0p-1020)
    .endif
    exp(_mm_mul_sd(xmm0, 6.9314718055994530942E-1))
else
    pow(2.0, x)
endif
    ret
    endp

    end
