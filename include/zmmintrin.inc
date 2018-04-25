ifndef _ZMMINTRIN_H_INCLUDED
_ZMMINTRIN_H_INCLUDED equ <>

ifndef _INCLUDED_IMM
.err <Header should only be included from immintrin.h>
endif

__mmask8		typedef byte
__mmask16		typedef word
__mmask32		typedef dword
__mmask64		typedef qword

__m512			union
m512_f32		real4 16 dup(?)
__m512			ENDS

__m512d			STRUC
m512d_f64		real8 8 dup(?)
__m512d			ENDS

__m512i			union
m512i_i8		sbyte 64 dup(?)
m512i_i16		sword 32 dup(?)
m512i_i32		sdword 16 dup(?)
m512i_i64		sqword 8 dup(?)
m512i_u8		db 64 dup(?)
m512i_u16		dw 32 dup(?)
m512i_u32		dd 16 dup(?)
m512i_u64		dq 8 dup(?)
__m512i			ENDS


_mm512_castps512_ps256	proto :zword
_mm512_castpd_ps	proto :zword
_mm512_castps256_ps512	proto :yword
_mm512_castsi512_ps	proto :zword
_mm512_castps128_ps512	proto :oword

_mm512_castpd512_pd256	proto :zword
_mm512_castpd256_pd512	proto :yword
_mm512_castps_pd	proto :zword
_mm512_castsi512_pd	proto :zword
_mm512_castpd128_pd512	proto :oword

_mm512_castsi512_si256	proto :zword
_mm512_castpd_si512	proto :zword
_mm512_castps_si512	proto :zword
_mm512_castsi256_si512	proto :yword

_MM_K0_REG		equ (0xffff)
_MM_K0_REG64		equ (0xffffffffffffffff)

_MM_BROADCAST32_NONE	equ 0
_MM_BROADCAST_16X16	equ _MM_BROADCAST32_NONE
_MM_BROADCAST_1X16	equ 1
_MM_BROADCAST_4X16	equ 2

_MM_BROADCAST64_NONE	equ 0
_MM_BROADCAST_8X8	equ _MM_BROADCAST64_NONE
_MM_BROADCAST_1X8	equ 1
_MM_BROADCAST_4X8	equ 2

_MM_ROUND_MODE_NEAREST	equ 0
_MM_ROUND_MODE_DOWN	equ 1
_MM_ROUND_MODE_UP	equ 2
_MM_ROUND_MODE_TOWARD_ZERO equ 3
_MM_ROUND_MODE_DEFAULT	equ 4

_MM_EXPADJ_NONE		equ 0
_MM_EXPADJ_4		equ 1
_MM_EXPADJ_5		equ 2
_MM_EXPADJ_8		equ 3
_MM_EXPADJ_16		equ 4
_MM_EXPADJ_24		equ 5
_MM_EXPADJ_31		equ 6
_MM_EXPADJ_32		equ 7

_MM_SCALE_1		equ 1
_MM_SCALE_2		equ 2
_MM_SCALE_4		equ 4
_MM_SCALE_8		equ 8

_MM_FIXUP_NO_CHANGE	equ 0
_MM_FIXUP_NEG_INF	equ 1
_MM_FIXUP_NEG_ZERO	equ 2
_MM_FIXUP_POS_ZERO	equ 3
_MM_FIXUP_POS_INF	equ 4
_MM_FIXUP_NAN		equ 5
_MM_FIXUP_MAX_FLOAT	equ 6
_MM_FIXUP_MIN_FLOAT	equ 7

_MM_FIXUP macro _NegInf
	exitm<>
	endm

_MM_MANT_NORM_1_2	equ 0
_MM_MANT_NORM_p5_2	equ 1
_MM_MANT_NORM_p5_1	equ 2
_MM_MANT_NORM_p75_1p5	equ 3

_MM_MANT_SIGN_src	equ 0
_MM_MANT_SIGN_zero	equ 1
_MM_MANT_SIGN_nan	equ 2

_MM_CMPINT_EQ		equ 0
_MM_CMPINT_LT		equ 1
_MM_CMPINT_LE		equ 2
_MM_CMPINT_UNUSED	equ 3
_MM_CMPINT_NE		equ 4
_MM_CMPINT_NLT		equ 5
_MM_CMPINT_GE		equ _MM_CMPINT_NLT
_MM_CMPINT_NLE		equ 6
_MM_CMPINT_GT		equ _MM_CMPINT_NLE


_mm512_setzero_ps	proto
_mm512_setzero_pd	proto

_mm512_set_ps		proto :real4, :real4, :real4, :real4, :real4, :real4, :real4, :real4,
			      :real4, :real4, :real4, :real4, :real4, :real4, :real4, :real4
_mm512_set_pd		proto :real8, :real8, :real8, :real8, :real8, :real8, :real8, :real8

_mm512_set1_ps		proto :real4
_mm512_set1_pd		proto :real8

_mm512_maskz_load_ps	proto :word, :ptr
_mm512_maskz_load_pd	proto :byte, :ptr
_mm512_mask_load_ps	proto :zword, :word, :ptr
_mm512_mask_load_pd	proto :zword, :byte, :ptr
_mm512_maskz_loadu_ps	proto :word, :ptr
_mm512_maskz_loadu_pd	proto :byte, :ptr
_mm512_mask_loadu_ps	proto :zword, :word, :ptr
_mm512_mask_loadu_pd	proto :zword, :byte, :ptr

_mm512_storeu_ps	proto :ptr, :zword
_mm512_storeu_pd	proto :ptr, :zword
_mm512_mask_store_ps	proto :ptr, :word, :zword
_mm512_mask_store_pd	proto :ptr, :byte, :zword
_mm512_mask_storeu_ps	proto :ptr, :word, :zword
_mm512_mask_storeu_pd	proto :ptr, :byte, :zword

_mm512_maskz_add_round_ps	proto :word, :zword, :zword, :sdword
_mm512_maskz_add_round_pd	proto :byte, :zword, :zword, :sdword
_mm512_mask_add_round_ps	proto :zword, :word, :zword, :zword, :sdword
_mm512_mask_add_round_pd	proto :zword, :byte, :zword, :zword, :sdword

_mm512_maskz_sub_round_ps	proto :word, :zword, :zword, :sdword
_mm512_maskz_sub_round_pd	proto :byte, :zword, :zword, :sdword
_mm512_mask_sub_round_ps	proto :zword, :word, :zword, :zword, :sdword
_mm512_mask_sub_round_pd	proto :zword, :byte, :zword, :zword, :sdword

_mm512_maskz_mul_round_ps	proto :word, :zword, :zword, :sdword
_mm512_maskz_mul_round_pd	proto :byte, :zword, :zword, :sdword
_mm512_mask_mul_round_ps	proto :zword, :word, :zword, :zword, :sdword
_mm512_mask_mul_round_pd	proto :zword, :byte, :zword, :zword, :sdword

_mm512_maskz_div_round_pd	proto :byte, :zword, :zword, :sdword
_mm512_maskz_div_round_ps	proto :word, :zword, :zword, :sdword
_mm512_mask_div_round_ps	proto :zword, :word, :zword, :zword, :sdword
_mm512_mask_div_round_pd	proto :zword, :byte, :zword, :zword, :sdword

_mm512_mask_fmadd_round_ps	proto :zword, :word, :zword, :zword, :sdword
_mm512_mask3_fmadd_round_ps	proto :zword, :zword, :zword, :word, :sdword
_mm512_maskz_fmadd_round_ps	proto :word, :zword, :zword, :zword, :sdword
_mm512_mask_fmadd_round_pd	proto :zword, :byte, :zword, :zword, :sdword
_mm512_mask3_fmadd_round_pd	proto :zword, :zword, :zword, :byte, :sdword
_mm512_maskz_fmadd_round_pd	proto :byte, :zword, :zword, :zword, :sdword

_mm512_mask_fmsub_round_ps	proto :zword, :word, :zword, :zword, :sdword
_mm512_mask3_fmsub_round_ps	proto :zword, :zword, :zword, :word, :sdword
_mm512_maskz_fmsub_round_ps	proto :word, :zword, :zword, :zword, :sdword
_mm512_mask_fmsub_round_pd	proto :zword, :byte, :zword, :zword, :sdword
_mm512_mask3_fmsub_round_pd	proto :zword, :zword, :zword, :byte, :sdword
_mm512_maskz_fmsub_round_pd	proto :byte, :zword, :zword, :zword, :sdword

_mm512_mask_fmaddsub_round_ps	proto :zword, :word, :zword, :zword, :sdword
_mm512_mask3_fmaddsub_round_ps	proto :zword, :zword, :zword, :word, :sdword
_mm512_maskz_fmaddsub_round_ps	proto :word, :zword, :zword, :zword, :sdword
_mm512_mask_fmaddsub_round_pd	proto :zword, :byte, :zword, :zword, :sdword
_mm512_mask3_fmaddsub_round_pd	proto :zword, :zword, :zword, :byte, :sdword
_mm512_maskz_fmaddsub_round_pd	proto :byte, :zword, :zword, :zword, :sdword

_mm512_mask_fmsubadd_round_ps	proto :zword, :word, :zword, :zword, :sdword
_mm512_mask3_fmsubadd_round_ps	proto :zword, :zword, :zword, :word, :sdword
_mm512_maskz_fmsubadd_round_ps	proto :word, :zword, :zword, :zword, :sdword
_mm512_mask_fmsubadd_round_pd	proto :zword, :byte, :zword, :zword, :sdword
_mm512_mask3_fmsubadd_round_pd	proto :zword, :zword, :zword, :byte, :sdword
_mm512_maskz_fmsubadd_round_pd	proto :byte, :zword, :zword, :zword, :sdword

_mm512_mask_fnmadd_round_ps	proto :zword, :word, :zword, :zword, :sdword
_mm512_mask3_fnmadd_round_ps	proto :zword, :zword, :zword, :word, :sdword
_mm512_maskz_fnmadd_round_ps	proto :word, :zword, :zword, :zword, :sdword
_mm512_mask_fnmadd_round_pd	proto :zword, :byte, :zword, :zword, :sdword
_mm512_mask3_fnmadd_round_pd	proto :zword, :zword, :zword, :byte, :sdword
_mm512_maskz_fnmadd_round_pd	proto :byte, :zword, :zword, :zword, :sdword

_mm512_mask_fnmsub_round_ps	proto :zword, :word, :zword, :zword, :sdword
_mm512_mask3_fnmsub_round_ps	proto :zword, :zword, :zword, :word, :sdword
_mm512_maskz_fnmsub_round_ps	proto :word, :zword, :zword, :zword, :sdword
_mm512_mask_fnmsub_round_pd	proto :zword, :byte, :zword, :zword, :sdword
_mm512_mask3_fnmsub_round_pd	proto :zword, :zword, :zword, :byte, :sdword
_mm512_maskz_fnmsub_round_pd	proto :byte, :zword, :zword, :zword, :sdword

_mm512_maskz_sqrt_round_ps	proto :word, :zword, :sdword
_mm512_maskz_sqrt_round_pd	proto :byte, :zword, :sdword
_mm512_mask_sqrt_round_ps	proto :zword, :word, :zword, :sdword
_mm512_mask_sqrt_round_pd	proto :zword, :byte, :zword, :sdword

_mm512_maskz_abs_ps		proto :word, :zword
_mm512_mask_abs_ps		proto :zword, :word, :zword
_mm512_maskz_abs_pd		proto :byte, :zword
_mm512_mask_abs_pd		proto :zword, :byte, :zword

_mm512_maskz_max_round_ps	proto :word, :zword, :zword, :sdword
_mm512_maskz_max_round_pd	proto :byte, :zword, :zword, :sdword
_mm512_mask_max_round_ps	proto :zword, :word, :zword, :zword, :sdword
_mm512_mask_max_round_pd	proto :zword, :byte, :zword, :zword, :sdword

_mm512_maskz_min_round_ps	proto :word, :zword, :zword, :sdword
_mm512_maskz_min_round_pd	proto :byte, :zword, :zword, :sdword
_mm512_mask_min_round_ps	proto :zword, :word, :zword, :zword, :sdword
_mm512_mask_min_round_pd	proto :zword, :byte, :zword, :zword, :sdword

_mm512_maskz_rcp14_ps	proto :word, :zword
_mm512_maskz_rcp14_pd	proto :byte, :zword
_mm512_mask_rcp14_ps	proto :zword, :word, :zword
_mm512_mask_rcp14_pd	proto :zword, :byte, :zword

_mm512_maskz_rsqrt14_ps proto :word, :zword
_mm512_maskz_rsqrt14_pd proto :byte, :zword
_mm512_mask_rsqrt14_ps	proto :zword, :word, :zword
_mm512_mask_rsqrt14_pd	proto :zword, :byte, :zword

_mm512_mask_rcp28_round_ps	proto :zword, :word, :zword, :sdword
_mm512_maskz_rcp28_round_ps	proto :word, :zword, :sdword
_mm512_mask_rcp28_round_pd	proto :zword, :byte, :zword, :sdword
_mm512_maskz_rcp28_round_pd	proto :byte, :zword, :sdword
_mm512_mask_rsqrt28_round_ps	proto :zword, :word, :zword, :sdword
_mm512_maskz_rsqrt28_round_ps	proto :word, :zword, :sdword
_mm512_mask_rsqrt28_round_pd	proto :zword, :byte, :zword, :sdword
_mm512_maskz_rsqrt28_round_pd	proto :byte, :zword, :sdword

_mm512_maskz_cvt_roundps_pd	proto :byte, :yword, :sdword
_mm512_maskz_cvt_roundpd_ps	proto :byte, :zword, :sdword
_mm512_mask_cvt_roundps_pd	proto :zword, :byte, :yword, :sdword
_mm512_mask_cvt_roundpd_ps	proto :yword, :byte, :zword, :sdword

_mm512_mask_cmp_round_ps_mask	proto :word, :zword, :zword, :sdword, :sdword
_mm512_mask_cmp_round_pd_mask	proto :byte, :zword, :zword, :sdword, :sdword

_mm512_mask_broadcast_f32x2	proto :zword, :word, :oword
_mm512_maskz_broadcast_f32x2	proto :word, :oword
_mm512_mask_broadcast_f32x4	proto :zword, :word, :oword
_mm512_maskz_broadcast_f32x4	proto :word, :oword
_mm512_mask_broadcast_f32x8	proto :zword, :word, :yword
_mm512_maskz_broadcast_f32x8	proto :word, :yword
_mm512_mask_broadcast_f64x2	proto :zword, :byte, :oword
_mm512_maskz_broadcast_f64x2	proto :byte, :oword
_mm512_mask_broadcast_f64x4	proto :zword, :byte, :yword
_mm512_maskz_broadcast_f64x4	proto :byte, :yword
_mm512_mask_broadcastsd_pd	proto :zword, :byte, :oword
_mm512_maskz_broadcastsd_pd	proto :byte, :oword
_mm512_mask_broadcastss_ps	proto :zword, :word, :oword
_mm512_maskz_broadcastss_ps	proto :word, :oword

_mm512_mask_extractf32x4_ps	proto :oword, :byte, :zword, :sdword
_mm512_maskz_extractf32x4_ps	proto :byte, :zword, :sdword
_mm512_mask_extractf32x8_ps	proto :yword, :byte, :zword, :sdword
_mm512_maskz_extractf32x8_ps	proto :byte, :zword, :sdword
_mm512_mask_extractf64x2_pd	proto :oword, :byte, :zword, :sdword
_mm512_maskz_extractf64x2_pd	proto :byte, :zword, :sdword
_mm512_mask_extractf64x4_pd	proto :yword, :byte, :zword, :sdword
_mm512_maskz_extractf64x4_pd	proto :byte, :zword, :sdword

_mm512_mask_insertf32x4		proto :zword, :word, :zword, :oword, :sdword
_mm512_maskz_insertf32x4	proto :word, :zword, :oword, :sdword
_mm512_mask_insertf32x8		proto :zword, :word, :zword, :yword, :sdword
_mm512_maskz_insertf32x8	proto :word, :zword, :yword, :sdword
_mm512_mask_insertf64x2		proto :zword, :byte, :zword, :oword, :sdword
_mm512_maskz_insertf64x2	proto :byte, :zword, :oword, :sdword
_mm512_mask_insertf64x4		proto :zword, :byte, :zword, :yword, :sdword
_mm512_maskz_insertf64x4	proto :byte, :zword, :yword, :sdword

_mm512_mask_shuffle_f32x4	proto :zword, :word, :zword, :zword, :sdword
_mm512_maskz_shuffle_f32x4	proto :word, :zword, :zword, :sdword
_mm512_mask_shuffle_f64x2	proto :zword, :byte, :zword, :zword, :sdword
_mm512_maskz_shuffle_f64x2	proto :byte, :zword, :zword, :sdword
_mm512_mask_shuffle_pd		proto :zword, :byte, :zword, :zword, :sdword
_mm512_maskz_shuffle_pd		proto :byte, :zword, :zword, :sdword
_mm512_mask_shuffle_ps		proto :zword, :word, :zword, :zword, :sdword
_mm512_maskz_shuffle_ps		proto :word, :zword, :zword, :sdword


_mm512_setzero macro
	exitm<_mm512_setzero_ps()>
	endm
_mm512_undefined macro
	exitm<_mm512_setzero()>
	endm
_mm512_undefined_pd macro
	exitm<_mm512_setzero_pd()>
	endm
_mm512_undefined_ps macro
	exitm<_mm512_undefined()>
	endm

_mm512_set4_pd macro a,b,c,d
	exitm<_mm512_set_pd((a), (b), (c), (d), (a), (b), (c), (d))>
	endm


_mm512_setr_ps macro e0,e1,e2,e3,e4,e5,e6,e7,e8
	exitm<e0,e1,e2,e3,e4,e5,e6,e7,e8>
	endm
_mm512_set_16to16_ps macro e0,e1,e2,e3,e4,e5,e6,e7,e8
	exitm<e0,e1,e2,e3,e4,e5,e6,e7,e8>
	endm

_mm512_setr_pd macro e0,e1,e2,e3,e4,e5,e6,e7
	exitm<_mm512_set_pd((e7), (e6), (e5), (e4), (e3), (e2), (e1), (e0))>
	endm


_mm512_set_8to8_pd macro e0,e1,e2,e3,e4,e5,e6,e7
	exitm<_mm512_set_pd((e0), (e1), (e2), (e3), (e4), (e5), (e6), (e7))>
	endm

_mm512_setr4_ps macro a,b,c,d
	exitm<_mm512_set4_ps((d), (c), (b), (a))>
	endm

_mm512_set_4to16_ps macro a,b,c,d
	exitm<_mm512_set4_ps((d), (c), (b), (a))>
	endm

_mm512_setr4_pd macro a,b,c,d
	exitm<_mm512_set4_pd((d), (c), (b), (a))>
	endm


_mm512_set_4to8_pd macro a,b,c,d
	exitm<_mm512_set4_pd((d), (c), (b), (a))>
	endm

_mm512_set_1to16_ps macro x
	exitm<_mm512_set1_ps((x))>
	endm
_mm512_set_1to8_pd macro x
	exitm<_mm512_set1_pd((x))>
	endm

_mm512_load_ps macro x
	exitm<_mm512_maskz_load_ps(_MM_K0_REG, (x))>
	endm
_mm512_load_pd macro x
	exitm<_mm512_maskz_load_pd(_MM_K0_REG, (x))>
	endm
_mm512_loadu_ps macro x
	exitm<_mm512_maskz_loadu_ps(_MM_K0_REG, (x))>
	endm
_mm512_loadu_pd macro x
	exitm<_mm512_maskz_loadu_pd(_MM_K0_REG, (x))>
	endm

_mm512_store_ps macro x, v
	exitm<_mm512_mask_store_ps((x), _MM_K0_REG, (v))>
	endm
_mm512_store_pd macro x, v
	exitm<_mm512_mask_store_pd((x), _MM_K0_REG, (v))>
	endm

