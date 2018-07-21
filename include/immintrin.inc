ifndef _INCLUDED_IMM
_INCLUDED_IMM equ <>
.pragma list(push, 0)

ifndef _M_IX86
ifndef _M_X64
.err <This header is specific to X86 and X64 targets>
endif
endif
include wmmintrin.inc

__m256		union
m256_f32	real4 8 dup(?)
__m256		ends

__m256d		struc
m256d_f64	real8 4 dup(?)
__m256d		ends

__m256i		union
m256i_i8	sbyte 32 dup(?)
m256i_i16	sword 16 dup(?)
m256i_i32	sdword 8 dup(?)
m256i_i64	sqword 4 dup(?)
m256i_u8	db 32 dup(?)
m256i_u16	dw 16 dup(?)
m256i_u32	dd 8 dup(?)
m256i_u64	dq 4 dup(?)
__m256i		ends

_CMP_EQ_OQ		equ 0x00
_CMP_LT_OS		equ 0x01
_CMP_LE_OS		equ 0x02
_CMP_UNORD_Q		equ 0x03
_CMP_NEQ_UQ		equ 0x04
_CMP_NLT_US		equ 0x05
_CMP_NLE_US		equ 0x06
_CMP_ORD_Q		equ 0x07
_CMP_EQ_UQ		equ 0x08
_CMP_NGE_US		equ 0x09
_CMP_NGT_US		equ 0x0A
_CMP_FALSE_OQ		equ 0x0B
_CMP_NEQ_OQ		equ 0x0C
_CMP_GE_OS		equ 0x0D
_CMP_GT_OS		equ 0x0E
_CMP_TRUE_UQ		equ 0x0F
_CMP_EQ_OS		equ 0x10
_CMP_LT_OQ		equ 0x11
_CMP_LE_OQ		equ 0x12
_CMP_UNORD_S		equ 0x13
_CMP_NEQ_US		equ 0x14
_CMP_NLT_UQ		equ 0x15
_CMP_NLE_UQ		equ 0x16
_CMP_ORD_S		equ 0x17
_CMP_EQ_US		equ 0x18
_CMP_NGE_UQ		equ 0x19
_CMP_NGT_UQ		equ 0x1A
_CMP_FALSE_OS		equ 0x1B
_CMP_NEQ_OS		equ 0x1C
_CMP_GE_OQ		equ 0x1D
_CMP_GT_OQ		equ 0x1E
_CMP_TRUE_US		equ 0x1F

_mm256_add_pd		proto __cdecl :yword, :yword
_mm256_add_ps		proto __cdecl :yword, :yword
_mm256_addsub_pd	proto __cdecl :yword, :yword
_mm256_addsub_ps	proto __cdecl :yword, :yword
_mm256_and_pd		proto __cdecl :yword, :yword
_mm256_and_ps		proto __cdecl :yword, :yword
_mm256_andnot_pd	proto __cdecl :yword, :yword
_mm256_andnot_ps	proto __cdecl :yword, :yword
_mm256_blend_pd		proto __cdecl :yword, :yword, :sdword
_mm256_blend_ps		proto __cdecl :yword, :yword, :sdword
_mm256_blendv_pd	proto __cdecl :yword, :yword, :yword
_mm256_blendv_ps	proto __cdecl :yword, :yword, :yword
_mm256_div_pd		proto __cdecl :yword, :yword
_mm256_div_ps		proto __cdecl :yword, :yword
_mm256_dp_ps		proto __cdecl :yword, :yword, :sdword
_mm256_hadd_pd		proto __cdecl :yword, :yword
_mm256_hadd_ps		proto __cdecl :yword, :yword
_mm256_hsub_pd		proto __cdecl :yword, :yword
_mm256_hsub_ps		proto __cdecl :yword, :yword
_mm256_max_pd		proto __cdecl :yword, :yword
_mm256_max_ps		proto __cdecl :yword, :yword
_mm256_min_pd		proto __cdecl :yword, :yword
_mm256_min_ps		proto __cdecl :yword, :yword
_mm256_mul_pd		proto __cdecl :yword, :yword
_mm256_mul_ps		proto __cdecl :yword, :yword
_mm256_or_pd		proto __cdecl :yword, :yword
_mm256_or_ps		proto __cdecl :yword, :yword
_mm256_shuffle_pd	proto __cdecl :yword, :yword, :sdword
_mm256_shuffle_ps	proto __cdecl :yword, :yword, :sdword
_mm256_sub_pd		proto __cdecl :yword, :yword
_mm256_sub_ps		proto __cdecl :yword, :yword
_mm256_xor_pd		proto __cdecl :yword, :yword
_mm256_xor_ps		proto __cdecl :yword, :yword

_mm_cmp_pd macro a, b, imm
	cmppd a,b,imm
	retm<a>
	endm
_mm256_cmp_pd macro a, b, imm
	vcmppd a,b,imm
	retm<a>
	endm
_mm_cmp_ps macro a, b, imm
	cmpps a,b,imm
	retm<a>
	endm
_mm256_cmp_ps macro a, b, imm
	vcmpps a,b,imm
	retm<a>
	endm
_mm_cmp_sd macro a, b, imm
	cmpsd a,b,imm
	retm<a>
	endm
_mm_cmp_ss macro a, b, imm
	cmpss a,b,imm
	retm<a>
	endm

