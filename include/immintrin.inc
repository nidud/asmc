ifndef _INCLUDED_IMM
define _INCLUDED_IMM
.pragma list(push, 0)
ifndef _LIBC_
include libc.inc
endif

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

_CMP_EQ_OQ	equ 0x00
_CMP_LT_OS	equ 0x01
_CMP_LE_OS	equ 0x02
_CMP_UNORD_Q	equ 0x03
_CMP_NEQ_UQ	equ 0x04
_CMP_NLT_US	equ 0x05
_CMP_NLE_US	equ 0x06
_CMP_ORD_Q	equ 0x07
_CMP_EQ_UQ	equ 0x08
_CMP_NGE_US	equ 0x09
_CMP_NGT_US	equ 0x0A
_CMP_FALSE_OQ	equ 0x0B
_CMP_NEQ_OQ	equ 0x0C
_CMP_GE_OS	equ 0x0D
_CMP_GT_OS	equ 0x0E
_CMP_TRUE_UQ	equ 0x0F
_CMP_EQ_OS	equ 0x10
_CMP_LT_OQ	equ 0x11
_CMP_LE_OQ	equ 0x12
_CMP_UNORD_S	equ 0x13
_CMP_NEQ_US	equ 0x14
_CMP_NLT_UQ	equ 0x15
_CMP_NLE_UQ	equ 0x16
_CMP_ORD_S	equ 0x17
_CMP_EQ_US	equ 0x18
_CMP_NGE_UQ	equ 0x19
_CMP_NGT_UQ	equ 0x1A
_CMP_FALSE_OS	equ 0x1B
_CMP_NEQ_OS	equ 0x1C
_CMP_GE_OQ	equ 0x1D
_CMP_GT_OQ	equ 0x1E
_CMP_TRUE_US	equ 0x1F

_mm256_add_pd macro a, b
    vaddpd a,a,b
    retm<a>
    endm
_mm256_add_ps macro a, b
    vaddps a,a,b
    retm<a>
    endm
_mm256_addsub_pd macro a, b
    vaddsubpd a,a,b
    retm<a>
    endm
_mm256_addsub_ps macro a, b
    vaddsubps a,a,b
    retm<a>
    endm
_mm256_and_pd macro a, b
    vandpd a,a,b
    retm<a>
    endm
_mm256_and_ps macro a, b
    vandps a,a,b
    retm<a>
    endm
_mm256_andnot_pd macro a, b
    vandnpd a,a,b
    retm<a>
    endm
_mm256_andnot_ps macro a, b
    vandnps a,a,b
    retm<a>
    endm

_mm256_blend_pd macro a, b, i
    vblendpd a,a,b,i
    retm<a>
    endm
_mm256_blend_ps macro a, b, i
    vblendps a,a,b,i
    retm<a>
    endm
_mm256_blendv_pd macro a, b, i
    vblendvpd a,a,b,i
    retm<a>
    endm
_mm256_blendv_ps macro a, b, i
    vblendvps a,a,b,i
    retm<a>
    endm

_mm256_div_pd macro a, b
    vdivpd a,a,b
    retm<a>
    endm
_mm256_div_ps macro a, b
    vdivps a,a,b
    retm<a>
    endm
_mm256_dp_ps macro a, b, i
    vdpps a,a,b,i
    retm<a>
    endm
_mm256_hadd_pd macro a, b
    vhaddpd a,a,b
    retm<a>
    endm
_mm256_hadd_ps macro a, b
    vhaddps a,a,b
    retm<a>
    endm
_mm256_hsub_pd macro a, b
    vhsubpd a,a,b
    retm<a>
    endm
_mm256_hsub_ps macro a, b
    vhsubps a,a,b
    retm<a>
    endm
_mm256_max_pd macro a, b
    vmaxpd a,a,b
    retm<a>
    endm
_mm256_max_ps macro a, b
    vmaxps a,a,b
    retm<a>
    endm
_mm256_min_pd macro a, b
    vminpd a,a,b
    retm<a>
    endm
_mm256_min_ps macro a, b
    vminps a,a,b
    retm<a>
    endm
_mm256_mul_pd macro a, b
    vmulpd a,a,b
    retm<a>
    endm
_mm256_mul_ps macro a, b
    vmulps a,a,b
    retm<a>
    endm
_mm256_or_pd macro a, b
    vorpd a,a,b
    retm<a>
    endm
_mm256_or_ps macro a, b
    vorps a,a,b
    retm<a>
    endm
_mm256_shuffle_pd macro a, b, i
    vshufpd a,a,b,i
    retm<a>
    endm
_mm256_shuffle_ps macro a, b, i
    vshufps a,a,b,i
    retm<a>
    endm
_mm256_sub_pd macro a, b
    vsubpd a,a,b
    retm<a>
    endm
_mm256_sub_ps macro a, b
    vsubps a,a,b
    retm<a>
    endm
_mm256_xor_pd macro a, b
    vxorpd a,a,b
    retm<a>
    endm
_mm256_xor_ps macro a, b
    vxorps a,a,b
    retm<a>
    endm

_mm_cmp_pd macro a, b, imm
    cmppd a,b,imm
    retm<a>
    endm
_mm256_cmp_pd macro a, b, imm
    vcmppd a,a,b,imm
    retm<a>
    endm
_mm_cmp_ps macro a, b, imm
    cmpps a,b,imm
    retm<a>
    endm
_mm256_cmp_ps macro a, b, imm
    vcmpps a,a,b,imm
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

_mm_comi_sd macro a, b, imm
    cmpsd a,b,imm
    retm<a>
    endm
_mm_comi_ss macro a, b, imm
    cmpss a,b,imm
    retm<a>
    endm

_mm256_cvtepi32_pd macro x:=<xmm0>
    vcvtdq2pd ymm0,x
    retm<ymm0>
    endm
_mm256_cvtepi32_ps macro x:=<xmm0>
    vcvtdq2ps ymm0,x
    retm<ymm0>
    endm
_mm256_cvtpd_ps macro y:=<ymm0>
    vcvtpd2ps xmm0,y
    retm<xmm0>
    endm
