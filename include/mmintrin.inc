ifndef _MMINTRIN_H_INCLUDED
_MMINTRIN_H_INCLUDED equ <>
.pragma list(push, 0)
ifndef __LIBC_INC
 include libc.inc
endif

ifndef _M_IX86
ifndef _M_X64
.err <This header is specific to X86 and X64 targets>
endif
endif
ifdef _M_CEE_PURE
.err <ERROR: EMM intrinsics not supported in the pure mode>
endif

ifndef _WIN64
ifndef _REGS6432
_REGS6432 equ 1
    rax equ <eax>
    rbx equ <ebx>
    rcx equ <ecx>
    rdx equ <edx>
    rdi equ <edi>
    rsi equ <esi>
    rbp equ <ebp>
    rsp equ <esp>
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
_m_empty macro
    emms
    retm<>
    endm
_m_from_int macro i
    movd mm0,i
    retm<mm0>
    endm
_m_to_int macro m
    movd eax,m
    retm<eax>
    endm

_m_packsswb macro a, b
    packsswb a,b
    retm<a>
    endm
_m_packssdw macro a, b
    packssdw a,b
    retm<a>
    endm
_m_packuswb macro a, b
    packuswb a,b
    retm<a>
    endm
_m_punpckhbw macro a, b
    punpckhbw a,b
    retm<a>
    endm
_m_punpckhwd macro a, b
    punpckhwd a,b
    retm<a>
    endm
_m_punpckhdq macro a, b
    punpckhdq a,b
    retm<a>
    endm
_m_punpcklbw macro a, b
    punpcklbw a,b
    retm<a>
    endm
_m_punpcklwd macro a, b
    punpcklwd a,b
    retm<a>
    endm
_m_punpckldq macro a, b
    punpckldq a,b
    retm<a>
    endm

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

_m_psllw macro a, b
    psllw a,b
    retm<a>
    endm
_m_psllwi macro m, imm
    psllw m,imm
    retm<m>
    endm
_m_pslld macro a, b
    pslld a,b
    retm<a>
    endm
_m_pslldi macro m, imm
    pslld m,imm
    retm<m>
    endm
_m_psllq macro a, b
    psllq a,b
    retm<a>
    endm
_m_psllqi macro m, imm
    psllq m,imm
    retm<m>
    endm
_m_psraw macro a, b
    psraw a,b
    retm<a>
    endm
_m_psrawi macro m, imm
    psraw m,imm
    retm<m>
    endm
_m_psrad macro a, b
    psrad a,b
    retm<a>
    endm
_m_psradi macro m, imm
    psrad m,imm
    retm<m>
    endm
_m_psrlw macro a, b
    psrlw a,b
    retm<a>
    endm
_m_psrlwi macro m, imm
    psrlw m,imm
    retm<m>
    endm
_m_psrld macro a, b
    psrld a,b
    retm<a>
    endm
_m_psrldi macro m, imm
    psrld m,imm
    retm<m>
    endm
_m_psrlq macro a, b
    psrlq a,b
    retm<a>
    endm
_m_psrlqi macro m, imm
    psrlq m,imm
    retm<m>
    endm

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
_mm_setzero_si64 macro m:=<mm0>
    pxor m,m
    retm<m>
    endm
_mm_set_pi32 macro d1, d2
    mov rax,(d1 shl 32) or d2
    movd mm0,rax
    retm<mm0>
    endm
_mm_set_pi16 macro w1, w2, w3, w4
    mov rax,(w1 shl 48) or (w2 shl 32) or (w3 shl 16) or w4
    movd mm0,rax
    retm<mm0>
    endm
_mm_set_pi8 macro b1, b2, b3, b4, b5, b6, b7, b8
    mov rax,(b1 shl 56) or (b2 shl 48) or (b3 shl 40) or (b4 shl 32) or (b5 shl 24) or (b6 shl 16) or (b7 shl 8) or b8
    movd mm0,rax
    retm<mm0>
    endm
_mm_set1_pi32 macro d
    mov rax,(d shl 32) or d
    movd mm0,rax
    retm<mm0>
    endm
_mm_set1_pi16 macro w
    mov rax,(w shl 48) or (w shl 32) or (w shl 16) or w
    movd mm0,rax
    retm<mm0>
    endm
_mm_set1_pi8 macro b
    mov rax,(b shl 56) or (b shl 48) or (b shl 40) or (b shl 32) or (b shl 24) or (b shl 16) or (b shl 8) or b
    movd mm0,rax
    retm<mm0>
    endm
_mm_setr_pi32 macro d1, d2
    mov rax,(d2 shl 32) or d1
    movd mm0,rax
    retm<mm0>
    endm
_mm_setr_pi16 macro w1, w2, w3, w4
    mov rax,(w4 shl 48) or (w3 shl 32) or (w2 shl 16) or w1
    movd mm0,rax
    retm<mm0>
    endm
_mm_setr_pi8 macro b1, b2, b3, b4, b5, b6, b7, b8
    mov rax,(b8 shl 56) or (b7 shl 48) or (b6 shl 40) or (b5 shl 32) or (b4 shl 24) or (b3 shl 16) or (b2 shl 8) or b1
    movd mm0,rax
    retm<mm0>
    endm

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

.pragma list(pop)
endif