_mm_comi_sd		proto __cdecl :yword, :yword, :sdword
_mm_comi_ss		proto __cdecl :yword, :yword, :sdword
_mm256_cvtepi32_pd	proto __cdecl :yword
_mm256_cvtepi32_ps	proto __cdecl :yword
_mm256_cvtpd_ps		proto __cdecl :yword
_mm256_cvtps_epi32	proto __cdecl :yword
_mm256_cvtps_pd		proto __cdecl :yword
_mm256_cvttpd_epi32	proto __cdecl :yword
_mm256_cvtpd_epi32	proto __cdecl :yword
_mm256_cvttps_epi32	proto __cdecl :yword
_mm256_extractf128_ps	proto __cdecl :yword, :sdword
_mm256_extractf128_pd	proto __cdecl :yword, :sdword
_mm256_extractf128_si256 proto __cdecl :yword, :sdword
_mm256_zeroall		proto __cdecl
_mm256_zeroupper	proto __cdecl
_mm256_permutevar_ps	proto __cdecl :yword, :yword
_mm_permutevar_ps	proto __cdecl :yword, :yword
_mm256_permute_ps	proto __cdecl :yword, :sdword

ifdef _XM_NO_INTRINSICS_
_mm_permute_ps		proto __cdecl :oword, :sdword
else
_mm_permute_ps macro x:=<xmm0>, imm:req
	vpermilps x, x, imm
	retm<x>
	endm
endif

_mm256_permutevar_pd	proto __cdecl :yword, :yword
_mm_permutevar_pd	proto __cdecl :yword, :yword
_mm256_permute_pd	proto __cdecl :yword, :sdword
_mm_permute_pd		proto __cdecl :yword, :sdword
_mm256_permute2f128_ps	proto __cdecl :yword, :yword, :sdword
_mm256_permute2f128_pd	proto __cdecl :yword, :yword, :sdword
_mm256_permute2f128_si256 proto __cdecl :yword, :yword, :sdword
_mm256_broadcast_ss	proto __cdecl :ptr real4
_mm_broadcast_ss	proto __cdecl :ptr real4
_mm256_broadcast_sd	proto __cdecl :ptr real8
_mm256_broadcast_ps	proto __cdecl :ptr yword
_mm256_broadcast_pd	proto __cdecl :ptr yword
_mm256_insertf128_ps	proto __cdecl :yword, :yword, :sdword
_mm256_insertf128_pd	proto __cdecl :yword, :yword, :sdword
_mm256_insertf128_si256 proto __cdecl :yword, :yword, :sdword
_mm256_load_pd		proto __cdecl :ptr real8
_mm256_store_pd		proto __cdecl :ptr real8, :yword
_mm256_load_ps		proto __cdecl :ptr real4
_mm256_store_ps		proto __cdecl :ptr real4, :yword
_mm256_loadu_pd		proto __cdecl :ptr real8
_mm256_storeu_pd	proto __cdecl :ptr real8, :yword
_mm256_loadu_ps		proto __cdecl :ptr real4
_mm256_storeu_ps	proto __cdecl :ptr real4, :yword
_mm256_load_si256	proto __cdecl :ptr yword
_mm256_store_si256	proto __cdecl :ptr yword, :yword
_mm256_loadu_si256	proto __cdecl :ptr yword
_mm256_storeu_si256	proto __cdecl :ptr yword, :yword
_mm256_loadu2_m128 macro
	exitm<_mm256_set_m128(_mm_loadu_ps(hiaddr), _mm_loadu_ps(loaddr))>
	endm
_mm256_loadu2_m128d macro
	exitm<_mm256_set_m128d(_mm_loadu_pd(hiaddr), _mm_loadu_pd(loaddr))>
	endm
_mm256_loadu2_m128i macro
	exitm<_mm256_set_m128i(_mm_loadu_si128(hiaddr), _mm_loadu_si128(loaddr))>
	endm

_mm256_storeu2_m128 macro
	exitm<>
	endm
_mm256_storeu2_m128d macro
	exitm<>
	endm
_mm256_storeu2_m128i macro
	exitm<>
	endm

_mm256_maskload_pd	proto __cdecl :ptr, :yword
_mm256_maskstore_pd	proto __cdecl :ptr, :yword, :yword
_mm_maskload_pd		proto __cdecl :ptr, :yword
_mm_maskstore_pd	proto __cdecl :ptr, :yword, :yword

_mm256_maskload_ps	proto __cdecl :ptr, :yword
_mm256_maskstore_ps	proto __cdecl :ptr, :yword, :yword
_mm_maskload_ps		proto __cdecl :ptr, :yword
_mm_maskstore_ps	proto __cdecl :ptr, :yword, :yword

_mm256_moveldup_ps	proto __cdecl :yword
_mm256_movedup_pd	proto __cdecl :yword
_mm256_lddqu_si256	proto __cdecl :ptr
_mm256_stream_si256	proto __cdecl :ptr, :yword
_mm256_stream_pd	proto __cdecl :ptr, :yword
_mm256_stream_ps	proto __cdecl :ptr, :yword
_mm256_rcp_ps		proto __cdecl :yword
_mm256_rsqrt_ps		proto __cdecl :yword
_mm256_sqrt_pd		proto __cdecl :yword
_mm256_sqrt_ps		proto __cdecl :yword
_mm256_round_pd		proto __cdecl :yword, :sdword
_mm256_ceil_pd macro val
	exitm<_mm256_round_pd((val), _MM_FROUND_CEIL)>
	endm
_mm256_floor_pd macro val
	exitm<_mm256_round_pd((val), _MM_FROUND_FLOOR)>
	endm

_mm256_round_ps		proto :oword, :sdword
_mm256_ceil_ps macro val
	exitm<_mm256_round_ps((val), _MM_FROUND_CEIL)>
	endm
_mm256_floor_ps macro val
	exitm<_mm256_round_ps((val), _MM_FROUND_FLOOR)>
	endm