_mm256_cvtps_epi32 macro y:=<ymm0>
    vcvtps2dq y,y
    retm<y>
    endm
_mm256_cvtps_pd macro x:=<xmm0>
    vcvtps2pd ymm0,x
    retm<ymm0>
    endm
_mm256_cvttpd_epi32 macro y:=<ymm0>
    vcvttpd2dq xmm0,y
    retm<xmm0>
    endm
_mm256_cvtpd_epi32 macro y:=<ymm0>
    vcvtpd2dq xmm0,y
    retm<xmm0>
    endm
_mm256_cvttps_epi32 macro y:=<ymm0>
    vcvttps2dq y,y
    retm<y>
    endm
_mm256_extractf128_ps macro y:=<ymm0>, imm:=<0>
    vextractf128 xmm0,y,imm
    retm<xmm0>
    endm
_mm256_extractf128_pd macro y:=<ymm0>, imm:=<0>
    vextractf128 xmm0,y,imm
    retm<xmm0>
    endm
_mm256_extractf128_si256 macro y:=<ymm0>, imm:=<0>
    vextractf128 xmm0,y,imm
    retm<xmm0>
    endm
_mm256_zeroall macro
    vzeroall
    retm<>
    endm
_mm256_zeroupper macro
    vzeroupper
    retm<>
    endm
_mm256_permutevar_ps macro y:=<ymm0>, yi:=<ymm1>
    vpermilps y,y,yi
    retm<y>
    endm
_mm_permutevar_ps macro x:=<xmm0>, xi:=<xmm1>
    vpermilps x,x,xi
    retm<y>
    endm
_mm256_permute_ps macro y:=<ymm0>, imm:=<0>
    vpermilps y,y,imm
    retm<y>
    endm
ifdef _XM_NO_INTRINSICS_
_mm_permute_ps		proto __cdecl :oword, :sdword
else
_mm_permute_ps macro x:=<xmm0>, imm:req
    vpermilps x,x,imm
    retm<x>
    endm
endif

_mm256_permutevar_pd macro y:=<ymm0>, yi:=<ymm1>
    vpermilpd y,y,yi
    retm<y>
    endm
_mm_permutevar_pd macro x:=<xmm0>, xi:=<xmm1>, xr:=<xmm0>
    vpermilpd xr,x,xi
    retm<xr>
    endm
_mm256_permute_pd macro y:=<ymm0>, imm:=<0>
    vpermilpd y,y,imm
    retm<y>
    endm
_mm_permute_pd macro x:=<xmm0>, imm:=<0>
    vpermilpd x,x,imm
    retm<x>
    endm
_mm256_permute2f128_ps macro y:=<ymm0>, yi:=<ymm1>, imm:=<0>
    vperm2f128 y,y,yi,imm
    retm<y>
    endm
_mm256_permute2f128_pd macro y:=<ymm0>, yi:=<ymm1>, imm:=<0>
    vperm2f128 y,y,yi,imm
    retm<y>
    endm
_mm256_permute2f128_si256 macro y:=<ymm0>, yi:=<ymm1>, imm:=<0>
    vperm2f128 y,y,yi,imm
    retm<y>
    endm

_mm256_broadcast_ss proto watcall :ptr, :abs=<ymm0> {
    vbroadcastss _2,[_1]
    }

_mm_broadcast_ss proto watcall :ptr, :abs=<xmm0> {
    vbroadcastss _2,[_1]
    }
_mm256_broadcast_sd proto watcall :ptr, :abs=<ymm0> {
    vbroadcastsd _2,[_1]
    }
_mm256_broadcast_ps proto watcall :ptr, :abs=<ymm0> {
    vbroadcastf128 _2,[_1]
    }
_mm256_broadcast_pd proto watcall :ptr, :abs=<ymm0> {
    vbroadcastf128 _2,[_1]
    }
_mm256_insertf128_ps macro y:=<ymm0>, x:=<xmm1>, imm:=<0>
    vinsertf128 y,y,x,imm
    retm<y>
    endm
_mm256_insertf128_pd macro y:=<ymm0>, x:=<xmm1>, imm:=<0>
    vinsertf128 y,y,x,imm
    retm<y>
    endm
_mm256_insertf128_si256 macro y:=<ymm0>, x:=<xmm1>, imm:=<0>
    vinsertf128 y,y,x,imm
    retm<y>
    endm
_mm256_load_pd proto watcall :ptr, :abs=<ymm0> {
    vmovupd _2,[_1]
    }
_mm256_store_pd proto watcall :ptr, :abs=<ymm0> {
    vmovupd [_1],_2
    }
_mm256_load_ps proto watcall :ptr, :abs=<ymm0> {
    vmovups _2,[_1]
    }
_mm256_store_ps macro ptr_real4, yr:=<ymm0>
    ifdif <ptr_real4>,<yr>
	vmovups ptr_real4,yr
    endif
    retm<ptr_real4>
    endm
_mm256_loadu_pd macro ptr_real8, yr:=<ymm0>
    vmovupd yr,ptr_real8
    retm<yr>
    endm
_mm256_storeu_pd macro ptr_real8, yr:=<ymm0>
    vmovupd ptr_real8,yr
    retm<>
    endm
_mm256_loadu_ps macro ptr_real4, yr:=<ymm0>
    vmovups yr,ptr_real4
    retm<yr>
    endm
_mm256_storeu_ps macro ptr_real4, yr:=<ymm0>
    vmovups ptr_real4,yr
    retm<>
    endm
_mm256_load_si256 macro ptr_yword, yr:=<ymm0>
    vmovupd yr,ptr_yword
    retm<yr>
    endm
_mm256_store_si256 macro ptr_yword, yr:=<ymm0>
    vmovdqu ptr_yword,yr
    retm<>
    endm
_mm256_loadu_si256 macro ptr_yword, yr:=<ymm0>
    vmovupd yr,ptr_yword
    retm<yr>
    endm
_mm256_storeu_si256 macro ptr_yword, yr:=<ymm0>
    vmovdqu ptr_yword,yr
    retm<>
    endm

