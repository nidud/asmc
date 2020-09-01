; TANH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
include immintrin.inc

    .code

    option win64:nosave

tanh proc x:double

    mov rax,50.0
    movq xmm1,rax
    .if _mm_comigt_sd(xmm0, xmm1)

        _mm_move_sd(xmm0, 1.0)
    .else

        _mm_move_sd(xmm2, -50.0)
        _mm_move_pd(xmm1, xmm0)
        _mm_move_sd(xmm0, -1.0)

        .if _mm_comile_sd(xmm2, xmm1)

            exp(xmm1)
            _mm_move_sd(xmm2, 1.0)
            _mm_move_pd(xmm1, xmm0)
            _mm_div_sd(xmm2, xmm0)
            _mm_add_sd(xmm0, xmm2)
            _mm_sub_sd(xmm1, xmm2)
            _mm_div_sd(xmm1, xmm0)
            _mm_move_pd(xmm0, xmm1)
        .endif
    .endif
    ret

tanh endp

    end