_mm256_unpackhi_pd	proto __cdecl :yword, :yword
_mm256_unpackhi_ps	proto __cdecl :yword, :yword
_mm256_unpacklo_pd	proto __cdecl :yword, :yword
_mm256_unpacklo_ps	proto __cdecl :yword, :yword
_mm256_testz_si256	proto __cdecl :yword, :yword

_mm256_test_all_zeros macro m, val
	exitm<_mm256_testz_si256((m), (val))>
	endm

_mm256_testc_si256	proto __cdecl :yword, :yword
_mm256_test_all_ones macro val
	exitm<_mm256_testc_si256((val), _mm256_cmpeq_epi32((val),(val)))>
	endm

_mm256_testnzc_si256	proto __cdecl :yword, :yword
_mm256_test_mix_ones_zeros macro m, val
	exitm<_mm256_testnzc_si256((m), (val))>
	endm

_mm256_testz_pd		proto __cdecl :yword, :yword
_mm256_testc_pd		proto __cdecl :yword, :yword
_mm256_testnzc_pd	proto __cdecl :yword, :yword
_mm_testz_pd		proto __cdecl :yword, :yword
_mm_testc_pd		proto __cdecl :yword, :yword
_mm_testnzc_pd		proto __cdecl :yword, :yword

_mm256_testz_ps		proto __cdecl :yword, :yword
_mm256_testc_ps		proto __cdecl :yword, :yword
_mm256_testnzc_ps	proto __cdecl :yword, :yword
_mm_testz_ps		proto __cdecl :yword, :yword
_mm_testc_ps		proto __cdecl :yword, :yword
_mm_testnzc_ps		proto __cdecl :yword, :yword

_mm256_movemask_pd	proto __cdecl :yword

_mm256_movemask_ps	proto __cdecl :yword

_mm256_setzero_pd	proto __cdecl
_mm256_setzero_ps	proto __cdecl
_mm256_setzero_si256	proto __cdecl

_mm256_set_pd		proto __cdecl :real8, :real8, :real8, :real8
_mm256_set_ps		proto __cdecl :real4, :real4, :real4, :real4, :real4, :real4, :real4, :real4
_mm256_set_epi8		proto __cdecl :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte,
				      :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte,
				      :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte,
				      :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte
_mm256_set_epi16	proto __cdecl :sword, :sword, :sword, :sword, :sword, :sword, :sword, :sword,
				      :sword, :sword, :sword, :sword, :sword, :sword, :sword, :sword
_mm256_set_epi32	proto __cdecl :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword
_mm256_set_epi64x	proto __cdecl :sqword, :sqword, :sqword, :sqword

_mm256_set_m128 macro
	exitm<_mm256_insertf128_ps(_mm256_castps128_ps256(lo), (hi), 0x1)>
	endm

_mm256_set_m128d macro
	exitm<_mm256_insertf128_pd(_mm256_castpd128_pd256(lo), (hi), 0x1)>
	endm

_mm256_set_m128i macro
	exitm<_mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 0x1)>
	endm

_mm256_setr_pd		proto __cdecl :real8, :real8, :real8, :real8
_mm256_setr_ps		proto __cdecl :real4, :real4, :real4, :real4, :real4, :real4, :real4, :real4
_mm256_setr_epi8	proto __cdecl :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte,
				      :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte,
				      :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte,
				      :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte
_mm256_setr_epi16	proto __cdecl :sword, :sword, :sword, :sword, :sword, :sword, :sword, :sword,
				      :sword, :sword, :sword, :sword, :sword, :sword, :sword, :sword
_mm256_setr_epi32	proto __cdecl :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword, :sdword
_mm256_setr_epi64x	proto __cdecl :sqword, :sqword, :sqword, :sqword

_mm256_setr_m128 macro lo, hi
	exitm<_mm256_set_m128((hi), (lo))>
	endm
_mm256_setr_m128d macro lo, hi
	exitm<_mm256_set_m128d((hi), (lo))>
	endm
_mm256_setr_m128i macro lo, hi
	exitm<_mm256_set_m128i((hi), (lo))>
	endm

_mm256_set1_pd		proto __cdecl :real8
_mm256_set1_ps		proto __cdecl :real4
_mm256_set1_epi8	proto __cdecl :sbyte
_mm256_set1_epi16	proto __cdecl :sword
_mm256_set1_epi32	proto __cdecl :sdword
_mm256_set1_epi64x	proto __cdecl :sqword

_mm256_castpd_ps	proto __cdecl :yword
_mm256_castps_pd	proto __cdecl :yword
_mm256_castps_si256	proto __cdecl :yword
_mm256_castpd_si256	proto __cdecl :yword
_mm256_castsi256_ps	proto __cdecl :yword
_mm256_castsi256_pd	proto __cdecl :yword
_mm256_castps256_ps128	proto __cdecl :yword
_mm256_castpd256_pd128	proto __cdecl :yword
_mm256_castsi256_si128	proto __cdecl :yword
_mm256_castps128_ps256	proto __cdecl :yword
_mm256_castpd128_pd256	proto __cdecl :yword
_mm256_castsi128_si256	proto __cdecl :yword

_mm_cvtph_ps		proto __cdecl :yword
_mm256_cvtph_ps		proto __cdecl :yword
_mm_cvtps_ph		proto __cdecl :yword, :sdword
_mm256_cvtps_ph		proto __cdecl :yword, :sdword

_mm_undefined_ps	equ <_mm_setzero_ps>
_mm_undefined_pd	equ <_mm_setzero_pd>
_mm_undefined_si128	equ <_mm_setzero_si128>
_mm256_undefined_ps	equ <_mm256_setzero_ps>
_mm256_undefined_pd	equ <_mm256_setzero_pd>
_mm256_undefined_si256	equ <_mm256_setzero_si256>