_mm256_loadu2_m128 macro hiaddr, loaddr
    exitm<_mm256_set_m128(_mm_loadu_ps(hiaddr), _mm_loadu_ps(loaddr))>
    endm
_mm256_loadu2_m128d macro hiaddr, loaddr
    exitm<_mm256_set_m128d(_mm_loadu_pd(hiaddr), _mm_loadu_pd(loaddr))>
    endm
_mm256_loadu2_m128i macro hiaddr, loaddr
    exitm<_mm256_set_m128i(_mm_loadu_si128(hiaddr), _mm_loadu_si128(loaddr))>
    endm

_mm256_storeu2_m128 proto asmcall :ptr, :ptr, :yword {
    vextractf128 xmm1,ymm0,1
    vmovups [_2],xmm0
    vmovups [_1],xmm1
    }
_mm256_storeu2_m128d equ <_mm256_storeu2_m128>
_mm256_storeu2_m128i equ <_mm256_storeu2_m128>

_mm256_maskload_pd proto asmcall :ptr, :yword {
    vmaskmovpd ymm0,_2,[_1]
    }
_mm256_maskstore_pd proto asmcall :ptr, :yword, :yword {
    vmaskmovpd [_1],_2,_3
    }

_mm_maskload_pd proto asmcall :ptr, :xmmword {
    vmaskmovpd xmm0,_2,[_1]
    }
_mm_maskstore_pd proto asmcall :ptr, :xmmword, :xmmword {
    vmaskmovpd [_1],_2,_3
    }

_mm256_maskload_ps macro ptr_real4, y:=<ymm0>
    vmaskmovps y,y,ptr_real4
    retm<y>
    endm
_mm256_maskstore_ps macro ptr_real4, mask:=<ymm0>, a:=<ymm1>
    vmaskmovps ptr_real4,mask,a
    retm<>
    endm
_mm_maskload_ps proto asmcall :ptr, :xmmword {
    vmaskmovps xmm0,_2,[_1]
    }
_mm_maskstore_ps proto asmcall :ptr, :xmmword, :xmmword {
    vmaskmovps [_1],_2,_3
    }
_mm256_movehdup_ps macro y:=<ymm0>
    vmovshdup y,y
    retm<y>
    endm
_mm256_moveldup_ps macro y:=<ymm0>
    vmovsldup y,y
    retm<y>
    endm
_mm256_movedup_pd macro y:=<ymm0>
    vunpcklpd y,y,y
    retm<y>
    endm
_mm256_lddqu_si256 macro ptr_real8, yr:=<ymm0>
    vlddqu yr,ptr_real8
    retm<yr>
    endm
_mm256_stream_si256 macro ptr_yword, y:=<ymm0>
    vmovntdq ptr_yword,y
    retm<>
    endm
_mm256_stream_pd macro ptr_real8, y:=<ymm0>
    vmovntpd ptr_real8,y
    retm<>
    endm
_mm256_stream_ps macro ptr_real4, y:=<ymm0>
    vmovntps ptr_real4,y
    retm<>
    endm
_mm256_rcp_ps macro y:=<ymm0>
    vrcpps y,y
    retm<y>
    endm
_mm256_rsqrt_ps macro y:=<ymm0>
    vrsqrtps y,y
    retm<y>
    endm
_mm256_sqrt_pd macro y:=<ymm0>
    vsqrtpd y,y
    retm<y>
    endm
_mm256_sqrt_ps macro y:=<ymm0>
    vsqrtps y,y
    retm<y>
    endm
_mm256_round_pd macro y, imm
    vroundpd y,y,imm
    retm<y>
    endm

_mm256_ceil_pd macro val
    exitm<_mm256_round_pd((val), _MM_FROUND_CEIL)>
    endm
_mm256_floor_pd macro val
    exitm<_mm256_round_pd((val), _MM_FROUND_FLOOR)>
    endm

_mm256_round_ps macro y, imm
    vroundps y,y,imm
    retm<y>
    endm
_mm256_ceil_ps macro val
    exitm<_mm256_round_ps((val), _MM_FROUND_CEIL)>
    endm
_mm256_floor_ps macro val
    exitm<_mm256_round_ps((val), _MM_FROUND_FLOOR)>
    endm

_mm256_unpackhi_pd macro y:=<ymm0>, yi:=<ymm1>
    vunpckhpd y,y,yi
    retm<y>
    endm
_mm256_unpackhi_ps macro y:=<ymm0>, yi:=<ymm1>
    vunpckhps y,y,yi
    retm<y>
    endm
_mm256_unpacklo_pd macro y:=<ymm0>, yi:=<ymm1>
    vunpcklpd y,y,yi
    retm<y>
    endm
_mm256_unpacklo_ps macro y:=<ymm0>, yi:=<ymm1>
    vunpcklps y,y,yi
    retm<y>
    endm
_mm256_testz_si256 macro y, yi
    vptest y,yi
    retm<ZERO?>
    endm

_mm256_test_all_zeros macro m, val
    exitm<_mm256_testz_si256((m), (val))>
    endm

_mm256_testc_si256 macro y, yi
    vptest y,yi
    retm<CARRY?>
    endm
_mm256_test_all_ones macro val
    exitm<_mm256_testc_si256((val), _mm256_cmpeq_epi32((val),(val)))>
    endm

_mm256_testnzc_si256 macro y, yi
    vptest y,yi
    retm<!CARRY? && !ZERO?>
    endm
_mm256_test_mix_ones_zeros macro m, val
    exitm<_mm256_testnzc_si256((m), (val))>
    endm

_mm256_testz_pd macro y, yi
    vtestpd y,yi
    retm<ZERO?>
    endm
_mm256_testc_pd macro y, yi
    vtestpd y,yi
    retm<CARRY?>
    endm
_mm256_testnzc_pd macro y, yi
    vtestpd y,yi
    retm<!CARRY? && !ZERO?>
    endm
_mm_testz_pd macro x, xi
    vtestpd x,xi
    retm<ZERO?>
    endm
