; TEST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

_ENABLE_VEC_DEBUG equ 1

include stdio.inc
include dvec.inc

    .code

test_M128 proc v:ptr M128

    assume rcx:ptr M128

    [rcx].mequ16    (xmm1)
    [rcx].__m128i   ()
    [rcx].mand16    (xmm1)
    [rcx].mor16     (xmm1)
    [rcx].mxor16    (xmm1)
    [rcx].rand16    (xmm1)
    [rcx].ror16     (xmm1)
    [rcx].rxor16    (xmm1)
    [rcx].andnot    (xmm1)
    ret

test_M128 endp

test_I128vec1 proc v:ptr I128vec1

    assume rcx:ptr I128vec1

    [rcx].mequ16    (xmm1)
    [rcx].__m128i   ()
    [rcx].mand16    (xmm1)
    [rcx].mor16     (xmm1)
    [rcx].mxor16    (xmm1)
    [rcx].rand16    (xmm1)
    [rcx].ror16     (xmm1)
    [rcx].rxor16    (xmm1)
    [rcx].andnot    (xmm1)
    ret

test_I128vec1 endp

test_I64vec2 proc v:ptr I64vec2

    assume rcx:ptr I64vec2

    [rcx].mequ16    (xmm1)
    [rcx].__m128i   ()
    [rcx].mand16    (xmm1)
    [rcx].mor16     (xmm1)
    [rcx].mxor16    (xmm1)
    [rcx].rand16    (xmm1)
    [rcx].ror16     (xmm1)
    [rcx].rxor16    (xmm1)
    [rcx].andnot    (xmm1)

    [rcx].mequ88    (1, 2)
    [rcx].madd16    (xmm1)
    [rcx].msub16    (xmm1)
    [rcx].mshl16    (xmm1)
    [rcx].mshr16    (xmm1)
    [rcx].rshl16    (xmm1)
    [rcx].rshr16    (xmm1)

    [rcx].rshl8     (2)
    [rcx].rshr8     (3)
    [rcx].unpack_low(xmm1)
    [rcx].unpack_high(xmm1)
    ret

test_I64vec2 endp

test_I32vec4 proc v:ptr I32vec4

    assume rcx:ptr I32vec4

    [rcx].mequ16    (xmm1)
    [rcx].__m128i   ()
    [rcx].mand16    (xmm1)
    [rcx].mor16     (xmm1)
    [rcx].mxor16    (xmm1)
    [rcx].rand16    (xmm1)
    [rcx].ror16     (xmm1)
    [rcx].rxor16    (xmm1)
    [rcx].andnot    (xmm1)

    [rcx].mequ888   (1, 2, 3, 4)
    [rcx].msub16    (xmm1)
    [rcx].madd16    (xmm1)
    [rcx].mshl16    (xmm1)
    [rcx].mshr16    (xmm1)

    [rcx].mshl8     (1)
    [rcx].rshl8     (2)
    [rcx].cmpeq     (xmm1)
    [rcx].cmpneq    (xmm1)
    [rcx].unpack_low(xmm1)
    [rcx].unpack_high(xmm1)
    ret

test_I32vec4 endp

test_Is32vec4 proc v:ptr Is32vec4

    assume rcx:ptr Is32vec4

    [rcx].mequ16    (xmm1)
    [rcx].__m128i   ()
    [rcx].mand16    (xmm1)
    [rcx].mor16     (xmm1)
    [rcx].mxor16    (xmm1)

    [rcx].mequ888   (1, 2, 3, 4)
    [rcx].cout      ("Is32vec4:")
    [rcx].msub16    (xmm1)
    [rcx].madd16    (xmm1)
    [rcx].mshl16    (xmm1)
    [rcx].mshr16    (xmm1)

    [rcx].mshl8     (1)
    [rcx].rshl8     (2)
    [rcx].cmpeq     (xmm1)
    [rcx].cmpneq    (xmm1)
    [rcx].unpack_low(xmm1)
    [rcx].unpack_high(xmm1)
    [rcx].cmpgt     (xmm1)
    [rcx].cmplt     (xmm1)
    ret

test_Is32vec4 endp

