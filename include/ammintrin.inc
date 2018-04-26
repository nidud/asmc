ifndef _INCLUDED_AMM
_INCLUDED_AMM equ <>
.pragma list(push, 0)

ifndef _M_IX86
ifndef _M_X64
.err <This header is specific to X86 and X64 targets>
endif
endif
ifdef _M_CEE_PURE
.err <ERROR: This file is not supported in the pure mode!>
endif

_MM_PCOMCTRL_LT		equ 0
_MM_PCOMCTRL_LE		equ 1
_MM_PCOMCTRL_GT		equ 2
_MM_PCOMCTRL_GE		equ 3
_MM_PCOMCTRL_EQ		equ 4
_MM_PCOMCTRL_NEQ	equ 5
_MM_PCOMCTRL_FALSE	equ 6
_MM_PCOMCTRL_TRUE	equ 7

_mm_comlt_epu8 macro v1, v2
	exitm<_mm_com_epu8(v1, v2, _MM_PCOMCTRL_LT)>
	endm
_mm_comle_epu8 macro v1, v2
	exitm<_mm_com_epu8(v1, v2, _MM_PCOMCTRL_LE)>
	endm
_mm_comgt_epu8 macro v1, v2
	exitm<_mm_com_epu8(v1, v2, _MM_PCOMCTRL_GT)>
	endm
_mm_comge_epu8 macro v1, v2
	exitm<_mm_com_epu8(v1, v2, _MM_PCOMCTRL_GE)>
	endm
_mm_comeq_epu8 macro v1, v2
	exitm<_mm_com_epu8(v1, v2, _MM_PCOMCTRL_EQ)>
	endm
_mm_comneq_epu8 macro v1, v2
	exitm<_mm_com_epu8(v1, v2, _MM_PCOMCTRL_NEQ)>
	endm
_mm_comfalse_epu8 macro v1, v2
	exitm<_mm_com_epu8(v1, v2, _MM_PCOMCTRL_FALSE)>
	endm
_mm_comtrue_epu8 macro v1, v2
	exitm<_mm_com_epu8(v1, v2, _MM_PCOMCTRL_TRUE)>
	endm

_mm_comlt_epu16 macro v1, v2
	exitm<_mm_com_epu16(v1, v2, _MM_PCOMCTRL_LT)>
	endm
_mm_comle_epu16 macro v1, v2
	exitm<_mm_com_epu16(v1, v2, _MM_PCOMCTRL_LE)>
	endm
_mm_comgt_epu16 macro v1, v2
	exitm<_mm_com_epu16(v1, v2, _MM_PCOMCTRL_GT)>
	endm
_mm_comge_epu16 macro v1, v2
	exitm<_mm_com_epu16(v1, v2, _MM_PCOMCTRL_GE)>
	endm
_mm_comeq_epu16 macro v1, v2
	exitm<_mm_com_epu16(v1, v2, _MM_PCOMCTRL_EQ)>
	endm
_mm_comneq_epu16 macro v1, v2
	exitm<_mm_com_epu16(v1, v2, _MM_PCOMCTRL_NEQ)>
	endm
_mm_comfalse_epu16 macro v1, v2
	exitm<_mm_com_epu16(v1, v2, _MM_PCOMCTRL_FALSE)>
	endm
_mm_comtrue_epu16 macro v1, v2
	exitm<_mm_com_epu16(v1, v2, _MM_PCOMCTRL_TRUE)>
	endm

_mm_comlt_epu32 macro v1, v2
	exitm<_mm_com_epu32(v1, v2, _MM_PCOMCTRL_LT)>
	endm
_mm_comle_epu32 macro v1, v2
	exitm<_mm_com_epu32(v1, v2, _MM_PCOMCTRL_LE)>
	endm
_mm_comgt_epu32 macro v1, v2
	exitm<_mm_com_epu32(v1, v2, _MM_PCOMCTRL_GT)>
	endm
_mm_comge_epu32 macro v1, v2
	exitm<_mm_com_epu32(v1, v2, _MM_PCOMCTRL_GE)>
	endm
