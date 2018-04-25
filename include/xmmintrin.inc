ifndef _INCLUDED_MM2
_INCLUDED_MM2 equ <>

ifndef _M_IX86
ifndef _M_X64
.err <This header is specific to X86 and X64 targets>
endif
endif
ifdef _M_CEE_PURE
.err <ERROR: EMM intrinsics not supported in the pure mode>
endif

ifndef _MMINTRIN_H_INCLUDED
include mmintrin.inc
endif

ifdef _MM2_FUNCTIONALITY
ifndef _MM_FUNCTIONALITY
_MM_FUNCTIONALITY equ <>
endif
endif

ifdef __ICL
ifdef _MM_FUNCTIONALITY
include xmm_func.inc
else
__m128			typedef oword
endif
else ;; __ICL

__m128			union
m128_f32		real4 4 dup(?)
m128_u64		dq 2 dup(?)
m128_i8			sbyte 16 dup(?)
m128_i16		sword 8 dup(?)
m128_i32		sdword 4 dup(?)
m128_i64		sqword 2 dup(?)
m128_u8			db 16 dup(?)
m128_u16		dw 8 dup(?)
m128_u32		dd 4 dup(?)
__m128			ends

ifndef _VCRT_BUILD
ifndef _INC_MALLOC
include malloc.inc
endif
endif

endif;; __ICL

_MM_SHUFFLE macro fp3,fp2,fp1,fp0
	exitm<(((fp3) SHL 6) OR ((fp2) SHL 4) OR ((fp1) SHL 2) OR ((fp0)))>
	endm

_MM_TRANSPOSE4_PS macro row0, row1, row2, row3
	exitm<>
	endm

_MM_HINT_NTA		equ 0
_MM_HINT_T0		equ 1
_MM_HINT_T1		equ 2
_MM_HINT_T2		equ 3
_MM_HINT_ENTA		equ 4

_MM_ALIGN16		equ _VCRT_ALIGN(16)

_MM_EXCEPT_MASK		equ 0x003f
_MM_EXCEPT_INVALID	equ 0x0001
_MM_EXCEPT_DENORM	equ 0x0002
_MM_EXCEPT_DIV_ZERO	equ 0x0004
_MM_EXCEPT_OVERFLOW	equ 0x0008
_MM_EXCEPT_UNDERFLOW	equ 0x0010
_MM_EXCEPT_INEXACT	equ 0x0020

_MM_MASK_MASK		equ 0x1f80
_MM_MASK_INVALID	equ 0x0080
_MM_MASK_DENORM		equ 0x0100
_MM_MASK_DIV_ZERO	equ 0x0200
_MM_MASK_OVERFLOW	equ 0x0400
_MM_MASK_UNDERFLOW	equ 0x0800
_MM_MASK_INEXACT	equ 0x1000

_MM_ROUND_MASK		equ 0x6000
_MM_ROUND_NEAREST	equ 0x0000
_MM_ROUND_DOWN		equ 0x2000
_MM_ROUND_UP		equ 0x4000
_MM_ROUND_TOWARD_ZERO	equ 0x6000

_MM_FLUSH_ZERO_MASK	equ 0x8000
_MM_FLUSH_ZERO_ON	equ 0x8000
_MM_FLUSH_ZERO_OFF	equ 0x0000

_MM_SET_EXCEPTION_STATE macro mask
	exitm<_mm_setcsr((_mm_getcsr() & ~_MM_EXCEPT_MASK) | (mask))>
	endm

_MM_GET_EXCEPTION_STATE macro
	exitm<(_mm_getcsr() & _MM_EXCEPT_MASK)>
	endm

_MM_SET_EXCEPTION_MASK macro mask
	exitm<_mm_setcsr((_mm_getcsr() & ~_MM_MASK_MASK) | (mask))>
	endm

_MM_GET_EXCEPTION_MASK macro
	exitm<(_mm_getcsr() & _MM_MASK_MASK)>
	endm

_MM_SET_ROUNDING_MODE macro mode
	exitm<_mm_setcsr((_mm_getcsr() & ~_MM_ROUND_MASK) | (mode))>
	endm

_MM_GET_ROUNDING_MODE macro
	exitm<(_mm_getcsr() & _MM_ROUND_MASK)>
	endm

