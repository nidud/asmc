ifndef _MMINTRIN_H_INCLUDED
_MMINTRIN_H_INCLUDED equ <>

ifndef _M_IX86
ifndef _M_X64
.err <This header is specific to X86 and X64 targets>
endif
endif
ifdef _M_CEE_PURE
.err <ERROR: EMM intrinsics not supported in the pure mode>
endif

ifndef _WIN64
    .686
    .xmm
ifndef _REGS6432
    rax equ <eax>
    rbx equ <ebx>
    rcx equ <ecx>
    rdx equ <edx>
    rdi equ <edi>
    rsi equ <esi>
    rbp equ <ebp>
    rsp equ <esp>
_REGS6432 equ 1
endif
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

;ifdef _M_IX86
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

_m_paddb macro a, b
    paddb a,b
    retm<a>
    endm
_m_paddw macro a, b
    paddw a,b
    retm<a>
    endm
_m_paddd macro a, b
    paddd a,b
    retm<a>
    endm
_m_paddsb macro a, b
    paddsb a,b
    retm<a>
    endm
_m_paddsw macro a, b
    paddsw a,b
    retm<a>
    endm
_m_paddusb macro a, b
    paddusb a,b
    retm<a>
    endm
_m_paddusw macro a, b
    paddusw a,b
    retm<a>
    endm
_m_psubb macro a, b
    psubb a,b
    retm<a>
    endm
_m_psubw macro a, b
    psubw a,b
    retm<a>
    endm
_m_psubd macro a, b
    psubd a,b
    retm<a>
    endm
_m_psubsb macro a, b
    psubsb a,b
    retm<a>
    endm
_m_psubsw macro a, b
    psubsw a,b
    retm<a>
    endm
_m_psubusb macro a, b
    psubusb a,b
    retm<a>
    endm
_m_psubusw macro a, b
    psubusw a,b
    retm<a>
    endm
_m_pmaddwd macro a, b
    pmaddwd a,b
    retm<a>
    endm
_m_pmulhw macro a, b
    pmulhw a,b
    retm<a>
    endm
_m_pmullw macro a, b
    pmullw a,b
    retm<a>
    endm

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
_m_pand macro a, b
    pand a,b
    retm<a>
    endm
_m_pandn macro a, b
    pandn a,b
    retm<a>
    endm
_m_por macro a, b
    por a,b
    retm<a>
    endm
_m_pxor macro a, b
    pxor a,b
    retm<a>
    endm

;; Comparison intrinsics
_m_pcmpeqb macro a, b
    pcmpeqb a,b
    retm<a>
    endm
_m_pcmpeqw macro a, b
    pcmpeqw a,b
    retm<a>
    endm
_m_pcmpeqd macro a, b
    pcmpeqd a,b
    retm<a>
    endm
_m_pcmpgtb macro a, b
    pcmpgtb a,b
    retm<a>
    endm
_m_pcmpgtw macro a, b
    pcmpgtw a,b
    retm<a>
    endm
_m_pcmpgtd macro a, b
    pcmpgtd a,b
    retm<a>
    endm

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
;endif

endif