_mm512_add_ps macro v1, v2
	exitm<_mm512_maskz_add_round_ps(_MM_K0_REG, (v1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_add_round_ps macro v1, v2, e3
	exitm<_mm512_maskz_add_round_ps(_MM_K0_REG, (v1), (v2), (e3))>
	endm

_mm512_maskz_add_ps macro k1, v2, v3
	exitm<_mm512_maskz_add_round_ps((k1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_add_ps macro v1, k2, v3, v4
	exitm<_mm512_mask_add_round_ps((v1), (k2), (v3), (v4), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_add_pd macro v1, v2
	exitm<_mm512_maskz_add_round_pd(_MM_K0_REG, (v1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_add_round_pd macro v1, v2, e3
	exitm<_mm512_maskz_add_round_pd(_MM_K0_REG, (v1), (v2), (e3))>
	endm

_mm512_maskz_add_pd macro k1, v2, v3
	exitm<_mm512_maskz_add_round_pd((k1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_add_pd macro v1, k2, v3, v4
	exitm<_mm512_mask_add_round_pd((v1), (k2), (v3), (v4), _MM_FROUND_CUR_DIRECTION)>
	endm


_mm512_sub_ps macro v1, v2
	exitm<_mm512_maskz_sub_round_ps(_MM_K0_REG, (v1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_sub_round_ps macro v1, v2, e3
	exitm<>
	endm

_mm512_maskz_sub_ps macro k1, v2, v3
	exitm<_mm512_maskz_sub_round_ps((k1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_sub_ps macro v1, k2, v3, v4
	exitm<_mm512_mask_sub_round_ps((v1), (k2), (v3), (v4), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_sub_pd macro v1, v2
	exitm<_mm512_maskz_sub_round_pd(_MM_K0_REG,(v1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_sub_round_pd macro v1, v2, e3
	exitm<_mm512_maskz_sub_round_pd(_MM_K0_REG, (v1), (v2), (e3))>
	endm

_mm512_maskz_sub_pd macro k1, v2, v3
	exitm<_mm512_maskz_sub_round_pd((k1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_sub_pd macro v1, k2, v3, v4
	exitm<_mm512_mask_sub_round_pd((v1), (k2), (v3), (v4), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mul_ps macro v1, v2
	exitm<_mm512_maskz_mul_round_ps(_MM_K0_REG, (v1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mul_round_ps macro v1, v2, e3
	exitm<_mm512_maskz_mul_round_ps(_MM_K0_REG,(v1), (v2), (e3))>
	endm

_mm512_maskz_mul_ps macro k1, v2, v3
	exitm<_mm512_maskz_mul_round_ps((k1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_mul_ps macro v1, k2, v3, v4
	exitm<_mm512_mask_mul_round_ps((v1), (k2), (v3), (v4), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mul_pd macro v1, v2
	exitm<_mm512_maskz_mul_round_pd(_MM_K0_REG, (v1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mul_round_pd macro v1, v2, e3
	exitm<_mm512_maskz_mul_round_pd(_MM_K0_REG, (v1), (v2), (e3))>
	endm

_mm512_maskz_mul_pd macro k1, v2, v3
	exitm<_mm512_maskz_mul_round_pd((k1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_mul_pd macro v1, k2, v3, v4
	exitm<_mm512_mask_mul_round_pd((v1), (k2), (v3), (v4), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_div_ps macro v1, v2
	exitm<_mm512_maskz_div_round_ps(_MM_K0_REG, (v1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_div_round_ps macro v1, v2, e3
	exitm<_mm512_maskz_div_round_ps(_MM_K0_REG, (v1), (v2), (e3))>
	endm

_mm512_maskz_div_ps macro k1, v2, v3
	exitm<_mm512_maskz_div_round_ps((k1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_div_ps macro v1, k2, v3, v4
	exitm<_mm512_mask_div_round_ps((v1), (k2), (v3), (v4), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_div_pd macro v1, v2
	exitm<_mm512_maskz_div_round_pd(_MM_K0_REG, (v1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_div_round_pd macro v1, v2, e3
	exitm<_mm512_maskz_div_round_pd(_MM_K0_REG, (v1), (v2), (e3))>
	endm

_mm512_maskz_div_pd macro k1, v2, v3
	exitm<_mm512_maskz_div_round_pd((k1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_div_pd macro v1, k2, v3, v4
	exitm<_mm512_mask_div_round_pd((v1), (k2), (v3), (v4), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_fmadd_round_ps macro v1, v2, v3, e4
	exitm<_mm512_maskz_fmadd_round_ps(_MM_K0_REG, (v1), (v2), (v3), (e4))>
	endm

_mm512_fmadd_ps macro v1, v2, v3
	exitm<_mm512_fmadd_round_ps((v1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_fmadd_ps macro v1, k1, v2, v3
	exitm<_mm512_mask_fmadd_round_ps((v1), (k1), (v2), (v3),>
	endm

_mm512_maskz_fmadd_ps macro k1, v1, v2, v3
	exitm<_mm512_maskz_fmadd_round_ps((k1), (v1), (v2), (v3),>
	endm

_mm512_fmadd_round_pd macro v1, v2, v3, e4
	exitm<_mm512_maskz_fmadd_round_pd(_MM_K0_REG, (v1), (v2), (v3), (e4))>
	endm

_mm512_fmadd_pd macro v1, v2, v3
	exitm<_mm512_fmadd_round_pd((v1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_fmadd_pd macro v1, k1, v2, v3
	exitm<_mm512_mask_fmadd_round_pd((v1), (k1), (v2), (v3),>
	endm

_mm512_maskz_fmadd_pd macro k1, v1, v2, v3
	exitm<_mm512_maskz_fmadd_round_pd((k1), (v1), (v2), (v3),>
	endm

_mm512_fmsub_round_ps macro v1, v2, v3, e4
	exitm<_mm512_maskz_fmsub_round_ps(_MM_K0_REG, (v1), (v2), (v3), (e4))>
	endm

_mm512_fmsub_ps macro v1, v2, v3
	exitm<_mm512_fmsub_round_ps((v1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_fmsub_ps macro v1, k1, v2, v3
	exitm<_mm512_mask_fmsub_round_ps((v1), (k1), (v2), (v3),>
	endm

_mm512_maskz_fmsub_ps macro k1, v1, v2, v3
	exitm<_mm512_maskz_fmsub_round_ps((k1), (v1), (v2), (v3),>
	endm

_mm512_fmsub_round_pd macro v1, v2, v3, e4
	exitm<_mm512_maskz_fmsub_round_pd(_MM_K0_REG, (v1), (v2), (v3), (e4))>
	endm

_mm512_fmsub_pd macro v1, v2, v3
	exitm<_mm512_fmsub_round_pd((v1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_fmsub_pd macro v1, k1, v2, v3
	exitm<_mm512_mask_fmsub_round_pd((v1), (k1), (v2), (v3),>
	endm

_mm512_maskz_fmsub_pd macro k1, v1, v2, v3
	exitm<_mm512_maskz_fmsub_round_pd((k1), (v1), (v2), (v3),>
	endm

_mm512_fnmadd_round_ps macro v1, v2, v3, e4
	exitm<_mm512_maskz_fnmadd_round_ps(_MM_K0_REG, (v1), (v2), (v3), (e4))>
	endm

_mm512_fnmadd_ps macro v1, v2, v3
	exitm<_mm512_fnmadd_round_ps((v1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_fnmadd_ps macro v1, k1, v2, v3
	exitm<_mm512_mask_fnmadd_round_ps((v1), (k1), (v2), (v3),>
	endm

_mm512_maskz_fnmadd_ps macro k1, v1, v2, v3
	exitm<_mm512_maskz_fnmadd_round_ps((k1), (v1), (v2), (v3),>
	endm

_mm512_fnmadd_round_pd macro v1, v2, v3, e4
	exitm<_mm512_maskz_fnmadd_round_pd(_MM_K0_REG, (v1), (v2), (v3), (e4))>
	endm

_mm512_fnmadd_pd macro v1, v2, v3
	exitm<_mm512_fnmadd_round_pd((v1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_fnmadd_pd macro v1, k1, v2, v3
	exitm<_mm512_mask_fnmadd_round_pd((v1), (k1), (v2), (v3),>
	endm

_mm512_maskz_fnmadd_pd macro k1, v1, v2, v3
	exitm<_mm512_maskz_fnmadd_round_pd((k1), (v1), (v2), (v3),>
	endm


_mm512_fnmsub_round_ps macro v1, v2, v3, e4
	exitm<_mm512_maskz_fnmsub_round_ps(_MM_K0_REG, (v1), (v2), (v3), (e4))>
	endm

_mm512_fnmsub_ps macro v1, v2, v3
	exitm<_mm512_fnmsub_round_ps((v1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_fnmsub_ps macro v1, k1, v2, v3
	exitm<_mm512_mask_fnmsub_round_ps((v1), (k1), (v2), (v3),>
	endm

_mm512_maskz_fnmsub_ps macro k1, v1, v2, v3
	exitm<_mm512_maskz_fnmsub_round_ps((k1), (v1), (v2), (v3),>
	endm

_mm512_fnmsub_round_pd macro v1, v2, v3, e4
	exitm<_mm512_maskz_fnmsub_round_pd(_MM_K0_REG, (v1), (v2), (v3), (e4))>
	endm

_mm512_fnmsub_pd macro v1, v2, v3
	exitm<_mm512_fnmsub_round_pd((v1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_fnmsub_pd macro v1, k1, v2, v3
	exitm<_mm512_mask_fnmsub_round_pd((v1), (k1), (v2), (v3),>
	endm

_mm512_maskz_fnmsub_pd macro k1, v1, v2, v3
	exitm<_mm512_maskz_fnmsub_round_pd((k1), (v1), (v2), (v3),>
	endm

_mm512_sqrt_ps macro v1
	exitm<_mm512_maskz_sqrt_round_ps(_MM_K0_REG, (v1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_sqrt_round_ps macro v1, e2
	exitm<_mm512_maskz_sqrt_round_ps(_MM_K0_REG, (v1), e2)>
	endm

_mm512_mask_sqrt_ps macro v1, k2, v2
	exitm<_mm512_mask_sqrt_round_ps(v1, k2, v2, _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_sqrt_ps macro k1, v1
	exitm<_mm512_maskz_sqrt_round_ps((k1), (v1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_sqrt_pd macro v1
	exitm<_mm512_maskz_sqrt_round_pd(_MM_K0_REG, (v1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_sqrt_round_pd macro v1, e2
	exitm<_mm512_maskz_sqrt_round_pd(_MM_K0_REG, (v1), e2)>
	endm

_mm512_mask_sqrt_pd macro v1, k2, v2
	exitm<_mm512_mask_sqrt_round_pd(v1, k2, v2, _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_sqrt_pd macro k1, v1
	exitm<_mm512_maskz_sqrt_round_pd((k1), (v1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_abs_ps macro v1
	exitm<_mm512_maskz_abs_ps(_MM_K0_REG, (v1))>
	endm

_mm512_abs_pd macro v1
	exitm<_mm512_maskz_abs_pd(_MM_K0_REG, (v1))>
	endm

_mm512_max_ps macro v1, v2
	exitm<_mm512_maskz_max_round_ps(_MM_K0_REG, (v1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_max_round_ps macro v1, v2, e3
	exitm<_mm512_maskz_max_round_ps(_MM_K0_REG, (v1), (v2), e3)>
	endm

_mm512_mask_max_ps macro v1, k2, v3, v4
	exitm<_mm512_mask_max_round_ps((v1), (k2), (v3), (v4), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_max_ps macro k1, v2, v3
	exitm<_mm512_maskz_max_round_ps((k1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_max_pd macro v1, v2
	exitm<_mm512_maskz_max_round_pd(_MM_K0_REG, (v1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_max_round_pd macro v1, v2, e3
	exitm<_mm512_maskz_max_round_pd(_MM_K0_REG, (v1), (v2), e3)>
	endm

_mm512_mask_max_pd macro v1, k2, v3, v4
	exitm<_mm512_mask_max_round_pd((v1), (k2), (v3), (v4), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_max_pd macro k1, v2, v3
	exitm<_mm512_maskz_max_round_pd((k1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_min_ps macro v1, v2
	exitm<_mm512_maskz_min_round_ps(_MM_K0_REG, (v1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_min_round_ps macro v1, v2, e3
	exitm<_mm512_maskz_min_round_ps(_MM_K0_REG, (v1), (v2), e3)>
	endm

_mm512_mask_min_ps macro v1, k2, v3, v4
	exitm<_mm512_mask_min_round_ps((v1), (k2), (v3), (v4), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_min_ps macro k1, v2, v3
	exitm<_mm512_maskz_min_round_ps((k1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_min_pd macro v1, v2
	exitm<_mm512_maskz_min_round_pd(_MM_K0_REG, (v1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_min_round_pd macro v1, v2, e3
	exitm<_mm512_maskz_min_round_pd(_MM_K0_REG, (v1), (v2), e3)>
	endm

_mm512_mask_min_pd macro v1, k2, v3, v4
	exitm<_mm512_mask_min_round_pd((v1), (k2), (v3), (v4), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_min_pd macro k1, v2, v3
	exitm<_mm512_maskz_min_round_pd((k1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_rcp14_ps macro v1
	exitm<_mm512_maskz_rcp14_ps(_MM_K0_REG, v1)>
	endm

_mm512_rcp14_pd macro v1
	exitm<_mm512_maskz_rcp14_pd(_MM_K0_REG, v1)>
	endm

_mm512_rsqrt14_ps macro v1
	exitm<_mm512_maskz_rsqrt14_ps(_MM_K0_REG, v1)>
	endm

_mm512_rsqrt14_pd macro v1
	exitm<_mm512_maskz_rsqrt14_pd(_MM_K0_REG, v1)>
	endm

_mm512_cvt_roundps_pd macro v1, e2
	exitm<_mm512_maskz_cvt_roundps_pd(_MM_K0_REG, (v1), e2)>
	endm

_mm512_cvtps_pd macro v1
	exitm<_mm512_cvt_roundps_pd((v1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_cvtps_pd macro k1, v2
	exitm<_mm512_maskz_cvt_roundps_pd((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvtps_pd macro v1, k2, v3
	exitm<_mm512_mask_cvt_roundps_pd((v1), (k2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvt_roundpd_ps macro v1, e2
	exitm<_mm512_maskz_cvt_roundpd_ps(_MM_K0_REG, (v1), e2)>
	endm

_mm512_cvtpd_ps macro v1
	exitm<_mm512_cvt_roundpd_ps((v1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_cvtpd_ps macro k1, v2
	exitm<_mm512_maskz_cvt_roundpd_ps((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvtpd_ps macro v1_old, k1, v2
	exitm<_mm512_mask_cvt_roundpd_ps((v1_old), (k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cmp_ps_mask macro v1, v2, i3
	exitm<_mm512_mask_cmp_round_ps_mask(_MM_K0_REG, v1, v2, i3, _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cmp_round_ps_mask macro v1, v2, i3, e4
	exitm<_mm512_mask_cmp_round_ps_mask(_MM_K0_REG, v1, v2, i3, e4)>
	endm

_mm512_mask_cmp_ps_mask macro k1, v2, v3, i4
	exitm<_mm512_mask_cmp_round_ps_mask(k1, v2, v3, i4, _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cmp_pd_mask macro v1, v2, i3
	exitm<_mm512_mask_cmp_round_pd_mask(_MM_K0_REG, v1, v2, i3, _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cmp_round_pd_mask macro v1, v2, i3, e4
	exitm<_mm512_mask_cmp_round_pd_mask(_MM_K0_REG, v1, v2, i3, e4)>
	endm

_mm512_mask_cmp_pd_mask macro k1, v2, v3, i4
	exitm<_mm512_mask_cmp_round_pd_mask(k1, v2, v3, i4, _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cmpeq_ps_mask macro v1, v2
	exitm<_mm512_cmp_ps_mask((v1), (v2), _CMP_EQ_OQ)>
	endm
_mm512_mask_cmpeq_ps_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_ps_mask((k1), (v1), (v2), _CMP_EQ_OQ)>
	endm

_mm512_cmplt_ps_mask macro v1, v2
	exitm<_mm512_cmp_ps_mask((v1), (v2), _CMP_LT_OS)>
	endm
_mm512_mask_cmplt_ps_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_ps_mask((k1), (v1), (v2), _CMP_LT_OS)>
	endm

_mm512_cmple_ps_mask macro v1, v2
	exitm<_mm512_cmp_ps_mask((v1), (v2), _CMP_LE_OS)>
	endm
_mm512_mask_cmple_ps_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_ps_mask((k1), (v1), (v2), _CMP_LE_OS)>
	endm

_mm512_cmpunord_ps_mask macro v1, v2
	exitm<_mm512_cmp_ps_mask((v1), (v2), _CMP_UNORD_Q)>
	endm

_mm512_mask_cmpunord_ps_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_ps_mask((k1), (v1), (v2), _CMP_UNORD_Q)>
	endm

_mm512_cmpneq_ps_mask macro v1, v2
	exitm<_mm512_cmp_ps_mask((v1), (v2), _CMP_NEQ_UQ)>
	endm

_mm512_mask_cmpneq_ps_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_ps_mask((k1), (v1), (v2), _CMP_NEQ_UQ)>
	endm

_mm512_cmpnlt_ps_mask macro v1, v2
	exitm<_mm512_cmp_ps_mask((v1), (v2), _CMP_NLT_US)>
	endm

_mm512_mask_cmpnlt_ps_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_ps_mask((k1), (v1), (v2), _CMP_NLT_US)>
	endm

_mm512_cmpnle_ps_mask macro v1, v2
	exitm<_mm512_cmp_ps_mask((v1), (v2), _CMP_NLE_US)>
	endm

_mm512_mask_cmpnle_ps_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_ps_mask((k1), (v1), (v2), _CMP_NLE_US)>
	endm

_mm512_cmpord_ps_mask macro v1, v2
	exitm<_mm512_cmp_ps_mask((v1), (v2), _CMP_ORD_Q)>
	endm

_mm512_mask_cmpord_ps_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_ps_mask((k1), (v1), (v2), _CMP_ORD_Q)>
	endm

_mm512_cmpeq_pd_mask macro v1, v2
	exitm<_mm512_cmp_pd_mask((v1), (v2), _CMP_EQ_OQ)>
	endm
_mm512_mask_cmpeq_pd_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_pd_mask((k1), (v1), (v2), _CMP_EQ_OQ)>
	endm

_mm512_cmplt_pd_mask macro v1, v2
	exitm<_mm512_cmp_pd_mask((v1), (v2), _CMP_LT_OS)>
	endm
_mm512_mask_cmplt_pd_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_pd_mask((k1), (v1), (v2), _CMP_LT_OS)>
	endm

_mm512_cmple_pd_mask macro v1, v2
	exitm<_mm512_cmp_pd_mask((v1), (v2), _CMP_LE_OS)>
	endm
_mm512_mask_cmple_pd_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_pd_mask((k1), (v1), (v2), _CMP_LE_OS)>
	endm

_mm512_cmpunord_pd_mask macro v1, v2
	exitm<_mm512_cmp_pd_mask((v1), (v2), _CMP_UNORD_Q)>
	endm

_mm512_mask_cmpunord_pd_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_pd_mask((k1), (v1), (v2), _CMP_UNORD_Q)>
	endm

_mm512_cmpneq_pd_mask macro v1, v2
	exitm<_mm512_cmp_pd_mask((v1), (v2), _CMP_NEQ_UQ)>
	endm

_mm512_mask_cmpneq_pd_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_pd_mask((k1), (v1), (v2), _CMP_NEQ_UQ)>
	endm

_mm512_cmpnlt_pd_mask macro v1, v2
	exitm<_mm512_cmp_pd_mask((v1), (v2), _CMP_NLT_US)>
	endm

_mm512_mask_cmpnlt_pd_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_pd_mask((k1), (v1), (v2), _CMP_NLT_US)>
	endm

_mm512_cmpnle_pd_mask macro v1, v2
	exitm<_mm512_cmp_pd_mask((v1), (v2), _CMP_NLE_US)>
	endm

_mm512_mask_cmpnle_pd_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_pd_mask((k1), (v1), (v2), _CMP_NLE_US)>
	endm

_mm512_cmpord_pd_mask macro v1, v2
	exitm<_mm512_cmp_pd_mask((v1), (v2), _CMP_ORD_Q)>
	endm

_mm512_mask_cmpord_pd_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_pd_mask((k1), (v1), (v2), _CMP_ORD_Q)>
	endm


_mm512_broadcast_f32x2 macro v1
	exitm<_mm512_maskz_broadcast_f32x2(_MM_K0_REG, (v1))>
	endm

_mm512_broadcast_f32x4 macro v1
	exitm<_mm512_maskz_broadcast_f32x4(_MM_K0_REG, (v1))>
	endm

_mm512_broadcast_f32x8 macro v1
	exitm<_mm512_maskz_broadcast_f32x8(_MM_K0_REG, (v1))>
	endm

_mm512_broadcast_f64x2 macro v1
	exitm<_mm512_maskz_broadcast_f64x2(_MM_K0_REG, (v1))>
	endm

_mm512_broadcast_f64x4 macro v1
	exitm<_mm512_maskz_broadcast_f64x4(_MM_K0_REG, (v1))>
	endm

_mm512_broadcastsd_pd macro v1
	exitm<_mm512_maskz_broadcastsd_pd(_MM_K0_REG, (v1))>
	endm

_mm512_broadcastss_ps macro v1
	exitm<_mm512_maskz_broadcastss_ps(_MM_K0_REG, (v1))>
	endm

_mm512_extractf32x4_ps macro v1, e2
	exitm<_mm512_maskz_extractf32x4_ps(_MM_K0_REG, (v1), (e2))>
	endm

_mm512_extractf32x8_ps macro v1, e2
	exitm<_mm512_maskz_extractf32x8_ps(_MM_K0_REG, (v1), (e2))>
	endm

_mm512_extractf64x2_pd macro v1, e2
	exitm<_mm512_maskz_extractf64x2_pd(_MM_K0_REG, (v1), (e2))>
	endm

_mm512_extractf64x4_pd macro v1, e2
	exitm<_mm512_maskz_extractf64x4_pd(_MM_K0_REG, (v1), (e2))>
	endm


_mm512_insertf32x4 macro v1, v2, e3
	exitm<_mm512_maskz_insertf32x4(_MM_K0_REG, (v1), (v2), (e3))>
	endm

_mm512_insertf32x8 macro v1, v2, e3
	exitm<_mm512_maskz_insertf32x8(_MM_K0_REG, (v1), (v2), (e3))>
	endm

_mm512_insertf64x2 macro v1, v2, e3
	exitm<_mm512_maskz_insertf64x2(_MM_K0_REG, (v1), (v2), (e3))>
	endm

_mm512_insertf64x4 macro v1, v2, e3
	exitm<_mm512_maskz_insertf64x4(_MM_K0_REG, (v1), (v2), (e3))>
	endm


_mm512_shuffle_f32x4 macro v1, v2, e3
	exitm<_mm512_maskz_shuffle_f32x4(_MM_K0_REG, (v1), (v2), (e3))>
	endm

_mm512_shuffle_f64x2 macro v1, v2, e3
	exitm<_mm512_maskz_shuffle_f64x2(_MM_K0_REG, (v1), (v2), (e3))>
	endm

_mm512_shuffle_pd macro v1, v2, e3
	exitm<_mm512_maskz_shuffle_pd(_MM_K0_REG, (v1), (v2), (e3))>
	endm

_mm512_shuffle_ps macro v1, v2, e3
	exitm<_mm512_maskz_shuffle_ps(_MM_K0_REG, (v1), (v2), (e3))>
	endm


_mm512_kand macro k1, k2
	exitm<(((k1) and (k2)))>
	endm

_mm512_kandn macro k1, k2
	exitm<((not (k1) and (k2)))>
	endm

_mm512_kor macro k1, k2
	exitm<(((k1) or (k2)))>
	endm

_mm512_kxor macro k1, k2
	exitm<(((k1) xor (k2)))>
	endm

_mm512_kxnor macro k1, k2
	exitm<((not ((k1) xor (k2))))>
	endm

_mm512_knot macro k1
	exitm<not k1>
	endm


_mm512_setzero_si512	proto
_mm512_set_epi8		proto :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte,
			      :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte,
			      :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte,
			      :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte,
			      :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte,
			      :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte,
			      :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte,
			      :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte
_mm512_set_epi16	proto :sword, :sword, :sword, :sword, :sword, :sword, :sword, :sword,
			      :sword, :sword, :sword, :sword, :sword, :sword, :sword, :sword,
			      :sword, :sword, :sword, :sword, :sword, :sword, :sword, :sword,
			      :sword, :sword, :sword, :sword, :sword, :sword, :sword, :sword
_mm512_set_epi32	proto :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword,
			      :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword
_mm512_set_epi64	proto :qword, :qword, :qword, :qword, :qword, :qword, :qword, :qword

_mm512_mask_set1_epi8	proto :zword, :qword, :sbyte
_mm512_maskz_set1_epi8	proto :qword, :sbyte
_mm512_mask_set1_epi16	proto :zword, :dword, :sword
_mm512_maskz_set1_epi16 proto :dword, :sword
_mm512_mask_set1_epi32	proto :zword, :word, :sdword
_mm512_maskz_set1_epi32 proto :word, :sdword
_mm512_mask_set1_epi64	proto :zword, :byte, :qword
_mm512_maskz_set1_epi64 proto :byte, :qword

_mm512_mask_add_epi8	proto :zword, :qword, :zword, :zword
_mm512_maskz_add_epi8	proto :qword, :zword, :zword
_mm512_mask_add_epi16	proto :zword, :dword, :zword, :zword
_mm512_maskz_add_epi16	proto :dword, :zword, :zword
_mm512_mask_add_epi32	proto :zword, :word, :zword, :zword
_mm512_maskz_add_epi32	proto :word, :zword, :zword
_mm512_mask_add_epi64	proto :zword, :byte, :zword, :zword
_mm512_maskz_add_epi64	proto :byte, :zword, :zword
_mm512_mask_adds_epi8	proto :zword, :qword, :zword, :zword
_mm512_maskz_adds_epi8	proto :qword, :zword, :zword
_mm512_mask_adds_epi16	proto :zword, :dword, :zword, :zword
_mm512_maskz_adds_epi16 proto :dword, :zword, :zword
_mm512_mask_adds_epu8	proto :zword, :qword, :zword, :zword
_mm512_maskz_adds_epu8	proto :qword, :zword, :zword
_mm512_mask_adds_epu16	proto :zword, :dword, :zword, :zword
_mm512_maskz_adds_epu16 proto :dword, :zword, :zword

_mm512_mask_abs_epi8	proto :zword, :qword, :zword
_mm512_maskz_abs_epi8	proto :qword, :zword
_mm512_mask_abs_epi16	proto :zword, :dword, :zword
_mm512_maskz_abs_epi16	proto :dword, :zword
_mm512_mask_abs_epi32	proto :zword, :word, :zword
_mm512_maskz_abs_epi32	proto :word, :zword
_mm512_mask_abs_epi64	proto :zword, :byte, :zword
_mm512_maskz_abs_epi64	proto :byte, :zword

_mm512_mask_broadcast_i32x2	proto :zword, :word, :oword
_mm512_maskz_broadcast_i32x2	proto :word, :oword
_mm512_mask_broadcast_i32x4	proto :zword, :word, :oword
_mm512_maskz_broadcast_i32x4	proto :word, :oword
_mm512_mask_broadcast_i32x8	proto :zword, :word, :yword
_mm512_maskz_broadcast_i32x8	proto :word, :yword
_mm512_mask_broadcast_i64x2	proto :zword, :byte, :oword
_mm512_maskz_broadcast_i64x2	proto :byte, :oword
_mm512_mask_broadcast_i64x4	proto :zword, :byte, :yword
_mm512_maskz_broadcast_i64x4	proto :byte, :yword
_mm512_mask_broadcastb_epi8	proto :zword, :qword, :oword
_mm512_maskz_broadcastb_epi8	proto :qword, :oword
_mm512_mask_broadcastw_epi16	proto :zword, :dword, :oword
_mm512_maskz_broadcastw_epi16	proto :dword, :oword
_mm512_mask_broadcastd_epi32	proto :zword, :word, :oword
_mm512_maskz_broadcastd_epi32	proto :word, :oword
_mm512_mask_broadcastq_epi64	proto :zword, :byte, :oword
_mm512_maskz_broadcastq_epi64	proto :byte, :oword
_mm512_broadcastmw_epi32	proto :word
_mm512_broadcastmb_epi64	proto :byte

_mm512_mask_sub_epi8	proto :zword, :qword, :zword, :zword
_mm512_maskz_sub_epi8	proto :qword, :zword, :zword
_mm512_mask_sub_epi16	proto :zword, :dword, :zword, :zword
_mm512_maskz_sub_epi16	proto :dword, :zword, :zword
_mm512_mask_sub_epi32	proto :zword, :word, :zword, :zword
_mm512_maskz_sub_epi32	proto :word, :zword, :zword
_mm512_mask_sub_epi64	proto :zword, :byte, :zword, :zword
_mm512_maskz_sub_epi64	proto :byte, :zword, :zword
_mm512_mask_subs_epi8	proto :zword, :qword, :zword, :zword
_mm512_maskz_subs_epi8	proto :qword, :zword, :zword
_mm512_mask_subs_epi16	proto :zword, :dword, :zword, :zword
_mm512_maskz_subs_epi16 proto :dword, :zword, :zword
_mm512_mask_subs_epu8	proto :zword, :qword, :zword, :zword
_mm512_maskz_subs_epu8	proto :qword, :zword, :zword
_mm512_mask_subs_epu16	proto :zword, :dword, :zword, :zword
_mm512_maskz_subs_epu16 proto :dword, :zword, :zword

_mm512_mask_max_epi8	proto :zword, :qword, :zword, :zword
_mm512_maskz_max_epi8	proto :qword, :zword, :zword
_mm512_mask_max_epi16	proto :zword, :dword, :zword, :zword
_mm512_maskz_max_epi16	proto :dword, :zword, :zword
_mm512_mask_max_epi32	proto :zword, :word, :zword, :zword
_mm512_maskz_max_epi32	proto :word, :zword, :zword
_mm512_mask_max_epi64	proto :zword, :byte, :zword, :zword
_mm512_maskz_max_epi64	proto :byte, :zword, :zword
_mm512_mask_max_epu8	proto :zword, :qword, :zword, :zword
_mm512_maskz_max_epu8	proto :qword, :zword, :zword
_mm512_mask_max_epu16	proto :zword, :dword, :zword, :zword
_mm512_maskz_max_epu16	proto :dword, :zword, :zword
_mm512_mask_max_epu32	proto :zword, :word, :zword, :zword
_mm512_maskz_max_epu32	proto :word, :zword, :zword
_mm512_mask_max_epu64	proto :zword, :byte, :zword, :zword
_mm512_maskz_max_epu64	proto :byte, :zword, :zword

_mm512_mask_min_epi8	proto :zword, :qword, :zword, :zword
_mm512_maskz_min_epi8	proto :qword, :zword, :zword
_mm512_mask_min_epi16	proto :zword, :dword, :zword, :zword
_mm512_maskz_min_epi16	proto :dword, :zword, :zword
_mm512_mask_min_epi32	proto :zword, :word, :zword, :zword
_mm512_maskz_min_epi32	proto :word, :zword, :zword
_mm512_mask_min_epi64	proto :zword, :byte, :zword, :zword
_mm512_maskz_min_epi64	proto :byte, :zword, :zword
_mm512_mask_min_epu8	proto :zword, :qword, :zword, :zword
_mm512_maskz_min_epu8	proto :qword, :zword, :zword
_mm512_mask_min_epu16	proto :zword, :dword, :zword, :zword
_mm512_maskz_min_epu16	proto :dword, :zword, :zword
_mm512_mask_min_epu32	proto :zword, :word, :zword, :zword
_mm512_maskz_min_epu32	proto :word, :zword, :zword
_mm512_mask_min_epu64	proto :zword, :byte, :zword, :zword
_mm512_maskz_min_epu64	proto :byte, :zword, :zword

_mm512_mask_mul_epi32		proto :zword, :byte, :zword, :zword
_mm512_maskz_mul_epi32		proto :byte, :zword, :zword
_mm512_mask_mul_epu32		proto :zword, :byte, :zword, :zword
_mm512_maskz_mul_epu32		proto :byte, :zword, :zword
_mm512_mask_mulhi_epi16		proto :zword, :dword, :zword, :zword
_mm512_maskz_mulhi_epi16	proto :dword, :zword, :zword
_mm512_mask_mulhi_epu16		proto :zword, :dword, :zword, :zword
_mm512_maskz_mulhi_epu16	proto :dword, :zword, :zword
_mm512_mask_mullo_epi16		proto :zword, :dword, :zword, :zword
_mm512_maskz_mullo_epi16	proto :dword, :zword, :zword
_mm512_mask_mullo_epi32		proto :zword, :word, :zword, :zword
_mm512_maskz_mullo_epi32	proto :word, :zword, :zword
_mm512_mask_mullo_epi64		proto :zword, :byte, :zword, :zword
_mm512_maskz_mullo_epi64	proto :byte, :zword, :zword
_mm512_mullox_epi64		proto :zword, :zword
_mm512_mask_mullox_epi64	proto :zword, :byte, :zword, :zword
_mm512_mask_mulhrs_epi16	proto :zword, :dword, :zword, :zword
_mm512_maskz_mulhrs_epi16	proto :dword, :zword, :zword

_mm512_mask_load_epi32		proto :zword, :word, :ptr
_mm512_maskz_load_epi32		proto :word, :ptr
_mm512_mask_load_epi64		proto :zword, :byte, :ptr
_mm512_maskz_load_epi64		proto :byte, :ptr
_mm512_mask_loadu_epi8		proto :zword, :qword, :ptr
_mm512_maskz_loadu_epi8		proto :qword, :ptr
_mm512_mask_loadu_epi16		proto :zword, :dword, :ptr
_mm512_maskz_loadu_epi16	proto :dword, :ptr
_mm512_mask_loadu_epi32		proto :zword, :word, :ptr
_mm512_maskz_loadu_epi32	proto :word, :ptr
_mm512_mask_loadu_epi64		proto :zword, :byte, :ptr
_mm512_maskz_loadu_epi64	proto :byte, :ptr

_mm512_mask_store_epi32		proto :ptr, :word, :zword
_mm512_mask_store_epi64		proto :ptr, :byte, :zword
_mm512_mask_storeu_epi8		proto :ptr, :qword, :zword
_mm512_mask_storeu_epi16	proto :ptr, :dword, :zword
_mm512_mask_storeu_epi32	proto :ptr, :word, :zword
_mm512_mask_storeu_epi64	proto :ptr, :byte, :zword

_mm512_mask_extracti32x4_epi32	proto :oword, :byte, :zword, :sdword
_mm512_maskz_extracti32x4_epi32 proto :byte, :zword, :sdword
_mm512_mask_extracti32x8_epi32	proto :yword, :byte, :zword, :sdword
_mm512_maskz_extracti32x8_epi32 proto :byte, :zword, :sdword
_mm512_mask_extracti64x2_epi64	proto :oword, :byte, :zword, :sdword
_mm512_maskz_extracti64x2_epi64 proto :byte, :zword, :sdword
_mm512_mask_extracti64x4_epi64	proto :yword, :byte, :zword, :sdword
_mm512_maskz_extracti64x4_epi64 proto :byte, :zword, :sdword

_mm512_mask_inserti32x4		proto :zword, :word, :zword, :oword, :sdword
_mm512_maskz_inserti32x4	proto :word, :zword, :oword, :sdword
_mm512_mask_inserti32x8		proto :zword, :word, :zword, :yword, :sdword
_mm512_maskz_inserti32x8	proto :word, :zword, :yword, :sdword
_mm512_mask_inserti64x2		proto :zword, :byte, :zword, :oword, :sdword
_mm512_maskz_inserti64x2	proto :byte, :zword, :oword, :sdword
_mm512_mask_inserti64x4		proto :zword, :byte, :zword, :yword, :sdword
_mm512_maskz_inserti64x4	proto :byte, :zword, :yword, :sdword

_mm512_mask_shuffle_epi8	proto :zword, :qword, :zword, :zword
_mm512_maskz_shuffle_epi8	proto :qword, :zword, :zword
_mm512_mask_shuffle_epi32	proto :zword, :word, :zword, :sdword
_mm512_maskz_shuffle_epi32	proto :word, :zword, :sdword
_mm512_mask_shuffle_i32x4	proto :zword, :word, :zword, :zword, :sdword
_mm512_maskz_shuffle_i32x4	proto :word, :zword, :zword, :sdword
_mm512_mask_shuffle_i64x2	proto :zword, :byte, :zword, :zword, :sdword
_mm512_maskz_shuffle_i64x2	proto :byte, :zword, :zword, :sdword
_mm512_mask_shufflehi_epi16	proto :zword, :dword, :zword, :sdword
_mm512_maskz_shufflehi_epi16	proto :dword, :zword, :sdword
_mm512_mask_shufflelo_epi16	proto :zword, :dword, :zword, :sdword
_mm512_maskz_shufflelo_epi16	proto :dword, :zword, :sdword

_mm512_mask_mov_ps	proto :zword, :word, :zword
_mm512_maskz_mov_ps	proto :word, :zword
_mm512_mask_mov_pd	proto :zword, :byte, :zword
_mm512_maskz_mov_pd	proto :byte, :zword
_mm512_mask_mov_epi8	proto :zword, :qword, :zword
_mm512_maskz_mov_epi8	proto :qword, :zword
_mm512_mask_mov_epi16	proto :zword, :dword, :zword
_mm512_maskz_mov_epi16	proto :dword, :zword
_mm512_mask_mov_epi32	proto :zword, :word, :zword
_mm512_maskz_mov_epi32	proto :word, :zword
_mm512_mask_mov_epi64	proto :zword, :byte, :zword
_mm512_maskz_mov_epi64	proto :byte, :zword
_mm512_mask_movedup_pd	proto :zword, :byte, :zword
_mm512_maskz_movedup_pd proto :byte, :zword
_mm512_mask_movehdup_ps proto :zword, :word, :zword
_mm512_maskz_movehdup_ps	proto :word, :zword
_mm512_mask_moveldup_ps		proto :zword, :word, :zword
_mm512_maskz_moveldup_ps	proto :word, :zword

_mm512_movm_epi8	proto :qword
_mm512_movm_epi16	proto :dword
_mm512_movm_epi32	proto :word
_mm512_movm_epi64	proto :byte
_mm512_movepi8_mask	proto :zword
_mm512_movepi16_mask	proto :zword
_mm512_movepi32_mask	proto :zword
_mm512_movepi64_mask	proto :zword

_mm512_mask_alignr_epi8		proto :zword, :qword, :zword, :zword, :sdword
_mm512_maskz_alignr_epi8	proto :qword, :zword, :zword, :sdword
_mm512_mask_alignr_epi32	proto :zword, :word, :zword, :zword, :sdword
_mm512_maskz_alignr_epi32	proto :word, :zword, :zword, :sdword
_mm512_mask_alignr_epi64	proto :zword, :byte, :zword, :zword, :sdword
_mm512_maskz_alignr_epi64	proto :byte, :zword, :zword, :sdword

_mm512_mask_and_pd	proto :zword, :byte, :zword, :zword
_mm512_maskz_and_pd	proto :byte, :zword, :zword
_mm512_mask_and_ps	proto :zword, :word, :zword, :zword
_mm512_maskz_and_ps	proto :word, :zword, :zword
_mm512_mask_and_epi32	proto :zword, :word, :zword, :zword
_mm512_maskz_and_epi32	proto :word, :zword, :zword
_mm512_mask_and_epi64	proto :zword, :byte, :zword, :zword
_mm512_maskz_and_epi64	proto :byte, :zword, :zword

_mm512_mask_andnot_pd		proto :zword, :byte, :zword, :zword
_mm512_maskz_andnot_pd		proto :byte, :zword, :zword
_mm512_mask_andnot_ps		proto :zword, :word, :zword, :zword
_mm512_maskz_andnot_ps		proto :word, :zword, :zword
_mm512_mask_andnot_epi32	proto :zword, :word, :zword, :zword
_mm512_maskz_andnot_epi32	proto :word, :zword, :zword
_mm512_mask_andnot_epi64	proto :zword, :byte, :zword, :zword
_mm512_maskz_andnot_epi64	proto :byte, :zword, :zword

_mm512_mask_or_pd	proto :zword, :byte, :zword, :zword
_mm512_maskz_or_pd	proto :byte, :zword, :zword
_mm512_mask_or_ps	proto :zword, :word, :zword, :zword
_mm512_maskz_or_ps	proto :word, :zword, :zword
_mm512_mask_or_epi32	proto :zword, :word, :zword, :zword
_mm512_maskz_or_epi32	proto :word, :zword, :zword
_mm512_mask_or_epi64	proto :zword, :byte, :zword, :zword
_mm512_maskz_or_epi64	proto :byte, :zword, :zword

_mm512_mask_xor_pd	proto :zword, :byte, :zword, :zword
_mm512_maskz_xor_pd	proto :byte, :zword, :zword
_mm512_mask_xor_ps	proto :zword, :word, :zword, :zword
_mm512_maskz_xor_ps	proto :word, :zword, :zword
_mm512_mask_xor_epi32	proto :zword, :word, :zword, :zword
_mm512_maskz_xor_epi32	proto :word, :zword, :zword
_mm512_mask_xor_epi64	proto :zword, :byte, :zword, :zword
_mm512_maskz_xor_epi64	proto :byte, :zword, :zword

_mm512_mask_blend_ps	proto :word, :zword, :zword
_mm512_mask_blend_pd	proto :byte, :zword, :zword
_mm512_mask_blend_epi8	proto :qword, :zword, :zword
_mm512_mask_blend_epi16 proto :dword, :zword, :zword
_mm512_mask_blend_epi32 proto :word, :zword, :zword
_mm512_mask_blend_epi64 proto :byte, :zword, :zword

_mm512_mask_sll_epi16	proto :zword, :dword, :zword, :oword
_mm512_maskz_sll_epi16	proto :dword, :zword, :oword
_mm512_mask_sll_epi32	proto :zword, :word, :zword, :oword
_mm512_maskz_sll_epi32	proto :word, :zword, :oword
_mm512_mask_sll_epi64	proto :zword, :byte, :zword, :oword
_mm512_maskz_sll_epi64	proto :byte, :zword, :oword
_mm512_mask_slli_epi16	proto :zword, :dword, :zword, :sdword
_mm512_maskz_slli_epi16 proto :dword, :zword, :sdword
_mm512_mask_slli_epi32	proto :zword, :word, :zword, :sdword
_mm512_maskz_slli_epi32 proto :word, :zword, :sdword
_mm512_mask_slli_epi64	proto :zword, :byte, :zword, :sdword
_mm512_maskz_slli_epi64 proto :byte, :zword, :sdword
_mm512_mask_sllv_epi16	proto :zword, :dword, :zword, :zword
_mm512_maskz_sllv_epi16 proto :dword, :zword, :zword
_mm512_mask_sllv_epi32	proto :zword, :word, :zword, :zword
_mm512_maskz_sllv_epi32 proto :word, :zword, :zword
_mm512_mask_sllv_epi64	proto :zword, :byte, :zword, :zword
_mm512_maskz_sllv_epi64 proto :byte, :zword, :zword

_mm512_mask_srl_epi16	proto :zword, :dword, :zword, :oword
_mm512_maskz_srl_epi16	proto :dword, :zword, :oword
_mm512_mask_srl_epi32	proto :zword, :word, :zword, :oword
_mm512_maskz_srl_epi32	proto :word, :zword, :oword
_mm512_mask_srl_epi64	proto :zword, :byte, :zword, :oword
_mm512_maskz_srl_epi64	proto :byte, :zword, :oword
_mm512_mask_srli_epi16	proto :zword, :dword, :zword, :sdword
_mm512_maskz_srli_epi16 proto :dword, :zword, :sdword
_mm512_mask_srli_epi32	proto :zword, :word, :zword, :sdword
_mm512_maskz_srli_epi32 proto :word, :zword, :sdword
_mm512_mask_srli_epi64	proto :zword, :byte, :zword, :sdword
_mm512_maskz_srli_epi64 proto :byte, :zword, :sdword
_mm512_mask_srlv_epi16	proto :zword, :dword, :zword, :zword
_mm512_maskz_srlv_epi16 proto :dword, :zword, :zword
_mm512_mask_srlv_epi32	proto :zword, :word, :zword, :zword
_mm512_maskz_srlv_epi32 proto :word, :zword, :zword
_mm512_mask_srlv_epi64	proto :zword, :byte, :zword, :zword
_mm512_maskz_srlv_epi64 proto :byte, :zword, :zword

_mm512_mask_sra_epi16	proto :zword, :dword, :zword, :oword
_mm512_maskz_sra_epi16	proto :dword, :zword, :oword
_mm512_mask_sra_epi32	proto :zword, :word, :zword, :oword
_mm512_maskz_sra_epi32	proto :word, :zword, :oword
_mm512_mask_sra_epi64	proto :zword, :byte, :zword, :oword
_mm512_maskz_sra_epi64	proto :byte, :zword, :oword
_mm512_mask_srai_epi16	proto :zword, :dword, :zword, :sdword
_mm512_maskz_srai_epi16 proto :dword, :zword, :sdword
_mm512_mask_srai_epi32	proto :zword, :word, :zword, :sdword
_mm512_maskz_srai_epi32 proto :word, :zword, :sdword
_mm512_mask_srai_epi64	proto :zword, :byte, :zword, :sdword
_mm512_maskz_srai_epi64 proto :byte, :zword, :sdword
_mm512_mask_srav_epi16	proto :zword, :dword, :zword, :zword
_mm512_maskz_srav_epi16 proto :dword, :zword, :zword
_mm512_mask_srav_epi32	proto :zword, :word, :zword, :zword
_mm512_maskz_srav_epi32 proto :word, :zword, :zword
_mm512_mask_srav_epi64	proto :zword, :byte, :zword, :zword
_mm512_maskz_srav_epi64 proto :byte, :zword, :zword

_mm512_bslli_epi128	proto :zword, :sdword
_mm512_bsrli_epi128	proto :zword, :sdword

_mm512_mask_rol_epi32	proto :zword, :word, :zword, :sdword
_mm512_maskz_rol_epi32	proto :word, :zword, :sdword
_mm512_mask_rol_epi64	proto :zword, :byte, :zword, :sdword
_mm512_maskz_rol_epi64	proto :byte, :zword, :sdword
_mm512_mask_rolv_epi32	proto :zword, :word, :zword, :zword
_mm512_maskz_rolv_epi32 proto :word, :zword, :zword
_mm512_mask_rolv_epi64	proto :zword, :byte, :zword, :zword
_mm512_maskz_rolv_epi64 proto :byte, :zword, :zword

_mm512_mask_ror_epi32	proto :zword, :word, :zword, :sdword
_mm512_maskz_ror_epi32	proto :word, :zword, :sdword
_mm512_mask_ror_epi64	proto :zword, :byte, :zword, :sdword
_mm512_maskz_ror_epi64	proto :byte, :zword, :sdword
_mm512_mask_rorv_epi32	proto :zword, :word, :zword, :zword
_mm512_maskz_rorv_epi32 proto :word, :zword, :zword
_mm512_mask_rorv_epi64	proto :zword, :byte, :zword, :zword
_mm512_maskz_rorv_epi64 proto :byte, :zword, :zword

_mm512_mask_unpackhi_pd		proto :zword, :byte, :zword, :zword
_mm512_maskz_unpackhi_pd	proto :byte, :zword, :zword
_mm512_mask_unpackhi_ps		proto :zword, :word, :zword, :zword
_mm512_maskz_unpackhi_ps	proto :word, :zword, :zword
_mm512_mask_unpacklo_pd		proto :zword, :byte, :zword, :zword
_mm512_maskz_unpacklo_pd	proto :byte, :zword, :zword
_mm512_mask_unpacklo_ps		proto :zword, :word, :zword, :zword
_mm512_maskz_unpacklo_ps	proto :word, :zword, :zword
_mm512_mask_unpackhi_epi8	proto :zword, :qword, :zword, :zword
_mm512_maskz_unpackhi_epi8	proto :qword, :zword, :zword
_mm512_mask_unpackhi_epi16	proto :zword, :dword, :zword, :zword
_mm512_maskz_unpackhi_epi16	proto :dword, :zword, :zword
_mm512_mask_unpackhi_epi32	proto :zword, :word, :zword, :zword
_mm512_maskz_unpackhi_epi32	proto :word, :zword, :zword
_mm512_mask_unpackhi_epi64	proto :zword, :byte, :zword, :zword
_mm512_maskz_unpackhi_epi64	proto :byte, :zword, :zword
_mm512_mask_unpacklo_epi8	proto :zword, :qword, :zword, :zword
_mm512_maskz_unpacklo_epi8	proto :qword, :zword, :zword
_mm512_mask_unpacklo_epi16	proto :zword, :dword, :zword, :zword
_mm512_maskz_unpacklo_epi16	proto :dword, :zword, :zword
_mm512_mask_unpacklo_epi32	proto :zword, :word, :zword, :zword
_mm512_maskz_unpacklo_epi32	proto :word, :zword, :zword
_mm512_mask_unpacklo_epi64	proto :zword, :byte, :zword, :zword
_mm512_maskz_unpacklo_epi64	proto :byte, :zword, :zword

_mm512_mask_getexp_round_ps	proto :zword, :word, :zword, :sdword
_mm512_maskz_getexp_round_ps	proto :word, :zword, :sdword
_mm512_mask_getexp_round_pd	proto :zword, :byte, :zword, :sdword
_mm512_maskz_getexp_round_pd	proto :byte, :zword, :sdword

_mm512_mask_getmant_round_ps	proto :zword, :word, :zword, :sdword, :sdword, :sdword
_mm512_maskz_getmant_round_ps	proto :word, :zword, :sdword, :sdword, :sdword
_mm512_mask_getmant_round_pd	proto :zword, :byte, :zword, :sdword, :sdword, :sdword
_mm512_maskz_getmant_round_pd	proto :byte, :zword, :sdword, :sdword, :sdword

_mm512_mask_permute_pd		proto :zword, :byte, :zword, :sdword
_mm512_maskz_permute_pd		proto :byte, :zword, :sdword
_mm512_mask_permute_ps		proto :zword, :word, :zword, :sdword
_mm512_maskz_permute_ps		proto :word, :zword, :sdword
_mm512_mask_permutevar_pd	proto :zword, :byte, :zword, :zword
_mm512_maskz_permutevar_pd	proto :byte, :zword, :zword
_mm512_mask_permutevar_ps	proto :zword, :word, :zword, :zword
_mm512_maskz_permutevar_ps	proto :word, :zword, :zword
_mm512_permutevar_epi32		proto :zword, :zword
_mm512_mask_permutevar_epi32	proto :zword, :word, :zword, :zword

_mm512_mask_permutex_pd		proto :zword, :byte, :zword, :sdword
_mm512_maskz_permutex_pd	proto :byte, :zword, :sdword
_mm512_mask_permutex_epi64	proto :zword, :byte, :zword, :sdword
_mm512_maskz_permutex_epi64	proto :byte, :zword, :sdword
_mm512_mask_permutexvar_pd	proto :zword, :byte, :zword, :zword
_mm512_maskz_permutexvar_pd	proto :byte, :zword, :zword
_mm512_mask_permutexvar_ps	proto :zword, :word, :zword, :zword
_mm512_maskz_permutexvar_ps	proto :word, :zword, :zword
_mm512_mask_permutexvar_epi16	proto :zword, :dword, :zword, :zword
_mm512_maskz_permutexvar_epi16	proto :dword, :zword, :zword
_mm512_mask_permutexvar_epi32	proto :zword, :word, :zword, :zword
_mm512_maskz_permutexvar_epi32	proto :word, :zword, :zword
_mm512_mask_permutexvar_epi64	proto :zword, :byte, :zword, :zword
_mm512_maskz_permutexvar_epi64	proto :byte, :zword, :zword

_mm512_mask_permutex2var_pd	proto :zword, :byte, :zword, :zword
_mm512_mask2_permutex2var_pd	proto :zword, :zword, :byte, :zword
_mm512_maskz_permutex2var_pd	proto :byte, :zword, :zword, :zword
_mm512_mask_permutex2var_ps	proto :zword, :word, :zword, :zword
_mm512_mask2_permutex2var_ps	proto :zword, :zword, :word, :zword
_mm512_maskz_permutex2var_ps	proto :word, :zword, :zword, :zword
_mm512_mask_permutex2var_epi16	proto :zword, :dword, :zword, :zword
_mm512_mask2_permutex2var_epi16 proto :zword, :zword, :dword, :zword
_mm512_maskz_permutex2var_epi16 proto :dword, :zword, :zword, :zword
_mm512_mask_permutex2var_epi32	proto :zword, :word, :zword, :zword
_mm512_mask2_permutex2var_epi32 proto :zword, :zword, :word, :zword
_mm512_maskz_permutex2var_epi32 proto :word, :zword, :zword, :zword
_mm512_mask_permutex2var_epi64	proto :zword, :byte, :zword, :zword
_mm512_mask2_permutex2var_epi64 proto :zword, :zword, :byte, :zword
_mm512_maskz_permutex2var_epi64 proto :byte, :zword, :zword, :zword

_mm512_mask_compress_pd		proto :zword, :byte, :zword
_mm512_maskz_compress_pd	proto :byte, :zword
_mm512_mask_compress_ps		proto :zword, :word, :zword
_mm512_maskz_compress_ps	proto :word, :zword
_mm512_mask_compress_epi32	proto :zword, :word, :zword
_mm512_maskz_compress_epi32	proto :word, :zword
_mm512_mask_compress_epi64	proto :zword, :byte, :zword
_mm512_maskz_compress_epi64	proto :byte, :zword

_mm512_mask_compressstoreu_pd	proto :ptr, :byte, :zword
_mm512_mask_compressstoreu_ps	proto :ptr, :word, :zword
_mm512_mask_compressstoreu_epi32 proto :ptr, :word, :zword
_mm512_mask_compressstoreu_epi64 proto :ptr, :byte, :zword

_mm512_mask_expand_pd		proto :zword, :byte, :zword
_mm512_maskz_expand_pd		proto :byte, :zword
_mm512_mask_expand_ps		proto :zword, :word, :zword
_mm512_maskz_expand_ps		proto :word, :zword
_mm512_mask_expand_epi32	proto :zword, :word, :zword
_mm512_maskz_expand_epi32	proto :word, :zword
_mm512_mask_expand_epi64	proto :zword, :byte, :zword
_mm512_maskz_expand_epi64	proto :byte, :zword
_mm512_mask_expandloadu_pd	proto :zword, :byte, :ptr
_mm512_maskz_expandloadu_pd	proto :byte, :ptr
_mm512_mask_expandloadu_ps	proto :zword, :word, :ptr
_mm512_maskz_expandloadu_ps	proto :word, :ptr
_mm512_mask_expandloadu_epi32	proto :zword, :word, :ptr
_mm512_maskz_expandloadu_epi32	proto :word, :ptr
_mm512_mask_expandloadu_epi64	proto :zword, :byte, :ptr
_mm512_maskz_expandloadu_epi64	proto :byte, :ptr

_mm512_mask_ternarylogic_epi32	proto :zword, :word, :zword, :zword, :sdword
_mm512_maskz_ternarylogic_epi32 proto :word, :zword, :zword, :zword, :sdword
_mm512_mask_ternarylogic_epi64	proto :zword, :byte, :zword, :zword, :sdword
_mm512_maskz_ternarylogic_epi64 proto :byte, :zword, :zword, :zword, :sdword

_mm512_mask_conflict_epi32	proto :zword, :word, :zword
_mm512_maskz_conflict_epi32	proto :word, :zword
_mm512_mask_conflict_epi64	proto :zword, :byte, :zword
_mm512_maskz_conflict_epi64	proto :byte, :zword

_mm512_mask_lzcnt_epi32		proto :zword, :word, :zword
_mm512_maskz_lzcnt_epi32	proto :word, :zword
_mm512_mask_lzcnt_epi64		proto :zword, :byte, :zword
_mm512_maskz_lzcnt_epi64	proto :byte, :zword

_mm512_mask_avg_epu8	proto :zword, :qword, :zword, :zword
_mm512_maskz_avg_epu8	proto :qword, :zword, :zword
_mm512_mask_avg_epu16	proto :zword, :dword, :zword, :zword
_mm512_maskz_avg_epu16	proto :dword, :zword, :zword

_mm512_sad_epu8		proto :zword, :zword
_mm512_mask_dbsad_epu8	proto :zword, :dword, :zword, :zword, :sdword
_mm512_maskz_dbsad_epu8 proto :dword, :zword, :zword, :sdword

_mm512_reduce_add_ps		proto :zword
_mm512_mask_reduce_add_ps	proto :word, :zword
_mm512_reduce_add_pd		proto :zword
_mm512_mask_reduce_add_pd	proto :byte, :zword
_mm512_reduce_add_epi32		proto :zword
_mm512_mask_reduce_add_epi32	proto :word, :zword
_mm512_reduce_add_epi64		proto :zword
_mm512_mask_reduce_add_epi64	proto :byte, :zword

_mm512_reduce_mul_ps		proto :zword
_mm512_mask_reduce_mul_ps	proto :word, :zword
_mm512_reduce_mul_pd		proto :zword
_mm512_mask_reduce_mul_pd	proto :byte, :zword
_mm512_reduce_mul_epi32		proto :zword
_mm512_mask_reduce_mul_epi32	proto :word, :zword
_mm512_reduce_mul_epi64		proto :zword
_mm512_mask_reduce_mul_epi64	proto :byte, :zword

_mm512_reduce_min_ps		proto :zword
_mm512_mask_reduce_min_ps	proto :word, :zword
_mm512_reduce_min_pd		proto :zword
_mm512_mask_reduce_min_pd	proto :byte, :zword
_mm512_reduce_min_epi32		proto :zword
_mm512_mask_reduce_min_epi32	proto :word, :zword
_mm512_reduce_min_epi64		proto :zword
_mm512_mask_reduce_min_epi64	proto :byte, :zword
_mm512_reduce_min_epu32		proto :zword
_mm512_mask_reduce_min_epu32	proto :word, :zword
_mm512_reduce_min_epu64		proto :zword
_mm512_mask_reduce_min_epu64	proto :byte, :zword

_mm512_reduce_max_ps		proto :zword
_mm512_mask_reduce_max_ps	proto :word, :zword
_mm512_reduce_max_pd		proto :zword
_mm512_mask_reduce_max_pd	proto :byte, :zword
_mm512_reduce_max_epi32		proto :zword
_mm512_mask_reduce_max_epi32	proto :word, :zword
_mm512_reduce_max_epi64		proto :zword
_mm512_mask_reduce_max_epi64	proto :byte, :zword
_mm512_reduce_max_epu32		proto :zword
_mm512_mask_reduce_max_epu32	proto :word, :zword
_mm512_reduce_max_epu64		proto :zword
_mm512_mask_reduce_max_epu64	proto :byte, :zword

_mm512_reduce_and_epi32		proto :zword
_mm512_mask_reduce_and_epi32	proto :word, :zword
_mm512_reduce_and_epi64		proto :zword
_mm512_mask_reduce_and_epi64	proto :byte, :zword

_mm512_reduce_or_epi32		proto :zword
_mm512_mask_reduce_or_epi32	proto :word, :zword
_mm512_reduce_or_epi64		proto :zword
_mm512_mask_reduce_or_epi64	proto :byte, :zword

_mm512_mask_reduce_round_pd	proto :zword, :byte, :zword, :sdword, :sdword
_mm512_maskz_reduce_round_pd	proto :byte, :zword, :sdword, :sdword
_mm512_mask_reduce_round_ps	proto :zword, :word, :zword, :sdword, :sdword
_mm512_maskz_reduce_round_ps	proto :word, :zword, :sdword, :sdword

_mm512_mask_roundscale_round_pd proto :zword, :byte, :zword, :sdword, :sdword
_mm512_maskz_roundscale_round_pd proto :byte, :zword, :sdword, :sdword
_mm512_mask_roundscale_round_ps proto :zword, :word, :zword, :sdword, :sdword
_mm512_maskz_roundscale_round_ps proto :word, :zword, :sdword, :sdword

_mm512_mask_scalef_round_pd	proto :zword, :byte, :zword, :zword, :sdword
_mm512_maskz_scalef_round_pd	proto :byte, :zword, :zword, :sdword
_mm512_mask_scalef_round_ps	proto :zword, :word, :zword, :zword, :sdword
_mm512_maskz_scalef_round_ps	proto :word, :zword, :zword, :sdword

_mm512_mask_fixupimm_round_pd	proto :zword, :byte, :zword, :zword, :sdword, :sdword
_mm512_maskz_fixupimm_round_pd	proto :byte, :zword, :zword, :zword, :sdword, :sdword
_mm512_mask_fixupimm_round_ps	proto :zword, :word, :zword, :zword, :sdword, :sdword
_mm512_maskz_fixupimm_round_ps	proto :word, :zword, :zword, :zword, :sdword, :sdword

_mm512_stream_pd		proto :ptr, :zword
_mm512_stream_ps		proto :ptr, :zword
_mm512_stream_si512		proto :ptr, :zword
_mm512_stream_load_si512	proto :ptr

_mm512_castpd512_pd128		proto :zword
_mm512_castps512_ps128		proto :zword
_mm512_castsi512_si128		proto :zword
_mm512_castsi128_si512		proto :oword

_mm512_mask_exp2a23_round_ps	proto :zword, :word, :zword, :sdword
_mm512_maskz_exp2a23_round_ps	proto :word, :zword, :sdword
_mm512_mask_exp2a23_round_pd	proto :zword, :byte, :zword, :sdword
_mm512_maskz_exp2a23_round_pd	proto :byte, :zword, :sdword

_mm512_mask_fpclass_ps_mask	proto :word, :zword, :sdword
_mm512_mask_fpclass_pd_mask	proto :byte, :zword, :sdword

_mm512_mask_range_round_pd	proto :zword, :byte, :zword, :zword, :sdword, :sdword
_mm512_maskz_range_round_pd	proto :byte, :zword, :zword, :sdword, :sdword
_mm512_mask_range_round_ps	proto :zword, :word, :zword, :zword, :sdword, :sdword
_mm512_maskz_range_round_ps	proto :word, :zword, :zword, :sdword, :sdword

_mm512_mask_madd_epi16		proto :zword, :word, :zword, :zword
_mm512_maskz_madd_epi16		proto :word, :zword, :zword
_mm512_mask_maddubs_epi16	proto :zword, :dword, :zword, :zword
_mm512_maskz_maddubs_epi16	proto :dword, :zword, :zword

_mm512_mask_packs_epi16		proto :zword, :qword, :zword, :zword
_mm512_maskz_packs_epi16	proto :qword, :zword, :zword
_mm512_mask_packs_epi32		proto :zword, :dword, :zword, :zword
_mm512_maskz_packs_epi32	proto :dword, :zword, :zword
_mm512_mask_packus_epi16	proto :zword, :qword, :zword, :zword
_mm512_maskz_packus_epi16	proto :qword, :zword, :zword
_mm512_mask_packus_epi32	proto :zword, :dword, :zword, :zword
_mm512_maskz_packus_epi32	proto :dword, :zword, :zword

_mm512_mask_cmp_epi8_mask	proto :qword, :zword, :zword, :sdword
_mm512_mask_cmp_epi16_mask	proto :dword, :zword, :zword, :sdword
_mm512_mask_cmp_epi32_mask	proto :word, :zword, :zword, :sdword
_mm512_mask_cmp_epi64_mask	proto :byte, :zword, :zword, :sdword
_mm512_mask_cmp_epu8_mask	proto :qword, :zword, :zword, :sdword
_mm512_mask_cmp_epu16_mask	proto :dword, :zword, :zword, :sdword
_mm512_mask_cmp_epu32_mask	proto :word, :zword, :zword, :sdword
_mm512_mask_cmp_epu64_mask	proto :byte, :zword, :zword, :sdword

_mm512_mask_test_epi8_mask	proto :qword, :zword, :zword
_mm512_mask_test_epi16_mask	proto :dword, :zword, :zword
_mm512_mask_testn_epi8_mask	proto :qword, :zword, :zword
_mm512_mask_testn_epi16_mask	proto :dword, :zword, :zword
_mm512_mask_test_epi32_mask	proto :word, :zword, :zword
_mm512_mask_test_epi64_mask	proto :byte, :zword, :zword
_mm512_mask_testn_epi32_mask	proto :word, :zword, :zword
_mm512_mask_testn_epi64_mask	proto :byte, :zword, :zword

_mm512_kunpackb		proto :word, :word
_mm512_kunpackw		proto :dword, :dword
_mm512_kunpackd		proto :qword, :qword

_m512_testz_and_mask8	proto :byte, :byte
_m512_testz_and_mask16	proto :word, :word
_m512_testz_and_mask32	proto :dword, :dword
_m512_testz_and_mask64	proto :qword, :qword
_m512_testz_andn_mask8	proto :byte, :byte
_m512_testz_andn_mask16 proto :word, :word
_m512_testz_andn_mask32 proto :dword, :dword
_m512_testz_andn_mask64 proto :qword, :qword
_m512_testz_or_mask8	proto :byte, :byte
_m512_testz_or_mask16	proto :word, :word
_m512_testz_or_mask32	proto :dword, :dword
_m512_testz_or_mask64	proto :qword, :qword
_m512_testz_nor_mask8	proto :byte, :byte
_m512_testz_nor_mask16	proto :word, :word
_m512_testz_nor_mask32	proto :dword, :dword
_m512_testz_nor_mask64	proto :qword, :qword

_mm512_i32gather_ps		proto :zword, :ptr, :sdword
_mm512_mask_i32gather_ps	proto :zword, :word, :zword, :ptr, :sdword
_mm512_i32scatter_ps		proto :ptr, :zword, :zword, :sdword
_mm512_mask_i32scatter_ps	proto :ptr, :word, :zword, :zword, :sdword
_mm512_i64gather_pd		proto :zword, :ptr, :sdword
_mm512_mask_i64gather_pd	proto :zword, :byte, :zword, :ptr, :sdword
_mm512_i64scatter_pd		proto :ptr, :zword, :zword, :sdword
_mm512_mask_i64scatter_pd	proto :ptr, :byte, :zword, :zword, :sdword
_mm512_i32gather_pd		proto :yword, :ptr, :sdword
_mm512_mask_i32gather_pd	proto :zword, :byte, :yword, :ptr, :sdword
_mm512_i32scatter_pd		proto :ptr, :yword, :zword, :sdword
_mm512_mask_i32scatter_pd	proto :ptr, :byte, :yword, :zword, :sdword
_mm512_i32gather_epi32		proto :zword, :ptr, :sdword
_mm512_mask_i32gather_epi32	proto :zword, :word, :zword, :ptr, :sdword
_mm512_i32scatter_epi32		proto :ptr, :zword, :zword, :sdword
_mm512_mask_i32scatter_epi32	proto :ptr, :word, :zword, :zword, :sdword
_mm512_i32gather_epi64		proto :yword, :ptr, :sdword
_mm512_mask_i32gather_epi64	proto :zword, :byte, :yword, :ptr, :sdword
_mm512_i64gather_epi64		proto :zword, :ptr, :sdword
_mm512_mask_i64gather_epi64	proto :zword, :byte, :zword, :ptr, :sdword
_mm512_i32scatter_epi64		proto :ptr, :yword, :zword, :sdword
_mm512_mask_i32scatter_epi64	proto :ptr, :byte, :yword, :zword, :sdword
_mm512_i64scatter_epi64		proto :ptr, :zword, :zword, :sdword
_mm512_mask_i64scatter_epi64	proto :ptr, :byte, :zword, :zword, :sdword
_mm512_i64gather_ps		proto :zword, :ptr, :sdword
_mm512_mask_i64gather_ps	proto :yword, :byte, :zword, :ptr, :sdword
_mm512_i64scatter_ps		proto :ptr, :zword, :yword, :sdword
_mm512_mask_i64scatter_ps	proto :ptr, :byte, :zword, :yword, :sdword
_mm512_i64gather_epi32		proto :zword, :ptr, :sdword
_mm512_mask_i64gather_epi32	proto :yword, :byte, :zword, :ptr, :sdword
_mm512_i64scatter_epi32		proto :ptr, :zword, :yword, :sdword
_mm512_mask_i64scatter_epi32	proto :ptr, :byte, :zword, :yword, :sdword

_mm512_prefetch_i32gather_pd	proto :yword, :ptr, :sdword, :sdword
_mm512_prefetch_i32gather_ps	proto :zword, :ptr, :sdword, :sdword
_mm512_prefetch_i32scatter_pd	proto :ptr, :yword, :sdword, :sdword
_mm512_prefetch_i32scatter_ps	proto :ptr, :zword, :sdword, :sdword
_mm512_prefetch_i64gather_pd	proto :zword, :ptr, :sdword, :sdword
_mm512_prefetch_i64gather_ps	proto :zword, :ptr, :sdword, :sdword
_mm512_prefetch_i64scatter_pd	proto :ptr, :zword, :sdword, :sdword
_mm512_prefetch_i64scatter_ps	proto :ptr, :zword, :sdword, :sdword
_mm512_mask_prefetch_i32gather_pd	proto :yword, :byte, :ptr, :sdword, :sdword
_mm512_mask_prefetch_i32gather_ps	proto :zword, :word, :ptr, :sdword, :sdword
_mm512_mask_prefetch_i32scatter_pd	proto :ptr, :byte, :yword, :sdword, :sdword
_mm512_mask_prefetch_i32scatter_ps	proto :ptr, :word, :zword, :sdword, :sdword
_mm512_mask_prefetch_i64gather_pd	proto :zword, :byte, :ptr, :sdword, :sdword
_mm512_mask_prefetch_i64gather_ps	proto :zword, :byte, :ptr, :sdword, :sdword
_mm512_mask_prefetch_i64scatter_pd	proto :ptr, :byte, :zword, :sdword, :sdword
_mm512_mask_prefetch_i64scatter_ps	proto :ptr, :byte, :zword, :sdword, :sdword

_mm512_cvtpslo_pd		proto :zword
_mm512_mask_cvtpslo_pd		proto :zword, :byte, :zword
_mm512_cvtepi32lo_pd		proto :zword
_mm512_mask_cvtepi32lo_pd	proto :zword, :byte, :zword
_mm512_cvtepu32lo_pd		proto :zword
_mm512_mask_cvtepu32lo_pd	proto :zword, :byte, :zword
_mm512_mask_cvtepi32_pd		proto :zword, :byte, :yword
_mm512_maskz_cvtepi32_pd	proto :byte, :yword
_mm512_mask_cvtepu32_pd		proto :zword, :byte, :yword
_mm512_maskz_cvtepu32_pd	proto :byte, :yword

_mm512_mask_cvt_roundepi32_ps	proto :zword, :word, :zword, :sdword
_mm512_maskz_cvt_roundepi32_ps	proto :word, :zword, :sdword
_mm512_mask_cvt_roundepu32_ps	proto :zword, :word, :zword, :sdword
_mm512_maskz_cvt_roundepu32_ps	proto :word, :zword, :sdword
_mm512_mask_cvt_roundph_ps	proto :zword, :word, :yword, :sdword
_mm512_maskz_cvt_roundph_ps	proto :word, :yword, :sdword
_mm512_mask_cvt_roundps_ph	proto :yword, :word, :zword, :sdword
_mm512_maskz_cvt_roundps_ph	proto :word, :zword, :sdword
_mm512_mask_cvt_roundepi64_ps	proto :yword, :byte, :zword, :sdword
_mm512_maskz_cvt_roundepi64_ps	proto :byte, :zword, :sdword
_mm512_mask_cvt_roundepu64_ps	proto :yword, :byte, :zword, :sdword
_mm512_maskz_cvt_roundepu64_ps	proto :byte, :zword, :sdword

_mm512_mask_cvtepi8_epi32	proto :zword, :word, :oword
_mm512_maskz_cvtepi8_epi32	proto :word, :oword
_mm512_mask_cvtepi8_epi64	proto :zword, :byte, :oword
_mm512_maskz_cvtepi8_epi64	proto :byte, :oword
_mm512_mask_cvtepi16_epi32	proto :zword, :word, :yword
_mm512_maskz_cvtepi16_epi32	proto :word, :yword
_mm512_mask_cvtepi16_epi64	proto :zword, :byte, :oword
_mm512_maskz_cvtepi16_epi64	proto :byte, :oword
_mm512_mask_cvtepi32_epi8	proto :oword, :word, :zword
_mm512_maskz_cvtepi32_epi8	proto :word, :zword
_mm512_mask_cvtepi32_storeu_epi8  proto :ptr, :word, :zword
_mm512_mask_cvtsepi32_epi8	proto :oword, :word, :zword
_mm512_maskz_cvtsepi32_epi8	proto :word, :zword
_mm512_mask_cvtsepi32_storeu_epi8 proto :ptr, :word, :zword
_mm512_mask_cvtusepi32_epi8	proto :oword, :word, :zword
_mm512_maskz_cvtusepi32_epi8	proto :word, :zword
_mm512_mask_cvtusepi32_storeu_epi8 proto :ptr, :word, :zword
_mm512_mask_cvtepi32_epi16	proto :yword, :word, :zword
_mm512_maskz_cvtepi32_epi16	proto :word, :zword
_mm512_mask_cvtepi32_storeu_epi16 proto :ptr, :word, :zword
_mm512_mask_cvtsepi32_epi16	proto :yword, :word, :zword
_mm512_maskz_cvtsepi32_epi16	proto :word, :zword
_mm512_mask_cvtsepi32_storeu_epi16 proto :ptr, :word, :zword
_mm512_mask_cvtusepi32_epi16	proto :yword, :word, :zword
_mm512_maskz_cvtusepi32_epi16	proto :word, :zword
_mm512_mask_cvtusepi32_storeu_epi16 proto :ptr, :word, :zword
_mm512_mask_cvtepi32_epi64	proto :zword, :byte, :yword
_mm512_maskz_cvtepi32_epi64	proto :byte, :yword
_mm512_mask_cvtepi64_epi8	proto :oword, :byte, :zword
_mm512_maskz_cvtepi64_epi8	proto :byte, :zword
_mm512_mask_cvtepi64_storeu_epi8 proto :ptr, :byte, :zword
_mm512_mask_cvtsepi64_epi8	proto :oword, :byte, :zword
_mm512_maskz_cvtsepi64_epi8	proto :byte, :zword
_mm512_mask_cvtsepi64_storeu_epi8 proto :ptr, :byte, :zword
_mm512_mask_cvtusepi64_epi8	proto :oword, :byte, :zword
_mm512_maskz_cvtusepi64_epi8	proto :byte, :zword
_mm512_mask_cvtusepi64_storeu_epi8 proto :ptr, :byte, :zword
_mm512_mask_cvtepi64_epi16	proto :oword, :byte, :zword
_mm512_maskz_cvtepi64_epi16	proto :byte, :zword
_mm512_mask_cvtepi64_storeu_epi16 proto :ptr, :byte, :zword
_mm512_mask_cvtsepi64_epi16	proto :oword, :byte, :zword
_mm512_maskz_cvtsepi64_epi16	proto :byte, :zword
_mm512_mask_cvtsepi64_storeu_epi16 proto :ptr, :byte, :zword
_mm512_mask_cvtusepi64_epi16	proto :oword, :byte, :zword
_mm512_maskz_cvtusepi64_epi16	proto :byte, :zword
_mm512_mask_cvtusepi64_storeu_epi16 proto :ptr, :byte, :zword
_mm512_mask_cvtepi64_epi32	proto :yword, :byte, :zword
_mm512_maskz_cvtepi64_epi32	proto :byte, :zword
_mm512_mask_cvtepi64_storeu_epi32 proto :ptr, :byte, :zword
_mm512_mask_cvtsepi64_epi32	proto :yword, :byte, :zword
_mm512_maskz_cvtsepi64_epi32	proto :byte, :zword
_mm512_mask_cvtsepi64_storeu_epi32 proto :ptr, :byte, :zword
_mm512_mask_cvtusepi64_epi32	proto :yword, :byte, :zword
_mm512_maskz_cvtusepi64_epi32	proto :byte, :zword
_mm512_mask_cvtusepi64_storeu_epi32 proto :ptr, :byte, :zword
_mm512_mask_cvtepu8_epi32	proto :zword, :word, :oword
_mm512_maskz_cvtepu8_epi32	proto :word, :oword
_mm512_mask_cvtepu8_epi64	proto :zword, :byte, :oword
_mm512_maskz_cvtepu8_epi64	proto :byte, :oword
_mm512_mask_cvtepu16_epi32	proto :zword, :word, :yword
_mm512_maskz_cvtepu16_epi32	proto :word, :yword
_mm512_mask_cvtepu16_epi64	proto :zword, :byte, :oword
_mm512_maskz_cvtepu16_epi64	proto :byte, :oword
_mm512_mask_cvtepu32_epi64	proto :zword, :byte, :yword
_mm512_maskz_cvtepu32_epi64	proto :byte, :yword

_mm512_mask_cvt_roundps_epi32	proto :zword, :word, :zword, :sdword
_mm512_maskz_cvt_roundps_epi32	proto :word, :zword, :sdword
_mm512_mask_cvtt_roundps_epi32	proto :zword, :word, :zword, :sdword
_mm512_maskz_cvtt_roundps_epi32 proto :word, :zword, :sdword
_mm512_mask_cvt_roundps_epu32	proto :zword, :word, :zword, :sdword
_mm512_maskz_cvt_roundps_epu32	proto :word, :zword, :sdword
_mm512_mask_cvtt_roundps_epu32	proto :zword, :word, :zword, :sdword
_mm512_maskz_cvtt_roundps_epu32 proto :word, :zword, :sdword
_mm512_mask_cvt_roundpd_epi32	proto :yword, :byte, :zword, :sdword
_mm512_maskz_cvt_roundpd_epi32	proto :byte, :zword, :sdword
_mm512_mask_cvtt_roundpd_epi32	proto :yword, :byte, :zword, :sdword
_mm512_maskz_cvtt_roundpd_epi32 proto :byte, :zword, :sdword
_mm512_mask_cvt_roundpd_epu32	proto :yword, :byte, :zword, :sdword
_mm512_maskz_cvt_roundpd_epu32	proto :byte, :zword, :sdword
_mm512_mask_cvtt_roundpd_epu32	proto :yword, :byte, :zword, :sdword
_mm512_maskz_cvtt_roundpd_epu32 proto :byte, :zword, :sdword

_mm512_mask_cvtepi8_epi16	proto :zword, :dword, :yword
_mm512_maskz_cvtepi8_epi16	proto :dword, :yword
_mm512_mask_cvtepu8_epi16	proto :zword, :dword, :yword
_mm512_maskz_cvtepu8_epi16	proto :dword, :yword
_mm512_mask_cvtepi16_epi8	proto :yword, :dword, :zword
_mm512_maskz_cvtepi16_epi8	proto :dword, :zword
_mm512_mask_cvtepi16_storeu_epi8 proto :ptr, :dword, :zword
_mm512_mask_cvtsepi16_epi8	proto :yword, :dword, :zword
_mm512_maskz_cvtsepi16_epi8	proto :dword, :zword
_mm512_mask_cvtsepi16_storeu_epi8 proto :ptr, :dword, :zword
_mm512_mask_cvtusepi16_epi8	proto :yword, :dword, :zword
_mm512_maskz_cvtusepi16_epi8	proto :dword, :zword
_mm512_mask_cvtusepi16_storeu_epi8 proto :ptr, :dword, :zword

_mm512_mask_cvt_roundepi64_pd	proto :zword, :byte, :zword, :sdword
_mm512_maskz_cvt_roundepi64_pd	proto :byte, :zword, :sdword
_mm512_mask_cvt_roundepu64_pd	proto :zword, :byte, :zword, :sdword
_mm512_maskz_cvt_roundepu64_pd	proto :byte, :zword, :sdword
_mm512_mask_cvt_roundpd_epi64	proto :zword, :byte, :zword, :sdword
_mm512_maskz_cvt_roundpd_epi64	proto :byte, :zword, :sdword
_mm512_mask_cvt_roundpd_epu64	proto :zword, :byte, :zword, :sdword
_mm512_maskz_cvt_roundpd_epu64	proto :byte, :zword, :sdword
_mm512_mask_cvtt_roundpd_epi64	proto :zword, :byte, :zword, :sdword
_mm512_maskz_cvtt_roundpd_epi64 proto :byte, :zword, :sdword
_mm512_mask_cvtt_roundpd_epu64	proto :zword, :byte, :zword, :sdword
_mm512_maskz_cvtt_roundpd_epu64 proto :byte, :zword, :sdword
_mm512_mask_cvt_roundps_epi64	proto :zword, :byte, :yword, :sdword
_mm512_maskz_cvt_roundps_epi64	proto :byte, :yword, :sdword
_mm512_mask_cvt_roundps_epu64	proto :zword, :byte, :yword, :sdword
_mm512_maskz_cvt_roundps_epu64	proto :byte, :yword, :sdword
_mm512_mask_cvtt_roundps_epi64	proto :zword, :byte, :yword, :sdword
_mm512_maskz_cvtt_roundps_epi64 proto :byte, :yword, :sdword
_mm512_mask_cvtt_roundps_epu64	proto :zword, :byte, :yword, :sdword
_mm512_maskz_cvtt_roundps_epu64 proto :byte, :yword, :sdword

_mm512_setzero_epi32	equ <_mm512_setzero_si512>
_mm512_set1_epi8 macro e1
	exitm<_mm512_maskz_set1_epi8(_MM_K0_REG64, (e1))>
	endm

_mm512_set1_epi16 macro e1
	exitm<_mm512_maskz_set1_epi16(_MM_K0_REG64, (e1))>
	endm

_mm512_set1_epi32 macro e1
	exitm<_mm512_maskz_set1_epi32(_MM_K0_REG, (e1))>
	endm

_mm512_set1_epi64 macro e1
	exitm<_mm512_maskz_set1_epi64(_MM_K0_REG, (e1))>
	endm

_mm512_set_1to8_pq macro x
	exitm<_mm512_set1_epi64((x))>
	endm
_mm512_set_1to8_epi64 macro x
	exitm<_mm512_set1_epi64((x))>
	endm
_mm512_set_1to16_pi macro x
	exitm<_mm512_set1_epi32((x))>
	endm
_mm512_set_1to16_epi32 macro x
	exitm<_mm512_set1_epi32((x))>
	endm
_mm512_set4_epi64 macro a,b,c,d
	exitm<_mm512_set_epi64((a), (b), (c), (d), (a), (b), (c), (d))>
	endm

_mm512_set4_epi32 macro a,b,c,d
	exitm<_mm512_set_epi32((a), (b), (c), (d), (a), (b), (c), (d), (b), (c), (d), (a), (b), (c), (d)) (a)>
	endm

_mm512_setr4_epi64 macro a,b,c,d
	exitm<>
	endm
_mm512_set_4to8_pq macro a,b,c,d
	exitm<>
	endm
_mm512_set_4to8_epi64 macro a,b,c,d
	exitm<>
	endm
_mm512_setr4_epi32 macro a,b,c,d
	exitm<>
	endm
_mm512_set_4to16_pi macro a,b,c,d
	exitm<>
	endm
_mm512_set_4to16_epi32 macro a,b,c,d
	exitm<>
	endm
_mm512_setr_epi32 macro e0,e1,e2,e3,e4,e5,e6,e7,e8
	exitm<e0,e1,e2,e3,e4,e5,e6,e7,e8>
	endm
_mm512_setr_epi64 macro e0,e1,e2,e3,e4,e5,e6,e7
	exitm<>
	endm
_mm512_set_8to8_pq macro e0,e1,e2,e3,e4,e5,e6,e7
	exitm<>
	endm
_mm512_set_8to8_epi64 macro e0,e1,e2,e3,e4,e5,e6,e7
	exitm<>
	endm

_mm512_add_epi8 macro v1, v2
	exitm<_mm512_maskz_add_epi8(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_add_epi16 macro v1, v2
	exitm<_mm512_maskz_add_epi16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_add_epi32 macro v1, v2
	exitm<_mm512_maskz_add_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_add_epi64 macro v1, v2
	exitm<_mm512_maskz_add_epi64(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_adds_epi8 macro v1, v2
	exitm<_mm512_maskz_adds_epi8(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_adds_epi16 macro v1, v2
	exitm<_mm512_maskz_adds_epi16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_adds_epu8 macro v1, v2
	exitm<_mm512_maskz_adds_epu8(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_adds_epu16 macro v1, v2
	exitm<_mm512_maskz_adds_epu16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_abs_epi8 macro v1
	exitm<_mm512_maskz_abs_epi8(_MM_K0_REG64, (v1))>
	endm

_mm512_abs_epi16 macro v1
	exitm<_mm512_maskz_abs_epi16(_MM_K0_REG64, (v1))>
	endm

_mm512_abs_epi32 macro v1
	exitm<_mm512_maskz_abs_epi32(_MM_K0_REG, (v1))>
	endm

_mm512_abs_epi64 macro v1
	exitm<_mm512_maskz_abs_epi64(_MM_K0_REG, (v1))>
	endm

_mm512_broadcast_i32x2 macro v1
	exitm<_mm512_maskz_broadcast_i32x2(_MM_K0_REG, (v1))>
	endm

_mm512_broadcast_i32x4 macro v1
	exitm<_mm512_maskz_broadcast_i32x4(_MM_K0_REG, (v1))>
	endm

_mm512_broadcast_i32x8 macro v1
	exitm<_mm512_maskz_broadcast_i32x8(_MM_K0_REG, (v1))>
	endm

_mm512_broadcast_i64x2 macro v1
	exitm<_mm512_maskz_broadcast_i64x2(_MM_K0_REG, (v1))>
	endm

_mm512_broadcast_i64x4 macro v1
	exitm<_mm512_maskz_broadcast_i64x4(_MM_K0_REG, (v1))>
	endm

_mm512_broadcastb_epi8 macro v1
	exitm<_mm512_maskz_broadcastb_epi8(_MM_K0_REG64, (v1))>
	endm

_mm512_broadcastw_epi16 macro v1
	exitm<_mm512_maskz_broadcastw_epi16(_MM_K0_REG64, (v1))>
	endm

_mm512_broadcastd_epi32 macro v1
	exitm<_mm512_maskz_broadcastd_epi32(_MM_K0_REG, (v1))>
	endm

_mm512_broadcastq_epi64 macro v1
	exitm<_mm512_maskz_broadcastq_epi64(_MM_K0_REG, (v1))>
	endm

_mm512_sub_epi8 macro v1, v2
	exitm<_mm512_maskz_sub_epi8(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_sub_epi16 macro v1, v2
	exitm<_mm512_maskz_sub_epi16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_sub_epi32 macro v1, v2
	exitm<_mm512_maskz_sub_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_sub_epi64 macro v1, v2
	exitm<_mm512_maskz_sub_epi64(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_subs_epi8 macro v1, v2
	exitm<_mm512_maskz_subs_epi8(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_subs_epi16 macro v1, v2
	exitm<_mm512_maskz_subs_epi16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_subs_epu8 macro v1, v2
	exitm<_mm512_maskz_subs_epu8(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_subs_epu16 macro v1, v2
	exitm<_mm512_maskz_subs_epu16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_max_epi8 macro v1, v2
	exitm<_mm512_maskz_max_epi8(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_max_epi16 macro v1, v2
	exitm<_mm512_maskz_max_epi16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_max_epi32 macro v1, v2
	exitm<_mm512_maskz_max_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_max_epi64 macro v1, v2
	exitm<_mm512_maskz_max_epi64(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_max_epu8 macro v1, v2
	exitm<_mm512_maskz_max_epu8(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_max_epu16 macro v1, v2
	exitm<_mm512_maskz_max_epu16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_max_epu32 macro v1, v2
	exitm<_mm512_maskz_max_epu32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_max_epu64 macro v1, v2
	exitm<_mm512_maskz_max_epu64(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_min_epi8 macro v1, v2
	exitm<_mm512_maskz_min_epi8(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_min_epi16 macro v1, v2
	exitm<_mm512_maskz_min_epi16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_min_epi32 macro v1, v2
	exitm<_mm512_maskz_min_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_min_epi64 macro v1, v2
	exitm<_mm512_maskz_min_epi64(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_min_epu8 macro v1, v2
	exitm<_mm512_maskz_min_epu8(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_min_epu16 macro v1, v2
	exitm<_mm512_maskz_min_epu16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_min_epu32 macro v1, v2
	exitm<_mm512_maskz_min_epu32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_min_epu64 macro v1, v2
	exitm<_mm512_maskz_min_epu64(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_mul_epi32 macro v1, v2
	exitm<_mm512_maskz_mul_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_mul_epu32 macro v1, v2
	exitm<_mm512_maskz_mul_epu32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_mulhi_epi16 macro v1, v2
	exitm<_mm512_maskz_mulhi_epi16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_mulhi_epu16 macro v1, v2
	exitm<_mm512_maskz_mulhi_epu16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_mullo_epi16 macro v1, v2
	exitm<_mm512_maskz_mullo_epi16(_MM_K0_REG64,(v1), (v2))>
	endm

_mm512_mullo_epi32 macro v1, v2
	exitm<_mm512_maskz_mullo_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_mullo_epi64 macro v1, v2
	exitm<_mm512_maskz_mullo_epi64(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_mulhrs_epi16 macro v1, v2
	exitm<_mm512_maskz_mulhrs_epi16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_load_epi32 macro p1
	exitm<_mm512_maskz_load_epi32(_MM_K0_REG, (p1))>
	endm

_mm512_load_si512	equ <_mm512_load_epi32>
_mm512_load_epi64 macro p1
	exitm<_mm512_maskz_load_epi64(_MM_K0_REG, (p1))>
	endm

_mm512_loadu_epi8 macro p1
	exitm<_mm512_maskz_loadu_epi8(_MM_K0_REG64, (p1))>
	endm

_mm512_loadu_epi16 macro p1
	exitm<_mm512_maskz_loadu_epi16(_MM_K0_REG64, (p1))>
	endm

_mm512_loadu_epi32 macro p1
	exitm<_mm512_maskz_loadu_epi32(_MM_K0_REG, (p1))>
	endm

_mm512_loadu_si512	equ <_mm512_loadu_epi32>
_mm512_loadu_epi64 macro p1
	exitm<_mm512_maskz_loadu_epi64(_MM_K0_REG, (p1))>
	endm

_mm512_store_epi32 macro p1, v1
	exitm<_mm512_mask_store_epi32((p1), _MM_K0_REG, (v1))>
	endm

_mm512_store_si512	equ <_mm512_store_epi32>
_mm512_store_epi64 macro p1, v1
	exitm<_mm512_mask_store_epi64((p1),_MM_K0_REG, (v1))>
	endm

_mm512_storeu_epi8 macro p1, v1
	exitm<_mm512_mask_storeu_epi8((p1), _MM_K0_REG64, (v1))>
	endm

_mm512_storeu_epi16 macro p1, v1
	exitm<_mm512_mask_storeu_epi16((p1),_MM_K0_REG64, (v1))>
	endm

_mm512_storeu_epi32 macro p1, v1
	exitm<_mm512_mask_storeu_epi32((p1), _MM_K0_REG, (v1))>
	endm

_mm512_storeu_si512	equ <_mm512_storeu_epi32>
_mm512_storeu_epi64 macro p1, v1
	exitm<_mm512_mask_storeu_epi64((p1),_MM_K0_REG, (v1))>
	endm

_mm512_extracti32x4_epi32 macro v1, e1
	exitm<_mm512_maskz_extracti32x4_epi32(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_extracti32x8_epi32 macro v1, e1
	exitm<_mm512_maskz_extracti32x8_epi32(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_extracti64x2_epi64 macro v1, e1
	exitm<_mm512_maskz_extracti64x2_epi64(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_extracti64x4_epi64 macro v1, e1
	exitm<_mm512_maskz_extracti64x4_epi64(_MM_K0_REG, (v1), (e1))>
	endm


_mm512_inserti32x4 macro v1, v2, e1
	exitm<_mm512_maskz_inserti32x4(_MM_K0_REG, (v1), (v2), (e1))>
	endm

_mm512_inserti32x8 macro v1, v2, e1
	exitm<_mm512_maskz_inserti32x8(_MM_K0_REG, (v1), (v2), (e1))>
	endm

_mm512_inserti64x2 macro v1, v2, e1
	exitm<_mm512_maskz_inserti64x2(_MM_K0_REG, (v1), (v2), (e1))>
	endm

_mm512_inserti64x4 macro v1, v2, e1
	exitm<_mm512_maskz_inserti64x4(_MM_K0_REG, (v1), (v2), (e1))>
	endm


_mm512_shuffle_epi8 macro v1, v2
	exitm<_mm512_maskz_shuffle_epi8(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_shuffle_epi32 macro v1, e1
	exitm<_mm512_maskz_shuffle_epi32(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_shuffle_i32x4 macro v1, v2, e1
	exitm<_mm512_maskz_shuffle_i32x4(_MM_K0_REG, (v1), (v2), (e1))>
	endm

_mm512_shuffle_i64x2 macro v1, v2, e1
	exitm<_mm512_maskz_shuffle_i64x2(_MM_K0_REG, (v1), (v2), (e1))>
	endm

_mm512_shufflehi_epi16 macro v1, e1
	exitm<_mm512_maskz_shufflehi_epi16(_MM_K0_REG64, (v1), (e1))>
	endm

_mm512_shufflelo_epi16 macro v1, e1
	exitm<_mm512_maskz_shufflelo_epi16(_MM_K0_REG64, (v1), (e1))>
	endm

_mm512_movedup_pd macro v1
	exitm<_mm512_maskz_movedup_pd(_MM_K0_REG, (v1))>
	endm

_mm512_movehdup_ps macro v1
	exitm<_mm512_maskz_movehdup_ps(_MM_K0_REG, (v1))>
	endm

_mm512_moveldup_ps macro v1
	exitm<_mm512_maskz_moveldup_ps(_MM_K0_REG,(v1))>
	endm


_mm512_alignr_epi8 macro v1, v2, e1
	exitm<_mm512_maskz_alignr_epi8(_MM_K0_REG64, (v1), (v2), (e1))>
	endm

_mm512_alignr_epi32 macro v1, v2, e1
	exitm<_mm512_maskz_alignr_epi32(_MM_K0_REG,(v1), (v2), (e1))>
	endm

_mm512_alignr_epi64 macro v1, v2, e1
	exitm<_mm512_maskz_alignr_epi64(_MM_K0_REG, (v1), (v2), (e1))>
	endm

_mm512_and_pd macro v1, v2
	exitm<_mm512_maskz_and_pd(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_and_ps macro v1, v2
	exitm<_mm512_maskz_and_ps(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_and_epi32 macro v1, v2
	exitm<_mm512_maskz_and_epi32(_MM_K0_REG,(v1), (v2))>
	endm

_mm512_and_si512	equ <_mm512_and_epi32>
_mm512_and_epi64 macro v1, v2
	exitm<_mm512_maskz_and_epi64(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_andnot_pd macro v1, v2
	exitm<_mm512_maskz_andnot_pd(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_andnot_ps macro v1, v2
	exitm<_mm512_maskz_andnot_ps(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_andnot_epi32 macro v1, v2
	exitm<_mm512_maskz_andnot_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_andnot_si512	equ <_mm512_andnot_epi32>
_mm512_andnot_epi64 macro v1, v2
	exitm<_mm512_maskz_andnot_epi64(_MM_K0_REG, (v1), (v2))>
	endm


_mm512_or_pd macro v1, v2
	exitm<_mm512_maskz_or_pd(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_or_ps macro v1, v2
	exitm<_mm512_maskz_or_ps(_MM_K0_REG,(v1), (v2))>
	endm

_mm512_or_epi32 macro v1, v2
	exitm<_mm512_maskz_or_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_or_si512		equ <_mm512_or_epi32>
_mm512_or_epi64 macro v1, v2
	exitm<_mm512_maskz_or_epi64(_MM_K0_REG, (v1), (v2))>
	endm


_mm512_xor_pd macro v1, v2
	exitm<_mm512_maskz_xor_pd(_MM_K0_REG,(v1), (v2))>
	endm

_mm512_xor_ps macro v1, v2
	exitm<_mm512_maskz_xor_ps(_MM_K0_REG,(v1), (v2))>
	endm

_mm512_xor_epi32 macro v1, v2
	exitm<_mm512_maskz_xor_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_xor_si512	equ <_mm512_xor_epi32>
_mm512_xor_epi64 macro v1, v2
	exitm<_mm512_maskz_xor_epi64(_MM_K0_REG, (v1), (v2))>
	endm


_mm512_sll_epi16 macro v1, v2
	exitm<_mm512_maskz_sll_epi16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_sll_epi32 macro v1, v2
	exitm<_mm512_maskz_sll_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_sll_epi64 macro v1, v2
	exitm<_mm512_maskz_sll_epi64(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_slli_epi16 macro v1, e1
	exitm<_mm512_maskz_slli_epi16(_MM_K0_REG64, (v1), (e1))>
	endm

_mm512_slli_epi32 macro v1, e1
	exitm<_mm512_maskz_slli_epi32(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_slli_epi64 macro v1, e1
	exitm<_mm512_maskz_slli_epi64(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_sllv_epi16 macro v1, v2
	exitm<_mm512_maskz_sllv_epi16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_sllv_epi32 macro v1, v2
	exitm<_mm512_maskz_sllv_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_sllv_epi64 macro v1, v2
	exitm<_mm512_maskz_sllv_epi64(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_srl_epi16 macro v1, v2
	exitm<_mm512_maskz_srl_epi16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_srl_epi32 macro v1, v2
	exitm<_mm512_maskz_srl_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_srl_epi64 macro v1, v2
	exitm<_mm512_maskz_srl_epi64(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_srli_epi16 macro v1, e1
	exitm<_mm512_maskz_srli_epi16(_MM_K0_REG64, (v1), (e1))>
	endm

_mm512_srli_epi32 macro v1, e1
	exitm<_mm512_maskz_srli_epi32(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_srli_epi64 macro v1, e1
	exitm<_mm512_maskz_srli_epi64(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_srlv_epi16 macro v1, v2
	exitm<_mm512_maskz_srlv_epi16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_srlv_epi32 macro v1, v2
	exitm<_mm512_maskz_srlv_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_srlv_epi64 macro v1, v2
	exitm<_mm512_maskz_srlv_epi64(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_sra_epi16 macro v1, v2
	exitm<_mm512_maskz_sra_epi16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_sra_epi32 macro v1, v2
	exitm<_mm512_maskz_sra_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_sra_epi64 macro v1, v2
	exitm<_mm512_maskz_sra_epi64(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_srai_epi16 macro v1, e1
	exitm<_mm512_maskz_srai_epi16(_MM_K0_REG64, (v1), (e1))>
	endm

_mm512_srai_epi32 macro v1, e1
	exitm<_mm512_maskz_srai_epi32(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_srai_epi64 macro v1, e1
	exitm<_mm512_maskz_srai_epi64(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_srav_epi16 macro v1, v2
	exitm<_mm512_maskz_srav_epi16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_srav_epi32 macro v1, v2
	exitm<_mm512_maskz_srav_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_srav_epi64 macro v1, v2
	exitm<_mm512_maskz_srav_epi64(_MM_K0_REG, (v1), (v2))>
	endm


_mm512_rol_epi32 macro v1, e1
	exitm<_mm512_maskz_rol_epi32(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_rol_epi64 macro v1, e1
	exitm<_mm512_maskz_rol_epi64(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_rolv_epi32 macro v1, v2
	exitm<_mm512_maskz_rolv_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_rolv_epi64 macro v1, v2
	exitm<_mm512_maskz_rolv_epi64(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_ror_epi32 macro v1, e1
	exitm<_mm512_maskz_ror_epi32(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_ror_epi64 macro v1, e1
	exitm<_mm512_maskz_ror_epi64(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_rorv_epi32 macro v1, v2
	exitm<_mm512_maskz_rorv_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_rorv_epi64 macro v1, v2
	exitm<_mm512_maskz_rorv_epi64(_MM_K0_REG, (v1), (v2))>
	endm


_mm512_unpackhi_pd macro v1, v2
	exitm<_mm512_maskz_unpackhi_pd(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_unpackhi_ps macro v1, v2
	exitm<_mm512_maskz_unpackhi_ps(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_unpacklo_pd macro v1, v2
	exitm<_mm512_maskz_unpacklo_pd(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_unpacklo_ps macro v1, v2
	exitm<_mm512_maskz_unpacklo_ps(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_unpackhi_epi8 macro v1, v2
	exitm<_mm512_maskz_unpackhi_epi8(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_unpackhi_epi16 macro v1, v2
	exitm<_mm512_maskz_unpackhi_epi16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_unpackhi_epi32 macro v1, v2
	exitm<_mm512_maskz_unpackhi_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_unpackhi_epi64 macro v1, v2
	exitm<_mm512_maskz_unpackhi_epi64(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_unpacklo_epi8 macro v1, v2
	exitm<_mm512_maskz_unpacklo_epi8(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_unpacklo_epi16 macro v1, v2
	exitm<_mm512_maskz_unpacklo_epi16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_unpacklo_epi32 macro v1, v2
	exitm<_mm512_maskz_unpacklo_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_unpacklo_epi64 macro v1, v2
	exitm<_mm512_maskz_unpacklo_epi64(_MM_K0_REG, (v1), (v2))>
	endm


_mm512_mask_getexp_ps macro v1, k1, v2
	exitm<_mm512_mask_getexp_round_ps((v1), (k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_getexp_ps macro k1, v1
	exitm<_mm512_maskz_getexp_round_ps((k1), (v1), _MM_FROUND_CUR_DIRECTION)>
	endm


_mm512_getexp_round_ps macro v1, e1
	exitm<_mm512_maskz_getexp_round_ps(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_getexp_ps macro v1
	exitm<_mm512_maskz_getexp_ps(_MM_K0_REG, (v1))>
	endm

_mm512_mask_getexp_pd macro v1, k1, v2
	exitm<_mm512_mask_getexp_round_pd((v1), (k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_getexp_pd macro k1, v1
	exitm<_mm512_maskz_getexp_round_pd((k1), (v1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_getexp_round_pd macro v1, e1
	exitm<_mm512_maskz_getexp_round_pd(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_getexp_pd macro v1
	exitm<_mm512_maskz_getexp_pd(_MM_K0_REG, (v1))>
	endm


_mm512_mask_getmant_ps macro v1, k1, v2, e1, e2
	exitm<_mm512_mask_getmant_round_ps((v1), (k1), (v2), (e1), (e2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_getmant_ps macro k1, v1, e1, e2
	exitm<_mm512_maskz_getmant_round_ps((k1), (v1), (e1), (e2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_getmant_round_ps macro v1, e1, e2, e3
	exitm<_mm512_maskz_getmant_round_ps(_MM_K0_REG, (v1), (e1), (e2), (e3))>
	endm

_mm512_getmant_ps macro v1, e1, e2
	exitm<_mm512_maskz_getmant_ps(_MM_K0_REG, (v1), (e1), (e2))>
	endm

_mm512_mask_getmant_pd macro v1, k1, v2, e1, e2
	exitm<_mm512_mask_getmant_round_pd((v1), (k1), (v2), (e1), (e2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_getmant_pd macro k1, v1, e1, e2
	exitm<_mm512_maskz_getmant_round_pd((k1), (v1), (e1), (e2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_getmant_round_pd macro v1, e1, e2, e3
	exitm<_mm512_maskz_getmant_round_pd(_MM_K0_REG, (v1), (e1), (e2), (e3))>
	endm

_mm512_getmant_pd macro v1, e1, e2
	exitm<_mm512_maskz_getmant_pd(_MM_K0_REG, (v1), (e1), (e2))>
	endm


_mm512_permute_pd macro v1, e1
	exitm<_mm512_maskz_permute_pd(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_permute_ps macro v1, e1
	exitm<_mm512_maskz_permute_ps(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_permutevar_pd macro v1, v2
	exitm<_mm512_maskz_permutevar_pd(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_permutevar_ps macro v1, v2
	exitm<_mm512_maskz_permutevar_ps(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_permutex_pd macro v1, e1
	exitm<_mm512_maskz_permutex_pd(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_permutex_epi64 macro v1, e1
	exitm<_mm512_maskz_permutex_epi64(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_permutexvar_pd macro v1, v2
	exitm<_mm512_maskz_permutexvar_pd(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_permutexvar_ps macro v1, v2
	exitm<_mm512_maskz_permutexvar_ps(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_permutexvar_epi16 macro v1, v2
	exitm<_mm512_maskz_permutexvar_epi16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_permutexvar_epi32 macro v1, v2
	exitm<_mm512_maskz_permutexvar_epi32(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_permutexvar_epi64 macro v1, v2
	exitm<_mm512_maskz_permutexvar_epi64(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_permutex2var_pd macro v1, v2, v3
	exitm<_mm512_maskz_permutex2var_pd(_MM_K0_REG, (v1), (v2), (v3))>
	endm

_mm512_permutex2var_ps macro v1, v2, v3
	exitm<_mm512_maskz_permutex2var_ps(_MM_K0_REG, (v1), (v2), (v3))>
	endm

_mm512_permutex2var_epi16 macro v1, v2, v3
	exitm<_mm512_maskz_permutex2var_epi16(_MM_K0_REG64, (v1), (v2), (v3))>
	endm

_mm512_permutex2var_epi32 macro v1, v2, v3
	exitm<_mm512_maskz_permutex2var_epi32(_MM_K0_REG, (v1), (v2), (v3))>
	endm

_mm512_permutex2var_epi64 macro v1, v2, v3
	exitm<_mm512_maskz_permutex2var_epi64(_MM_K0_REG, (v1), (v2), (v3))>
	endm


_mm512_ternarylogic_epi32 macro v1, v2, v3, e1
	exitm<_mm512_maskz_ternarylogic_epi32(_MM_K0_REG, (v1), (v2), (v3), (e1))>
	endm

_mm512_ternarylogic_epi64 macro v1, v2, v3, e1
	exitm<_mm512_maskz_ternarylogic_epi64(_MM_K0_REG, (v1), (v2), (v3), (e1))>
	endm

_mm512_conflict_epi32 macro v1
	exitm<_mm512_maskz_conflict_epi32(_MM_K0_REG, (v1))>
	endm

_mm512_conflict_epi64 macro v1
	exitm<_mm512_maskz_conflict_epi64(_MM_K0_REG, (v1))>
	endm

_mm512_lzcnt_epi32 macro v1
	exitm<_mm512_maskz_lzcnt_epi32(_MM_K0_REG, (v1))>
	endm

_mm512_lzcnt_epi64 macro v1
	exitm<_mm512_maskz_lzcnt_epi64(_MM_K0_REG,(v1))>
	endm

_mm512_avg_epu8 macro v1, v2
	exitm<_mm512_maskz_avg_epu8(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_avg_epu16 macro v1, v2
	exitm<_mm512_maskz_avg_epu16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_dbsad_epu8 macro v1, v2, e1
	exitm<_mm512_maskz_dbsad_epu8(_MM_K0_REG64, (v1), (v2), (e1))>
	endm

_mm512_reduce_round_pd macro v1, e1, e2
	exitm<_mm512_maskz_reduce_round_pd(_MM_K0_REG, (v1), (e1), (e2))>
	endm

_mm512_mask_reduce_pd macro v1, k1, v2, e1
	exitm<_mm512_mask_reduce_round_pd((v1), (k1), (v2), (e1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_reduce_pd macro k1, v1, e1
	exitm<_mm512_maskz_reduce_round_pd((k1), (v1), (e1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_reduce_pd macro v1, e1
	exitm<_mm512_maskz_reduce_pd(_MM_K0_REG, (v1), (e1))>
	endm
_mm512_reduce_round_ps macro v1, e1, e2
	exitm<_mm512_maskz_reduce_round_ps(_MM_K0_REG, (v1), (e1), (e2))>
	endm

_mm512_mask_reduce_ps macro v1, k1, v2, e1
	exitm<_mm512_mask_reduce_round_ps((v1), (k1), (v2), (e1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_reduce_ps macro k1, v1, e1
	exitm<_mm512_maskz_reduce_round_ps((k1), (v1), (e1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_reduce_ps macro v1, e1
	exitm<_mm512_maskz_reduce_ps(_MM_K0_REG,(v1), (e1))>
	endm

_mm512_roundscale_round_pd macro v1, e1, e2
	exitm<_mm512_maskz_roundscale_round_pd(_MM_K0_REG, (v1), (e1), (e2))>
	endm

_mm512_mask_roundscale_pd macro v1, k1, v2, e1
	exitm<_mm512_mask_roundscale_round_pd((v1), (k1), (v2), (e1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_roundscale_pd macro k1, v1, e1
	exitm<_mm512_maskz_roundscale_round_pd((k1), (v1), (e1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_roundscale_pd macro v1, e1
	exitm<_mm512_maskz_roundscale_pd(_MM_K0_REG, (v1), (e1))>
	endm


_mm512_roundscale_round_ps macro v1, e1, e2
	exitm<_mm512_maskz_roundscale_round_ps(_MM_K0_REG, (v1), (e1), (e2))>
	endm

_mm512_mask_roundscale_ps macro v1, k1, v2, e1
	exitm< _mm512_mask_roundscale_round_ps((v1), (k1), (v2), (e1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_roundscale_ps macro k1, v1, e1
	exitm<_mm512_maskz_roundscale_round_ps((k1), (v1), (e1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_roundscale_ps macro v1, e1
	exitm<_mm512_maskz_roundscale_ps(_MM_K0_REG, (v1), (e1))>
	endm


_mm512_scalef_round_pd macro v1, v2, e1
	exitm<_mm512_maskz_scalef_round_pd(_MM_K0_REG, (v1), (v2), (e1))>
	endm

_mm512_mask_scalef_pd macro v1, k1, v2, v3
	exitm<_mm512_mask_scalef_round_pd((v1), (k1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_scalef_pd macro k1, v1, v2
	exitm<_mm512_maskz_scalef_round_pd((k1), (v1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_scalef_pd macro v1, v2
	exitm<_mm512_maskz_scalef_pd(_MM_K0_REG, (v1), (v2))>
	endm


_mm512_scalef_round_ps macro v1, v2, e1
	exitm<_mm512_maskz_scalef_round_ps(_MM_K0_REG, (v1), (v2), (e1))>
	endm

_mm512_mask_scalef_ps macro v1, k1, v2, v3
	exitm<_mm512_mask_scalef_round_ps((v1), (k1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_scalef_ps macro k1, v1, v2
	exitm<_mm512_maskz_scalef_round_ps((k1), (v1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_scalef_ps macro v1, v2
	exitm<_mm512_maskz_scalef_ps(_MM_K0_REG, (v1), (v2))>
	endm


_mm512_fixupimm_round_pd macro v1, v2, v3, e1, e2
	exitm<_mm512_maskz_fixupimm_round_pd(_MM_K0_REG, (v1), (v2), (v3), (e1), (e2))>
	endm

_mm512_mask_fixupimm_pd macro v1, k1, v2, v3, e1
	exitm<_mm512_mask_fixupimm_round_pd((v1), (k1), (v2), (v3), (e1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_fixupimm_pd macro k1, v1, v2, v3, e1
	exitm<_mm512_maskz_fixupimm_round_pd((k1), (v1), (v2), (v3), (e1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_fixupimm_pd macro v1, v2, v3, e1
	exitm<_mm512_maskz_fixupimm_pd(_MM_K0_REG, (v1), (v2), (v3), (e1))>
	endm

_mm512_fixupimm_round_ps macro v1, v2, v3, e1, e2
	exitm<_mm512_maskz_fixupimm_round_ps(_MM_K0_REG, (v1), (v2), (v3), (e1), (e2))>
	endm

_mm512_mask_fixupimm_ps macro v1, k1, v2, v3, e1
	exitm<_mm512_mask_fixupimm_round_ps((v1), (k1), (v2), (v3), (e1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_fixupimm_ps macro k1, v1, v2, v3, e1
	exitm<_mm512_maskz_fixupimm_round_ps((k1), (v1), (v2), (v3), (e1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_fixupimm_ps macro v1, v2, v3, e1
	exitm<_mm512_maskz_fixupimm_ps(_MM_K0_REG,(v1), (v2), (v3), (e1))>
	endm

_mm512_exp2a23_round_ps macro v1, e1
	exitm<_mm512_maskz_exp2a23_round_ps(_MM_K0_REG,(v1), (e1))>
	endm

_mm512_mask_exp2a23_ps macro v1, k1, v2
	exitm<_mm512_mask_exp2a23_round_ps((v1), (k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_exp2a23_ps macro k1, v1
	exitm<_mm512_maskz_exp2a23_round_ps((k1), (v1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_exp2a23_ps macro v1
	exitm<_mm512_maskz_exp2a23_ps(_MM_K0_REG, (v1))>
	endm

_mm512_exp2a23_round_pd macro v1, e1
	exitm<_mm512_maskz_exp2a23_round_pd(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_mask_exp2a23_pd macro v1, k1, v2
	exitm<_mm512_mask_exp2a23_round_pd((v1), (k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_exp2a23_pd macro k1, v1
	exitm<_mm512_maskz_exp2a23_round_pd((k1), (v1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_exp2a23_pd macro v1
	exitm<_mm512_maskz_exp2a23_pd(_MM_K0_REG, (v1))>
	endm

_mm512_fpclass_ps_mask macro v1, e1
	exitm<_mm512_mask_fpclass_ps_mask(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_fpclass_pd_mask macro v1, e1
	exitm<_mm512_mask_fpclass_pd_mask(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_range_round_pd macro v1, v2, e1, e2
	exitm<_mm512_maskz_range_round_pd(_MM_K0_REG, (v1), (v2), (e1), (e2))>
	endm

_mm512_mask_range_pd macro v1, k1, v2, v3, e1
	exitm<_mm512_mask_range_round_pd((v1), (k1), (v2), (v3), (e1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_range_pd macro k1, v1, v2, e1
	exitm<_mm512_maskz_range_round_pd((k1), (v1), (v2), (e1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_range_pd macro v1, v2, e1
	exitm<_mm512_maskz_range_pd(_MM_K0_REG, (v1), (v2), (e1))>
	endm


_mm512_range_round_ps macro v1, v2, e1, e2
	exitm<_mm512_maskz_range_round_ps(_MM_K0_REG, (v1), (v2), (e1), (e2))>
	endm

_mm512_mask_range_ps macro v1, k1, v2, v3, e1
	exitm<_mm512_mask_range_round_ps((v1), (k1), (v2), (v3), (e1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_range_ps macro k1, v1, v2, e1
	exitm<_mm512_maskz_range_round_ps((k1), (v1), (v2), (e1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_range_ps macro v1, v2, e1
	exitm<_mm512_maskz_range_ps(_MM_K0_REG, (v1), (v2), (e1))>
	endm


_mm512_madd_epi16 macro v1, v2
	exitm<_mm512_maskz_madd_epi16(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_maddubs_epi16 macro v1, v2
	exitm<_mm512_maskz_maddubs_epi16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_packs_epi16 macro v1, v2
	exitm<_mm512_maskz_packs_epi16(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_packs_epi32 macro v1, v2
	exitm<_mm512_maskz_packs_epi32(_MM_K0_REG64,(v1), (v2))>
	endm

_mm512_packus_epi16 macro v1, v2
	exitm<_mm512_maskz_packus_epi16(_MM_K0_REG64,(v1), (v2))>
	endm

_mm512_packus_epi32 macro v1, v2
	exitm<_mm512_maskz_packus_epi32(_MM_K0_REG64, (v1), (v2))>
	endm


_mm512_mask_rcp28_ps macro v1, k1, v2
	exitm<_mm512_mask_rcp28_round_ps((v1), (k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_rcp28_ps macro k1, v1
	exitm<_mm512_maskz_rcp28_round_ps((k1), (v1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_rcp28_round_ps macro v1, e1
	exitm<_mm512_maskz_rcp28_round_ps(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_rcp28_ps macro v1
	exitm<_mm512_maskz_rcp28_ps(_MM_K0_REG, (v1))>
	endm

_mm512_mask_rcp28_pd macro v1, k1, v2
	exitm<_mm512_mask_rcp28_round_pd((v1), (k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_rcp28_pd macro k1, v1
	exitm<_mm512_maskz_rcp28_round_pd((k1), (v1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_rcp28_round_pd macro v1, e1
	exitm<_mm512_maskz_rcp28_round_pd(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_rcp28_pd macro v1
	exitm<_mm512_maskz_rcp28_pd(_MM_K0_REG, (v1))>
	endm

_mm512_mask_rsqrt28_ps macro v1, k1, v2
	exitm<_mm512_mask_rsqrt28_round_ps((v1), (k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_rsqrt28_ps macro k1, v1
	exitm<_mm512_maskz_rsqrt28_round_ps((k1), (v1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_rsqrt28_round_ps macro v1, e1
	exitm<_mm512_maskz_rsqrt28_round_ps(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_rsqrt28_ps macro v1
	exitm<_mm512_maskz_rsqrt28_ps(_MM_K0_REG, (v1))>
	endm

_mm512_mask_rsqrt28_pd macro v1, k1, v2
	exitm<_mm512_mask_rsqrt28_round_pd((v1), (k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_rsqrt28_pd macro k1, v1
	exitm<_mm512_maskz_rsqrt28_round_pd((k1), (v1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_rsqrt28_round_pd macro v1, e1
	exitm<_mm512_maskz_rsqrt28_round_pd(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_rsqrt28_pd macro v1
	exitm<_mm512_maskz_rsqrt28_pd(_MM_K0_REG, (v1))>
	endm

_mm512_mask3_fmadd_ps macro v1, v2, v3, k3
	exitm<_mm512_mask3_fmadd_round_ps((v1), (v2), (v3), (k3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask3_fmadd_pd macro v1, v2, v3, k3
	exitm<_mm512_mask3_fmadd_round_pd((v1), (v2), (v3), (k3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask3_fmsub_ps macro v1, v2, v3, k3
	exitm<_mm512_mask3_fmsub_round_ps((v1), (v2), (v3), (k3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask3_fmsub_pd macro v1, v2, v3, k3
	exitm<_mm512_mask3_fmsub_round_pd((v1), (v2), (v3), (k3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask3_fnmadd_ps macro v1, v2, v3, k3
	exitm<_mm512_mask3_fnmadd_round_ps((v1), (v2), (v3), (k3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask3_fnmadd_pd macro v1, v2, v3, k3
	exitm<_mm512_mask3_fnmadd_round_pd((v1), (v2), (v3), (k3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask3_fnmsub_ps macro v1, v2, v3, k3
	exitm<_mm512_mask3_fnmsub_round_ps((v1), (v2), (v3), (k3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask3_fnmsub_pd macro v1, v2, v3, k3
	exitm<_mm512_mask3_fnmsub_round_pd((v1), (v2), (v3), (k3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask3_fmaddsub_ps macro v1, v2, v3, k3
	exitm<_mm512_mask3_fmaddsub_round_ps((v1), (v2), (v3), (k3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask3_fmaddsub_pd macro v1, v2, v3, k3
	exitm<_mm512_mask3_fmaddsub_round_pd((v1), (v2), (v3), (k3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask3_fmsubadd_ps macro v1, v2, v3, k3
	exitm<_mm512_mask3_fmsubadd_round_ps((v1), (v2), (v3), (k3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask3_fmsubadd_pd macro v1, v2, v3, k3
	exitm<_mm512_mask3_fmsubadd_round_pd((v1), (v2), (v3), (k3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_fmaddsub_ps macro v1, k1, v2, v3
	exitm<_mm512_mask_fmaddsub_round_ps((v1), (k1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_fmaddsub_ps macro k1, v1, v2, v3
	exitm<_mm512_maskz_fmaddsub_round_ps((k1), (v1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_fmaddsub_round_ps macro v1, v2, v3, e1
	exitm<_mm512_maskz_fmaddsub_round_ps(_MM_K0_REG, (v1), (v2), (v3), (e1))>
	endm

_mm512_fmaddsub_ps macro v1, v2, v3
	exitm<_mm512_maskz_fmaddsub_ps(_MM_K0_REG, (v1), (v2), (v3))>
	endm

_mm512_mask_fmaddsub_pd macro v1, k1, v2, v3
	exitm<_mm512_mask_fmaddsub_round_pd((v1), (k1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_fmaddsub_pd macro k1, v1, v2, v3
	exitm<_mm512_maskz_fmaddsub_round_pd((k1), (v1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_fmaddsub_round_pd macro v1, v2, v3, e1
	exitm<_mm512_maskz_fmaddsub_round_pd(_MM_K0_REG, (v1), (v2), (v3), (e1))>
	endm

_mm512_fmaddsub_pd macro v1, v2, v3
	exitm<_mm512_maskz_fmaddsub_pd(_MM_K0_REG, (v1), (v2), (v3))>
	endm

_mm512_mask_fmsubadd_ps macro v1, k1, v2, v3
	exitm<_mm512_mask_fmsubadd_round_ps((v1), (k1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_fmsubadd_ps macro k1, v1, v2, v3
	exitm<_mm512_maskz_fmsubadd_round_ps((k1), (v1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_fmsubadd_round_ps macro v1, v2, v3, e1
	exitm<_mm512_maskz_fmsubadd_round_ps(_MM_K0_REG, (v1), (v2), (v3), (e1))>
	endm

_mm512_fmsubadd_ps macro v1, v2, v3
	exitm<_mm512_maskz_fmsubadd_ps(_MM_K0_REG,(v1), (v2), (v3))>
	endm

_mm512_mask_fmsubadd_pd macro v1, k1, v2, v3
	exitm<_mm512_mask_fmsubadd_round_pd((v1), (k1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_fmsubadd_pd macro k1, v1, v2, v3
	exitm<_mm512_maskz_fmsubadd_round_pd((k1), (v1), (v2), (v3), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_fmsubadd_round_pd macro v1, v2, v3, e1
	exitm<_mm512_maskz_fmsubadd_round_pd(_MM_K0_REG, (v1), (v2), (v3), (e1))>
	endm

_mm512_fmsubadd_pd macro v1, v2, v3
	exitm<_mm512_maskz_fmsubadd_pd(_MM_K0_REG, (v1), (v2), (v3))>
	endm

_mm512_cmp_epi8_mask macro v1, v2, e1
	exitm<_mm512_mask_cmp_epi8_mask(_MM_K0_REG64, (v1), (v2), (e1))>
	endm

_mm512_cmp_epi16_mask macro v1, v2, e1
	exitm<_mm512_mask_cmp_epi16_mask(_MM_K0_REG64, (v1), (v2), (e1))>
	endm

_mm512_cmp_epi32_mask macro v1, v2, e1
	exitm<_mm512_mask_cmp_epi32_mask(_MM_K0_REG, (v1), (v2), (e1))>
	endm

_mm512_cmp_epi64_mask macro v1, v2, e1
	exitm<_mm512_mask_cmp_epi64_mask(_MM_K0_REG, (v1), (v2), (e1))>
	endm

_mm512_cmp_epu8_mask macro v1, v2, e1
	exitm<_mm512_mask_cmp_epu8_mask(_MM_K0_REG64, (v1), (v2), (e1))>
	endm

_mm512_cmp_epu16_mask macro v1, v2, e1
	exitm<_mm512_mask_cmp_epu16_mask(_MM_K0_REG64, (v1), (v2), (e1))>
	endm

_mm512_cmp_epu32_mask macro v1, v2, e1
	exitm<_mm512_mask_cmp_epu32_mask(_MM_K0_REG,(v1), (v2), (e1))>
	endm

_mm512_cmp_epu64_mask macro v1, v2, e1
	exitm<_mm512_mask_cmp_epu64_mask(_MM_K0_REG, (v1), (v2), (e1))>
	endm

_mm512_cmpeq_epi32_mask macro v1, v2
	exitm<_mm512_cmp_epi32_mask((v1),(v2), _MM_CMPINT_EQ)>
	endm

_mm512_mask_cmpeq_epi32_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi32_mask((k1), (v1), (v2), _MM_CMPINT_EQ)>
	endm

_mm512_cmplt_epi32_mask macro v1, v2
	exitm<_mm512_cmp_epi32_mask((v1), (v2), _MM_CMPINT_LT)>
	endm

_mm512_mask_cmplt_epi32_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi32_mask((k1), (v1), (v2), _MM_CMPINT_LT)>
	endm

_mm512_cmple_epi32_mask macro v1, v2
	exitm<_mm512_cmp_epi32_mask((v1),(v2), _MM_CMPINT_LE)>
	endm

_mm512_mask_cmple_epi32_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi32_mask((k1), (v1), (v2), _MM_CMPINT_LE)>
	endm

_mm512_cmpneq_epi32_mask macro v1, v2
	exitm<_mm512_cmp_epi32_mask((v1), (v2), _MM_CMPINT_NE)>
	endm

_mm512_mask_cmpneq_epi32_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi32_mask((k1), (v1), (v2), _MM_CMPINT_NE)>
	endm

_mm512_cmpge_epi32_mask macro v1, v2
	exitm<_mm512_cmp_epi32_mask((v1), (v2), _MM_CMPINT_GE)>
	endm

_mm512_mask_cmpge_epi32_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi32_mask((k1), (v1), (v2), _MM_CMPINT_GE)>
	endm

_mm512_cmpgt_epi32_mask macro v1, v2
	exitm<_mm512_cmp_epi32_mask((v1), (v2), _MM_CMPINT_GT)>
	endm

_mm512_mask_cmpgt_epi32_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi32_mask((k1), (v1), (v2), _MM_CMPINT_GT)>
	endm

_mm512_cmpeq_epu32_mask macro v1, v2
	exitm<_mm512_cmp_epu32_mask((v1), (v2), _MM_CMPINT_EQ)>
	endm

_mm512_mask_cmpeq_epu32_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu32_mask((k1), (v1), (v2), _MM_CMPINT_EQ)>
	endm

_mm512_cmplt_epu32_mask macro v1, v2
	exitm<_mm512_cmp_epu32_mask((v1), (v2), _MM_CMPINT_LT)>
	endm

_mm512_mask_cmplt_epu32_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu32_mask((k1), (v1), (v2), _MM_CMPINT_LT)>
	endm

_mm512_cmple_epu32_mask macro v1, v2
	exitm<_mm512_cmp_epu32_mask((v1), (v2), _MM_CMPINT_LE)>
	endm

_mm512_mask_cmple_epu32_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu32_mask((k1), (v1), (v2), _MM_CMPINT_LE)>
	endm

_mm512_cmpneq_epu32_mask macro v1, v2
	exitm<_mm512_cmp_epu32_mask((v1), (v2), _MM_CMPINT_NE)>
	endm

_mm512_mask_cmpneq_epu32_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu32_mask((k1), (v1), (v2), _MM_CMPINT_NE)>
	endm

_mm512_cmpge_epu32_mask macro v1, v2
	exitm<_mm512_cmp_epu32_mask((v1), (v2), _MM_CMPINT_GE)>
	endm

_mm512_mask_cmpge_epu32_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu32_mask((k1), (v1), (v2), _MM_CMPINT_GE)>
	endm

_mm512_cmpgt_epu32_mask macro v1, v2
	exitm<_mm512_cmp_epu32_mask((v1), (v2), _MM_CMPINT_GT)>
	endm

_mm512_mask_cmpgt_epu32_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu32_mask((k1), (v1), (v2), _MM_CMPINT_GT)>
	endm

_mm512_cmpeq_epi64_mask macro v1, v2
	exitm<_mm512_cmp_epi64_mask((v1), (v2), _MM_CMPINT_EQ)>
	endm

_mm512_mask_cmpeq_epi64_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi64_mask((k1), (v1), (v2), _MM_CMPINT_EQ)>
	endm

_mm512_cmplt_epi64_mask macro v1, v2
	exitm<_mm512_cmp_epi64_mask((v1), (v2), _MM_CMPINT_LT)>
	endm

_mm512_mask_cmplt_epi64_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi64_mask((k1), (v1), (v2), _MM_CMPINT_LT)>
	endm

_mm512_cmple_epi64_mask macro v1, v2
	exitm<_mm512_cmp_epi64_mask((v1), (v2), _MM_CMPINT_LE)>
	endm

_mm512_mask_cmple_epi64_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi64_mask((k1), (v1), (v2), _MM_CMPINT_LE)>
	endm

_mm512_cmpgt_epi64_mask macro v1, v2
	exitm<_mm512_cmp_epi64_mask((v1), (v2), _MM_CMPINT_GT)>
	endm

_mm512_mask_cmpgt_epi64_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi64_mask((k1), (v1), (v2), _MM_CMPINT_GT)>
	endm

_mm512_cmpge_epi64_mask macro v1, v2
	exitm<_mm512_cmp_epi64_mask((v1), (v2), _MM_CMPINT_GE)>
	endm

_mm512_mask_cmpge_epi64_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi64_mask((k1), (v1), (v2), _MM_CMPINT_GE)>
	endm

_mm512_cmpneq_epi64_mask macro v1, v2
	exitm<_mm512_cmp_epi64_mask((v1), (v2), _MM_CMPINT_NE)>
	endm

_mm512_mask_cmpneq_epi64_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi64_mask((k1), (v1), (v2), _MM_CMPINT_NE)>
	endm

_mm512_cmpeq_epu64_mask macro v1, v2
	exitm<_mm512_cmp_epu64_mask((v1), (v2), _MM_CMPINT_EQ)>
	endm

_mm512_mask_cmpeq_epu64_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu64_mask((k1), (v1), (v2), _MM_CMPINT_EQ)>
	endm

_mm512_cmplt_epu64_mask macro v1, v2
	exitm<_mm512_cmp_epu64_mask((v1), (v2), _MM_CMPINT_LT)>
	endm

_mm512_mask_cmplt_epu64_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu64_mask((k1), (v1), (v2), _MM_CMPINT_LT)>
	endm

_mm512_cmple_epu64_mask macro v1, v2
	exitm<_mm512_cmp_epu64_mask((v1), (v2), _MM_CMPINT_LE)>
	endm

_mm512_mask_cmple_epu64_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu64_mask((k1), (v1), (v2), _MM_CMPINT_LE)>
	endm

_mm512_cmpgt_epu64_mask macro v1, v2
	exitm<_mm512_cmp_epu64_mask((v1), (v2), _MM_CMPINT_GT)>
	endm

_mm512_mask_cmpgt_epu64_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu64_mask((k1), (v1), (v2), _MM_CMPINT_GT)>
	endm

_mm512_cmpge_epu64_mask macro v1, v2
	exitm<_mm512_cmp_epu64_mask((v1), (v2), _MM_CMPINT_GE)>
	endm

_mm512_mask_cmpge_epu64_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu64_mask((k1), (v1), (v2), _MM_CMPINT_GE)>
	endm

_mm512_cmpneq_epu64_mask macro v1, v2
	exitm<_mm512_cmp_epu64_mask((v1), (v2), _MM_CMPINT_NE)>
	endm

_mm512_mask_cmpneq_epu64_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu64_mask((k1), (v1), (v2), _MM_CMPINT_NE)>
	endm


_mm512_cmpeq_epi8_mask macro v1, v2
	exitm<_mm512_cmp_epi8_mask((v1), (v2), _MM_CMPINT_EQ)>
	endm

_mm512_mask_cmpeq_epi8_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi8_mask((k1), (v1), (v2), _MM_CMPINT_EQ)>
	endm

_mm512_cmplt_epi8_mask macro v1, v2
	exitm<_mm512_cmp_epi8_mask((v1), (v2), _MM_CMPINT_LT)>
	endm

_mm512_mask_cmplt_epi8_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi8_mask((k1), (v1), (v2), _MM_CMPINT_LT)>
	endm

_mm512_cmple_epi8_mask macro v1, v2
	exitm<_mm512_cmp_epi8_mask((v1), (v2), _MM_CMPINT_LE)>
	endm

_mm512_mask_cmple_epi8_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi8_mask((k1), (v1), (v2), _MM_CMPINT_LE)>
	endm

_mm512_cmpgt_epi8_mask macro v1, v2
	exitm<_mm512_cmp_epi8_mask((v1), (v2), _MM_CMPINT_GT)>
	endm

_mm512_mask_cmpgt_epi8_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi8_mask((k1), (v1), (v2), _MM_CMPINT_GT)>
	endm

_mm512_cmpge_epi8_mask macro v1, v2
	exitm<_mm512_cmp_epi8_mask((v1), (v2), _MM_CMPINT_GE)>
	endm

_mm512_mask_cmpge_epi8_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi8_mask((k1),(v1), (v2), _MM_CMPINT_GE)>
	endm

_mm512_cmpneq_epi8_mask macro v1, v2
	exitm<_mm512_cmp_epi8_mask((v1), (v2), _MM_CMPINT_NE)>
	endm

_mm512_mask_cmpneq_epi8_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi8_mask((k1), (v1), (v2), _MM_CMPINT_NE)>
	endm

_mm512_cmpeq_epu8_mask macro v1, v2
	exitm<_mm512_cmp_epu8_mask((v1), (v2), _MM_CMPINT_EQ)>
	endm

_mm512_mask_cmpeq_epu8_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu8_mask((k1), (v1), (v2), _MM_CMPINT_EQ)>
	endm

_mm512_cmplt_epu8_mask macro v1, v2
	exitm<_mm512_cmp_epu8_mask((v1), (v2), _MM_CMPINT_LT)>
	endm

_mm512_mask_cmplt_epu8_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu8_mask((k1), (v1), (v2), _MM_CMPINT_LT)>
	endm

_mm512_cmple_epu8_mask macro v1, v2
	exitm<_mm512_cmp_epu8_mask((v1), (v2), _MM_CMPINT_LE)>
	endm

_mm512_mask_cmple_epu8_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu8_mask((k1), (v1), (v2), _MM_CMPINT_LE)>
	endm

_mm512_cmpgt_epu8_mask macro v1, v2
	exitm<_mm512_cmp_epu8_mask((v1), (v2), _MM_CMPINT_GT)>
	endm

_mm512_mask_cmpgt_epu8_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu8_mask((k1), (v1), (v2), _MM_CMPINT_GT)>
	endm

_mm512_cmpge_epu8_mask macro v1, v2
	exitm<_mm512_cmp_epu8_mask((v1), (v2), _MM_CMPINT_GE)>
	endm

_mm512_mask_cmpge_epu8_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu8_mask((k1), (v1), (v2), _MM_CMPINT_GE)>
	endm

_mm512_cmpneq_epu8_mask macro v1, v2
	exitm<_mm512_cmp_epu8_mask((v1), (v2), _MM_CMPINT_NE)>
	endm

_mm512_mask_cmpneq_epu8_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu8_mask((k1), (v1), (v2), _MM_CMPINT_NE)>
	endm

_mm512_cmpeq_epi16_mask macro v1, v2
	exitm<_mm512_cmp_epi16_mask((v1),(v2), _MM_CMPINT_EQ)>
	endm

_mm512_mask_cmpeq_epi16_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi16_mask((k1), (v1), (v2), _MM_CMPINT_EQ)>
	endm

_mm512_cmplt_epi16_mask macro v1, v2
	exitm<_mm512_cmp_epi16_mask((v1), (v2), _MM_CMPINT_LT)>
	endm

_mm512_mask_cmplt_epi16_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi16_mask((k1), (v1), (v2), _MM_CMPINT_LT)>
	endm

_mm512_cmple_epi16_mask macro v1, v2
	exitm<_mm512_cmp_epi16_mask((v1), (v2), _MM_CMPINT_LE)>
	endm

_mm512_mask_cmple_epi16_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi16_mask((k1), (v1), (v2), _MM_CMPINT_LE)>
	endm

_mm512_cmpgt_epi16_mask macro v1, v2
	exitm<_mm512_cmp_epi16_mask((v1), (v2), _MM_CMPINT_GT)>
	endm

_mm512_mask_cmpgt_epi16_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi16_mask((k1), (v1), (v2), _MM_CMPINT_GT)>
	endm

_mm512_cmpge_epi16_mask macro v1, v2
	exitm<_mm512_cmp_epi16_mask((v1), (v2), _MM_CMPINT_GE)>
	endm

_mm512_mask_cmpge_epi16_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi16_mask((k1), (v1), (v2), _MM_CMPINT_GE)>
	endm

_mm512_cmpneq_epi16_mask macro v1, v2
	exitm<_mm512_cmp_epi16_mask((v1), (v2), _MM_CMPINT_NE)>
	endm

_mm512_mask_cmpneq_epi16_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epi16_mask((k1), (v1), (v2), _MM_CMPINT_NE)>
	endm

_mm512_cmpeq_epu16_mask macro v1, v2
	exitm<_mm512_cmp_epu16_mask((v1), (v2), _MM_CMPINT_EQ)>
	endm

_mm512_mask_cmpeq_epu16_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu16_mask((k1), (v1), (v2), _MM_CMPINT_EQ)>
	endm

_mm512_cmplt_epu16_mask macro v1, v2
	exitm<_mm512_cmp_epu16_mask((v1), (v2), _MM_CMPINT_LT)>
	endm

_mm512_mask_cmplt_epu16_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu16_mask((k1), (v1), (v2), _MM_CMPINT_LT)>
	endm

_mm512_cmple_epu16_mask macro v1, v2
	exitm<_mm512_cmp_epu16_mask((v1), (v2), _MM_CMPINT_LE)>
	endm

_mm512_mask_cmple_epu16_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu16_mask((k1), (v1), (v2), _MM_CMPINT_LE)>
	endm

_mm512_cmpgt_epu16_mask macro v1, v2
	exitm<_mm512_cmp_epu16_mask((v1), (v2), _MM_CMPINT_GT)>
	endm

_mm512_mask_cmpgt_epu16_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu16_mask((k1), (v1), (v2), _MM_CMPINT_GT)>
	endm

_mm512_cmpge_epu16_mask macro v1, v2
	exitm<_mm512_cmp_epu16_mask((v1), (v2), _MM_CMPINT_GE)>
	endm

_mm512_mask_cmpge_epu16_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu16_mask((k1), (v1), (v2), _MM_CMPINT_GE)>
	endm

_mm512_cmpneq_epu16_mask macro v1, v2
	exitm<_mm512_cmp_epu16_mask((v1), (v2), _MM_CMPINT_NE)>
	endm

_mm512_mask_cmpneq_epu16_mask macro k1, v1, v2
	exitm<_mm512_mask_cmp_epu16_mask((k1), (v1), (v2), _MM_CMPINT_NE)>
	endm

_mm512_test_epi8_mask macro v1, v2
	exitm<_mm512_mask_test_epi8_mask(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_test_epi16_mask macro v1, v2
	exitm<_mm512_mask_test_epi16_mask(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_testn_epi8_mask macro v1, v2
	exitm<_mm512_mask_testn_epi8_mask(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_testn_epi16_mask macro v1, v2
	exitm<_mm512_mask_testn_epi16_mask(_MM_K0_REG64, (v1), (v2))>
	endm

_mm512_test_epi32_mask macro v1, v2
	exitm<_mm512_mask_test_epi32_mask(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_test_epi64_mask macro v1, v2
	exitm<_mm512_mask_test_epi64_mask(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_testn_epi32_mask macro v1, v2
	exitm<_mm512_mask_testn_epi32_mask(_MM_K0_REG, (v1), (v2))>
	endm

_mm512_testn_epi64_mask macro v1, v2
	exitm<_mm512_mask_testn_epi64_mask(_MM_K0_REG, (v1), (v2))>
	endm


_mm512_kmov macro m
	exitm<m>
	endm
_mm512_mask2int macro m
	exitm<m>
	endm
_mm512_int2mask macro i
	exitm<i>
	endm
_mm512_kortestz macro m1, m2
	exitm<(_mm512_testz_or_mask16((m1), (m2)))>
	endm
_mm512_kortestc macro m1, m2
	exitm<(_mm512_testz_nor_mask16((m1), (m2)))>
	endm
_mm512_undefined_epi32 macro
	exitm<_mm512_castps_si512(_mm512_undefined())>
	endm

_mm512_i32logather_epi64 macro index, ad, scale
	exitm<_mm512_i32gather_epi64(_mm512_castsi512_si256(index),(ad), (scale))>
	endm

_mm512_mask_i32logather_epi64 macro v1, k1, index, addr, scale
	exitm<_mm512_mask_i32gather_epi64((v1), (k1), _mm512_castsi512_si256(index), (addr), (scale))>
	endm

_mm512_i32logather_pd macro index, addr, scale
	exitm<_mm512_i32gather_pd(_mm512_castsi512_si256(index),(addr), (scale))>
	endm

_mm512_mask_i32logather_pd macro v1, k1, index, addr, scale
	exitm<_mm512_mask_i32gather_pd((v1),(k1), _mm512_castsi512_si256(index), (addr), (scale))>
	endm

_mm512_i32loscatter_pd macro addr, index, v1, scale
	exitm<_mm512_i32scatter_pd((addr), _mm512_castsi512_si256(index), (v1), (scale))>
	endm

_mm512_mask_i32loscatter_pd macro addr, k1, index, v1, scale
	exitm<_mm512_mask_i32scatter_pd((addr), (k1), _mm512_castsi512_si256(index), (v1), (scale))>
	endm


_mm512_cvtepi32_pd macro v1
	exitm<_mm512_maskz_cvtepi32_pd(_MM_K0_REG, (v1))>
	endm

_mm512_cvtepu32_pd macro v1
	exitm<_mm512_maskz_cvtepu32_pd(_MM_K0_REG, (v1))>
	endm


_mm512_cvt_roundepi32_ps macro v1, e1
	exitm<_mm512_maskz_cvt_roundepi32_ps(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_cvt_roundepu32_ps macro v1, e1
	exitm<_mm512_maskz_cvt_roundepu32_ps(_MM_K0_REG,(v1), (e1))>
	endm

_mm512_cvt_roundph_ps macro v1, e1
	exitm<_mm512_maskz_cvt_roundph_ps(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_cvt_roundps_ph macro v1, e1
	exitm<_mm512_maskz_cvt_roundps_ph(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_cvt_roundepi64_ps macro v1, e1
	exitm<_mm512_maskz_cvt_roundepi64_ps(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_cvt_roundepu64_ps macro v1, e1
	exitm<_mm512_maskz_cvt_roundepu64_ps(_MM_K0_REG, (v1), (e1))>
	endm


_mm512_cvtepi8_epi32 macro v1
	exitm<_mm512_maskz_cvtepi8_epi32(_MM_K0_REG, (v1))>
	endm

_mm512_cvtepi8_epi64 macro v1
	exitm<_mm512_maskz_cvtepi8_epi64(_MM_K0_REG, (v1))>
	endm

_mm512_cvtepi16_epi32 macro v1
	exitm<_mm512_maskz_cvtepi16_epi32(_MM_K0_REG, (v1))>
	endm

_mm512_cvtepi16_epi64 macro v1
	exitm<_mm512_maskz_cvtepi16_epi64(_MM_K0_REG, (v1))>
	endm

_mm512_cvtepi32_epi8 macro v1
	exitm<_mm512_maskz_cvtepi32_epi8(_MM_K0_REG, (v1))>
	endm

_mm512_cvtsepi32_epi8 macro v1
	exitm<_mm512_maskz_cvtsepi32_epi8(_MM_K0_REG, (v1))>
	endm

_mm512_cvtusepi32_epi8 macro v1
	exitm<_mm512_maskz_cvtusepi32_epi8(_MM_K0_REG, (v1))>
	endm

_mm512_cvtepi32_epi16 macro v1
	exitm<_mm512_maskz_cvtepi32_epi16(_MM_K0_REG, (v1))>
	endm

_mm512_cvtsepi32_epi16 macro v1
	exitm<_mm512_maskz_cvtsepi32_epi16(_MM_K0_REG, (v1))>
	endm

_mm512_cvtusepi32_epi16 macro v1
	exitm<_mm512_maskz_cvtusepi32_epi16(_MM_K0_REG, (v1))>
	endm

_mm512_cvtepi32_epi64 macro v1
	exitm<_mm512_maskz_cvtepi32_epi64(_MM_K0_REG, (v1))>
	endm

_mm512_cvtepi64_epi8 macro v1
	exitm<_mm512_maskz_cvtepi64_epi8(_MM_K0_REG, (v1))>
	endm

_mm512_cvtsepi64_epi8 macro v1
	exitm<_mm512_maskz_cvtsepi64_epi8(_MM_K0_REG, (v1))>
	endm

_mm512_cvtusepi64_epi8 macro v1
	exitm<_mm512_maskz_cvtusepi64_epi8(_MM_K0_REG, (v1))>
	endm

_mm512_cvtepi64_epi16 macro v1
	exitm<_mm512_maskz_cvtepi64_epi16(_MM_K0_REG, (v1))>
	endm

_mm512_cvtsepi64_epi16 macro v1
	exitm<_mm512_maskz_cvtsepi64_epi16(_MM_K0_REG, (v1))>
	endm

_mm512_cvtusepi64_epi16 macro v1
	exitm<_mm512_maskz_cvtusepi64_epi16(_MM_K0_REG, (v1))>
	endm

_mm512_cvtepi64_epi32 macro v1
	exitm<_mm512_maskz_cvtepi64_epi32(_MM_K0_REG, (v1))>
	endm

_mm512_cvtsepi64_epi32 macro v1
	exitm<_mm512_maskz_cvtsepi64_epi32(_MM_K0_REG, (v1))>
	endm

_mm512_cvtusepi64_epi32 macro v1
	exitm<_mm512_maskz_cvtusepi64_epi32(_MM_K0_REG, (v1))>
	endm

_mm512_cvtepu8_epi32 macro v1
	exitm<_mm512_maskz_cvtepu8_epi32(_MM_K0_REG, (v1))>
	endm

_mm512_cvtepu8_epi64 macro v1
	exitm<_mm512_maskz_cvtepu8_epi64(_MM_K0_REG, (v1))>
	endm

_mm512_cvtepu16_epi32 macro v1
	exitm<_mm512_maskz_cvtepu16_epi32(_MM_K0_REG, (v1))>
	endm

_mm512_cvtepu16_epi64 macro v1
	exitm<_mm512_maskz_cvtepu16_epi64(_MM_K0_REG, (v1))>
	endm

_mm512_cvtepu32_epi64 macro v1
	exitm<_mm512_maskz_cvtepu32_epi64(_MM_K0_REG, (v1))>
	endm

_mm512_cvt_roundps_epi32 macro v1, e1
	exitm<_mm512_maskz_cvt_roundps_epi32(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_cvtt_roundps_epi32 macro v1, e1
	exitm<_mm512_maskz_cvtt_roundps_epi32(_MM_K0_REG,(v1), (e1))>
	endm

_mm512_cvt_roundps_epu32 macro v1, e1
	exitm<_mm512_maskz_cvt_roundps_epu32(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_cvtt_roundps_epu32 macro v1, e1
	exitm<_mm512_maskz_cvtt_roundps_epu32(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_cvt_roundpd_epi32 macro v1, e1
	exitm<_mm512_maskz_cvt_roundpd_epi32(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_cvtt_roundpd_epi32 macro v1, e1
	exitm<_mm512_maskz_cvtt_roundpd_epi32(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_cvt_roundpd_epu32 macro v1, e1
	exitm<_mm512_maskz_cvt_roundpd_epu32(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_cvtt_roundpd_epu32 macro v1, e1
	exitm<_mm512_maskz_cvtt_roundpd_epu32(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_cvtepi8_epi16 macro v1
	exitm<_mm512_maskz_cvtepi8_epi16(_MM_K0_REG64, (v1))>
	endm

_mm512_cvtepu8_epi16 macro v1
	exitm<_mm512_maskz_cvtepu8_epi16(_MM_K0_REG64, (v1))>
	endm

_mm512_cvtepi16_epi8 macro v1
	exitm<_mm512_maskz_cvtepi16_epi8(_MM_K0_REG64, (v1))>
	endm

_mm512_cvtsepi16_epi8 macro v1
	exitm<_mm512_maskz_cvtsepi16_epi8(_MM_K0_REG64, (v1))>
	endm

_mm512_cvtusepi16_epi8 macro v1
	exitm<_mm512_maskz_cvtusepi16_epi8(_MM_K0_REG64, (v1))>
	endm

_mm512_cvt_roundepi64_pd macro v1, e1
	exitm<_mm512_maskz_cvt_roundepi64_pd(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_cvt_roundepu64_pd macro v1, e1
	exitm<_mm512_maskz_cvt_roundepu64_pd(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_cvt_roundpd_epi64 macro v1, e1
	exitm<_mm512_maskz_cvt_roundpd_epi64(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_cvt_roundpd_epu64 macro v1, e1
	exitm<_mm512_maskz_cvt_roundpd_epu64(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_cvtt_roundpd_epi64 macro v1, e1
	exitm<_mm512_maskz_cvtt_roundpd_epi64(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_cvtt_roundpd_epu64 macro v1, e1
	exitm<_mm512_maskz_cvtt_roundpd_epu64(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_cvt_roundps_epi64 macro v1, e1
	exitm<_mm512_maskz_cvt_roundps_epi64(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_cvt_roundps_epu64 macro v1, e1
	exitm<_mm512_maskz_cvt_roundps_epu64(_MM_K0_REG, (v1), (e1))>
	endm

_mm512_cvtt_roundps_epi64 macro v1, e1
	exitm<_mm512_maskz_cvtt_roundps_epi64(_MM_K0_REG,(v1), (e1))>
	endm

_mm512_cvtt_roundps_epu64 macro v1, e1
	exitm<_mm512_maskz_cvtt_roundps_epu64(_MM_K0_REG, (v1), (e1))>
	endm


_mm512_cvtepi32_ps macro v
	exitm<_mm512_cvt_roundepi32_ps((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvtepi32_ps macro v1, k1, v2
	exitm<_mm512_mask_cvt_roundepi32_ps((v1), (k1), (v2),>
	endm

_mm512_maskz_cvtepi32_ps macro k1, v2
	exitm<_mm512_maskz_cvt_roundepi32_ps((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvtepu32_ps macro v
	exitm<_mm512_cvt_roundepu32_ps((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvtepu32_ps macro v1, k1, v2
	exitm<_mm512_mask_cvt_roundepu32_ps((v1), (k1), (v2),>
	endm

_mm512_maskz_cvtepu32_ps macro k1, v2
	exitm<_mm512_maskz_cvt_roundepu32_ps((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvtps_epi32 macro v
	exitm<_mm512_cvt_roundps_epi32((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvtps_epi32 macro v1, k1, v2
	exitm<_mm512_mask_cvt_roundps_epi32((v1), (k1), (v2),>
	endm

_mm512_maskz_cvtps_epi32 macro k1, v2
	exitm<_mm512_maskz_cvt_roundps_epi32((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvttps_epi32 macro v
	exitm<_mm512_cvtt_roundps_epi32((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvttps_epi32 macro v1, k1, v2
	exitm<_mm512_mask_cvtt_roundps_epi32((v1), (k1), (v2),>
	endm

_mm512_maskz_cvttps_epi32 macro k1, v2
	exitm<_mm512_maskz_cvtt_roundps_epi32((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvtps_epu32 macro v
	exitm<_mm512_cvt_roundps_epu32((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvtps_epu32 macro v1, k1, v2
	exitm<_mm512_mask_cvt_roundps_epu32((v1), (k1), (v2),>
	endm

_mm512_maskz_cvtps_epu32 macro k1, v2
	exitm<_mm512_maskz_cvt_roundps_epu32((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvttps_epu32 macro v
	exitm<_mm512_cvtt_roundps_epu32((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvttps_epu32 macro v1, k1, v2
	exitm<_mm512_mask_cvtt_roundps_epu32((v1), (k1), (v2),>
	endm

_mm512_maskz_cvttps_epu32 macro k1, v2
	exitm<_mm512_maskz_cvtt_roundps_epu32((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvtpd_epi32 macro v
	exitm<_mm512_cvt_roundpd_epi32((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvtpd_epi32 macro v1, k1, v2
	exitm<_mm512_mask_cvt_roundpd_epi32((v1), (k1), (v2),>
	endm

_mm512_maskz_cvtpd_epi32 macro k1, v2
	exitm<_mm512_maskz_cvt_roundpd_epi32((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvttpd_epi32 macro v
	exitm<_mm512_cvtt_roundpd_epi32((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvttpd_epi32 macro v1, k1, v2
	exitm<_mm512_mask_cvtt_roundpd_epi32((v1), (k1), (v2),>
	endm

_mm512_maskz_cvttpd_epi32 macro k1, v2
	exitm<_mm512_maskz_cvtt_roundpd_epi32((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvtpd_epu32 macro v
	exitm<_mm512_cvt_roundpd_epu32((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvtpd_epu32 macro v1, k1, v2
	exitm<_mm512_mask_cvt_roundpd_epu32((v1),(k1), (v2),>
	endm

_mm512_maskz_cvtpd_epu32 macro k1, v2
	exitm<_mm512_maskz_cvt_roundpd_epu32((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvttpd_epu32 macro v
	exitm<_mm512_cvtt_roundpd_epu32((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvttpd_epu32 macro v1, k1, v2
	exitm<_mm512_mask_cvtt_roundpd_epu32((v1), (k1), (v2),>
	endm

_mm512_maskz_cvttpd_epu32 macro k1, v2
	exitm<_mm512_maskz_cvtt_roundpd_epu32((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvtph_ps macro v1
	exitm<_mm512_cvt_roundph_ps((v1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvtph_ps macro v1, k, v2
	exitm<_mm512_mask_cvt_roundph_ps((v1), (k), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_maskz_cvtph_ps macro k, v1
	exitm<_mm512_maskz_cvt_roundph_ps((k), (v1), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvtps_ph macro v1, a
	exitm<_mm512_cvt_roundps_ph((v1), (a))>
	endm

_mm512_mask_cvtps_ph macro v1, k, v2, a
	exitm<_mm512_mask_cvt_roundps_ph((v1), (k), (v2), (a))>
	endm

_mm512_maskz_cvtps_ph macro k, v2, a
	exitm<_mm512_maskz_cvt_roundps_ph((k), (v2), (a))>
	endm

_mm512_cvtepi64_pd macro v
	exitm<_mm512_cvt_roundepi64_pd((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvtepi64_pd macro v1, k1, v2
	exitm<_mm512_mask_cvt_roundepi64_pd((v1), (k1), (v2),>
	endm

_mm512_maskz_cvtepi64_pd macro k1, v2
	exitm<_mm512_maskz_cvt_roundepi64_pd((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvtepu64_pd macro v
	exitm<_mm512_cvt_roundepu64_pd((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvtepu64_pd macro v1, k1, v2
	exitm<_mm512_mask_cvt_roundepu64_pd((v1), (k1), (v2),>
	endm

_mm512_maskz_cvtepu64_pd macro k1, v2
	exitm<_mm512_maskz_cvt_roundepu64_pd((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvtpd_epi64 macro v
	exitm<_mm512_cvt_roundpd_epi64((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvtpd_epi64 macro v1, k1, v2
	exitm<_mm512_mask_cvt_roundpd_epi64((v1), (k1), (v2),>
	endm

_mm512_maskz_cvtpd_epi64 macro k1, v2
	exitm<_mm512_maskz_cvt_roundpd_epi64((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvtpd_epu64 macro v
	exitm<_mm512_cvt_roundpd_epu64((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvtpd_epu64 macro v1, k1, v2
	exitm<_mm512_mask_cvt_roundpd_epu64((v1), (k1), (v2),>
	endm

_mm512_maskz_cvtpd_epu64 macro k1, v2
	exitm<_mm512_maskz_cvt_roundpd_epu64((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvttpd_epi64 macro v
	exitm<_mm512_cvtt_roundpd_epi64((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvttpd_epi64 macro v1, k1, v2
	exitm<_mm512_mask_cvtt_roundpd_epi64((v1), (k1), (v2),>
	endm

_mm512_maskz_cvttpd_epi64 macro k1, v2
	exitm<_mm512_maskz_cvtt_roundpd_epi64((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm


_mm512_cvttpd_epu64 macro v
	exitm<_mm512_cvtt_roundpd_epu64((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvttpd_epu64 macro v1, k1, v2
	exitm<_mm512_mask_cvtt_roundpd_epu64((v1), (k1), (v2),>
	endm

_mm512_maskz_cvttpd_epu64 macro k1, v2
	exitm<_mm512_maskz_cvtt_roundpd_epu64((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvtps_epi64 macro v
	exitm<_mm512_cvt_roundps_epi64((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvtps_epi64 macro v1, k1, v2
	exitm<_mm512_mask_cvt_roundps_epi64((v1), (k1), (v2),>
	endm

_mm512_maskz_cvtps_epi64 macro k1, v2
	exitm<_mm512_maskz_cvt_roundps_epi64((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvtps_epu64 macro v
	exitm<_mm512_cvt_roundps_epu64((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvtps_epu64 macro v1, k1, v2
	exitm<_mm512_mask_cvt_roundps_epu64((v1), (k1), (v2),>
	endm

_mm512_maskz_cvtps_epu64 macro k1, v2
	exitm< _mm512_maskz_cvt_roundps_epu64((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvtepi64_ps macro v
	exitm< _mm512_cvt_roundepi64_ps((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvtepi64_ps macro v1, k1, v2
	exitm<_mm512_mask_cvt_roundepi64_ps((v1), (k1), (v2),>
	endm

_mm512_maskz_cvtepi64_ps macro k1, v2
	exitm<_mm512_maskz_cvt_roundepi64_ps((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvtepu64_ps macro v
	exitm<_mm512_cvt_roundepu64_ps((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvtepu64_ps macro v1, k1, v2
	exitm<_mm512_mask_cvt_roundepu64_ps((v1), (k1), (v2),>
	endm

_mm512_maskz_cvtepu64_ps macro k1, v2
	exitm<_mm512_maskz_cvt_roundepu64_ps((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvttps_epi64 macro v
	exitm<_mm512_cvtt_roundps_epi64((v), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_mask_cvttps_epi64 macro v1, k1, v2
	exitm<_mm512_mask_cvtt_roundps_epi64((v1), (k1), (v2))>
	endm

_mm512_maskz_cvttps_epi64 macro k1, v2
	exitm<_mm512_maskz_cvtt_roundps_epi64((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

_mm512_cvttps_epu64 macro v
	exitm<>
	endm

_mm512_mask_cvttps_epu64 macro v1, k1, v2
	exitm<_mm512_mask_cvtt_roundps_epu64((v1), (k1), (v2),>
	endm

_mm512_maskz_cvttps_epu64 macro k1, v2
	exitm<_mm512_maskz_cvtt_roundps_epu64((k1), (v2), _MM_FROUND_CUR_DIRECTION)>
	endm

endif
