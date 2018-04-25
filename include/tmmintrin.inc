ifndef _INCLUDED_TMM
_INCLUDED_TMM equ <>
ifndef _M_IX86
ifndef _M_X64
.err <This header is specific to X86 and X64 targets>
endif
endif
ifdef _M_CEE_PURE
.err <ERROR: This file is not supported in the pure mode!>
endif
include pmmintrin.inc
ifdef _MM2_FUNCTIONALITY
ifndef _MM_FUNCTIONALITY
_MM_FUNCTIONALITY equ <>
endif
endif

_mm_hadd_epi16	proto :oword, :oword
_mm_hadd_epi32	proto :oword, :oword
_mm_hadds_epi16 proto :oword, :oword

ifdef _M_IX86
_mm_hadd_pi16 proto :sqword, :sqword
_mm_hadd_pi32 proto :sqword, :sqword
_mm_hadds_pi16 proto :sqword, :sqword
endif

_mm_hsub_epi16 proto :oword, :oword
_mm_hsub_epi32 proto :oword, :oword
_mm_hsubs_epi16 proto :oword, :oword

ifdef _M_IX86
_mm_hsub_pi16 proto :sqword, :sqword
_mm_hsub_pi32 proto :sqword, :sqword
_mm_hsubs_pi16 proto :sqword, :sqword
endif

_mm_maddubs_epi16 proto :oword, :oword

ifdef _M_IX86
_mm_maddubs_pi16 proto :sqword, :sqword
endif

_mm_mulhrs_epi16 proto :oword, :oword

ifdef _M_IX86
_mm_mulhrs_pi16 proto :sqword, :sqword
endif

_mm_shuffle_epi8 proto :oword, :oword

ifdef _M_IX86
_mm_shuffle_pi8 proto :sqword, :sqword
endif

_mm_sign_epi8	proto :oword, :oword
_mm_sign_epi16	proto :oword, :oword
_mm_sign_epi32	proto :oword, :oword

ifdef _M_IX86
_mm_sign_pi8	proto :sqword, :sqword
_mm_sign_pi16	proto :sqword, :sqword
_mm_sign_pi32	proto :sqword, :sqword
endif

_mm_alignr_epi8 proto :oword, :oword

ifdef _M_IX86
_mm_alignr_pi8	proto :sqword, :sqword, :sdword
endif

_mm_abs_epi8	proto :oword
_mm_abs_epi16	proto :oword
_mm_abs_epi32	proto :oword

ifdef _M_IX86
_mm_abs_pi8 proto :qword
_mm_abs_pi16 proto :qword
_mm_abs_pi32 proto :qword
endif

endif