_mm_testc_pd macro x, xi
    vtestpd x,xi
    retm<CARRY?>
    endm
_mm_testnzc_pd macro x, xi
    vtestpd x,xi
    retm<!CARRY? && !ZERO?>
    endm

_mm256_testz_ps macro y, yi
    vtestps y,yi
    retm<ZERO?>
    endm
_mm256_testc_ps macro y, yi
    vtestps y,yi
    retm<CARRY?>
    endm
_mm256_testnzc_ps macro y, yi
    vtestps y,yi
    retm<!CARRY? && !ZERO?>
    endm
_mm_testz_ps macro x, yi
    vtestps x,xi
    retm<ZERO?>
    endm
_mm_testc_ps macro x, yi
    vtestps x,xi
    retm<CARRY?>
    endm
_mm_testnzc_ps macro x, xi
    vtestps x,xi
    retm<!CARRY? && !ZERO?>
    endm

_mm256_movemask_pd macro y:=<ymm0>
    vmovmskpd eax,y
    retm<eax>
    endm
_mm256_movemask_ps macro y:=<ymm0>
    vmovmskps eax,y
    retm<eax>
    endm

_mm256_setzero_pd macro
    vxorpd xmm0,xmm0,xmm0
    retm<ymm0>
    endm
_mm256_setzero_ps macro
    vxorps xmm0,xmm0,xmm0
    retm<ymm0>
    endm
_mm256_setzero_si256 macro
    vpxor xmm0,xmm0,xmm0
    retm<ymm0>
    endm

_mm256_set_epix macro ymm, op, args:vararg
.data
    align 16
    @@ label ymmword
    op &args
.code
    vmovupd ymm,@B
    retm<ymm>
    endm

_mm256_set_epi64x macro ymm, _1, _2, _3, _4
ifnb <_4>
    exitm<_mm256_set_epix(ymm,dq,_4,_3,_2,_1)>
else
    exitm<_mm256_set_epix(ymm0,dq,_4,_3,_2,_1)>
endif
    endm
_mm256_set_epi32 macro ymm, _1,_2,_3,_4,_5,_6,_7,_8
ifnb <_8>
    exitm<_mm256_set_epix(ymm,dd,_8,_7,_6,_5,_4,_3,_2,_1)>
else
    exitm<_mm256_set_epix(ymm0,dd,_7,_6,_5,_4,_3,_2,_1,ymm)>
endif
    endm
_mm256_set_epi16 macro _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16
    exitm<_mm256_set_epix(ymm0,dw,_16,_15,_14,_13,_12,_11,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1)>
    endm
_mm256_set_epi8 macro _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32
    _mm256_set_epix(ymm0,db,_32,_31,_30,_29,_28,_27,_26,_25,_24,_23,_22,_21,_20,_19,_18,_17,_16,_15,_14,_13,_12,_11,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1)
    retm<ymm0>
    endm

_mm256_set_ps equ <_mm256_set_epi32>
_mm256_set_pd equ <_mm256_set_epi64x>

_mm256_set_m128 macro lo, hi
    exitm<_mm256_insertf128_ps(_mm256_castps128_ps256(lo), (hi), 0x1)>
    endm
_mm256_set_m128d macro lo, hi
    exitm<_mm256_insertf128_pd(_mm256_castpd128_pd256(lo), (hi), 0x1)>
    endm
_mm256_set_m128i macro lo, hi
    exitm<_mm256_insertf128_si256(_mm256_castsi128_si256(lo), (hi), 0x1)>
    endm

_mm256_setr_epi64x macro args:vararg
    _mm256_set_epix(ymm0,dq,args)
    retm<ymm0>
    endm
_mm256_setr_epi32 macro args:vararg
    _mm256_set_epix(ymm0,dd,args)
    retm<ymm0>
    endm
_mm256_setr_epi8 macro args:vararg
    _mm256_set_epix(ymm0,db,args)
    retm<ymm0>
    endm
_mm256_setr_epi16 macro args:vararg
    _mm256_set_epix(ymm0,dw,args)
    retm<ymm0>
    endm
_mm256_setr_ps equ <_mm256_setr_epi32>
_mm256_setr_pd equ <_mm256_setr_epi64x>

_mm256_setr_m128 macro lo, hi
    exitm<_mm256_set_m128((hi), (lo))>
    endm
_mm256_setr_m128d macro lo, hi
    exitm<_mm256_set_m128d((hi), (lo))>
    endm
_mm256_setr_m128i macro lo, hi
    exitm<_mm256_set_m128i((hi), (lo))>
    endm

_mm256_set1_epi64x macro q
    exitm<_mm256_set_epi64x(q,q,q,q)>
    endm
_mm256_set1_epi32 macro q
    exitm<_mm256_set_epi32(q,q,q,q,q,q,q,q)>
    endm
_mm256_set1_epi16 macro q
    exitm<_mm256_set_epi16(q,q,q,q,q,q,q,q,q,q,q,q,q,q,q,q)>
    endm
_mm256_set1_epi8 macro q
    exitm<_mm256_set_epi8(q,q,q,q,q,q,q,q,q,q,q,q,q,q,q,q,q,q,q,q,q,q,q,q,q,q,q,q,q,q,q,q)>
    endm

_mm256_set1_ps equ <_mm256_set1_epi32>
_mm256_set1_pd equ <_mm256_set1_epi64x>

_mm256_castpd_ps macro ymm
    exitm<ymm>
    endm
_mm256_castps_pd macro ymm
    exitm<ymm>
    endm
_mm256_castps_si256 macro ymm
    exitm<ymm>
    endm
_mm256_castpd_si256 macro ymm
    exitm<ymm>
    endm
_mm256_castsi256_ps macro ymm
    exitm<ymm>
    endm
_mm256_castsi256_pd macro ymm
    exitm<ymm>
    endm
_mm256_castps256_ps128 macro ymm
    exitm<@CatStr(<xmm>,@SubStr(ymm,4))>
    endm
_mm256_castpd256_pd128 macro ymm
    exitm<@CatStr(<xmm>,@SubStr(ymm,4))>
    endm
