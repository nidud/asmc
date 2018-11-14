; ATAN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
include immintrin.inc

    .data
    C00 oword 0x400E4FA47972904240038F4C070B63C1
    C01 oword 0x3F953DB49B9FCF6B4002609372076E2C
    C10 oword 0x401AE0FB08F2DC004015E43168D7C2B6
    C11 oword 0xC013E370146726B3C00792D5BF17C0BC

    .code

    option win64:rsp nosave noauto

atan2 proc y:double, x:double

    _mm_move_sd(xmm4, FLT8(-0.0))
    _mm_xor_pd(xmm4, xmm1)

    .switch

      .case _mm_ucomige_sd(xmm0, xmm1)

        .ifz
            .if _mm_ucomige_sd(xmm0, FLT8(-0.0))

                .ifz
                    _mm_srai_epi16(xmm1, 12)
                    _mm_cmp_sd(xmm1, xmm1, _CMP_UNORD_Q)
                    _mm_move_sd(xmm2, FLT8(3.1415924))
                    _mm_and_pd(xmm2, xmm1)
                    _mm_or_pd(xmm0, xmm2)
                    ret
                .endif
                _mm_move_sd(xmm0, FLT8(0.7853981633974483096156608))
                ret
            .endif
            _mm_move_sd(xmm0, FLT8(-2.356194490192344928846982))
            ret
        .endif

        .if _mm_ucomige_sd(xmm4, xmm0)

            .ifz
                _mm_move_sd(xmm0, FLT8(2.356194490192344928846982))
                ret
            .endif

            _mm_move_sd(xmm5, FLT8(-0.0))
            _mm_move_pd(xmm4, xmm5)
            _mm_and_pd(xmm5, xmm0)
            _mm_div_sd(xmm0, xmm1)
            _mm_andnot_pd(xmm4, xmm0)

            .if _mm_comile_sd(xmm4, FLT8(2.384185791015625e-07))

                _mm_move_sd(xmm0, FLT8(3.1415924))
                _mm_xor_pd(xmm0, xmm5)
                ret
            .endif

            _mm_move_sd(xmm3, FLT8(3.141592653589793238462643))
            _mm_or_pd(xmm5, xmm3)
            _mm_move_sd(xmm1, xmm0)
            .endc
        .endif

        _mm_move_sd(xmm4, FLT8(-0.0))
        _mm_move_sd(xmm5, FLT8(1.570796326794896619231322))
        _mm_div_sd(xmm1, xmm0)
        _mm_xor_pd(xmm1, xmm4)
        .endc

      .case ZERO?
        _mm_add_sd(xmm0, xmm1)
        ret

      .case _mm_ucomige_sd(xmm4, xmm0)

        .ifz

            _mm_move_sd(xmm0, FLT8(-0.7853981633974483096156608))
            ret
        .endif

        _mm_move_sd(xmm4, FLT8(-0.0))
        _mm_div_sd(xmm1, xmm0)
        _mm_xor_pd(xmm1, xmm4)
        _mm_move_sd(xmm5, FLT8(-1.570796326794896619231322))
        .endc

      .default
        _mm_div_sd(xmm0, xmm1)
        _mm_move_sd(xmm1, xmm0)
        _mm_move_sd(xmm5, FLT8(-0.0))
        .endc
    .endsw

    _mm_move_sd(xmm3, xmm1)
    _mm_move_pd(xmm2, C11)
    _mm_mul_sd(xmm1, xmm1)
    _mm_movelh_ps(xmm1, xmm1)
    _mm_add_pd(xmm2, xmm1)
    _mm_mul_pd(xmm2, xmm1)
    _mm_add_pd(xmm2, C10)
    _mm_load_pd(C01)
    _mm_add_pd(xmm0, xmm1)
    _mm_mul_pd(xmm0, xmm1)
    _mm_loadh_pd(xmm3, FLT8(0.0029352921857004596570518))
    _mm_add_pd(xmm0, C00)
    _mm_mul_pd(xmm0, xmm2)
    _mm_mul_pd(xmm0, xmm3)
    _mm_movehl_ps(xmm2, xmm0)
    _mm_mul_sd(xmm0, xmm2)
    _mm_add_sd(xmm0, xmm5)
    ret

atan2 endp

    end