_XCR_XFEATURE_ENABLED_MASK equ 0

_xgetbv			proto __cdecl :sdword
_xsetbv			proto __cdecl :dword, :qword
_xsave			proto __cdecl :ptr, :qword
ifdef _M_X64
_xsave64		proto __cdecl :ptr, :qword
endif
_xsaveopt		proto __cdecl :ptr, :qword
ifdef _M_X64
_xsaveopt64		proto __cdecl :ptr, :qword
endif
_xsavec			proto __cdecl :ptr, :qword
ifdef _M_X64
_xsavec64		proto __cdecl :ptr, :qword
endif
_xrstor			proto __cdecl :ptr, :qword
ifdef _M_X64
_xrstor64		proto __cdecl :ptr, :qword
endif
_xsaves			proto __cdecl :ptr, :qword
ifdef _M_X64
_xsaves64		proto __cdecl :ptr, :qword
endif
_xrstors		proto __cdecl :ptr, :qword
ifdef _M_X64
_xrstors64		proto __cdecl :ptr, :qword
endif
_fxsave			proto __cdecl :ptr
ifdef _M_X64
_fxsave64		proto __cdecl :ptr
endif
_fxrstor		proto __cdecl :ptr
ifdef _M_X64
_fxrstor64		proto __cdecl :ptr
endif

_rdrand16_step		proto __cdecl :ptr
_rdrand32_step		proto __cdecl :ptr
ifdef _M_X64
_rdrand64_step		proto __cdecl :ptr
endif

ifdef _M_X64
_readfsbase_u32		proto __cdecl
_readgsbase_u32		proto __cdecl
_readfsbase_u64		proto __cdecl
_readgsbase_u64		proto __cdecl
_writefsbase_u32	proto __cdecl :dword
_writegsbase_u32	proto __cdecl :dword
_writefsbase_u64	proto __cdecl :qword
_writegsbase_u64	proto __cdecl :qword
endif

_mm_fmadd_ps		proto __cdecl :oword, :oword, :oword
_mm_fmadd_pd		proto __cdecl :oword, :oword, :oword
_mm_fmadd_ss		proto __cdecl :oword, :oword, :oword
_mm_fmadd_sd		proto __cdecl :oword, :oword, :oword
_mm_fmsub_ps		proto __cdecl :oword, :oword, :oword
_mm_fmsub_pd		proto __cdecl :oword, :oword, :oword
_mm_fmsub_ss		proto __cdecl :oword, :oword, :oword
_mm_fmsub_sd		proto __cdecl :oword, :oword, :oword
_mm_fnmadd_ps		proto __cdecl :oword, :oword, :oword
_mm_fnmadd_pd		proto __cdecl :oword, :oword, :oword
_mm_fnmadd_ss		proto __cdecl :oword, :oword, :oword
_mm_fnmadd_sd		proto __cdecl :oword, :oword, :oword
_mm_fnmsub_ps		proto __cdecl :oword, :oword, :oword
_mm_fnmsub_pd		proto __cdecl :oword, :oword, :oword
_mm_fnmsub_ss		proto __cdecl :oword, :oword, :oword
_mm_fnmsub_sd		proto __cdecl :oword, :oword, :oword

_mm256_fmadd_ps		proto __cdecl :yword, :yword, :yword
_mm256_fmadd_pd		proto __cdecl :yword, :yword, :yword
_mm256_fmsub_ps		proto __cdecl :yword, :yword, :yword
_mm256_fmsub_pd		proto __cdecl :yword, :yword, :yword
_mm256_fnmadd_ps	proto __cdecl :yword, :yword, :yword
_mm256_fnmadd_pd	proto __cdecl :yword, :yword, :yword
_mm256_fnmsub_ps	proto __cdecl :yword, :yword, :yword
_mm256_fnmsub_pd	proto __cdecl :yword, :yword, :yword

_mm_fmaddsub_ps		proto __cdecl :oword, :oword, :oword
_mm_fmaddsub_pd		proto __cdecl :oword, :oword, :oword
_mm_fmsubadd_ps		proto __cdecl :oword, :oword, :oword
_mm_fmsubadd_pd		proto __cdecl :oword, :oword, :oword

_mm256_fmaddsub_ps	proto __cdecl :yword, :yword, :yword
_mm256_fmaddsub_pd	proto __cdecl :yword, :yword, :yword
_mm256_fmsubadd_ps	proto __cdecl :yword, :yword, :yword
_mm256_fmsubadd_pd	proto __cdecl :yword, :yword, :yword

_mm256_cmpeq_epi8	proto __cdecl :yword, :yword
_mm256_cmpeq_epi16	proto __cdecl :yword, :yword
_mm256_cmpeq_epi32	proto __cdecl :yword, :yword
_mm256_cmpeq_epi64	proto __cdecl :yword, :yword

_mm256_cmpgt_epi8	proto __cdecl :yword, :yword
_mm256_cmpgt_epi16	proto __cdecl :yword, :yword
_mm256_cmpgt_epi32	proto __cdecl :yword, :yword
_mm256_cmpgt_epi64	proto __cdecl :yword, :yword

_mm256_max_epi8		proto __cdecl :yword, :yword
_mm256_max_epi16	proto __cdecl :yword, :yword
_mm256_max_epi32	proto __cdecl :yword, :yword
_mm256_max_epu8		proto __cdecl :yword, :yword
_mm256_max_epu16	proto __cdecl :yword, :yword
_mm256_max_epu32	proto __cdecl :yword, :yword

