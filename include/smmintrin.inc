ifndef _INCLUDED_SMM
define _INCLUDED_SMM
.pragma list(push, 0)
ifndef _LIBC_
include libc.inc
endif
ifndef _M_IX86
ifndef _M_X64
.err <This header is specific to X86 and X64 targets>
endif
endif
ifdef _M_CEE_PURE
.err <ERROR: This file is not supported in the pure mode!>
endif

include tmmintrin.inc

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

_mm_test_all_zeros macro m, val
	exitm<_mm_testz_si128((m), (val))>
	endm

_mm_test_all_ones macro val
	exitm<_mm_testc_si128((val), _mm_cmpeq_epi32((val),(val)))>
	endm

_mm_test_mix_ones_zeros macro m, val
	exitm<_mm_testnzc_si128((m), (val))>
	endm

_mm_blend_epi16 macro a, b, imm
	pblendw a, b, imm
	retm<a>
	endm
_mm_blendv_epi8 macro a, b, x
	pblendvb a, b, x
	retm<a>
	endm
_mm_blend_ps macro a, b, imm
	blendps a, b, imm
	retm<a>
	endm
_mm_blendv_ps macro a, b, x
	blendvps a, b, x
	retm<a>
	endm
_mm_blend_pd macro a, b, imm
	blendpd a, b, imm
	retm<a>
	endm
_mm_blendv_pd macro a, b, x
	blendvpd a, b, x
	retm<a>
	endm

_mm_dp_ps macro a, b, imm
	dpps a,b,imm
	retm<a>
	endm
_mm_dp_pd macro a, b, imm
	dppd a,b,imm
	retm<a>
	endm

_mm_cmpeq_epi64 macro a, b
	pcmpeqq a,b
	retm<a>
	endm

_mm_min_epi8 macro a, b
	pminsb a,b
	retm<a>
	endm
_mm_max_epi8 macro a, b
	pmaxsb a,b
	retm<a>
	endm

_mm_min_epu16 macro a, b
	pminuw a,b
	retm<a>
	endm
_mm_max_epu16 macro a, b
	pmaxuw a,b
	retm<a>
	endm

_mm_min_epi32 macro a, b
	pminsd a,b
	retm<a>
	endm
_mm_max_epi32 macro a, b
	pmaxsd a,b
	retm<a>
	endm
_mm_min_epu32 macro a, b
	pminud a,b
	retm<a>
	endm
_mm_max_epu32 macro a, b
	pmaxud a,b
	retm<a>
	endm

_mm_mullo_epi32 macro a, b
	pmulld a,b
	retm<a>
	endm

_mm_mul_epi32 macro a, b
	pmuldq a,b
	retm<a>
	endm

_mm_testz_si128 macro a, b
	ptest a,b
	retm<ZERO?>
	endm

_mm_testc_si128 macro a, b
	ptest a,b
	retm<CARRY?>
	endm

_mm_testnzc_si128 macro a, b
	ptest a,b
	retm<!CARRY? && !ZERO?>
	endm

_mm_insert_ps macro a, b, imm
	insertps a, b, imm
	retm<a>
	endm

_MM_MK_INSERTPS_NDX macro srcField, dstField, zeroMask
	exitm<(((srcField) shl 6) or ((dstField) shl 4) or (zeroMask))>
	endm

_mm_extract_ps macro x, imm
	extractps x, imm
	retm<x>
	endm

_MM_EXTRACT_FLOAT macro dest, src, ndx
	exitm<_mm_store_ps(dest, _mm_extract_ps((src), (ndx)))>
	endm

_MM_PICK_OUT_PS macro src, num
	exitm<_mm_insert_ps(_mm_setzero_ps(), (src), _MM_MK_INSERTPS_NDX((num), 0, 0x0e))>
	endm

_mm_insert_epi8 macro x, r, imm
	pinsrb x,r,imm
	retm<x>
	endm
_mm_insert_epi32 macro x, r, imm
	pinsrd x,r,imm
	retm<x>
	endm

ifdef _M_X64
_mm_insert_epi64 macro x, r, imm
	pinsrq x,r,imm
	retm<x>
	endm
endif

_mm_extract_epi8 macro x, imm
	pextrb eax,x,imm
	retm<eax>
	endm
_mm_extract_epi32 macro x, imm
	pextrd eax,x,imm
	retm<eax>
	endm

ifdef _M_X64
_mm_extract_epi64 macro x, imm
	pextrq rax,x,imm
	retm<rax>
	endm
endif

_mm_minpos_epu16 macro x
	phminposuw x,x
	retm<x>
	endm

_mm_round_pd macro x, imm
	roundpd x,imm
	retm<x>
	endm
_mm_round_sd macro a, b, imm
	roundsd a,b,imm
	retm<a>
	endm
_mm_round_ps macro x, imm
	roundps x,x,imm
	retm<x>
	endm
_mm_round_ss macro a, b, imm
	roundss a,b,imm
	retm<a>
	endm
ifdef _M_X64
_mm_cvt_roundsd_i64 macro a, r
	vcvtsd2si rax,a,r
	retm<rax>
	endm
endif

_mm_cvtepi8_epi32 macro x:=<xmm0>
	pmovsxbd x,x
	retm<x>
	endm
_mm_cvtepi16_epi32 macro x:=<xmm0>
	pmovsxwd x,x
	retm<x>
	endm
_mm_cvtepi8_epi64 macro x:=<xmm0>
	pmovsxbq x,x
	retm<x>
	endm
_mm_cvtepi32_epi64 macro x
	pmovsxdq x,x
	retm<x>
	endm
_mm_cvtepi16_epi64 macro x
	pmovsxwq x,x
	retm<x>
	endm
_mm_cvtepi8_epi16 macro x
	pmovsxbw x,x
	retm<x>
	endm

_mm_cvtepu8_epi32 macro x
	pmovzxbd x,x
	retm<x>
	endm
_mm_cvtepu16_epi32 macro x
	pmovzxwd x,x
	retm<x>
	endm
_mm_cvtepu8_epi64 macro x
	pmovzxbq x,x
	retm<x>
	endm
_mm_cvtepu32_epi64 macro x
	pmovzxdq x,x
	retm<x>
	endm
_mm_cvtepu16_epi64 macro x
	pmovzxwq x,x
	retm<x>
	endm
_mm_cvtepu8_epi16 macro x
	pmovzxbw x,x
	retm<x>
	endm

_mm_packus_epi32 macro a, b
	packusdw a,b
	retm<a>
	endm

_mm_mpsadbw_epu8 macro a, b, imm
	mpsadbw a,b,imm
	retm<a>
	endm

_mm_stream_load_si128 macro p
	movdqa xmm0,p
	retm<xmm0>
	endm

.pragma list(pop)
endif