test_Iu32vec4 proc v:ptr Iu32vec4

    assume rcx:ptr Iu32vec4

    [rcx].mequ16    (xmm1)
    [rcx].__m128i   ()
    [rcx].mand16    (xmm1)
    [rcx].mor16     (xmm1)
    [rcx].mxor16    (xmm1)

    [rcx].mequ888   (1, 2, 3, 4)
    [rcx].cout      ("Iu32vec4:")
    [rcx].msub16    (xmm1)
    [rcx].madd16    (xmm1)
    [rcx].mshl16    (xmm1)
    [rcx].mshr16    (xmm1)
    [rcx].rmul16    (xmm1)

    [rcx].mshl8     (1)
    [rcx].rshl8     (2)
    [rcx].cmpeq     (xmm1)
    [rcx].cmpneq    (xmm1)
    [rcx].unpack_low(xmm1)
    [rcx].unpack_high(xmm1)
    ret

test_Iu32vec4 endp

test_I16vec8 proc v:ptr I16vec8

    assume rcx:ptr I16vec8

    [rcx].mequ16    (xmm1)
    [rcx].__m128i   ()
    [rcx].mand16    (xmm1)
    [rcx].mor16     (xmm1)
    [rcx].mxor16    (xmm1)

    [rcx].mequ888   (0, 1, 2, 3, 4, 5, 6, 7)

    [rcx].msub16    (xmm1)
    [rcx].madd16    (xmm1)
    [rcx].mmul16    (xmm1)
    [rcx].mshl16    (xmm1)
    [rcx].rshl16    (xmm1)

    [rcx].rshl8     (1)
    [rcx].mshl8     (2)

    [rcx].rmul16    (xmm1)
    [rcx].cmpeq     (xmm1)
    [rcx].cmpneq    (xmm1)
    [rcx].unpack_low(xmm1)
    [rcx].unpack_high(xmm1)
    ret

test_I16vec8 endp

test_Is16vec8 proc v:ptr Is16vec8

    assume rcx:ptr Is16vec8

    [rcx].mequ888   (0, 1, 2, 3, 4, 5, 6, 7)
    [rcx].cout      ("Is16vec8:")

    [rcx].mequ16    (xmm1)
    [rcx].__m128i   ()
    [rcx].mand16    (xmm1)
    [rcx].mor16     (xmm1)
    [rcx].mxor16    (xmm1)

    [rcx].msub16    (xmm1)
    [rcx].madd16    (xmm1)
    [rcx].mmul16    (xmm1)
    [rcx].mshl16    (xmm1)

    [rcx].rshl8     (1)
    [rcx].mshl8     (1)

    [rcx].rmul16    (xmm1)
    [rcx].cmpeq     (xmm1)
    [rcx].cmpneq    (xmm1)
    [rcx].unpack_low(xmm1)
    [rcx].unpack_high(xmm1)

    [rcx].cmpgt     (xmm1)
    [rcx].cmplt     (xmm1)
    [rcx].mul_high  (xmm1)
    [rcx].mul_add   (xmm1)
    [rcx].sat_add   (xmm1)
    [rcx].sat_sub   (xmm1)
    [rcx].simd_max  (xmm1)
    [rcx].simd_min  (xmm1)
    ret

test_Is16vec8 endp

test_Iu16vec8 proc v:ptr Iu16vec8

    assume rcx:ptr Iu16vec8

    [rcx].mequ888   (0, 1, 2, 3, 4, 5, 6, 7)
    [rcx].cout      ("Iu16vec8:")

    [rcx].mequ16    (xmm1)
    [rcx].__m128i   ()
    [rcx].mand16    (xmm1)
    [rcx].mor16     (xmm1)
    [rcx].mxor16    (xmm1)

    [rcx].msub16    (xmm1)
    [rcx].madd16    (xmm1)
    [rcx].mmul16    (xmm1)
    [rcx].mshl16    (xmm1)
    [rcx].mshr16    (xmm1)
    [rcx].rshr16    (xmm1)

    [rcx].rshl8     (1)
    [rcx].mshl8     (1)

    [rcx].rmul16    (xmm1)
    [rcx].cmpeq     (xmm1)
    [rcx].cmpneq    (xmm1)
    [rcx].unpack_low(xmm1)
    [rcx].unpack_high(xmm1)

    [rcx].mul_high  (xmm1)
    [rcx].sat_add   (xmm1)
    [rcx].sat_sub   (xmm1)
    [rcx].rmul16    (xmm1)
    ret

test_Iu16vec8 endp