_mm256_min_epi8		proto __cdecl :yword, :yword
_mm256_min_epi16	proto __cdecl :yword, :yword
_mm256_min_epi32	proto __cdecl :yword, :yword
_mm256_min_epu8		proto __cdecl :yword, :yword
_mm256_min_epu16	proto __cdecl :yword, :yword
_mm256_min_epu32	proto __cdecl :yword, :yword

_mm256_and_si256	proto __cdecl :yword, :yword
_mm256_andnot_si256	proto __cdecl :yword, :yword
_mm256_or_si256		proto __cdecl :yword, :yword
_mm256_xor_si256	proto __cdecl :yword, :yword

_mm256_abs_epi8		proto __cdecl :yword
_mm256_abs_epi16	proto __cdecl :yword
_mm256_abs_epi32	proto __cdecl :yword

_mm256_add_epi8		proto __cdecl :yword, :yword
_mm256_add_epi16	proto __cdecl :yword, :yword
_mm256_add_epi32	proto __cdecl :yword, :yword
_mm256_add_epi64	proto __cdecl :yword, :yword

_mm256_adds_epi8	proto __cdecl :yword, :yword
_mm256_adds_epi16	proto __cdecl :yword, :yword
_mm256_adds_epu8	proto __cdecl :yword, :yword
_mm256_adds_epu16	proto __cdecl :yword, :yword

_mm256_sub_epi8		proto __cdecl :yword, :yword
_mm256_sub_epi16	proto __cdecl :yword, :yword
_mm256_sub_epi32	proto __cdecl :yword, :yword
_mm256_sub_epi64	proto __cdecl :yword, :yword

_mm256_subs_epi8	proto __cdecl :yword, :yword
_mm256_subs_epi16	proto __cdecl :yword, :yword
_mm256_subs_epu8	proto __cdecl :yword, :yword
_mm256_subs_epu16	proto __cdecl :yword, :yword

_mm256_avg_epu8		proto __cdecl :yword, :yword
_mm256_avg_epu16	proto __cdecl :yword, :yword
_mm256_hadd_epi16	proto __cdecl :yword, :yword
_mm256_hadd_epi32	proto __cdecl :yword, :yword
_mm256_hadds_epi16	proto __cdecl :yword, :yword
_mm256_hsub_epi16	proto __cdecl :yword, :yword

_mm256_hsub_epi32	proto __cdecl :yword, :yword
_mm256_hsubs_epi16	proto __cdecl :yword, :yword

_mm256_madd_epi16	proto __cdecl :yword, :yword
_mm256_maddubs_epi16	proto __cdecl :yword, :yword

_mm256_mulhi_epi16	proto __cdecl :yword, :yword
_mm256_mulhi_epu16	proto __cdecl :yword, :yword

_mm256_mullo_epi16	proto __cdecl :yword, :yword
_mm256_mullo_epi32	proto __cdecl :yword, :yword

_mm256_mul_epu32	proto __cdecl :yword, :yword
_mm256_mul_epi32	proto __cdecl :yword, :yword

_mm256_sign_epi8	proto __cdecl :yword, :yword
_mm256_sign_epi16	proto __cdecl :yword, :yword
_mm256_sign_epi32	proto __cdecl :yword, :yword

_mm256_mulhrs_epi16	proto __cdecl :yword, :yword

_mm256_sad_epu8		proto __cdecl :yword, :yword
_mm256_mpsadbw_epu8	proto __cdecl :yword, :yword, :sdword

_mm256_slli_si256	proto __cdecl :yword, :sdword
_mm256_bslli_epi128	equ <_mm256_slli_si256>
_mm256_srli_si256	proto __cdecl :yword, :sdword
_mm256_bsrli_epi128	equ <_mm256_srli_si256>

_mm256_sll_epi16	proto __cdecl :yword, :yword
_mm256_sll_epi32	proto __cdecl :yword, :yword
_mm256_sll_epi64	proto __cdecl :yword, :yword

_mm256_slli_epi16	proto __cdecl :yword, :sdword
_mm256_slli_epi32	proto __cdecl :yword, :sdword
_mm256_slli_epi64	proto __cdecl :yword, :sdword

_mm256_sllv_epi32	proto __cdecl :yword, :yword
_mm256_sllv_epi64	proto __cdecl :yword, :yword

_mm_sllv_epi32		proto __cdecl :oword, :oword
_mm_sllv_epi64		proto __cdecl :oword, :oword

_mm256_sra_epi16	proto __cdecl :yword, :oword
_mm256_sra_epi32	proto __cdecl :yword, :oword

_mm256_srai_epi16	proto __cdecl :yword, :sdword
_mm256_srai_epi32	proto __cdecl :yword, :sdword

_mm256_srav_epi32	proto __cdecl :yword, :yword

_mm_srav_epi32		proto __cdecl :oword, :oword

_mm256_srl_epi16	proto __cdecl :yword, :oword
_mm256_srl_epi32	proto __cdecl :yword, :oword
_mm256_srl_epi64	proto __cdecl :yword, :oword

_mm256_srli_epi16	proto __cdecl :yword, :sdword
_mm256_srli_epi32	proto __cdecl :yword, :sdword
_mm256_srli_epi64	proto __cdecl :yword, :sdword

_mm256_srlv_epi32	proto __cdecl :yword, :yword
_mm256_srlv_epi64	proto __cdecl :yword, :yword

_mm_srlv_epi32		proto __cdecl :oword, :oword
_mm_srlv_epi64		proto __cdecl :oword, :oword

_mm_blend_epi32		proto __cdecl :oword, :oword, :sdword
_mm256_blend_epi32	proto __cdecl :yword, :yword, :sdword
_mm256_alignr_epi8	proto __cdecl :yword, :yword, :sdword

