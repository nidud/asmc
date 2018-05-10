ifndef _INCLUDED_WMM
_INCLUDED_WMM equ <>
ifndef _M_IX86
ifndef _M_X64
.err <This header is specific to X86 and X64 targets>
endif
endif
ifdef _M_CEE_PURE
.err <ERROR: Intel Architecture intrinsic functions not supported in the pure mode>
endif

include nmmintrin.inc

;;
;; Principal header file for Intel(R) AES and PCLMULQDQ intrinsics.
;;

_mm_aesdec_si128 macro a, r
	aesdec a,b
	retm<a>
	endm
_mm_aesdeclast_si128 macro a, r
	aesdeclast a,b
	retm<a>
	endm
_mm_aesenc_si128 macro a, r
	aesenc a,b
	retm<a>
	endm
_mm_aesenclast_si128 macro a, r
	aesenclast a,b
	retm<a>
	endm
_mm_aesimc_si128 macro a
	aesimc a,b
	retm<a>
	endm
_mm_aeskeygenassist_si128 macro a, r
	aeskeygenassist a,b
	retm<a>
	endm
_mm_clmulepi64_si128 macro a, b, i
	pclmulqdq a,b,i
	retm<a>
	endm

endif