_MM_SET_FLUSH_ZERO_MODE macro mode
	exitm<_mm_setcsr((_mm_getcsr() & ~_MM_FLUSH_ZERO_MASK) | (mode))>
	endm

_MM_GET_FLUSH_ZERO_MODE macro
	exitm<(_mm_getcsr() & _MM_FLUSH_ZERO_MASK)>
	endm


_mm_add_ss	proto :oword, :oword
_mm_add_ps	proto :oword, :oword
_mm_sub_ss	proto :oword, :oword
_mm_sub_ps	proto :oword, :oword
_mm_mul_ss	proto :oword, :oword
_mm_mul_ps	proto :oword, :oword
_mm_div_ss	proto :oword, :oword
_mm_div_ps	proto :oword, :oword
_mm_sqrt_ss	proto :oword
_mm_sqrt_ps	proto :oword
_mm_rcp_ss	proto :oword
_mm_rcp_ps	proto :oword
_mm_rsqrt_ss	proto :oword
_mm_rsqrt_ps	proto :oword
_mm_min_ss	proto :oword, :oword
_mm_min_ps	proto :oword, :oword
_mm_max_ss	proto :oword, :oword
_mm_max_ps	proto :oword, :oword

_mm_and_ps	proto :oword, :oword
_mm_andnot_ps	proto :oword, :oword
_mm_or_ps	proto :oword, :oword
_mm_xor_ps	proto :oword, :oword

_mm_cmpeq_ss	proto :oword, :oword
_mm_cmpeq_ps	proto :oword, :oword
_mm_cmplt_ss	proto :oword, :oword
_mm_cmplt_ps	proto :oword, :oword
_mm_cmple_ss	proto :oword, :oword
_mm_cmple_ps	proto :oword, :oword
_mm_cmpgt_ss	proto :oword, :oword
_mm_cmpgt_ps	proto :oword, :oword
_mm_cmpge_ss	proto :oword, :oword
_mm_cmpge_ps	proto :oword, :oword
_mm_cmpneq_ss	proto :oword, :oword
_mm_cmpneq_ps	proto :oword, :oword
_mm_cmpnlt_ss	proto :oword, :oword
_mm_cmpnlt_ps	proto :oword, :oword
_mm_cmpnle_ss	proto :oword, :oword
_mm_cmpnle_ps	proto :oword, :oword
_mm_cmpngt_ss	proto :oword, :oword
_mm_cmpngt_ps	proto :oword, :oword
_mm_cmpnge_ss	proto :oword, :oword
_mm_cmpnge_ps	proto :oword, :oword
_mm_cmpord_ss	proto :oword, :oword
_mm_cmpord_ps	proto :oword, :oword
_mm_cmpunord_ss proto :oword, :oword
_mm_cmpunord_ps proto :oword, :oword
_mm_comieq_ss	proto :oword, :oword
_mm_comilt_ss	proto :oword, :oword
_mm_comile_ss	proto :oword, :oword
_mm_comigt_ss	proto :oword, :oword
_mm_comige_ss	proto :oword, :oword
_mm_comineq_ss	proto :oword, :oword
_mm_ucomieq_ss	proto :oword, :oword
_mm_ucomilt_ss	proto :oword, :oword
_mm_ucomile_ss	proto :oword, :oword
_mm_ucomigt_ss	proto :oword, :oword
_mm_ucomige_ss	proto :oword, :oword
_mm_ucomineq_ss proto :oword, :oword

_mm_cvt_ss2si	proto :oword
_mm_cvtt_ss2si	proto :oword
_mm_cvt_si2ss	proto :oword, :sdword
_mm_cvtss_f32	proto :oword

ifdef _M_IX86
_mm_cvt_ps2pi	proto :oword
_mm_cvtt_ps2pi	proto :oword
_mm_cvt_pi2ps	proto :oword, :qword
endif

ifdef _M_X64
_mm_cvtss_si64	proto :oword
_mm_cvttss_si64 proto :oword
_mm_cvtsi64_ss	proto :oword, :qword
endif