_mm_comeq_epu32 macro v1, v2
	exitm<_mm_com_epu32(v1, v2, _MM_PCOMCTRL_EQ)>
	endm
_mm_comneq_epu32 macro v1, v2
	exitm<_mm_com_epu32(v1, v2, _MM_PCOMCTRL_NEQ)>
	endm
_mm_comfalse_epu32 macro v1, v2
	exitm<_mm_com_epu32(v1, v2, _MM_PCOMCTRL_FALSE)>
	endm
_mm_comtrue_epu32 macro v1, v2
	exitm<_mm_com_epu32(v1, v2, _MM_PCOMCTRL_TRUE)>
	endm

_mm_comlt_epu64 macro v1, v2
	exitm<_mm_com_epu64(v1, v2, _MM_PCOMCTRL_LT)>
	endm
_mm_comle_epu64 macro v1, v2
	exitm<_mm_com_epu64(v1, v2, _MM_PCOMCTRL_LE)>
	endm
_mm_comgt_epu64 macro v1, v2
	exitm<_mm_com_epu64(v1, v2, _MM_PCOMCTRL_GT)>
	endm
_mm_comge_epu64 macro v1, v2
	exitm<_mm_com_epu64(v1, v2, _MM_PCOMCTRL_GE)>
	endm
_mm_comeq_epu64 macro v1, v2
	exitm<_mm_com_epu64(v1, v2, _MM_PCOMCTRL_EQ)>
	endm
_mm_comneq_epu64 macro v1, v2
	exitm<_mm_com_epu64(v1, v2, _MM_PCOMCTRL_NEQ)>
	endm
_mm_comfalse_epu64 macro v1, v2
	exitm<_mm_com_epu64(v1, v2, _MM_PCOMCTRL_FALSE)>
	endm
_mm_comtrue_epu64 macro v1, v2
	exitm<_mm_com_epu64(v1, v2, _MM_PCOMCTRL_TRUE)>
	endm

_mm_comlt_epi8 macro v1, v2
	exitm<_mm_com_epi8(v1, v2, _MM_PCOMCTRL_LT)>
	endm
_mm_comle_epi8 macro v1, v2
	exitm<_mm_com_epi8(v1, v2, _MM_PCOMCTRL_LE)>
	endm
_mm_comgt_epi8 macro v1, v2
	exitm<_mm_com_epi8(v1, v2, _MM_PCOMCTRL_GT)>
	endm
_mm_comge_epi8 macro v1, v2
	exitm<_mm_com_epi8(v1, v2, _MM_PCOMCTRL_GE)>
	endm
_mm_comeq_epi8 macro v1, v2
	exitm<_mm_com_epi8(v1, v2, _MM_PCOMCTRL_EQ)>
	endm
_mm_comneq_epi8 macro v1, v2
	exitm<_mm_com_epi8(v1, v2, _MM_PCOMCTRL_NEQ)>
	endm
_mm_comfalse_epi8 macro v1, v2
	exitm<_mm_com_epi8(v1, v2, _MM_PCOMCTRL_FALSE)>
	endm
_mm_comtrue_epi8 macro v1, v2
	exitm<_mm_com_epi8(v1, v2, _MM_PCOMCTRL_TRUE)>
	endm

_mm_comlt_epi16 macro v1, v2
	exitm<_mm_com_epi16(v1, v2, _MM_PCOMCTRL_LT)>
	endm
_mm_comle_epi16 macro v1, v2
	exitm<_mm_com_epi16(v1, v2, _MM_PCOMCTRL_LE)>
	endm
_mm_comgt_epi16 macro v1, v2
	exitm<_mm_com_epi16(v1, v2, _MM_PCOMCTRL_GT)>
	endm
_mm_comge_epi16 macro v1, v2
	exitm<_mm_com_epi16(v1, v2, _MM_PCOMCTRL_GE)>
	endm
_mm_comeq_epi16 macro v1, v2
	exitm<_mm_com_epi16(v1, v2, _MM_PCOMCTRL_EQ)>
	endm
_mm_comneq_epi16 macro v1, v2
	exitm<_mm_com_epi16(v1, v2, _MM_PCOMCTRL_NEQ)>
	endm