_mm256_castsi256_si128 macro ymm
    exitm<@CatStr(<xmm>,@SubStr(ymm,4))>
    endm
_mm256_castps128_ps256 macro xmm
    exitm<@CatStr(<ymm>,@SubStr(xmm,4))>
    endm
_mm256_castpd128_pd256 macro xmm
    exitm<@CatStr(<ymm>,@SubStr(xmm,4))>
    endm
_mm256_castsi128_si256 macro xmm
    exitm<@CatStr(<ymm>,@SubStr(xmm,4))>
    endm

_mm_cvtph_ps proto :oword {
    vcvtph2ps xmm0, xmm0
    }
_mm256_cvtph_ps proto :oword {
    vcvtph2ps ymm0, xmm0
    }
_mm_cvtps_ph proto x:oword, i:abs {
    vcvtps2ph xmm0, xmm0, i
    }
_mm256_cvtps_ph proto y:yword, i:abs {
    vcvtps2ph xmm0, ymm0, i
    }

_mm_undefined_ps	equ <_mm_setzero_ps>
_mm_undefined_pd	equ <_mm_setzero_pd>
_mm_undefined_si128	equ <_mm_setzero_si128>
_mm256_undefined_ps	equ <_mm256_setzero_ps>
_mm256_undefined_pd	equ <_mm256_setzero_pd>
_mm256_undefined_si256	equ <_mm256_setzero_si256>

_XCR_XFEATURE_ENABLED_MASK equ 0

_xgetbv proto :sdword {
    xgetbv
    shl rdx,32
    or	rax,rdx
    }
_xsetbv proto :dword, :qword {
    mov rax,rdx
    shr rdx,32
    xsetbv
    }
_xsave proto :ptr, :qword {
    mov rax,rdx
    shr rdx,32
    xsave qword ptr [rcx]
    }

ifdef _M_X64
_xsave64 proto :ptr, :qword {
    mov rax,rdx
    shr rdx,32
    xsave64 qword ptr [rcx]
    }
endif
_xsaveopt proto :ptr, :qword {
    mov rax,rdx
    shr rdx,32
    xsaveopt qword ptr [rcx]
    }
ifdef _M_X64
_xsaveopt64 proto :ptr, :qword {
    mov rax,rdx
    shr rdx,32
    xsaveopt64 qword ptr [rcx]
    }
endif
_xsavec proto :ptr, :qword {
    mov rax,rdx
    shr rdx,32
    xsavec qword ptr [rcx]
    }
ifdef _M_X64
_xsavec64 proto :ptr, :qword {
    mov rax,rdx
    shr rdx,32
    xsavec64 qword ptr [rcx]
    }
endif
_xrstor proto :ptr, :qword {
    mov rax,rdx
    shr rdx,32
    xrstor qword ptr [rcx]
    }
ifdef _M_X64
_xrstor64 proto :ptr, :qword {
    mov rax,rdx
    shr rdx,32
    xrstor64 qword ptr [rcx]
    }
endif
_xsaves proto :ptr, :qword {
    mov rax,rdx
    shr rdx,32
    xsaves qword ptr [rcx]
    }
ifdef _M_X64
_xsaves64 proto :ptr, :qword {
    mov rax,rdx
    shr rdx,32
    xsaves64 qword ptr [rcx]
    }
endif
_xrstors proto :ptr, :qword {
    mov rax,rdx
    shr rdx,32
    xrstors qword ptr [rcx]
    }
ifdef _M_X64
_xrstors64 proto :ptr, :qword {
    mov rax,rdx
    shr rdx,32
    xrstors64 qword ptr [rcx]
    }
endif
_fxsave proto :ptr {
    fxsave qword ptr [rcx]
    }
ifdef _M_X64
_fxsave64 proto :ptr {
    fxsave64 qword ptr [rcx]
    }
endif
_fxrstor proto :ptr {
    fxrstor qword ptr [rcx]
    }
ifdef _M_X64
_fxrstor64 proto :ptr {
    fxrstor64 qword ptr [rcx]
    }
endif

_rdrand16_step proto :ptr word {
	rdrand	ax
	mov	[rcx],ax
	mov	ecx,1
	mov	eax,0
	cmovb	eax,ecx
	}
_rdrand32_step proto :ptr dword {
	rdrand	eax
	mov	[rcx],eax
	mov	ecx,1
	mov	eax,0
	cmovb	eax,ecx
	}
ifdef _M_X64
_rdrand64_step proto :ptr qword {
	rdrand	rax
	mov	[rcx],rax
	mov	ecx,1
	mov	eax,0
	cmovb	eax,ecx
	}
endif

ifdef _M_X64
_readfsbase_u32 proto reg:abs=<eax> {
	rdfsbase reg
	}
_readgsbase_u32 proto reg:abs=<eax> {
	rdgsbase reg
	}
_readfsbase_u64 proto reg:abs=<rax> {
	rdfsbase reg
	}
_readgsbase_u64 proto reg:abs=<rax> {
	rdgsbase reg
	}
_writefsbase_u32 proto :dword {
	wrfsbase ecx
	}
_writegsbase_u32 proto :dword {
	wrgsbase ecx
	}
_writefsbase_u64 proto :qword {
	wrfsbase rcx
	}
_writegsbase_u64 proto :qword {
	wrgsbase rcx
	}
endif

_mm_fmadd_ps proto :oword, :oword, :oword {
	vfmadd132ps xmm0, xmm2, xmm1
	}
_mm_fmadd_pd proto :oword, :oword, :oword {
	vfmadd231pd xmm2, xmm0, xmm1
	movaps xmm0,xmm2
	}
_mm_fmadd_ss proto :oword, :oword, :oword {
	vfmadd213ss xmm0, xmm1, xmm2
	}
_mm_fmadd_sd proto :oword, :oword, :oword {
	vfmadd213sd xmm0, xmm1, xmm2
	}
_mm_fmsub_ps proto :oword, :oword, :oword {
	vfmsub132ps xmm0, xmm2, xmm1
	}
