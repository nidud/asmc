ifndef __GRAPHENE_SIMD4F_H__
define __GRAPHENE_SIMD4F_H__

if  not defined(GRAPHENE_H_INSIDE) and not defined(GRAPHENE_COMPILATION)
.err <"Only graphene.h can be included directly.">
endif

include string.inc
include math.inc
include float.inc

include graphene/graphene-config.inc
include graphene/graphene-macros.inc
include graphene/graphene-version-macros.inc

graphene_simd4f_init proto :real4, :real4, :real4, :real4
graphene_simd4f_init_zero proto
graphene_simd4f_init_4f proto :ptr
graphene_simd4f_init_3f proto :ptr
graphene_simd4f_init_2f proto :ptr

graphene_simd4f_dup_4f proto :graphene_simd4f_t, :ptr
graphene_simd4f_dup_3f proto :graphene_simd4f_t, :ptr
graphene_simd4f_dup_2f proto :graphene_simd4f_t, :ptr

graphene_simd4f_get proto :graphene_simd4f_t, :dword
graphene_simd4f_get_x proto :graphene_simd4f_t
graphene_simd4f_get_y proto :graphene_simd4f_t
graphene_simd4f_get_z proto :graphene_simd4f_t
graphene_simd4f_get_w proto :graphene_simd4f_t

graphene_simd4f_splat proto :real4
graphene_simd4f_splat_x proto :graphene_simd4f_t
graphene_simd4f_splat_y proto :graphene_simd4f_t
graphene_simd4f_splat_z proto :graphene_simd4f_t
graphene_simd4f_splat_w proto :graphene_simd4f_t

graphene_simd4f_add proto :graphene_simd4f_t, :graphene_simd4f_t
graphene_simd4f_sub proto :graphene_simd4f_t, :graphene_simd4f_t
graphene_simd4f_mul proto :graphene_simd4f_t, :graphene_simd4f_t
graphene_simd4f_div proto :graphene_simd4f_t, :graphene_simd4f_t

graphene_simd4f_sqrt proto :graphene_simd4f_t
graphene_simd4f_reciprocal proto :graphene_simd4f_t
graphene_simd4f_rsqrt proto :graphene_simd4f_t

graphene_simd4f_cross3 proto :graphene_simd4f_t, :graphene_simd4f_t
graphene_simd4f_dot3 proto :graphene_simd4f_t, :graphene_simd4f_t
graphene_simd4f_dot3_scalar proto :graphene_simd4f_t, :graphene_simd4f_t

graphene_simd4f_min proto :graphene_simd4f_t, :graphene_simd4f_t
graphene_simd4f_max proto :graphene_simd4f_t, :graphene_simd4f_t

graphene_simd4f_shuffle_wxyz proto :graphene_simd4f_t
graphene_simd4f_shuffle_zwxy proto :graphene_simd4f_t
graphene_simd4f_shuffle_yzwx proto :graphene_simd4f_t

graphene_simd4f_zero_w proto :graphene_simd4f_t
graphene_simd4f_zero_zw proto :graphene_simd4f_t

graphene_simd4f_merge_high proto :graphene_simd4f_t, :graphene_simd4f_t
graphene_simd4f_merge_low proto :graphene_simd4f_t, :graphene_simd4f_t
graphene_simd4f_merge_w proto :graphene_simd4f_t, :real4

graphene_simd4f_flip_sign_0101 proto :graphene_simd4f_t
graphene_simd4f_flip_sign_1010 proto :graphene_simd4f_t

graphene_simd4f_cmp_eq proto :graphene_simd4f_t, :graphene_simd4f_t
graphene_simd4f_cmp_neq proto :graphene_simd4f_t, :graphene_simd4f_t
graphene_simd4f_cmp_lt proto :graphene_simd4f_t, :graphene_simd4f_t
graphene_simd4f_cmp_le proto :graphene_simd4f_t, :graphene_simd4f_t
graphene_simd4f_cmp_ge proto :graphene_simd4f_t, :graphene_simd4f_t
graphene_simd4f_cmp_gt proto :graphene_simd4f_t, :graphene_simd4f_t
graphene_simd4f_neg proto :graphene_simd4f_t

if  not defined(__GI_SCANNER__) and defined(GRAPHENE_USE_SSE)

graphene_simd4f_union_t UNION
s                       graphene_simd4f_t <>
f                       real4 4 dup(?)
graphene_simd4f_union_t ENDS

if defined(__GNUC__)

if defined(GRAPHENE_USE_SSE4_1)
else
endif

elseif defined (_MSC_VER)


graphene_simd4f_init macro x,y,z,w
  exitm<_simd4f_init(x,y,z,w)>
  endm


graphene_simd4f_init_zero macro
  exitm<_mm_setzero_ps()>
  endm

graphene_simd4f_init_4f macro v
  exitm<_mm_loadu_ps(v)>
  endm

graphene_simd4f_init_3f macro v
  exitm<graphene_simd4f_init (v[0], v[1], v[2], 0.f)>
  endm

graphene_simd4f_init_2f macro v
  exitm<graphene_simd4f_init (v[0], v[1], 0.f, 0.f)>
  endm

graphene_simd4f_dup_4f macro s,v
  exitm<_mm_storeu_ps (v, s)>
  endm

graphene_simd4f_dup_3f macro s,v
  exitm<memcpy (v, &s, sizeof (float) * 3)>
  endm

