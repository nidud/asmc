ifndef _INCLUDED_SMM
_INCLUDED_SMM equ <>
.xlist
ifndef _M_IX86
ifndef _M_X64
.err <This header is specific to X86 and X64 targets>
endif
endif
ifdef _M_CEE_PURE
.err <ERROR: This file is not supported in the pure mode!>
endif
include tmmintrin.inc
.xlist

_MM_FROUND_TO_NEAREST_INT equ 0x00
_MM_FROUND_TO_NEG_INF	equ 0x01
_MM_FROUND_TO_POS_INF	equ 0x02
_MM_FROUND_TO_ZERO	equ 0x03
_MM_FROUND_CUR_DIRECTION equ 0x04

_MM_FROUND_RAISE_EXC	equ 0x00
_MM_FROUND_NO_EXC	equ 0x08

_MM_FROUND_NINT		equ _MM_FROUND_TO_NEAREST_INT OR _MM_FROUND_RAISE_EXC
_MM_FROUND_FLOOR	equ _MM_FROUND_TO_NEG_INF OR _MM_FROUND_RAISE_EXC
_MM_FROUND_CEIL		equ _MM_FROUND_TO_POS_INF OR _MM_FROUND_RAISE_EXC
_MM_FROUND_TRUNC	equ _MM_FROUND_TO_ZERO OR _MM_FROUND_RAISE_EXC
_MM_FROUND_RINT		equ _MM_FROUND_CUR_DIRECTION OR _MM_FROUND_RAISE_EXC
_MM_FROUND_NEARBYINT	equ _MM_FROUND_CUR_DIRECTION OR _MM_FROUND_NO_EXC

_mm_ceil_pd macro val
	exitm<_mm_round_pd((val), _MM_FROUND_CEIL)>
	endm
_mm_ceil_sd macro dst, val
	exitm<_mm_round_sd((dst), (val), _MM_FROUND_CEIL)>
	endm

_mm_floor_pd macro val
	exitm<_mm_round_pd((val), _MM_FROUND_FLOOR)>
	endm
_mm_floor_sd macro dst, val
	exitm<_mm_round_sd((dst), (val), _MM_FROUND_FLOOR)>
	endm

_mm_ceil_ps macro val
	exitm<_mm_round_ps((val), _MM_FROUND_CEIL)>
	endm
_mm_ceil_ss macro dst, val
	exitm<_mm_round_ss((dst), (val), _MM_FROUND_CEIL)>
	endm

_mm_floor_ps macro val
	exitm<_mm_round_ps((val), _MM_FROUND_FLOOR)>
	endm
_mm_floor_ss macro dst, val
	exitm<_mm_round_ss((dst), (val), _MM_FROUND_FLOOR)>
	endm

_mm_test_all_zeros macro mask, val
	exitm<_mm_testz_si128((mask), (val))>
	endm

_mm_test_all_ones macro val
	exitm<_mm_testc_si128((val), _mm_cmpeq_epi32((val),(val)))>
	endm

_mm_test_mix_ones_zeros macro mask, val
	exitm<_mm_testnzc_si128((mask), (val))>
	endm

_mm_blend_epi16		proto :oword, :oword, :sdword
_mm_blendv_epi8		proto :oword, :oword, :oword

_mm_blend_ps		proto :oword, :oword, :sdword
_mm_blendv_ps		proto :oword, :oword, :oword

_mm_blend_pd		proto :oword, :oword, :sdword
_mm_blendv_pd		proto :oword, :oword, :oword

_mm_dp_ps		proto :oword, :oword, :sdword
_mm_dp_pd		proto :oword, :oword, :sdword

_mm_cmpeq_epi64		proto :oword, :oword

_mm_min_epi8		proto :oword, :oword
_mm_max_epi8		proto :oword, :oword

_mm_min_epu16		proto :oword, :oword
_mm_max_epu16		proto :oword, :oword

_mm_min_epi32		proto :oword, :oword
_mm_max_epi32		proto :oword, :oword
_mm_min_epu32		proto :oword, :oword
_mm_max_epu32		proto :oword, :oword

_mm_mullo_epi32		proto :oword, :oword
_mm_mul_epi32		proto :oword, :oword
_mm_testz_si128		proto :oword, :oword
_mm_testc_si128		proto :oword, :oword
_mm_testnzc_si128	proto :oword, :oword
_mm_insert_ps		proto :oword, :oword, :sdword

_MM_MK_INSERTPS_NDX macro srcField, dstField, zeroMask
	exitm<(((srcField) shl 6) or ((dstField) shl 4) or (zeroMask))>
	endm

_mm_extract_ps		proto :oword, :sdword

_MM_EXTRACT_FLOAT macro dest, src, ndx
	exitm<mov dest,_mm_extract_ps((src), (ndx))>
	endm

_MM_PICK_OUT_PS macro src, num
	exitm<_mm_insert_ps(_mm_setzero_ps(), (src), _MM_MK_INSERTPS_NDX((num), 0, 0x0e))>
	endm

_mm_insert_epi8		proto :oword, :sdword, :sdword
_mm_insert_epi32	proto :oword, :sdword, :sdword

ifdef _M_X64
_mm_insert_epi64	proto :oword, :qword, :sdword
endif

_mm_extract_epi8	proto :oword, :sdword
_mm_extract_epi32	proto :oword, :sdword

ifdef _M_X64
_mm_extract_epi64	proto :oword, :sdword
endif

_mm_minpos_epu16	proto :oword

_mm_round_pd		proto :oword, :sdword
_mm_round_sd		proto :oword, :oword, :sdword

_mm_round_ps		proto :oword, :sdword
_mm_round_ss		proto :oword, :oword, :sdword

_mm_cvtepi8_epi32	proto :oword
_mm_cvtepi16_epi32	proto :oword
_mm_cvtepi8_epi64	proto :oword
_mm_cvtepi32_epi64	proto :oword
_mm_cvtepi16_epi64	proto :oword
_mm_cvtepi8_epi16	proto :oword

_mm_cvtepu8_epi32	proto :oword
_mm_cvtepu16_epi32	proto :oword
_mm_cvtepu8_epi64	proto :oword
_mm_cvtepu32_epi64	proto :oword
_mm_cvtepu16_epi64	proto :oword
_mm_cvtepu8_epi16	proto :oword
_mm_packus_epi32	proto :oword, :oword
_mm_mpsadbw_epu8	proto :oword, :oword, :sdword
_mm_stream_load_si128	proto :oword

.list
endif  ;; _INCLUDED_SMM
