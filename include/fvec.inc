ifndef _FVEC_H_INCLUDED
_FVEC_H_INCLUDED equ <>

    option win64:align

    vec128_t typedef real16

include xmmintrin.inc
include ivec.inc
include vcruntime.inc

.template F32vec4
    vec __m128 <>

    .operator = :real4, :real4, :real4, :real4 {
        movss xmm4,_4
        movss xmm0,_1
        _mm_store_ps([this], _mm_set_ps(xmm0, _2, _3, xmm4))
        }
    .operator = :vec128_t {
        _mm_store_ps([this], _1)
        }
    .operator = :real4 {
        _mm_store_ps([this], _mm_set_ps1(_mm_store_ps(xmm0, _1)))
        }
    .operator = :real8 {
        _mm_store_ps([this], _mm_set_ps1(_mm_cvtsd_ss(xmm0, _1)))
        }
    .operator __m128 {
        _mm_store_ps(xmm0, [this])
        }
    .operator & :vec128_t {
        _mm_and_ps(xmm0, _1)
        }
    .operator | :vec128_t {
        _mm_or_ps(xmm0, _1)
        }
    .operator ^ :vec128_t {
        _mm_xor_ps(xmm0, _1)
        }
    .operator + :vec128_t {
        _mm_add_ps(xmm0, _1)
        }
    .operator - :vec128_t {
        _mm_sub_ps(xmm0, _1)
        }
    .operator * :vec128_t {
        _mm_mul_ps(xmm0, _1)
        }
    .operator / :vec128_t {
        _mm_div_ps(xmm0, _1)
        }
    .operator += :vec128_t {
        _mm_store_ps([this], _mm_add_ps(xmm0, _1))
        }
    .operator -= :vec128_t {
        _mm_store_ps([this], _mm_sub_ps(xmm0, _1))
        }
    .operator *= :vec128_t {
        _mm_store_ps([this], _mm_mul_ps(xmm0, _1))
        }
    .operator /= :vec128_t {
        _mm_store_ps([this], _mm_div_ps(xmm0, _1))
        }
    .operator &= :vec128_t {
        _mm_store_ps([this], _mm_and_ps(xmm0, _1))
        }
    .operator |= :vec128_t {
        _mm_store_ps([this], _mm_or_ps(xmm0, _1))
        }
    .operator ^= :vec128_t {
        _mm_store_ps([this], _mm_xor_ps(xmm0, _1))
        }

    .operator add_horizontal {
        _mm_store_ps(xmm1, xmm0)
        _mm_add_ps(xmm0, _mm_movehl_ps(xmm1, xmm1))
        _mm_store_ps(xmm1, xmm0)
        _mm_add_ss(xmm0, _mm_shuffle_ps(xmm1, xmm1, 1))
        _mm_cvtss_f32(xmm0)
        }
    .operator sqrt {
        _mm_sqrt_ps(xmm0)
        }
    .operator rcp {
        _mm_rcp_ps(xmm0)
        }
    .operator rsqrt {
        _mm_rsqrt_ps(xmm0)
        }
    .operator rcp_nr {
        _mm_store_ps(xmm1, xmm0)
        _mm_rcp_ps(xmm0)
        _mm_store_ps(xmm2, xmm0)
        _mm_mul_ps(xmm1, xmm0)
        _mm_sub_ps(_mm_add_ps(xmm0, xmm0), _mm_mul_ps(xmm1, xmm2))
        }

    .operator rsqrt_nr {
        rsqrtps xmm1,xmm0
        mulps   xmm0,xmm1
        movaps  xmm2,xmm0
        mulps   xmm2,xmm1
        mulps   _mm_set_epi32(5.0, 5.0, 5.0, 5.0),xmm1
        _mm_sub_ps(_mm_set_epi32(xmm1, 3.0, 3.0, 3.0, 3.0), xmm2)
        _mm_mul_ps(xmm0, xmm1)
        }

    .operator cmpeq     :vec128_t { _mm_cmpeq_ps(xmm0, _1) }
    .operator cmplt     :vec128_t { _mm_cmplt_ps(xmm0, _1) }
    .operator cmple     :vec128_t { _mm_cmple_ps(xmm0, _1) }
    .operator cmpneq    :vec128_t { _mm_cmpneq_ps(xmm0, _1) }
    .operator cmpnlt    :vec128_t { _mm_cmpnlt_ps(xmm0, _1) }
    .operator cmpnle    :vec128_t { _mm_cmpnle_ps(xmm0, _1) }

    .operator cmpgt :vec128_t {
        cmpltps xmm1,xmm0
        movaps xmm0,xmm1
        }
    .operator cmpge :vec128_t {
        cmpleps xmm1,xmm0
        movaps xmm0,xmm1
        }
    .operator cmpngt :vec128_t {
        cmpnltps xmm1,xmm0
        movaps xmm0,xmm1
        }
    .operator cmpnge :vec128_t {
        cmpnleps xmm1,xmm0
        movaps xmm0,xmm1
        }

    .operator simd_max  :vec128_t { _mm_max_ps(xmm0, _1) }
    .operator simd_min  :vec128_t { _mm_min_ps(xmm0, _1) }

    Fvec32s4_SELECT macro op
        .operator select_&op& :vec128_t, :vec128_t, :vec128_t {
            _mm_cmp&op&_ps(xmm0, _1)
            _mm_store_ps(_1, xmm0)
            _mm_and_ps(xmm0, _2)
            _mm_andnot_ps(_1, _3)
            _mm_or_ps(xmm0, _1)
            }
        exitm<>
        endm
        Fvec32s4_SELECT(eq)
        Fvec32s4_SELECT(lt)
        Fvec32s4_SELECT(le)
        Fvec32s4_SELECT(neq)
        Fvec32s4_SELECT(nlt)
        Fvec32s4_SELECT(nle)
        undef Fvec32s4_SELECT

    Fvec32s4_SELECT macro op
        .operator select_&op& :vec128_t, :vec128_t, :vec128_t {
            _mm_cmp&op&_ps(_1, xmm0, _1)
            _mm_store_ps(xmm0, _1)
            _mm_and_ps(xmm0, _2)
            _mm_andnot_ps(_1, _3)
            _mm_or_ps(xmm0, _1)
            }
        exitm<>
        endm
        Fvec32s4_SELECT(gt)
        Fvec32s4_SELECT(ge)
        Fvec32s4_SELECT(ngt)
        Fvec32s4_SELECT(nge)
        undef Fvec32s4_SELECT

    .operator abs {
        pcmpeqd xmm1,xmm1
        psrld xmm1,1
        _mm_and_ps(xmm0, xmm1)
        }
    .operator unpack_low :vec128_t {
        _mm_unpacklo_ps(xmm0, _1)
        }
    .operator unpack_high :vec128_t {
        _mm_unpackhi_ps(xmm0, _1)
        }
    .operator loadu {
        _mm_loadu_ps([this])
        }
    .operator storeu {
        _mm_storeu_ps([this], xmm0)
        }
    .operator store_nta {
        _mm_stream_ps([this], xmm0)
        }