_mm256_blendv_epi8	proto __cdecl :yword, :yword, :yword
_mm256_blend_epi16	proto __cdecl :yword, :yword, :sdword

_mm256_packs_epi16	proto __cdecl :yword, :yword
_mm256_packs_epi32	proto __cdecl :yword, :yword
_mm256_packus_epi16	proto __cdecl :yword, :yword
_mm256_packus_epi32	proto __cdecl :yword, :yword

_mm256_unpackhi_epi8	proto __cdecl :yword, :yword
_mm256_unpackhi_epi16	proto __cdecl :yword, :yword
_mm256_unpackhi_epi32	proto __cdecl :yword, :yword
_mm256_unpackhi_epi64	proto __cdecl :yword, :yword

_mm256_unpacklo_epi8	proto __cdecl :yword, :yword
_mm256_unpacklo_epi16	proto __cdecl :yword, :yword
_mm256_unpacklo_epi32	proto __cdecl :yword, :yword
_mm256_unpacklo_epi64	proto __cdecl :yword, :yword

_mm256_shuffle_epi8	proto __cdecl :yword, :yword
_mm256_shuffle_epi32	proto __cdecl :yword, :sdword

_mm256_shufflehi_epi16	proto __cdecl :yword, :sdword
_mm256_shufflelo_epi16	proto __cdecl :yword, :sdword

_mm256_extracti128_si256 proto __cdecl :yword, :sdword
_mm256_inserti128_si256 proto __cdecl :yword, :oword, :sdword

_mm_broadcastss_ps	proto __cdecl :oword
_mm_broadcastsd_pd	proto __cdecl :oword

_mm_broadcastb_epi8	proto __cdecl :oword
_mm_broadcastw_epi16	proto __cdecl :oword
_mm_broadcastd_epi32	proto __cdecl :oword
_mm_broadcastq_epi64	proto __cdecl :oword

_mm256_broadcastss_ps	proto __cdecl :oword
_mm256_broadcastsd_pd	proto __cdecl :oword

_mm256_broadcastb_epi8	proto __cdecl :oword
_mm256_broadcastw_epi16 proto __cdecl :oword
_mm256_broadcastd_epi32 proto __cdecl :oword
_mm256_broadcastq_epi64 proto __cdecl :oword

_mm256_broadcastsi128_si256 proto __cdecl :oword

_mm256_cvtepi8_epi16	proto __cdecl :oword
_mm256_cvtepi8_epi32	proto __cdecl :oword
_mm256_cvtepi8_epi64	proto __cdecl :oword
_mm256_cvtepi16_epi32	proto __cdecl :oword
_mm256_cvtepi16_epi64	proto __cdecl :oword
_mm256_cvtepi32_epi64	proto __cdecl :oword

_mm256_cvtepu8_epi16	proto __cdecl :oword
_mm256_cvtepu8_epi32	proto __cdecl :oword
_mm256_cvtepu8_epi64	proto __cdecl :oword
_mm256_cvtepu16_epi32	proto __cdecl :oword
_mm256_cvtepu16_epi64	proto __cdecl :oword
_mm256_cvtepu32_epi64	proto __cdecl :oword

_mm256_movemask_epi8	proto __cdecl :yword

_mm_maskload_epi32	proto __cdecl :ptr, :oword
_mm_maskload_epi64	proto __cdecl :ptr, :oword

_mm_maskstore_epi32	proto __cdecl :ptr, :oword, :oword
_mm_maskstore_epi64	proto __cdecl :ptr, :oword, :oword

_mm256_maskload_epi32	proto __cdecl :ptr, :yword
_mm256_maskload_epi64	proto __cdecl :ptr, :yword

_mm256_maskstore_epi32	proto __cdecl :ptr, :yword, :yword
_mm256_maskstore_epi64	proto __cdecl :ptr, :yword, :yword

_mm256_permutevar8x32_epi32 proto __cdecl :yword, :yword
_mm256_permutevar8x32_ps proto __cdecl :yword, :yword

_mm256_permute4x64_epi64 proto __cdecl :yword, :sdword
_mm256_permute4x64_pd	proto __cdecl :yword, :sdword

_mm256_permute2x128_si256 proto __cdecl :yword, :yword, :sdword

_mm256_stream_load_si256 proto __cdecl :ptr

_mm256_mask_i32gather_pd proto __cdecl :yword, :ptr, :oword, :yword, :sdword
_mm256_mask_i32gather_ps proto __cdecl :yword, :ptr, :yword, :yword, :sdword
_mm256_mask_i64gather_pd proto __cdecl :yword, :ptr, :yword, :yword, :sdword
_mm256_mask_i64gather_ps proto __cdecl :oword, :ptr, :yword, :oword, :sdword

_mm_mask_i32gather_pd	 proto __cdecl :oword, :ptr, :oword, :oword, :sdword
_mm_mask_i32gather_ps	 proto __cdecl :oword, :ptr, :oword, :oword, :sdword
_mm_mask_i64gather_pd	 proto __cdecl :oword, :ptr, :oword, :oword, :sdword
_mm_mask_i64gather_ps	 proto __cdecl :oword, :ptr, :oword, :oword, :sdword

_mm256_mask_i32gather_epi32 proto __cdecl :yword, :ptr, :yword, :yword, :sdword
_mm256_mask_i32gather_epi64 proto __cdecl :yword, :ptr, :oword, :yword, :sdword
_mm256_mask_i64gather_epi32 proto __cdecl :oword, :ptr, :yword, :oword, :sdword
_mm256_mask_i64gather_epi64 proto __cdecl :yword, :ptr, :yword, :yword, :sdword