_mm_fmsub_pd proto :oword, :oword, :oword {
	vfmsub231pd xmm2, xmm0, xmm1
	movaps xmm0,xmm2
	}
_mm_fmsub_ss proto :oword, :oword, :oword {
	vfmsub213ss xmm0, xmm1, xmm2
	}
_mm_fmsub_sd proto :oword, :oword, :oword {
	vfmsub213sd xmm0, xmm1, xmm2
	}
_mm_fnmadd_ps proto :oword, :oword, :oword {
	vfnmadd132ps xmm0, xmm2, xmm1
	}
_mm_fnmadd_pd proto :oword, :oword, :oword {
	vfnmadd231pd xmm2, xmm0, xmm1
	movaps xmm0,xmm2
	}
_mm_fnmadd_ss proto :oword, :oword, :oword {
	vfnmadd213ss xmm0, xmm1, xmm2
	}
_mm_fnmadd_sd proto :oword, :oword, :oword {
	vfnmadd213sd xmm0, xmm1, xmm2
	}
_mm_fnmsub_ps proto :oword, :oword, :oword {
	vfnmsub132ps xmm0, xmm2, xmm1
	}
_mm_fnmsub_pd proto :oword, :oword, :oword {
	vfnmsub231pd xmm2, xmm0, xmm1
	movaps xmm0, xmm2
	}
_mm_fnmsub_ss proto :oword, :oword, :oword {
	vfnmsub213ss xmm0, xmm1, xmm2
	}
_mm_fnmsub_sd proto :oword, :oword, :oword {
	vfnmsub213sd xmm0, xmm1, xmm2
	}

_mm256_fmadd_ps proto :yword, :yword, :yword {
	vfmadd132ps ymm0, ymm2, ymm1
	}
_mm256_fmadd_pd proto :yword, :yword, :yword {
	vfmadd132pd ymm0, ymm2, ymm1
	}
_mm256_fmsub_ps proto :yword, :yword, :yword {
	vfmsub132ps ymm0, ymm2, ymm1
	}
_mm256_fmsub_pd proto :yword, :yword, :yword {
	vfmsub132pd ymm0, ymm2, ymm1
	}
_mm256_fnmadd_ps proto :yword, :yword, :yword {
	vfnmadd132ps ymm0, ymm2, ymm1
	}
_mm256_fnmadd_pd proto :yword, :yword, :yword {
	vfnmadd132pd ymm0, ymm2, ymm1
	}
_mm256_fnmsub_ps proto :yword, :yword, :yword {
	vfnmsub132ps ymm0, ymm2, ymm1
	}
_mm256_fnmsub_pd proto :yword, :yword, :yword {
	vfnmsub132pd ymm0, ymm2, ymm1
	}

_mm_fmaddsub_ps proto :oword, :oword, :oword {
	vfmaddsub132ps xmm0, xmm2, xmm1
	}
_mm_fmaddsub_pd proto :oword, :oword, :oword {
	vfmaddsub231pd xmm2, xmm0, xmm1
	movaps xmm0,xmm2
	}
_mm_fmsubadd_ps proto :oword, :oword, :oword {
	vfmsubadd132ps xmm0, xmm2, xmm1
	}
_mm_fmsubadd_pd proto :oword, :oword, :oword {
	vfmsubadd231pd xmm2, xmm0, xmm1
	movaps xmm0,xmm2
	}

_mm256_fmaddsub_ps proto :yword, :yword, :yword {
	vfmaddsub132ps ymm0, ymm2, ymm1
	}
_mm256_fmaddsub_pd proto :yword, :yword, :yword {
	vfmaddsub132pd ymm0, ymm2, ymm1
	}
_mm256_fmsubadd_ps proto :yword, :yword, :yword {
	vfmsubadd132ps ymm0, ymm2, ymm1
	}
_mm256_fmsubadd_pd proto :yword, :yword, :yword {
	vfmsubadd132pd ymm0, ymm2, ymm1
	}

_mm256_cmpeq_epi8 proto :yword, :yword {
	vpcmpeqb ymm0, ymm0, ymm1
	}
_mm256_cmpeq_epi16 proto :yword, :yword {
	vpcmpeqw ymm0, ymm0, ymm1
	}
_mm256_cmpeq_epi32 proto :yword, :yword {
	vpcmpeqd ymm0, ymm0, ymm1
	}
_mm256_cmpeq_epi64 proto :yword, :yword {
	vpcmpeqq ymm0, ymm0, ymm1
	}

_mm256_cmpgt_epi8 proto :yword, :yword {
	vpcmpgtb ymm0, ymm0, ymm1
	}
_mm256_cmpgt_epi16 proto :yword, :yword {
	vpcmpgtw ymm0, ymm0, ymm1
	}
_mm256_cmpgt_epi32 proto :yword, :yword {
	vpcmpgtd ymm0, ymm0, ymm1
	}
_mm256_cmpgt_epi64 proto :yword, :yword {
	vpcmpgtq ymm0, ymm0, ymm1
	}

_mm256_max_epi8 proto :yword, :yword {
	vpmaxsb ymm0, ymm0, ymm1
	}
_mm256_max_epi16 proto :yword, :yword {
	vpmaxsw ymm0, ymm0, ymm1
	}
_mm256_max_epi32 proto :yword, :yword {
	vpmaxsd ymm0, ymm0, ymm1
	}
_mm256_max_epu8 proto :yword, :yword {
	vpmaxub ymm0, ymm0, ymm1
	}
_mm256_max_epu16 proto :yword, :yword {
	vpmaxuw ymm0, ymm0, ymm1
	}
_mm256_max_epu32 proto :yword, :yword {
	vpmaxud ymm0, ymm0, ymm1
	}

_mm256_min_epi8 proto :yword, :yword {
	vpminsb ymm0, ymm0, ymm1
	}
_mm256_min_epi16 proto :yword, :yword {
	vpminsw ymm0, ymm0, ymm1
	}
_mm256_min_epi32 proto :yword, :yword {
	vpminsd ymm0, ymm0, ymm1
	}
