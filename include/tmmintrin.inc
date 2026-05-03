ifndef _INCLUDED_TMM
define _INCLUDED_TMM
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
include pmmintrin.inc
ifdef _MM2_FUNCTIONALITY
;; support old notation
ifndef _MM_FUNCTIONALITY
define _MM_FUNCTIONALITY
endif
endif

_mm_hadd_epi16 macro a, b
	phaddw a,b
	retm<a>
	endm
_mm_hadd_epi32 macro a, b
	phaddd a,b
	retm<a>
	endm
_mm_hadds_epi16 macro a, b
	phaddsw a,b
	retm<a>
	endm

ifdef _M_IX86
_mm_hadd_pi16 macro a, b
	phaddw a,b
	retm<a>
	endm
_mm_hadd_pi32 macro a, b
	phaddd a,b
	retm<a>
	endm
_mm_hadds_pi16 macro a, b
	phaddsw a,b
	retm<a>
	endm
endif

_mm_hsub_epi16 macro a, b
	phsubw a,b
	retm<a>
	endm
_mm_hsub_epi32 macro a, b
	phsubd a,b
	retm<a>
	endm
_mm_hsubs_epi16 macro a, b
	phsubsw a,b
	retm<a>
	endm

ifdef _M_IX86
_mm_hsub_pi16 macro a, b
	phsubw a,b
	retm<a>
	endm
_mm_hsub_pi32 macro a, b
	phsubd a,b
	retm<a>
	endm
_mm_hsubs_pi16 macro a, b
	phsubsw a,b
	retm<a>
	endm
endif

_mm_maddubs_epi16 macro a, b
	pmaddubsw a,b
	retm<a>
	endm

ifdef _M_IX86
_mm_maddubs_pi16 macro a, b
	pmaddubsw a,b
	retm<a>
	endm
endif

_mm_mulhrs_epi16 macro a, b
	pmulhrsw a,b
	retm<a>
	endm

ifdef _M_IX86
_mm_mulhrs_pi16 macro a, b
	pmulhrsw a,b
	retm<a>
	endm
endif

_mm_shuffle_epi8 macro a, b
	pshufb a,b
	retm<a>
	endm

ifdef _M_IX86
_mm_shuffle_pi8 macro a, b
	pshufb a,b
	retm<a>
	endm
endif

_mm_sign_epi8 macro a, b
	psignb a,b
	retm<a>
	endm
_mm_sign_epi16 macro a, b
	psignw a,b
	retm<a>
	endm
_mm_sign_epi32 macro a, b
	psignd a,b
	retm<a>
	endm

ifdef _M_IX86
_mm_sign_pi8 macro a, b
	psignb a,b
	retm<a>
	endm
_mm_sign_pi16 macro a, b
	psignw a,b
	retm<a>
	endm
_mm_sign_pi32 macro a, b
	psignd a,b
	retm<a>
	endm
endif

_mm_alignr_epi8 macro a, b, i
	palignr a,b,i
	retm<a>
	endm

ifdef _M_IX86
_mm_alignr_pi8 macro a, b, i
	palignr a,b,i
	retm<a>
	endm
endif

_mm_abs_epi8 macro a
	pabsb a,a
	retm<a>
	endm
_mm_abs_epi16 macro a
	pabsw a,a
	retm<a>
	endm
_mm_abs_epi32 macro a
	pabsd a,a
	retm<a>
	endm

ifdef _M_IX86
_mm_abs_pi8 macro a
	pabsb a,a
	retm<a>
	endm
_mm_abs_pi16 macro a
	pabsw a,a
	retm<a>
	endm
_mm_abs_pi32 macro a
	pabsd a,a
	retm<a>
	endm
endif

.pragma list(pop)
endif