_mm_comfalse_epi16 macro v1, v2
	exitm<_mm_com_epi16(v1, v2, _MM_PCOMCTRL_FALSE)>
	endm
_mm_comtrue_epi16 macro v1, v2
	exitm<_mm_com_epi16(v1, v2, _MM_PCOMCTRL_TRUE)>
	endm

_mm_comlt_epi32 macro v1, v2
	exitm<_mm_com_epi32(v1, v2, _MM_PCOMCTRL_LT)>
	endm
_mm_comle_epi32 macro v1, v2
	exitm<_mm_com_epi32(v1, v2, _MM_PCOMCTRL_LE)>
	endm
_mm_comgt_epi32 macro v1, v2
	exitm<_mm_com_epi32(v1, v2, _MM_PCOMCTRL_GT)>
	endm
_mm_comge_epi32 macro v1, v2
	exitm<_mm_com_epi32(v1, v2, _MM_PCOMCTRL_GE)>
	endm
_mm_comeq_epi32 macro v1, v2
	exitm<_mm_com_epi32(v1, v2, _MM_PCOMCTRL_EQ)>
	endm
_mm_comneq_epi32 macro v1, v2
	exitm<_mm_com_epi32(v1, v2, _MM_PCOMCTRL_NEQ)>
	endm
_mm_comfalse_epi32 macro v1, v2
	exitm<_mm_com_epi32(v1, v2, _MM_PCOMCTRL_FALSE)>
	endm
_mm_comtrue_epi32 macro v1, v2
	exitm<_mm_com_epi32(v1, v2, _MM_PCOMCTRL_TRUE)>
	endm

_mm_comlt_epi64 macro v1, v2
	exitm<_mm_com_epi64(v1, v2, _MM_PCOMCTRL_LT)>
	endm
_mm_comle_epi64 macro v1, v2
	exitm<_mm_com_epi64(v1, v2, _MM_PCOMCTRL_LE)>
	endm
_mm_comgt_epi64 macro v1, v2
	exitm<_mm_com_epi64(v1, v2, _MM_PCOMCTRL_GT)>
	endm
_mm_comge_epi64 macro v1, v2
	exitm<_mm_com_epi64(v1, v2, _MM_PCOMCTRL_GE)>
	endm
_mm_comeq_epi64 macro v1, v2
	exitm<_mm_com_epi64(v1, v2, _MM_PCOMCTRL_EQ)>
	endm
_mm_comneq_epi64 macro v1, v2
	exitm<_mm_com_epi64(v1, v2, _MM_PCOMCTRL_NEQ)>
	endm
_mm_comfalse_epi64 macro v1, v2
	exitm<_mm_com_epi64(v1, v2, _MM_PCOMCTRL_FALSE)>
	endm
_mm_comtrue_epi64 macro v1, v2
	exitm<_mm_com_epi64(v1, v2, _MM_PCOMCTRL_TRUE)>
	endm

;; SSE5 intrinsics
;; Float/double multiply-accumulate

ifndef _MM_NOINLINE

_mm_macc_ps macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm
_mm_macc_pd macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm
_mm_macc_ss macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm
_mm_macc_sd macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm
_mm_maddsub_ps macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm
_mm_maddsub_pd macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm
_mm_msubadd_ps macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm
_mm_msubadd_pd macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm
_mm_msub_ps macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm
_mm_msub_pd macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm
_mm_msub_ss macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm
_mm_msub_sd macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm
_mm_nmacc_ps macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm
_mm_nmacc_pd macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm
_mm_nmacc_ss macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm
_mm_nmacc_sd macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm
_mm_nmsub_ps macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm
_mm_nmsub_pd macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm
_mm_nmsub_ss macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm
_mm_nmsub_sd macro x0:=<xmm0>, x2:=<xmm1>, x2:=<xmm2>
	endm

else