test_I8vec16 proc v:ptr I8vec16

    assume rcx:ptr I8vec16

    [rcx].mequ888   (15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

    [rcx].mequ16    (xmm1)
    [rcx].__m128i   ()
    [rcx].mand16    (xmm1)
    [rcx].mor16     (xmm1)
    [rcx].mxor16    (xmm1)
    [rcx].msub16    (xmm1)
    [rcx].madd16    (xmm1)

    [rcx].cmpeq     (xmm1)
    [rcx].cmpneq    (xmm1)
    [rcx].unpack_low(xmm1)
    [rcx].unpack_high(xmm1)
    ret

test_I8vec16 endp

test_Is8vec16 proc v:ptr Is8vec16

    assume rcx:ptr Is8vec16

    [rcx].mequ888   (15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
    [rcx].cout      ("Is8vec16:")

    [rcx].mequ16    (xmm1)
    [rcx].__m128i   ()
    [rcx].mand16    (xmm1)
    [rcx].mor16     (xmm1)
    [rcx].mxor16    (xmm1)
    [rcx].msub16    (xmm1)
    [rcx].madd16    (xmm1)

    [rcx].cmpeq     (xmm1)
    [rcx].cmpneq    (xmm1)
    [rcx].unpack_low(xmm1)
    [rcx].unpack_high(xmm1)

    [rcx].cmpgt     (xmm1)
    [rcx].cmplt     (xmm1)
    [rcx].sat_add   (xmm1)
    [rcx].sat_sub   (xmm1)
    [rcx].pack_sat  (xmm1)

    ret

test_Is8vec16 endp

test_Iu8vec16 proc v:ptr Iuvec16

    assume rcx:ptr Iu8vec16

    [rcx].mequ888   (15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
    [rcx].cout      ("Iu8vec16:")

    [rcx].mequ16    (xmm1)
    [rcx].__m128i   ()
    [rcx].mand16    (xmm1)
    [rcx].mor16     (xmm1)
    [rcx].mxor16    (xmm1)
    [rcx].msub16    (xmm1)
    [rcx].madd16    (xmm1)
    [rcx].cmpeq     (xmm1)
    [rcx].cmpneq    (xmm1)
    [rcx].unpack_low(xmm1)
    [rcx].unpack_high(xmm1)
    [rcx].sat_add   (xmm1)
    [rcx].sat_sub   (xmm1)
    [rcx].simd_avg  (xmm1)
    [rcx].simd_max  (xmm1)
    [rcx].simd_min  (xmm1)
    [rcx].packu_sat (xmm1)
    ret

test_Iu8vec16 endp

test_F64vec2 proc v:ptr F64vec2

    assume rcx:ptr F64vec2

    [rcx].mequ88    (2.0, 1.0)
    [rcx].cout      ("F64vec2:")

    [rcx].mequ16    (xmm1)
    [rcx].__m128d   ()

    [rcx].rand16    (xmm1)
    [rcx].ror16     (xmm1)
    [rcx].rxor16    (xmm1)
    [rcx].rsub16    (xmm1)
    [rcx].radd16    (xmm1)
    [rcx].rmul16    (xmm1)
    [rcx].rdiv16    (xmm1)

    [rcx].madd16    (xmm1)
    [rcx].msub16    (xmm1)
    [rcx].mmul16    (xmm1)
    [rcx].mdiv16    (xmm1)
    [rcx].mand16    (xmm1)
    [rcx].mor16     (xmm1)
    [rcx].mxor16    (xmm1)

    [rcx].add_horizontal()
    [rcx].andnot    (xmm1)
    [rcx].sqrt      ()

    [rcx].cmpeq     (xmm1)
    [rcx].cmplt     (xmm1)
    [rcx].cmple     (xmm1)
    [rcx].cmpgt     (xmm1)
    [rcx].cmpge     (xmm1)
    [rcx].cmpngt    (xmm1)
    [rcx].cmpnge    (xmm1)
    [rcx].cmpnlt    (xmm1)
    [rcx].cmpnle    (xmm1)

    [rcx].simd_min  (xmm1)
    [rcx].simd_max  (xmm1)
    [rcx].abs       ()

    [rcx].comieq    (xmm1)
    [rcx].comilt    (xmm1)
    [rcx].comile    (xmm1)
    [rcx].comigt    (xmm1)
    [rcx].comige    (xmm1)
    [rcx].comineq   (xmm1)

    [rcx].ucomieq   (xmm1)
    [rcx].ucomilt   (xmm1)
    [rcx].ucomile   (xmm1)
    [rcx].ucomigt   (xmm1)
    [rcx].ucomige   (xmm1)
    [rcx].ucomineq  (xmm1)

    [rcx].unpack_low(xmm1)
    [rcx].unpack_high(xmm1)
    [rcx].move_mask ()
    [rcx].loadu     ()
    [rcx].storeu    ()
    [rcx].store_nta ()

    [rcx].select_eq (xmm1, xmm2, xmm3)
    [rcx].select_lt (xmm1, xmm2, xmm3)
    [rcx].select_le (xmm1, xmm2, xmm3)
    [rcx].select_gt (xmm1, xmm2, xmm3)
    [rcx].select_ge (xmm1, xmm2, xmm3)
    [rcx].select_neq(xmm1, xmm2, xmm3)
    [rcx].select_nlt(xmm1, xmm2, xmm3)
    [rcx].select_nle(xmm1, xmm2, xmm3)
    [rcx].ToInt     ()
    [rcx].ToF32vec4 ()
    ret

test_F64vec2 endp

test_F32vec8 proc v:ptr F32vec8

    assume rcx:ptr F32vec8

    [rcx].mequ888   (8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0)
    [rcx].cout      ("F32vec8:")
    [rcx].mequ4     (4.0)
    [rcx].mequ8     (8.0)
    [rcx].mequ32    (_mm256_set_epi32(ymm1,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0))
    [rcx].__m256    ()

    [rcx].add_horizontal()
    [rcx].andnot    (ymm1)
    [rcx].sqrt      ()

    [rcx].rcp       ()
    [rcx].rsqrt     ()
    [rcx].rcp_nr    ()
    [rcx].rsqrt_nr  ()

    [rcx].cmp_eq    (ymm1)
    [rcx].cmp_lt    (ymm1)
    [rcx].cmp_le    (ymm1)
    [rcx].cmp_gt    (ymm1)
    [rcx].cmp_ge    (ymm1)
    [rcx].cmp_neq   (ymm1)
    [rcx].cmp_nlt   (ymm1)
    [rcx].cmp_nle   (ymm1)
    [rcx].cmp_ngt   (ymm1)
    [rcx].cmp_nge   (ymm1)

    [rcx].simd_min  (ymm1)
    [rcx].simd_max  (ymm1)
    [rcx].abs       ()

    [rcx].unpack_low(ymm1)
    [rcx].unpack_high(ymm1)
    [rcx].move_mask ()
    [rcx].loadu     ()
    [rcx].storeu    ()
    [rcx].store_nta ()
    [rcx].maskload  ()
    [rcx].maskstore (ymm1)

    [rcx].select_eq (ymm1, ymm2, ymm3)
    [rcx].select_lt (ymm1, ymm2, ymm3)
    [rcx].select_le (ymm1, ymm2, ymm3)
    [rcx].select_gt (ymm1, ymm2, ymm3)
    [rcx].select_ge (ymm1, ymm2, ymm3)
    [rcx].select_neq(ymm1, ymm2, ymm3)
    [rcx].select_nlt(ymm1, ymm2, ymm3)
    [rcx].select_nle(ymm1, ymm2, ymm3)
    [rcx].select_ngt(ymm1, ymm2, ymm3)
    [rcx].select_nge(ymm1, ymm2, ymm3)
    ret

test_F32vec8 endp

test_F32vec4 proc v:ptr F32vec4

    assume rcx:ptr F32vec4

    [rcx].mequ444   (1.0, 2.0, 3.0, 4.0)
    [rcx].cout      ("F32vec4:")
    [rcx].mequ4     (4.0)
    [rcx].mequ8     (8.0)
    [rcx].mequ16    (xmm1)
    [rcx].__m128    ()

    [rcx].rand16    (xmm1)
    [rcx].ror16     (xmm1)
    [rcx].rxor16    (xmm1)
    [rcx].radd16    (xmm1)
    [rcx].rsub16    (xmm1)
    [rcx].rmul16    (xmm1)
    [rcx].rdiv16    (xmm1)

    [rcx].madd16    (xmm1)
    [rcx].msub16    (xmm1)
    [rcx].mmul16    (xmm1)
    [rcx].mdiv16    (xmm1)
    [rcx].mand16    (xmm1)
    [rcx].mor16     (xmm1)
    [rcx].mxor16    (xmm1)

    [rcx].add_horizontal()
    [rcx].sqrt      ()
    [rcx].rcp       ()
    [rcx].rsqrt     ()
    [rcx].rcp_nr    ()
    [rcx].rsqrt_nr  ()

    [rcx].cmpeq     (xmm1)
    [rcx].cmplt     (xmm1)
    [rcx].cmple     (xmm1)
    [rcx].cmpgt     (xmm1)
    [rcx].cmpge     (xmm1)
    [rcx].cmpneq    (xmm1)
    [rcx].cmpnlt    (xmm1)
    [rcx].cmpnle    (xmm1)
    [rcx].cmpngt    (xmm1)
    [rcx].cmpnge    (xmm1)

    [rcx].simd_max  (xmm1)
    [rcx].simd_min  (xmm1)

    [rcx].select_eq (xmm1, xmm2, xmm3)
    [rcx].select_lt (xmm1, xmm2, xmm3)
    [rcx].select_le (xmm1, xmm2, xmm3)
    [rcx].select_neq(xmm1, xmm2, xmm3)
    [rcx].select_nlt(xmm1, xmm2, xmm3)
    [rcx].select_nle(xmm1, xmm2, xmm3)
    [rcx].select_ngt(xmm1, xmm2, xmm3)
    [rcx].select_nge(xmm1, xmm2, xmm3)
    [rcx].select_gt (xmm1, xmm2, xmm3)
    [rcx].select_ge (xmm1, xmm2, xmm3)

    [rcx].abs       ()
    [rcx].unpack_low(xmm1)
    [rcx].unpack_high(xmm1)
    [rcx].loadu     ()
    [rcx].storeu    ()
    [rcx].store_nta ()
    ret

test_F32vec4 endp

test_F32vec1 proc v:ptr F32vec1

    assume rcx:ptr F32vec1

    [rcx].mequ4     (4.0)
    [rcx].mequ8     (8.0)
    [rcx].cout      ("F32vec1:")
    [rcx].mequ16    (xmm1)
    [rcx].__m128    ()

    [rcx].rand16    (xmm1)
    [rcx].ror16     (xmm1)
    [rcx].rxor16    (xmm1)
    [rcx].radd16    (xmm1)
    [rcx].rsub16    (xmm1)
    [rcx].rmul16    (xmm1)
    [rcx].rdiv16    (xmm1)

    [rcx].madd16    (xmm1)
    [rcx].msub16    (xmm1)
    [rcx].mmul16    (xmm1)
    [rcx].mdiv16    (xmm1)
    [rcx].mand16    (xmm1)
    [rcx].mor16     (xmm1)
    [rcx].mxor16    (xmm1)

    [rcx].sqrt      ()
    [rcx].rcp       ()
    [rcx].rsqrt     ()
    [rcx].rcp_nr    ()
    [rcx].rsqrt_nr  ()

    [rcx].cmpeq     (xmm1)
    [rcx].cmplt     (xmm1)
    [rcx].cmple     (xmm1)
    [rcx].cmpgt     (xmm1)
    [rcx].cmpge     (xmm1)
    [rcx].cmpneq    (xmm1)
    [rcx].cmpnlt    (xmm1)
    [rcx].cmpnle    (xmm1)
    [rcx].cmpngt    (xmm1)
    [rcx].cmpnge    (xmm1)

    [rcx].simd_max  (xmm1)
    [rcx].simd_min  (xmm1)

    [rcx].select_eq (xmm1, xmm2, xmm3)
    [rcx].select_lt (xmm1, xmm2, xmm3)
    [rcx].select_le (xmm1, xmm2, xmm3)
    [rcx].select_neq(xmm1, xmm2, xmm3)
    [rcx].select_nlt(xmm1, xmm2, xmm3)
    [rcx].select_nle(xmm1, xmm2, xmm3)
    [rcx].select_ngt(xmm1, xmm2, xmm3)
    [rcx].select_nge(xmm1, xmm2, xmm3)
    [rcx].select_gt (xmm1, xmm2, xmm3)
    [rcx].select_ge (xmm1, xmm2, xmm3)
    ret

test_F32vec1 endp


main proc

  local v256:vec256_t
  local v128:vec128_t

    test_M128       (&v128)
    test_I128vec1   (&v128)
    test_I64vec2    (&v128)
    test_I32vec4    (&v128)
    test_Is32vec4   (&v128)
    test_Iu32vec4   (&v128)
    test_I16vec8    (&v128)
    test_Is16vec8   (&v128)
    test_Iu16vec8   (&v128)
    test_I8vec16    (&v128)
    test_Is8vec16   (&v128)
    test_Iu8vec16   (&v128)
    test_F64vec2    (&v128)
    test_F32vec8    (&v256)
    test_F32vec4    (&v128)
    test_F32vec1    (&v128)

    vzeroupper
    .return 0

main endp

    end