_mm_mask_i32gather_epi32 proto __cdecl :oword, :ptr, :oword, :oword, :sdword
_mm_mask_i32gather_epi64 proto __cdecl :oword, :ptr, :oword, :oword, :sdword
_mm_mask_i64gather_epi32 proto __cdecl :oword, :ptr, :oword, :oword, :sdword
_mm_mask_i64gather_epi64 proto __cdecl :oword, :ptr, :oword, :oword, :sdword

_mm256_i32gather_pd	proto __cdecl :ptr, :oword, :sdword
_mm256_i32gather_ps	proto __cdecl :ptr, :yword, :sdword
_mm256_i64gather_pd	proto __cdecl :ptr, :yword, :sdword
_mm256_i64gather_p	proto __cdecl :ptr, :yword, :sdword

_mm_i32gather_pd	proto __cdecl :ptr, :oword, :sdword
_mm_i32gather_ps	proto __cdecl :ptr, :oword, :sdword
_mm_i64gather_pd	proto __cdecl :ptr, :oword, :sdword
_mm_i64gather_ps	proto __cdecl :ptr, :oword, :sdword

_mm256_i32gather_epi32	proto __cdecl :ptr, :yword, :sdword
_mm256_i32gather_epi64	proto __cdecl :ptr, :oword, :sdword
_mm256_i64gather_epi32	proto __cdecl :ptr, :yword, :sdword
_mm256_i64gather_epi64	proto __cdecl :ptr, :yword, :sdword

_mm_i32gather_epi32	proto __cdecl :ptr, :oword, :sdword
_mm_i32gather_epi64	proto __cdecl :ptr, :oword, :sdword
_mm_i64gather_epi32	proto __cdecl :ptr, :oword, :sdword
_mm_i64gather_epi64	proto __cdecl :ptr, :oword, :sdword

_bextr_u32		proto __cdecl :dword, :dword, :dword
_blsi_u32		proto __cdecl :dword
_blsmsk_u32		proto __cdecl :dword
_blsr_u32		proto __cdecl :dword
_bzhi_u32		proto __cdecl :dword, :dword
_mulx_u32		proto __cdecl :dword, :dword, :ptr
_pext_u32		proto __cdecl :dword, :dword
_rorx_u32		proto __cdecl :dword, :dword
_sarx_i32		proto __cdecl :sdword, :sdword
_shlx_u32		proto __cdecl :dword, :dword
_shrx_u32		proto __cdecl :dword, :dword

ifdef _M_X64
_bextr_u64		proto __cdecl :qword, :dword, :dword
_blsi_u64		proto __cdecl :qword
_blsmsk_u64		proto __cdecl :qword
_blsr_u64		proto __cdecl :qword
_bzhi_u64		proto __cdecl :qword, :dword
_mulx_u64		proto __cdecl :qword, :dword
_pdep_u64		proto __cdecl :qword, :dword
_pext_u64		proto __cdecl :qword, :dword
_rorx_u64		proto __cdecl :qword, :dword
_srx_i64		proto __cdecl :sqword, :sdword
_shlx_u64		proto __cdecl :qword, :dword
_shrx_u64		proto __cdecl :qword, :dword
endif

_lzcnt_u32		proto __cdecl :dword
ifdef _M_X64
_lzcnt_u64		proto __cdecl :qword
endif

_tzcnt_u32		proto __cdecl :dword
ifdef _M_X64
_tzcnt_u64		proto __cdecl :qword
endif

_invpcid		proto __cdecl :dword, :ptr

_Store_HLERelease	proto __cdecl :ptr, :sdword
_StorePointer_HLERelease proto __cdecl :ptr, :ptr

_InterlockedExchange_HLEAcquire proto __cdecl :ptr
_InterlockedExchange_HLERelease proto __cdecl :ptr, :sdword
_InterlockedExchangePointer_HLEAcquire proto __cdecl :ptr, :ptr
_InterlockedExchangePointer_HLERelease proto __cdecl :ptr, :ptr

_InterlockedCompareExchange_HLEAcquire proto __cdecl :ptr, :sdword, :sdword
_InterlockedCompareExchange_HLERelease proto __cdecl :ptr, :sdword, :sdword
_InterlockedCompareExchange64_HLEAcquire proto __cdecl :ptr, :sqword, :sqword
_InterlockedCompareExchange64_HLERelease proto __cdecl :ptr, :sqword, :sqword
_InterlockedCompareExchangePointer_HLEAcquire proto __cdecl :ptr, :ptr, :ptr
_InterlockedCompareExchangePointer_HLERelease proto __cdecl :ptr, :ptr, :ptr

_InterlockedExchangeAdd_HLEAcquire proto __cdecl :ptr, :sdword
_InterlockedExchangeAdd_HLERelease proto __cdecl :ptr, :sdword

_InterlockedAnd_HLEAcquire proto __cdecl :ptr, :sdword
_InterlockedAnd_HLERelease proto __cdecl :ptr, :sdword
_InterlockedOr_HLEAcquire proto __cdecl :ptr, :sdword
_InterlockedOr_HLERelease proto __cdecl :ptr, :sdword
_InterlockedXor_HLEAcquire proto __cdecl :ptr, :sdword
_InterlockedXor_HLERelease proto __cdecl :ptr, :sdword

_interlockedbittestandset_HLEAcquire proto __cdecl :ptr, :sdword
_interlockedbittestandset_HLERelease proto __cdecl :ptr, :sdword
_interlockedbittestandreset_HLEAcquire proto __cdecl :ptr, :sdword
_interlockedbittestandreset_HLERelease proto __cdecl :ptr, :sdword

