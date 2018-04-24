ifndef _MMINTRIN_H_INCLUDED
_MMINTRIN_H_INCLUDED equ <>
.xlist

ifndef _M_IX86
ifndef _M_X64
.err <This header is specific to X86 and X64 targets>
endif
endif
ifdef _M_CEE_PURE
.err <ERROR: EMM intrinsics not supported in the pure mode>
endif

__m64		union
m64_u64		dq ?
m64_f32		real4 2 dup(?)
m64_i8		sbyte 8 dup(?)
m64_i16		sword 4 dup(?)
m64_i32		sdword 2 dup(?)
m64_i64		sqword ?
m64_u8		db 8 dup(?)
m64_u16		dw 4 dup(?)
m64_u32		dd 2 dup(?)
__m64		ends

ifdef _M_IX86
_m_empty	proto
_m_from_int	proto :sdword
_m_to_int	proto :qword

_m_packsswb	proto :qword, :qword
_m_packssdw	proto :qword, :qword
_m_packuswb	proto :qword, :qword
_m_punpckhbw	proto :qword, :qword
_m_punpckhwd	proto :qword, :qword
_m_punpckhdq	proto :qword, :qword
_m_punpcklbw	proto :qword, :qword
_m_punpcklwd	proto :qword, :qword
_m_punpckldq	proto :qword, :qword

;; Packed arithmetic intrinsics

_m_paddb	proto :qword, :qword
_m_paddw	proto :qword, :qword
_m_paddd	proto :qword, :qword
_m_paddsb	proto :qword, :qword
_m_paddsw	proto :qword, :qword
_m_paddusb	proto :qword, :qword
_m_paddusw	proto :qword, :qword
_m_psubb	proto :qword, :qword
_m_psubw	proto :qword, :qword
_m_psubd	proto :qword, :qword
_m_psubsb	proto :qword, :qword
_m_psubsw	proto :qword, :qword
_m_psubusb	proto :qword, :qword
_m_psubusw	proto :qword, :qword
_m_pmaddwd	proto :qword, :qword
_m_pmulhw	proto :qword, :qword
_m_pmullw	proto :qword, :qword

;; Shift intrinsics

_m_psllw	proto :qword, :qword
_m_psllwi	proto :qword, :sdword
_m_pslld	proto :qword, :qword
_m_pslldi	proto :qword, :sdword
_m_psllq	proto :qword, :qword
_m_psllqi	proto :qword, :sdword
_m_psraw	proto :qword, :qword
_m_psrawi	proto :qword, :sdword
_m_psrad	proto :qword, :qword
_m_psradi	proto :qword, :sdword
_m_psrlw	proto :qword, :qword
_m_psrlwi	proto :qword, :sdword
_m_psrld	proto :qword, :qword
_m_psrldi	proto :qword, :sdword
_m_psrlq	proto :qword, :qword
_m_psrlqi	proto :qword, :sdword

;; Logical intrinsics
_m_pand		proto :qword, :qword
_m_pandn	proto :qword, :qword
_m_por		proto :qword, :qword
_m_pxor		proto :qword, :qword

;; Comparison intrinsics
_m_pcmpeqb	proto :qword, :qword
_m_pcmpeqw	proto :qword, :qword
_m_pcmpeqd	proto :qword, :qword
_m_pcmpgtb	proto :qword, :qword
_m_pcmpgtw	proto :qword, :qword
_m_pcmpgtd	proto :qword, :qword

;; Utility intrinsics
_mm_setzero_si64 proto
_mm_set_pi32	proto :sdword, :sdword
_mm_set_pi16	proto :sword, :sword, :sword, :sword
_mm_set_pi8	proto :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte
_mm_set1_pi32	proto :sdword
_mm_set1_pi16	proto :sword
_mm_set1_pi8	proto :sbyte
_mm_setr_pi32	proto :sdword, :sdword
_mm_setr_pi16	proto :sword, :sword, :sword, :sword
_mm_setr_pi8	proto :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte

;; Alternate intrinsic name definitions
_mm_empty		equ <_m_empty>
_mm_cvtsi32_si64	equ <_m_from_int>
_mm_cvtsi64_si32	equ <_m_to_int>
_mm_packs_pi16		equ <_m_packsswb>
_mm_packs_pi32		equ <_m_packssdw>
_mm_packs_pu16		equ <_m_packuswb>
_mm_unpackhi_pi8	equ <_m_punpckhbw>
_mm_unpackhi_pi16	equ <_m_punpckhwd>
_mm_unpackhi_pi32	equ <_m_punpckhdq>
_mm_unpacklo_pi8	equ <_m_punpcklbw>
_mm_unpacklo_pi16	equ <_m_punpcklwd>
_mm_unpacklo_pi32	equ <_m_punpckldq>
_mm_add_pi8		equ <_m_paddb>
_mm_add_pi16		equ <_m_paddw>
_mm_add_pi32		equ <_m_paddd>
_mm_adds_pi8		equ <_m_paddsb>
_mm_adds_pi16		equ <_m_paddsw>
_mm_adds_pu8		equ <_m_paddusb>
_mm_adds_pu16		equ <_m_paddusw>
_mm_sub_pi8		equ <_m_psubb>
_mm_sub_pi16		equ <_m_psubw>
_mm_sub_pi32		equ <_m_psubd>
_mm_subs_pi8		equ <_m_psubsb>
_mm_subs_pi16		equ <_m_psubsw>
_mm_subs_pu8		equ <_m_psubusb>
_mm_subs_pu16		equ <_m_psubusw>
_mm_madd_pi16		equ <_m_pmaddwd>
_mm_mulhi_pi16		equ <_m_pmulhw>
_mm_mullo_pi16		equ <_m_pmullw>
_mm_sll_pi16		equ <_m_psllw>
_mm_slli_pi16		equ <_m_psllwi>
_mm_sll_pi32		equ <_m_pslld>
_mm_slli_pi32		equ <_m_pslldi>
_mm_sll_si64		equ <_m_psllq>
_mm_slli_si64		equ <_m_psllqi>
_mm_sra_pi16		equ <_m_psraw>
_mm_srai_pi16		equ <_m_psrawi>
_mm_sra_pi32		equ <_m_psrad>
_mm_srai_pi32		equ <_m_psradi>
_mm_srl_pi16		equ <_m_psrlw>
_mm_srli_pi16		equ <_m_psrlwi>
_mm_srl_pi32		equ <_m_psrld>
_mm_srli_pi32		equ <_m_psrldi>
_mm_srl_si64		equ <_m_psrlq>
_mm_srli_si64		equ <_m_psrlqi>
_mm_and_si64		equ <_m_pand>
_mm_andnot_si64		equ <_m_pandn>
_mm_or_si64		equ <_m_por>
_mm_xor_si64		equ <_m_pxor>
_mm_cmpeq_pi8		equ <_m_pcmpeqb>
_mm_cmpeq_pi16		equ <_m_pcmpeqw>
_mm_cmpeq_pi32		equ <_m_pcmpeqd>
_mm_cmpgt_pi8		equ <_m_pcmpgtb>
_mm_cmpgt_pi16		equ <_m_pcmpgtw>
_mm_cmpgt_pi32		equ <_m_pcmpgtd>
endif

.list
endif  ;; _MMINTRIN_H_INCLUDED