_mm_shuffle_ps	proto :oword, :oword, :sdword
_mm_unpackhi_ps proto :oword, :oword
_mm_unpacklo_ps proto :oword, :oword
_mm_loadh_pi	proto :oword, :ptr
_mm_movehl_ps	proto :oword, :oword
_mm_movelh_ps	proto :oword, :oword
_mm_storeh_pi	proto :ptr, :oword
_mm_loadl_pi	proto :oword, :ptr
_mm_storel_pi	proto :ptr, :oword
_mm_movemask_ps proto :oword


ifdef _M_IX86
_m_pextrw	proto :qword, :sdword
_m_pinsrw	proto :qword, :sdword, :sdword
_m_pmaxsw	proto :qword, :qword
_m_pmaxub	proto :qword, :qword
_m_pminsw	proto :qword, :qword
_m_pminub	proto :qword, :qword
_m_pmovmskb	proto :qword
_m_pmulhuw	proto :qword, :qword
_m_pshufw	proto :qword, :sdword
_m_maskmovq	proto :qword, :qword, :ptr
_m_pavgb	proto :qword, :qword
_m_pavgw	proto :qword, :qword
_m_psadbw	proto :qword, :qword
endif

_mm_set_ss	proto :real4
_mm_set_ps1	proto :real4
_mm_set_ps	proto :real4, :real4, :real4, :real4
_mm_setr_ps	proto :real4, :real4, :real4, :real4
_mm_setzero_ps	proto
_mm_load_ss	proto :ptr
_mm_load_ps1	proto :ptr
_mm_load_ps	proto :ptr
_mm_loadr_ps	proto :ptr
_mm_loadu_ps	proto :ptr
_mm_store_ss	proto :ptr, :oword
_mm_store_ps1	proto :ptr, :oword
_mm_store_ps	proto :ptr, :oword
_mm_storer_ps	proto :ptr, :oword
_mm_storeu_ps	proto :ptr, :oword
_mm_prefetch	proto :ptr, :sdword
if defined(_M_IX86)
_mm_stream_pi	proto :ptr, :qword
endif
_mm_stream_ps	proto :ptr, :oword
_mm_move_ss	proto :oword, :oword

_mm_sfence	proto
_mm_getcsr	proto
_mm_setcsr	proto :sdword

ifdef __ICL
_mm_malloc	proto __cdecl :size_t, :size_t
_mm_free	proto __cdecl :ptr
endif

ifdef _M_IX86
_mm_cvtps_pi32		equ <_mm_cvt_ps2pi>
_mm_cvttps_pi32		equ <_mm_cvtt_ps2pi>
_mm_cvtpi32_ps		equ <_mm_cvt_pi2ps>
_mm_extract_pi16	equ <_m_pextrw>
_mm_insert_pi16		equ <_m_pinsrw>
_mm_max_pi16		equ <_m_pmaxsw>
_mm_max_pu8		equ <_m_pmaxub>
_mm_min_pi16		equ <_m_pminsw>
_mm_min_pu8		equ <_m_pminub>
_mm_movemask_pi8	equ <_m_pmovmskb>
_mm_mulhi_pu16		equ <_m_pmulhuw>
_mm_shuffle_pi16	equ <_m_pshufw>
_mm_maskmove_si64	equ <_m_maskmovq>
_mm_avg_pu8		equ <_m_pavgb>
_mm_avg_pu16		equ <_m_pavgw>
_mm_sad_pu8		equ <_m_psadbw>
endif
_mm_cvtss_si32		equ <_mm_cvt_ss2si>
_mm_cvttss_si32		equ <_mm_cvtt_ss2si>
_mm_cvtsi32_ss		equ <_mm_cvt_si2ss>
_mm_set1_ps		equ <_mm_set_ps1>
_mm_load1_ps		equ <_mm_load_ps1>
_mm_store1_ps		equ <_mm_store_ps1>

ifdef _M_IX86
_mm_cvtpi16_ps macro _A
	endm
_mm_cvtpu16_ps macro _A
	endm
_mm_cvtps_pi16 macro _A
	endm
_mm_cvtpi8_ps macro _A
	endm
_mm_cvtpu8_ps macro _A
	endm
_mm_cvtps_pi8 macro _A
	endm
_mm_cvtpi32x2_ps macro _A, _B
	endm
endif

endif