_mm_macc_ps	proto :oword, :oword, :oword
_mm_macc_pd	proto :oword, :oword, :oword
_mm_macc_ss	proto :oword, :oword, :oword
_mm_macc_sd	proto :oword, :oword, :oword
_mm_maddsub_ps	proto :oword, :oword, :oword
_mm_maddsub_pd	proto :oword, :oword, :oword
_mm_msubadd_ps	proto :oword, :oword, :oword
_mm_msubadd_pd	proto :oword, :oword, :oword
_mm_msub_ps	proto :oword, :oword, :oword
_mm_msub_pd	proto :oword, :oword, :oword
_mm_msub_ss	proto :oword, :oword, :oword
_mm_msub_sd	proto :oword, :oword, :oword
_mm_nmacc_ps	proto :oword, :oword, :oword
_mm_nmacc_pd	proto :oword, :oword, :oword
_mm_nmacc_ss	proto :oword, :oword, :oword
_mm_nmacc_sd	proto :oword, :oword, :oword
_mm_nmsub_ps	proto :oword, :oword, :oword
_mm_nmsub_pd	proto :oword, :oword, :oword
_mm_nmsub_ss	proto :oword, :oword, :oword
_mm_nmsub_sd	proto :oword, :oword, :oword

endif

;; Integer multiply-accumulate

_mm_maccs_epi16		proto :oword, :oword, :oword
_mm_macc_epi16		proto :oword, :oword, :oword
_mm_maccsd_epi16	proto :oword, :oword, :oword
_mm_maccd_epi16		proto :oword, :oword, :oword
_mm_maccs_epi32		proto :oword, :oword, :oword
_mm_macc_epi32		proto :oword, :oword, :oword
_mm_maccslo_epi32	proto :oword, :oword, :oword
_mm_macclo_epi32	proto :oword, :oword, :oword
_mm_maccshi_epi32	proto :oword, :oword, :oword
_mm_macchi_epi32	proto :oword, :oword, :oword
_mm_maddsd_epi16	proto :oword, :oword, :oword
_mm_maddd_epi16		proto :oword, :oword, :oword

;; Horizontal add/subtract

_mm_haddw_epi8		proto :oword
_mm_haddd_epi8		proto :oword
_mm_haddq_epi8		proto :oword
_mm_haddd_epi16		proto :oword
_mm_haddq_epi16		proto :oword
_mm_haddq_epi32		proto :oword
_mm_haddw_epu8		proto :oword
_mm_haddd_epu8		proto :oword
_mm_haddq_epu8		proto :oword
_mm_haddd_epu16		proto :oword
_mm_haddq_epu16		proto :oword
_mm_haddq_epu32		proto :oword
_mm_hsubw_epi8		proto :oword
_mm_hsubd_epi16		proto :oword
_mm_hsubq_epi32		proto :oword

;; Vector conditional moves

_mm_cmov_si128		proto :oword, :oword, :oword
_mm_perm_epi8		proto :oword, :oword, :oword

;; Vector shifts and rotates

_mm_rot_epi8		proto :oword, :oword
_mm_rot_epi16		proto :oword, :oword
_mm_rot_epi32		proto :oword, :oword
_mm_rot_epi64		proto :oword, :oword
_mm_roti_epi8		proto :oword, :sdword
_mm_roti_epi16		proto :oword, :sdword
_mm_roti_epi32		proto :oword, :sdword
_mm_roti_epi64		proto :oword, :sdword
_mm_shl_epi8		proto :oword, :oword
_mm_shl_epi16		proto :oword, :oword
_mm_shl_epi32		proto :oword, :oword
_mm_shl_epi64		proto :oword, :oword
_mm_sha_epi8		proto :oword, :oword
_mm_sha_epi16		proto :oword, :oword
_mm_sha_epi32		proto :oword, :oword
_mm_sha_epi64		proto :oword, :oword

;; Vector integer comparisons

_mm_com_epu8		proto :oword, :oword, :sdword
_mm_com_epu16		proto :oword, :oword, :sdword
_mm_com_epu32		proto :oword, :oword, :sdword
_mm_com_epu64		proto :oword, :oword, :sdword
_mm_com_epi8		proto :oword, :oword, :sdword
_mm_com_epi16		proto :oword, :oword, :sdword
_mm_com_epi32		proto :oword, :oword, :sdword
_mm_com_epi64		proto :oword, :oword, :sdword