graphene_simd4f_dup_2f macro s,v
  exitm<memcpy (v, &s, sizeof (float) * 2)>
  endm

graphene_simd4f_get macro s,i
  exitm<_simd4f_get_xyzw(s, i)>
  endm
graphene_simd4f_get_x macro s
  exitm<_simd4f_get_xyzw(s, 0)>
  endm
graphene_simd4f_get_y macro s
  exitm<_simd4f_get_xyzw(s, 1)>
  endm
graphene_simd4f_get_z macro s
  exitm<_simd4f_get_xyzw(s, 2)>
  endm
graphene_simd4f_get_w macro s
  exitm<_simd4f_get_xyzw(s, 3)>
  endm



graphene_simd4f_splat macro v
  exitm<_mm_set1_ps (v)>
  endm

graphene_simd4f_splat_x macro v
  exitm<_mm_shuffle_ps (v, v, _MM_SHUFFLE (0, 0, 0, 0))>
  endm

graphene_simd4f_splat_y macro v
  exitm<_mm_shuffle_ps (v, v, _MM_SHUFFLE (1, 1, 1, 1))>
  endm

graphene_simd4f_splat_z macro v
  exitm<_mm_shuffle_ps (v, v, _MM_SHUFFLE (2, 2, 2, 2))>
  endm

graphene_simd4f_splat_w macro v
  exitm<_mm_shuffle_ps (v, v, _MM_SHUFFLE (3, 3, 3, 3))>
  endm

graphene_simd4f_add macro a,b
  exitm<_mm_add_ps (a, b)>
  endm

graphene_simd4f_sub macro a,b
  exitm<_mm_sub_ps (a, b)>
  endm

graphene_simd4f_mul macro a,b
  exitm<_mm_mul_ps (a, b)>
  endm

graphene_simd4f_div macro a,b
  exitm<_mm_div_ps (a, b)>
  endm

graphene_simd4f_sqrt macro v
  exitm<_mm_sqrt_ps (v)>
  endm

graphene_simd4f_reciprocal macro v
  exitm<_simd4f_reciprocal(v)>
  endm

graphene_simd4f_rsqrt macro v
  exitm<_simd4f_rsqrt(v)>
  endm

graphene_simd4f_cross3 macro a,b
  exitm<_simd4f_cross3(a,b)>
  endm

graphene_simd4f_dot3 macro a,b
  exitm<_simd4f_dot3(a,b)>
  endm

if defined(GRAPHENE_USE_SSE4_1)

else
endif

graphene_simd4f_dot3_scalar macro a,b
  exitm<_simd4f_dot3_scalar(a,b)>
  endm

graphene_simd4f_min macro a,b
  exitm<_mm_min_ps (a, b)>
  endm

graphene_simd4f_max macro a,b
  exitm<_mm_max_ps (a, b)>
  endm


graphene_simd4f_shuffle_wxyz macro v
  exitm<_mm_shuffle_ps (v, v, _MM_SHUFFLE (2, 1, 0, 3))>
  endm

graphene_simd4f_shuffle_zwxy macro v
  exitm<_mm_shuffle_ps (v, v, _MM_SHUFFLE (1, 0, 3, 2))>
  endm

graphene_simd4f_shuffle_yzwx macro v
  exitm<_mm_shuffle_ps (v, v, _MM_SHUFFLE (0, 3, 2, 1))>
  endm

graphene_simd4f_zero_w macro v
  exitm<_mm_movelh_ps (v, _mm_unpackhi_ps (v, _mm_setzero_ps ()))>
  endm

graphene_simd4f_zero_zw macro v
  exitm<_mm_movelh_ps (v, _mm_setzero_ps ())>
  endm

graphene_simd4f_merge_w macro s,v
  exitm<_mm_movelh_ps (s, _mm_unpackhi_ps (s, _mm_set1_ps (v)))>
  endm

graphene_simd4f_merge_high macro a,b
  exitm<_mm_movehl_ps (b, a)>
  endm

graphene_simd4f_merge_low macro a,b
  exitm<_mm_movelh_ps (a, b)>
  endm

graphene_simd4f_flip_sign_0101 macro v
  exitm<_simd4f_flip_sign_0101(v)>
  endm

graphene_simd4f_flip_sign_1010 macro v
  exitm<_simd4f_flip_sign_1010(v)>
  endm

graphene_simd4f_cmp_eq macro a,b
  exitm<_simd4f_cmp_eq(a,b)>
  endm

graphene_simd4f_cmp_neq macro a,b
  exitm<_simd4f_cmp_neq(a,b)>
  endm

graphene_simd4f_cmp_lt macro a,b
  exitm<_simd4f_cmp_lt(a,b)>
  endm

graphene_simd4f_cmp_le macro a,b
  exitm<_simd4f_cmp_le(a,b)>
  endm

graphene_simd4f_cmp_ge macro a,b
  exitm<_simd4f_cmp_ge(a,b)>
  endm

graphene_simd4f_cmp_gt macro a,b
  exitm<_simd4f_cmp_gt(a,b)>
  endm

graphene_simd4f_neg macro s
  exitm<_simd4f_neg(s)>
  endm

else

.err <"Need GCC-compatible or Visual Studio compiler for SSE extensions.">

endif

elseif  not defined(__GI_SCANNER__) and defined(GRAPHENE_USE_GCC)
endif

endif