_mm256_min_epu8 proto :yword, :yword {
	vpminub ymm0, ymm0, ymm1
	}
_mm256_min_epu16 proto :yword, :yword {
	vpminuw ymm0, ymm0, ymm1
	}
_mm256_min_epu32 proto :yword, :yword {
	vpminud ymm0, ymm0, ymm1
	}

_mm256_and_si256 proto :yword, :yword {
	vpand	ymm0, ymm0, ymm1
	}
_mm256_andnot_si256 proto :yword, :yword {
	vpandn	ymm0, ymm0, ymm1
	}
_mm256_or_si256 proto :yword, :yword {
	vpor	ymm0, ymm0, ymm1
	}
_mm256_xor_si256 proto :yword, :yword {
	vpxor	ymm0, ymm0, ymm1
	}

_mm256_abs_epi8 proto :yword {
	vpabsb	ymm0, ymm0
	}
_mm256_abs_epi16 proto :yword {
	vpabsw	ymm0, ymm0
	}
_mm256_abs_epi32 proto :yword {
	vpabsd	ymm0, ymm0
	}

_mm256_add_epi8 proto :yword, :yword {
	vpaddb	ymm0, ymm0, ymm1
	}
_mm256_add_epi16 proto :yword, :yword {
	vpaddw	ymm0, ymm0, ymm1
	}
_mm256_add_epi32 proto :yword, :yword {
	vpaddd	ymm0, ymm0, ymm1
	}
_mm256_add_epi64 proto :yword, :yword {
	vpaddq	ymm0, ymm0, ymm1
	}

_mm256_adds_epi8 proto :yword, :yword {
	vpaddsb ymm0, ymm0, ymm1
	}
_mm256_adds_epi16 proto :yword, :yword {
	vpaddsw ymm0, ymm0, ymm1
	}
_mm256_adds_epu8 proto :yword, :yword {
	vpaddusb ymm0, ymm0, ymm1
	}
_mm256_adds_epu16 proto :yword, :yword {
	vpaddusw ymm0, ymm0, ymm1
	}

_mm256_sub_epi8 proto :yword, :yword {
	vpsubb	ymm0, ymm0, ymm1
	}
_mm256_sub_epi16 proto :yword, :yword {
	vpsubw	ymm0, ymm0, ymm1
	}
_mm256_sub_epi32 proto :yword, :yword {
	vpsubd	ymm0, ymm0, ymm1
	}
_mm256_sub_epi64 proto :yword, :yword {
	vpsubq	ymm0, ymm0, ymm1
	}

_mm256_subs_epi8 proto :yword, :yword {
	vpsubsb ymm0, ymm0, ymm1
	}
_mm256_subs_epi16 proto :yword, :yword {
	vpsubsw ymm0, ymm0, ymm1
	}
_mm256_subs_epu8 proto :yword, :yword {
	vpsubusb ymm0, ymm0, ymm1
	}
_mm256_subs_epu16 proto :yword, :yword {
	vpsubusw ymm0, ymm0, ymm1
	}

_mm256_avg_epu8 proto :yword, :yword {
	vpavgb	ymm0, ymm0, ymm1
	}
_mm256_avg_epu16 proto :yword, :yword {
	vpavgw	ymm0, ymm0, ymm1
	}
_mm256_hadd_epi16 proto :yword, :yword {
	vphaddw ymm0, ymm0, ymm1
	}
_mm256_hadd_epi32 proto :yword, :yword {
	vphaddd ymm0, ymm0, ymm1
	}
_mm256_hadds_epi16 proto :yword, :yword {
	vphaddsw ymm0, ymm0, ymm1
	}
_mm256_hsub_epi16 proto :yword, :yword {
	vphsubw ymm0, ymm0, ymm1
	}

_mm256_hsub_epi32 proto :yword, :yword {
	vphsubd ymm0, ymm0, ymm1
	}
_mm256_hsubs_epi16 proto :yword, :yword {
	vphsubsw ymm0, ymm0, ymm1
	}

_mm256_madd_epi16 proto :yword, :yword {
	vpmaddwd ymm0, ymm0, ymm1
	}
_mm256_maddubs_epi16 proto :yword, :yword {
	vpmaddubsw ymm0, ymm0, ymm1
	}

_mm256_mulhi_epi16 proto :yword, :yword {
	vpmulhw ymm0, ymm0, ymm1
	}
_mm256_mulhi_epu16 proto :yword, :yword {
	vpmulhuw ymm0, ymm0, ymm1
	}

_mm256_mullo_epi16 proto :yword, :yword {
	vpmullw ymm0, ymm0, ymm1
	}
_mm256_mullo_epi32 proto :yword, :yword {
	vpmulld ymm0, ymm0, ymm1
	}

_mm256_mul_epu32 proto :yword, :yword {
	vpmuludq ymm0, ymm0, ymm1
	}
_mm256_mul_epi32 proto :yword, :yword {
	vpmuldq ymm0, ymm0, ymm1
	}

_mm256_sign_epi8 proto :yword, :yword {
	vpsignb ymm0, ymm0, ymm1
	}
_mm256_sign_epi16 proto :yword, :yword {
	vpsignw ymm0, ymm0, ymm1
	}
_mm256_sign_epi32 proto :yword, :yword {
	vpsignd ymm0, ymm0, ymm1
	}

_mm256_mulhrs_epi16 proto :yword, :yword {
	vpmulhrsw ymm0, ymm0, ymm1
	}

_mm256_sad_epu8 proto :yword, :yword {
	vpsadbw ymm0, ymm0, ymm1
	}
_mm256_mpsadbw_epu8 proto :yword, :yword, i:abs {
	vmpsadbw ymm0, ymm0, ymm1, i
	}

_mm256_slli_si256 proto :yword, i:abs {
	vpslldq ymm0, ymm0, i
	}
_mm256_bslli_epi128	equ <_mm256_slli_si256>
_mm256_srli_si256 proto :yword, i:abs {
	vpsrldq ymm0, ymm0, i
	}
_mm256_bsrli_epi128	equ <_mm256_srli_si256>