;; Precision control

_mm_frcz_ps		proto :oword
_mm_frcz_pd		proto :oword
_mm_frcz_ss		proto :oword, :oword
_mm_frcz_sd		proto :oword, :oword

;; Control values for permute2 intrinsics
_MM_PERMUTE2_COPY	equ 0 ;; just copy the selected value
;; Note that using the constant 1 would have the same effect as 0
_MM_PERMUTE2_ZEROIF1	equ 2 ;; zero selected value if src3 bit is 1
_MM_PERMUTE2_ZEROIF0	equ 3 ;; zero selected value if src3 bit is 3

;; Permutation
_mm_permute2_ps		proto :oword, :oword, :oword, :sdword
_mm_permute2_pd		proto :oword, :oword, :oword, :sdword

;; YMM versions
_mm256_macc_ps		proto :yword, :yword, :yword
_mm256_macc_pd		proto :yword, :yword, :yword
_mm256_maddsub_ps	proto :yword, :yword, :yword
_mm256_maddsub_pd	proto :yword, :yword, :yword
_mm256_msubadd_ps	proto :yword, :yword, :yword
_mm256_msubadd_pd	proto :yword, :yword, :yword
_mm256_msub_ps		proto :yword, :yword, :yword
_mm256_msub_pd		proto :yword, :yword, :yword
_mm256_nmacc_ps		proto :yword, :yword, :yword
_mm256_nmacc_pd		proto :yword, :yword, :yword
_mm256_nmsub_ps		proto :yword, :yword, :yword
_mm256_nmsub_pd		proto :yword, :yword, :yword
_mm256_cmov_si256	proto :yword, :yword, :yword
_mm256_frcz_ps		proto :yword
_mm256_frcz_pd		proto :yword
_mm256_permute2_ps	proto :yword, :yword, :yword, :sdword
_mm256_permute2_pd	proto :yword, :yword, :yword, :sdword

;; LWP intrinsics

;void
__llwpcb	proto
;void *
__slwpcb	proto
;void
__lwpval32	proto :dword, :dword, :dword
;unsigned
__lwpins32	proto :dword, :dword, :dword
ifdef _M_X64
;void
__lwpval64	proto :qword, :dword, :dword
;unsigned
__lwpins64	proto :qword, :dword, :dword
endif

;;BMI intrinsics

;unsigned
_bextr_u32	proto :dword, :dword, :dword
_andn_u32	proto :dword, :dword
_tzcnt_u32	proto :dword
_lzcnt_u32	proto :dword
_blsr_u32	proto :dword
_blsmsk_u32	proto :dword
_blsi_u32	proto :dword

ifdef _M_X64
_bextr_u64	proto :qword, :dword, :dword
_andn_u64	proto :qword, :qword
_tzcnt_u64	proto :qword
_lzcnt_u64	proto :qword
_blsr_u64	proto :qword
_blsmsk_u64	proto :qword
_blsi_u64	proto :qword
endif

;; TBM intrinsics

_bextri_u32	proto :dword, :dword
_blcfill_u32	proto :dword
_blsfill_u32	proto :dword
_blcs_u32	proto :dword

_tzmsk_u32	proto :dword
_blcic_u32	proto :dword
_blsic_u32	proto :dword
_t1mskc_u32	proto :dword
_blcmsk_u32	proto :dword
_blci_u32	proto :dword

ifdef _M_X64
_bextri_u64	proto :qword, :dword
_blcfill_u64	proto :qword
_blsfill_u64	proto :qword
_blcs_u64	proto :qword
_tzmsk_u64	proto :qword
_blcic_u64	proto :qword
_blsic_u64	proto :qword
_t1mskc_u64	proto :qword
_blcmsk_u64	proto :qword
_blci_u64	proto :qword
endif

;void
_mm_monitorx	proto :ptr, :dword, :dword
_mm_mwaitx	proto :dword, :dword, :dword
_mm_clzero	proto

.pragma list(pop)
endif