if defined (_ENABLE_VEC_DEBUG)
    .operator cout :string_t {
        .new this_ptr:ptr
        mov this_ptr,this
        movq r8, _mm_cvtss_sd(_mm_move_ss(xmm0, [this+0x0C]))
        movq r9, _mm_cvtss_sd(_mm_move_ss(xmm0, [this+0x08]))
        movq r10,_mm_cvtss_sd(_mm_move_ss(xmm0, [this+0x04]))
        movq r11,_mm_cvtss_sd(_mm_move_ss(xmm0, [this+0x00]))
        printf( addr @CStr("%s\n [3]:%f\n [2]:%f\n [1]:%f\n [0]:%f\n"), rdx, r8, r9, r10, r11 )
        mov this,this_ptr
        }
endif
    .ends

if defined(_M_IX86)
endif


.template F32vec1
    vec __m128 <>

    .operator = :vec128_t {
        _mm_store_ps([this], _1)
        }
    .operator = :real4 {
        _mm_store_ss([this], _mm_set_ss(_1))
        }
    .operator = :real8 {
        _mm_store_ps([this], _mm_set_ss(_mm_cvtsd_ss(xmm0, _1)))
        }
    .operator __m128 {
        _mm_store_ps(xmm0, [this])
        }
    .operator & :vec128_t {
        _mm_and_ps(xmm0, _1)
        }
    .operator | :vec128_t {
        _mm_or_ps(xmm0, _1)
        }
    .operator ^ :vec128_t {
        _mm_xor_ps(xmm0, _1)
        }
    .operator + :vec128_t {
        _mm_add_ss(xmm0, _1)
        }
    .operator - :vec128_t {
        _mm_sub_ss(xmm0, _1)
        }
    .operator * :vec128_t {
        _mm_mul_ss(xmm0, _1)
        }
    .operator / :vec128_t {
        _mm_div_ss(xmm0, _1)
        }
    .operator += :vec128_t {
        _mm_store_ps([this], _mm_add_ss(xmm0, _1))
        }
    .operator -= :vec128_t {
        _mm_store_ps([this], _mm_sub_ss(xmm0, _1))
        }
    .operator *= :vec128_t {
        _mm_store_ps([this], _mm_mul_ss(xmm0, _1))
        }
    .operator /= :vec128_t {
        _mm_store_ps([this], _mm_div_ss(xmm0, _1))
        }
    .operator &= :vec128_t {
        _mm_store_ps([this], _mm_and_ps(xmm0, _1))
        }
    .operator |= :vec128_t {
        _mm_store_ps([this], _mm_or_ps(xmm0, _1))
        }
    .operator ^= :vec128_t {
        _mm_store_ps([this], _mm_xor_ps(xmm0, _1))
        }

    .operator sqrt {
        _mm_sqrt_ss(xmm0)
        }
    .operator rcp {
        _mm_rcp_ss(xmm0)
        }
    .operator rsqrt {
        _mm_rsqrt_ss(xmm0)
        }

    .operator rcp_nr {
        _mm_store_ps(xmm1, xmm0)
        _mm_rcp_ss(xmm0)
        _mm_store_ps(xmm2, xmm0)
        _mm_mul_ss(xmm1, xmm0)
        _mm_sub_ss(_mm_add_ss(xmm0, xmm0), _mm_mul_ss(xmm1, xmm2))
        }

    .operator rsqrt_nr {
        rsqrtss xmm1,xmm0
        mulss   xmm0,xmm1
        movaps  xmm2,xmm0
        mulss   xmm2,xmm1
        mulss   _mm_set_epi32(5.0, 5.0, 5.0, 5.0),xmm1
        _mm_sub_ss(_mm_set_epi32(xmm1, 3.0, 3.0, 3.0, 3.0), xmm2)
        _mm_mul_ss(xmm0, xmm1)
        }

    .operator cmpeq     :vec128_t { _mm_cmpeq_ss(xmm0, _1) }
    .operator cmplt     :vec128_t { _mm_cmplt_ss(xmm0, _1) }
    .operator cmple     :vec128_t { _mm_cmple_ss(xmm0, _1) }
    .operator cmpneq    :vec128_t { _mm_cmpneq_ss(xmm0, _1) }
    .operator cmpnlt    :vec128_t { _mm_cmpnlt_ss(xmm0, _1) }
    .operator cmpnle    :vec128_t { _mm_cmpnle_ss(xmm0, _1) }

    .operator cmpgt :vec128_t {
        cmpltss xmm1,xmm0
        movaps xmm0,xmm1
        }
    .operator cmpge :vec128_t {
        cmpless xmm1,xmm0
        movaps xmm0,xmm1
        }
    .operator cmpngt :vec128_t {
        cmpnltss xmm1,xmm0
        movaps xmm0,xmm1
        }
    .operator cmpnge :vec128_t {
        cmpnless xmm1,xmm0
        movaps xmm0,xmm1
        }

    .operator simd_max  :vec128_t { _mm_max_ss(xmm0, _1) }
    .operator simd_min  :vec128_t { _mm_min_ss(xmm0, _1) }

    Fvec32s1_SELECT macro op
        .operator select_&op& :vec128_t, :vec128_t, :vec128_t {
            _mm_cmp&op&_ss(xmm0, _1)
            _mm_store_ps(_1, xmm0)
            _mm_and_ps(xmm0, _2)
            _mm_andnot_ps(_1, _3)
            _mm_or_ps(xmm0, _1)
            }
        exitm<>
        endm
        Fvec32s1_SELECT(eq)
        Fvec32s1_SELECT(lt)
        Fvec32s1_SELECT(le)
        Fvec32s1_SELECT(neq)
        Fvec32s1_SELECT(nlt)
        Fvec32s1_SELECT(nle)
        undef Fvec32s1_SELECT

    Fvec32s1_SELECT macro op
        .operator select_&op& :vec128_t, :vec128_t, :vec128_t {
            _mm_cmp&op&_ss(_1, xmm0, _1)
            _mm_store_ps(xmm0, _1)
            _mm_and_ps(xmm0, _2)
            _mm_andnot_ps(_1, _3)
            _mm_or_ps(xmm0, _1)
            }
        exitm<>
        endm
        Fvec32s1_SELECT(gt)
        Fvec32s1_SELECT(ge)
        Fvec32s1_SELECT(ngt)
        Fvec32s1_SELECT(nge)
        undef Fvec32s1_SELECT
if defined (_ENABLE_VEC_DEBUG)
    .operator cout :string_t {
        .new this_ptr:ptr
        mov this_ptr,rcx
        cvtss2sd xmm0,xmm0
        movq r8,xmm0
        printf( addr @CStr("%s\n [0]:%f\n"), rdx, r8 )
        mov rcx,this_ptr
        }
endif
    .ends

endif