_mm256_sll_epi16 proto :yword, :oword {
	vpsllw	ymm0, ymm0, xmm1
	}
_mm256_sll_epi32 proto :yword, :yword {
	vpslld	ymm0, ymm0, xmm1
	}
_mm256_sll_epi64 proto :yword, :yword {
	vpsllq	ymm0, ymm0, xmm1
	}

_mm256_slli_epi16 proto :yword, i:abs {
	vpsllw	ymm0, ymm0, i
	}
_mm256_slli_epi32 proto :yword, i:abs {
	vpslld	ymm0, ymm0, i
	}
_mm256_slli_epi64 proto :yword, i:abs {
	vpsllq	ymm0, ymm0, i
	}

_mm256_sllv_epi32 proto :yword, :yword {
	vpsllvd ymm0, ymm0, ymm1
	}
_mm256_sllv_epi64 proto :yword, :yword {
	vpsllvq ymm0, ymm0, ymm1
	}

_mm_sllv_epi32 proto :oword, :oword {
	vpsllvd xmm0, xmm0, xmm1
	}
_mm_sllv_epi64 proto :oword, :oword {
	vpsllvq xmm0, xmm0, xmm1
	}

_mm256_sra_epi16 proto :yword, :oword {
	vpsraw	ymm0, ymm0, xmm1
	}
_mm256_sra_epi32 proto :yword, :oword {
	vpsrad	ymm0, ymm0, xmm1
	}

_mm256_srai_epi16 proto :yword, i:abs {
	vpsraw	ymm0, ymm0, i
	}
_mm256_srai_epi32 proto :yword, i:abs {
	vpsrad	ymm0, ymm0, i
	}

_mm256_srav_epi32 proto :yword, :yword {
	vpsravd ymm0, ymm0, ymm1
	}

_mm_srav_epi32 proto :oword, :oword {
	vpsravd xmm0, xmm0, xmm1
	}

_mm256_srl_epi16 proto :yword, :oword {
	vpsrlw	ymm0, ymm0, xmm1
	}
_mm256_srl_epi32 proto :yword, :oword {
	vpsrld	ymm0, ymm0, xmm1
	}
_mm256_srl_epi64 proto :yword, :oword {
	vpsrlq	ymm0, ymm0, xmm1
	}

_mm256_srli_epi16 proto :yword, i:abs {
	vpsrlw	ymm0, ymm0, i
	}
_mm256_srli_epi32 proto :yword, i:abs {
	vpsrld	ymm0, ymm0, i
	}
_mm256_srli_epi64 proto :yword, i:abs {
	vpsrlq	ymm0, ymm0, i
	}

_mm256_srlv_epi32 proto :yword, :yword {
	vpsrlvd ymm0, ymm0, ymm1
	}
_mm256_srlv_epi64 proto :yword, :yword {
	vpsrlvq ymm0, ymm0, ymm1
	}

_mm_srlv_epi32 proto :oword, :oword {
	vpsrlvd xmm0, xmm0, xmm1
	}
_mm_srlv_epi64 proto :oword, :oword {
	vpsrlvq xmm0, xmm0, xmm1
	}

_mm_blend_epi32 proto :oword, :oword, i:abs {
	vpblendd xmm0, xmm0, xmm1, i
	}

_mm256_blend_epi32 proto :yword, :yword, i:abs {
	vpblendd ymm0, ymm0, ymm1, i
	}
_mm256_alignr_epi8 proto :yword, :yword, i:abs {
	vpalignr ymm0, ymm0, ymm1, i
	}

_mm256_blendv_epi8 proto :yword, :yword, :yword {
	vpblendvb ymm0, ymm0, ymm1, ymm2
	}
_mm256_blend_epi16 proto :yword, :yword, i:abs {
	vpblendw ymm0, ymm0, ymm1, i
	}

_mm256_packs_epi16 proto :yword, :yword {
	vpacksswb ymm0, ymm0, ymm1
	}
_mm256_packs_epi32 proto :yword, :yword {
	vpackssdw ymm0, ymm0, ymm1
	}
_mm256_packus_epi16 proto :yword, :yword {
	vpackuswb ymm0, ymm0, ymm1
	}
_mm256_packus_epi32 proto :yword, :yword {
	vpackusdw ymm0, ymm0, ymm1
	}

_mm256_unpackhi_epi8 proto :yword, :yword {
	vpunpckhbw ymm0, ymm0, ymm1
	}
_mm256_unpackhi_epi16 proto :yword, :yword {
	vpunpckhwd ymm0, ymm0, ymm1
	}
_mm256_unpackhi_epi32 proto :yword, :yword {
	vpunpckhdq ymm0, ymm0, ymm1
	}
_mm256_unpackhi_epi64 proto :yword, :yword {
	vpunpckhqdq ymm0, ymm0, ymm1
	}

_mm256_unpacklo_epi8 proto :yword, :yword {
	vpunpcklbw ymm0, ymm0, ymm1
	}
_mm256_unpacklo_epi16 proto :yword, :yword {
	vpunpcklwd ymm0, ymm0, ymm1
	}
_mm256_unpacklo_epi32 proto :yword, :yword {
	vpunpckldq ymm0, ymm0, ymm1
	}
_mm256_unpacklo_epi64 proto :yword, :yword {
	vpunpcklqdq ymm0, ymm0, ymm1
	}

_mm256_shuffle_epi8 proto :yword, :yword {
	vpshufb ymm0, ymm0, ymm1
	}
_mm256_shuffle_epi32 proto :yword, i:abs {
	vpshufd ymm0, ymm0, i
	}

_mm256_shufflehi_epi16 proto :yword, i:abs {
	vpshufhw ymm0, ymm0, i
	}
_mm256_shufflelo_epi16 proto :yword, i:abs {
	vpshuflw ymm0, ymm0, i
	}

_mm256_extracti128_si256 proto :yword, i:abs {
	vextracti128 xmm0, ymm0, i
	vzeroupper
	}
_mm256_inserti128_si256 proto :yword, :oword, i:abs {
	vinserti128 ymm0, ymm0, xmm1, i
	}

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