ifdef _M_X64
_Store64_HLERelease	proto __cdecl :ptr, :sqword
_InterlockedExchange64_HLEAcquire proto __cdecl :ptr, :sqword
_InterlockedExchange64_HLERelease proto __cdecl :ptr, :sqword
_InterlockedExchangeAdd64_HLEAcquire proto __cdecl :ptr, :sqword
_InterlockedExchangeAdd64_HLERelease proto __cdecl :ptr, :sqword
_InterlockedAnd64_HLEAcquire proto __cdecl :ptr, :sqword
_InterlockedAnd64_HLERelease proto __cdecl :ptr, :sqword
_InterlockedOr64_HLEAcquire proto __cdecl :ptr, :sqword
_InterlockedOr64_HLERelease proto __cdecl :ptr, :sqword
_InterlockedXor64_HLEAcquire proto __cdecl :ptr, :sqword
_InterlockedXor64_HLERelease proto __cdecl :ptr, :sqword
_interlockedbittestandset64_HLEAcquire	proto __cdecl :ptr, :sqword
_interlockedbittestandset64_HLERelease	proto __cdecl :ptr, :sqword
_interlockedbittestandreset64_HLEAcquire proto __cdecl :ptr, :sqword
_interlockedbittestandreset64_HLERelease proto __cdecl :ptr, :sqword
endif

;;  Restricted Transactional Memory

_XBEGIN_STARTED		equ ( NOT 0)
_XABORT_EXPLICIT	equ (1 SHL 0)
_XABORT_RETRY		equ (1 SHL 1)
_XABORT_CONFLICT	equ (1 SHL 2)
_XABORT_CAPACITY	equ (1 SHL 3)
_XABORT_DEBUG		equ (1 SHL 4)
_XABORT_NESTED		equ (1 SHL 5)
_XABORT_CODE macro x
	exitm<((((x) SHR 24) AND 0xFF))>
	endm

_xbegin			proto __cdecl
_xend			proto __cdecl
_xabort			proto __cdecl :dword
_xtest			proto __cdecl

_rdseed16_step		proto __cdecl :ptr
_rdseed32_step		proto __cdecl :ptr
ifdef _M_X64
_rdseed64_step		proto __cdecl :ptr
endif
_addcarryx_u32		proto __cdecl :byte, :dword, :dword, :dword
ifdef _M_X64
_addcarryx_u64		proto __cdecl :byte, :qword, :qword, :qword
endif

_load_be_u16		proto __cdecl :ptr
_load_be_u32		proto __cdecl :ptr
_load_be_u64		proto __cdecl :ptr
_loadbe_i16 macro be_ptr
	exitm<_load_be_u16(be_ptr)>
	endm
_loadbe_i32 macro be_ptr
	exitm<_load_be_u32(be_ptr)>
	endm
_loadbe_i64 macro be_ptr
	exitm<_load_be_u64(be_ptr)>
	endm

_store_be_u16		proto __cdecl :ptr, :word
_store_be_u32		proto __cdecl :ptr, :dword
_store_be_u64		proto __cdecl :ptr, :qword
_storebe_i16 macro be_ptr, val
	exitm<_store_be_u16(be_ptr, (val))>
	endm
_storebe_i32 macro be_ptr, val
	exitm<_store_be_u32(be_ptr, (val))>
	endm
_storebe_i64 macro be_ptr, val
	exitm<_store_be_u64(be_ptr, (val))>
	endm

_mm_sha1msg1_epu32	proto __cdecl :oword, :oword
_mm_sha1msg2_epu32	proto __cdecl :oword, :oword
_mm_sha1nexte_epu32	proto __cdecl :oword, :oword
_mm_sha1rnds4_epu32	proto __cdecl :oword, :oword, :sdword

_mm_sha256msg1_epu32	proto __cdecl :oword, :oword
_mm_sha256msg2_epu32	proto __cdecl :oword, :oword
_mm_sha256rnds2_epu32	proto __cdecl :oword, :oword, :oword

_bnd_set_ptr_bounds	proto __cdecl :ptr, :size_t
_bnd_narrow_ptr_bounds	proto __cdecl :ptr, :ptr, :size_t
_bnd_copy_ptr_bounds	proto __cdecl :ptr, :ptr
_bnd_init_ptr_bounds	proto __cdecl :ptr
_bnd_store_ptr_bounds	proto __cdecl :ptr ptr, :ptr
_bnd_chk_ptr_lbounds	proto __cdecl :ptr
_bnd_chk_ptr_ubounds	proto __cdecl :ptr
_bnd_chk_ptr_bounds	proto __cdecl :ptr, :size_t
_bnd_load_ptr_bounds	proto __cdecl :ptr ptr, :ptr
_bnd_get_ptr_lbound	proto __cdecl :ptr
_bnd_get_ptr_ubound	proto __cdecl :ptr

_mm256_insert_epi8	proto __cdecl :yword, :sdword, :sdword
_mm256_insert_epi16	proto __cdecl :yword, :sdword, :sdword
_mm256_insert_epi32	proto __cdecl :yword, :sdword, :sdword
ifdef _M_X64
_mm256_insert_epi64	proto __cdecl :yword, :sqword, :sdword
endif

_mm256_extract_epi8	proto __cdecl :yword, :sdword
_mm256_extract_epi16	proto __cdecl :yword, :sdword
_mm256_extract_epi32	proto __cdecl :yword, :sdword
ifdef _M_X64
_mm256_extract_epi64	proto __cdecl :yword, :sdword
endif

include zmmintrin.inc

.pragma list(pop)
endif
